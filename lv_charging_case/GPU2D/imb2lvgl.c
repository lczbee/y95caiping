#include "system/includes.h"
#include "clock_cfg.h"
#include "asm/imb.h"
#include "asm/img.h"
#include "asm/lcd_buffer_manager.h"
#include "ui/lcd_spi/lcd_drive.h"
#include "ui/ui_pic_index.h"
#include "ui/ui_str_index.h"
#include "res/resfile.h"
#include "asm/psram_api.h"
#include "res/jpeg_decoder.h"
OS_MUTEX jpg_cache_MUTEX;
#include "asm/psram_hw.h"
#include "asm/psram_api.h"

#include "lvgl.h"
#include "usr_pic_index.h"
#include "usr_sd.h"

#include "imb2lvgl.h"
#include "gif/gif.h"

static u8 sd_busy;

struct hentry {
#if LBUF_DEBUG
    int magic_a;
#endif
    struct list_head entry;
    u16 len;
    ///hentry结构体与lbuf_head结构体的头地址的偏移
    u16 offset;
    ///需要被读的次数
    u8 ref;
    ///需要映射的通道
    u8 channel_map;
#if LBUF_DEBUG
    int magic_b;
#endif
    int rets;
};
struct lbuf_test_head {
    u32 len;
    u8 data[0];
};

struct usr_sd_decoder_info {
    void *fp;
    void *cache;
    struct lbuff_head *lbuf_handle;
    struct img_h img_info;
    void **img_data;
    u8 sd_busy;
    u8 cache_full;
    struct img_h pre_img_info;
    lv_timer_t * time;
};
struct FileIndex {
    char *name;
    int addr;
    int len;
};

struct api_ciner_img_info {
    int width;//输入图片的宽和高，可以不是全屏
    int height;//输入图片的宽和高，可以不是全屏
    int format;//输入图片的格式，只支持RGB565/RGB888
    u8 *img_buf;//输入图片
};
struct api_src_block_info {
    struct rect rect;
    u8 *buf;
    u32 buf_size;
};
struct api_scale_info {
    struct rect src;
    struct api_src_block_info *src_block;
    struct rect dst;
    struct rect *dst_block;
    float ratio_w;//缩放比例，必须ratio_w == ratio_h
    float ratio_h;//缩放比例，必须ratio_w == ratio_h
    int width;//背景的宽和高，一般是全屏
    int height;//背景的宽和高，一般是全屏
    int format;//输入图片的格式，只支持RGB565/RGB888
    int bytesperpixel;
    int backcolor;
    int h_block_n;
    int v_block_n;
    u8 to_argb8565;
    u8 *cut_buf[4];
    u32 cut_buf_size[4];
    int max_block_n;
};
struct api_scale_info g_sca_hdl[2];
struct api_scale_info *api_get_blk_sca_info2(struct api_scale_info *sca, int width, int height, float ratio_w, float ratio_h, int x_offset, int y_offset, int limit_h, struct api_ciner_img_info *sca_img, int status);

//文件缓存
struct CacheFile {
    int len;
    u8  data[0];
};
struct CacheFile* readFromCache(char* indexfile);


/*----------------------------------------------------------------------------*/
/**@brief    创建背景任务
   @param    format:合成的格式, 屏驱配置
   @param    width:背景宽度
   @param    height:背景高度
   @param    color:背景颜色(RGB565格式)
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void imb_create_bg_task(u8 format, u16 width, u16 height, u16 color)
{
    struct imb_task_info imb_tsk_info = {0};
    imb_tsk_info.data_src       = DATA_SRC_NONE;//无数据源
    imb_tsk_info.zip_en         = 0;
    imb_tsk_info.in_format      = LAYER_FORMAT_SOLID;//纯色
    imb_tsk_info.out_format     = format;
    imb_tsk_info.x_offset       = 0;
    imb_tsk_info.y_offset       = 0;
    imb_tsk_info.src_w          = width;
    imb_tsk_info.src_h          = height;
    imb_tsk_info.des_w          = width;
    imb_tsk_info.des_h          = height;
    imb_tsk_info.priv           = color;//纯色格式，该参数表示颜色0xr5g6b5
    imb_tsk_info.osd0_in_buf    = 1;
    imb_task_list_init(imb_task_head_get(0), &imb_tsk_info);
}


#if USR_LVGL_IMB2D_EN
#include "ui/ui_core.h"
#include "../lv_frame/lvgl/src/draw/sw/lv_draw_sw.h"
#include "../lv_frame/lvgl/src/core/lv_refr.h"

typedef struct {
    int offset;
    int length;
} IndexEntry;
typedef struct _ui_res_t {
    u8 letter;   //盘符
    u8 mode;   //标识资源名
    u8 *imbindex;  //索引表路径（IMB资源）
    u8 *imbres;    //资源路径（IMB资源）
    RESFILE *resfile;   //资源文件句柄（IMB资源）
    RESFILE *indexfile; //索引表文件句柄（IMB资源）
    int filelen;    //文件数
    int namelen;    //文件长度
    void *cache;    //索引表sram缓存
    struct flash_file_info flash_file_info; //tab表

    void *phyaddr;//    自定义区起始地址
    void *reladdr;//    资源相对于自定义区的地址

} ui_res_t;


/* IMB资源 */
//  ID资源
#define IN_RES_WITH_ID   0  //不支持
#define IMG_BIN_JPG_FILE    1
#define NXP_F_FILE      2
#define IMG_ANIMING_FILE    3


static ui_res_t ui_res_gropu[] = {
    //  纯ID去搜索    
    {.letter = '\0',    .mode = IN_RES_WITH_ID,    .imbres = RES_PATH"ui/ui.res",                                                    },    //文件系统资源
    
    // {.letter = 'A',     .mode = IN_RES_WITH_ID,    .imbres = RES_PATH"ui/ui.res",     },    //code索引表
    // {.letter = 'B',     .mode = IMG_BIN_JPG_FILE,       },    //文件系统资源

    {.letter = 'F',     .mode = NXP_F_FILE,   .imbres = RES_PATH"ui/ui.res",    },    //文件系统资源
    {.letter = 'B',     .mode = IMG_ANIMING_FILE,       },    //文件系统资源
};

//  P->lv普通文件访问




struct rect *image_set_crop(int x, int y, int width, int height)
{
    static struct rect crop = {0};
    crop.left = x;
    crop.top = y;
    crop.width = width;
    crop.height = height;
    return &crop;
}
enum LOAD_METHOD {
    LOAD_FROM_FLASH_WITH_TAB,       //flash数据带地址映射表选择该方式，该方式只支持压缩数据(L1格式除外)
    LOAD_FROM_FLASH_WITHOUT_TAB,    //flash数据不带地址映射表选择该方式，该方式支持压缩数据或者非压缩数据
    LOAD_FROM_RAM,                  //malloc申请的内存选择该方式, imb任务销毁的时候会调用free释放内存
    LOAD_FROM_VLT_RAM,              //malloc_vlt申请的内存选择该方式,imb任务销毁的时候会调用free_vlt释放内存
    LOAD_FROM_PSRAM,                //malloc_psram申请的内存选择该方式,imb任务销毁的时候会调用free_psram释放内存
    LOAD_FROM_RAM_AUTO,             //imb_malloc申请的内存选择该方式(若存在掉电RAM，会优先从掉电RAM里申请)，imb任务销毁的时候会调用imb_free释放内存
    LOAD_FROM_STATIC_RAM,           //若希望外部去释放malloc/malloc_vlt/malloc_psram申请的内存或者或者是一个静态
    //数组时选择该方式，imb任务销毁的时候不对该内存做释放处理
};
static const struct ui_platform_api br28_platform_api = {
    .malloc             = malloc,
    .free               = free,
};
struct bg_buffer {
    u8 *buf;
    int len;
};
static struct flash_file_info g_ui_resfile_info;
static struct flash_file_info g_ui_strfile_info;
static RESFILE *g_ui_resfile = NULL;
static RESFILE *g_ui_strfile = NULL;
struct ui_res_info {
    const char *path;
    struct flash_file_info ui_resfile_info;
    struct flash_file_info ui_strfile_info;
    RESFILE *ui_resfile;
    RESFILE *ui_strfile;
};

struct ui_display {
    struct lcd_interface *lcd;
};
static struct ui_display display = {0};
#define __this (&display)
struct ui_res_info *__this_res = NULL;
u8 *usr_buf = NULL;
//合成一次lines前，获取存放合成输出的buf，根据合成配置的lines(当lines=height，就表示一次合成一帧)而变化,必须要实现
u8 *usr_buf_get(u8 index, u8 *pre_baddr){
    // if((usr_buf >= 0x2000000) && (usr_buf < (0x2000000 + 0x1000000))){
        // psram_flush_invaild_cache(usr_buf, 392*392*2);
    //     return psram_cache2nocache_addr(usr_buf);
    // }


    return usr_buf;    //获取当前正在合成的BUF
}
//如果有buf管理,该接口可用于设置buf写好数据后调用本接口设置成等待状态才能推,不是必要
u8 usr_buf_set_pending(u8 index, u8 *buf){
    // r_printf("%s %d",__func__,__LINE__);
    return 0;
}
//合成一次lines之后，输出到外部的buf,如果lines不等于height（分块合成的时候），
//最后一次合成的数据可能没有lines那么多行，例如454X454的屏，lines=40，最后一次合成的lines只有454-40*11=14行,必须要实现
int usr_draw_area(u8 index, u8 *buf, int left, int top, int width, int height, int wait){
    // r_printf("%s %d ltwh %d %d %d %d",__func__,__LINE__,
    //     left, top, width, height
    // );
    // lcd_draw_area(0, buf, left, top, width, height, 0); 
    // lcd_wait();
    return 0;
}
//判断buffer是不是可以推屏，当没有用我们原本的推屏buf管理模块的时候，不是必要
u8 *usr_buf_check(u8 index, u8 *pre_baddr){
    r_printf("%s %d",__func__,__LINE__);
    return usr_buf;    //获取当前正在合成的BUF
}
//修改buffer状态为空闲,当没有用我们原本的推屏buf管理模块的时候，不是必要
void usr_buf_set_idle(u8 index){
    r_printf("%s %d",__func__,__LINE__);
}
//等待推屏完成，当没有用我们原本的推屏buf管理模块的时候，不是必要
void usr_buf_wait_finish(){
    r_printf("%s %d",__func__,__LINE__);
}
//当使用我们原本的推屏buf管理模块的时候,可以用lcd_draw_area_direct赋值，不是必要
int usr_draw_meld_area(u8 *buf0, u8 *buf1, u8 *meld_buf, int left, int top, int width, int height, int wait){
    r_printf("%s %d",__func__,__LINE__);
}

static u8 *psram_buf1;
static u8 *psram_buf2;
static u8 *psram_act;

/*----------------------------------------------------------------------------*/
/**@brief
   @param   type : 1 - 全屏区域,  2 - 局部区域
   @param   rect : 当前帧需要刷新的区域(该区域会根据buffer大小分成n块)
   @param   lcd_buf : 当前分块buffer的地址
   @param   stride : 当前分块一行像素的字节数（2D硬件加速生成的是4字节对齐，不足4字节则补齐）
   @param   left, top, width, height : 当前分块的范围
   @param   wait : 0 - 中间分块， 1 - 第一个分块， 2 - 最后一个分块(若只有一个分块则为1， 若只有两个分块,则第一个分块为1，第二个分块为2)
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static void imb_data_output(u8 type, struct rect *rect, u8 *lcd_buf, int stride, int left, int top, int width, int height, int wait)
{
    // printf("[%d, %d, %d, %d], block [%d, %d, %d, %d], type:%d, buf:0x%x, stride:%d, wait:%d\n", rect->left, rect->top, rect->width, rect->height, left, top, width, height, type, lcd_buf, stride, wait); 
    
    u8 *p = psram_buf2;
    
    dma_memcpy(psram_cache2nocache_addr(&p[top * stride]), lcd_buf, stride * height);
    // lcd_draw_area(0, lcd_buf, left, top, width, height, 0); 
    /* put_buf(lcd_buf, stride * height); */
    /* os_time_dly(50); */
}


/*----------------------------------------------------------------------------*/
/**@brief   若imb_data_output里面的接口为非阻塞接口(例如dma操作)， 这里需要等待处理完成， 若为阻塞接口，这里不需要改动
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static void imb_data_output_wait_finish(u8 buf_index)
{
    imb_buffer_unlock(buf_index); /* 解锁buffer(必须) */
}
void lcd_disp_init(void *arg, void **buf1, void **buf2, int *lenp)
{
    struct lcd_info info = {0};
    __this->lcd = lcd_get_hdl();
    ASSERT(__this->lcd);

    if (__this->lcd->power_ctrl) {
        __this->lcd->power_ctrl(true);
    }

    if (__this->lcd->init) {
        __this->lcd->init(arg);
    }

    if (__this->lcd->clear_screen) {
        __this->lcd->clear_screen(0x000000);
    }

    if (__this->lcd->backlight_ctrl) {
        __this->lcd->backlight_ctrl(0);
    }

    if (__this->lcd->get_screen_info) {
        __this->lcd->get_screen_info(&info);
    }

    u8 *buf = NULL;
    u32 len;





#if 0   //  单个整BUF(适用屏幕比较小的情况，如240*240)
        *buf1 = malloc(info.width*info.height*2);      
        *buf2 = NULL;
        *lenp = info.width*info.height*2;        
#elif 1 //  2个小BUFFER（屏幕比较大）    
printf(">>>>>>>>>>>>>>>>LCD DOUBLE BUF MALLOC<<<<<<<<<<<<<<<");
mem_stats();
    if (__this->lcd->buffer_malloc) {
        __this->lcd->buffer_malloc(&buf, &len);
    }
    *buf2 = lcd_buffer_init(0, buf, len / info.buf_num, info.buf_num);
    *buf1 = buf;
    *lenp = len;    
mem_stats();
#else   //PSRAM整帧
    len = info.height*info.width*2;
    *lenp = len*2;
    *buf2 = malloc_psram(len);
    *buf1 = malloc_psram(len);
    psram_flush_invaild_cache(*buf2, len);
    psram_flush_invaild_cache(*buf1, len);
#endif
	//	无作用
    struct rect rect;
    rect.left   = 0;
    rect.top    = 0;
    rect.width  = info.width;
    rect.height = info.height;
    ui_core_init(&br28_platform_api, &rect);
}

    // psram_flush_invaild_cache(*buf2, len);
    // psram_flush_invaild_cache(*buf1, len);
int imb_api_init()
{
    int ret = 0;

    //打开图片资源文件
    g_ui_resfile = res_fopen(RES_PATH"ui/ui.res", "r");
    ASSERT(g_ui_resfile);
    //获取图片资源文件flash存储信息
    ret = ui_res_flash_info_get(&g_ui_resfile_info, RES_PATH"ui/ui.res", "res");
    ASSERT(!ret);

    // g_ui_strfile = res_fopen(RES_PATH"ui/ui.str", "r");
    // ASSERT(g_ui_strfile);
    // ret = ui_res_flash_info_get(&g_ui_strfile_info, RES_PATH"ui/ui.str", "res");
    // ASSERT(!ret);

    return 0;
}

int imb_api_uninit()
{
    imb_task_all_destroy(imb_task_head_get(0));
    if (g_ui_resfile) {
        res_fclose(g_ui_resfile);
        g_ui_resfile = NULL;
        ui_res_flash_info_free(&g_ui_resfile_info, "res");
    }

    if (g_ui_strfile) {
        res_fclose(g_ui_strfile);
        g_ui_strfile = NULL;
        ui_res_flash_info_free(&g_ui_strfile_info, "res");
    }

    return 0;
}
struct ui_res_info *ui_res_init()
{
    static struct ui_res_info ui_res_info_t = {0};
    int ret;

    ui_res_info_t.path = RES_PATH"ui/ui.res";

    //打开图片资源文件
    ui_res_info_t.ui_resfile = res_fopen(RES_PATH"ui/ui.res", "r");
    ASSERT(ui_res_info_t.ui_resfile);
    //获取图片资源文件flash存储信息
    ret = ui_res_flash_info_get(&ui_res_info_t.ui_resfile_info, RES_PATH"ui/ui.res", "res");
    ASSERT(!ret);

    ui_res_info_t.ui_strfile = res_fopen(RES_PATH"ui/ui.str", "r");
    ASSERT(ui_res_info_t.ui_strfile);
    ret = ui_res_flash_info_get(&ui_res_info_t.ui_strfile_info, RES_PATH"ui/ui.str", "res");
    ASSERT(!ret);

    __this_res = &ui_res_info_t;
    return &ui_res_info_t;
}

void imb_large_image_scale_optimize_test(struct ui_res_info *info);
s8 open_res(int n);


void lvgl_disp_init(void *arg, void **buf1, void **buf2, int *lcd_w,int *lcd_h, int *colums, int *lines){
    printf("lvgl_task.\n");

    extern char *ui_lib_version();
    printf("lib ver : %s\n", ui_lib_version());

    // struct ui_res_info *res = ui_res_init();
    // imb_api_init();
    
    //屏初始化
    int buflen=0;
    lcd_disp_init(arg, buf1, buf2, &buflen);
    printf("buf1:%x buf2:%x",*buf1,*buf2 );

    struct lcd_info info = {0};
    if (__this->lcd->get_screen_info) {
        __this->lcd->get_screen_info(&info);
    }

    *lcd_w = info.width;
    *lcd_h = info.height;
    *colums = info.width;
    *lines = buflen / info.buf_num / info.stride;



#if   PSRAM_FULL_SCREEN

#if 1//双PSRAM
    psram_buf1 = malloc_psram(info.width*info.height*2);
    psram_buf2 = malloc_psram(info.width*info.height*2);
#else //单psram
    psram_buf1 = malloc_psram(info.width*info.height*2);
#endif
    psram_act = psram_buf1;  // 活动BUF
#endif

}

#if defined(TCFG_PSRAM_DEV_ENABLE) && TCFG_PSRAM_DEV_ENABLE
#define PHY_ADDR(addr) psram_cache2nocache_addr(addr)
#else
#define PHY_ADDR(addr) addr
#endif

volatile u8 usr_wait_te = 0;
volatile u8 usr_full_screen = 1;

void full_screen_flush(){
    struct lcd_info info = {0};
    if (__this->lcd->get_screen_info) {
        __this->lcd->get_screen_info(&info);
    }

    if (NULL == psram_buf2){//0//1   //单PSRAM BUFFER
        lcd_draw_area(0, PHY_ADDR(psram_act), 0, 0, info.width, info.height, usr_wait_te);
    }else{   //双PSRAM BUFFER
        if(psram_act == psram_buf1){ 
            lcd_draw_area(0, PHY_ADDR(psram_act), 0, 0, info.width, info.height, usr_wait_te);
            psram_act = psram_buf2;
        }else{
            lcd_draw_area(0, PHY_ADDR(psram_act), 0, 0, info.width, info.height, usr_wait_te);
            psram_act = psram_buf1;
        }
    }
}

void lv_lcd_data_copy(u8 *lcd_buf, int left, int top, int width, int height)
{
    struct lcd_info info = {0};
    if (__this->lcd->get_screen_info) {
        __this->lcd->get_screen_info(&info);
    }

    int h;
    u8 *p;

    int bytes_per_pixel = 2;
    int lcd_stride = info.width*2;

    p = psram_act;

    if(psram_buf2==NULL) lcd_wait();   
    if ((left == 0) && (width == info.width)) {
        dma_memcpy(PHY_ADDR(&p[top * lcd_stride]), lcd_buf, width * height * bytes_per_pixel);
    } else {
        for (h = 0; h < height; h++) {
            dma_memcpy(PHY_ADDR(&p[(top + h)*lcd_stride + left * bytes_per_pixel]), &lcd_buf[h * width * bytes_per_pixel], width * bytes_per_pixel);
        }
    }
}


struct jpeg_api_info {
    int id;

    u8 out_format;
    void *fat_info;
    jpg_stream_input jpg_ginfo_cb;
    struct jpeg_decoder_fd *jpg_fd;
};

struct jpeg_api_out_lines {
    struct rect jpeg_page_rect;
    struct rect cur_draw;
    struct rect control_draw;//控件相对背景的实际范围，图片可能比控件大
    u8 *outbuf;
};
// static struct flash_file_info g_ui_resfile_info = {0};
static struct flash_file_info g_jpg_flash_info = {0};

static struct flash_file_info *jpeg_api_get_finfo(int id, struct image_file *f)
{
    struct flash_file_info *flash_info = NULL;
    u32 filelen;
    u32 flash_map_tab_num;
    u32 file_base_addr;

    if (!g_ui_resfile_info.tab) {
        printf("e1\n");
        return NULL;
    }

    int ret = open_image_by_id(0, g_ui_resfile, f, id & 0xffff, id >> 16);
    if (ret != 0) {
        printf("e2\n");
        return NULL;
    }

    flash_info = &g_jpg_flash_info;

    imb_task_lock();

    filelen = f->len;
    flash_info->tab = &g_ui_resfile_info.tab[(f->offset + g_ui_resfile_info.offset) / 4096];
    file_base_addr = flash_info->tab[0] + (f->offset + g_ui_resfile_info.offset) % 4096;
    flash_map_tab_num = (file_base_addr % 4096 + filelen + 4096 - 1) / 4096;
    flash_info->offset = file_base_addr % 4096;
    flash_info->tab_size = flash_map_tab_num * sizeof(u32);
    flash_info->last_tab_data_len = flash_map_tab_num * 4096 - filelen - flash_info->offset;

    imb_task_unlock();

    return flash_info;
}
void *test_vuf;
static u8 *usr_jpg_dec_stream_input(void *__fat_info, u32 *len, u32 offset_4k);
int jpeg_api_get_info(struct jpeg_api_info *info)
{
    struct jpeg_decoder_fd *jpg_fd;
    struct image_file file;
    int ret;

    jpg_fd = jpeg_dec_get_fd();
    if ((!jpg_fd) || (!jpg_fd->fat_info) || (!jpg_fd->info.x)
        || (jpg_fd->fat_info != info->fat_info)) {

        info->fat_info = jpeg_api_get_finfo(info->id, &file);
        if (info->fat_info == NULL) {
            printf("jpg get info err1\n");
            return -1;
        // }
        }

        imb_task_lock();
        ret = jpeg_dec_init(info->fat_info, info->out_format, info->jpg_ginfo_cb);
        imb_task_unlock();
        if (ret != 0) {
            printf("jpg get info err2\n");
            return -1;
        }
    }

    /* info->out_format = info->out_format;  */
    /* info->jpg_ginfo_cb = info->jpg_ginfo_cb; */
    info->jpg_fd = jpeg_dec_get_fd();

    return 0;
}

// static u8 *jpg_dec_stream_input(void *__fat_info, u32 *len, u32 offset_4k)
// {
//     struct jpeg_decfile_info *info = (struct jpeg_decfile_info *)__fat_info;
//     u8 *jpg_stream = info->jpg_stream;
//     int file_len = info->jpg_file_len;
//     u32 offset = offset_4k * 4096;
//     u32 res_len;

//     if (offset >= file_len) {
//         *len = 0;
//         return NULL;
//     }
//     res_len = file_len - offset;
//     *len = (res_len > 4096) ? 4096 : res_len;

//     return jpg_stream + offset;
// }




int jpeg_api_open(struct jpeg_api_info *info)
{
    int ret;
    struct image_file file;

    info->fat_info = jpeg_api_get_finfo(info->id, &file);
    if (info->fat_info == NULL) {
        return -1;
    // }
    }
// struct flash_file_info *p = info->fat_info;
    // printf("llen offset tab tabsize %d %d %d %d",
    //     p->last_tab_data_len,
    //     p->offset,
    //     p->tab,
    //     p->tab_size
    // );
    

    imb_task_lock();
    ret = jpeg_dec_init(info->fat_info, info->out_format, info->jpg_ginfo_cb);
    imb_task_unlock();
    if (ret != 0) {
        printf("jpg get info err\n");
        return -1;
    }
    info->jpg_fd = jpeg_dec_get_fd();

    return 0;
}
int jpeg_api_close(struct jpeg_api_info *info)
{
    jpeg_dec_uninit();

    memset(&g_jpg_flash_info, 0, sizeof(struct flash_file_info));
    return 0;
}
int jpeg_api_read_lines(struct jpeg_api_info *info, struct jpeg_api_out_lines *out)
{
    struct jpeg_decoder_fd *jpg_fd;
    struct rect *jpeg_page_rect = &out->jpeg_page_rect;
    struct rect *cur_draw = &out->cur_draw;
    struct rect *control_draw = &out->control_draw;//控件相对背景的实际范围，图片可能比控件大
    struct rect jpeg_rect;
    struct rect draw_rect;
    struct rect r;
    int ret;

    if (!get_rect_cover(jpeg_page_rect, cur_draw, &r)) {
        /* printf("jpeg not in area1\n"); */
        return -1;
    }
    if (!get_rect_cover(control_draw, &r, &draw_rect)) {
        /* printf("jpeg not in area2\n"); */
        return -1;
    }

    jpg_fd = jpeg_dec_get_fd();
    jpeg_rect.left = draw_rect.left - jpeg_page_rect->left;
    jpeg_rect.top = draw_rect.top - jpeg_page_rect->top;
    jpeg_rect.width = draw_rect.width;
    jpeg_rect.height = draw_rect.height;

    if ((jpeg_rect.left < 0) || (jpeg_rect.top < 0)
        || (jpeg_rect.left + jpeg_rect.width > jpg_fd->info.x)
        || (jpeg_rect.top + jpeg_rect.height > jpg_fd->info.y)) {
        printf("\nerr_draw_jpeg %d, %d, %d, %d, %d, %d\n", jpeg_rect.left, jpeg_rect.top, jpeg_rect.width, jpeg_rect.height, jpg_fd->info.x, jpg_fd->info.y);
        return -1;
    }

    /* printf("top %d, %d\n", jpeg_rect.top, cur_draw->top); */
    /* printf("top %d\n", jpeg_rect.top); */
    /* printf("top %d\n", cur_draw->top); */

    imb_task_lock();
    // putchar('A');
    
    ret = jpeg_dec_start(cur_draw, &draw_rect, &jpeg_rect, out->outbuf);
    // putchar('B');
    imb_task_unlock();

    return 0;
}
void imb_jpeg_draw(struct rect rect,
    int px,int py,int pw, int ph, 
    int id, void *buf, int bufsize){

    struct lcd_info info = {0};
    __this->lcd = lcd_get_hdl();
    if (__this->lcd->get_screen_info) {
        __this->lcd->get_screen_info(&info);
    }
    static struct jpeg_api_info api_info = {0};
    static struct jpeg_api_out_lines out = {0};
    static struct jpeg_decoder_fd *jpg_fd = NULL;
    int h, width, height;
    u32 pixel_lines;
    u32 pixel_len;
    u8 plane_num;
    u8 *pre_baddr;
    memset(&api_info, 0 ,sizeof(struct jpeg_api_info));
    /* api_info.id = PAGE0_0000_KK; */
    api_info.id = id;
    api_info.out_format = OUTPUT_FORMAT_RGB565;//支持565
    api_info.jpg_ginfo_cb = NULL;
    api_info.jpg_fd = NULL;

    /* api_info.id = PAGE0_0000_TEST3; */
    int ret = jpeg_api_get_info(&api_info);
    if (ret != 0) {
        printf("get info err\n");
        while (1);
    }

    ret = jpeg_api_open(&api_info);
    if (ret != 0) {
        printf("jpg open err\n");
        while (1);
    }

    jpg_fd = api_info.jpg_fd;
    width = jpg_fd->info.x;//jpeg图片本身的宽度
    height = jpg_fd->info.y;//jpeg图片本身的高度


    //jpeg图片原本的范围，相对于背景
    out.jpeg_page_rect.left = px;
    out.jpeg_page_rect.top = py;
    out.jpeg_page_rect.width = pw;
    out.jpeg_page_rect.height = ph;

    //需要合成的范围，该范围必须在jpeg范围内，相对于背景
    memcpy(&out.control_draw, &out.jpeg_page_rect, sizeof(struct rect));

    // printf("w %d, h %d\n", width, height);

    //合成区域
    out.cur_draw.left = rect.left;
    out.cur_draw.top = rect.top;
    out.cur_draw.width = rect.width;//屏幕的宽
    out.cur_draw.height = rect.height;//屏幕推一次的高
    out.outbuf = buf;

    // printf("rect %d %d %d %d", rect.left, rect.top, rect.width, rect.height);
    // printf("pxywh %d %d %d %d %x", px,py,pw,ph , buf);
    lcd_buffer_idle(0);
    ret = jpeg_api_read_lines(&api_info, &out);
    lcd_buffer_pending(0, out.outbuf);
    jpeg_api_close(&api_info);



}
const char *fs_get_equre(const char *fn)
{
    size_t i;
    for (i = strlen(fn); i > 0; i--) {
        if (fn[i] == '=') {
            return &fn[i + 1];
        } else if (fn[i] == '/' || fn[i] == '\\') {
            return ""; /*No extension if a '\' or '/' found*/
        }
    }

    return ""; /*Empty string if no '.' in the file name.*/
}

int hex_to_int(char *hex_string) {
    int result = 0;
    int len = strlen(hex_string);
    for (int i = 0; i < len; i++) {
        char c = hex_string[i];
        if (c >= '0' && c <= '9') {
            result = result * 16 + (c - '0');
        } else if (c >= 'a' && c <= 'f') {
            result = result * 16 + (c - 'a' + 10);
        } else if (c >= 'A' && c <= 'F') {
            result = result * 16 + (c - 'A' + 10);
        } else {
            printf("Invalid hex string!\n");
            return -1;
        }
    }
    return result;
}

// int get_jl_image_info_by_src(const void *src, lv_img_header_t *header, struct image_file *file)
// {
//     int ret;
//     if (memcmp("JL2DZIP/", src, strlen("JL2DZIP/"))){
//         return 0;
//     }
//     int i,id=0;
    
//     char *name = lv_fs_get_last(src);

//     char *idstr = fs_get_equre(src);
//     if(*idstr){
//         id = hex_to_int(idstr);
//         // printf("idstr SUCCEED %s %d", name,id);
//     } else {
//         for(i=0;i<get_img_num();i++){
//             extern const struct fid my_fid[];
//             if(!strcmp(my_fid[i].name, src)){
//                 id = my_fid[i].id;
//                 // printf("noidstr SUCCEED %s %d", name,id);
//                 break;
//             }
//         }
//     }

//     if(i == get_img_num()){
//         return 0;
//     }
    
//     if(!__this_res){
//         return 0;   
//     }

//     struct image_file file_t;
//     if(file==NULL){
//         file = &file_t;
//     }
//     ret = open_image_by_id(0, __this_res->ui_resfile, file, id & 0xffff, id >> 16);
//     if(ret){
//         return 0;
//     }

//     if(!header){
//         return id;
//     }   
//     // printf("wh format: %d %d %d", file->width, file->height, file->format);
//     header->w  = file->width;
//     header->h  = file->height;
//     if(file->format == 8){
//         header->cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
//     } else {
//         header->cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
//     }

//     return id;
// }
int imb_task_get_id()
{
    static int task_id = 0;
    return ++task_id;
}


