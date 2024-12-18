/*
** 包含board的头文件，确定baord里面开关的屏驱宏
*/
#include "app_config.h"
#include "clock_cfg.h"


/*
** 驱动代码的宏开关
*/
//<<<[qspi屏 256x400]>>>//
#if defined(TCFG_LCD_SPI_L_WEA2012_ENABLE) && TCFG_LCD_SPI_L_WEA2012_ENABLE

/* #define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE0_1T8B */
#define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE1_1T2B
/* #define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE2_1T2B */

/*
** 包含imd头文件，屏驱相关的变量和结构体都定义在imd.h
*/
#include "asm/imd.h"
#include "asm/imb.h"
#include "includes.h"
#include "ui/ui_api.h"


/* #define SCR_X 0 */
/* #define SCR_Y 0 */
/* #define SCR_W 356 */
/* #define SCR_H 356 */
/* #define LCD_W 356 */
/* #define LCD_H 356 */
/* #define LCD_BLOCK_W 356 */
/* #define LCD_BLOCK_H 40 */
/* #define BUF_NUM 2 */

#define SCR_X 0
#define SCR_Y 0
#define SCR_W 356
#define SCR_H 400
#define LCD_W 356
#define LCD_H 400
#define LCD_BLOCK_W 356
#define LCD_BLOCK_H 40
#define BUF_NUM 2

#define LCD_FORMAT OUTPUT_FORMAT_RGB565

