/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void events_init(lv_ui *ui);

void events_init_screen_music(lv_ui *ui);
void events_init_screen_music_local_music(lv_ui *ui);
void events_init_screen_music_lyrics(lv_ui *ui);
void events_init_screen_volume(lv_ui *ui);
void events_init_screen_anc(lv_ui *ui);
void events_init_screen_equalizer(lv_ui *ui);
void events_init_screen_alarm(lv_ui *ui);
void events_init_screen_brightness(lv_ui *ui);
void events_init_screen_language(lv_ui *ui);
void events_init_screen_wallpaper(lv_ui *ui);
void events_init_screen_squelch(lv_ui *ui);
void events_init_screen_findmy(lv_ui *ui);
void events_init_screen_light(lv_ui *ui);
void events_init_screen_time(lv_ui *ui);
void events_init_screen_time_cont_set(lv_ui *ui);
void events_init_screen_tiktok(lv_ui *ui);
void events_init_screen_tiktok_rejust(lv_ui *ui);
void events_init_screen_snap(lv_ui *ui);
void events_init_screen_charging(lv_ui *ui);
void events_init_screen_poweron(lv_ui *ui);
void events_init_screen_call(lv_ui *ui);
void events_init_screen_lock(lv_ui *ui);
void events_init_screen_product_test(lv_ui *ui);
void events_init_screen_pc_mode(lv_ui *ui);
void events_init_screen_alarm_ring(lv_ui *ui);
void events_init_screen_menu(lv_ui *ui);
void events_init_screen_wooden_fish(lv_ui *ui);
void events_init_screen_weather(lv_ui *ui);
void events_init_screen_pop_up(lv_ui *ui);
void events_init_screen_poweroff(lv_ui *ui);
void events_init_screen_upgrade(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