/*----------------------------------------------------------------------------*/
/**@brief    创建图片缩放任务
   @param    task_id : 任务id
   @param    file:图片信息
   @param    priv : LOAD_FROM_FLASH_WITH_TAB时为flash_file_info, 其他为图像数据的地址
   @param    ratio_w:水平放大倍率
   @param    ratio_h:垂直放大倍率
   @param    x:相对背景的x坐标
   @param    y:相对背景的y坐标
   @param    width:显示的图片宽度（放大后的宽度）
   @param    height:显示的图片高度（放大后的高度）
   @param    crop:为空时不对图片进行裁剪, 非空时为图片的裁剪区域
   @param    zip:是否压缩数据
   @param    load_method:数据的加载方式, 具体参考enum LOAD_METHOD
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void imb_create_image_scale_task(int task_id, struct image_file *file, u32 priv, float ratio_w, float ratio_h, int x, int y, int width, int height, struct rect *crop, int zip, int load_method)
{
    struct imb_task_info imb_tsk_info = {0};
    struct imb_task *p = NULL;

    imb_tsk_info.elm_id = task_id;
    imb_tsk_info.scale_en = 1;//true;//缩放使能
    if (imb_tsk_info.scale_en) {
        imb_tsk_info.ratio_w = ratio_w;
        imb_tsk_info.ratio_h = ratio_h;
        ASSERT(imb_tsk_info.ratio_w);
        ASSERT(imb_tsk_info.ratio_h);
    }

    if (load_method == LOAD_FROM_FLASH_WITH_TAB) {
        imb_tsk_info.data_src = DATA_SRC_FLASH;
        imb_tsk_info.cur_in_flash = 1;
    } else {
        imb_tsk_info.data_src = DATA_SRC_SRAM;
        imb_tsk_info.cur_in_flash = 0;
    }

    if (file->format == PIXEL_FMT_L1) {
        imb_tsk_info.zip_en     = 0;
    } else {
        imb_tsk_info.zip_en     = zip;
    }

    if (load_method == LOAD_FROM_FLASH_WITH_TAB || load_method == LOAD_FROM_FLASH_WITHOUT_TAB) {
        imb_tsk_info.addr_source = SOURCE_FLASH;
    } else if (load_method == LOAD_FROM_RAM_AUTO) {
        imb_tsk_info.addr_source = SOURCE_DEFAULT;
    } else if (load_method == LOAD_FROM_RAM) {
        imb_tsk_info.addr_source = SOURCE_RAM;
    } else if (load_method == SOURCE_VLT_RAM) {
        imb_tsk_info.addr_source = SOURCE_VLT_RAM;
    } else if (load_method == SOURCE_PSRAM) {
        imb_tsk_info.addr_source = SOURCE_PSRAM;
    } else if (load_method == SOURCE_STATIC_RAM) {
        imb_tsk_info.addr_source = SOURCE_STATIC_RAM;
    }

    imb_tsk_info.in_format      = file->format;
    imb_tsk_info.x_offset       = x;
    imb_tsk_info.y_offset       = y;
    imb_tsk_info.src_w          = file->width;
    imb_tsk_info.src_h          = file->height;
    imb_tsk_info.des_w          = width;
    imb_tsk_info.des_h          = height;

    if (load_method == LOAD_FROM_FLASH_WITH_TAB) {
        imb_tsk_info.ff_info = priv;
        imb_tsk_info.priv = (u32)file;
    } else {
        imb_tsk_info.priv = (u32)priv;
    }

    if (imb_tsk_info.in_format == PIXEL_FMT_L1) {
        imb_tsk_info.l1_type        = L1_IMAGE;
    }

    //裁剪区域
    if (crop) {
        imb_tsk_info.rotate_scale_crop_en = 1;
        imb_tsk_info.crop.left = crop->left;
        imb_tsk_info.crop.top = crop->top;
        imb_tsk_info.crop.width = crop->width;
        imb_tsk_info.crop.height = crop->height;
    }

    /* elm_id、id(低8位有效)可作为任务的唯一标识，通过该标识搜索任务句柄，若搜到则重置任务信息，没搜到则创建任务 */
    p = imb_task_search_by_id(imb_task_head_get(0), imb_tsk_info.elm_id, imb_tsk_info.id);

    if (p) {
        imb_task_reset(imb_task_head_get(0), p, &imb_tsk_info);
    } else {
        imb_task_list_add(imb_task_head_get(0), &imb_tsk_info);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    创建图片任务
   @param    task_id : 任务id
   @param    file : 图片信息
   @param    priv : LOAD_FROM_FLASH_WITH_TAB时为flash_file_info, 其他为图像数据的地址
   @param    x:相对背景的x坐标
   @param    y:相对背景的y坐标
   @param    width:图片显示的宽度，必须小于或者等于图片的实际宽度，小于实际宽度则截取显示
   @param    height:图片显示的高度，必须小于或者等于图片的实际高度，小于实际高度则截取显示
   @param    crop : 为空时不对图片进行裁剪, 非空时为图片的裁剪区域
   @param    zip : 是否压缩数据
   @param    load_method : 数据的加载方式, 具体参考enum LOAD_METHOD
   @return
   @note     图片存储在flash, 指定flash地址映射表(可以支持数据不连续存储，以4k为单位，中间4k必须填满)
*/
/*----------------------------------------------------------------------------*/
void imb_create_image_task(int task_id, struct image_file *file, u32 priv, int x, int y, int width, int height, struct rect *crop, int zip, int load_method, lv_color_t color)
{
    struct imb_task_info imb_tsk_info = {0};
    struct imb_task *p = NULL;

    imb_tsk_info.elm_id = task_id;
    if (load_method == LOAD_FROM_FLASH_WITH_TAB) {
        imb_tsk_info.data_src = DATA_SRC_FLASH;//直接从flash取数
        imb_tsk_info.cur_in_flash = 1;//数据存在flash
    } else {
        imb_tsk_info.data_src = DATA_SRC_SRAM;
        imb_tsk_info.cur_in_flash = 0;
    }
    if (file->format == PIXEL_FMT_L1) {
        imb_tsk_info.zip_en = 0;
    } else {
        imb_tsk_info.zip_en = zip;
    }
    if (load_method == LOAD_FROM_FLASH_WITH_TAB || load_method == LOAD_FROM_FLASH_WITHOUT_TAB) {
        imb_tsk_info.addr_source = SOURCE_FLASH;
    } else if (load_method == LOAD_FROM_RAM_AUTO) {
        imb_tsk_info.addr_source = SOURCE_DEFAULT;
    } else if (load_method == LOAD_FROM_RAM) {
        imb_tsk_info.addr_source = SOURCE_RAM;
    } else if (load_method == SOURCE_VLT_RAM) {
        imb_tsk_info.addr_source = SOURCE_VLT_RAM;
    } else if (load_method == SOURCE_PSRAM) {
        imb_tsk_info.addr_source = SOURCE_PSRAM;
    } else if (load_method == LOAD_FROM_STATIC_RAM) {
        imb_tsk_info.addr_source = SOURCE_STATIC_RAM;
    }
    imb_tsk_info.in_format = file->format;
    imb_tsk_info.x_offset = x;
    imb_tsk_info.y_offset = y;
    imb_tsk_info.src_w = file->width;
    imb_tsk_info.src_h = file->height;
    imb_tsk_info.des_w = width;
    imb_tsk_info.des_h = height;
    if (load_method == LOAD_FROM_FLASH_WITH_TAB) {
        imb_tsk_info.ff_info = priv;
        imb_tsk_info.priv = (u32)file;
    } else {
        imb_tsk_info.priv = (u32)priv;
    }

    if (imb_tsk_info.in_format == PIXEL_FMT_L1) {
        imb_tsk_info.l1_type = L1_IMAGE;
    }

    //裁剪区域
    if (crop) {
        imb_tsk_info.crop.left = crop->left;
        imb_tsk_info.crop.top = crop->top;
        imb_tsk_info.crop.width = crop->width;
        imb_tsk_info.crop.height = crop->height;
    }

    imb_tsk_info.text_color = (((color.full&0xff)<<8)+(color.full>>8));
    imb_tsk_info.l1_type = L1_TEXT;
 
    /* elm_id、id(低8位有效)可作为任务的唯一标识，通过该标识搜索任务句柄，若搜到则重置任务信息，没搜到则创建任务 */
    p = imb_task_search_by_id(imb_task_head_get(0), imb_tsk_info.elm_id, imb_tsk_info.id);

    if (p) {
        imb_task_reset(imb_task_head_get(0), p, &imb_tsk_info); //imb_task参数重置
    } else {
        imb_task_list_add(imb_task_head_get(0), &imb_tsk_info);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    创建图片旋转任务
   @param    task_id : 任务id
   @param    file:图片信息
   @param    priv:图片存储信息
   @param    cx:图片的旋转中心x坐标，相对于图片
   @param    cy:图片的旋转中心y坐标，相对于图片
   @param    angle:旋转角度(0~359,最小单位1度)
   @param    dx:输出的旋转中心点x坐标，相对于背景
   @param    dy:输出的旋转中心点y坐标，相对于背景
   @param    crop : 为空时不对图片进行裁剪, 非空时为图片的裁剪区域
   @param    load_method : 数据的加载方式, 具体参考enum LOAD_METHOD
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void imb_create_image_rotate_task(int task_id, struct image_file *file, u32 priv, int cx, int cy, int angle, int dx, int dy, struct rect *crop, int load_method)
{
    static struct imb_task_info imb_tsk_info = {0};
    struct imb_task *p = NULL;

    imb_tsk_info.elm_id = task_id;
    imb_tsk_info.rotate_en = 1;
    if (imb_tsk_info.rotate_en) {
        imb_tsk_info.x_src_offset   = 0;
        imb_tsk_info.y_src_offset   = 0;
        imb_tsk_info.rotate_c_x     = cx;
        imb_tsk_info.rotate_c_y     = cy;
        imb_tsk_info.rotate_angle   = angle;
        imb_tsk_info.rotate_dx      = dx;
        imb_tsk_info.rotate_dy      = dy;
        imb_tsk_info.rotate_chunk   = 0;
    }

    if (load_method == LOAD_FROM_FLASH_WITH_TAB) {
        imb_tsk_info.data_src       = DATA_SRC_SRAM;
        imb_tsk_info.cur_in_flash   = 1;//数据存放在flash，内部会先将压缩数据解压到sram, 然后imb从sram取数
    } else {
        imb_tsk_info.data_src       = DATA_SRC_SRAM;
        imb_tsk_info.cur_in_flash   = 0;
        // printf("data_src %x",  printf("addr %x",  imb_tsk_info.priv););
    }

    imb_tsk_info.zip_en         = 0;//旋转不支持压缩格式
    if (load_method == LOAD_FROM_FLASH_WITH_TAB) {
        imb_tsk_info.addr_source = SOURCE_DEFAULT;
    } else if (load_method == LOAD_FROM_FLASH_WITHOUT_TAB) {
        imb_tsk_info.addr_source = SOURCE_FLASH;
    } else if (load_method == LOAD_FROM_RAM_AUTO) {
        imb_tsk_info.addr_source = SOURCE_DEFAULT;
    } else if (load_method == LOAD_FROM_RAM) {
        imb_tsk_info.addr_source = SOURCE_RAM;
    } else if (load_method == LOAD_FROM_VLT_RAM) {
        imb_tsk_info.addr_source = SOURCE_VLT_RAM;
    } else if (load_method == LOAD_FROM_PSRAM) {
        imb_tsk_info.addr_source = SOURCE_PSRAM;
    } else if (load_method == LOAD_FROM_STATIC_RAM) {
        imb_tsk_info.addr_source = SOURCE_STATIC_RAM;
    }

    imb_tsk_info.in_format      = file->format;
    imb_tsk_info.src_w          = file->width;
    imb_tsk_info.src_h          = file->height;
    //旋转这组参数设置无效，默认为背景任务大小
    imb_tsk_info.x_offset       = 0;
    imb_tsk_info.y_offset       = 0;
    imb_tsk_info.des_w          = 0;
    imb_tsk_info.des_h          = 0;

    if (load_method == LOAD_FROM_FLASH_WITH_TAB) {
        imb_tsk_info.ff_info = priv;
        imb_tsk_info.priv = (u32)file;
    } else {
        imb_tsk_info.priv = (u32)priv;
        // printf("addr %x",  imb_tsk_info.priv);
    }

    if (imb_tsk_info.in_format == PIXEL_FMT_L1) {
        imb_tsk_info.l1_type        = L1_IMAGE;
    }

    //裁剪区域
    if (crop) {
        imb_tsk_info.rotate_scale_crop_en = 1;
        imb_tsk_info.crop.left = crop->left;
        imb_tsk_info.crop.top = crop->top;
        imb_tsk_info.crop.width = crop->width;
        imb_tsk_info.crop.height = crop->height;
    }

    // imb_tsk_info.quote = 1;

    /* elm_id、id(低8位有效)可作为任务的唯一标识，通过该标识搜索任务句柄，若搜到则重置任务信息，没搜到则创建任务 */
    p = imb_task_search_by_id(imb_task_head_get(0), imb_tsk_info.elm_id, imb_tsk_info.id);

    if (p) {
        imb_task_reset(imb_task_head_get(0), p, &imb_tsk_info);
    } else {
        imb_task_list_add(imb_task_head_get(0), &imb_tsk_info);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief    图片旋转分块输入回调
   @param    priv:任务信息
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
static void imb_rotate_chunk_cb(void *priv)
{
    struct imb_task_info *tsk_info = (struct imb_task_info *)priv;
    struct imb_task *task = (struct imb_task *)tsk_info->task;
    struct imb_task_head *head = imb_task_head_get(task->root_index);
    struct rect *rect = &head->curr_draw;

    task->x_src_offset = tsk_info->x_src_offset;
    task->src_w = tsk_info->src_w;
    task->y_src_offset = tsk_info->y_src_offset + tsk_info->rotate_chunk_offset_cur;
    task->src_h = (tsk_info->src_h - tsk_info->y_src_offset - tsk_info->rotate_chunk_offset_cur) > tsk_info->rotate_chunk ?
                  tsk_info->rotate_chunk : (tsk_info->src_h - tsk_info->y_src_offset - tsk_info->rotate_chunk_offset_cur);
    task->src_w_pre = tsk_info->src_w;
    task->src_h_pre = tsk_info->src_h;
    task->cur_format = tsk_info->in_format; //LAYER_FORMAT_ARGB8565;

    int stride = image_stride(task->src_w, task->cur_format);
    u16 lut_tab_size = image_palette_size(task->cur_format);

    if (lut_tab_size) {
        printf("lut_tab_size %d", lut_tab_size);
        return;
    }

    int height = tsk_info->rotate_chunk + 1;
    u8* buf1 = tsk_info->rotate_buffer;
    u8* buf2 = (u8*)tsk_info->rotate_buffer + stride * height;

    if (!tsk_info->rotate_buffer) {
        tsk_info->rotate_buffer = (u8 *)imb_malloc(stride * height*2, false);
        // printf("buf:%d",stride * height*2);
        buf1 = tsk_info->rotate_buffer;
        buf2 = (u8*)tsk_info->rotate_buffer + stride * height;

        task->dat_src_adr = buf2;
        u8 * p = (u8*)tsk_info->ff_info + lut_tab_size + stride * task->y_src_offset;

        if ((task->y_src_offset + task->src_h) < task->src_h_pre) {
            // res_fread(file, tsk_info->rotate_buffer, stride * (task->src_h + 1));//为了解决分块输入导致的相位问题，非最后一个分块需要多读取一行像素数据
            dma_memcpy(buf1, p, stride * (task->src_h + 1));
        } else {
            // res_fread(file, tsk_info->rotate_buffer, stride * task->src_h);
            dma_memcpy(buf1, p, stride * task->src_h);
        }
    }

    if(buf1==task->dat_src_adr){
        // 上一次显示的为buf1，上一次拷贝的是buf2
        dma_memcpy_wait_idle();
        // 等上次buf2 copy完了，现在可以用buf2了
        task->dat_src_adr = buf2;
        //  同时预存下一帧，存到buf1
        if ((task->y_src_offset + task->src_h ) >= task->src_h_pre){
            // printf("end");
            return;
        }

        u8 * p = (u8*)tsk_info->ff_info + lut_tab_size + stride * (task->y_src_offset +tsk_info->rotate_chunk);
        if ((task->y_src_offset + task->src_h +tsk_info->rotate_chunk) < task->src_h_pre) {
            // res_fread(file, tsk_info->rotate_buffer, stride * (task->src_h + 1));//为了解决分块输入导致的相位问题，非最后一个分块需要多读取一行像素数据
            dma_memcpy(buf1, p, stride * (task->src_h + 1));
        } else {
            // res_fread(file, tsk_info->rotate_buffer, stride * task->src_h);
            dma_memcpy(buf1, p, stride * task->src_h);
            
        }
    } else if(buf2==task->dat_src_adr) {
        // 上一次显示的为buf2，上一次拷贝的是buf1
        dma_memcpy_wait_idle();
        // 等上次buf1 copy完了，现在可以用buf1显示了
        task->dat_src_adr = buf1;
        //  同时预存下一帧，存到buf2
        if ((task->y_src_offset + task->src_h ) >= task->src_h_pre){
            // printf("end");
            return;
        }

        u8 * p = (u8*)tsk_info->ff_info + lut_tab_size + stride * (task->y_src_offset + tsk_info->rotate_chunk);
        if ((task->y_src_offset + task->src_h + tsk_info->rotate_chunk) < task->src_h_pre ) {
            // res_fread(file, tsk_info->rotate_buffer, stride * (task->src_h + 1));//为了解决分块输入导致的相位问题，非最后一个分块需要多读取一行像素数据
            dma_memcpy(buf2, p, stride * (task->src_h + 1));
        } else {
            // res_fread(file, tsk_info->rotate_buffer, stride * task->src_h);
            dma_memcpy(buf2, p, stride * task->src_h);
            
        }
    }
}
/*----------------------------------------------------------------------------*/
/**@brief    创建图片旋转任务(图片分块拷贝到sram作为输入)
   @param    task_id : 任务id
   @param    file:图片信息
   @param    file_info:图片存储信息
   @param    cx:图片的旋转中心x坐标，相对于图片
   @param    cy:图片的旋转中心y坐标，相对于图片
   @param    angle:旋转角度
   @param    dx:输出的旋转中心点x坐标，相对于背景
   @param    dy:输出的旋转中心点y坐标，相对于背景
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void imb_create_image_rotate_chunk_task(int task_id, struct image_file *file, u32 priv, int cx, int cy, int angle, int dx, int dy, int load_mef)
{
    struct imb_task_info imb_tsk_info = {0};
    struct imb_task *p = NULL;

    imb_tsk_info.elm_id = task_id;
    imb_tsk_info.rotate_en = 1;//旋转使能
    if (imb_tsk_info.rotate_en) {
        imb_tsk_info.x_src_offset   = 0;
        imb_tsk_info.y_src_offset   = 0;
        imb_tsk_info.rotate_c_x     = cx;
        imb_tsk_info.rotate_c_y     = cy;
        imb_tsk_info.rotate_angle   = angle;
        imb_tsk_info.rotate_dx      = dx;
        imb_tsk_info.rotate_dy      = dy;
        imb_tsk_info.rotate_chunk   = 1;

        // printf("rotate:>>  %d  %d  %d  %d  %d  %d  %d",
        //     imb_tsk_info.x_src_offset   ,
        //     imb_tsk_info.y_src_offset   ,
        //     imb_tsk_info.rotate_c_x     ,
        //     imb_tsk_info.rotate_c_y     ,
        //     imb_tsk_info.rotate_angle   ,
        //     imb_tsk_info.rotate_dx      ,
        //     imb_tsk_info.rotate_dy               
        // );

        if (imb_tsk_info.rotate_chunk) {
            imb_tsk_info.rotate_chunk_offset = 0;
            u8 chunk_num = 4;//20;//输入分块数量(分块数量越少，合成速度越快，消耗ram越多)
            imb_tsk_info.rotate_chunk = (file->height / chunk_num + 9) / 10 * 10;//每个分块高度
            imb_tsk_info.rotate_chunk_num = (file->height + imb_tsk_info.rotate_chunk - 1) / imb_tsk_info.rotate_chunk;
        }
    }

    imb_tsk_info.data_src       = DATA_SRC_SRAM;
    imb_tsk_info.cur_in_flash   = 1;
    imb_tsk_info.zip_en         = 0;

    imb_tsk_info.in_format      = file->format;
    imb_tsk_info.src_w          = file->width;
    imb_tsk_info.src_h          = file->height;
    imb_tsk_info.x_offset       = 0;
    imb_tsk_info.y_offset       = 0;
    imb_tsk_info.des_w          = file->width;
    imb_tsk_info.des_h          = file->height;
    imb_tsk_info.ff_info        = (u32)priv;
    imb_tsk_info.priv           = (u32)file;

    if (imb_tsk_info.in_format == PIXEL_FMT_L1) {
        imb_tsk_info.l1_type        = L1_IMAGE;
    }

    if(load_mef != LOAD_FROM_FLASH_WITH_TAB ){
        imb_tsk_info.cb         = imb_rotate_chunk_cb; //注释该句则跑内部的分块流程 
    }

    /* elm_id、id(低8位有效)可作为任务的唯一标识，通过该标识搜索任务句柄，若搜到则重置任务信息，没搜到则创建任务 */
    p = imb_task_search_by_id(imb_task_head_get(0), imb_tsk_info.elm_id, imb_tsk_info.id);

    if (p) {
        imb_task_reset(imb_task_head_get(0), p, &imb_tsk_info);
    } else {
        imb_task_list_add(imb_task_head_get(0), &imb_tsk_info);
    }
}

static void *imb_jpeg_cb(void *priv)
{
    struct imb_task_out *out = (struct imb_task_out *)priv;
    struct jpeg_decoder_fd *jpg_fd;
    struct rect *jpeg_page_rect = out->priv;
    struct rect *cur_draw = &out->rect;
    struct rect jpeg_rect;
    struct rect draw_rect;
    int ret;
    struct imb_task *task = out->task;

    if (task->task_en == false) {
        printf("jpeg task_en == false\n");
        return NULL;
    }

    jpg_fd = jpeg_dec_get_fd();

    if (jpg_fd && (jpg_fd->fat_info != task->flash_file_info)) {
        printf("redec_init\n");
        imb_task_lock();
        jpeg_dec_init(task->flash_file_info, out->format, NULL);
        imb_task_unlock();
    }

    struct rect r;

    if (!get_rect_cover(jpeg_page_rect, cur_draw, &r)) {
        printf("jpeg not in area\n");
        return NULL;
    }

    jpeg_rect.left = r.left - jpeg_page_rect->left;
    jpeg_rect.top = r.top - jpeg_page_rect->top;
    jpeg_rect.width = r.width;
    jpeg_rect.height = r.height;

    if ((jpeg_rect.left < 0) || (jpeg_rect.top < 0)
        || (jpeg_rect.left + jpeg_rect.width > jpg_fd->info.x)
        || (jpeg_rect.top + jpeg_rect.height > jpg_fd->info.y)) {
        printf("\nerr_draw_jpeg %d, %d, %d, %d, %d, %d\n", jpeg_rect.left, jpeg_rect.top, jpeg_rect.width, jpeg_rect.height, jpg_fd->info.x, jpg_fd->info.y);
        return NULL;
    }


    imb_task_lock();
    ret = jpeg_dec_start(cur_draw, &r, &jpeg_rect, out->outbuf);
    imb_task_unlock();

    return NULL;
}

/*----------------------------------------------------------------------------*/
/**@brief    创建jpeg图片任务
   @param    task_id : 任务id
   @param    file : 图片信息
   @param    priv : LOAD_FROM_FLASH_WITH_TAB时为flash_file_info, 其他为图像数据的地址
   @param    lcd_format : 屏接口的格式，这里要与屏接口的格式保持一致
   @param    x:相对背景的x坐标
   @param    y:相对背景的y坐标
   @param    width:图片的宽度
   @param    height:图片的高度
   @param    load_method : 数据的加载方式, 具体参考enum LOAD_METHOD
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void imb_create_jpeg_task(int task_id, struct image_file *file, u32 priv, int lcd_format, int x, int y, int width, int height, struct rect *crop, int load_method)
{
    struct imb_task_info imb_tsk_info = {0};
    struct imb_task *p = NULL;

    imb_tsk_info.elm_id = task_id;
    if (load_method == LOAD_FROM_FLASH_WITH_TAB) {
        imb_tsk_info.data_src = DATA_SRC_FLASH;//直接从flash取数
        imb_tsk_info.cur_in_flash = 1;//数据存在flash
    } else {
        imb_tsk_info.data_src = DATA_SRC_SRAM;
        imb_tsk_info.cur_in_flash = 0;
    }
    imb_tsk_info.in_format      = file->format;
    imb_tsk_info.x_offset       = x;
    imb_tsk_info.y_offset       = y;
    imb_tsk_info.src_w          = file->width;
    imb_tsk_info.src_h          = file->height;
    imb_tsk_info.des_w          = crop->width;
    imb_tsk_info.des_h          = crop->height;
    imb_tsk_info.zip_en         = 0;
    imb_tsk_info.lcd_format     = lcd_format;
    imb_tsk_info.cb             = imb_jpeg_cb;
    imb_tsk_info.quote          = 1;
    imb_tsk_info.ff_info        = priv;
    imb_tsk_info.priv           = (u32)file;

    //裁剪区域
    if (crop) {
        imb_tsk_info.crop.left = crop->left;
        imb_tsk_info.crop.top = crop->top;
        imb_tsk_info.crop.width = crop->width;
        imb_tsk_info.crop.height = crop->height;
    }


    /* elm_id、id(低8位有效)可作为任务的唯一标识，通过该标识搜索任务句柄，若搜到则重置任务信息，没搜到则创建任务 */
    p = imb_task_search_by_id(imb_task_head_get(0), imb_tsk_info.elm_id, imb_tsk_info.id);

    if (p) {
        imb_task_reset(imb_task_head_get(0), p, &imb_tsk_info); //imb_task参数重置
    } else {
        p = imb_task_list_add(imb_task_head_get(0), &imb_tsk_info);

        struct rect jpeg_page_rect;
        jpeg_page_rect.left = x;
        jpeg_page_rect.top = y;
        jpeg_page_rect.width = width;
        jpeg_page_rect.height = height;

        memcpy(p->priv_buf, &jpeg_page_rect, sizeof(struct rect));
        /* memcpy((u8 *)p->priv_buf + sizeof(struct rect), &draw, sizeof(struct rect)); */
        p->cb_priv = p->priv_buf;
    }
}

// //  BUF显示区域    图片信息+资源组号     图片绝对区域+wh缩放       ID  BUF SIZE    剪切区域
// int imb_image_draw(struct rect rect, struct image_file file, int ui_group_n, 
//     const lv_area_t * coords, int prw, int prh, u16 angle,int dx, int dy,
//     void *src, void *buf, int bufsize, struct rect *crop, int load_mef)
// {
//     int px = coords->x1; //图片绝对区域x
//     int py = coords->y1; //图片绝对区域y
//     int pw = coords->x2-coords->x1+1; //图片绝对区域w
//     int ph = coords->y2-coords->y1+1;  //图片绝对区域h

//     struct lcd_info info = {0};
//     static struct bg_buffer bg = {0};
//     if (__this->lcd->get_screen_info) {
//         __this->lcd->get_screen_info(&info);
//     }

//     if(PIXEL_FMT_JPEG == file.format){  //JPEG图片
//         // printf("JPGKPG");
//         // imb_create_jpeg_task(imb_task_get_id(), &file, &ui_res_gropu[ui_group_n].flash_file_info, info.color_format, 
//         //     px,py,file.width,file.height, 
//         //     crop, load_mef);

//         struct flash_file_info *flash_info = NULL;
//         static struct jpeg_api_out_lines out = {0};
//         struct image_file *f = &file;
//         u32 filelen;
//         u32 flash_map_tab_num;
//         u32 file_base_addr;
//         static struct flash_file_info g_jpg_flash_info = {0};
//         flash_info = &g_jpg_flash_info;

//         imb_task_lock();

//         filelen = f->len;
//         flash_info->tab = &ui_res_gropu[ui_group_n].flash_file_info.tab[(f->offset + ui_res_gropu[ui_group_n].flash_file_info.offset) / 4096];
//         file_base_addr = flash_info->tab[0] + (f->offset + ui_res_gropu[ui_group_n].flash_file_info.offset) % 4096;
//         flash_map_tab_num = (file_base_addr % 4096 + filelen + 4096 - 1) / 4096;
//         flash_info->offset = file_base_addr % 4096;
//         flash_info->tab_size = flash_map_tab_num * sizeof(u32);
//         flash_info->last_tab_data_len = flash_map_tab_num * 4096 - filelen - flash_info->offset;

//         imb_task_unlock();

//         struct jpeg_decoder_fd *jpg_fd = jpeg_dec_get_fd();

//         int ref_w = rect.width;
//         static int last_w;
//         //  这里加判断可以节约初始化的时间，但目前找不到相关失效的条件
//         if(jpg_fd && jpg_fd->fat_info != flash_info || last_w != ref_w || 1){    
//             last_w = ref_w;
//             u8 rgb_format = 1;//1 :rgb_565 0:rgb_888
//             // printf("jpg init");
//             imb_task_lock();
//             char err = jpeg_dec_init(flash_info, rgb_format, NULL);
//             imb_task_unlock();
//         }       

//         struct rect jpeg_rect;
//         int width = jpg_fd->info.x;//jpeg图片本身的宽度
//         int heigh = jpg_fd->info.y;//jpeg图片本身的高度

//         //jpeg图片原本的范围，相对于背景
//         out.jpeg_page_rect.left = coords->x1;
//         out.jpeg_page_rect.top = coords->y1;
//         out.jpeg_page_rect.width = width;
//         out.jpeg_page_rect.height = heigh;

//         //需要合成的范围，该范围必须在jpeg范围内，相对于背景
//         memcpy(&out.control_draw, &out.jpeg_page_rect, sizeof(struct rect));

//         out.cur_draw.left = rect.left;
//         out.cur_draw.top = rect.top;
//         out.cur_draw.width = rect.width;//屏幕的宽
//         out.cur_draw.height = rect.height;//屏幕推一次的高

//         out.outbuf = buf;

//         // int a = jiffies_msec();
//         jpeg_api_read_lines(NULL, &out);
//         return 1;
//     }

// // if(ui_res_gropu[ui_group_n].mode == PSRAM_IMG && !PSRAM_FULL_SCREEN){
// //     return 1;
// // }

//     //以BUF左上角为起始
//     int xoffset = rect.left;
//     int yoffset = rect.top;
//     px = px - xoffset;
//     py = py - yoffset;
//     crop->left -= xoffset;
//     crop->top -= yoffset;
//     rect.left -= xoffset;
//     rect.top -= yoffset;

//     int compx = 0;
//     int compy = 0;

//     printf("dxy %d %d xyoffset %d %d",dx,dy, xoffset, yoffset);

//     //  旋转的圆心负坐标需要特殊处理
//     if(dy-yoffset<0){
//         compy = dy-yoffset;
//     }
//     if(dx-xoffset<0){
//         compx = dx-xoffset;
//     }


//     struct imb_task_info imb_tsk_info = {0};
//     imb_tsk_info.data_src       = DATA_SRC_NONE;//无数据源
//     imb_tsk_info.zip_en         = 0;
//     imb_tsk_info.in_format      = LAYER_FORMAT_SOLID;//纯色
//     imb_tsk_info.out_format     = OUTPUT_FORMAT_RGB565;
//     imb_tsk_info.x_offset       = compx;//rect.left;
//     imb_tsk_info.y_offset       = compy;//rect.top;
//     imb_tsk_info.src_w          = rect.width-compx;
//     imb_tsk_info.src_h          = rect.height-compy;
//     imb_tsk_info.des_w          = rect.width-compx;
//     imb_tsk_info.des_h          = rect.height-compy;
//     imb_tsk_info.priv           = 0;//纯色格式，该参数表示颜色0xr5g6b5
//     imb_tsk_info.osd0_in_buf    = 1;
//     imb_task_list_init(imb_task_head_get(0), &imb_tsk_info);

//     //1.图片缩放输出测试(其他方式可参考图片任务接口的用法，跟图片任务类似)

//     //  PSRAM截图图片
//     if(ui_res_gropu[ui_group_n].mode == PSRAM_IMG){

//         printf("IMB PSRAM ");
//         struct api_ciner_img_info _sca_img = {0};
//         _sca_img.width   = 454;
//         _sca_img.height  = 454;
//         _sca_img.format  = LAYER_FORMAT_RGB565;
//         _sca_img.img_buf = NULL;//pic->data;
//         // struct api_ciner_img_info *sca_img = &_sca_img;
//         struct api_scale_info *sca = api_get_blk_sca_info2(&g_sca_hdl[0], 454, 454, 
//             (float)prw/(float)LV_IMG_ZOOM_NONE, (float)prw/(float)LV_IMG_ZOOM_NONE, 
//             px+xoffset, py+yoffset, 91, &_sca_img, 1);

//         u8 block_index;
//         int v,h;
//         struct image_file tmp_file = {0};
//         for (v = 0; v < sca->v_block_n; v++) {
//             for (h = 0; h < sca->h_block_n; h++) {
//                 block_index = v * sca->h_block_n + h;
//                 tmp_file.width = sca->src_block[block_index].rect.width;
//                 tmp_file.height = sca->src_block[block_index].rect.height;
//                 tmp_file.format = sca->format;
//                 imb_create_image_scale_task(imb_task_get_id(), &tmp_file, psram_cache2nocache_addr(sca->src_block[block_index].buf), 
//                 sca->ratio_w, sca->ratio_h, 
//                 sca->dst_block[block_index].left -xoffset , sca->dst_block[block_index].top-yoffset, 
//                 sca->dst_block[block_index].width, sca->dst_block[block_index].height, 
//                 NULL, false, LOAD_FROM_STATIC_RAM);
//                 // printf("分块缩放");
//             }
//         }
//     } else {
//         //  普通图片
//         if(LV_IMG_ZOOM_NONE != prw || LV_IMG_ZOOM_NONE != prh ){   //  缩放
//             y_printf("%s%d",__func__,__LINE__);
//             imb_create_image_scale_task(imb_task_get_id(), &file,  &ui_res_gropu[ui_group_n].flash_file_info, 
//                 (float)prw/(float)LV_IMG_ZOOM_NONE, (float)prh/(float)LV_IMG_ZOOM_NONE,
//                 px+dx*(LV_IMG_ZOOM_NONE-prw-128)/LV_IMG_ZOOM_NONE, 
//                 py+dy*(LV_IMG_ZOOM_NONE-prh-128)/LV_IMG_ZOOM_NONE, 
//                 pw*prw/LV_IMG_ZOOM_NONE,ph*prh/LV_IMG_ZOOM_NONE,
//                 crop, true, load_mef);         
//         } 
//         else if(angle){   //  不带TAB不占RAM但速度慢
//             if (file.height*file.width < 120*120*2 && 0) {  
//                 imb_create_image_rotate_task(imb_task_get_id(), &file, &ui_res_gropu[ui_group_n].flash_file_info, 
//                     dx, dy, (angle/10)%360, px+dx-compx, py+dy-compy,
//                     NULL, load_mef
//                 );
//             } else {  //不占RAM速度慢
//                 imb_create_image_rotate_chunk_task(imb_task_get_id(), &file, &ui_res_gropu[ui_group_n].flash_file_info, 
//                     dx, dy, (angle/10)%360, px+dx-compx, py+dy-compy
//                 );
//             }
//         } else{    //      原大小
//             imb_create_image_task(imb_task_get_id(),&file, &ui_res_gropu[ui_group_n].flash_file_info, 
//                 px,py,pw,ph,
//                 crop,true, load_mef);//width,height参数可小于file.width, file.height,若小于则裁剪 
//         }       
//     }
    
//     //打印所有任务信息
//     // imb_task_info_dump(imb_task_head_get(0));

//     //启动合成&推屏
//     struct rect disp;//unused
//     struct rect page_draw = {0};
//     struct rect screen_rect;//屏幕有效显示区域
//     screen_rect.left = 0;
//     screen_rect.top = 0;
//     screen_rect.width = rect.width;
//     screen_rect.height = rect.height;

//     rect.left  = 0;
//     rect.top = 0;

//     u16 bg_stride = (rect.width * 2 + 3) / 4 * 4;
//     u16 colums = rect.width;
//     u16 lines = rect.height;//info.buffer_size / info.buf_num / bg_stride;

//     imb_task_head_set_buf(imb_task_head_get(0), buf, bufsize, rect.width, rect.height, bg_stride, lines, 1);
//     imb_task_head_config(imb_task_head_get(0), &rect, &screen_rect, &screen_rect, &page_draw, STATE_SYNTHESIS_AND_DRAW);

//     struct imb_cb_interface itf = {0};
//     usr_buf = buf;
//     itf.buf_get = usr_buf_get;
//     itf.buf_check = usr_buf_check;
//     itf.buf_set_idle = usr_buf_set_idle;
//     itf.buf_set_pending = usr_buf_set_pending;
//     itf.buf_wait_finish = usr_buf_wait_finish;
//     itf.draw_area = usr_draw_area;
//     itf.draw_meld_area = usr_draw_meld_area;

//     // int a = jiffies_msec();
//     imb_start(imb_task_head_get(0), &screen_rect, disp, colums, lines, &itf );
//     // int b = jiffies_msec();
//     // printf("%d",b-a);

//     imb_task_all_destroy(imb_task_head_get(0));

//     return 1;
// }


//
int imb_rgb565torgb888(struct rect rect, int bg_width, int bg_height, 
    void *buf, int bufsize, void *out_buf)
{
    // memset(buf, 0xf0, rect.width*rect.height);
    struct lcd_info info = {0};
    static struct bg_buffer bg = {0};
    if (__this->lcd->get_screen_info) {
        __this->lcd->get_screen_info(&info);
    }

    struct imb_task_info imb_tsk_info = {0};
    imb_tsk_info.data_src       = DATA_SRC_NONE;//无数据源
    imb_tsk_info.zip_en         = 0;
    imb_tsk_info.in_format      = LAYER_FORMAT_SOLID;//纯色
    imb_tsk_info.out_format     = OUTPUT_FORMAT_RGB888;
    imb_tsk_info.x_offset       = rect.left;
    imb_tsk_info.y_offset       = rect.top;
    imb_tsk_info.src_w          = rect.width;
    imb_tsk_info.src_h          = rect.height;
    imb_tsk_info.des_w          = rect.width;
    imb_tsk_info.des_h          = rect.height;
    imb_tsk_info.priv           = 0x0000;//纯色格式，该参数表示颜色0xr5g6b5
    imb_tsk_info.osd0_in_buf    = 1;
    imb_task_list_init(imb_task_head_get(0), &imb_tsk_info);

    struct image_file tmp_file;
    tmp_file.width = bg_width;
    tmp_file.height = bg_height;
    tmp_file.format = LAYER_FORMAT_RGB565;
    // imb_create_image_task(imb_task_get_id(), &tmp_file, buf, rect.left, rect.top, tmp_file.width, tmp_file.height, NULL, false, LOAD_FROM_STATIC_RAM,  draw_dsc->recolor);


    //打印所有任务信息
    // imb_task_info_dump(imb_task_head_get(0));

    //启动合成&推屏
    struct rect disp;//unused
    struct rect page_draw = {0};
    struct rect screen_rect;//屏幕有效显示区域
    screen_rect.left = 0;
    screen_rect.top = 0;
    screen_rect.width = info.width;//bg_width;
    screen_rect.height = info.height;//bg_height;

    // imb_set_output_cb(imb_data_output, imb_data_output_wait_finish);
    // printf("buf %d len %d  n %d",buf,bufsize, info.buf_num);

    u16 bg_stride = (bg_width * 2 + 3) / 4 * 4;
    u16 colums = bg_width;
    u16 lines = info.buffer_size / info.buf_num / bg_stride;

    imb_task_head_set_buf(imb_task_head_get(0), out_buf/*info.buffer*/, bufsize/*info.buffer_size*/, bg_width, bg_height, bg_stride, lines, info.buf_num);
    
    imb_task_head_config(imb_task_head_get(0), &rect, &screen_rect, &screen_rect, &page_draw, STATE_SYNTHESIS_AND_DRAW);
    
    // static u8 temp_buf[240*70*2];

    struct imb_cb_interface itf = {0};
    usr_buf = out_buf;
    itf.buf_get = usr_buf_get;
    itf.buf_check = usr_buf_check;
    itf.buf_set_idle = usr_buf_set_idle;
    itf.buf_set_pending = usr_buf_set_pending;
    itf.buf_wait_finish = usr_buf_wait_finish;
    itf.draw_area = usr_draw_area;
    itf.draw_meld_area = usr_draw_meld_area;
    imb_start(imb_task_head_get(0), &screen_rect, disp, colums, lines, &itf );

    imb_task_all_destroy(imb_task_head_get(0));

    return 1;
}

void imb_jpg_draw(void* res, struct _lv_draw_ctx_t * draw_buf, const lv_area_t * coords, jpg_stream_input cb, lv_area_t * clip_area){
    static struct jpeg_api_info api_info = {0};
        static struct jpeg_api_out_lines out = {0};

    // struct CacheFile* res= readFromCache(src, RES_PATH"ui/temp.bin"); 
    // if(!res || res->len==0){
    //     printf("ccccccccc");
    //     return 0;
    // }

    // printf("JPG_RES %x %d", res->data, res->len);
    struct jpeg_decoder_fd *jpg_fd = jpeg_dec_get_fd();
    
    int ref_w = (draw_buf->buf_area->x2) - (draw_buf->buf_area->x1) +1;
    static int last_w;
    //  这里加判断可以节约初始化的时间，但目前找不到相关失效的条件
    // if(jpg_fd && jpg_fd->fat_info != res || last_w != ref_w){    
        last_w = ref_w;
        u8 rgb_format = 1;//1 :rgb_565 0:rgb_888
        imb_task_lock();
        char err = jpeg_dec_init(res, rgb_format, cb);
        imb_task_unlock();
        // printf("xxxxxx");
    // }       
    if(draw_buf==NULL){
        return;
    }


    struct rect jpeg_rect;

    // jpg_fd = api_info.jpg_fd;
    int width = jpg_fd->info.x;//jpeg图片本身的宽度
    int heigh = jpg_fd->info.y;//jpeg图片本身的高度

    // printf("wh %d %d", width, heigh);

    //jpeg图片原本的范围，相对于背景
    out.jpeg_page_rect.left = coords->x1;
    out.jpeg_page_rect.top = coords->y1;
    out.jpeg_page_rect.width = lv_area_get_width(coords);//width;
    out.jpeg_page_rect.height = lv_area_get_height(coords);//100;//heigh;

    //需要合成的范围，该范围必须在jpeg范围内，相对于背景
    memcpy(&out.control_draw, &out.jpeg_page_rect, sizeof(struct rect));

    out.control_draw.left = clip_area->x1;
    out.control_draw.top = clip_area->y1;
    out.control_draw.width = clip_area->x2-clip_area->x1+1;
    out.control_draw.height = clip_area->y2-clip_area->y1+1;

    // out.control_draw.width /= 2;
    // out.control_draw.height /= 2;

    out.cur_draw.left = draw_buf->buf_area->x1;
    out.cur_draw.top = draw_buf->buf_area->y1;;
    out.cur_draw.width = (draw_buf->buf_area->x2) - (draw_buf->buf_area->x1) +1;//屏幕的宽
    out.cur_draw.height = (draw_buf->buf_area->y2) - (draw_buf->buf_area->y1) +1;//屏幕推一次的高

    out.outbuf = draw_buf->buf;

    // int a = jiffies_msec();
    jpeg_api_read_lines(&api_info, &out);
    // int b = jiffies_msec();
    // printf("%d", b-a);
}
static u8 *usr_jpg_dec_stream_input2(void *__fat_info, u32 *len, u32 offset_4k);
void lv_draw_imb_img_decoded(struct _lv_draw_ctx_t * draw_ctx, const lv_draw_img_dsc_t * draw_dsc,
                                                  const lv_area_t * coords, const uint8_t * src_buf, lv_img_cf_t cf);

static lv_res_t lv_draw_jl_imb_img(struct _lv_draw_ctx_t * draw_buf, const lv_draw_img_dsc_t * draw_dsc,
                         const lv_area_t * coords, const void * src){
    const lv_img_dsc_t * img_dsc = (const lv_img_dsc_t *)src;
//  判断是否为IMB头
    uint8_t * raw_imb_data = (uint8_t *)img_dsc->data;

    // put_buf(raw_imb_data,16);
    const uint32_t raw_imb_data_size = img_dsc->data_size;
    const uint8_t *imb_signature = "IMB";
    if(memcmp(imb_signature, raw_imb_data, sizeof(imb_signature))){
        return LV_RES_INV;
    }

    int cf = 1;


    lv_area_t map_area_rot;
    lv_area_copy(&map_area_rot, coords);
    if (draw_dsc->angle || draw_dsc->zoom != LV_IMG_ZOOM_NONE)
    {
        int32_t w = lv_area_get_width(coords);
        int32_t h = lv_area_get_height(coords);

        _lv_img_buf_get_transformed_area(&map_area_rot, w, h, draw_dsc->angle, draw_dsc->zoom, &draw_dsc->pivot);

        map_area_rot.x1 += coords->x1;
        map_area_rot.y1 += coords->y1;
        map_area_rot.x2 += coords->x1;
        map_area_rot.y2 += coords->y1;
    }

    struct _lv_draw_ctx_t * draw_ctx = draw_buf;
    lv_area_t clip_com; /*Common area of mask and coords*/
    bool union_ok;
    union_ok = _lv_area_intersect(&clip_com, draw_ctx->clip_area, &map_area_rot);
    /*Out of mask. There is nothing to draw so the image is drawn successfully.*/
    if (union_ok == false)
    {
        // printf("Out of mask. There is nothing to draw so the image is drawn successfully.");
        // draw_cleanup(cdsc);
        return LV_RES_OK;
    }

    const lv_area_t *clip_area_ori = draw_ctx->clip_area;
    draw_ctx->clip_area = &clip_com;
    lv_draw_imb_img_decoded(draw_ctx, draw_dsc, coords, raw_imb_data, cf);
    draw_ctx->clip_area = clip_area_ori;
    
    return LV_RES_OK;


}
u32 get_file_addr(char *path);
static lv_res_t lv_draw_jl_imb_img_by_fs(struct _lv_draw_ctx_t * draw_buf, const lv_draw_img_dsc_t * draw_dsc,
                         const lv_area_t * coords, const void * src){
                            
    u8 *u8_p = src;//  盘符
    char * real_path = NULL;  //  真实路径
    if(u8_p[1] == ':') real_path = &u8_p[2]; 
    u8* lastname = NULL;//  文件名 

    //  查找资源组所属
    int n = -1;   
    if(u8_p[0]>='0' && u8_p[0]<='9'){
        lastname = src;
        n = 0;
    }else{
        for(u8 i=0;i<ARRAY_SIZE(ui_res_gropu);i++){
            if( u8_p[0] == ui_res_gropu[i].letter)   //盘符是否匹配
            {
                lastname = real_path;
                n = i;
                break;
            }
        }
        if(n==-1) {
            // printf("没有需要加速的资源返回下一个解码器");
            return LV_RES_INV; //没有需要加速的资源返回下一个解码器
        } 
    }


    //  休眠判断,休眠不能跑硬件2D加速
    if(lcd_sleep_status()){
        // g_printf("sleep can't run imb");
        return LV_RES_OK;
    }

    //  BUF地址判断，ARG8565输出BUF不支持，也就是图片改变ALAPHA是不支持的
    //  canves绘图 buf是第三方
    // if(lv_disp_get_default()->driver->draw_buf->buf_act != draw_buf->buf){
    //     // 透明图片暂未优化
    //     putchar('E');
    //     return LV_RES_OK;
    // }

    lv_area_t map_area_rot;
    lv_area_copy(&map_area_rot, coords);
    if (draw_dsc->angle || draw_dsc->zoom != LV_IMG_ZOOM_NONE)
    {
        int32_t w = lv_area_get_width(coords);
        int32_t h = lv_area_get_height(coords);

        _lv_img_buf_get_transformed_area(&map_area_rot, w, h, draw_dsc->angle, draw_dsc->zoom, &draw_dsc->pivot);

        map_area_rot.x1 += coords->x1;
        map_area_rot.y1 += coords->y1;
        map_area_rot.x2 += coords->x1;
        map_area_rot.y2 += coords->y1;
    }

    struct _lv_draw_ctx_t * draw_ctx = draw_buf;
    lv_area_t clip_com; /*Common area of mask and coords*/
    bool union_ok;
    union_ok = _lv_area_intersect(&clip_com, draw_ctx->clip_area, &map_area_rot);
    /*Out of mask. There is nothing to draw so the image is drawn successfully.*/
    if (union_ok == false)
    {
        // printf("Out of mask. There is nothing to draw so the image is drawn successfully.");
        // draw_cleanup(cdsc);
        return LV_RES_OK;
    }

    // struct flash_file_info ui_resfile_info;
    // int ret = ui_res_flash_info_get(&ui_resfile_info, lastname, "res");
    // ASSERT(!ret);
    // u32 file_addr = ui_resfile_info.tab[0] + ui_resfile_info.offset;//计算文件的物理地址
    // ui_res_flash_info_free(&ui_resfile_info, "res");

    const lv_area_t *clip_area_ori = draw_ctx->clip_area;
    draw_ctx->clip_area = &clip_com;

    int cf = LV_IMG_CF_RAW;
    void *user_data_ori = draw_buf->user_data;
    void *temp_src;
    if(ui_res_gropu[n].mode == IN_RES_WITH_ID ||
        ui_res_gropu[n].mode == NXP_F_FILE  ||
        ui_res_gropu[n].mode == IMG_ANIMING_FILE
    ) {
        draw_buf->user_data = 0x1234;   //文件系统标识
        temp_src = src;
        // printf("xxxxxxxxxxxxxx");
        lv_draw_imb_img_decoded(draw_ctx, draw_dsc, coords, temp_src, cf);
    }
    draw_buf->user_data = user_data_ori;
    
    draw_ctx->clip_area = clip_area_ori;

    return LV_RES_OK;
}
static lv_res_t lv_draw_jl_jpg_img(struct _lv_draw_ctx_t * draw_buf, const lv_draw_img_dsc_t * draw_dsc,
                         const lv_area_t * coords, const void * src){
    const lv_img_dsc_t * img_dsc = (const lv_img_dsc_t *)src;
//  判断是否为JPG头
    uint8_t * raw_jpeg_data = (uint8_t *)img_dsc->data;
    const uint32_t raw_jpeg_data_size = img_dsc->data_size;
    const uint8_t jpg_signature[] = {0xFF, 0xD8, 0xFF};
    if(memcmp(jpg_signature, raw_jpeg_data, sizeof(jpg_signature))){
        return LV_RES_INV;
    }
    
    struct FileIndex jpgres = {0};
    jpgres.addr = raw_jpeg_data;
    jpgres.len  = raw_jpeg_data_size;

    lv_area_t map_area_rot;
    lv_area_copy(&map_area_rot, coords);
    if (draw_dsc->angle || draw_dsc->zoom != LV_IMG_ZOOM_NONE)
    {
        int32_t w = lv_area_get_width(coords);
        int32_t h = lv_area_get_height(coords);

        _lv_img_buf_get_transformed_area(&map_area_rot, w, h, draw_dsc->angle, draw_dsc->zoom, &draw_dsc->pivot);

        map_area_rot.x1 += coords->x1;
        map_area_rot.y1 += coords->y1;
        map_area_rot.x2 += coords->x1;
        map_area_rot.y2 += coords->y1;
    }

    struct _lv_draw_ctx_t * draw_ctx = draw_buf;
    lv_area_t clip_com; /*Common area of mask and coords*/
    bool union_ok;
    union_ok = _lv_area_intersect(&clip_com, draw_ctx->clip_area, &map_area_rot);
    /*Out of mask. There is nothing to draw so the image is drawn successfully.*/
    if (union_ok == false)
    {
        printf("Out of mask. There is nothing to draw so the image is drawn successfully.");
        // draw_cleanup(cdsc);
        return LV_RES_OK;
    }

    const lv_area_t *clip_area_ori = draw_ctx->clip_area;
    draw_ctx->clip_area = &clip_com;
    // lv_draw_img_decoded(draw_ctx, draw_dsc, coords, cdsc->dec_dsc.img_data, cf);
    
    imb_jpg_draw(&jpgres, draw_buf, coords, usr_jpg_dec_stream_input2, draw_ctx->clip_area);
    draw_ctx->clip_area = clip_area_ori;
    
    return LV_RES_OK;

}
static lv_res_t lv_draw_jl_dma2d_img_file(struct _lv_draw_ctx_t * draw_buf, const lv_draw_img_dsc_t * draw_dsc,
                         const lv_area_t * coords, const void * src){
// //  缩放旋转区域计算
    // lv_draw_jl_imb_img_by_fs();
    return LV_RES_OK;
}

static int check_gif_res(struct _lv_draw_ctx_t * draw_buf, const lv_draw_img_dsc_t * draw_dsc,
                         const lv_area_t * coords, const void * src);

LV_ATTRIBUTE_FAST_MEM static lv_res_t lv_draw_jl_dma2d_img(struct _lv_draw_ctx_t * draw_buf, const lv_draw_img_dsc_t * draw_dsc,
                         const lv_area_t * coords, const void * src){

    if(app_get_curr_task() == 13){
        printf("STOP UI...");
        return LV_RES_OK;
    }

    if(LV_RES_OK == check_gif_res(draw_buf, draw_dsc,
                         coords, src)){
        return LV_RES_OK;
    }

    if (draw_dsc->opa <= LV_OPA_MIN)
        return LV_RES_OK;

    //  VAR类型的资源
    lv_img_src_t src_type = lv_img_src_get_type(src);
    if(src_type == LV_IMG_SRC_VARIABLE) {
        const lv_img_dsc_t * img_dsc = src;
        if(img_dsc->data == NULL) return LV_RES_INV;
    } else if(src_type == LV_IMG_SRC_FILE){
        //FILE类型走这
        return lv_draw_jl_imb_img_by_fs(draw_buf, draw_dsc,
                         coords, src);
    }

    //  VAR类型的资源
    //  RAW自定义解码器
    const lv_img_dsc_t * img_dsc = (const lv_img_dsc_t *)src;
    lv_img_cf_t cf = img_dsc->header.cf;
    if(cf != LV_IMG_CF_RAW){
        return LV_RES_INV;
    }

    //  同时缩放与旋转判断，IMB不支持同时缩放与旋转
    if(draw_dsc->angle && draw_dsc->zoom != LV_IMG_ZOOM_NONE ){
        printf("no support zoom and angle");
        return LV_RES_OK;   //不支持同时缩放与旋转
    }

    //  休眠判断,休眠不能跑硬件2D加速
    if(lcd_sleep_status()){
        // g_printf("sleep can't run imb");
        return LV_RES_OK;
    }

    //  BUF地址判断，ARG8565输出BUF不支持，也就是图片改变ALAPHA是不支持的
    if(lv_disp_get_default()->driver->draw_buf->buf_act != draw_buf->buf){
        // 透明图片暂未优化
        putchar('E');
        return LV_RES_OK;
    }

    //  JPG头识别并解码成功接管返回
    if(LV_RES_OK == lv_draw_jl_jpg_img(draw_buf, draw_dsc, coords, src)){
        return LV_RES_OK;
    }

    //  IMB头识别并解码成功接管返回
    if(LV_RES_OK == lv_draw_jl_imb_img(draw_buf, draw_dsc, coords, src)){
        // printf("IMB");
        return LV_RES_OK;
    }

return LV_RES_INV;
}
/*----------------------------------------------------------------------------*/
/**@brief     创建纯色任务(矩形填充)
   @param     task_id : 任务id
   @param     x : 相对背景的x坐标
   @param     y : 相对背景的y坐标
   @param     width : 矩形的宽度
   @param     height: 矩形的高度
   @param     color : argb8565格式 (alpha 0~100)
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void imb_create_color_task(int task_id, int x, int y, int width, int height, u32 color)
{
    struct imb_task_info imb_tsk_info = {0};
    struct imb_task *p = NULL;

    imb_tsk_info.elm_id = task_id;
    imb_tsk_info.data_src = DATA_SRC_NONE;
    imb_tsk_info.zip_en = 0;
    imb_tsk_info.in_format = LAYER_FORMAT_SOLID;
    imb_tsk_info.x_offset = x;
    imb_tsk_info.y_offset = y;
    imb_tsk_info.src_w = width;
    imb_tsk_info.src_h = height;
    imb_tsk_info.des_w = width;
    imb_tsk_info.des_h = height;
    imb_tsk_info.priv = color;

    /* elm_id、id(低8位有效)可作为任务的唯一标识，通过该标识搜索任务句柄，若搜到则重置任务信息，没搜到则创建任务 */
    p = imb_task_search_by_id(imb_task_head_get(0), imb_tsk_info.elm_id, imb_tsk_info.id);

    if (p) {
        imb_task_reset(imb_task_head_get(0), p, &imb_tsk_info);
    } else {
        imb_task_list_add(imb_task_head_get(0), &imb_tsk_info);
    }
}
//  1处理成功，0处理失败
int jl_draw_sw_blend_basic(lv_draw_ctx_t * draw_ctx, const lv_draw_sw_blend_dsc_t * dsc){

    // if(dsc->src_buf){
    //     printf("%s %d",__func__,__LINE__);
    //     printf("mode %d opa %d mask %x", dsc->blend_mode, dsc->opa, dsc->mask_buf);
    // }
        

    lv_opa_t * mask;
    if(dsc->mask_buf == NULL) mask = NULL;
    if(dsc->mask_buf && dsc->mask_res == LV_DRAW_MASK_RES_TRANSP) return 1;
    else if(dsc->mask_res == LV_DRAW_MASK_RES_FULL_COVER) mask = NULL;
    else mask = dsc->mask_buf;

    lv_coord_t dest_stride = lv_area_get_width(draw_ctx->buf_area);

    lv_area_t blend_area;
    if(!_lv_area_intersect(&blend_area, dsc->blend_area, draw_ctx->clip_area)) return 1;

    lv_disp_t * disp = _lv_refr_get_disp_refreshing();
    lv_color_t * dest_buf = draw_ctx->buf;
    if(disp->driver->set_px_cb == NULL) {
        if(disp->driver->screen_transp) {
            return 0;
        }
    } else {
        return 0;
    }

    const lv_color_t * src_buf = dsc->src_buf;
    lv_coord_t src_stride;
    if(src_buf) {
        src_stride = lv_area_get_width(dsc->blend_area);
        src_buf += src_stride * (blend_area.y1 - dsc->blend_area->y1) + (blend_area.x1 - dsc->blend_area->x1);
    }
    else {
        src_stride = 0;
    }

    lv_coord_t mask_stride = 0;
    if(mask==NULL && dsc->blend_mode == LV_BLEND_MODE_NORMAL){
        if(dsc->src_buf == NULL) {
            // printf("fill_normal");
            //矩形纯色带A填充
            if((dsc->opa >= LV_OPA_MAX)){
                // fill_normal(dest_buf, &blend_area, dest_stride, dsc->color, dsc->opa, mask, mask_stride);
                return 0;
            } else {
                int32_t bw = lv_area_get_width(&blend_area);
                int32_t bh = lv_area_get_height(&blend_area);
                int32_t dw = lv_area_get_width(draw_ctx->buf_area);
                int32_t dh = lv_area_get_height(draw_ctx->buf_area);
                
                struct lcd_info info = {0};
                static struct bg_buffer bg = {0};
                if (__this->lcd->get_screen_info) {
                    __this->lcd->get_screen_info(&info);
                }

                struct imb_task_info imb_tsk_info = {0};
                imb_tsk_info.data_src       = DATA_SRC_NONE;//无数据源
                imb_tsk_info.zip_en         = 0;
                imb_tsk_info.in_format      = LAYER_FORMAT_SOLID;//纯色
                imb_tsk_info.out_format     = OUTPUT_FORMAT_RGB565;
                imb_tsk_info.x_offset       = draw_ctx->buf_area->x1;
                imb_tsk_info.y_offset       = draw_ctx->buf_area->y1;
                imb_tsk_info.src_w          = dw;
                imb_tsk_info.src_h          = dh;
                imb_tsk_info.des_w          = dw;
                imb_tsk_info.des_h          = dh;
                imb_tsk_info.priv           = dsc->color.full;//纯色格式，该参数表示颜色0xr5g6b5
                imb_tsk_info.osd0_in_buf    = 1;
                imb_task_list_init(imb_task_head_get(0), &imb_tsk_info);
                imb_create_color_task(imb_task_get_id(), blend_area.x1, blend_area.y1, bw, bh, dsc->opa*100/256 << 24 | ((dsc->color.full&0xff<<8)+dsc->color.full>>8));

                //启动合成&推屏
                struct rect rect; 
                struct rect disp; //unused
                struct rect page_draw = {0};
                struct rect screen_rect;//屏幕有效显示区域
                screen_rect.left = 0;
                screen_rect.top = 0;
                screen_rect.width = 392;//bg_width;
                screen_rect.height = 392;//bg_height;

                rect.left = draw_ctx->buf_area->x1;
                rect.top = draw_ctx->buf_area->y1;
                rect.width = dw;//bg_width;
                rect.height = dh;//bg_height;

                // imb_set_output_cb(imb_data_output, imb_data_output_wait_finish);
                // printf("buf %d len %d  n %d",buf,bufsize, info.buf_num);

                u16 bg_stride = (dw * 2 + 3) / 4 * 4;
                u16 colums = dw;
                u16 lines = dh;//info.buffer_size / info.buf_num / bg_stride;

                imb_task_head_set_buf(imb_task_head_get(0), draw_ctx->buf/*info.buffer*/, dw*dh*2/*info.buffer_size*/, dw, dh, dw*2, dh, 1);
                
                imb_task_head_config(imb_task_head_get(0), &rect, &screen_rect, &screen_rect, &page_draw, STATE_SYNTHESIS_AND_DRAW);
                
                // static u8 temp_buf[240*70*2];

                struct imb_cb_interface itf = {0};
                usr_buf = draw_ctx->buf;
                itf.buf_get = usr_buf_get;
                itf.buf_check = usr_buf_check;
                itf.buf_set_idle = usr_buf_set_idle;
                itf.buf_set_pending = usr_buf_set_pending;
                itf.buf_wait_finish = usr_buf_wait_finish;
                itf.draw_area = usr_draw_area;
                itf.draw_meld_area = usr_draw_meld_area;
                imb_start(imb_task_head_get(0), &screen_rect, disp, colums, lines, &itf );

                imb_task_all_destroy(imb_task_head_get(0));

                return 1;

            }
            // 

        }
        else {
            // // printf("map_normal");
            // // printf(" %d",dsc->opa);
            // // RAM 矩形合成
            // if((dsc->opa >= LV_OPA_MAX)){
            //     int32_t bw = lv_area_get_width(&blend_area);
            //     int32_t bh = lv_area_get_height(&blend_area);
            //     int32_t dw = lv_area_get_width(draw_ctx->buf_area);
            //     int32_t dh = lv_area_get_height(draw_ctx->buf_area);
                
            //     struct lcd_info info = {0};
            //     static struct bg_buffer bg = {0};
            //     if (__this->lcd->get_screen_info) {
            //         __this->lcd->get_screen_info(&info);
            //     }

            //     struct imb_task_info imb_tsk_info = {0};
            //     imb_tsk_info.data_src       = DATA_SRC_NONE;//无数据源
            //     imb_tsk_info.zip_en         = 0;
            //     imb_tsk_info.in_format      = LAYER_FORMAT_SOLID;//纯色
            //     imb_tsk_info.out_format     = OUTPUT_FORMAT_RGB565;
            //     imb_tsk_info.x_offset       = draw_ctx->buf_area->x1;
            //     imb_tsk_info.y_offset       = draw_ctx->buf_area->y1;
            //     imb_tsk_info.src_w          = dw;
            //     imb_tsk_info.src_h          = dh;
            //     imb_tsk_info.des_w          = dw;
            //     imb_tsk_info.des_h          = dh;
            //     imb_tsk_info.priv           = dsc->color.full;//纯色格式，该参数表示颜色0xr5g6b5
            //     imb_tsk_info.osd0_in_buf    = 1;
            //     imb_task_list_init(imb_task_head_get(0), &imb_tsk_info);

            //     struct image_file tmp_file;
            //     tmp_file.width = bw;
            //     tmp_file.height = bh;
            //     tmp_file.format = LAYER_FORMAT_RGB565;
            //     imb_create_image_task(imb_task_get_id(), &tmp_file, dsc->src_buf, 
            //         blend_area.x1, blend_area.y1, bw, bh, NULL, false, LOAD_FROM_STATIC_RAM);

            //     //启动合成&推屏
            //     struct rect rect; 
            //     struct rect disp; //unused
            //     struct rect page_draw = {0};
            //     struct rect screen_rect;//屏幕有效显示区域
            //     screen_rect.left = 0;
            //     screen_rect.top = 0;
            //     screen_rect.width = 392;//bg_width;
            //     screen_rect.height = 392;//bg_height;

            //     rect.left = draw_ctx->buf_area->x1;
            //     rect.top = draw_ctx->buf_area->y1;
            //     rect.width = dw;//bg_width;
            //     rect.height = dh;//bg_height;

            //     // imb_set_output_cb(imb_data_output, imb_data_output_wait_finish);
            //     // printf("buf %d len %d  n %d",buf,bufsize, info.buf_num);

            //     u16 bg_stride = (dw * 2 + 3) / 4 * 4;
            //     u16 colums = dw;
            //     u16 lines = dh;//info.buffer_size / info.buf_num / bg_stride;

            //     imb_task_head_set_buf(imb_task_head_get(0), draw_ctx->buf/*info.buffer*/, dw*dh*2/*info.buffer_size*/, dw, dh, dw*2, dh, 1);
                
            //     imb_task_head_config(imb_task_head_get(0), &rect, &screen_rect, &screen_rect, &page_draw, STATE_SYNTHESIS_AND_DRAW);
                
            //     // static u8 temp_buf[240*70*2];

            //     struct imb_cb_interface itf = {0};
            //     usr_buf = draw_ctx->buf;
            //     itf.buf_get = usr_buf_get;
            //     itf.buf_check = usr_buf_check;
            //     itf.buf_set_idle = usr_buf_set_idle;
            //     itf.buf_set_pending = usr_buf_set_pending;
            //     itf.buf_wait_finish = usr_buf_wait_finish;
            //     itf.draw_area = usr_draw_area;
            //     itf.draw_meld_area = usr_draw_meld_area;
            //     imb_start(imb_task_head_get(0), &screen_rect, disp, colums, lines, &itf );

            //     imb_task_all_destroy(imb_task_head_get(0));

            //     return 0;
  

            // }
            // map_normal(dest_buf, &blend_area, dest_stride, src_buf, src_stride, dsc->opa, mask, mask_stride);
            return 0;
        }

        return 0;
    }

    return 0;
}

//  优先IMB接管
void lv_draw_jl_dma2d_blend(lv_draw_ctx_t * draw_ctx, const lv_draw_sw_blend_dsc_t * dsc){
return;
    if(jl_draw_sw_blend_basic( draw_ctx,   dsc) == 1){
        // 预处理OK直接返回
        return;
    }

    //  IMB不支持直接走软件合成
    lv_draw_sw_blend_basic(draw_ctx, dsc);
}

static void imb_task_info_dump(struct imb_task_head *root)
{
    struct imb_task *p;

    printf("\nimb_task_info dump:\n");
    list_for_each_entry(p, &root->entry, entry) {
        printf("[%d:%s---%d ], %d, %d elm_id:%x\n", root->index, p->name, p->group, p->cur_tsk_valid, p->task_en,p->elm_id);
        printf("zip_en %x, rgb_tsk_en %x, cur_osd0_en %x, des_w %d, src_h %d, src_w %d, nxt_wait_en %x, scale_en %x, des_h %x, y_offset %x, x_offset %x, cur_format %x, rotate_c_y %x, rotate_c_x %x, rotate_angle %x, adr_map_adr %x, dat_src_adr %x, nxt_tsk_adr %x, a_from_tsk %x, r_from_tsk %x, g_from_tsk %x, b_from_tsk %x, cur_tsk_valid %x, cur_in_flash %x, osd0_in_buf %x, rotate_en %x, rotate_dy %x, rotate_dx %x, src_h_pre %x, src_w_pre %x, y_src_offset %x, x_src_offset %x\n", p->zip_en, p->rgb_tsk_en, p->cur_osd0_en, p->des_w, p->src_h, p->src_w, p->nxt_wait_en, p->scale_en, p->des_h, p->y_offset, p->x_offset, p->cur_format, p->rotate_c_y, p->rotate_c_x, p->rotate_angle, p->adr_map_adr, p->dat_src_adr, p->nxt_tsk_adr, p->a_from_tsk, p->r_from_tsk, p->g_from_tsk, p->b_from_tsk, p->cur_tsk_valid, p->cur_in_flash, p->osd0_in_buf, p->rotate_en, p->rotate_dy, p->rotate_dx, p->src_h_pre, p->src_w_pre, p->y_src_offset, p->x_src_offset);

        printf("\n");
    }
}

LV_ATTRIBUTE_FAST_MEM void jl_gpu_fill(lv_color_t * buf, lv_coord_t dest_stride, lv_area_t * blend_area, lv_color_t color, lv_opa_t opa, int hight) {
       // LVGL的BUF刷新窗口计算
    struct rect rect;//当前刷新区域
    rect.left = 0;
    rect.top = 0;
    rect.width = dest_stride;//(blend_area->x2) - (blend_area->x1) +1;
    rect.height = hight;//240;//(blend_area->y2) +1;//- (blend_area->y1) +1;    
    int bufsize = rect.width*rect.height*2;
   
    //以BUF左上角为起始
    int xoffset = rect.left;
    int yoffset = rect.top;
    rect.left -= xoffset;
    rect.top -= yoffset;
    int compx = 0;
    int compy = 0;

    struct imb_task_info imb_tsk_info = {0};
    imb_tsk_info.data_src       = DATA_SRC_NONE;//无数据源
    imb_tsk_info.zip_en         = 0;
    imb_tsk_info.in_format      = LAYER_FORMAT_SOLID;//纯色
    imb_tsk_info.out_format     = OUTPUT_FORMAT_RGB565;
    imb_tsk_info.x_offset       = compx;
    imb_tsk_info.y_offset       = compy;
    imb_tsk_info.src_w          = rect.width - compx;
    imb_tsk_info.src_h          = rect.height - compy;
    imb_tsk_info.des_w          = rect.width - compx;
    imb_tsk_info.des_h          = rect.height - compy;
    imb_tsk_info.priv           = 0;//纯色格式，该参数表示颜色0xr5g6b5
    imb_tsk_info.osd0_in_buf    = 1;
    imb_task_list_init(imb_task_head_get(0), &imb_tsk_info);
    
    //  纯色
    imb_create_color_task(imb_task_get_id(), 
                    blend_area->x1, blend_area->y1, 
                    lv_area_get_width(blend_area), 
                    lv_area_get_height(blend_area),
                    (lv_map(opa, 0, 230, 0, 100) << 24) | (((color.full&0xff)<<8)+(color.full>>8)));


    
    //打印所有任务信息
    // imb_task_info_dump(imb_task_head_get(0));

    //启动合成&推屏
    struct rect disp;//unused
    struct rect page_draw = {0};
    struct rect screen_rect;//屏幕有效显示区域
    screen_rect.left = 0;
    screen_rect.top = 0;
    screen_rect.width = rect.width;
    screen_rect.height = rect.height;

    rect.left  = 0;
    rect.top = 0;

    u16 bg_stride = (rect.width * 2 + 3) / 4 * 4;
    u16 colums = rect.width;
    u16 lines = rect.height;//info.buffer_size / info.buf_num / bg_stride;

    imb_task_head_set_buf(imb_task_head_get(0), buf, 0, rect.width, rect.height, bg_stride, lines, 0);
    imb_task_head_config(imb_task_head_get(0), &rect, &screen_rect, &screen_rect, &page_draw, STATE_SYNTHESIS_AND_DRAW);

    struct imb_cb_interface itf = {0};
    usr_buf = buf;
    itf.buf_get = usr_buf_get;
    itf.buf_check = usr_buf_check;
    itf.buf_set_idle = usr_buf_set_idle;
    itf.buf_set_pending = usr_buf_set_pending;
    itf.buf_wait_finish = usr_buf_wait_finish;
    itf.draw_area = usr_draw_area;
    itf.draw_meld_area = usr_draw_meld_area;

    //打印所有任务信息
    // imb_task_info_dump(imb_task_head_get(0));

    int a = jiffies_half_msec();
    int aa = TICK_CNT;//jiffies_half_msec();
    imb_start(imb_task_head_get(0), &screen_rect, disp, colums, lines, &itf);
    int b = jiffies_half_msec();
     int bb = TICK_CNT;//jiffies_half_msec();
    // printf("L %d 1/2 %d",b-a, bb-aa);

    imb_task_all_destroy(imb_task_head_get(0));

    return ;    
}

LV_ATTRIBUTE_FAST_MEM void my_draw_blend(lv_draw_ctx_t * draw_ctx, const lv_draw_sw_blend_dsc_t * dsc)
{
    /*Let's get the blend area which is the intersection of the area to fill and the clip area.*/
    lv_area_t blend_area;
    if(!_lv_area_intersect(&blend_area, dsc->blend_area, draw_ctx->clip_area)) return;  /*Fully clipped, nothing to do*/

    /*Fill only non masked, fully opaque, normal blended and not too small areas*/
    if(1 && dsc->src_buf == NULL && dsc->mask_buf == NULL &&  dsc->opa > LV_OPA_MIN && dsc->opa < LV_OPA_MAX&& /* 这里改成透明度经过IMB合成，非透明走软件memset合成速度更快 */
       dsc->blend_mode == LV_BLEND_MODE_NORMAL && lv_area_get_size(&blend_area) > 10000) {
        
        //  判断合成buf与裁剪区域是否相等，进一步加速
        u8 equal = _lv_area_is_equal(&blend_area, draw_ctx->clip_area);

        /*Got the first pixel on the buffer*/
        lv_coord_t dest_stride = lv_area_get_width(draw_ctx->buf_area); /*Width of the destination buffer*/
        lv_color_t * dest_buf = draw_ctx->buf;
        // dest_buf += dest_stride * (blend_area.y1 - draw_ctx->buf_area->y1);// + (blend_area.x1 - draw_ctx->buf_area->x1);

        /*Make the blend area relative to the buffer*/      
        lv_area_move(&blend_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);

        /*Call your custom gou fill function to fill blend_area, on dest_buf with dsc->color*/  

        // // 黑白纯色，简单的memset加速
        // if(dsc->opa > LV_OPA_MAX && (dsc->color.full == 0 || dsc->color.full == 0xffff)) {
        //     int32_t w = lv_area_get_width(&blend_area);
        //     int32_t h = lv_area_get_height(&blend_area);

        //     int32_t x;
        //     int32_t y;

        //     if(equal){
        //         memset(dest_buf, dsc->color.full, w*h*2);
        //     } else {
        //         for(y = 0; y < h; y++) {
        //             memset(dest_buf, dsc->color.full, w*2);
        //             dest_buf += dest_stride;
        //         }                
        //     }
        //     return;
        // } 

        //  其他颜色就GPU加速       优化效率22%     纯色200*200 20%透明度测试
        int a = jiffies_half_msec();
        int aa = TICK_CNT;//jiffies_half_msec();
        jl_gpu_fill(dest_buf, dest_stride, &blend_area, dsc->color, dsc->opa, lv_area_get_height(draw_ctx->buf_area));
        int b = jiffies_half_msec();
        int bb = TICK_CNT;//jiffies_half_msec();
        // printf("imb L %d 1/2 %d",b-a, bb-aa);

        // int a = jiffies_half_msec();
        // int aa = TICK_CNT;//jiffies_half_msec();
        // lv_draw_sw_blend_basic(draw_ctx, dsc);
        // int b = jiffies_half_msec();
        // int bb = TICK_CNT;//jiffies_half_msec();
        // printf("sw L %d 1/2 %d",b-a, bb-aa);
    }
    /*Fallback: the GPU doesn't support these settings. Call the SW renderer.*/
    else {
        int a = jiffies_half_msec();
        int aa = TICK_CNT;//jiffies_half_msec();
        lv_draw_sw_blend_basic(draw_ctx, dsc);
        int b = jiffies_half_msec();
        int bb = TICK_CNT;//jiffies_half_msec();
        // printf("sw L %d 1/2 %d",b-a, bb-aa);
    }
}


void wait_for_finish(struct _lv_draw_ctx_t * draw_ctx){
    // int a = jiffies_msec();
    // while (!(JL_IMB->IMB_CON0 & BIT(31))){
    //     if(jiffies_msec()-a>100) break;
    // }
    // imb_task_unlock();
}

void flash_tab_info_release(struct flash_file_info *file_info);
LV_ATTRIBUTE_FAST_MEM void lv_draw_imb_img_decoded(struct _lv_draw_ctx_t * draw_ctx, const lv_draw_img_dsc_t * draw_dsc,
                                                  const lv_area_t * coords_src, const uint8_t * src_buf, lv_img_cf_t cf)
{
    
    //     u32 rets;//, reti;
    // __asm__ volatile("%0 = rets":"=r"(rets));
    // printf("%x", rets);
    // if(0x604b39c != rets) return;
        
    //  转成非CONST变量
    lv_area_t coords_temp = {0};
    lv_area_t  * coords;
    coords = &coords_temp;
    memcpy(coords, coords_src, sizeof(lv_area_t)); 

    struct image_file file = {0};
    int ui_group_n;
    file.compress = 0;
    struct flash_file_info file_info={0};
    // printf(">>>%x cf:%d", src_buf, cf);

    struct _lv_draw_ctx_t * draw_buf = draw_ctx;
    int px = coords->x1; //图片绝对区域x
    int py = coords->y1; //图片绝对区域y
    int pw = coords->x2-coords->x1+1; //图片绝对区域w
    int ph = coords->y2-coords->y1+1;  //图片绝对区域h


    //  图片裁剪区域
    lv_area_t  res_p={0};
    lv_area_t  res_p2={0};
    //  BUF与人工裁剪区域的交集
    if(0==(_lv_area_intersect(&res_p, draw_buf->buf_area, draw_buf->clip_area))){
        printf("lv no intersect buf and clip");
        // lv_draw_sw_img_decoded(draw_ctx, draw_dsc,coords, src_buf, cf);
        return ;   //没有剪切区域
    }  
    //  BUF与图片区域的交集
    // _lv_area_intersect(&res_p2, draw_buf->buf_area, coords);

    

    // printf("333");
    struct rect *crop = image_set_crop( res_p.x1, 
                                res_p.y1, 
                                res_p.x2-res_p.x1+1, 
                                res_p.y2-res_p.y1+1 );   

    // printf("pw,ph %d %d src_buf %x",pw,ph, src_buf);

    static int flag = 1;
    // flag = 1-flag;
    //  支持的
    if(flag && (LV_IMG_CF_ALPHA_8BIT == cf ||
        (LV_IMG_CF_TRUE_COLOR == cf && lv_area_get_size(&res_p) > 240*240)||    //  解压RGB没必要用IMB加速，用MEMCPY更块一点
        // LV_IMG_CF_TRUE_COLOR_ALPHA == cf || /* &&(src_buf>=PSRAM_CACHE_ADDR) */ /* 解压图片 */
        LV_IMG_CF_RAW == cf)) /* 压缩图片 */
    {

    } else {
        // printf("SW PIC DECORD");
        int a = jiffies_half_msec();// TICK_CNT;
        int aa = TICK_CNT;
        lv_draw_sw_img_decoded(draw_ctx, draw_dsc,coords, src_buf, cf);
        int b = jiffies_half_msec();// TICK_CNT;
        int bb = TICK_CNT;
        // printf("sw %d 1/2 %d", b-a, bb-aa);
        return;        
    }

    //  但不支持
    if(0/*  || (lv_disp_get_default()->driver->draw_buf->buf_act != draw_buf->buf && !(draw_ctx->user_data==777 || draw_ctx->user_data==333))  ALPHA输出不支持 */
            || (draw_dsc->angle  && draw_dsc->zoom != LV_IMG_ZOOM_NONE)  /* 同时缩放旋转 */
        //  || ((pw > 240 || ph >240) && draw_dsc->zoom != LV_IMG_ZOOM_NONE) /* 缩放超过240*240 */
    )
    {
        if(cf == LV_IMG_CF_RAW) return; //RAW自定义格式LV软件不支持的，直接返回
        //LV格式的资源imb不支持的格式走LV软件合成
        lv_draw_sw_img_decoded(draw_ctx, draw_dsc,coords, src_buf, cf);
        return;
    }

    //  IMB合成


    //  不需要做以下限制，旋转缩放不需要与原图交集，与CLIP即可。
    // if(0==(_lv_area_intersect(&res_p, &res_p, coords))){
    //     printf("lv no intersect buf and clip");
    //     // lv_draw_sw_img_decoded(draw_ctx, draw_dsc,coords, src_buf, cf);
    //     return ;   //没有剪切区域
    // }  

    // printf("111");



    //  进行对齐处理
    // if(LV_IMG_CF_TRUE_COLOR == cf){
    //     pw = pw+pw%2;
    // }else if(LV_IMG_CF_TRUE_COLOR_ALPHA == cf){
    //     pw = (pw+3)/4*4;
    // }
    

    // 初始化imb的file信息
    if(LV_IMG_CF_ALPHA_8BIT == cf){     //24.8%    SRAM104*45
        file.format = PIXEL_FMT_A8;
        file.width  = pw;
        file.height = ph;
        // printf("RGB");
    }else if(LV_IMG_CF_TRUE_COLOR == cf){   //  96%  FLASH296*240
        file.format = PIXEL_FMT_RGB565;
        file.width  = pw;
        file.height = ph;
        // printf("RGB");
    }else if(LV_IMG_CF_TRUE_COLOR_ALPHA == cf){     //10%    FLASH296*240
        file.format = PIXEL_FMT_ARGB8565;
        file.width  = pw;
        file.height = ph;
        // printf("ARGB");
    }else if(LV_IMG_CF_RAW == cf){      // 非压缩的80%
        //压缩资源，构建表
        if(0x1234 == draw_ctx->user_data){  //imb文件系统
            // printf("%s", src_buf);
            ui_group_n = get_jl_img_info_by_group_incache(src_buf, &file, NULL);
            if(ui_group_n  == -1){
                printf("ui_group_n ==-1");
                return ;
            }
        } else {    //  自定义地址跑这
            // printf("src_buf: %x", src_buf);
            struct img_h * img_head = src_buf;
            memcpy(&file, &(img_head->file), sizeof(struct image_file));
            // printf("dec w h f %d %d %d ",img_head->file.width, img_head->file.height, img_head->file.format);
            // put_buf(img_head->data, 4);
        }
    }

    

    if(file.format == PIXEL_FMT_JPEG && 0x1234 == draw_ctx->user_data){  //imb文件系统
        //2.图片阻塞式解压测试(不依赖文件系统)
        struct flash_file_info tmp_file_info = {0};
        
        //  资源ID所在FLASH存储
        int lut_tab_offset = 0;
        struct flash_file_info *info = (struct flash_file_info *)&ui_res_gropu[ui_group_n].flash_file_info;
        struct flash_file_info *flash_info = &tmp_file_info;
        struct image_file * f = &file;
        int filelen = f->len;
        flash_info->tab = &info->tab[(f->offset + info->offset + lut_tab_offset) / 4096];
        int file_base_addr = flash_info->tab[0] + (f->offset + info->offset + lut_tab_offset) % 4096;
        int flash_map_tab_num = (file_base_addr % 4096 + filelen + 4096 - 1) / 4096;
        flash_info->offset = file_base_addr % 4096;
        flash_info->tab_size = flash_map_tab_num * sizeof(u32);
        flash_info->last_tab_data_len = flash_map_tab_num * 4096 - filelen - flash_info->offset;

        imb_jpg_draw(flash_info, draw_buf, coords, NULL, draw_ctx->clip_area);

        return;
    }

    if(file.format == PIXEL_FMT_JPEG) {
        static struct FileIndex jpgres = {0};
        struct img_h* img_data = (struct img_h*)src_buf;
        jpgres.addr = img_data->data;
        jpgres.len  = img_data->file.len;
        // printf("JPG DEC ADR:%x %d", jpgres.addr, jpgres.len);

        const uint8_t jpg_signature[] = {0xFF, 0xD8, 0xFF};
        if(memcmp(jpg_signature, img_data->data, sizeof(jpg_signature))){

            printf("JPG 数据异常 指针:%x", img_data->data);
            put_buf(img_data->data, 4);
            return ;
        }

        // while(sd_busy);
        static void * tempbuf;
        tempbuf = malloc(img_data->file.len);
        memcpy(tempbuf, img_data->data, img_data->file.len);
        jpgres.addr = tempbuf;

        imb_jpg_draw(&jpgres, draw_buf, coords, usr_jpg_dec_stream_input2, draw_ctx->clip_area);
        
        free(tempbuf);

        return;
    }

        //  判断是否需要截图
    if(!_lv_area_is_equal(&res_p2, &res_p) && 0){
        // printf("判断是否需要截图");
        // printf("222");

        // if(lv_area_get_width(&res_p)%2!=0){
        //     return;
        // }

        // u8 * temp = malloc(lv_area_get_size(&res_p)*3);
        // // printf("malloc %d", lv_area_get_size(&res_p)*2);
        // if(temp==0) return;

        // // printf("draw_ctx->buf : %x 十： %d",draw_ctx->buf,draw_ctx->buf);
        // // printf("temp->buf : %x 十： %d",temp,temp);
        // lv_area_t  s_res_p={0};
        // lv_area_t  e_res_p={0};
        // lv_area_copy(&s_res_p, &res_p);
        // lv_area_copy(&e_res_p, &res_p);
        // lv_area_move(&s_res_p, -res_p.x1, -res_p.y1);   
        // lv_area_move(&e_res_p, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);   

        // lv_draw_sw_buffer_copy(draw_ctx,  temp, lv_area_get_width(&s_res_p), &s_res_p,
        //                                    draw_ctx->buf, lv_area_get_width(draw_ctx->buf_area), &e_res_p);


        // lv_area_t ori_area={0};
        // void *ori_buf = draw_ctx->buf;
        // draw_ctx->buf = temp;
        // lv_area_copy(&ori_area, draw_ctx->buf_area);
        // lv_area_copy(draw_ctx->buf_area, &res_p);
        // lv_draw_imb_img_decoded(draw_ctx, draw_dsc, coords_src, src_buf, cf);
        // draw_ctx->buf = ori_buf;
        // lv_area_copy(draw_ctx->buf_area, &ori_area);

        // lv_draw_sw_buffer_copy(draw_ctx, draw_ctx->buf, lv_area_get_width(draw_ctx->buf_area), &e_res_p, 
        //                                     temp, lv_area_get_width(&s_res_p), &s_res_p);

        // free(temp);
        // return;

        //2.图片阻塞式解压测试(不依赖文件系统)
        struct flash_file_info tmp_file_info = {0};
        struct flash_file_info *info = (struct flash_file_info *)&ui_res_gropu[ui_group_n].flash_file_info;

        int lut_tab_offset = 0;
        tmp_file_info.tab = &info->tab[(file.offset + info->offset + lut_tab_offset) / 4096];
        tmp_file_info.offset = tmp_file_info.tab[0] + (file.offset + info->offset + lut_tab_offset) % 4096;

        int image_size = image_pixel_size(lv_area_get_width(&res_p), lv_area_get_height(&res_p), file.format);
        u8 * image_buf = (u8 *)malloc(image_size);
        img_set_input(DATA_SRC_FLASH, file.compress, file.width, file.height, file.format, tmp_file_info.tab, tmp_file_info.offset);
        img_set_output(image_buf, 0, 0, file.width, file.height);
        img_kick_sync();
        
        lv_draw_imb_img_decoded(draw_ctx, draw_dsc, coords_src, image_buf, cf);

        free(image_buf);

        flash_tab_info_release(&tmp_file_info);

        return;
    }

    //  加载资源方式
    int load_mef = -1;
    void * src_addr = NULL;
    if(LV_IMG_CF_RAW == cf){
        //IMB压缩资源，构建表
        if(0x1234 == draw_ctx->user_data){  //imb文件系统
            load_mef = LOAD_FROM_FLASH_WITH_TAB; 
            src_addr = &ui_res_gropu[ui_group_n].flash_file_info;
        } else {
            load_mef = LOAD_FROM_STATIC_RAM; 
            if(src_buf >= PSRAM_CACHE_ADDR) { //PSRAM DMA地址
                src_addr = psram_cache2nocache_addr(32+src_buf);
            } else {
                src_addr = 32+src_buf;
            }
        }
    } else if(src_buf >= 0x6000000){   //内挂flash
        load_mef = LOAD_FROM_FLASH_WITHOUT_TAB;
        src_addr = src_buf;
    }else if(src_buf >= 0x4000000){ //外挂flash
        load_mef = LOAD_FROM_FLASH_WITHOUT_TAB;
        src_addr = src_buf;
    }else if(src_buf >= PSRAM_CACHE_ADDR + PSRAM_MAPPING_SIZE) { //PSRAM DMA地址
        load_mef = LOAD_FROM_STATIC_RAM;
        src_addr = src_buf;
        //  分块缩放原图先判断是否2对齐
        if(LV_IMG_ZOOM_NONE != draw_dsc->zoom ){
            int coords_src_w = lv_area_get_width(coords_src);
            int coords_src_h = lv_area_get_height(coords_src);
            if(lv_area_get_width(coords) % 2 != 0){
                printf("div part src pic width no align 2 px");
                return;
            }
        }
    }else if(src_buf >= PSRAM_CACHE_ADDR){  //PSRAM cache地址
        load_mef = LOAD_FROM_STATIC_RAM;  
        src_addr = psram_cache2nocache_addr(src_buf);
    }else{
        load_mef = LOAD_FROM_STATIC_RAM;//LOAD_FROM_RAM_AUTO;//
        // LOAD_FROM_STATIC_RAM;
        src_addr = src_buf;
        // printf("111111111111");
        //imb不支持的格式走软件合成
        // lv_draw_sw_img_decoded(draw_ctx, draw_dsc,coords, src_buf, cf);
        // return;
    }
    


    // printf("IMB DECORD %x", src_addr);

    // LVGL的BUF刷新窗口计算
    struct rect rect;//当前刷新区域
    rect.left = draw_buf->buf_area->x1;
    rect.top = draw_buf->buf_area->y1;
    rect.width = (draw_buf->buf_area->x2) - (draw_buf->buf_area->x1) +1;
    rect.height = (draw_buf->buf_area->y2) - (draw_buf->buf_area->y1) +1;
    
    //  图片相关参数    
    int prw =  draw_dsc->zoom;
    int prh =  draw_dsc->zoom; //XY缩放
    u16 angle = draw_dsc->angle; //旋转角度
    int dx = draw_dsc->pivot.x;
    int dy = draw_dsc->pivot.y;   //旋转或缩放中心
    void *buf = draw_buf->buf;  //当前合成输出的BUF
    int bufsize = rect.width*rect.height*2; //当前合成输出BUF长度
    

    // memset(buf, 0x00, bufsize);//白色


    //以BUF左上角为起始
    int xoffset = 0;
    int yoffset = 0;
    xoffset = rect.left;
    yoffset = rect.top;
    px = px - xoffset;
    py = py - yoffset;
    crop->left -= xoffset;
    crop->top -= yoffset;
    rect.left -= xoffset;
    rect.top -= yoffset;
    int compx = 0;
    int compy = 0;
    if(dy-yoffset<compy){//  旋转的圆心负坐标需要特殊处理
        compy = dy-yoffset;
    }
    if(dx-xoffset<compx){
        compx = dx-xoffset;
    }
    if(py+dy<compy){
        compy = py+dy;
    }    
    if(px+dx<compx){
        compx = px+dx;
    }


int ss=TICK_CNT;
    int imb_task_get_id = 0;

    struct imb_task_info imb_tsk_info = {0};
    imb_tsk_info.data_src       = DATA_SRC_NONE;//无数据源
    imb_tsk_info.zip_en         = 0;
    imb_tsk_info.in_format      = LAYER_FORMAT_SOLID;//纯色
    imb_tsk_info.out_format     = OUTPUT_FORMAT_RGB565;
    imb_tsk_info.x_offset       = compx;
    imb_tsk_info.y_offset       = compy;
    imb_tsk_info.src_w          = rect.width - compx;
    imb_tsk_info.src_h          = rect.height - compy;
    imb_tsk_info.des_w          = rect.width - compx;
    imb_tsk_info.des_h          = rect.height - compy;
    imb_tsk_info.priv           = 0;//纯色格式，该参数表示颜色0xr5g6b5
    imb_tsk_info.osd0_in_buf    = 1;

    // struct imb_task *p_task = imb_task_search_by_id(imb_task_head_get(0), 0, 0);
    // if(p_task){
    //     imb_task_reset(imb_task_head_get(0), p_task, &imb_tsk_info); //imb_task参数重置
    //     if (imb_tsk_info.osd0_in_buf) {
    //         p_task->osd0_in_buf = 1;
    //         p_task->rgb_tsk_en = false;
    //     }
    // } else {
        imb_task_list_init(imb_task_head_get(0), &imb_tsk_info);
    // }
    
    // __imb_task_delete_by_id(imb_task_head_get(0), 1, 0);
    
    //  普通图片
    if(LV_IMG_ZOOM_NONE != prw || LV_IMG_ZOOM_NONE != prh ){   //  缩放
 
        if(0 && src_buf >= PSRAM_CACHE_ADDR && src_buf < PSRAM_NO_CACHE_ADDR+PSRAM_MAPPING_SIZE){

    
            int  ZOOM_W_LIMIT = 240;//90//120
            int  ZOOM_H_LIMIT = 240;//90//120

            int coords_src_w = lv_area_get_width(coords_src);
            int coords_src_h = lv_area_get_height(coords_src);
            ZOOM_W_LIMIT = coords_src_w / 2;
            ZOOM_H_LIMIT = coords_src_h / 2;

            //  基数加1，成为2对齐
            if(ZOOM_W_LIMIT%2 != 0){
                ZOOM_W_LIMIT += 1;
            }

            u8 *src_buf = src_addr;

            //  X方向分割
            for(coords->x1 = coords_src->x1; 
                (coords->x1 + ZOOM_W_LIMIT - 1 < coords_src->x2) ||
                (coords_src->x2 != coords->x2);
                coords->x1 += ZOOM_W_LIMIT) {
                if((coords->x1 + ZOOM_W_LIMIT - 1 >= coords_src->x2) && 
                    coords_src->x2 != coords->x2){
                    coords->x1 = coords->x1;
                    coords->x2 = coords_src->x2;
                } else {
                    coords->x2 = coords->x1 + ZOOM_W_LIMIT - 1;
                }
                
                //  Y方向分割
                for(coords->y1 = coords_src->y1; 
                    (coords->y1 + ZOOM_H_LIMIT - 1 < coords_src->y2) ||
                    (coords_src->y2 != coords->y2);
                    coords->y1 += ZOOM_H_LIMIT) {
                    if((coords->y1 + ZOOM_H_LIMIT - 1 >= coords_src->y2) && 
                        coords_src->y2 != coords->y2){
                        coords->y1 = coords->y1;
                        coords->y2 = coords_src->y2;
                    } else {
                        coords->y2 = coords->y1 + ZOOM_H_LIMIT - 1;
                    }

                    // printf("PIVOT XY: %d %d", draw_dsc->pivot.x, draw_dsc->pivot.y);
                    // printf("\n cf %d coords x12 y12 : %d %d %d %d \n",
                    //     cf,
                    //     coords->x1,
                    //     coords->x2,
                    //     coords->y1,
                    //     coords->y2
                    // );    
                    lv_area_t coords_zoom = {0};
                    lv_memcpy(&coords_zoom, coords, sizeof(lv_area_t));
                    
                    // int px = ((coords->x1-coords_src->x1 ) * draw_dsc->zoom/256) + 1;
                    // coords_zoom.x1 = coords_src->x1 + px                        - 1;//(coords->x2-coords->x1)/2;
                    // coords_zoom.x2 = coords_zoom.x1 + lv_area_get_width(coords) - 1;
                    // int py = ((coords->y1-coords_src->y1 )* draw_dsc->zoom/256) + 1;
                    // coords_zoom.y1 = coords_src->y1 + py                         - 1;//(coords->x2-coords->x1)/2;
                    // coords_zoom.y2 = coords_zoom.y1 + lv_area_get_height(coords) - 1;


                    lv_draw_img_dsc_t draw_dsc_zoom = {0};
                    lv_memcpy(&draw_dsc_zoom, draw_dsc, sizeof(lv_draw_img_dsc_t));

                    draw_dsc_zoom.pivot.x -= coords->x1 - coords_src->x1 ;
                    draw_dsc_zoom.pivot.y -= coords->y1 - coords_src->y1 ;
                    // draw_dsc_zoom.zoom *= 1..;

                    //  缩放微调，消除拼接线
                    if(draw_dsc->zoom>256){
                        if(coords->x1 == coords_src->x1){
                            draw_dsc_zoom.pivot.x -= 1;                  
                        }else{
                            draw_dsc_zoom.pivot.x += 1; 
                        }

                        if(coords->y1 == coords_src->y1){
                            draw_dsc_zoom.pivot.y -= 1;      
                        }else{
                            draw_dsc_zoom.pivot.y += 1;  
                        }                
                    } else if(draw_dsc->zoom<256){
                        if(coords->x1 == coords_src->x1){
                            draw_dsc_zoom.pivot.x += 1;                  
                        }else{
                            draw_dsc_zoom.pivot.x -= 1; 
                        }

                        if(coords->y1 == coords_src->y1){
                            draw_dsc_zoom.pivot.y += 1;      
                        }else{
                            draw_dsc_zoom.pivot.y -= 1;  
                        }                                
                    }

                    // lv_draw_sw_img_decoded(draw_ctx, &draw_dsc_zoom, &coords_zoom, src_buf, cf);
                    file.width = lv_area_get_width(&coords_zoom);
                    file.height = lv_area_get_height(&coords_zoom);
                    px = coords_zoom.x1; //图片绝对区域x
                    py = coords_zoom.y1; //图片绝对区域y
                    pw = coords_zoom.x2-coords_zoom.x1+1; //图片绝对区域w
                    ph = coords_zoom.y2-coords_zoom.y1+1;  //图片绝对区域h
                    dx = draw_dsc_zoom.pivot.x;
                    dy = draw_dsc_zoom.pivot.y;   //旋转或缩放中心

                    //  左上角调整
                    px = px - xoffset;
                    py = py - yoffset;

                    imb_create_image_scale_task(++imb_task_get_id, &file,  src_buf, 
                        (float)prw/(float)LV_IMG_ZOOM_NONE, (float)prh/(float)LV_IMG_ZOOM_NONE,
                        px+dx*(LV_IMG_ZOOM_NONE-prw)/LV_IMG_ZOOM_NONE, 
                        py+dy*(LV_IMG_ZOOM_NONE-prh)/LV_IMG_ZOOM_NONE, 
                        pw*prw/LV_IMG_ZOOM_NONE,ph*prh/LV_IMG_ZOOM_NONE,
                        NULL, file.compress, load_mef);      

                    uint8_t px_size = lv_img_cf_get_px_size(cf);
                    src_buf += lv_area_get_size(coords)*((px_size + 7) >> 3);

                    // break;
                }

                // break;
            }
        } else {
            // y_printf("%s%d",__func__,__LINE__);
            imb_create_image_scale_task(++imb_task_get_id, &file,  src_addr, 
                (float)prw/(float)LV_IMG_ZOOM_NONE, (float)prh/(float)LV_IMG_ZOOM_NONE,
                px+dx*(LV_IMG_ZOOM_NONE-prw)/LV_IMG_ZOOM_NONE, 
                py+dy*(LV_IMG_ZOOM_NONE-prh)/LV_IMG_ZOOM_NONE, 
                pw*prw/LV_IMG_ZOOM_NONE,ph*prh/LV_IMG_ZOOM_NONE,
                NULL, file.compress, load_mef);         
        }
    } 
    else if(angle){   //  旋转

        if (1 || file.height*file.width < 120*120*2 ) {  //占RAM速度快120*120图以内不分快
            imb_create_image_rotate_task(++imb_task_get_id, &file, src_addr, 
                dx, dy, (angle/10)%360, px+dx-compx, py+dy-compy, 
                NULL, load_mef
            );
        } else {  //不占RAM速度慢
            // printf("YYYY %d h %d",py+dy-compy, rect.height);
            imb_create_image_rotate_chunk_task(++imb_task_get_id, &file, src_addr, 
                dx, dy, (angle/10)%360, px+dx-compx, py+dy-compy, load_mef
            );
        }
        
        // int b = jiffies_half_msec();
        // printf("imb rota %d %d 1/2ms", angle, b-a);
    } else{    //      原大小

        if(0 && src_buf >= PSRAM_CACHE_ADDR && src_buf < PSRAM_NO_CACHE_ADDR+PSRAM_MAPPING_SIZE){

    
            int  ZOOM_W_LIMIT = 240;//90//120
            int  ZOOM_H_LIMIT = 240;//90//120

            int coords_src_w = lv_area_get_width(coords_src);
            int coords_src_h = lv_area_get_height(coords_src);
            ZOOM_W_LIMIT = coords_src_w / 2;
            ZOOM_H_LIMIT = coords_src_h / 2;

            //  基数加1，成为2对齐
            if(ZOOM_W_LIMIT%2 != 0){
                ZOOM_W_LIMIT += 1;
            }

            u8 *src_buf = src_addr;

            //  X方向分割
            for(coords->x1 = coords_src->x1; 
                (coords->x1 + ZOOM_W_LIMIT - 1 < coords_src->x2) ||
                (coords_src->x2 != coords->x2);
                coords->x1 += ZOOM_W_LIMIT) {
                if((coords->x1 + ZOOM_W_LIMIT - 1 >= coords_src->x2) && 
                    coords_src->x2 != coords->x2){
                    coords->x1 = coords->x1;
                    coords->x2 = coords_src->x2;
                } else {
                    coords->x2 = coords->x1 + ZOOM_W_LIMIT - 1;
                }
                

                // printf("PIVOT XY: %d %d", draw_dsc->pivot.x, draw_dsc->pivot.y);
                // printf("\n cf %d coords x12 y12 : %d %d %d %d \n",
                //     cf,
                //     coords->x1,
                //     coords->x2,
                //     coords->y1,
                //     coords->y2
                // );    
                lv_area_t coords_zoom = {0};
                lv_memcpy(&coords_zoom, coords, sizeof(lv_area_t));
                
                // int px = ((coords->x1-coords_src->x1 ) * draw_dsc->zoom/256) + 1;
                // coords_zoom.x1 = coords_src->x1 + px                        - 1;//(coords->x2-coords->x1)/2;
                // coords_zoom.x2 = coords_zoom.x1 + lv_area_get_width(coords) - 1;
                // int py = ((coords->y1-coords_src->y1 )* draw_dsc->zoom/256) + 1;
                // coords_zoom.y1 = coords_src->y1 + py                         - 1;//(coords->x2-coords->x1)/2;
                // coords_zoom.y2 = coords_zoom.y1 + lv_area_get_height(coords) - 1;


                lv_draw_img_dsc_t draw_dsc_zoom = {0};
                lv_memcpy(&draw_dsc_zoom, draw_dsc, sizeof(lv_draw_img_dsc_t));

                draw_dsc_zoom.pivot.x -= coords->x1 - coords_src->x1 ;
                draw_dsc_zoom.pivot.y -= coords->y1 - coords_src->y1 ;
                // draw_dsc_zoom.zoom *= 1..;

                //  缩放微调，消除拼接线
                if(draw_dsc->zoom>256){
                    // if(coords->x1 == coords_src->x1){
                    //     draw_dsc_zoom.pivot.x -= 1;                  
                    // }else{
                    //     draw_dsc_zoom.pivot.x += 1; 
                    // }

                    // if(coords->y1 == coords_src->y1){
                    //     draw_dsc_zoom.pivot.y -= 1;      
                    // }else{
                    //     draw_dsc_zoom.pivot.y += 1;  
                    // }                
                }

                // lv_draw_sw_img_decoded(draw_ctx, &draw_dsc_zoom, &coords_zoom, src_buf, cf);
                file.width = lv_area_get_width(&coords_zoom);
                file.height = lv_area_get_height(&coords_zoom);
                px = coords_zoom.x1; //图片绝对区域x
                py = coords_zoom.y1; //图片绝对区域y
                pw = coords_zoom.x2-coords_zoom.x1+1; //图片绝对区域w
                ph = coords_zoom.y2-coords_zoom.y1+1;  //图片绝对区域h
                dx = draw_dsc_zoom.pivot.x;
                dy = draw_dsc_zoom.pivot.y;   //旋转或缩放中心

                //  左上角调整
                px = px - xoffset;
                py = py - yoffset;

                imb_create_image_task(++imb_task_get_id, &file, src_buf, 
                    px,py,pw,ph,
                    NULL, file.compress, load_mef,  draw_dsc->recolor);//wid 

                uint8_t px_size = lv_img_cf_get_px_size(cf);
                src_buf += lv_area_get_size(coords)*((px_size + 7) >> 3);
            }
        } else {
            imb_create_image_task(++imb_task_get_id, &file, src_addr, 
                px,py,pw,ph,
                crop, file.compress, load_mef, draw_dsc->recolor);//width,height参数可小于file.width, file.height,若小于则裁剪 
        }
    }       
    
    //打印所有任务信息
    // imb_task_info_dump(imb_task_head_get(0));

    struct lcd_info info = {0};
    static struct bg_buffer bg = {0};
    if (__this->lcd->get_screen_info) {
        __this->lcd->get_screen_info(&info);
    }

    //启动合成&推屏
    struct rect disp;//unused
    struct rect page_draw = {0};
    struct rect screen_rect;//屏幕有效显示区域
    screen_rect.left = 0;
    screen_rect.top = 0;
    screen_rect.width = rect.width;
    screen_rect.height = rect.height;

    rect.left  = 0;
    rect.top = 0;

    u16 bg_stride = (rect.width * 2 + 3) / 4 * 4;

    imb_task_head_set_buf(imb_task_head_get(0), buf, NULL, rect.width, rect.height, bg_stride, rect.height, NULL);
    imb_task_head_config(imb_task_head_get(0), &rect, &screen_rect, &screen_rect, &page_draw, STATE_SYNTHESIS_AND_DRAW);

    struct imb_cb_interface itf = {0};
    usr_buf = buf;
    itf.buf_get = usr_buf_get;
    itf.buf_check = usr_buf_check;
    itf.buf_set_idle = usr_buf_set_idle;
    itf.buf_set_pending = usr_buf_set_pending;
    itf.buf_wait_finish = usr_buf_wait_finish;
    itf.draw_area = usr_draw_area;
    itf.draw_meld_area = usr_draw_meld_area;

    //打印所有任务信息
    // imb_task_info_dump(imb_task_head_get(0));

    
    int a = jiffies_half_msec();// TICK_CNT;
    int aa = TICK_CNT;//jiffies_half_msec();
    imb_start(imb_task_head_get(0), &screen_rect, disp, rect.width, rect.height, &itf );
    // extern void imb_task_kick(struct imb_task_head *root, struct rect *limit, struct rect disp, u16 colums, u16 lines, struct imb_cb_interface *itf);
    // ____imb_task_kick(imb_task_head_get(0), &screen_rect, disp, colums, lines, &itf );
    int bb = TICK_CNT;//jiffies_half_msec();
    int b = jiffies_half_msec();// TICK_CNT;
// TICK_CNT
    //  dump_imb_reg(imb_task_head_get(0));

    imb_task_all_destroy(imb_task_head_get(0));
    flash_tab_info_release(&file_info);

    int ee = TICK_CNT;
        

    // printf(" %d %d %d", aa-ss, bb-aa, ee-bb);

    return ;
    
}

LV_ATTRIBUTE_FAST_MEM void lv_draw_imb_draw_letter(struct _lv_draw_ctx_t * draw_ctx, const lv_draw_label_dsc_t * dsc,  const lv_point_t * pos_p,
                        uint32_t letter)
{
    #if 0//1   //  A8缓冲&2D加速

    // lv_draw_label(driver.draw_ctx, draw_dsc, &coords, txt, NULL);
    //  申请一块字体空间，改draw_ctx区域
    lv_draw_sw_letter(draw_ctx, dsc,   pos_p,  letter);

    if(bpp == LV_IMGFONT_BPP) { //is imgfont
        lv_area_t fill_area;
        fill_area.x1 = pos->x;
        fill_area.y1 = pos->y;
        fill_area.x2 = pos->x + g->box_w - 1;
        fill_area.y2 = pos->y + g->box_h - 1;
        lv_draw_img_dsc_t img_dsc;
        lv_draw_img_dsc_init(&img_dsc);
        img_dsc.angle = 0;
        img_dsc.zoom = LV_IMG_ZOOM_NONE;
        img_dsc.opa = dsc->opa;
        img_dsc.blend_mode = dsc->blend_mode;
        lv_draw_img(draw_ctx, &img_dsc, &fill_area, map_p);
        return;
    }


    #endif
    lv_draw_sw_letter(draw_ctx, dsc,   pos_p,
                         letter);

}

void lv_draw_jl_dma2d_ctx_init(lv_disp_drv_t * drv, lv_draw_ctx_t * draw_ctx)
{
    lv_draw_sw_init_ctx(drv, draw_ctx);

    lv_draw_sw_ctx_t * dma2d_draw_ctx = (lv_draw_sw_ctx_t *)draw_ctx;

    //  不带mask半透背景优化效率22%     纯色200*200 20%透明度测试
    // dma2d_draw_ctx->blend = my_draw_blend;//lv_draw_jl_dma2d_blend; //  纯色灰度填充，预先IMB合成, 其中纯色0透明度好像没啥优化效果,392*392矩形带A优化效果：IMB 44fps  lv 25FPS
    dma2d_draw_ctx->base_draw.draw_img = lv_draw_jl_dma2d_img;//    杰理压缩图片或jpg硬解码 直接接管合成
   
    //  PIXEL_FMT_A8                24.8%       SRAM104*45      RAAM小图可以36-58fps
    //  PIXEL_FMT_RGB565            96%         FLASH296*240    小图不行
    //  LV_IMG_CF_TRUE_COLOR_ALPHA  10%         FLASH296*240   
    //  ARGB    27*24  200*200
    //  SRAM    27->60fps
    //  FLASH   30->53fps
    dma2d_draw_ctx->base_draw.draw_img_decoded = lv_draw_imb_img_decoded;// 对于RAM或连续的FLASH的图片可以直接预先IMB合成

    // dma2d_draw_ctx->base_draw.draw_letter =  lv_draw_imb_draw_letter;
}

void lv_draw_jl_dma2d_ctx_deinit(lv_disp_drv_t * drv, lv_draw_ctx_t * draw_ctx)
{
    LV_UNUSED(drv);
    LV_UNUSED(draw_ctx);
}

#endif


#if 1//JPG







//  释放资源
void close_ui_res_gropu(int n){
    if(ui_res_gropu[n].resfile != NULL){
        res_fclose(ui_res_gropu[n].resfile);
        ui_res_gropu[n].resfile = NULL;
    }
    if(ui_res_gropu[n].indexfile != NULL){
        res_fclose(ui_res_gropu[n].indexfile);
        ui_res_gropu[n].indexfile = NULL;
    }
    if(ui_res_gropu[n].cache != NULL){
        free(ui_res_gropu[n].cache);
        ui_res_gropu[n].cache = NULL;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    构造flash地址映射表(不依赖文件系统)，只适用于地址连续的情况
   @param    flash_file_info : 文件地址信息
   @param    file_base_addr : 文件存放在flash的物理地址
   @param    filelen : 文件长度
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
int flash_tab_info_get(struct flash_file_info *file_info, u32 file_base_addr, u32 filelen)
{
    int i;
    u32 flash_map_tab_num;

    flash_map_tab_num = (file_base_addr % 4096 + filelen + 4096 - 1) / 4096;

    file_info->tab_size = flash_map_tab_num * sizeof(u32);
    file_info->tab = (u32 *)malloc(file_info->tab_size);
    if(!file_info->tab) return -1;
    file_info->offset = file_base_addr % 4096;
    file_info->last_tab_data_len = flash_map_tab_num * 4096 - filelen - file_info->offset;
    for (i = 0; i < flash_map_tab_num; i++) {
        file_info->tab[i] = file_base_addr / 4096 * 4096 + 4096 * i;
        // printf("info->tab[%d] : 0x%x\n", i, file_info->tab[i]);
    }

    return 0;
}

void flash_tab_info_release(struct flash_file_info *file_info)
{
    if (file_info->tab) {
        free(file_info->tab);
        file_info->tab = NULL;
    }
}

s8 open_res(int n){
    if(ui_res_gropu[n].resfile == NULL && ui_res_gropu[n].imbres){
        g_printf("打开分组资源: %s", ui_res_gropu[n].imbres);
        ui_res_gropu[n].resfile = res_fopen(ui_res_gropu[n].imbres, "r");
        if(!ui_res_gropu[n].resfile){
            g_printf("打开IMB资源失败");
            return -1;
        }
        if(ui_res_flash_info_get(&ui_res_gropu[n].flash_file_info, ui_res_gropu[n].imbres, "res")){
            res_fclose(ui_res_gropu[n].resfile);
            ui_res_gropu[n].resfile = NULL;
            g_printf("打开IMB资源失败");
            return -1;
        }
    }
    return 0;
}


int A2I(char* str) {
    int result = 0;
    int i = 0;

    // 逐个字符进行转换
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result;
}


//  IMB资源获取文件信息
LV_ATTRIBUTE_FAST_MEM int get_jl_img_info_by_group_incache(const void *src, struct image_file *file, lv_img_header_t * header){
    u8 *u8_p = src;//  盘符
    char * real_path = NULL;  //  真实路径
    if(u8_p[1] == ':') real_path = &u8_p[2]; 
    u8* lastname = NULL;//  文件名 

    //  查找资源组所属
    int n = -1;   
    if(u8_p[0]>='0' && u8_p[0]<='9'){
        lastname = src;
        n = 0;
    }else{
        for(u8 i=0;i<ARRAY_SIZE(ui_res_gropu);i++){
            if( u8_p[0] == ui_res_gropu[i].letter)   //盘符是否匹配
            {
                lastname = real_path;
                n = i;
                break;
            }
        }
        if(n==-1) return -1;
    }

    //  ID查找(文件系统)
    if(ui_res_gropu[n].mode == IN_RES_WITH_ID){
        open_res(n);
        // printf("id name %s", lastname);
        int id = A2I(lastname);
        open_image_by_id(0, ui_res_gropu[n].resfile, file, id&0xffff, id>>16);
        if(header){
            header->always_zero =0;
            header->cf = 1; //自定义解码格式
            header->reserved = 0;
            header->h = file->height;
            header->w = file->width;
            
        }
        // printf("%d %d",file->width,file->height);
        // printf("id2 name %s", lastname);
        return n;
    }   

    if(ui_res_gropu[n].mode == NXP_F_FILE){
        open_res(n);
        // printf("id name %s", lastname);
        int id = NAME2ID(lastname);
        // printf("%d",id);
        // int id = A2I(lastname);
        open_image_by_id(0, ui_res_gropu[n].resfile, file, id&0xffff, id>>16);
        if(header){
            header->always_zero =0;
            header->cf = 1; //自定义解码格式
            header->reserved = 0;
            header->h = file->height;
            header->w = file->width;
            // printf("%d %d", header->h, header->w);
        }
        // printf("id2 name %s", lastname);
        return n;
    }   

    if(ui_res_gropu[n].mode == IMG_ANIMING_FILE){
        void * p = NULL;
        void * table = NULL;
        int id = 0;
        usr_get_animing_info(lastname, &p, &table, &id);
        memcpy(&ui_res_gropu[n].flash_file_info, table, sizeof(struct flash_file_info));
        ui_res_gropu[n].resfile = p;
        // printf("FILE_P:%x id:%d", p, id);
        open_image_by_id(0, ui_res_gropu[n].resfile, file, id&0xffff, id>>16);
        if(header){
            header->always_zero =0;
            header->cf = 1; //自定义解码格式
            header->reserved = 0;
            header->h = file->height;
            header->w = file->width;
            // printf("%d %d", header->h, header->w);
        }
        // printf("id3 name %s", lastname);
        return n;
    }   


    // if(ui_res_gropu[n].mode == IMG_BIN_JPG_FILE) {
    //     if(header){
    //         // printf("lastname %s",lastname);
    //         if(!memcmp(lv_fs_get_ext(src), "bin", strlen("bin"))){
    //             void *fd = fopen(lastname,"r");
    //             if(fd){
    //                 fread(fd, header, sizeof(lv_img_header_t));
    //                 fclose(fd);
    //                 return n;
    //             }
    //         }
    //         else if(!memcmp(lv_fs_get_ext(src), "jpg", strlen("jpg"))) {
    //             struct flash_file_info jpg_ui_resfile_info;
    //             int ret = ui_res_flash_info_get(&jpg_ui_resfile_info, lastname, "res");
    //             imb_jpg_draw(&jpg_ui_resfile_info, NULL, NULL, NULL, NULL);
    //             struct jpeg_decoder_fd *jpg_fd = jpeg_dec_get_fd();
    //             header->always_zero =0;
    //             header->cf = 1;
    //             header->reserved = 0;
    //             header->h = jpg_fd->info.y;
    //             header->w = jpg_fd->info.x;
    //             ui_res_flash_info_free(&jpg_ui_resfile_info, "res");       
    //             return n;
    //         }  
    //     }
    // }

    return -1;
}


static u8 *usr_jpg_dec_stream_input(void *__fat_info, u32 *len, u32 offset_4k)
{
    struct CacheFile* info = (struct CacheFile*)__fat_info;
    u8 *jpg_stream = info->data;
    int file_len = info->len;
    u32 offset = offset_4k * 4096;
    u32 res_len;

    if (offset >= file_len) {
        *len = 0;
        return NULL;
    }
    res_len = file_len - offset;
    *len = (res_len > 4096) ? 4096 : res_len;

    return jpg_stream + offset;
}



static u8 *usr_jpg_dec_stream_input2(void *__fat_info, u32 *len, u32 offset_4k)
{
    
    struct FileIndex* info = (struct FileIndex*)__fat_info;
    u8 *jpg_stream = info->addr;
    int file_len = info->len;
    u32 offset = offset_4k * 4096;
    u32 res_len;

    if (offset >= file_len) {
        *len = 0;
        return NULL;
    }
    res_len = file_len - offset;
    *len = (res_len > 4096) ? 4096 : res_len;

    

    return jpg_stream + offset;
}
// jpg_prep_cache


static lv_res_t decoder_info(lv_img_decoder_t * decoder, const void * src, lv_img_header_t * header)
{
    // printf("%s", src);

    // if(lcd_sleep_status()){
    //     g_printf("休眠不能访问IMB资源 %s", src);
    //     return LV_RES_INV;
    // }
    // put_buf(src,16);
    lv_img_src_t src_type = lv_img_src_get_type(src);          /*Get the source type*/
    lv_res_t ret = LV_RES_OK;
    if(src_type == LV_IMG_SRC_VARIABLE) {
        const lv_img_dsc_t * img_dsc = src;
        uint8_t * raw_jpeg_data = (uint8_t *)img_dsc->data;
        const uint32_t raw_jpeg_data_size = img_dsc->data_size;
        const uint8_t jpg_signature[] = {0xFF, 0xD8, 0xFF};
        const uint8_t *imb_signature = "IMB";
        if(!memcmp(jpg_signature, raw_jpeg_data, sizeof(jpg_signature))){
            header->always_zero = 0;
            header->h = img_dsc->header.h;
            header->w = img_dsc->header.w;
            return LV_RES_OK;
        }else if(!memcmp(imb_signature, raw_jpeg_data, sizeof(imb_signature))){
            header->always_zero = 0;
            header->h = img_dsc->header.h;
            header->w = img_dsc->header.w;
            return LV_RES_OK;
        }
        return LV_RES_INV;
    }


    //userdata  路径    图片尺寸

    //判断是否是文件名
    // lv_img_src_t src_type = lv_img_src_get_type(src);
    if(src_type == LV_IMG_SRC_VARIABLE) {
        return LV_RES_INV;
    }
    else if(src_type != LV_IMG_SRC_FILE) {
        return LV_RES_INV;
    }

    struct image_file imgfile={0};
    sizeof(struct image_file);
    int ui_group_n = get_jl_img_info_by_group_incache(src, &imgfile, header);
    if(ui_group_n  != -1){
        return LV_RES_OK;
    }

    printf("ui_group_n ==-1");
    return LV_RES_INV;
// printf("ui_group_n == %d", ui_group_n);
    // if(imgfile.len != 0){
    //     header->always_zero = 0;
    //     header->cf = 0;/*  */
    //     header->h = imgfile.height;
    //     header->w = imgfile.width;
    //     // header->cf = 
    //     // printf("SUCCEED");
    //     return LV_RES_OK;
    // }

    // /*Support only "*.anim" files*/
    // if(ui_res_gropu[ui_group_n].mode == JPG_ANIM_WITH_FS && !memcmp(lv_fs_get_ext(src), "bin", strlen("bin"))) {
    //     // printf("anmi src %s", src);
    //     u8 *u8_p = src;//  盘符
    //     u8 * real_path = NULL; 
    //     if(u8_p[1] == ':') real_path = &u8_p[2];  //  真实路径

    //     //  通过SRAM缓存解码或者PSRAM
    //     struct CacheFile* res= readFromCache(real_path);
    //     if(res==NULL){
    //         return LV_RES_OK;
    //     }

    //     struct jpeg_decoder_fd *jpg_fd = jpeg_dec_get_fd();
    //     if(jpg_fd->fat_info != res){
    //         u8 rgb_format = 1;//1 :rgb_565 0:rgb_888
    //         char err = jpeg_dec_init(res, rgb_format, usr_jpg_dec_stream_input);
    //     }       
        
    //     header->always_zero = 0;
    //     header->h = jpg_fd->info.y;
    //     header->w = jpg_fd->info.x;
    //     return LV_RES_OK;
    // }


    // if(ui_res_gropu[ui_group_n].mode == PSRAM_IMG){
    //     if(!PSRAM_FULL_SCREEN){
    //         return LV_RES_INV;
    //     }
    //     printf("PSRAMING...");
    //     header->always_zero = 0;
    //     header->cf = 0;/*  */
    //     header->h = 454;
    //     header->w = 454;
    //     return LV_RES_OK;
    // }
    

    return LV_RES_INV;
}

void jl_imb_init(void)
{
    lv_img_decoder_t * dec = lv_img_decoder_create();
    lv_img_decoder_set_info_cb(dec, decoder_info);
    // lv_img_decoder_set_open_cb(dec, NULL);
    // lv_img_decoder_set_close_cb(dec, NULL);
    // lv_img_decoder_set_read_line_cb(dec, NULL);
}



// //  CYCLE-BUFF 管理
// #define CACHE_SIZE      3    //实际缓存个数CACHE_SIZE-1
// #define CYCLE_MALLOC    malloc
// #define CYCLE_FREE      free

// typedef struct {
//     int id;
//     struct CacheFile* buffer;
//     u8* idexfile;
//     void* idexfile_fd;
// } CacheEntry;

// CacheEntry cache[CACHE_SIZE];
// int currentEntry = 0;

// void initCache() {
//     int i;
//     for (i = 0; i < CACHE_SIZE; i++) {
//         cache[i].id = -1;
//         cache[i].buffer = NULL;
//     }
// }

// int nextEntry;

// u8 Entryisbusy(){
//     return (nextEntry != currentEntry);
// }

// void addEntry(int id, u8* idexfile) {
//     nextEntry = (currentEntry + 1) % CACHE_SIZE;
    
//     //  解析文件
//     static void *fd = NULL;
//     static void *tempfd = NULL;

//     if(!fd){
//         fd = fopen(idexfile, "r");  //SD内容
//         // printf(">>>>>>>>>>>>>>>>>>fd %d %s", fd,idexfile);
//         if(!fd){
//             return;
//         }
            
//         tempfd = fopen("storage/virfat_flash/C/temp.bin", "w+");
//         int head[4];
//         fread(fd, head, 16);
//         int tablelen = head[2]*head[3];
//         u8 * headdata = malloc(head[2]*head[3]);
//         printf("申请表长度 ：%d ", head[2]*head[3]);
//         if(!headdata){
//             printf("内存不足");
//             return;
//         }
//         fread(fd, headdata, tablelen);
//         fwrite(tempfd, headdata, tablelen);
//         free(headdata);
//     }

//     u8* buffer;
//     int len;

//     if(!fd){
//         return;
//     }
    
//     if(tempfd){
//         fseek(tempfd, id*8, SEEK_SET);
//         fread(tempfd, &buffer, 4);
//         fread(tempfd, &len, 4);
//         // printf("tempfd %x %d", buffer, len);
//     }

//     //  申请内存，拷贝内容
//     cache[currentEntry].id = id;
//     if(cache[currentEntry].buffer == NULL){
//         cache[currentEntry].buffer = CYCLE_MALLOC(sizeof(struct CacheFile) + len);  
//     }

//     if(cache[currentEntry].buffer){
        
//         fseek(fd, buffer, SEEK_SET);
//         cache[currentEntry].buffer->len = len;
//         fread(fd, cache[currentEntry].buffer->data, len);
//     }

//     //  释放下一个
//     cache[nextEntry].id = -1;
//     if(cache[nextEntry].buffer){
//         CYCLE_FREE(cache[nextEntry].buffer);
//         cache[nextEntry].buffer = NULL;
//     }

//     currentEntry = nextEntry;
// }



// void printCache() {
//     int i;
//     for (i = 0; i < CACHE_SIZE; i++) {
//         if (cache[i].id != -1) {
//             printf("ID: %d, BUFFER\n", cache[i].id);
//             // put_buf(cache[i].buffer, 16);
//         }
//     }
// }


// int isCached(int nowid) {
//     for (int i = 0; i < CACHE_SIZE; i++) {
//         if (cache[i].id == nowid) {
//             return i;
//         }
//     }
//     return -1;
// }



// IndexEntry search_file_by_name(char*name, char*index);

// void* outputfd;

// spinlock_t jpgcache;



// static int now_cache_num;


// void jpg_prep_cache(int num, int next_num, char* indexfile){
//     now_cache_num = num;
//     // while(Entryisbusy()){
//     //     // printf("xxxxx");
//     //     // os_time_dly(1);  //延时会浪费10ms
//     // }
//     // printf("{jpg_prep_cache}%d %s", num, indexfile);
//     // int a = jiffies_msec();
//     os_mutex_pend(&jpg_cache_MUTEX, 0);
//     os_taskq_post_msg("sd_jpg", 2, next_num, indexfile);
//     os_mutex_post(&jpg_cache_MUTEX);
//     // int b = jiffies_msec();
//     // printf("%d", b-a);
// }


// struct CacheFile* readFromCache(char* indexfile) {
//     // cycle-cache

//     if(isCached(now_cache_num)!=-1){
//         // printf("{isCached}%d", now_cache_num);
//         return cache[isCached(now_cache_num)].buffer;
//     } 
    
//     // printf("{noCached}%d %s", now_cache_num,indexfile );
//     // jpg_prep_cache(num, indexfile);

//     // int cnt = 100;  //1s超时
//     // while(Entryisbusy() && cnt--){
//     //     os_time_dly(1);
//     // }    

//     // if(isCached(num)){
//     //     return cache[isCached(num)].buffer;
//     // }    

//     return NULL;
// }






// //  二分法查找
// IndexEntry search_file_by_name(char*name, char*index){
//     static FILE* file=NULL;
//     static int file_num=0;
//     IndexEntry res={0};

//     if(file==NULL){
//         printf(">>>%s",index);
//         file = fopen(index, "r");
//         printf("1111file_num:%d", file_num);
//     }
//     if(file){
//         fseek(file,0,SEEK_SET);
//         fread(file, &file_num, sizeof(file_num));
//         // printf("222file_num:%d", file_num);
//     }
//     printf("file_num:%d", file_num);

//     int left = 0, right = file_num - 1;
// int a =jiffies_msec();    
//     while (left <= right) {
//         int mid = left + (right - left) / 2;
//         int name_addr, name_addr_next;
//         fseek(file, 4+mid*4,SEEK_SET);
//         fread(file, &name_addr, sizeof(name_addr));
//         fread(file, &name_addr_next, sizeof(name_addr_next));
//         u8 len = name_addr_next - name_addr - 8;
//         fseek(file, 4+file_num*4 + name_addr, SEEK_SET);
//         u8* filename = malloc(len+1);
//         memset(filename,0,len+1);
//         fread(file, filename, len);    
//         int cmp = strcmp(filename, name);
//         free(filename);
//         if (cmp == 0) {
            
//             fread(file, &res, sizeof(IndexEntry));
//             int b =jiffies_msec();
//             // printf("filename :%s t:%d %x %d", name, b-a, res.offset, res.length);
//             return res;
//         } else if (cmp < 0) {
//             left = mid + 1;
//         } else {
//             right = mid - 1;
//         }
//     }

//     return res;
    

// }

    

// os_taskq_post_msg(PT_TASK_NAME, 1, PT_TASK_MSG_RUN);

// static void sd_jpg_task(void *p){
//             if (app_get_curr_task() != 4) {
//                 music_set_start_auto_play(1);
//                 app_task_switch_to(4);
//             } else {
//                 app_task_put_key_msg(134, 0);
//             }

//     initCache();
//     os_time_dly(2);
//     int msg[32];
//     int ret;
//     while(1){
//         ret = os_taskq_pend(NULL, msg, ARRAY_SIZE(msg));
//         if (ret != OS_TASKQ) {
//             continue;
//         }

//         if (msg[1]<0){
//             continue;
//         }

//         if(isCached(msg[1]) != -1){
//             continue; 
//         }
        
//         os_mutex_pend(&jpg_cache_MUTEX, 0);
//         // printf("id %d    name %s", msg[1], msg[2]);
//         addEntry(msg[1], msg[2]);
//         os_mutex_post(&jpg_cache_MUTEX);
//     }
// }



// int sd_jpg_test() {
//     os_mutex_create(&jpg_cache_MUTEX);
//     task_create(sd_jpg_task,NULL,"sd_jpg"); //启动索引表
//     return 0;
// }

#endif


#if 1   //LVGL截图

#endif//
#include "ui/ui_effect.h"
extern struct effect_ctrl ectl;
#define API_CUSTOM_SCA_LIMIT_W		(240)
#define API_SCA_LIMIT_W		(240)
static u32 sca_pixel_size(u32 format)
{
    const u8 bits[] = {32, 24, 16, 8, 16, 8, 8, 1, 24, 16, 0, 0};
    if (format > sizeof(bits)) {
        printf("sca format err %d\n", format);
        return 0;
    }

    return bits[format];
}




/**
 * @brief api_get_blk_sca_info:计算输入输出的缩放分块信息
 *
 *
 * @param sca:输出参数，由该函数内部初始化,必须静态或者全局
 * @param width:背景的宽和高，一般是全屏
 * @param height:背景的宽和高，一般是全屏
 * @param ratio_w:缩放比例，必须ratio_w == ratio_h
 * @param ratio_h:缩放比例，必须ratio_w == ratio_h
 * @param x_offset:居中缩放之后的水平偏移
 * @param y_offset:居中缩放之后的垂直偏移
 * @param limit_h:该值必须等于屏分块的高度
 * @param sca_img:输入图片的信息
 * @param status: 0:表示初始状态，会将图片分割成多个小图片，并计算输入分块信息，其他:表示只计算输出分块信息
 *
 * @return:返回初始化之后的sca句柄
 */
struct api_scale_info *api_get_blk_sca_info(struct api_scale_info *sca, int width, int height, float ratio_w, float ratio_h, int x_offset, int y_offset, int limit_h, struct api_ciner_img_info *sca_img, int status)
{
    sca->width = width;
    sca->height = height;
    sca->format = sca_img->format;
    sca->bytesperpixel = sca_pixel_size(sca_img->format) / 8;
    sca->backcolor = 0xffff;

    sca->src.left = 0;
    sca->src.top = 0;
    sca->src.width = sca_img->width;
    sca->src.height = sca_img->height;

    sca->dst.width = sca->src.width * ratio_w;
    sca->dst.height = sca->src.height * ratio_h;
    sca->dst.left = (width - sca->dst.width) / 2 + x_offset;
    sca->dst.top = (height - sca->dst.height) / 2 + y_offset;

    printf("dst_left %d, dst_top %d\n", sca->dst.left, sca->dst.top);

    sca->ratio_w = ratio_w;
    sca->ratio_h = ratio_h;

    if (sca->src.height <= 240) {
        printf("sca->src.height <= 240");
        limit_h = sca->src.height;
    }
    //最后一块的高度不能太小(例如1就太极端)，否则合成超时
    int res = sca->src.height - (sca->src.height / limit_h) * limit_h;
    float ratio_tmp = ratio_h * res;
    if (ratio_tmp && (ratio_tmp < 1)) {//微调
        printf("res too small %d\n", res);
        limit_h += 1;
    }

    printf("new_h %d, ratio %f\n", limit_h, ratio_h);

    int h_block_n = (sca->src.width + API_CUSTOM_SCA_LIMIT_W - 1) / API_CUSTOM_SCA_LIMIT_W;
    int v_block_n = (sca->src.height + limit_h - 1) / limit_h;
    int h, v;
    u8 block_index;
    int start;

    sca->h_block_n = h_block_n;
    sca->v_block_n = v_block_n;
    //status: 0:
    if (status == 0) {

        int kstart = jiffies_msec();

        sca->src_block = (struct api_src_block_info *)imb_malloc(h_block_n * v_block_n * sizeof(struct api_src_block_info), true);
        if (!sca->src_block) {
            return -1;
        }
        sca->dst_block = (struct rect *)imb_malloc(h_block_n * v_block_n * sizeof(struct rect), true);
        if (!sca->dst_block) {
            return -1;
        }

        int h_block_len = sca->src.width / h_block_n;
        int v_block_len = limit_h;

        img_set_input(DATA_SRC_SRAM, DATA_NOZIP, sca->src.width, sca->src.height, sca_img->format, NULL, psram_cache2nocache_addr(sca_img->img_buf));

        /* printf("%d, %d, %d, %d\n", h_block_n, v_block_n, h_block_len, v_block_len); */

        //计算源图片分块参数
        for (v = 0; v < v_block_n; v++) {
            for (h = 0; h < h_block_n; h++) {
                block_index = v * h_block_n + h;
                sca->src_block[block_index].rect.left = h * h_block_len;
                sca->src_block[block_index].rect.top = v * v_block_len;
                if (h == (h_block_n - 1)) {
                    sca->src_block[block_index].rect.width = sca->src.width - sca->src_block[block_index].rect.left;
                } else {
                    sca->src_block[block_index].rect.width = h_block_len;
                }
                if (v == (v_block_n - 1)) {
                    sca->src_block[block_index].rect.height = sca->src.height - sca->src_block[block_index].rect.top;
                } else {
                    sca->src_block[block_index].rect.height = v_block_len;
                }

                sca->src_block[block_index].buf_size = ((sca->src_block[block_index].rect.width * sca->bytesperpixel + 3) / 4 * 4) * sca->src_block[block_index].rect.height;
                sca->src_block[block_index].buf = (u8 *)br28_malloc_psram(sca->src_block[block_index].buf_size);

                /* printf("%d, %d, %d, %d, %d, %x\n", block_index, sca->src_block[block_index].rect.width, sca->src_block[block_index].rect.height, sca->bytesperpixel, sca->src_block[block_index].buf_size, (u32)sca->src_block[block_index].buf);	 */
                ASSERT(sca->src_block[block_index].buf, "src_block malloc %d fail, %d\n", sca->src_block[block_index].buf_size, block_index);

                flushinv_dcache(sca->src_block[block_index].buf, sca->src_block[block_index].buf_size);
                img_set_output(psram_cache2nocache_addr(sca->src_block[block_index].buf), sca->src_block[block_index].rect.left, sca->src_block[block_index].rect.top, sca->src_block[block_index].rect.width, sca->src_block[block_index].rect.height);
                img_kick_sync();

            }
        }

        printf("img_cut time : %d ms\n", jiffies_msec() - kstart);
    }


    //计算目标缩放分块参数
    int h_offset = 0, v_offset = 0;
    for (v = 0; v < v_block_n; v++) {
        for (h = 0; h < h_block_n; h++) {
            block_index = v * h_block_n + h;
            sca->dst_block[block_index].left = sca->dst.left + h_offset;
            sca->dst_block[block_index].top = sca->dst.top + v_offset;
            sca->dst_block[block_index].width = sca->src_block[block_index].rect.width * ratio_w;
            sca->dst_block[block_index].height = sca->src_block[block_index].rect.height * ratio_h;

            h_offset += sca->dst_block[block_index].width;

            /* printf("index %d, %d, %d, %d, %d\n", block_index, sca->dst_block[block_index].left, sca->dst_block[block_index].top, sca->dst_block[block_index].width, sca->dst_block[block_index].height); */

        }
        h_offset = 0;
        v_offset += sca->dst_block[block_index].height;
    }

    return sca;
}
/**
 * @brief api_get_blk_sca_info2:计算输入输出的缩放分块信息
 * 该函数与api_get_blk_sca_info()的区别是，根据不同的缩放
 * 比例调整不同的分块块数，目的的减轻移动过程中的抖动，但
 * 不同的分块块数会导致需要重复的申请和释放内存，因此一般
 * 是在连续移动时调用该函数，例如左右滑屏，在不移动时还是
 * 调用api_get_blk_sca_info()好
 *
 *
 * @param sca:输出参数，由该函数内部初始化,必须静态或者全局
 * @param width:背景的宽和高，一般是全屏
 * @param height:背景的宽和高，一般是全屏
 * @param ratio_w:缩放比例，必须ratio_w == ratio_h
 * @param ratio_h:缩放比例，必须ratio_w == ratio_h
 * @param x_offset:居中缩放之后的水平偏移
 * @param y_offset:居中缩放之后的垂直偏移
 * @param limit_h:该值必须等于屏分块的高度
 * @param sca_img:输入图片的信息
 * @param status: 0:表示初始状态，会将图片分割成多个小图片，并计算输入分块信息，其他:表示只计算输出分块信息
 *
 * @return:返回初始化之后的sca句柄
 */
struct api_scale_info *api_get_blk_sca_info2(struct api_scale_info *sca, int width, int height, float ratio_w, float ratio_h, int x_offset, int y_offset, int limit_h, struct api_ciner_img_info *sca_img, int status)
{
    sca->width = width;
    sca->height = height;
    sca->format = sca_img->format;
    sca->bytesperpixel = sca_pixel_size(sca_img->format) / 8;
    sca->backcolor = 0xffff;

    sca->src.left = 0;
    sca->src.top = 0;
    sca->src.width = sca_img->width;
    sca->src.height = sca_img->height;

    printf(">>>>>%d %d", sca->src.height, limit_h);

    if (sca->src.height <= 240) {
        limit_h = sca->src.height;
    }
    ASSERT(ratio_w == ratio_h);
    float ratio_tmp;
    int limit_h_tmp;
    int res;

    /* 计算输出分块高度对应的输入分块高度 */
    ratio_tmp = (float)limit_h / ratio_h;
    limit_h_tmp = (int)ratio_tmp;//取整

    printf("limit_h ratio_h limit_h_tmp %d %f %d",limit_h, ratio_h, limit_h_tmp);

    //最后一块的高度不能太小(例如1就太极端)，否则合成超时
    res = sca->src.height - (sca->src.height / limit_h_tmp) * limit_h_tmp;//最后一个分块的高度
    ratio_tmp = ratio_h * res;//最后一个分块缩放后的高度
    if (ratio_tmp && (ratio_tmp < 1)) {//微调
        printf("res too small %d\n", res);
        limit_h_tmp += 1;
    }

    ratio_h = (float)limit_h / (float)limit_h_tmp;
    ratio_w = ratio_h;
    limit_h = limit_h_tmp;

    printf("new_h %d, ratio_h %f\n", limit_h, ratio_h);

    sca->dst.width = sca->src.width * ratio_w;
    sca->dst.height = sca->src.height * ratio_h;
    sca->dst.left = (width - sca->dst.width) / 2 + x_offset;
    sca->dst.top = (height - sca->dst.height) / 2 + y_offset;

    printf("dst_left %d, dst_top %d\n", sca->dst.left, sca->dst.top);

    sca->ratio_w = ratio_w;
    sca->ratio_h = ratio_h;

    int h_block_n = (sca->src.width + API_SCA_LIMIT_W - 1) / API_SCA_LIMIT_W;//水平分块数量
    int v_block_n = (sca->src.height + limit_h - 1) / limit_h;//垂直分块数量
    int h, v;
    u8 block_index;
    int start;

    /* printf("v_block_n %d\n", v_block_n);	 */

    sca->h_block_n = h_block_n;
    sca->v_block_n = v_block_n;

    int h_block_len = sca->src.width / h_block_n;
    int v_block_len = limit_h;

    if (status == 0) {
        int kstart = jiffies_msec();

        img_set_input(DATA_SRC_SRAM, DATA_NOZIP, sca->src.width, sca->src.height, sca_img->format, NULL, psram_cache2nocache_addr(sca_img->img_buf));

        int cut_w, cut_left;
        for (h = 0; h < h_block_n; h++) {
            cut_left = h * h_block_len;
            if (h == (h_block_n - 1)) {
                cut_w = sca->src.width - cut_left;
            } else {
                cut_w = h_block_len;
            }
            sca->cut_buf_size[h] = ((cut_w * sca->bytesperpixel + 3) / 4 * 4) * sca->src.height;
            sca->cut_buf[h] = (u8 *)br28_malloc_psram(sca->cut_buf_size[h]);
            ASSERT(sca->cut_buf[h], "src_block malloc %d fail, %d\n", sca->cut_buf_size[h], h);

            flushinv_dcache(sca->cut_buf[h], sca->cut_buf_size[h]);
            img_set_output(psram_cache2nocache_addr(sca->cut_buf[h]), cut_left, 0, cut_w, sca->src.height);
            img_kick_sync();
        }

        printf("img_cut time : %d ms\n", jiffies_msec() - kstart);
    }


    if (sca->max_block_n < h_block_n * v_block_n) {
        if (sca->src_block) {
            imb_free(sca->src_block);
            sca->src_block = NULL;
        }
        if (sca->dst_block) {
            imb_free(sca->dst_block);
            sca->dst_block = NULL;
        }
        sca->max_block_n = h_block_n * v_block_n;
    }
    if (sca->src_block == NULL) {
        sca->src_block = (struct api_src_block_info *)imb_malloc(h_block_n * v_block_n * sizeof(struct api_src_block_info), true);
        if (!sca->src_block) {
            return -1;
        }
    }
    if (sca->dst_block == NULL) {
        sca->dst_block = (struct rect *)imb_malloc(h_block_n * v_block_n * sizeof(struct rect), true);
        if (!sca->dst_block) {
            return -1;
        }
    }

    /* printf("%d, %d, %d, %d\n", h_block_n, v_block_n, h_block_len, v_block_len); */


    int offset[4] = {0};
    //计算源图片分块参数
    for (v = 0; v < v_block_n; v++) {
        for (h = 0; h < h_block_n; h++) {
            block_index = v * h_block_n + h;
            sca->src_block[block_index].rect.left = h * h_block_len;
            sca->src_block[block_index].rect.top = v * v_block_len;
            if (h == (h_block_n - 1)) {
                sca->src_block[block_index].rect.width = sca->src.width - sca->src_block[block_index].rect.left;
            } else {
                sca->src_block[block_index].rect.width = h_block_len;
            }
            if (v == (v_block_n - 1)) {
                sca->src_block[block_index].rect.height = sca->src.height - sca->src_block[block_index].rect.top;
            } else {
                sca->src_block[block_index].rect.height = v_block_len;
            }

            sca->src_block[block_index].buf_size = ((sca->src_block[block_index].rect.width * sca->bytesperpixel + 3) / 4 * 4) * sca->src_block[block_index].rect.height;
            sca->src_block[block_index].buf = sca->cut_buf[h] + offset[h];

            ASSERT(((u32)sca->src_block[block_index].buf + sca->src_block[block_index].buf_size) <= ((u32)sca->cut_buf[h] + sca->cut_buf_size[h]), "src_small_block malloc %d fail, %d, %x, %x, %x\n", sca->src_block[block_index].buf_size, block_index, (u32)sca->src_block[block_index].buf, (u32)sca->cut_buf[h], sca->cut_buf_size[h]);
            offset[h] += sca->src_block[block_index].buf_size;
        }
    }


    //计算目标缩放分块参数
    int h_offset = 0, v_offset = 0;
    for (v = 0; v < v_block_n; v++) {
        for (h = 0; h < h_block_n; h++) {
            block_index = v * h_block_n + h;
            sca->dst_block[block_index].left = sca->dst.left + h_offset;
            sca->dst_block[block_index].top = sca->dst.top + v_offset;
            sca->dst_block[block_index].width = sca->src_block[block_index].rect.width * ratio_w;
            sca->dst_block[block_index].height = sca->src_block[block_index].rect.height * ratio_h;

            h_offset += sca->dst_block[block_index].width;
        }
        h_offset = 0;
        v_offset += sca->dst_block[block_index].height;
    }

    return sca;
}
void api_free_blk_sca_info2(struct api_scale_info *sca)
{
    int h, v;
    u8 block_index;
    int h_block_n = sca->h_block_n;
    int v_block_n = sca->v_block_n;

    if (sca->src_block == NULL) {
        return;
    }

    for (h = 0; h < h_block_n; h++) {
        if (sca->cut_buf[h]) {
            br28_free_psram(sca->cut_buf[h]);
            sca->cut_buf[h] = NULL;
        }
    }

    if (sca->src_block) {
        imb_free(sca->src_block);
        sca->src_block = NULL;
    }
    if (sca->dst_block) {
        imb_free(sca->dst_block);
        sca->dst_block = NULL;
    }
    sca->max_block_n = 0;
}

void api_free_blk_sca_info(struct api_scale_info *sca)
{
    int h, v;
    u8 block_index;
    int h_block_n = sca->h_block_n;
    int v_block_n = sca->v_block_n;

    if (sca->src_block == NULL) {
        return;
    }

    for (v = 0; v < v_block_n; v++) {
        for (h = 0; h < h_block_n; h++) {
            block_index = v * h_block_n + h;
            if (sca->src_block[block_index].buf) {
                br28_free_psram(sca->src_block[block_index].buf);
                sca->src_block[block_index].buf = NULL;
            }
        }
    }

    if (sca->src_block) {
        imb_free(sca->src_block);
        sca->src_block = NULL;
    }
    if (sca->dst_block) {
        imb_free(sca->dst_block);
        sca->dst_block = NULL;
    }
}

/**
 * @brief api_blk_sca : 处理分块缩放的合成函数
 *
 * @param scale[]:分块图片的数组，一个数组代表一张大图片的分块信息
 * @param page_num:图片数组的个数
 * @param base_img:底图,可以为NULL
 * @param sw_buf:NULL表示合成完联动推屏直接显示，否则其他psram的DMA地址值
 *
 * @return:0成功 其他失败
 */
int api_blk_sca(struct api_scale_info *scale[], int page_num, struct api_ciner_img_info *base_img, u8 *sw_buf)
{
    int ret;
    int i;
    int h, v;
    u8 block_index;
    struct rect cache_rect;
    struct rect screen_rect;//屏幕有效显示区域
    struct image_file tmp_file = {0};
    struct imb_task_head *new_root = imb_task_head_get(0);
    struct api_scale_info *sca = NULL;

    if ((scale == NULL) || (page_num <= 0)) {
        return -1;
    }

    new_root->ring_buf[0] = NULL;
    new_root->ring_buf[1] = NULL;
    for (i = 0; i < RING_MAX_TASK; i++) {
        if (new_root->task_tab[i]) {
            new_root->task_tab[i] = NULL;
        }
    }

    if (sw_buf) {
        new_root->copy_to_psram = 3;
    } else {
        new_root->copy_to_psram = 0;
    }
    new_root->state = STATE_SYNTHESIS_AND_DRAW;
    new_root->new_copy = 0;

    //创建背景任务(必须)
    imb_create_bg_task(new_root->format, new_root->screen_width, new_root->screen_height, 0x0);

    if (base_img) {
        tmp_file.width = base_img->width;
        tmp_file.height = base_img->height;
        tmp_file.format = base_img->format;
        // imb_create_image_task(imb_task_get_id(), &tmp_file, base_img->img_buf, 0, 0, base_img->width, base_img->height, NULL, false, LOAD_FROM_STATIC_RAM);
    }

    i = 0;
    do {
        sca = scale[i];

        for (v = 0; v < sca->v_block_n; v++) {
            for (h = 0; h < sca->h_block_n; h++) {
                block_index = v * sca->h_block_n + h;
                tmp_file.width = sca->src_block[block_index].rect.width;
                tmp_file.height = sca->src_block[block_index].rect.height;
                tmp_file.format = sca->format;
                imb_create_image_scale_task(imb_task_get_id(), &tmp_file, psram_cache2nocache_addr(sca->src_block[block_index].buf), sca->ratio_w, sca->ratio_h, sca->dst_block[block_index].left, sca->dst_block[block_index].top, sca->dst_block[block_index].width, sca->dst_block[block_index].height, NULL, false, LOAD_FROM_STATIC_RAM);
            }
        }

        i++;
    } while (--page_num);

    printf("start meld\n");
    screen_rect.left = 0;
    screen_rect.top = 0;
    screen_rect.width = new_root->screen_width;
    screen_rect.height = new_root->screen_height;

    /* imb_task_info_dump(new_root); */

    /* lcd_wait(); */
    if (sw_buf) {
        lcd_wait();
        ectl.ps_obuf = sw_buf;
    }
    
// imb_set_output_cb(imb_data_output, imb_data_output_wait_finish);
    // imb_task_head_set_buf(imb_task_head_get(0), lcd_info.buffer, lcd_info.buffer_size, lcd_info.width, lcd_info.height, lcd_info.stride, lines, lcd_info.buf_num);
    // imb_task_head_config(imb_task_head_get(0), &api_rect, &api_screen_rect, &api_screen_rect, &api_page_draw, STATE_SYNTHESIS_AND_DRAW);


    imb_start(new_root, &screen_rect, cache_rect, new_root->screen_width, new_root->lines, NULL);

    new_root->copy_to_psram = 0;

    if (sw_buf) {
        int wait = 0x20;//推单独的一屏
        lcd_draw_area(0, ectl.sca_obuf, 0, 0, new_root->screen_width, new_root->screen_height, wait);//推屏
        ectl.ps_obuf = NULL;
        ectl.sca_obuf = NULL;
    }

    imb_task_all_destroy(new_root);



    return 0;
}
#include "lvgl.h"


static struct api_scale_info *sca[2] = {0};

//  剪切当前页面到PSRAM ，最多是g_sca_hdl大小
int cut_now_page_in_psram(u8 i){
    if(!PSRAM_FULL_SCREEN){
        return -1;
    }
    if (i>ARRAY_SIZE(g_sca_hdl)){
        printf("g_sca_hdl i error %d", i);
        return -1;
    }

    api_free_blk_sca_info2(&g_sca_hdl[i]);

    struct api_scale_info  *sca = &g_sca_hdl[i];
    struct api_ciner_img_info _sca_img = {0};
    _sca_img.width   = 454;
    _sca_img.height  = 454;
    _sca_img.format  = LAYER_FORMAT_RGB565;
    _sca_img.img_buf = psram_act;//pic->data;
    struct api_ciner_img_info *sca_img = &_sca_img;
      int limit_h = 91;  

    api_get_blk_sca_info2(sca, 454,454,1.0,1.0,0,0,91,sca_img, 0);

}

#define RES_BASE_ADDR   0x600000   //自定义区起始地址

//  这里只做一个自定义分区打开关闭，需要同时使用更多分区自行用另外的方法管理
static void *fd = 0;
void open_fd(char*name){
    if(fd){
        dev_close(fd);
        fd = NULL;
    }
    if(!fd){
        fd = dev_open(name, NULL);
    }
}
void* get_res_fd(){
    return fd;
}
void close_fd(){
    if(fd){
        dev_close(fd);
        fd = NULL;
    }
}

//  SD卡直接访问图片资源有两种方式
//  1.预先拷贝RAM内存
//  2.预先拷贝到内部flash
//  3.预先拷贝到PSRAM



void lv_close_res(lv_img_dsc_t*img_dst);
//  分区句柄，分区所在的物理地址，bin文件在分区的偏移，图片在bin文件中的地址长度，
void lv_open_res(void *fd, int phyaddr, int offset, struct FileIndex res, lv_img_dsc_t*img_dst){
    if(!fd){
        return;
    }
    lv_close_res(img_dst);

    u8 test[16];
    dev_bulk_read(fd, test, 0, 16);
    printf("BEGIN 16");
    put_buf(test, 16);

    

    printf("file addr:%x", offset + res.addr);
    dev_bulk_read(fd, &(img_dst->header), offset + res.addr, sizeof(lv_img_header_t));

    lv_img_header_t tp;
    dev_bulk_read(fd, &(tp), offset + res.addr, sizeof(lv_img_header_t));
    put_buf(&tp, sizeof(lv_img_header_t));

#if TCFG_VIRFAT_INSERT_FLASH_ENABLE //内置FLASH资源
    int cpuaddr = sdfile_flash_addr2cpu_addr(phyaddr);
#else   //外挂FLASH资源
    int cpuaddr = 0x4000000 + phyaddr;
#endif

    img_dst->data = cpuaddr + offset + res.addr + sizeof(lv_img_header_t);
    img_dst->data_size = res.len - sizeof(lv_img_header_t);;
    printf("zero %d, cf %d, h %d, re %d, w %d, addr %x, size %d",
        img_dst->header.always_zero,
        img_dst->header.cf,
        img_dst->header.h,
        img_dst->header.reserved,
        img_dst->header.w,
        img_dst->data,
        img_dst->data_size
    );
    if(img_dst->header.reserved == 0x1 && 1){    //把资源copy到RAM
        img_dst->data = malloc(res.len);
        if(img_dst->data == NULL){
            printf("malloc fail %d", res.len);
            return;
        }
        printf("malloc  %d", res.len);
        dev_bulk_read(fd, img_dst->data, offset + res.addr + 4, res.len);
        img_dst->header.reserved |= 0x2;
    }
}

void lv_close_res(lv_img_dsc_t*img_dst){
    if((img_dst->header.reserved&0x2)){    //copy到RAM释放
        if(img_dst->data){
            free(img_dst->data);
            img_dst->data == NULL;
        }
    }
    memset(img_dst, 0, sizeof(img_dst));
}
static void get_sys_time(struct sys_time *time)
{
    void *fd = dev_open("rtc", NULL);
    if (!fd) {
        // get_elapse_time(time);
        return;
    }
    dev_ioctl(fd, IOCTL_GET_SYS_TIME, (u32)time);
    /* log_info("get_sys_time : %d-%d-%d,%d:%d:%d\n", time->year, time->month, time->day, time->hour, time->min, time->sec); */
    dev_close(fd);
}
static lv_img_dsc_t ui_test;

static lv_obj_t * ui_sec;
static lv_obj_t * ui_min;
static lv_obj_t * ui_hour;

// void test_timer_cb11(lv_timer_t * timer){
    //     lv_obj_t * img_obj = timer->user_data;
    //     if(_lv_area_is_on(&img_obj->coords, &lv_scr_act()->coords)==false){
        //         return;
    //     }

    //     static int cnt = FILE_1199_jpg;
    //     if(cnt>=FILE_preview){
        //         cnt = FILE_1199_jpg;
    //     }

    //     if(cnt<=FILE_1204_jpg){
        //         lv_obj_set_size(img_obj, 277, 277);
    //     }else{
        //         lv_obj_set_size(img_obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    //     }

    //     lv_open_res(get_res_fd(), RES_BASE_ADDR, 0, FILE_index[cnt++], &ui_test);
    //     lv_img_set_src(img_obj, &ui_test);
    

    //     struct sys_time time;

    //     get_sys_time(&time);

    //     // int angle= jiffies_msec()*60/1000;
    //     lv_img_set_angle(ui_sec, time.sec*60%3600 );
    //     lv_img_set_angle(ui_min, time.min*60%3600 );
    //     lv_img_set_angle(ui_hour, time.hour*150%3600 );
    
    //     // lv_obj_invalidate(lv_scr_act());
// }

void ui_event____initial_actions1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%d", event_code);
    
}

static void event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_current_target(e);
    LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
}

// void lv_example_msgbox_1(void)
// {
//     static const char * btns[] = {"Apply", "Close", ""};

//     lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Hello", "This is a message box with two buttons.", btns, true);
//     lv_obj_add_event_cb(mbox1, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
//     lv_obj_center(mbox1);
// }


static void value_changed_event_cb(lv_event_t * e);

// void lv_example_arc_1(lv_obj_t * obj)
// {
//     lv_obj_t * label = lv_label_create(obj);

//     /*Create an Arc*/
//     lv_obj_t * arc = lv_arc_create(obj);
//     lv_obj_set_size(arc, 300, 300);
//     lv_arc_set_rotation(arc, 135);
//     lv_arc_set_bg_angles(arc, 0, 270);
//     lv_arc_set_value(arc, 10);
//     lv_obj_center(arc);
//     lv_obj_add_event_cb(arc, value_changed_event_cb, LV_EVENT_VALUE_CHANGED, label);

//     /*Manually update the label for the first time*/
//     lv_event_send(arc, LV_EVENT_VALUE_CHANGED, NULL);
// }

static void value_changed_event_cb(lv_event_t * e)
{
    lv_obj_t * arc = lv_event_get_target(e);
    lv_obj_t * label = lv_event_get_user_data(e);

    lv_label_set_text_fmt(label, "%d%%", lv_arc_get_value(arc));

    /*Rotate the label to the current position of the arc*/
    lv_arc_rotate_obj_to_angle(arc, label, 25);
}

static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

// void lv_example_keyboard_1(lv_obj_t * obj)
// {
//     /*Create a keyboard to use it with an of the text areas*/
//     lv_obj_t * kb = lv_keyboard_create(obj);

//     /*Create a text area. The keyboard will write here*/
//     lv_obj_t * ta;
//     ta = lv_textarea_create(obj);
//     lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, 10);
//     lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
//     lv_textarea_set_placeholder_text(ta, "Hello");
//     lv_obj_set_size(ta, 140, 80);

//     ta = lv_textarea_create(obj);
//     lv_obj_align(ta, LV_ALIGN_TOP_RIGHT, -10, 10);
//     lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
//     lv_obj_set_size(ta, 140, 80);

//     lv_keyboard_set_textarea(kb, ta);
// }


// void scroll_effect(lv_event_t* e) {
    //     static uint8_t index = 0;
    //     lv_event_code_t code = lv_event_get_code(e);
    //     lv_obj_t* control = lv_event_get_target(e);

    //     if (code == LV_EVENT_SCROLL) {

        //         //printf("LV_EVENT_SCROLL=%d", index);
        //         lv_area_t control_area;
        //         lv_obj_get_coords(control, &control_area);
        //         lv_coord_t control_center = control_area.x1 + LV_HOR_RES / 4;

        //         for (uint32_t i = 0; i < lv_obj_get_child_cnt(control); i++) {
            //             lv_obj_t* item = lv_obj_get_child(control, i);
            //             lv_area_t item_area;
            //             lv_obj_get_coords(item, &item_area);
            //             lv_coord_t item_center = item_area.x1 + lv_area_get_width(&item_area) / 2;
            //             lv_coord_t diff_x = item_area.x1 - control_area.x1;
            //             lv_coord_t zoom = lv_map(LV_ABS(diff_x), 0, LV_HOR_RES, 256, 16);
            //             lv_img_set_zoom(item, zoom);



        //         }
//     }
// }
// static lv_obj_t * kuangkuang;
// static lv_img_dsc_t * snapshot;
// static lv_obj_t * img;
// static void test_cb(lv_timer_t * t){
  //   lv_obj_t * obj = t->user_data;
    //     static u8 cnt = 7;
    //     static char name[20] = {0};
    //     memset(name, 0, 20);
    //     sprintf(name, "%d", cnt);
    //     printf("name :%s",name);
    //     cnt++;
    //     if(cnt>45)cnt = 7;
    //     lv_img_set_src(img, name);
    //     jl_lv_snapshot_take_to_buf(kuangkuang, LV_IMG_CF_TRUE_COLOR, snapshot, snapshot->data, 454*454*2);


// }
// void lv_zh_(void)
// {
//     // void *p = malloc_psram(454*454*2);
    //     // memset(p, 0x11, 454*454*2);


        //         // lv_obj_t * img = lv_img_create(NULL);
        //         // lv_obj_set_size(img, 398, 398);
        //         // lv_img_set_src(img, A_SMARTWEAR_UI_BG3);

    //     lv_obj_t * panel = lv_obj_create(lv_scr_act());
    //     lv_obj_remove_style_all(panel);
    //     lv_obj_set_size(panel, 454, 454);
    //     lv_obj_set_scroll_snap_x(panel, LV_SCROLL_SNAP_CENTER);
    //     lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
    //     lv_obj_align(panel, LV_ALIGN_CENTER, 0, 0);
    //     lv_obj_set_scroll_dir(panel, LV_DIR_HOR);
    //     lv_obj_set_scrollbar_mode(panel, LV_SCROLLBAR_MODE_OFF);
    //     lv_obj_set_style_bg_color(lv_scr_act(), lv_palette_main(LV_PALETTE_NONE), 0);//黑色
    //     // lv_obj_set_style_bg_color(panel, lv_palette_main(LV_PALETTE_BLUE), 0);
    //     // lv_obj_set_style_bg_opa(panel, LV_OPA_100, 0);
    //     //lv_obj_remove_style(panel, 0, LV_STATE_ANY);




    //     uint32_t i;
    //     for(i = 0; i < 2; i++) {

        //         printf("i>>>>>   %d",i);

        //         lv_obj_t* zh_obj = lv_img_create(panel);
        //         // lv_obj_set_style_bg_color(zh_obj, lv_palette_main(LV_PALETTE_PURPLE), 0);
        //         lv_obj_set_style_bg_opa(zh_obj, LV_OPA_TRANSP, 0);//    设置透明，减少多余的色层合成
        //         //lv_image_set_zoom(zh_obj, 128);

        //         //  截图区域必须要2像素对齐
        //         kuangkuang = lv_obj_create(NULL);
        //         lv_obj_set_size(kuangkuang, 454, 454);
        //         img = lv_img_create(kuangkuang);
        //         // lv_obj_set_size(img, 398, 398);
        //         // lv_img_set_src(img, A_SMARTWEAR_UI_BIRD_1);
        //         lv_obj_set_align(img, LV_ALIGN_CENTER);

        //         if(zh_obj) {
            //             snapshot = (void *)lv_img_get_src(zh_obj);
            //             if(snapshot) {
                //                 jl_lv_snapshot_free(snapshot);
            //             }

            //             /*Update the snapshot, we know parent of object is the container.*/
            //             snapshot = jl_lv_snapshot_take(kuangkuang, LV_IMG_CF_TRUE_COLOR);
            //             if(snapshot == NULL)
                //                 break;
            //             lv_img_set_src(zh_obj, snapshot);
        //         }


    //     }
//     lv_obj_update_snap(panel, LV_ANIM_ON);
    //     lv_obj_add_event_cb(panel, scroll_effect, LV_EVENT_SCROLL, 0);
    //     lv_obj_add_event_cb(panel, scroll_effect, LV_EVENT_READY, 0);
    //     lv_obj_add_flag(panel, LV_OBJ_FLAG_SCROLL_ONE);


    //     lv_timer_create(test_cb, 20, NULL);
// }

// static void snap_event_cb(lv_event_t * e)
// {
//     lv_obj_t * snapshot_obj = lv_event_get_user_data(e);
    //     lv_obj_t * img = lv_event_get_target(e);

    //     if(snapshot_obj) {
        //         lv_img_dsc_t * snapshot = (void *)lv_img_get_src(snapshot_obj);
        //         if(snapshot) {
            //             jl_lv_snapshot_free(snapshot);
        //         }

        //         /*Update the snapshot, we know parent of object is the container.*/
        //         snapshot = jl_lv_snapshot_take(img->parent, LV_IMG_CF_TRUE_COLOR);
        //         if(snapshot == NULL)
            //             return;
        //         lv_img_set_src(snapshot_obj, snapshot);
    //     }
// }

// void lv_example_snapshot_1(void)
// {
//     // LV_IMG_DECLARE(img_star);
    //     lv_obj_t * root = NULL;
    //     // lv_obj_set_style_bg_color(root, lv_palette_main(LV_PALETTE_LIGHT_BLUE), 0);

    //     /*Create an image object to show snapshot*/
    //     lv_obj_t * snapshot_obj = lv_img_create(lv_scr_act());
    //     lv_obj_set_style_bg_color(snapshot_obj, lv_palette_main(LV_PALETTE_PURPLE), 0);
    //     lv_obj_set_style_bg_opa(snapshot_obj, LV_OPA_100, 0);
    //     lv_img_set_zoom(snapshot_obj, 128);
    //     // lv_img_set_angle(snapshot_obj, 300);
    //     lv_obj_set_align(snapshot_obj, LV_ALIGN_CENTER);
    //     lv_obj_set_x(snapshot_obj, 0);
    //     lv_obj_set_y(snapshot_obj, 0);
    //     //     lv_obj_set_style_transform_pivot_x(snapshot_obj, 0, 0);
    //     // lv_obj_set_style_transform_pivot_y(snapshot_obj, 0, 0);

    //     /*Create the container and its children*/
    //     lv_obj_t * container = lv_obj_create(root);

    //     lv_obj_center(container);
    //     lv_obj_set_size(container, 454, 454);
    //     lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW_WRAP);
    //     lv_obj_set_flex_align(container, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //     lv_obj_set_style_radius(container, 50, 0);
    //     lv_obj_t * img;
    //     int i;
    //     // for(i = 0; i < 4; i++) {
        //         img = lv_img_create(container);
        //         lv_obj_set_size(img, 398, 398);
        //         // lv_img_set_src(img, A_SMARTWEAR_UI_BG3);
        //         lv_obj_set_style_bg_color(img, lv_color_black(), 0);
        //         lv_obj_set_style_bg_opa(img, LV_OPA_COVER, 0);
        //         lv_obj_set_style_transform_zoom(img, 256, LV_STATE_PRESSED);
        //         lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
        //         lv_obj_add_event_cb(img, snap_event_cb, LV_EVENT_PRESSED, snapshot_obj);
        //         lv_obj_add_event_cb(img, snap_event_cb, LV_EVENT_RELEASED, snapshot_obj);
    //     // }

    //     //     lv_obj_t * snapshot_obj = lv_event_get_user_data(e);
    //     // lv_obj_t * img = lv_event_get_target(e);

    //     if(snapshot_obj) {
        //         lv_img_dsc_t * snapshot = (void *)lv_img_get_src(snapshot_obj);
        //         if(snapshot) {
            //             jl_lv_snapshot_free(snapshot);
        //         }

        //         /*Update the snapshot, we know parent of object is the container.*/
        //         snapshot = jl_lv_snapshot_take(img, LV_IMG_CF_TRUE_COLOR);
        //         if(snapshot == NULL)
            //             return;
        //         lv_img_set_src(snapshot_obj, snapshot);
    //     }

    //     lv_timer_create(test_cb, 10, img);
// }

// void lv_example_tileview_1(void)
// {
//     lv_zh_();
//     // lv_example_snapshot_1();
//     return;

//     // lv_example_msgbox_1();
//     open_fd("usr_nor");

//     lv_obj_t * tv = lv_tileview_create(lv_scr_act());
//     // lv_obj_set_style_bg_color(tv, lv_color_hex(0x0), LV_PART_MAIN | LV_STATE_DEFAULT);

//     lv_obj_t * tilep = lv_tileview_add_tile(tv, 2, 1, LV_DIR_ALL);


//     lv_example_arc_1(tilep);

//     lv_obj_t * tile0 = lv_tileview_add_tile(tv, 1, 2, LV_DIR_ALL);
//     lv_example_keyboard_1(tile0);

//     lv_obj_t * tiles = lv_tileview_add_tile(tv, 0, 1, LV_DIR_ALL);


//     /*Tile1: just a label*/
//     lv_obj_t * tile1 = lv_tileview_add_tile(tv, 1, 1, LV_DIR_ALL);
//     // lv_obj_t *img_obj = lv_img_create(tile1);
//     // lv_obj_add_event_cb(tile1, ui_event____initial_actions1, LV_EVENT_ALL, NULL);
    
//     lv_open_res(get_res_fd(), RES_BASE_ADDR, 0, FILE_index[FILE_RGB565_1_dat], &ui_test);
//     // put_buf(ui_test.data, 16);
//     lv_obj_t *img_obj = lv_img_create(tile1);
//     lv_img_set_src(img_obj, &ui_test);
//     // lv_obj_set_size(img_obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
//     lv_obj_set_align(img_obj, LV_ALIGN_CENTER);
//     lv_timer_create(test_timer_cb11, 20, img_obj); // 每1000毫秒（1秒）触发一次
//     lv_obj_t * label2 = lv_label_create(img_obj);
//     lv_label_set_text(label2, "FILE_RGB565_1_dat");
//     lv_obj_center(label2);

// //     /*Tile2: a button*/
//     lv_obj_t * tile2 = lv_tileview_add_tile(tv, 1, 0, LV_DIR_ALL);

//     lv_obj_t * btn = lv_btn_create(tile2);

//     lv_obj_t * label = lv_label_create(btn);
//     lv_label_set_text(label, "Scroll up or right");

//     lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
//     lv_obj_center(btn);

//     /*Tile3: a list*/
//     lv_obj_t * tile3 = lv_tileview_add_tile(tv, 1, 1, LV_DIR_ALL);

    
// //     lv_obj_t * tile4 = lv_tileview_add_tile(tv, 1, 0, LV_DIR_ALL);
// //     lv_obj_t * img4 = lv_img_create(tile4);
// //     lv_img_set_src(img4, "A:bgjpg2.jpg");
// //     lv_obj_set_size(img4, 240, 272);

// //     lv_obj_t * tile5 = lv_tileview_add_tile(tv, 2, 0, LV_DIR_ALL);
// //      img5 = lv_img_create(tile5);
// //     lv_img_set_src(img5, "B:6");//bird_2.png
// //     lv_obj_set_size(img5, 454, 454);

// //     tile6 = lv_tileview_add_tile(tv, 2, 1, LV_DIR_ALL);
// //     lv_obj_t * img6 = lv_img_create(tile6);
// //     lv_img_set_src(img6, "G:storage/sd0/C/animal.bin");
// //     lv_obj_set_size(img6, 454, 454);

// #define LV_IMG_DECLARE_JL(var_name) extern volatile lv_img_dsc_t var_name;
// LV_IMG_DECLARE_JL(ui_img_clockwise_sec_png);    // assets\bg1.png
// LV_IMG_DECLARE_JL(ui_img_clockwise_min_png);    // assets\flash.png
// LV_IMG_DECLARE_JL(ui_img_clockwise_hour_png);    // assets\weather_sun_cloud.png//     lv_timer_create(test_timer_cb, 1, img6);

//     lv_open_res(get_res_fd(), RES_BASE_ADDR, 0, FILE_index[FILE_ARGB8565_clockwise_sec_dat], &ui_img_clockwise_sec_png);
//     lv_open_res(get_res_fd(), RES_BASE_ADDR, 0, FILE_index[FILE_ARGB8565_clockwise_min_dat], &ui_img_clockwise_min_png);
//     lv_open_res(get_res_fd(), RES_BASE_ADDR, 0, FILE_index[FILE_ARGB8565_clockwise_hour_dat], &ui_img_clockwise_hour_png);

//     ui_sec = lv_img_create(tile3);
//     lv_img_set_src(ui_sec, &ui_img_clockwise_sec_png);
//     lv_obj_set_width(ui_sec, LV_SIZE_CONTENT);   /// 1
//     lv_obj_set_height(ui_sec, LV_SIZE_CONTENT);    /// 1
//     lv_obj_set_x(ui_sec, 0);
//     lv_obj_set_y(ui_sec, -67);
//     lv_obj_set_align(ui_sec, LV_ALIGN_CENTER);
//     lv_obj_add_flag(ui_sec, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
//     lv_obj_clear_flag(ui_sec, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//     lv_img_set_pivot(ui_sec, 15, 155);
//     lv_img_set_angle(ui_sec, 12000);
//     // sec_Animation(ui_sec, 0);

//    ui_min = lv_img_create(tile3);
//     lv_img_set_src(ui_min, &ui_img_clockwise_min_png);
//     lv_obj_set_width(ui_min, LV_SIZE_CONTENT);   /// 1
//     lv_obj_set_height(ui_min, LV_SIZE_CONTENT);    /// 1
//     lv_obj_set_x(ui_min, 0);
//     lv_obj_set_y(ui_min, -75);
//     lv_obj_set_align(ui_min, LV_ALIGN_CENTER);
//     lv_obj_add_flag(ui_min, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
//     lv_obj_clear_flag(ui_min, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//     lv_img_set_pivot(ui_min, 9, 153);

//     ui_hour = lv_img_create(tile3);
//     lv_img_set_src(ui_hour, &ui_img_clockwise_hour_png);
//     lv_obj_set_width(ui_hour, LV_SIZE_CONTENT);   /// 1
//     lv_obj_set_height(ui_hour, LV_SIZE_CONTENT);    /// 1
//     lv_obj_set_x(ui_hour, 0);
//     lv_obj_set_y(ui_hour, -45);
//     lv_obj_set_align(ui_hour, LV_ALIGN_CENTER);
//     lv_obj_add_flag(ui_hour, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
//     lv_obj_clear_flag(ui_hour, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//     lv_img_set_pivot(ui_hour, 9, 93);

// //     lv_obj_t * tile7 = lv_tileview_add_tile(tv, 3, 0, LV_DIR_ALL);
// //     lv_obj_t *img7 = lv_img_create(tile7);
// //     lv_img_set_src(img7, "C:6.png");
// //     lv_obj_set_size(img7, 176, 220);

// //     lv_obj_t * tile8 = lv_tileview_add_tile(tv, 3, 1, LV_DIR_ALL);
// //     lv_obj_t *img8 = lv_img_create(tile8);
// // // #define 4_150_PNG			"0"
// // // #define 5_PNG			"1"
// // // #define 5_150_PNG			"2"
// // // #define 6_PNG			"3"
// // #define AQ_PNG			"4"
// // #define CHICKEN_1_PNG			"5"
// //     lv_img_set_src(img8, "D:"CHICKEN_1_PNG);
// //     lv_obj_set_size(img8, 750, 750);
// }




//  把JPG存到内部FLASH，测试文件是temp.jpg
void save_jpg_to_flash(void);
//  退出页面调用这个释放jpg内存
void free_dial_ui_draw_custom();
//  自定义绘JPG图，自动申请buf,放在布局POST事件即可
void dial_ui_draw_custom(void *_dc, int x, int y, int width, int height, u8 *name);



struct jpeg_decfile_info {
    u8 *jpg_stream;
    int jpg_file_len;
};
static struct jpeg_decfile_info testinfo;
static u8 *pic_buf=NULL;
static int run_jpg_time = 0;
static u8 *jpg_dec_stream_input(void *__fat_info, u32 *len, u32 offset_4k)
{
    struct jpeg_decfile_info *info = (struct jpeg_decfile_info *)__fat_info;
    u8 *jpg_stream = info->jpg_stream;
    int file_len = info->jpg_file_len;
    u32 offset = offset_4k * 4096;
    u32 res_len;

    if (offset >= file_len) {
        *len = 0;
        return NULL;
    }
    res_len = file_len - offset;
    *len = (res_len > 4096) ? 4096 : res_len;

    return jpg_stream + offset;
}
//  保存到内部flash测试
#define SD_TEST     1//SD卡图片测试，摄像头存flash需要关闭


void save_jpg_to_flash(void)
{
#if SD_TEST
    //从SD拿数据JPG到BUF
    char fname[100];
    FILE *fp;

    static int cnt = 400;
    sprintf(fname, "storage/sd0/C/output/o_%04d.jpg", cnt++);

    fp = fopen(fname, "r");
    if(!fp){
        printf("SD没有这个文件：%s", fname);
        return;
    }

    //  把SD卡读到BUF
    static struct jpeg_decfile_info info;
    int len = flen(fp);
    void *pp = malloc(len);
    fread(fp, pp, len);
    fclose(fp);
    fp = NULL;
#endif

    //JPG缓存写入FLASH
    // pp   JPG缓存地址
    // len  JPG长度

    //  把BUF存到FLASH
    fp =fopen("storage/virfat_flash/C/temp.jpg", "wb+");
    if (fp == NULL) {
        printf("[error]>>>>>>>NO FLASH");
        return ;
    }
    fwrite(fp, pp, len); 
    fclose(fp);
    fp = NULL;


#if SD_TEST
    free(pp);
    
#endif
}



// static void dial_ui_custom_draw_cb(int id, u8 *dst_buf, struct rect *dst_r, struct rect *src_r, u8 bytes_per_pixel, void *priv)
// {
// //buf区域   图片绝对地址

//     // printf("%s id %d dst %x dstltwh %d %d %d %d srcltwh %d %d %d %d pix %d p %d", __func__,
//     //     id, 
//     //     dst_buf, 
//     //     dst_r->left, dst_r->top, dst_r->height, dst_r->width, 
//     //     src_r->left, src_r->top, src_r->height, src_r->width,  
//     //     bytes_per_pixel, 
//     //     priv);
    
//     int h;
//     struct rect r;
//     struct lbuf_test_head *rbuf = NULL;
//     int dst_stride = (dst_r->width * bytes_per_pixel + 3) / 4 * 4;
//     int src_stride = (src_r->width * bytes_per_pixel + 3) / 4 * 4;
//     static u8 time = 0;
//     u8 rgb_format = 1;//1 :rgb_565 0:rgb_888

//     static struct rect draw;
//     // static struct jpeg_decfile_info info;
//     static struct rect draw_rect;
//     static struct rect jpeg_rect;
//     static struct rect cur_draw;
//     static struct jpeg_api_out_lines out = {0};
    
//     static struct jpeg_decoder_fd *jpg_fd;

//     if (1) {

//         if (run_jpg_time == 0) {
//             run_jpg_time = 1;
//         }

//         if (run_jpg_time > 0) {
//             /* printf("dst [%d, %d, %d, %d],  src [%d, %d, %d, %d]\n", dst_r->left, dst_r->top, dst_r->width, dst_r->height, src_r->left, src_r->top, src_r->width, src_r->height); */
// #if USE_JPG_DEMO
//             cur_draw.left = dst_r->left;
//             cur_draw.top = dst_r->top;
//             cur_draw.width = dst_r->width;
//             cur_draw.height = dst_r->height;

//             out.jpeg_page_rect.left = src_r->left; //, , ,  ;
//             out.jpeg_page_rect.top = src_r->top;
//             out.jpeg_page_rect.width = src_r->width;//hSPI_CAMERA_W;
//             out.jpeg_page_rect.height = src_r->height;//280;

//             //需要合成的范围，该范围必须在jpeg范围内，相对于背景
//             memcpy(&out.control_draw, &out.jpeg_page_rect, sizeof(struct rect));

//             if (!get_rect_cover(&out.jpeg_page_rect, &cur_draw, &r)) {
//                 printf("jpeg not in area1\n");
//             }

//             if (!get_rect_cover(&out.control_draw, &r, &draw_rect)) {
//                 printf("jpeg 0not in area2\n");
//             }

//             jpg_fd = jpeg_dec_get_fd();
//             jpeg_rect.left = draw_rect.left - out.jpeg_page_rect.left;
//             jpeg_rect.top = draw_rect.top - out.jpeg_page_rect.top;
//             jpeg_rect.width = draw_rect.width;
//             jpeg_rect.height = draw_rect.height;

//             jpeg_dec_start(&cur_draw, &draw_rect, &jpeg_rect, dst_buf);


// #endif
//             run_jpg_time++;
//         }
//     }
// }




// //  退出页面调用这个释放jpg内存
// void free_dial_ui_draw_custom(){
//     if(run_jpg_time){
//         jpeg_dec_uninit();
//         run_jpg_time = 0;
//     }
//     if(pic_buf){
//         free(pic_buf);
//         pic_buf = NULL;
//     }
// }


// //  自定义绘JPG图，自动申请buf
// void dial_ui_draw_custom(void *_dc, int x, int y, int width, int height, u8 *name)
// {
//     if(name == NULL || name[0]=='\0'){
//         return;
//     }

//     printf("ui_draw_custom 0x%x, %d\n", testinfo.jpg_stream, testinfo.jpg_file_len); 

//     static u8 last_name[20];
//     if(strcmp(last_name, name)) {    
//         memset(last_name, 0, sizeof(last_name));
//         strcpy(last_name, name);

//         if(pic_buf){
//             free(pic_buf);
//             pic_buf = NULL;
//         }

//         int len;
//         void* fp = fopen(last_name, "r");
//         if(fp){
//             len = flen(fp);
//             pic_buf = malloc(len);
//             fread(fp, pic_buf, len);
//             fclose(fp);
//         } else {
//             printf("内部flash没有这个文件: %s", name);
//             return;
//         }        
//         testinfo.jpg_stream     =   pic_buf;//rbuf->data;
//         testinfo.jpg_file_len   =   len;//rbuf->len;
//     }    


//     jpeg_dec_uninit();

//     u8 rgb_format = 1;//1 :rgb_565 0:rgb_888
//     char err = jpeg_dec_init(&testinfo, rgb_format, jpg_dec_stream_input);
//     run_jpg_time = 0;

//     if (err == -1) {
//         printf("\n [ERROR] %s -[jpg_dec_init_fail] %d\n", __FUNCTION__, __LINE__);
//         return;
//     }

//     run_jpg_time++;
    
//     ui_draw(_dc, NULL, x, y, width, height, dial_ui_custom_draw_cb, NULL, NULL, DRAW_DEMO);

// }

/*----------------------------------------------------------------------------*/
/**@brief   获取外挂flash资源文件的物理地址
   @param   path:文件路径, e.g "storage/virfat_flash/C/ui/scale454.bin"
   @return  文件的flash地址
   @note
*/
/*----------------------------------------------------------------------------*/
u32 get_file_addr(char *path)
{
    struct flash_file_info ui_resfile_info;
    int ret = ui_res_flash_info_get(&ui_resfile_info, path, "res");
    ASSERT(!ret);
    u32 file_addr = ui_resfile_info.tab[0] + ui_resfile_info.offset;//计算文件的物理地址
    ui_res_flash_info_free(&ui_resfile_info, "res");

    return file_addr;
}






/*
*---------------------------------------------------------------
*                        Lvgl Font Tool                         
*                                                               
* 注:使用unicode编码                                              
* 注:本字体文件由Lvgl Font Tool V0.4 生成                          
* 作者:阿里(qq:617622104)                                         
*---------------------------------------------------------------
*/




LV_FONT_DECLARE(ms_r_external_20)


#include "lvgl.h"
// #include "lv_src.h"



typedef struct{
    uint16_t min;
    uint16_t max;
    uint8_t  bpp;
    uint8_t  reserved[3];
}x_header_t;
typedef struct{
    uint32_t pos;
}x_table_t;
typedef struct{
    uint8_t adv_w;
    uint8_t box_w;
    uint8_t box_h;
    int8_t  ofs_x;
    int8_t  ofs_y;
    uint8_t r;
}glyph_dsc_t;


static x_header_t __g_xbf_hd = {
    .min = 0x000a,
    .max = 0xffe5,
    .bpp = 4,
};


// static uint8_t __g_font_buf[378];//如bin文件存在SPI FLASH可使用此buff
// #include "../misc/lv_fs.h"
// #include "../misc/lv_ll.h"
// #include "../misc/lv_gc.h"
// #include "ui/ui/jl_images/FILE_index.h"
// #include "../misc/lv_lru.h"
// static uint8_t *__user_font_getdata(int offset, int size){
//     if(offset<0){
//         return NULL;
//     }
//     //如字模保存在SPI FLASH, SPIFLASH_Read(__g_font_buf,offset,size);
//     //如字模已加载到SDRAM,直接返回偏移地址即可如:return (uint8_t*)(sdram_fontddr+offset);
//     extern const struct FileIndex FILE_index[] ;
//     // FILE_index[FILE_ms_r_external_20].addr
//     // ui_imb_read(IMB_RESOURCE_UI_FL,LV_SRC_MS_R_EXTERNAL_20_BIN+offset,__g_font_buf,size);
//     // return __g_font_buf;
//     extern u32 get_file_addr(char*);
//     static u32 file_addr=0;
    
//     if(!file_addr){
//         file_addr = get_file_addr("storage/virfat_flash/C/lvimg/font.bin");//55hz
//     }

//     // int addr = 0x4000000 + 0x600000 + FILE_index[FILE_ms_r_external_20].addr + offset;
//     int addr = file_addr + offset;

//     // lv_lru_t * lv_lru_create(size_t cache_size, size_t average_length, lv_lru_free_t * value_free,
//     //                      lv_lru_free_t * key_free);
//     // static lv_lru_t * mylru = NULL;
//     // if(mylru == NULL){
//     //     mylru = lv_lru_create(32*1024, 128, NULL, NULL);
//     //     printf("creat : %x",mylru);
//     // }
    


//     // void * value = NULL;

//     // if(mylru){
//     //     int key[1];
//     //     key[0] = offset;
//     //     // key[1] = size;
//     //     lv_lru_get(mylru, &key[0], sizeof(key), &value);
//     //     if(value == NULL) {
//     //         printf("lv_lru_get NO : offset %d %d",offset, size);
//     //         void *new = lv_mem_alloc(size);
//     //         memcpy(new, addr, size);
//     //         if(LV_LRU_OK != lv_lru_set(mylru, &key[0], sizeof(key), new, size)){
//     //             printf("lv_lru_set FALE %d %d",offset, size);
//     //             value = NULL;
//     //         } else {
//     //             value = new;
//     //         }
//     //     }
//     // }
    



//     return addr;//value;//__g_font_buf;//0x4000000 + FILE_index[FILE_ms_r_external_20].addr + offset;
// }


// static const uint8_t * __user_font_get_bitmap(const lv_font_t * font, uint32_t unicode_letter) {
//     if( unicode_letter>__g_xbf_hd.max || unicode_letter<__g_xbf_hd.min ) {
//         return NULL;
//     }
//     uint32_t unicode_offset = sizeof(x_header_t)+(unicode_letter-__g_xbf_hd.min)*4;
//     uint32_t *p_pos = (uint32_t *)__user_font_getdata(unicode_offset, 4);
//     if( p_pos[0] != 0 ) {
//         uint32_t pos = p_pos[0];
//         glyph_dsc_t * gdsc = (glyph_dsc_t*)__user_font_getdata(pos, sizeof(glyph_dsc_t));
//         return __user_font_getdata(pos+sizeof(glyph_dsc_t), gdsc->box_w*gdsc->box_h*__g_xbf_hd.bpp/8);
//     }
//     return NULL;
// }


// static bool __user_font_get_glyph_dsc(const lv_font_t * font, lv_font_glyph_dsc_t * dsc_out, uint32_t unicode_letter, uint32_t unicode_letter_next) {
//     if( unicode_letter>__g_xbf_hd.max || unicode_letter<__g_xbf_hd.min ) {
//         return NULL;
//     }
//     uint32_t unicode_offset = sizeof(x_header_t)+(unicode_letter-__g_xbf_hd.min)*4;
//     uint32_t *p_pos = (uint32_t *)__user_font_getdata(unicode_offset, 4);
//     if( p_pos[0] != 0 ) {
//         glyph_dsc_t * gdsc = (glyph_dsc_t*)__user_font_getdata(p_pos[0], sizeof(glyph_dsc_t));
//         dsc_out->adv_w = gdsc->adv_w;
//         dsc_out->box_h = gdsc->box_h;
//         dsc_out->box_w = gdsc->box_w;
//         dsc_out->ofs_x = gdsc->ofs_x;
//         dsc_out->ofs_y = gdsc->ofs_y;
//         dsc_out->bpp   = __g_xbf_hd.bpp;
//         return true;
//     }
//     return false;
// }


// //MiSans,,-1
// //字模高度：27
// //XBF字体,外部bin文件
// const lv_font_t ms_r_external_20 = {
//     .get_glyph_bitmap = __user_font_get_bitmap,
//     .get_glyph_dsc = __user_font_get_glyph_dsc,
//     .line_height = 27,
//     .base_line = 0,
// };


// #include <stdio.h>
// #include <stdlib.h>




// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#if TCFG_PSRAM_DEV_ENABLE
#include "usr_sd.h"
#include "generic/list.h"
#include "lbuf.h"

//  缓存空间
#define JL_ANMI_CACHE_SIZE  (256*1024)

//  动态图FIFO缓存



static lv_res_t sd_decoder_info(lv_img_decoder_t * decoder, const void * src, lv_img_header_t * header)
{
    lv_img_src_t src_type = lv_img_src_get_type(src);          /*Get the source type*/
    lv_res_t ret = LV_RES_OK;

    if(src_type != LV_IMG_SRC_FILE) return LV_RES_INV;

    struct image_file imgfile={0};

    if(strncmp("d:", src, sizeof("d:")-1)) return LV_RES_INV;

    char * real_path = NULL;  //  真实路径
    if(((u8*)src)[1] == ':') real_path = &((u8*)src)[2]; 

    printf("get info sd: %s", real_path);

    void *fp = fopen(real_path, "r");
    if(!fp) return LV_RES_INV;

    struct sd_res_h head={0};
    fread(fp, &head, sizeof(struct sd_res_h));
            printf("Head:\n\
                int checksum = %d\n\
                int tablen = %d\n\
                int filesnum = %d\n\
                int fps = %d\n\
                u8 name[12] = %s\n\
                int fileslen %d\n\
            ", head.checksum, head.tablen, head.filesnum, head.fps, head.name, head.fileslen);

    struct sd_table_data table={0};
    fread(fp, &table, sizeof(struct sd_table_data));
    printf("\n\
    sd_table_data :\n\
        u8 name [12] = %s\n\
        int addr = %x\n\
    ",
    table.name,
    table.addr
    );

    int first_img_addr = table.addr;
    fseek(fp, first_img_addr, SEEK_SET);
    struct img_h img_head={0};
    fread(fp, &img_head, sizeof(struct img_h));
    printf("\n\
    first img_head :\n\
        int nowaddr = %x\n\
        int nextaddr = %x\n\
        struct image_file file :\n\
            u8 format = %d\n\
            u8 compress = %d\n\
            u16 data_crc = %d\n\
            u16 width = %d\n\
            u16 height = %d\n\
            u32 offset = %x\n\
            u32 len = %d\n\
            u32 unzipOffset = %d\n\
            u32 unzipLen = %d\n\
        u8 data[0] = %x\n\
    ",
    img_head.nowaddr,
    img_head.nextaddr,
    img_head.file.format,
    img_head.file.compress,
    img_head.file.data_crc,
    img_head.file.width,
    img_head.file.height,
    img_head.file.offset,
    img_head.file.len,
    img_head.file.unzipOffset,
    img_head.file.unzipLen,
    img_head.file.len,
    img_head.data
    );      


    header->always_zero = 0;
    header->cf = 1;
    header->reserved = 0;
    header->w = img_head.file.width;
    header->h = img_head.file.height;

    fclose(fp);

    return LV_RES_OK;
}

int post_sd_msg(int *msg, u8 len);
static void anim_cb(lv_timer_t * p){
    struct usr_sd_decoder_info * usr_sd = p->user_data;
    // usr_sd->cache
    // printf("anim tick....");

    int msg[2] ={0};
    msg[0] = usr_sd;
    msg[1] = 0;
    post_sd_msg(msg, 2);

    //  动画被用户释放，删掉定时器
    if(usr_sd == NULL){
        printf("动画被用户释放，删掉定时器");
        lv_timer_del(p);
    }

    //  pop出来，如果是空的就维持当前图片
    struct img_h * new_img_data = jpg_lbuf_pop(usr_sd->lbuf_handle, BIT(0));
    psram_flush_invaild_cache(new_img_data, sizeof(struct img_h)+new_img_data->file.len);

    if(new_img_data){
        if(*(usr_sd->img_data) != new_img_data) {
            // printf("释放上一张图片的数据 *(usr_sd->img_data) : %x", *(usr_sd->img_data));
            jpg_lbuf_free(*(usr_sd->img_data));
            // printf("更新新图片数据");
            
            *(usr_sd->img_data) = new_img_data;
            
        } else {
            printf("维持原图");
        }
    } else {
        printf("lbuf 队列为空");
    }
}


static lv_res_t sd_decoder_open(lv_img_decoder_t * decoder, lv_img_decoder_dsc_t * dsc)
{
    printf("sd_decoder_open....");
    LV_UNUSED(decoder);
    lv_res_t lv_ret = LV_RES_OK;

    if(dsc->src_type != LV_IMG_SRC_FILE) return LV_RES_INV;
    
    if(strncmp("d:", dsc->src, sizeof("d:")-1)) return LV_RES_INV;
    char * real_path = NULL;  //  真实路径
    if(((u8*)dsc->src)[1] == ':') real_path = &((u8*)dsc->src)[2]; 

    void *fp = fopen(real_path, "r");
    printf("open fp: %x", fp);
    if(!fp) return LV_RES_INV;

    fseek(fp, 0, SEEK_SET);
    struct sd_res_h sd_head;
    fread(fp, &sd_head, sizeof(struct sd_res_h));
    fseek(fp, sizeof(struct sd_res_h), SEEK_SET);
    struct sd_table_data table={0};
    fread(fp, &table, sizeof(struct sd_table_data));
    int first_img_addr = table.addr;
    fseek(fp, first_img_addr, SEEK_SET);
    struct img_h now_img_head={0};
    fread(fp, &now_img_head, sizeof(struct img_h));

    printf("打开图片，第一张地址：%x 长度 %d", first_img_addr, now_img_head.file.len);

    //  申请缓冲
    struct lbuff_head *lbuf_handle = NULL;
    int buf_size = JL_ANMI_CACHE_SIZE;//256*1024;//256*1024;    //  动图JPG缓冲空间
    void * lbuf_ptr = malloc_psram(buf_size);

    if (lbuf_ptr == NULL) { 
        printf("lbuf malloc buf err");
        return LV_RES_INV;
    }
    extern struct lbuff_head *jpg_lbuf_init(void *buf, u32 len, int align, int priv_head_len);
    lbuf_handle = jpg_lbuf_init(lbuf_ptr, buf_size, 4, sizeof(struct img_h));

    printf("lbuf_handle %x", lbuf_handle);
    extern void *jpg_lbuf_alloc(struct lbuff_head *head, u32 len);
    struct img_h * pdata = jpg_lbuf_alloc(lbuf_handle, now_img_head.file.len);
    memcpy(pdata, &now_img_head, sizeof(struct img_h));
    printf("img_head_addr : %x  pdata_addr : %x", pdata, pdata->data);

    //如果要解压，需要改成CF = 具体格式，dsc->img_data 指向 img头+解压数据

    fread(fp, pdata->data, now_img_head.file.len);

    psram_flush_invaild_cache(pdata, sizeof(struct img_h)+now_img_head.file.len);
    // put_buf(pdata->data, 128);

    // put_buf((u8*)pdata->data + 5822 - 128, 128);

    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>PUSH");
    jpg_lbuf_push(pdata, BIT(0));   //  推入缓冲

    put_buf(pdata->data, 128);

    
    dsc->img_data = pdata;

    struct usr_sd_decoder_info * usr_info_p = zalloc(sizeof(struct usr_sd_decoder_info));
    if(usr_info_p==NULL) return LV_RES_INV;
    usr_info_p->fp = fp;
    usr_info_p->cache = lbuf_ptr;
    usr_info_p->lbuf_handle = lbuf_handle;
    usr_info_p->img_info = now_img_head;
    usr_info_p->img_data = &dsc->img_data;
    usr_info_p->pre_img_info = now_img_head;

    printf("Init lbuf_handle :%x", usr_info_p->lbuf_handle);
    //  是动图创建刷新定时器
    if(sd_head.fps!=0){
        usr_info_p->time = lv_timer_create(anim_cb, sd_head.fps, usr_info_p);
    }
    
    printf("usr_info_p : %x",usr_info_p);
    dsc->user_data = usr_info_p;
    
    printf("sd_decoder_open end");
    os_time_dly(10);
    return LV_RES_OK;
}

static void sd_decoder_close(lv_img_decoder_t * decoder, lv_img_decoder_dsc_t * dsc)
{
    LV_UNUSED(decoder);

    if(LV_IMG_SRC_FILE == dsc->src_type){
        struct usr_sd_decoder_info * usr_sd = dsc->user_data;
        printf("释放ANMI资源 : %x busy : %d", usr_sd, usr_sd->sd_busy);
        while(usr_sd->sd_busy==1){
            printf("wait");
            os_time_dly(1);
        }
        fclose(usr_sd->fp);
        usr_sd->fp = NULL;
        jpg_lbuf_clear(usr_sd->lbuf_handle);
        free_psram(usr_sd->cache);
        lv_timer_del(usr_sd->time);
        // free(usr_sd);
        int msg[2] ={0};
        msg[0] = usr_sd;
        msg[1] = 0x123; //  sd线程去释放usr_sd
        post_sd_msg(msg, 2);

        printf("释放ANMI资源 END");
    }
}

static OS_SEM lv_read_task_sem;



#define __get_entry(lbuf)   \
	(struct hentry *)((u8 *)lbuf - sizeof(struct hentry))

void lv_read_task(void *p){
    int msg[32];
    while (1) {
        memset(msg, 0, sizeof(msg));
        int ret = os_taskq_pend(NULL, msg, ARRAY_SIZE(msg)); 
        // printf("lv_read_task... ret %d",ret);
        // os_time_dly(10);
        if(ret!=OS_TASKQ) continue;
        if(!msg[0])    continue;

        // printf("lv_read_task : %x", msg[0]);
        struct usr_sd_decoder_info * usr_info_p = msg[0];

        if(usr_info_p->fp == NULL){
            if(msg[1] == 0x123) free(usr_info_p);
            printf("sd任务释放：%x %x", usr_info_p, msg[1]);
            continue;
        }

        usr_info_p->sd_busy = 1;
        sd_busy = 1;

        //  推缓冲
        while(1){
            static struct img_h pre_img_info;
            static u8 full = 0;
            int free_space = jpg_lbuf_free_space(usr_info_p->lbuf_handle);
            int pos;
            int len;

            if(!full) {
                // printf("lv_read_task fp: %x",usr_info_p->fp);
                int a = jiffies_half_msec();
                fseek(usr_info_p->fp, usr_info_p->pre_img_info.nextaddr, SEEK_SET);
                fread(usr_info_p->fp, &pre_img_info, sizeof(struct img_h));
                int pos = fpos(usr_info_p->fp);
                int len = flen(usr_info_p->fp);     
                int b = jiffies_half_msec();      
                // printf("nexet 1/2ms %d", b-a);     
                // if(pos >= len){
                //     printf("最后一张图");
                //     pre_img_info = usr_info_p->img_info;//跳到第一张
                // } else {
                    // printf("f:%x %x", pos, len);
                    // printf("now:%x next:%x", pre_img_info.nowaddr , usr_info_p->pre_img_info.nextaddr);
                    if(pre_img_info.nowaddr != usr_info_p->pre_img_info.nextaddr){
                        printf("地址校验失败 : %x", pre_img_info.nowaddr);
                        break;
                    }                
                // }           
            }

            if(pre_img_info.file.len>= free_space){
                // printf("已推满缓冲 下一张图大小：%d 剩余大小：%d",pre_img_info.file.len, free_space);
                // full = 1;
                break;
            }
            full = 0;
            // printf("推缓冲。。。usr_info_p->lbuf_handle:%x", usr_info_p->lbuf_handle);
            extern void *jpg_lbuf_alloc(struct lbuff_head *head, u32 len);
            struct img_h * pdata = jpg_lbuf_alloc(usr_info_p->lbuf_handle, pre_img_info.file.len);
            struct hentry *p = __get_entry(pdata);
            struct lbuff_head *head = (struct lbuff_head *)((u8 *)p - p->offset);
            // printf("head %x offset %x", head, p->offset);
        //      ASSERT(((u32)p->entry.next & 0x03) == 0, "%p,%p", head, p->entry.next);
        // ASSERT(((u32)p->entry.prev & 0x03) == 0, "%p,%p", head, p->entry.prev);
        // ASSERT(((u32)head->head.prev & 0x03) == 0, "%p,%x,%p", head, head->total_size, head->head.prev);
        // ASSERT(((u32)head->head.next & 0x03) == 0, "%p,%x,%p", head, head->total_size, head->head.next);
            // pdata->data[pre_img_info.file.len]=0x55;
            memcpy(pdata, &pre_img_info, sizeof(struct img_h));
            // printf("img_head_addr : %x  pdata_addr : %x", pdata, pdata->data);
            fread(usr_info_p->fp, pdata->data, pre_img_info.file.len);
            // printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>PUSH %x", &pdata->data[pre_img_info.file.len+4]);

        //     ASSERT(pdata->data[pre_img_info.file.len]==0x55);

        //         ASSERT(((u32)p->entry.next & 0x03) == 0, "%p,%p", head, p->entry.next);
        // ASSERT(((u32)p->entry.prev & 0x03) == 0, "%p,%p", head, p->entry.prev);
        // ASSERT(((u32)head->head.prev & 0x03) == 0, "%p,%x,%p", head, head->total_size, head->head.prev);
        // ASSERT(((u32)head->head.next & 0x03) == 0, "%p,%x,%p", head, head->total_size, head->head.next);
            jpg_lbuf_push(pdata, BIT(0));   //  推入缓冲
            // printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>PUSH 222");
            memcpy(&usr_info_p->pre_img_info, &pre_img_info, sizeof(struct img_h));
        }
        
        // printf("push end... ： %x", usr_info_p);
        usr_info_p->sd_busy = 0;
        sd_busy = 0;
    }
}

int post_sd_msg(int *msg, u8 len)
{
    os_taskq_post_type("lvgl_sd", msg[0], len - 1, &msg[1]);
}

void sd_task_init(){
    int err = 0;
    clock_add_set(DEC_UI_CLK);
    err = task_create(lv_read_task, NULL, "lvgl_sd");
    if (err) {
        r_printf("ui task create err:%d \n", err);
    }

}

void lv_jl_sd_init(void)
{
    sd_task_init();
    lv_img_decoder_t * dec = lv_img_decoder_create();
    lv_img_decoder_set_info_cb(dec, sd_decoder_info);
    lv_img_decoder_set_open_cb(dec, sd_decoder_open);   
    lv_img_decoder_set_close_cb(dec, sd_decoder_close);
    // lv_img_decoder_set_read_line_cb(dec, decoder_read_line);
}

























//  静态 L-F-U 缓存
struct usr_lfu_img_info {
    void *  cache;    
    void ** pp_data;  
    lv_timer_t * time;
};

static lv_res_t sd_img_decoder_info(lv_img_decoder_t * decoder, const void * src, lv_img_header_t * header)
{
    lv_img_src_t src_type = lv_img_src_get_type(src);          /*Get the source type*/
    lv_res_t ret = LV_RES_OK;
    if(src_type != LV_IMG_SRC_FILE) return LV_RES_INV;
    if(strncmp("s:", src, sizeof("s:")-1)) return LV_RES_INV;
    char * real_path = NULL;  //  真实路径
    if(((u8*)src)[1] == ':') real_path = &((u8*)src)[2]; 

    printf("get info sd s: %s", real_path);

    struct image_file imgfile={0};
    void *fp = fopen(real_path, "r");
    if(!fp) goto __error;

    //  加载header信息即可
    if(!memcmp(lv_fs_get_ext(real_path), "bin", strlen("bin"))){
        printf("bin文件 %s");
        fseek(fp, 0, SEEK_SET);
        int checkhead = 0;
        fread(fp, &checkhead, 4);
        put_buf(&checkhead, 4);
        printf(">>%s", &checkhead);
        if(!memcmp(&checkhead, "IMB", sizeof("IMB"))){
            struct img_h head_temp;
            fread(fp, &head_temp, sizeof(struct img_h));
            fclose(fp);  


            printf("\n\
            first img_head :\n\
                int nowaddr = %x\n\
                int nextaddr = %x\n\
                struct image_file file :\n\
                    u8 format = %d\n\
                    u8 compress = %d\n\
                    u16 data_crc = %d\n\
                    u16 width = %d\n\
                    u16 height = %d\n\
                    u32 offset = %x\n\
                    u32 len = %d\n\
                    u32 unzipOffset = %d\n\
                    u32 unzipLen = %d\n\
                u8 data[0] = %x\n\
            ",
            head_temp.nowaddr,
            head_temp.nextaddr,
            head_temp.file.format,
            head_temp.file.compress,
            head_temp.file.data_crc,
            head_temp.file.width,
            head_temp.file.height,
            head_temp.file.offset,
            head_temp.file.len,
            head_temp.file.unzipOffset,
            head_temp.file.unzipLen,
            head_temp.file.len,
            head_temp.data
            );      


            if(head_temp.file.width == 0) goto __error;

            header->w = head_temp.file.width;
            header->h = head_temp.file.height;
            header->cf = 1;
            return LV_RES_OK; 
        }
    }
  
    if(!memcmp(lv_fs_get_ext(real_path), "jpg", strlen("jpg"))){
        printf("jpg文件 %s");
        fseek(fp, 0, SEEK_SET);
        u8 checkhead[3] = {0};
        u8 jpg_head[3] = {0xFF, 0xD8, 0xFF};
        fread(fp, &checkhead, 3);
        if(!memcmp(checkhead, jpg_head, sizeof(jpg_head))){
            void * jpg_temp = malloc(flen(fp));
            if(jpg_temp==NULL) goto __error;

            fseek(fp, 0, SEEK_SET);
            fread(fp, jpg_temp, flen(fp));

            struct jpeg_decoder_fd *jpg_fd = jpeg_dec_get_fd();
            struct FileIndex jpgres = {0};
            jpgres.addr = jpg_temp;
            jpgres.len = flen(fp);
            imb_task_lock();
            char err = jpeg_dec_init(&jpgres, 1, usr_jpg_dec_stream_input2);
            imb_task_unlock();
            free(jpg_temp);
            jpg_temp = NULL;

            header->w = jpg_fd->info.x;//jpeg图片本身的宽度
            header->h = jpg_fd->info.y;//jpeg图片本身的高度
            header->cf = 1;
            fclose(fp);
            return LV_RES_OK;
        }
    }

__error:    
    if(fp)fclose(fp);
    printf("文件资源加载失败");
    return LV_RES_INV;
}

static lv_res_t sd_img_decoder_open(lv_img_decoder_t * decoder, lv_img_decoder_dsc_t * dsc)
{
    printf("s: sd_decoder_open....");
    LV_UNUSED(decoder);

    if(dsc->src_type != LV_IMG_SRC_FILE) return LV_RES_INV;
    if(strncmp("s:", dsc->src, sizeof("s:")-1)) return LV_RES_INV;
    char * real_path = NULL;  //  真实路径
    if(((u8*)dsc->src)[1] == ':') real_path = &((u8*)dsc->src)[2]; 

    void *fp = fopen(real_path, "r");
    printf("s: open fp: %x", fp);
    if(!fp) goto __error;

    if(!memcmp(lv_fs_get_ext(real_path), "bin", strlen("bin"))){
        fseek(fp, 0, SEEK_SET);
        int checkhead = 0;
        fread(fp, &checkhead, 4);
        if(!memcmp(&checkhead, "IMB", sizeof("IMB"))){
            printf("malloc psram lem: %d", flen(fp));
            void * data = malloc_psram(flen(fp)-4);
            if(data == NULL) goto __error;
            fread(fp, data, flen(fp)-4);
            int flent  = flen(fp)-4;
            fclose(fp);

            struct usr_lfu_img_info * usr_data = zalloc(sizeof(struct usr_lfu_img_info));
            if(usr_data == NULL) goto __error;
            usr_data->cache = data;
            usr_data->pp_data = &dsc->img_data;
            usr_data->time = NULL;

            dsc->img_data = data;
            dsc->user_data = usr_data;   
            printf("打开 %s 图片成功 图片地址 %x", dsc->src, dsc->img_data);
            psram_flush_invaild_cache(data, flent);
            return LV_RES_OK;
        }
        if(checkhead == 0x12345678){
            // void * data = malloc_psram(flen(fp)-4);
            // if(data == NULL) goto __error;
            // fread(fp, data, flen(fp)-4);
            // fclose(fp);
            // dsc->user_data
                // //  是动图创建刷新定时器
    // if(sd_head.fps!=0){
    //     usr_info_p->time = lv_timer_create(anim_cb, sd_head.fps, usr_info_p);
    // }

            fclose(fp);
            return LV_RES_OK;
        }
    }

    if(!memcmp(lv_fs_get_ext(real_path), "jpg", strlen("jpg"))){
        fseek(fp, 0, SEEK_SET);
        u8 checkhead[3] = {0};
        u8 jpg_head[3] = {0xFF, 0xD8, 0xFF};
        fread(fp, &checkhead, 3);
        if(!memcmp(checkhead, jpg_head, sizeof(jpg_head))){
            struct img_h img_h_temp = {0};  //  补充头信息
            img_h_temp.file.format = 11;
            img_h_temp.file.len = flen(fp);
            img_h_temp.file.width = dsc->header.w;
            img_h_temp.file.height = dsc->header.h;
            printf("JPG: L W H %d %d %d", img_h_temp.file.len,
            img_h_temp.file.width,img_h_temp.file.height
            );
            struct img_h * data = malloc_psram(sizeof(struct img_h) + flen(fp));
            if(data == NULL) goto __error;
            memcpy(data, &img_h_temp, sizeof(struct img_h));
            printf("JPG: L W H %d %d %d", data->file.len,
            data->file.width,data->file.height
            );
            fseek(fp, 0, SEEK_SET);
            fread(fp, data->data, flen(fp));
            int flent  = sizeof(struct img_h) + flen(fp);
            fclose(fp);

            struct usr_lfu_img_info * usr_data = zalloc(sizeof(struct usr_lfu_img_info));
            if(usr_data == NULL) goto __error;
            usr_data->cache = data;
            usr_data->pp_data = &dsc->img_data;
            usr_data->time = NULL;

            dsc->img_data = data;
            dsc->user_data = usr_data;   
            printf("打开 %s 图片成功 %x", dsc->src, data);
            put_buf(data->data, 4);
            psram_flush_invaild_cache(data, flent);
            put_buf(data->data, 4);
            return LV_RES_OK;
        }
    }

__error:    
    if(fp)fclose(fp);
    return LV_RES_INV;
}

static void sd_img_decoder_close(lv_img_decoder_t * decoder, lv_img_decoder_dsc_t * dsc)
{
    LV_UNUSED(decoder);

    if(LV_IMG_SRC_FILE == dsc->src_type){
        if(dsc->user_data){
            struct usr_lfu_img_info * usr_data = dsc->user_data;
            if(usr_data->cache){
                free_psram(usr_data->cache);
                usr_data->cache = NULL;
            }
            free(dsc->user_data);
            dsc->user_data = NULL;
        }
    }
}
1
void lv_jl_sd_img_init(void)
{
    lv_img_decoder_t * dec = lv_img_decoder_create();
    lv_img_decoder_set_info_cb(dec, sd_img_decoder_info);
    lv_img_decoder_set_open_cb(dec, sd_img_decoder_open);   
    lv_img_decoder_set_close_cb(dec, sd_img_decoder_close);
    // lv_img_decoder_set_read_line_cb(dec, decoder_read_line);
}

#endif




//  动画解析换一个路径 d:盘,后面保留1字节

//  新动画访问方式，可以一个res一个动画，也可以一个res多组动画
//  加载就直接显示，释放用lv_img_cache_invalidate_src();
//  d: + 标准res路径                    ID为1
//  d: + 标准res路径 + | + \xID         ID为自定义
//  d: + 标准res路径 + + + 123        ID为自定义
//  设置ui.res访问114ID号的GIF图         "d:storage/virfat_flash/C/ui/ui.res"

// d:storage/virfat_flash/C/ui/ui.res#24

#define JLANIMLETTER    "d:"
#define JLIDKEY         '|'
#define JLIDKEY_A       '+'

static void draw_cleanup(_lv_img_cache_entry_t * cache);


static lv_res_t jl_animimg_decoder_info(lv_img_decoder_t * decoder, const void * src, lv_img_header_t * header)
{
    lv_img_src_t src_type = lv_img_src_get_type(src);          /*Get the source type*/
    lv_res_t ret = LV_RES_OK;
    if(src_type != LV_IMG_SRC_FILE) return LV_RES_INV;
    if(strncmp(JLANIMLETTER, src, sizeof(JLANIMLETTER)-1)) return LV_RES_INV;
    char * temp_real_path = NULL;  
    if(((u8*)src)[1] == ':') temp_real_path = &((u8*)src)[2]; 
    int id = 1;
    char real_path[64] = {0};
    char *position = strrchr(temp_real_path, JLIDKEY);
    if (position != NULL) {
        memcpy(real_path, temp_real_path, position - temp_real_path);
        id = (u8)(*(position+1));
        if (id==0) id=1;
    }  else if((position = strrchr(temp_real_path, JLIDKEY_A))) {
        memcpy(real_path, temp_real_path, position - temp_real_path);
        id = A2I(position+1);
        if (id==0) id=1;
    } else strcpy(real_path, temp_real_path);
    
    RESFILE * fp = res_fopen(real_path, "r");
    printf("jl_animimg_decoder_info : %s %x", real_path, fp);
    if(!fp) return LV_RES_INV;
    if(!memcmp(lv_fs_get_ext(real_path), "RES", strlen("RES"))){
        fp->ver = 0x410;
        u8 * strid = real_path + strlen(real_path) + 1;
        struct image_file img_file = {0};
        struct gif_file_info gifinfo = {0};
        int ret = open_image_by_id(0, fp, &img_file, id & 0xffff, id >> 16);
        if(ret) {
            r_printf("error1");
            fp->ver = 0x0; 
            ret = open_image_by_id(0, fp, &img_file, id & 0xffff, id >> 16);
        }
        if(ret) {
            r_printf("error2");
            if(fp)res_fclose(fp);
            return LV_RES_INV;
        }
        // if(img_file.format != PIXEL_FMT_GIF){
        //     if(fp)res_fclose(fp);
        //     return LV_RES_INV;
        // }
        if(img_file.width == 0){
            if(fp)res_fclose(fp);
            return LV_RES_INV;
        }
        header->w = img_file.width;
        header->h = img_file.height;
        header->cf = 1;
        printf("%d %d", header->w,header->h);
        if(fp)res_fclose(fp);
        return LV_RES_OK;
    }

    if(fp)res_fclose(fp);
    return LV_RES_INV;
}

static lv_res_t jl_animimg_decoder_open(lv_img_decoder_t * decoder, lv_img_decoder_dsc_t * dsc)
{
    LV_UNUSED(decoder);
    if(dsc->src_type != LV_IMG_SRC_FILE) return LV_RES_INV;
    if(strncmp(JLANIMLETTER, dsc->src, sizeof(JLANIMLETTER)-1)) return LV_RES_INV;
    char * temp_real_path = NULL;  
    if(((u8*)dsc->src)[1] == ':') temp_real_path = &((u8*)dsc->src)[2]; 
    int id = 1;
    char real_path[64] = {0};
    char *position = strrchr(temp_real_path, JLIDKEY);
    if (position != NULL) {
        memcpy(real_path, temp_real_path, position - temp_real_path);
        id = (u8)(*(position+1));
        if (id==0) id=1;
    }  else if((position = strrchr(temp_real_path, JLIDKEY_A))) {
        memcpy(real_path, temp_real_path, position - temp_real_path);
        id = A2I(position+1);
        if (id==0) id=1;
    }   else strcpy(real_path, temp_real_path);
    printf("jl_animimg_decoder_open %s", real_path);
    RESFILE *fp = res_fopen(real_path, "r");
    if(!fp) return LV_RES_INV;
    struct jl_animimg_info * usr_data = zalloc(sizeof(struct jl_animimg_info));
    if(usr_data==NULL) {
        res_fclose(fp);
        return LV_RES_INV;
    }
    usr_data->nowindex = 1; 
    fp->ver = 0x410;
    struct gif_file_info gifinfo = {0};
    int ret = open_image_by_id(0, fp, &(usr_data->img_file), id & 0xffff, id >> 16);
    if(ret) {
        fp->ver = 0x0;  
        ret = open_image_by_id(0, fp, &(usr_data->img_file), id & 0xffff, id >> 16);
    }
    if(ret) {
        if(fp)res_fclose(fp);
        return LV_RES_INV;
    }

    printf("_____ui_res_flash_info_get前 %s", real_path);
    usr_data->fd = fp; 
    ui_res_flash_info_get(&usr_data->ui_resfile_info, real_path, "res");    
    printf("_____ui_res_flash_info_get后");

    if(usr_data->img_file.format != PIXEL_FMT_GIF) {
        //  普通图片，啥也不干
    } else {
        usr_data->nowindex = 1; 
        dsc->img_data = NULL;   
        gif_read_head_info(0, fp, &(usr_data->img_file), &(usr_data->gifinfo));
        struct gif_file_frame tempframe = {0};
        read_gif_file_frame(0, fp, &(usr_data->img_file), &tempframe, usr_data->nowindex, usr_data->gifinfo.version);
        if(tempframe.base_index == tempframe.curr_index && tempframe.curr_index == usr_data->nowindex){
            memcpy(&usr_data->bframe, &tempframe, sizeof(struct gif_file_frame));
            memcpy(&usr_data->dframe, &tempframe, sizeof(struct gif_file_frame));
            if(usr_data->bframe.flag&BIT(0)){
                read_image_data(0, usr_data->fd, &(usr_data->img_file), usr_data->btub, 256 * 4, usr_data->bframe.addr);
            }
        }    
        
        //  获取所有帧率信息
        int idx = 1;
        int fnum = (usr_data->gifinfo.frame_num);
        void * fnump = zalloc(sizeof(usr_data->allframeinfo)+sizeof(int)*fnum+4);//留4byte保险
        if(fnump){       
            usr_data->allframeinfo = fnump;
            usr_data->allframeinfo->num = fnum;
            for(idx = 1; idx <= fnum; idx++){
                read_gif_file_frame(0, fp, &(usr_data->img_file), &tempframe, idx, usr_data->gifinfo.version);
                //int*n
                usr_data->allframeinfo->delay[idx-1] = tempframe.delay;
            }

            //回读
            g_printf("all idx:%d", usr_data->allframeinfo->num);
            for(idx = 1; idx <= fnum; idx++){
                g_printf("idx:%d delay:%d", idx, usr_data->allframeinfo->delay[idx-1]);
            }
            put_buf(fnump, sizeof(usr_data->allframeinfo)+sizeof(int)*fnum+4);
        }
    }

    printf("gif %d %d", usr_data->bframe.width, usr_data->bframe.height);
    // usr_data->fd = res_fopen(real_path, "r");
    dsc->user_data = usr_data;   
    return LV_RES_OK;
}

static void jl_animimg_decoder_close(lv_img_decoder_t * decoder, lv_img_decoder_dsc_t * dsc)
{
    LV_UNUSED(decoder);

    if(LV_IMG_SRC_FILE == dsc->src_type){
        if(dsc->user_data){
            printf("%s %d",__func__,__LINE__);
            struct jl_animimg_info * usr_data = dsc->user_data;
            ui_res_flash_info_free(&usr_data->ui_resfile_info, "res");
            res_fclose(usr_data->fd);

            if(usr_data->allframeinfo){
                free(usr_data->allframeinfo);
                usr_data->allframeinfo = NULL;
            }

            free(usr_data);
            dsc->user_data = NULL;
        }
    }
}

void jl_animimg_decoder_init(void)
{
    lv_img_decoder_t * dec = lv_img_decoder_create();
    lv_img_decoder_set_info_cb(dec, jl_animimg_decoder_info);
    lv_img_decoder_set_open_cb(dec, jl_animimg_decoder_open);   
    lv_img_decoder_set_close_cb(dec, jl_animimg_decoder_close);
    dec->user_data = 0x314159;
}


//  通过路径去切换索引
    // _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(src, recolor, 0);
    // if(cdsc == NULL) return;
    // struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    // if(usr_data == NULL) {draw_cleanup(cdsc);return;}


    // draw_cleanup(cdsc);


//  

void usr_anim_start(char * src){

}

void usr_anim_stop(char * src){
    
}

static void change_anim_index(lv_timer_t * p){
    // return;
    void * src = p->user_data;
    lv_color_t recolor;
    recolor.full = 0;
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(src, recolor, 0);
    if(cdsc == NULL) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) {draw_cleanup(cdsc);return;}
if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;
    // if(!lv_obj_is_valid(usr_data->obj)){draw_cleanup(cdsc);return;}//有问题

    read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &(usr_data->dframe), usr_data->nowindex, usr_data->gifinfo.version);
    if(usr_data->dframe.base_index != usr_data->bframe.curr_index){
        read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &(usr_data->bframe), usr_data->dframe.base_index, usr_data->gifinfo.version);
        if(usr_data->bframe.flag&BIT(0)){
            read_image_data(0, usr_data->fd, &(usr_data->img_file), usr_data->btub, 256 * 4, usr_data->bframe.addr);
        }
    }

    if(usr_data->nexttime) lv_timer_set_period(usr_data->nexttime, usr_data->dframe.delay);
    static int last_time = 0;
    if(last_time == 0){last_time = lv_tick_get();}
    printf("当前时间撮 %d 与上次差值 %d 下一帧间隔 ：%d ", lv_tick_get(), lv_tick_elaps(last_time), usr_data->dframe.delay);
    last_time = lv_tick_get();
    usr_data->nowindex = (usr_data->nowindex % usr_data->gifinfo.frame_num) + 1;
    if(p->repeat_count == 0){
        usr_data->nexttime = NULL;
        if(usr_data->func){
            // printf("func   data  %x %x", usr_data->func, usr_data->func_data);
            // os_time_dly(10);
            // usr_data->func(usr_data->func_data);
            lv_timer_t * t = lv_timer_create(usr_data->func, 0, usr_data->func_data);
            lv_timer_set_repeat_count(t, 1);

            // test_to_main();
        }
    }
    // if(lv_obj_is_valid(usr_data->obj))lv_obj_invalidate(usr_data->obj);//////有问题

    draw_cleanup(cdsc);
}