/*
** 初始化代码
*/
static const u8 lcd_spi_L_WEA2012_cmd_list_poweron[] ALIGNED(4) = {
    _BEGIN_, 0xFF, 0x20, 0x10, 0x10, _END_,
    _BEGIN_, 0x0C, 0x11, _END_,
    _BEGIN_, 0x10, 0x02, _END_,
    _BEGIN_, 0x11, 0x11, _END_,
    _BEGIN_, 0x15, 0x42, _END_,
    _BEGIN_, 0x16, 0x11, _END_,
    _BEGIN_, 0x1A, 0x02, _END_,
    _BEGIN_, 0x1B, 0x11, _END_,
    _BEGIN_, 0x61, 0x80, _END_,
    _BEGIN_, 0x62, 0x80, _END_,
    _BEGIN_, 0x54, 0x44, _END_,
    _BEGIN_, 0x58, 0x88, _END_,
    _BEGIN_, 0x5C, 0xCC, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x10, _END_,
    _BEGIN_, 0x20, 0x80, _END_,
    _BEGIN_, 0x21, 0x81, _END_,
    _BEGIN_, 0x22, 0x31, _END_,
    _BEGIN_, 0x23, 0x20, _END_,
    _BEGIN_, 0x24, 0x11, _END_,
    _BEGIN_, 0x25, 0x11, _END_,
    _BEGIN_, 0x26, 0x12, _END_,
    _BEGIN_, 0x27, 0x12, _END_,
    _BEGIN_, 0x30, 0x80, _END_,
    _BEGIN_, 0x31, 0x81, _END_,
    _BEGIN_, 0x32, 0x31, _END_,
    _BEGIN_, 0x33, 0x20, _END_,
    _BEGIN_, 0x34, 0x11, _END_,
    _BEGIN_, 0x35, 0x11, _END_,
    _BEGIN_, 0x36, 0x12, _END_,
    _BEGIN_, 0x37, 0x12, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x10, _END_,
    _BEGIN_, 0x41, 0x11, _END_,
    _BEGIN_, 0x42, 0x22, _END_,
    _BEGIN_, 0x43, 0x33, _END_,
    _BEGIN_, 0x49, 0x11, _END_,
    _BEGIN_, 0x4A, 0x22, _END_,
    _BEGIN_, 0x4B, 0x33, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x15, _END_,
    _BEGIN_, 0x00, 0x00, _END_,
    _BEGIN_, 0x01, 0x00, _END_,
    _BEGIN_, 0x02, 0x00, _END_,
    _BEGIN_, 0x03, 0x00, _END_,
    _BEGIN_, 0x04, 0x10, _END_,
    _BEGIN_, 0x05, 0x0C, _END_,
    _BEGIN_, 0x06, 0x23, _END_,
    _BEGIN_, 0x07, 0x22, _END_,
    _BEGIN_, 0x08, 0x21, _END_,
    _BEGIN_, 0x09, 0x20, _END_,
    _BEGIN_, 0x0A, 0x33, _END_,
    _BEGIN_, 0x0B, 0x32, _END_,
    _BEGIN_, 0x0C, 0x34, _END_,
    _BEGIN_, 0x0D, 0x35, _END_,
    _BEGIN_, 0x0E, 0x01, _END_,
    _BEGIN_, 0x0F, 0x01, _END_,
    _BEGIN_, 0x20, 0x00, _END_,
    _BEGIN_, 0x21, 0x00, _END_,
    _BEGIN_, 0x22, 0x00, _END_,
    _BEGIN_, 0x23, 0x00, _END_,
    _BEGIN_, 0x24, 0x0C, _END_,
    _BEGIN_, 0x25, 0x10, _END_,
    _BEGIN_, 0x26, 0x20, _END_,
    _BEGIN_, 0x27, 0x21, _END_,
    _BEGIN_, 0x28, 0x22, _END_,
    _BEGIN_, 0x29, 0x23, _END_,
    _BEGIN_, 0x2A, 0x33, _END_,
    _BEGIN_, 0x2B, 0x32, _END_,
    _BEGIN_, 0x2C, 0x34, _END_,
    _BEGIN_, 0x2D, 0x35, _END_,
    _BEGIN_, 0x2E, 0x01, _END_,
    _BEGIN_, 0x2F, 0x01, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x16, _END_,
    _BEGIN_, 0x00, 0x00, _END_,
    _BEGIN_, 0x01, 0x00, _END_,
    _BEGIN_, 0x02, 0x00, _END_,
    _BEGIN_, 0x03, 0x00, _END_,
    _BEGIN_, 0x04, 0x08, _END_,
    _BEGIN_, 0x05, 0x04, _END_,
    _BEGIN_, 0x06, 0x19, _END_,
    _BEGIN_, 0x07, 0x18, _END_,
    _BEGIN_, 0x08, 0x17, _END_,
    _BEGIN_, 0x09, 0x16, _END_,
    _BEGIN_, 0x0A, 0x33, _END_,
    _BEGIN_, 0x0B, 0x32, _END_,
    _BEGIN_, 0x0C, 0x34, _END_,
    _BEGIN_, 0x0D, 0x35, _END_,
    _BEGIN_, 0x0E, 0x01, _END_,
    _BEGIN_, 0x0F, 0x01, _END_,
    _BEGIN_, 0x20, 0x00, _END_,
    _BEGIN_, 0x21, 0x00, _END_,
    _BEGIN_, 0x22, 0x00, _END_,
    _BEGIN_, 0x23, 0x00, _END_,
    _BEGIN_, 0x24, 0x04, _END_,
    _BEGIN_, 0x25, 0x08, _END_,
    _BEGIN_, 0x26, 0x16, _END_,
    _BEGIN_, 0x27, 0x17, _END_,
    _BEGIN_, 0x28, 0x18, _END_,
    _BEGIN_, 0x29, 0x19, _END_,
    _BEGIN_, 0x2A, 0x33, _END_,
    _BEGIN_, 0x2B, 0x32, _END_,
    _BEGIN_, 0x2C, 0x34, _END_,
    _BEGIN_, 0x2D, 0x35, _END_,
    _BEGIN_, 0x2E, 0x01, _END_,
    _BEGIN_, 0x2F, 0x01, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x12, _END_,
    _BEGIN_, 0x00, 0x99, _END_,
    _BEGIN_, 0x2A, 0x28, _END_,
    _BEGIN_, 0x2B, 0x0F, _END_,
    _BEGIN_, 0x2C, 0x16, _END_,
    _BEGIN_, 0x2D, 0x28, _END_,
    _BEGIN_, 0x2E, 0x0F, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0xA0, _END_,
    _BEGIN_, 0x08, 0xDC, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x45, _END_,
    _BEGIN_, 0x03, 0x64, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x42, _END_,
    _BEGIN_, 0x05, 0x2C, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x11, _END_,
    _BEGIN_, 0x50, 0x01, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0x2A, 0x00, 0x00, 0x01, 0x63, _END_,
    _BEGIN_, 0x2B, 0x00, 0x00, 0x01, 0x8F, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x40, _END_,
    _BEGIN_, 0x86, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x12, _END_,
    _BEGIN_, 0x0D, 0x66, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x17, _END_,
    _BEGIN_, 0x39, 0x3C, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x31, _END_,
    _BEGIN_, 0x38, 0x03, _END_, //03
    _BEGIN_, 0x39, 0xF0, _END_,
    _BEGIN_, 0x36, 0x03, _END_,
    _BEGIN_, 0x37, 0xE8, _END_,
    _BEGIN_, 0x34, 0x03, _END_,
    _BEGIN_, 0x35, 0xDA, _END_,
    _BEGIN_, 0x35, 0xCF, _END_,
    _BEGIN_, 0x32, 0x03, _END_,
    _BEGIN_, 0x33, 0xCF, _END_,
    _BEGIN_, 0x33, 0xBA, _END_,
    _BEGIN_, 0x30, 0x03, _END_,
    _BEGIN_, 0x31, 0xC8, _END_,
    _BEGIN_, 0x31, 0xA2, _END_,
    _BEGIN_, 0x2E, 0x03, _END_,
    _BEGIN_, 0x2F, 0xBA, _END_,
    _BEGIN_, 0x2F, 0x8E, _END_,
    _BEGIN_, 0x2C, 0x03, _END_,
    _BEGIN_, 0x2D, 0xAC, _END_,
    _BEGIN_, 0x2D, 0x70, _END_,
    _BEGIN_, 0x2A, 0x03, _END_,
    _BEGIN_, 0x2B, 0xA0, _END_,
    _BEGIN_, 0x2B, 0x52, _END_,
    _BEGIN_, 0x28, 0x03, _END_,
    _BEGIN_, 0x29, 0x70, _END_,
    _BEGIN_, 0x29, 0x3E, _END_,
    _BEGIN_, 0x26, 0x02, _END_,
    _BEGIN_, 0x27, 0xFA, _END_,
    _BEGIN_, 0x24, 0x02, _END_,
    _BEGIN_, 0x25, 0xC2, _END_,
    _BEGIN_, 0x22, 0x02, _END_,
    _BEGIN_, 0x23, 0x80, _END_,
    _BEGIN_, 0x20, 0x02, _END_,
    _BEGIN_, 0x21, 0x53, _END_,
    _BEGIN_, 0x1E, 0x02, _END_,
    _BEGIN_, 0x1F, 0x0E, _END_,
    _BEGIN_, 0x1C, 0x01, _END_,
    _BEGIN_, 0x1D, 0xCF, _END_,
    _BEGIN_, 0x1A, 0x01, _END_,
    _BEGIN_, 0x1B, 0x7B, _END_,
    _BEGIN_, 0x18, 0x01, _END_,
    _BEGIN_, 0x19, 0x3D, _END_,
    _BEGIN_, 0x16, 0x01, _END_,
    _BEGIN_, 0x17, 0x0E, _END_,
    _BEGIN_, 0x14, 0x00, _END_,
    _BEGIN_, 0x15, 0xD0, _END_,
    _BEGIN_, 0x12, 0x00, _END_,
    _BEGIN_, 0x13, 0xA6, _END_,
    _BEGIN_, 0x10, 0x00, _END_,
    _BEGIN_, 0x11, 0x79, _END_,
    _BEGIN_, 0x0E, 0x00, _END_,
    _BEGIN_, 0x0F, 0x72, _END_,
    _BEGIN_, 0x0C, 0x00, _END_,
    _BEGIN_, 0x0D, 0x62, _END_,
    _BEGIN_, 0x0A, 0x00, _END_,
    _BEGIN_, 0x0B, 0x54, _END_,
    _BEGIN_, 0x08, 0x00, _END_,
    _BEGIN_, 0x09, 0x3D, _END_,
    _BEGIN_, 0x06, 0x00, _END_,
    _BEGIN_, 0x07, 0x36, _END_,
    _BEGIN_, 0x04, 0x00, _END_,
    _BEGIN_, 0x05, 0x1C, _END_,
    _BEGIN_, 0x02, 0x00, _END_,
    _BEGIN_, 0x03, 0x09, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x32, _END_,
    _BEGIN_, 0x38, 0x03, _END_, //03
    _BEGIN_, 0x39, 0xF0, _END_,
    _BEGIN_, 0x36, 0x03, _END_,
    _BEGIN_, 0x37, 0xE8, _END_,
    _BEGIN_, 0x34, 0x03, _END_,
    _BEGIN_, 0x35, 0xDA, _END_,
    _BEGIN_, 0x35, 0xCF, _END_,
    _BEGIN_, 0x32, 0x03, _END_,
    _BEGIN_, 0x33, 0xCF, _END_,
    _BEGIN_, 0x33, 0xBA, _END_,
    _BEGIN_, 0x30, 0x03, _END_,
    _BEGIN_, 0x31, 0xC8, _END_,
    _BEGIN_, 0x31, 0xA2, _END_,
    _BEGIN_, 0x2E, 0x03, _END_,
    _BEGIN_, 0x2F, 0xBA, _END_,
    _BEGIN_, 0x2F, 0x8E, _END_,
    _BEGIN_, 0x2C, 0x03, _END_,
    _BEGIN_, 0x2D, 0xAC, _END_,
    _BEGIN_, 0x2D, 0x70, _END_,
    _BEGIN_, 0x2A, 0x03, _END_,
    _BEGIN_, 0x2B, 0xA0, _END_,
    _BEGIN_, 0x2B, 0x52, _END_,
    _BEGIN_, 0x28, 0x03, _END_,
    _BEGIN_, 0x29, 0x70, _END_,
    _BEGIN_, 0x29, 0x3E, _END_,
    _BEGIN_, 0x26, 0x02, _END_,
    _BEGIN_, 0x27, 0xFA, _END_,
    _BEGIN_, 0x24, 0x02, _END_,
    _BEGIN_, 0x25, 0xC2, _END_,
    _BEGIN_, 0x22, 0x02, _END_,
    _BEGIN_, 0x23, 0x80, _END_,
    _BEGIN_, 0x20, 0x02, _END_,
    _BEGIN_, 0x21, 0x53, _END_,
    _BEGIN_, 0x1E, 0x02, _END_,
    _BEGIN_, 0x1F, 0x0E, _END_,
    _BEGIN_, 0x1C, 0x01, _END_,
    _BEGIN_, 0x1D, 0xCF, _END_,
    _BEGIN_, 0x1A, 0x01, _END_,
    _BEGIN_, 0x1B, 0x7B, _END_,
    _BEGIN_, 0x18, 0x01, _END_,
    _BEGIN_, 0x19, 0x3D, _END_,
    _BEGIN_, 0x16, 0x01, _END_,
    _BEGIN_, 0x17, 0x0E, _END_,
    _BEGIN_, 0x14, 0x00, _END_,
    _BEGIN_, 0x15, 0xD0, _END_,
    _BEGIN_, 0x12, 0x00, _END_,
    _BEGIN_, 0x13, 0xA6, _END_,
    _BEGIN_, 0x10, 0x00, _END_,
    _BEGIN_, 0x11, 0x79, _END_,
    _BEGIN_, 0x0E, 0x00, _END_,
    _BEGIN_, 0x0F, 0x72, _END_,
    _BEGIN_, 0x0C, 0x00, _END_,
    _BEGIN_, 0x0D, 0x62, _END_,
    _BEGIN_, 0x0A, 0x00, _END_,
    _BEGIN_, 0x0B, 0x54, _END_,
    _BEGIN_, 0x08, 0x00, _END_,
    _BEGIN_, 0x09, 0x3D, _END_,
    _BEGIN_, 0x06, 0x00, _END_,
    _BEGIN_, 0x07, 0x36, _END_,
    _BEGIN_, 0x04, 0x00, _END_,
    _BEGIN_, 0x05, 0x1C, _END_,
    _BEGIN_, 0x02, 0x00, _END_,
    _BEGIN_, 0x03, 0x09, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x11, _END_,
    _BEGIN_, 0x60, 0x01, _END_,
    _BEGIN_, 0x65, 0x03, _END_,
    _BEGIN_, 0x66, 0x38, _END_,
    _BEGIN_, 0x67, 0x04, _END_,
    _BEGIN_, 0x68, 0x34, _END_,
    _BEGIN_, 0x69, 0x03, _END_,
    _BEGIN_, 0x61, 0x03, _END_,
    _BEGIN_, 0x62, 0x38, _END_,
    _BEGIN_, 0x63, 0x04, _END_,
    _BEGIN_, 0x64, 0x34, _END_,
    _BEGIN_, 0x0A, 0x11, _END_,
    _BEGIN_, 0x0B, 0x14, _END_,
    _BEGIN_, 0x0C, 0x14, _END_,
    _BEGIN_, 0x55, 0x06, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x42, _END_,
    _BEGIN_, 0x05, 0x3D, _END_,
    _BEGIN_, 0x06, 0x03, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x12, _END_,
    _BEGIN_, 0x1F, 0xDC, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x17, _END_,
    _BEGIN_, 0x11, 0xAA, _END_,
    _BEGIN_, 0x16, 0x12, _END_,
    _BEGIN_, 0x0B, 0xC3, _END_,
    _BEGIN_, 0x10, 0x0E, _END_,
    _BEGIN_, 0x14, 0xAA, _END_,
    _BEGIN_, 0x18, 0xA0, _END_,
    _BEGIN_, 0x1A, 0x80, _END_,
    _BEGIN_, 0x1F, 0x80, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x11, _END_,
    _BEGIN_, 0x30, 0xEE, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x12, _END_,
    _BEGIN_, 0x15, 0x0F, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x2D, _END_,
    _BEGIN_, 0x01, 0x3E, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x40, _END_,
    _BEGIN_, 0x83, 0xC4, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x12, _END_,
    _BEGIN_, 0x2B, 0x1E, _END_,
    _BEGIN_, 0x2C, 0x26, _END_,
    _BEGIN_, 0x2E, 0x1E, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x12, _END_,
    _BEGIN_, 0x10, 0x0F, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x18, _END_,
    _BEGIN_, 0x01, 0x01, _END_,
    _BEGIN_, 0x00, 0x1E, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x43, _END_,
    _BEGIN_, 0x03, 0x04, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x50, _END_,
    _BEGIN_, 0x05, 0x08, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x50, _END_,
    _BEGIN_, 0x00, 0xA6, _END_,
    _BEGIN_, 0x01, 0xA6, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x50, _END_,
    _BEGIN_, 0x08, 0x55, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x10, _END_,
    _BEGIN_, 0x0B, 0x43, _END_,
    _BEGIN_, 0x0C, 0x12, _END_,
    _BEGIN_, 0x10, 0x01, _END_,
    _BEGIN_, 0x11, 0x12, _END_,
    _BEGIN_, 0x15, 0x00, _END_,
    _BEGIN_, 0x16, 0x00, _END_,
    _BEGIN_, 0x1A, 0x00, _END_,
    _BEGIN_, 0x1B, 0x00, _END_,
    _BEGIN_, 0x61, 0x00, _END_,
    _BEGIN_, 0x62, 0x00, _END_,
    _BEGIN_, 0x51, 0x11, _END_,
    _BEGIN_, 0x55, 0x55, _END_,
    _BEGIN_, 0x58, 0x00, _END_,
    _BEGIN_, 0x5C, 0x00, _END_,
    _BEGIN_, 0x20, 0x81, _END_,
    _BEGIN_, 0x21, 0x82, _END_,
    _BEGIN_, 0x22, 0x72, _END_,
    _BEGIN_, 0x30, 0x00, _END_,
    _BEGIN_, 0x31, 0x00, _END_,
    _BEGIN_, 0x32, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x10, _END_,
    _BEGIN_, 0x44, 0x44, _END_,
    _BEGIN_, 0x45, 0x55, _END_,
    _BEGIN_, 0x46, 0x66, _END_,
    _BEGIN_, 0x47, 0x77, _END_,
    _BEGIN_, 0x49, 0x00, _END_,
    _BEGIN_, 0x4A, 0x00, _END_,
    _BEGIN_, 0x4B, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x17, _END_,
    _BEGIN_, 0x37, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x15, _END_,
    _BEGIN_, 0x04, 0x08, _END_,
    _BEGIN_, 0x05, 0x04, _END_,
    _BEGIN_, 0x06, 0x1C, _END_,
    _BEGIN_, 0x07, 0x1A, _END_,
    _BEGIN_, 0x08, 0x18, _END_,
    _BEGIN_, 0x09, 0x16, _END_,
    _BEGIN_, 0x24, 0x05, _END_,
    _BEGIN_, 0x25, 0x09, _END_,
    _BEGIN_, 0x26, 0x17, _END_,
    _BEGIN_, 0x27, 0x19, _END_,
    _BEGIN_, 0x28, 0x1B, _END_,
    _BEGIN_, 0x29, 0x1D, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x16, _END_,
    _BEGIN_, 0x04, 0x09, _END_,
    _BEGIN_, 0x05, 0x05, _END_,
    _BEGIN_, 0x06, 0x1D, _END_,
    _BEGIN_, 0x07, 0x1B, _END_,
    _BEGIN_, 0x08, 0x19, _END_,
    _BEGIN_, 0x09, 0x17, _END_,
    _BEGIN_, 0x24, 0x04, _END_,
    _BEGIN_, 0x25, 0x08, _END_,
    _BEGIN_, 0x26, 0x16, _END_,
    _BEGIN_, 0x27, 0x18, _END_,
    _BEGIN_, 0x28, 0x1A, _END_,
    _BEGIN_, 0x29, 0x1C, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x18, _END_,
    _BEGIN_, 0x1F, 0x02, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x18, _END_,
    _BEGIN_, 0x3A, 0x01, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x11, _END_,
    _BEGIN_, 0x08, 0x80, _END_,
    _BEGIN_, 0x09, 0x00, _END_,
    _BEGIN_, 0x6A, 0x10, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0x35, 0x00, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0x3A, 0x05, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x12, _END_,
    _BEGIN_, 0x21, 0xB8, _END_,
    _BEGIN_, 0xFF, 0x20, 0x10, 0x00, _END_,
    _BEGIN_, 0x11, _END_,
    _BEGIN_, REGFLAG_DELAY, 20, _END_,
    _BEGIN_, 0x29, _END_,
    _BEGIN_, REGFLAG_DELAY, 150, _END_,
};


