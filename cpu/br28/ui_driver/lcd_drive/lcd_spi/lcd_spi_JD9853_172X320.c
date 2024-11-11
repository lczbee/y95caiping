/*
** 包含board的头文件，确定baord里面开关的屏驱宏
*/
#include "app_config.h"


/*
** 驱动代码的宏开关
*/
//<<<[4-fire屏 173x240]>>>//
#if TCFG_LCD_JD9853_320X147



// #define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE0_1T8B
/* #define LCD_DRIVE_CONFIG                    QSPI_RGB565_SUBMODE1_1T2B */
#define LCD_DRIVE_CONFIG                   SPI_4WIRE_RGB565_1T8B/* SPI_4WIRE_RGB565_1T8B */ /* QSPI_RGB565_SUBMODE1_1T2B */

/*
** 包含imd头文件，屏驱相关的变量和结构体都定义在imd.h
*/
#include "asm/imd.h"
#include "asm/imb.h"
#include "includes.h"
#include "ui/ui_api.h"


#if 1
#define SCR_X 34
#define SCR_Y 0//34
#define SCR_W 320//320
#define SCR_H 172//172
#define LCD_W 320//320
#define LCD_H 172//172
#define LCD_BLOCK_W 172//320
#if (defined(TCFG_SMART_VOICE_ENABLE) && (TCFG_SMART_VOICE_ENABLE == 1))
#define LCD_BLOCK_H 20
#else /*TCFG_SMART_VOICE_ENABLE == 0*/
#define LCD_BLOCK_H 320
#endif /*TCFG_SMART_VOICE_ENABLE*/
#define BUF_NUM 2
#else
#define SCR_X 0
#define SCR_Y 0//34
#define SCR_W 320
#define SCR_H 172
#define LCD_W 320
#define LCD_H 172
#define LCD_BLOCK_W 320
#if (defined(TCFG_SMART_VOICE_ENABLE) && (TCFG_SMART_VOICE_ENABLE == 1))
#define LCD_BLOCK_H 20
#else /*TCFG_SMART_VOICE_ENABLE == 0*/
#define LCD_BLOCK_H 40
#endif /*TCFG_SMART_VOICE_ENABLE*/
#define BUF_NUM 2
#endif



#if (TCFG_PSRAM_DEV_ENABLE)
#define LCD_FORMAT OUTPUT_FORMAT_RGB565
#else
#define LCD_FORMAT OUTPUT_FORMAT_RGB565
#endif




/*
** 初始化代码
*/
static const u8 lcd_spi_sh8601a_cmd_list_poweron[] ALIGNED(4) = {
    _BEGIN_, 0xDF,0x98,0x53, _END_,
    _BEGIN_, 0XB2,0X23, _END_,
    _BEGIN_, 0xB7,0x00,0x47,0x00,0x6F, _END_,
    _BEGIN_, 0xBB,0x2F,0x9A,0x55,0x73,0x6F,0xF0, _END_,
    _BEGIN_, 0xC0,0x22,0x22, _END_,
    _BEGIN_, 0xC1,0x12, _END_,
    _BEGIN_, 0xC3,0x7D,0x07,0x14,0x06,0xCF,0x71,0x72,0x77, _END_,
    _BEGIN_, 0xC4,0x00,0x00,0xA0,0x79,0x0B,0x0A,0x16,0x79,0x0B,0x0A,0x16,0x82,_END_,
    _BEGIN_, 0xC8,0x3F,0x32,0x29,0x29,0x27,0x2B,0x27,0x28,0x28,0x26,0x25,0x17,0x12,0x0D,0x04,0x00,0x3F,0x32,0x29,0x29,0x27,0x2B,0x27,0x28,0x28,0x26,0x25,0x17,0x12,0x0D,0x04,0x00,_END_,
    _BEGIN_, 0xD0,0x04,0x06,0x6B,0x0F,0x00,_END_,
    _BEGIN_, 0xD7,0x00,0x30,_END_,
    _BEGIN_, 0xE6,0x04,_END_,
    _BEGIN_, 0xDE,0x01,_END_,
    _BEGIN_, 0xB7,0x03,0x13,0xEF,0x35,0x35,_END_,
    _BEGIN_, 0xC1,0x14,0x15,0xC0,_END_,
    // _BEGIN_, 0xC2,0x06,0x3A,0xE7,_END_,
    _BEGIN_, 0xC4,0x72,0x12,_END_,
    _BEGIN_, 0xBE,0x00,_END_,
    _BEGIN_, 0xDE,0x00,_END_,
    _BEGIN_, 0x35,0x00,_END_,
    _BEGIN_, 0x3A,0x05,_END_,
    _BEGIN_, 0x2A,0x00,0x22,0x00,0xCD,_END_,
    _BEGIN_, 0x2B,0x00,0x00,0x01,0x3F,_END_,
    _BEGIN_, 0xC4,0x00,0x00,0xA0,0x79,0x0B,_END_,

    _BEGIN_, 0x11,_END_,
    _BEGIN_, REGFLAG_DELAY,120,_END_,
    _BEGIN_, 0x29,_END_,
    _BEGIN_, REGFLAG_DELAY,50,_END_,
};