void jl_set_imgs_id(lv_obj_t* obj, int id){
    lv_img_t * img = (lv_img_t *)obj;
    lv_color_t recolor;
    recolor.full = 0;
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(img->src, recolor, 0);
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;
    if(cdsc == NULL) return;
    cdsc->dec_dsc.frame_id = id;
    draw_cleanup(cdsc);
}



void jl_animing_start(lv_obj_t* obj, int repeat, int endly, void (*fun)(void *), void *fun_data){
    lv_img_t * img = (lv_img_t *)obj;
    lv_color_t recolor;
    recolor.full = 0;
    printf("%x %s", img, img->src);
    if(!img || !img->src) return;
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(img->src, recolor, 0);
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;
    if(cdsc == NULL) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return;

    if(usr_data->img_file.format != PIXEL_FMT_GIF){
        return;
    }

    usr_data->endly = endly;
    usr_data->func  = fun;
    usr_data->func_data = fun_data;

    // printf("func   data %x  %x", fun, fun_data);

    usr_data->obj = obj;
    if(usr_data->nexttime){
        lv_timer_del(usr_data->nexttime);
        usr_data->nexttime = NULL;
    }
    if(!usr_data->nexttime){
        usr_data->nowindex = 1;
        usr_data->nexttime = lv_timer_create(change_anim_index, usr_data->dframe.delay, img->src);
    }
    if(repeat>0){
        lv_timer_set_repeat_count(usr_data->nexttime, repeat*usr_data->gifinfo.frame_num);
    }
    draw_cleanup(cdsc);
}