extern struct lcd_spi_platform_data *lcd_get_platform_data();

void lcd_send_cmd_enable()
{
    u8 para[2];
    para[0] = 0x5a;
    para[1] = 0x5a;
    lcd_write_cmd(0xc0, para, 2);
    lcd_write_cmd(0xc1, para, 2);
}

void lcd_send_cmd_disable()
{
    u8 para[2];
    para[0] = 0xa5;
    para[1] = 0xa5;
    lcd_write_cmd(0xc0, para, 2);
    lcd_write_cmd(0xc1, para, 2);
}

static void lcd_adjust_display_brightness(u8 percent)
{
    u16 brightness;
    u8 para[2];

    brightness = percent * 0x3ff / 100;

    para[0] = brightness & 0xff;
    para[1] = (brightness >> 8) & 0x3;

    lcd_write_cmd(0x51, para, 2);
    /* lcd_write_cmd(0x4a, para, 2); //Brightness Value of AOD Mode, 无效果 */
    /* lcd_write_cmd(0x63, para, 2); //Brightness Value of HBM Mode, 无效果 */
}

/*
** lcd背光控制
** 考虑到手表应用lcd背光控制需要更灵活自由，可能需要pwm调光，随时亮灭等
** 因此内部不操作lcd背光，全部由外部自行控制
*/
static int lcd_spi_L_WEA2012_backlight_ctrl(u8 percent)
{
    if (percent) {
        lcd_write_cmd(0x29, NULL, 0);
        if (percent <= 20) {
            lcd_adjust_display_brightness(1);
        } else if (percent <= 40) {
            lcd_adjust_display_brightness(3);
        } else if (percent <= 60) {
            lcd_adjust_display_brightness(6);
        } else if (percent <= 80) {
            lcd_adjust_display_brightness(10);
        } else if (percent <= 100) {
            lcd_adjust_display_brightness(100);
        }
        /* g_printf("lcd backlight percent:%d",percent); */
    } else {
        lcd_write_cmd(0x28, NULL, 0);
    }

    return 0;
}


