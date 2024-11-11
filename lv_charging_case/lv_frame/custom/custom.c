/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
	//初始化外部动画
#if EXTERN_ANIMING
	extern void open_animing_res();
	printf("ANIMNG.........INIT");
	mem_stats();
	open_animing_res();
	mem_stats();
#endif

	// 初始化状态刷新定时器
	lv_screen_refresh_start();
#if LV_LOW_POWER_EN
    uint8_t lowpower_entry_info = 0;
    syscfg_read(LOWPOWER_ENTRY_INFO, &lowpower_entry_info, sizeof(lowpower_entry_info));
	r_printf("screen_poweron_enter lowpower_entry_info:0x%x\n",lowpower_entry_info);
	if(lowpower_entry_info != 0xAA)
	{
		//加载开机画面
		screen_poweron_enter();
	}else{
		screen_lock_enter();
	}
#else
	//加载开机画面
	screen_poweron_enter();
#endif
	// 初始化页面管理器
	screen_loop_enter();
}

