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


void setup_scr_screen_pop_up(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_pop_up
	ui->screen_pop_up = lv_obj_create(page);
	lv_obj_set_size(ui->screen_pop_up, 320, 172);

	//Write style for screen_pop_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pop_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pop_up_cont_pop_up
	ui->screen_pop_up_cont_pop_up = lv_obj_create(ui->screen_pop_up);
	lv_obj_set_pos(ui->screen_pop_up_cont_pop_up, 0, 0);
	lv_obj_set_size(ui->screen_pop_up_cont_pop_up, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_pop_up_cont_pop_up, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_pop_up_cont_pop_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pop_up_cont_pop_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pop_up_cont_pop_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pop_up_cont_pop_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pop_up_cont_pop_up, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pop_up_cont_pop_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pop_up_cont_pop_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pop_up_cont_pop_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pop_up_cont_pop_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pop_up_cont_pop_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pop_up_animimg_pop_l
	ui->screen_pop_up_animimg_pop_l = lv_animimg_create(ui->screen_pop_up_cont_pop_up);
	lv_animimg_set_src(ui->screen_pop_up_animimg_pop_l, (const void **) screen_pop_up_animimg_pop_l_imgs, 1);
	lv_animimg_set_duration(ui->screen_pop_up_animimg_pop_l, 100*1);
	lv_animimg_set_repeat_count(ui->screen_pop_up_animimg_pop_l, 1);
	lv_img_set_src(ui->screen_pop_up_animimg_pop_l, screen_pop_up_animimg_pop_l_imgs[0]);
	lv_obj_set_pos(ui->screen_pop_up_animimg_pop_l, 0, 0);
	lv_obj_set_size(ui->screen_pop_up_animimg_pop_l, 160, 160);

	//Write codes screen_pop_up_animimg_pop_r
	ui->screen_pop_up_animimg_pop_r = lv_animimg_create(ui->screen_pop_up_cont_pop_up);
	lv_animimg_set_src(ui->screen_pop_up_animimg_pop_r, (const void **) screen_pop_up_animimg_pop_r_imgs, 1);
	lv_animimg_set_duration(ui->screen_pop_up_animimg_pop_r, 100*1);
	lv_animimg_set_repeat_count(ui->screen_pop_up_animimg_pop_r, 1);
	lv_img_set_src(ui->screen_pop_up_animimg_pop_r, screen_pop_up_animimg_pop_r_imgs[0]);
	lv_obj_set_pos(ui->screen_pop_up_animimg_pop_r, 160, 0);
	lv_obj_set_size(ui->screen_pop_up_animimg_pop_r, 160, 160);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_pop_up);

	
}