/*
** lcd电源控制
*/
static int lcd_spi_L_WEA2012_power_ctrl(u8 onoff)
{
    lcd_en_ctrl(onoff);
    return 0;
}



/*
** 设置lcd进入睡眠
*/
static void lcd_spi_L_WEA2012_entersleep(void)
{
    u8 dstb = 0x01;

    lcd_write_cmd(0x28, NULL, 0);
    lcd_write_cmd(0x10, NULL, 0);
    delay_2ms(120 / 2);	// delay 120ms
}



/*
** 设置lcd退出睡眠
*/
static void lcd_spi_L_WEA2012_exitsleep(void)
{
    lcd_write_cmd(0x11, NULL, 0);
    delay_2ms(5);	// delay 120ms
    lcd_write_cmd(0x29, NULL, 0);
}


struct imd_param lcd_spi_L_WEA2012_param = {
    .scr_x    = SCR_X,
    .scr_y	  = SCR_Y,
    .scr_w	  = SCR_W,
    .scr_h	  = SCR_H,

    .in_width  = SCR_W,
    .in_height = SCR_H,
    .in_format = LCD_FORMAT,

    .lcd_width  = LCD_W,
    .lcd_height = LCD_H,

    .lcd_type = LCD_TYPE_SPI,

    .buffer_num = BUF_NUM,
    .buffer_size = LCD_BLOCK_W * LCD_BLOCK_H * 2,

