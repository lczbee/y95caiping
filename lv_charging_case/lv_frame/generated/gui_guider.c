/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"


void ui_init_style(lv_style_t * style)
{
  if (style->prop_cnt > 1)
    lv_style_reset(style);
  else
    lv_style_init(style);
}

void init_scr_del_flag(lv_ui *ui)
{
  
	ui->screen_music_del = true;
	ui->screen_volume_del = true;
	ui->screen_anc_del = true;
	ui->screen_equalizer_del = true;
	ui->screen_alarm_del = true;
	ui->screen_brightness_del = true;
	ui->screen_language_del = true;
	ui->screen_wallpaper_del = true;
	ui->screen_squelch_del = true;
	ui->screen_findmy_del = true;
	ui->screen_light_del = true;
	ui->screen_time_del = true;
	ui->screen_tiktok_del = true;
	ui->screen_snap_del = true;
	ui->screen_charging_del = true;
	ui->screen_poweron_del = true;
	ui->screen_call_del = true;
	ui->screen_lock_del = true;
	ui->screen_product_test_del = true;
	ui->screen_pc_mode_del = true;
	ui->screen_alarm_ring_del = true;
	ui->screen_menu_del = true;
	ui->screen_wooden_fish_del = true;
	ui->screen_weather_del = true;
	ui->screen_pop_up_del = true;
	ui->screen_poweroff_del = true;
	ui->screen_upgrade_del = true;
}

void setup_ui(lv_ui *ui)
{
  init_scr_del_flag(ui);
//   setup_scr_screen_wallpaper(ui);
//   lv_scr_load(ui->screen_wallpaper);
}