void jl_animing_stop(lv_obj_t* obj, u8 del){
    lv_img_t * img = (lv_img_t *)obj;
    lv_color_t recolor;
    recolor.full = 0;
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(img->src, recolor, 0);
    if(cdsc == NULL) return;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return;
    if(usr_data->img_file.format != PIXEL_FMT_GIF){
        return;
    }
    if(usr_data->nexttime){
        lv_timer_del(usr_data->nexttime);
        usr_data->nexttime = NULL;
    }
    if(del) lv_img_cache_invalidate_src(img->src);
    draw_cleanup(cdsc);
}

int jl_animing_get_all_time(lv_obj_t* obj){
    lv_img_t * img = (lv_img_t *)obj;
    lv_color_t recolor;
    recolor.full = 0;
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(img->src, recolor, 0);
    if(cdsc == NULL) return 0;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return 0;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return 0;
    int alltime = 0;
    int temp_index = 1;
    struct gif_file_frame tempframe = {0};
    for(temp_index=1; temp_index<=usr_data->gifinfo.frame_num; temp_index++) {
        read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &tempframe, temp_index, usr_data->gifinfo.version);
        alltime = tempframe.delay + alltime;
    }
    usr_data->alltime = alltime;
    printf("一次动画所有时间 : %d", alltime);

    draw_cleanup(cdsc);
    return usr_data->alltime;
}