    .fps = 60,

    .spi = {
        .spi_mode = SPI_IF_MODE(LCD_DRIVE_CONFIG),
        .pixel_type = PIXEL_TYPE(LCD_DRIVE_CONFIG),
        .out_format = OUT_FORMAT(LCD_DRIVE_CONFIG),
        .port = SPI_PORTA,
        .spi_dat_mode = SPI_MODE_UNIDIR,
    },

    .debug_mode_en = false,
    .debug_mode_color = 0xff0000,
};

REGISTER_LCD_DEVICE() = {
    .logo = "l-wea2012",
    .row_addr_align    = 4,
    .column_addr_align = 4,

    .lcd_cmd = (void *) &lcd_spi_L_WEA2012_cmd_list_poweron,
    .cmd_cnt = sizeof(lcd_spi_L_WEA2012_cmd_list_poweron) / sizeof(lcd_spi_L_WEA2012_cmd_list_poweron[0]),
    .param   = (void *) &lcd_spi_L_WEA2012_param,

    .reset = NULL,	// 没有特殊的复位操作，用内部普通复位函数即可
    .backlight_ctrl = lcd_spi_L_WEA2012_backlight_ctrl,
    .power_ctrl = lcd_spi_L_WEA2012_power_ctrl,
    .entersleep = lcd_spi_L_WEA2012_entersleep,
    .exitsleep = lcd_spi_L_WEA2012_exitsleep,
};


#endif


