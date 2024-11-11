/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef WIDGET_INIT_H
#define WIDGET_INIT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "gui_guider.h"

__attribute__((unused)) void kb_event_cb(lv_event_t *e);
__attribute__((unused)) void ta_event_cb(lv_event_t *e);
#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec);
#endif

extern const char * screen_loop_img_bg_imgs[1];
extern const char * screen_music_animimg_wait_imgs[1];
extern const char * screen_wallpaper_animimg_wp_imgs[1];
extern const lv_img_dsc_t * screen_charging_animimg_charging_imgs[1];
extern const char * screen_poweron_animimg_poweron_imgs[1];
extern const char * screen_call_animimg_call_bg_imgs[1];
extern const char * screen_lock_animimg_lock_imgs[1];
extern const char * screen_alarm_ring_animimg_ring_bg_imgs[1];
extern const char * screen_pop_up_animimg_pop_l_imgs[1];
extern const char * screen_pop_up_animimg_pop_r_imgs[1];

#ifdef __cplusplus
}
#endif
#endif