static void draw_cleanup(_lv_img_cache_entry_t * cache);
static struct imb_task *imb_create_gif_frame_task(struct imb_task_head *root, int elm_id, int id, struct image_file *file, u32 priv, int x, int y, int width, int height, struct rect *crop, int zip, int data_in_falsh);
static int check_gif_res(struct _lv_draw_ctx_t * draw_buf, const lv_draw_img_dsc_t * draw_dsc,
                         const lv_area_t * coords, const void * src){
    lv_img_src_t src_type = lv_img_src_get_type(src);        
    if(src_type != LV_IMG_SRC_FILE) return LV_RES_INV;
    if(strncmp(JLANIMLETTER, src, sizeof(JLANIMLETTER)-1)) return LV_RES_INV; 
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(src, draw_dsc->recolor, draw_dsc->frame_id);
    if(cdsc == NULL) return LV_RES_OK;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return LV_RES_OK;
    if(cdsc->dec_dsc.header.cf != 1) return LV_RES_OK;
    if(draw_dsc->angle)  return LV_RES_OK;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return LV_RES_OK;
    lv_area_t map_area_rot;
    lv_area_copy(&map_area_rot, coords);
    if (draw_dsc->angle || draw_dsc->zoom != LV_IMG_ZOOM_NONE)
    {
        int32_t w = lv_area_get_width(coords);
        int32_t h = lv_area_get_height(coords);
        _lv_img_buf_get_transformed_area(&map_area_rot, w, h, draw_dsc->angle, draw_dsc->zoom, &draw_dsc->pivot);
        map_area_rot.x1 += coords->x1;
        map_area_rot.y1 += coords->y1;
        map_area_rot.x2 += coords->x1;
        map_area_rot.y2 += coords->y1;
    }
    struct _lv_draw_ctx_t * draw_ctx = draw_buf;
    lv_area_t clip_com;
    bool union_ok;
    union_ok = _lv_area_intersect(&clip_com, draw_ctx->clip_area, &map_area_rot);
    if (union_ok == false)
    {
        draw_cleanup(cdsc);
        return LV_RES_OK;
    }
    const lv_area_t * clip_area_ori = draw_ctx->clip_area;
    draw_ctx->clip_area = &clip_com;
    int load_mef = LOAD_FROM_FLASH_WITH_TAB;
    void * src_addr = &(usr_data->ui_resfile_info);

    // printf("首地址 %x  tabsize offset tablen %d %d %d", usr_data->ui_resfile_info.tab[0], usr_data->ui_resfile_info.tab_size, usr_data->ui_resfile_info.offset, usr_data->ui_resfile_info.last_tab_data_len);

    // put_buf(usr_data->ui_resfile_info.tab[0], 32);

    // printf("file %d ol %d %d wh %d %d", usr_data->img_file.compress, usr_data->img_file.offset, usr_data->img_file.len, usr_data->img_file.width, usr_data->img_file.height
    // );

    struct image_file bframe = {0}; // = &(usr_data->bframe);
    struct image_file dframe = {0}; // = &(usr_data->dframe);
    if(usr_data->img_file.format != PIXEL_FMT_GIF) {
        // memcpy(&bframe, &(usr_data->img_file), sizeof(struct image_file));
    } else {
        bframe.format = LAYER_FORMAT_L8;
        bframe.width  = usr_data->bframe.width;
        bframe.height = usr_data->bframe.height;
        bframe.offset = usr_data->img_file.offset + usr_data->bframe.addr - ((usr_data->bframe.flag&BIT(0))?0:256*4);
        bframe.len    = usr_data->bframe.size;
        bframe.compress = 1;
        dframe.format = LAYER_FORMAT_L8;
        dframe.width  = usr_data->dframe.width;
        dframe.height = usr_data->dframe.height;
        dframe.offset = usr_data->img_file.offset + usr_data->dframe.addr - ((usr_data->dframe.flag&BIT(0))?0:256*4);
        dframe.len    = usr_data->dframe.size;
        dframe.compress = 1;        
    }
    int px = coords->x1; 
    int py = coords->y1; 
    int pw = coords->x2-coords->x1+1; 
    int ph = coords->y2-coords->y1+1;  
    lv_area_t  res_p={0};
    lv_area_t  res_p2={0};
    if(0==(_lv_area_intersect(&res_p, draw_buf->buf_area, draw_buf->clip_area))){
        return LV_RES_OK;  
    }  
    struct rect *crop = image_set_crop( res_p.x1, 
                                res_p.y1, 
                                res_p.x2-res_p.x1+1, 
                                res_p.y2-res_p.y1+1 );   
    struct image_file img_file = {0};
    struct rect rect;
    rect.left = draw_buf->buf_area->x1;
    rect.top = draw_buf->buf_area->y1;
    rect.width = (draw_buf->buf_area->x2) - (draw_buf->buf_area->x1) +1;
    rect.height = (draw_buf->buf_area->y2) - (draw_buf->buf_area->y1) +1;
    if(rect.width < 2) return LV_RES_OK;
    int prw =  draw_dsc->zoom;
    int prh =  draw_dsc->zoom; 
    u16 angle = draw_dsc->angle; 
    int dx = draw_dsc->pivot.x;
    int dy = draw_dsc->pivot.y;   
    void *buf = draw_buf->buf;  
    int bufsize = rect.width*rect.height*2; 
    int xoffset = 0;
    int yoffset = 0;
    xoffset = rect.left;
    yoffset = rect.top;
    px = px - xoffset;
    py = py - yoffset;
    crop->left -= xoffset;
    crop->top -= yoffset;
    rect.left -= xoffset;
    rect.top -= yoffset;
    int compx = 0;
    int compy = 0;
    if(dy-yoffset<compy)compy = dy-yoffset;
    if(dx-xoffset<compx)compx = dx-xoffset;
    if(py+dy<compy)compy = py+dy;
    if(px+dx<compx)compx = px+dx;

    if(usr_data->img_file.format == PIXEL_FMT_JPEG){

        // usr_data->fd->var = 0x410;
        struct gif_file_info gifinfo = {0};
        static int id = 1;
        if(usr_data->nowid==0){
            usr_data->nowid = 1;
        }
        id = usr_data->nowid;
        open_image_by_id(0, usr_data->fd, &(usr_data->img_file), id & 0xffff, id >> 16);
        // id++;
        // if(id>374)id = 1;

        //  资源ID所在FLASH存储
        struct flash_file_info tmp_file_info = {0};
        int lut_tab_offset = 0;
        struct flash_file_info *info = &(usr_data->ui_resfile_info);
        struct flash_file_info *flash_info = &tmp_file_info;
        struct image_file * f = &(usr_data->img_file);
        int filelen = f->len;
        flash_info->tab = &info->tab[(f->offset + info->offset + lut_tab_offset) / 4096];
        int file_base_addr = flash_info->tab[0] + (f->offset + info->offset + lut_tab_offset) % 4096;
        int flash_map_tab_num = (file_base_addr % 4096 + filelen + 4096 - 1) / 4096;
        flash_info->offset = file_base_addr % 4096;
        flash_info->tab_size = flash_map_tab_num * sizeof(u32);
        flash_info->last_tab_data_len = flash_map_tab_num * 4096 - filelen - flash_info->offset;

        imb_jpg_draw(flash_info, draw_buf, coords, NULL, draw_ctx->clip_area);
        return LV_RES_OK;
    }

    int imb_task_get_id = 0;
    struct imb_task_info imb_tsk_info = {0};
    imb_tsk_info.data_src       = DATA_SRC_NONE;
    imb_tsk_info.zip_en         = 0;
    imb_tsk_info.in_format      = LAYER_FORMAT_SOLID;
    imb_tsk_info.out_format     = OUTPUT_FORMAT_RGB565;
    imb_tsk_info.x_offset       = compx;
    imb_tsk_info.y_offset       = compy;
    imb_tsk_info.src_w          = rect.width - compx;
    imb_tsk_info.src_h          = rect.height - compy;
    imb_tsk_info.des_w          = rect.width - compx;
    imb_tsk_info.des_h          = rect.height - compy;
    imb_tsk_info.priv           = 0;
    imb_tsk_info.osd0_in_buf    = 1;
    imb_task_list_init(imb_task_head_get(0), &imb_tsk_info);
    if(LV_IMG_ZOOM_NONE != prw || LV_IMG_ZOOM_NONE != prh ){   
        // imb_create_image_scale_task(++imb_task_get_id, &file,  src_addr, 
        //     (float)prw/(float)LV_IMG_ZOOM_NONE, (float)prh/(float)LV_IMG_ZOOM_NONE,
        //     px+dx*(LV_IMG_ZOOM_NONE-prw)/LV_IMG_ZOOM_NONE, 
        //     py+dy*(LV_IMG_ZOOM_NONE-prh)/LV_IMG_ZOOM_NONE, 
        //     pw*prw/LV_IMG_ZOOM_NONE,ph*prh/LV_IMG_ZOOM_NONE,
        //     NULL, file.compress, load_mef);         
    } else{    
        if(usr_data->img_file.format != PIXEL_FMT_GIF){
            // printf("%s %d", __func__, __LINE__);
            imb_create_image_task(++imb_task_get_id, &(usr_data->img_file), src_addr, 
                px,py,pw,ph,
                crop, usr_data->img_file.compress, load_mef, draw_dsc->recolor);//width,height参数可小于file.width, file.height,若小于则裁剪 
        } else {
            // printf("%s %d", __func__, __LINE__);
            struct imb_task *p_task = imb_create_gif_frame_task(imb_task_head_get(0), ++imb_task_get_id, 0, &bframe, src_addr, 
                px + usr_data->bframe.x, py + usr_data->bframe.y, pw,ph, 
                crop, bframe.compress, 1);
            if(usr_data->dframe.curr_index != usr_data->bframe.curr_index) {
                // printf("%s %d", __func__, __LINE__);
                struct imb_task *p_task2 = imb_create_gif_frame_task(imb_task_head_get(0), ++imb_task_get_id, 0, &dframe, src_addr, 
                    px + usr_data->dframe.x, py + usr_data->dframe.y, pw,ph, 
                    crop, dframe.compress, 1);
                if(!(usr_data->dframe.flag&BIT(0))){
                    if (p_task2->lut_tab) memcpy(p_task2->lut_tab, usr_data->btub, 256 * 4);
                    if(usr_data->dframe.flag&BIT(1)) p_task2->lut_tab[0xff&(usr_data->dframe.flag>>8)] = 0;
                }  
            }
        }
    }       
    struct lcd_info info = {0};
    static struct bg_buffer bg = {0};
    if (__this->lcd->get_screen_info) {
        __this->lcd->get_screen_info(&info);
    }
    struct rect disp;
    struct rect page_draw = {0};
    struct rect screen_rect;
    screen_rect.left = 0;
    screen_rect.top = 0;
    screen_rect.width = rect.width;
    screen_rect.height = rect.height;
    rect.left  = 0;
    rect.top = 0;
    u16 bg_stride = (rect.width * 2 + 3) / 4 * 4;
    // printf("%s %d", __func__, __LINE__);
    imb_task_head_set_buf(imb_task_head_get(0), buf, NULL, rect.width, rect.height, bg_stride, rect.height, NULL);
    imb_task_head_config(imb_task_head_get(0), &rect, &screen_rect, &screen_rect, &page_draw, STATE_SYNTHESIS_AND_DRAW);
    struct imb_cb_interface itf = {0};
    usr_buf = buf;
    itf.buf_get = usr_buf_get;
    itf.buf_check = usr_buf_check;
    itf.buf_set_idle = usr_buf_set_idle;
    itf.buf_set_pending = usr_buf_set_pending;
    itf.buf_wait_finish = usr_buf_wait_finish;
    itf.draw_area = usr_draw_area;
    itf.draw_meld_area = usr_draw_meld_area;
    int a = jiffies_half_msec();// TICK_CNT;
    int aa = TICK_CNT;//jiffies_half_msec();
    // imb_task_info_dump(imb_task_head_get(0));
    imb_start(imb_task_head_get(0), &screen_rect, disp, rect.width, rect.height, &itf );
    // printf("%s %d", __func__, __LINE__);
    int bb = TICK_CNT;//jiffies_half_msec();
    int b = jiffies_half_msec();// TICK_CNT;
    imb_task_all_destroy(imb_task_head_get(0));
    int ee = TICK_CNT;
    draw_ctx->clip_area = clip_area_ori;
    draw_cleanup(cdsc);
    return LV_RES_OK;
}


