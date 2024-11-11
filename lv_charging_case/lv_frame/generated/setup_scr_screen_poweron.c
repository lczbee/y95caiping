/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_screen_poweron(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_poweron
	ui->screen_poweron = lv_obj_create(page);
	lv_obj_set_size(ui->screen_poweron, 320, 172);

	//Write style for screen_poweron, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_poweron_cont_poweron
	ui->screen_poweron_cont_poweron = lv_obj_create(ui->screen_poweron);
	lv_obj_set_pos(ui->screen_poweron_cont_poweron, 0, 0);
	lv_obj_set_size(ui->screen_poweron_cont_poweron, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_poweron_cont_poweron, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_poweron_cont_poweron, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_poweron_cont_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_poweron_cont_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_poweron_cont_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_poweron_cont_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_poweron_cont_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_poweron_cont_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_poweron_cont_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_poweron_cont_poweron, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_poweron_animimg_poweron
	ui->screen_poweron_animimg_poweron = lv_animimg_create(ui->screen_poweron_cont_poweron);
	lv_animimg_set_src(ui->screen_poweron_animimg_poweron, (const void **) screen_poweron_animimg_poweron_imgs, 1);
	lv_animimg_set_duration(ui->screen_poweron_animimg_poweron, 100);
#if EXTERN_ANIMING
	usr_update_animing(ui->screen_poweron_animimg_poweron, "PWO");
#endif
	lv_animimg_set_repeat_count(ui->screen_poweron_animimg_poweron, LV_ANIM_REPEAT_INFINITE);
	lv_animimg_start(ui->screen_poweron_animimg_poweron);
	lv_obj_set_pos(ui->screen_poweron_animimg_poweron, 0, 0);
	lv_obj_set_size(ui->screen_poweron_animimg_poweron, 320, 172);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_poweron);
}
