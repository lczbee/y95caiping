/*
 * @Description: 
 * @Author: HJY
 * @Date: 2024-05-29 15:27:52
 * @LastEditTime: 2024-05-29 15:31:19
 * @LastEditors: HJY
 */
#ifndef __COMM_SETTING_H__
#define __COMM_SETTING_H__

#include "typedef.h"
#include "app_config.h"
#define FUNC_PARAMS_OFFSET      5
#define COMM_SETTING_RESP_BUF_SIZE			(256)

extern char * getselectwallper();

#define COMM_SETTING_VERSION        0X00        //协议版本号
#define SCREEN_SAVER_PATH         (getselectwallper()+sizeof("d:storage/virfat_flash/C")-1)
#define SCREEN_SAVER_PATH_C       (getselectwallper()+2)// "storage/virfat_flash/C/VIE_CST.RES"


enum {
    SET_SCREEN_BRIGHTNESS       = 0X00001,      //屏幕亮度设置
    SET_FLASHLIGHT_SWITECH      = 0X00002,      //手电筒开关
    SET_BIND_DEV_STATUS         = 0X00003,      //绑定设备状态
    SET_FUNC_USAGE_RES          = 0X00004,      //功能使用资源动画表盘
    SET_FUNC_SCREEN_EXT_INFO    = 0X00007,      //屏幕信息
};

enum {
    READ_OPT        = 0x00,
    WRITE_OPT       = 0x01,
    NOTIFY_OPT       = 0x02,

};
enum {
    SCREEN_CIRCLES                = 0x01,   //圆形
    SCREEN_RECTANGLE              = 0x02,   //矩形
    SCREEN_ROUNDED_RECTANGLE      = 0x03,   //圆角矩形

};

enum {
    COMM_SETTING_OP_SUCCESS         = 0X00,
};

enum {
    COMM_SETTING_SCREEN_SAVER         = 0X01,   //屏保
    COMM_SETTING_BOOT_ANIMATION       = 0X02,   //开机动画
};

struct _COMM_SETTING_PARAM
{
    u8 version;
    u16 function;
    u8 func_version;
    u8 func_op;
    u8 *func_params;
    u16 func_params_len;
};

struct _COMM_SETTING_COMM_RESP
{
    u8 result;
    u8 payload_version;
    u16 payload_func;
    u8 func_version;
    u8 func_op;
}__attribute__((packed));


struct _COMM_SETTING_FUNC_USAGE_PARAM
{
    u8 func_code;
    u32 dev_headle;
    u32 file_cluster;
    u16 crc;
    u16 path_len;
    u8 *path_data;
    /* data */
} __attribute__((packed));


struct _COMM_SETTING_SCREEN_EXT_INFO
{
    /* data */
    u8 screen_shape;    //屏幕形状
    u16 screen_radius;         //边缘半径
    u8 screen_color_Alpha;      //填充背景颜色透明度
    u8 screen_color_Red;        //填充背景颜色红色值
    u8 screen_color_Green;      //填充背景颜色绿色值
    u8 screen_color_Blue;       //填充背景颜色蓝色值
    u16 screen_Width;           //屏幕宽度
    u16 screen_Height;          //屏幕高度

} __attribute__((packed));

struct __COMM_SETTING_INFO {
    u8 screen_brightness;
    struct _COMM_SETTING_SCREEN_EXT_INFO screen_ext_info;

};

#endif//__COMM_SETTING_H__