static struct imb_task *imb_create_gif_frame_task(struct imb_task_head *root, int elm_id, int id, struct image_file *file, u32 priv, int x, int y, int width, int height, struct rect *crop, int zip, int data_in_falsh)
{
    struct imb_task_info imb_tsk_info = {0};
    struct imb_task *p = NULL;
    imb_tsk_info.elm_id = elm_id;
    imb_tsk_info.id = id;
    imb_tsk_info.zip_en = zip;
    if (data_in_falsh == 0) {
        imb_tsk_info.data_src = DATA_SRC_SRAM;
        imb_tsk_info.cur_in_flash = 0;
        if (((u32)priv >= 0x2000000) && ((u32)priv < 0x3000000)) {
            imb_tsk_info.addr_source = SOURCE_PSRAM;
        } else {
            imb_tsk_info.addr_source = SOURCE_DEFAULT;
        }
    } else {
        imb_tsk_info.data_src = DATA_SRC_FLASH;
        imb_tsk_info.cur_in_flash = 1;
        imb_tsk_info.addr_source = SOURCE_DEFAULT;
    }
    imb_tsk_info.in_format = file->format;
    imb_tsk_info.x_offset = x;
    imb_tsk_info.y_offset = y;
    imb_tsk_info.src_w = file->width;
    imb_tsk_info.src_h = file->height;
    imb_tsk_info.des_w = width;
    imb_tsk_info.des_h = height;
    if (data_in_falsh == 0) {
        imb_tsk_info.priv = (u32)priv;
    } else {
        imb_tsk_info.ff_info = priv;
        imb_tsk_info.priv = (u32)file;
    }
    //裁剪区域
    if (crop) {
        imb_tsk_info.crop.left = crop->left;
        imb_tsk_info.crop.top = crop->top;
        imb_tsk_info.crop.width = crop->width;
        imb_tsk_info.crop.height = crop->height;
    }
    /* elm_id、id(低8位有效)可作为任务的唯一标识，通过该标识搜索任务句柄，若搜到则重置任务信息，没搜到则创建任务 */
    p = imb_task_search_by_id(root, imb_tsk_info.elm_id, imb_tsk_info.id);
    if (p) {
        if (p->flash_file_info) {
            imb_free(p->flash_file_info);
            p->flash_file_info = NULL;
        }
        imb_task_reset(root, p, &imb_tsk_info); //imb_task参数重置
    } else {
        p = imb_task_list_add(root, &imb_tsk_info);
    }
    return p;
}

static void draw_cleanup(_lv_img_cache_entry_t * cache)
{
    /*Automatically close images with no caching*/
#if LV_IMG_CACHE_DEF_SIZE == 0
    lv_img_decoder_close(&cache->dec_dsc);
#else
    LV_UNUSED(cache);
#endif
}