/* Copyright(C)
 * not free
 * All right reserved
 *
 * @file load_jpeg_from_sd.c
 *
 * @brief 从SD卡加载jpeg图片显示（注意：jpeg的宽高必须16对齐）
 *
 * 注意：这部分代码从imb_demo.c的JPEG_SD_TEST部分代码copy而来，
 * 用于杰理UI框架搭配从SD卡读取jpeg图片显示功能，具体逻辑可参考
 * imb_demo.c文件的JPEG_SD_TEST宏包住部分。
 *
 * @author
 * @version V1.0.0
 * @date 2023-08-01
 */

#include "system/includes.h"
#include "asm/imb.h"
#include "asm/psram_api.h"
#include "res/jpeg_decoder.h"

#include "load_jpeg_from_sd.h"

#define ENABLE_LOAD_JPG_FROM_SD		0	// 模块使能

#if (ENABLE_LOAD_JPG_FROM_SD)
/* 每次读取的数据长度(不可修改) */
#define BUF_4K_LEN			(4*1024)


/* jpeg文件读取任务名称，根据task_table配置 */
/* 公版参考：{"jpg_sd",           	3,      0,  1024,   0}, */
#define LOAD_JPG_TASK_NAME	"jpg_sd"


struct load_jpeg_handler {
    int has_init;
    void *file;		/* jpeg文件句柄，必须确保指针指向的是全局的变量地址 */

    /* 从SD卡读取JPEG数据，存放到该buf,必须是4K大小,最后一次读到的数据可以小于4k */
    u8 *buf_4k;		// 4K长度的buf缓存
    u32 offset_4k;	// jpeg模块内部需要读取的图片的偏移，4K为单位
    u32 len;		// 某一次读取的长度，不能超过4K

    OS_SEM sem;		// jpeg解码器读文件交互的信号量

    volatile int buf_ok;	// 某一次读取完成标志
    int last_offset_4k;
};

/* 由于只有一个jpeg解码器，因此本模块只设计一个句柄，每次只能解码一张jpeg */
/* static struct load_jpeg_handler *load_jpg_hdl = NULL; */
/* #define __this (load_jpg_hdl) */
static struct load_jpeg_handler load_jpg_hdl = {0};
#define __this (&load_jpg_hdl)



/* ------------------------------------------------------------------------------------*/
/**
 * @brief load_jpg_from_sd_callback 传递给jpeg模块内部的回调函数(由用户实现)
 *
 * 注意：jpeg内部调用该回调时，可能会连续两次传递同一个offset_4k的偏移值，用户可以使用类似
 * 本示例的方式记录上一次的offset_4k(last_offset_4k=offset_4k)，在重复第二次获取相同偏移的
 * 数据时直接返回，不需要重复操作SD卡来获取，加快读取速度。
 *
 * 主要功能：用于发送信号量通知task任务读取jpeg内容
 *
 * @Params _hdl 从sd卡读取jpeg的操作句柄
 * @Params len 读取的实际长度
 * @Params offset_4k 读取的偏移，4K字节为单位
 *
 * @return
 */
/* ------------------------------------------------------------------------------------*/
static u8 *load_jpg_from_sd_callback(void *_hdl, u32 *len, u32 offset_4k)
{
    struct load_jpeg_handler *hdl = (struct load_jpeg_handler *)_hdl;

    hdl->offset_4k = offset_4k;	//通知后台要读取的偏移
    if ((hdl->last_offset_4k == offset_4k) && hdl->len && hdl->buf_4k) {
        *len = hdl->len;	//读取的长度
        return hdl->buf_4k;
    }

    hdl->buf_ok = 0;
    hdl->len = 0;

    os_sem_post(&hdl->sem);	//发信号通知后台

    while (!hdl->buf_ok);	//等待读取完成

    *len = hdl->len;	//读取的长度

    if (hdl->len == 0) {
        hdl->last_offset_4k = -1;
        printf("get jpg_src_data err\n");
        return NULL;
    }

    hdl->last_offset_4k = hdl->offset_4k;

    return hdl->buf_4k;
}