static const u8 lcd_cmd_list_sleepout[] ALIGNED(4) = {
//     _BEGIN_, 0xc0, 0x5a, 0x5a, _END_,
//     _BEGIN_, 0xc1, 0x5a, 0x5a, _END_,

// #if (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB565)
//     _BEGIN_, 0x3A, 0x55, _END_,
// #elif (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB666)
//     _BEGIN_, 0x3A, 0x66, _END_,
// #elif (OUT_FORMAT(LCD_DRIVE_CONFIG) == FORMAT_RGB888)
//     _BEGIN_, 0x3A, 0x77, _END_,
// #endif

//     _BEGIN_, 0x44, 0, 0, _END_,
//     _BEGIN_, 0x35, 0x00, _END_,
//     _BEGIN_, 0xb0, 0x16, _END_,
//     _BEGIN_, 0xb1, 0x01, 0x05, 0x00, 0xa2, 0x00, 0xa7, 0x00, 0xa7, 0x00, _END_,
//     _BEGIN_, 0x53, 0x28, _END_,
//     _BEGIN_, 0xc4, 0x80, _END_,

//     _BEGIN_, 0xb1, 0xc0, _END_,

//     _BEGIN_, 0xc0, 0xa5, 0xa5, _END_,
//     _BEGIN_, 0xc1, 0xa5, 0xa5, _END_,
};


extern struct lcd_spi_platform_data *lcd_get_platform_data();

void lcd_send_cmd_enable()
{
//     u8 para[2];
//     para[0] = 0x5a;
//     para[1] = 0x5a;
//     lcd_write_cmd(0xc0, para, 2);
//     lcd_write_cmd(0xc1, para, 2);
}

void lcd_send_cmd_disable()
{
    // u8 para[2];
    // para[0] = 0xa5;
    // para[1] = 0xa5;
    // lcd_write_cmd(0xc0, para, 2);
    // lcd_write_cmd(0xc1, para, 2);
}

static void lcd_adjust_display_brightness(u8 percent)
{
     gpio_set_die(TCFG_BACKLIGHT_PWM_IO, 1);

    gpio_set_output_value(TCFG_BACKLIGHT_PWM_IO, 1);
    gpio_set_direction(TCFG_BACKLIGHT_PWM_IO, 0);
    // u16 brightness;
    // u8 para[2];

    // brightness = percent * 0x3ff / 100;

    // para[0] = brightness & 0xff;
    // para[1] = (brightness >> 8) & 0x3;

    // lcd_write_cmd(0x51, para, 2);
    /* lcd_write_cmd(0x4a, para, 2); //Brightness Value of AOD Mode, 无效果 */
    /* lcd_write_cmd(0x63, para, 2); //Brightness Value of HBM Mode, 无效果 */
}

/*
** lcd背光控制
** 考虑到手表应用lcd背光控制需要更灵活自由，可能需要pwm调光，随时亮灭等
** 因此内部不操作lcd背光，全部由外部自行控制
*/
static int lcd_spi_sh8601a_backlight_ctrl(u8 percent)
{
    y_printf("%s\n", __func__);
    gpio_set_die(TCFG_BACKLIGHT_PWM_IO, 1);

    gpio_set_output_value(TCFG_BACKLIGHT_PWM_IO, 1);
    gpio_set_direction(TCFG_BACKLIGHT_PWM_IO, 0);
    // if (percent) {
    //     lcd_write_cmd(0x29, NULL, 0);
    //     if (percent <= 20) {
    //         lcd_adjust_display_brightness(1);
    //     } else if (percent <= 40) {
    //         lcd_adjust_display_brightness(3);
    //     } else if (percent <= 60) {
    //         lcd_adjust_display_brightness(6);
    //     } else if (percent <= 80) {
    //         lcd_adjust_display_brightness(10);
    //     } else if (percent <= 100) {
    //         lcd_adjust_display_brightness(100);
    //     }
    //     /* g_printf("lcd backlight percent:%d",percent); */
    // } else {
    //     lcd_write_cmd(0x28, NULL, 0);
    // }

    return 0;
}


