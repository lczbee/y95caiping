/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "smartbox_user_app.h"

#include "gui_guider.h"
#include "events_adapter.h"
#include "events_init.h"
#include "widgets_init.h"

#include "usr_animing.h"

#include "lv_demo_equalizer/lv_demo_equalizer.h"
#include "lv_demo_findmy/lv_demo_findmy.h"
#include "lv_demo_light/lv_demo_light.h"
#include "lv_demo_language/lv_demo_language.h"
#include "lv_demo_brightness/lv_demo_brightness.h"
#include "lv_demo_wallpaper/lv_demo_wallpaper.h"
#include "lv_demo_music/lv_demo_music.h"
#include "lv_demo_music/sd_music_api.h"
#include "lv_demo_anc/lv_demo_anc.h"
#include "lv_demo_time/lv_demo_time.h"
#include "lv_demo_time/time_api.h"
#include "lv_demo_squelch/lv_demo_squelch.h"
#include "lv_demo_status_bar/lv_demo_status_bar_top.h"
#include "lv_demo_status_bar/lv_demo_status_bar_bottom.h"
#include "lv_demo_snap/lv_demo_snap.h"
#include "lv_demo_snap/snap_api.h"
#include "lv_demo_tiktok/lv_demo_tiktok.h"
#include "lv_demo_tiktok/tiktok_api.h"
#include "lv_demo_alarm/lv_demo_alarm.h"
#include "lv_demo_alarm/alarm_api.h"
#include "lv_demo_volume/lv_demo_volume.h"
#include "lv_demo_call/lv_demo_call.h"
#include "lv_demo_lock/lv_demo_lock.h"
#include "lv_demo_charging/lv_demo_charging.h"
#include "lv_demo_poweron/lv_demo_poweron.h"
#include "lv_demo_product_test/lv_demo_product_test.h"
#include "lv_demo_pc_mode/lv_demo_pc_mode.h"
#include "lv_demo_alarm/lv_demo_alarm_ring.h"
#include "lv_demo_menu/lv_demo_menu.h"
#include "lv_demo_wooden_fish/lv_demo_wooden_fish.h"
#include "lv_demo_weather/lv_demo_weather.h"
#include "lv_demo_pop_up/lv_demo_pop_up.h"
#include "lv_demo_upgrade/lv_demo_upgrade.h"
#include "lv_demo_multilingual/lv_demo_multilingual.h"
#include "lv_demo_low_rle_animing/low_rle_animing.h"
#include "math/math_function.h"
#include "message/ui_msg_action.h"

//循环页面管理器
#include "screen_loop_manager/lv_demo_screen_loop.h"
#include "screen_loop_manager/page_adapter.h"

//系统机制
#include "system/device_sleep_control.h"
#include "system/device_refresh_control.h"


void custom_init(lv_ui *ui);



//---------------------------------------------------------------
//                    LVGL应用参数配置
//---------------------------------------------------------------

#define EXTERN_ANIMING	            (1)     // 使用外部动画    
#define POWERON_PLAYTIME	        (3000)  // 开机动画持续时间（毫秒）
#define SCREEN_REFRESH_INTERVAL	    (200)   // 状态刷新时间间隔（毫秒）











//---------------------------------------------------------------
//                        版本信息
//---------------------------------------------------------------
#define BETA_VERSION                (0)

#define FORMAL_F_VERSION_NUMBER	    (2)
#define FORMAL_L_VERSION_NUMBER	    (0)

#define TEST_VERSION                (1)
//---------------------------------------------------------------


//---------------------------------------------------------------
//---------------------------------------------------------------


#ifdef __cplusplus
}
#endif
#endif /* __CUSTOM_H_ */