/* ------------------------------------------------------------------------------------*/
/**
 * @brief load_jpg_from_sd_task 通过SD卡文件系统读取jpeg内容(jpeg任务调用)
 *
 * @Params hdl
 */
/* ------------------------------------------------------------------------------------*/
static void load_jpg_from_sd_task(struct load_jpeg_handler *hdl)
{
    int ret;
    int offset = hdl->offset_4k * BUF_4K_LEN;

    hdl->len = 0;
    if (offset >= flen(hdl->file)) {
        printf("sdcard offset overflow err %d, %d", offset, flen(hdl->file));
        return ;
    }

    ret = fseek(hdl->file, offset, SEEK_SET);
    if (ret != 0) {
        printf("sdcard set err %x, %x\n", ret, offset);
        return ;
    }

    ret = fread(hdl->file, hdl->buf_4k, BUF_4K_LEN);
    if ((ret > 0) && (ret <= BUF_4K_LEN)) {
        hdl->len = ret;
    } else {
        printf("sdcard_fread_err %x\n", ret);
    }
}


static OS_SEM lv_sd_task_sem;
static void lv_sd_task(void *arg)
{

    while (1) {
        os_sem_pend(&hdl->sem, 0);
        load_jpg_from_sd_task(hdl);
        hdl->buf_ok = 1;
    }
}



int load_jpg_from_sd_init()
{
    /* if (__this->has_init) { */
    /*     printf("load jpeg from sd handler has init!!!\n"); */
    /*     return 1; */
    /* } */

    /* __this = (struct load_jpeg_handler *)malloc(sizeof(struct load_jpeg_handler)); */
    if (!__this->has_init) {
        os_sem_create(&__this->sem, 0);
        task_create(lv_sd_task, __this, LOAD_JPG_TASK_NAME);
    } else {
        printf("load jpeg from sd handler has init!!!\n");
    }

    if (!__this->buf_4k) {
        __this->buf_4k = imb_malloc(BUF_4K_LEN, true);
    }
    if (!__this->buf_4k) {
        printf("Error: malloc 4k buf faild\n");
        /* free(__this); */
        return -1;
    }

    __this->file = NULL;
    __this->buf_ok = 0;
    __this->last_offset_4k = -1;
    __this->has_init = true;

    return 0;
    /* } */
    /* return -1; */
}

// 关闭时，释放4Kbuf，但不关闭jpg_sd任务，即启动后不关
void load_jpg_from_sd_free(void)
{
    if (__this->has_init) {
        /* os_sem_set(&__this->sem, 0); */

        if (__this->file) {
            fclose(__this->file);
            __this->file = NULL;
        }
        if (__this->buf_4k) {
            imb_free(__this->buf_4k);
            __this->buf_4k = NULL;
        }
        /* free(__this); */
        /* __this = NULL; */
    }
}


int load_jpg_from_sd_start(char *path, int out_format, u8 *addr)
{
    int ret = 0;
    if (__this->has_init && __this->buf_4k) {
        if (__this->file) {
            fclose(__this->file);
            __this->file = NULL;
        }

        __this->file = fopen(path, "r");
        if (!__this->file) {
            printf("sdcard_fopen_err");
            return - 1;
        }
        printf("sdcard_fopen_success: 0x%x\n", __this->file);

        ret = jpeg_dec_init(__this, out_format, load_jpg_from_sd_callback);
        if (ret) {
            printf("jpeg dec init err!\n");
            return -1;
        }

        struct rect rect;
        struct jpeg_decoder_fd *jpg_fd = NULL;
        jpg_fd = jpeg_dec_get_fd();

        rect.left = 0;
        rect.top = 0;
        rect.width = jpg_fd->info.x;	//jpeg图片本身的宽度
        rect.height = jpg_fd->info.y;	//jpeg图片本身的高度

        jpeg_dec_start(&rect, &rect, &rect, addr);
        return 0;
    } else {
        printf("Error: load jpeg module uninit!\n");
        return -1;
    }
}

#else

int load_jpg_from_sd_init()
{
    return -1;
}

void load_jpg_from_sd_free(void)
{}

int load_jpg_from_sd_start(char *path, int out_format, u8 *addr)
{
    return -1;
}

#endif