/*
** lcd电源控制
*/
static int lcd_spi_sh8601a_power_ctrl(u8 onoff)
{
    lcd_en_ctrl(onoff);
    return 0;
}


#define DEEP_STANDBY  1

/*
** 设置lcd进入睡眠
*/
static void lcd_spi_sh8601a_entersleep(void)
{
    lcd_write_cmd(0x28, NULL, 0);
    delay_2ms(30);
    lcd_write_cmd(0x10, NULL, 0);
    delay_2ms(60);
    u8 dstb = 0x01;
    // u8 data = 0x10;

    lcd_write_cmd(0x4f, &dstb, sizeof(dstb));
    delay_2ms(102 / 2); // delay 120ms
    // // lcd_write_cmd(0x10, NULL, 0);
    struct lcd_platform_data *lcd_dat = lcd_get_platform_data();
    if (lcd_dat->pin_te != NO_CONFIG_PORT) {
        gpio_set_pull_up(lcd_dat->pin_te, 0);
        gpio_set_pull_down(lcd_dat->pin_te, 0);
        gpio_direction_input(lcd_dat->pin_te);
        gpio_set_die(lcd_dat->pin_te, 0);
    }
    // delay_2ms(120 / 2);	// delay 120ms

}



/*
** 设置lcd退出睡眠
*/
static void lcd_spi_sh8601a_exitsleep(void)
{
    y_printf("%s\n",__func__);
#if DEEP_STANDBY
    // struct lcd_platform_data *lcd_dat = lcd_get_platform_data();
    // if (lcd_dat && lcd_dat->pin_reset) {
    //     gpio_direction_output(lcd_dat->pin_reset, 0);
    //     delay_2ms(4);	// delay >5ms
    //     gpio_direction_output(lcd_dat->pin_reset, 1);
    //     delay_2ms(4);	// delay >5ms
    // }
    u8 data = 0x29;
    lcd_write_cmd(0x11, NULL, 1);
    delay_2ms(5);
    lcd_write_cmd(0x29, NULL, 0);
    delay_2ms(5);

    // extern struct imd_param lcd_spi_sh8601a_param;
    // lcd_init(&lcd_spi_sh8601a_param);
    // lcd_drv_cmd_list(lcd_cmd_list_sleepout, sizeof(lcd_cmd_list_sleepout) / sizeof(lcd_cmd_list_sleepout[0]));
#else
    lcd_write_cmd(0x11, NULL, 0);
    delay_2ms(5);	// delay 120ms
    lcd_write_cmd(0x29, NULL, 0);
#endif
}


struct imd_param lcd_spi_sh8601a_param = {
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

    .fps = 70,

    .spi = {
        .spi_mode = SPI_IF_MODE(LCD_DRIVE_CONFIG),
        .pixel_type = PIXEL_TYPE(LCD_DRIVE_CONFIG),
        .out_format = OUT_FORMAT(LCD_DRIVE_CONFIG),
        .port = SPI_PORTA,
        .spi_dat_mode = SPI_MODE_UNIDIR,
    },

    .debug_mode_en = 0,
    .debug_mode_color = 0xff0000,
};
static u32 lcd_spi_sh8601a_read_id()
{
    // u8 id[3];
    // lcd_read_cmd(0x04, id, sizeof(id));
    // return ((id[0] << 16) | (id[1] << 8) | id[2]);
    return 0;
}
REGISTER_LCD_DEVICE(sh8601) = {
    .logo = "sh8601",
    .row_addr_align    = 2,
    .column_addr_align = 2,

    .lcd_cmd = (void *) &lcd_spi_sh8601a_cmd_list_poweron,
    .cmd_cnt = sizeof(lcd_spi_sh8601a_cmd_list_poweron) / sizeof(lcd_spi_sh8601a_cmd_list_poweron[0]),
    .param   = (void *) &lcd_spi_sh8601a_param,

    .reset = NULL,	// 没有特殊的复位操作，用内部普通复位函数即可
    .backlight_ctrl = NULL,//lcd_spi_sh8601a_backlight_ctrl,
    .power_ctrl = lcd_spi_sh8601a_power_ctrl,
    .entersleep = lcd_spi_sh8601a_entersleep,
    .exitsleep = lcd_spi_sh8601a_exitsleep,
	.read_id = NULL,
	.lcd_id = 0x000000,
};
#endif