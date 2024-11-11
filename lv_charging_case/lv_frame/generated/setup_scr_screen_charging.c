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


void setup_scr_screen_charging(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_charging
	ui->screen_charging = lv_obj_create(page);
	lv_obj_set_size(ui->screen_charging, 320, 172);

	//Write style for screen_charging, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_charging_cont_charging
	ui->screen_charging_cont_charging = lv_obj_create(ui->screen_charging);
	lv_obj_clear_flag(ui->screen_charging_cont_charging, LV_OBJ_FLAG_SCROLLABLE);	//������-��ֹ��������
	lv_obj_set_pos(ui->screen_charging_cont_charging, 0, 0);
	lv_obj_set_size(ui->screen_charging_cont_charging, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_charging_cont_charging, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_charging_cont_charging, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_charging_cont_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_charging_cont_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_charging_cont_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_charging_cont_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_charging_cont_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_charging_cont_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_charging_cont_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_charging_cont_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_charging_animimg_charging
	ui->screen_charging_animimg_charging = lv_animimg_create(ui->screen_charging_cont_charging);
	lv_animimg_set_src(ui->screen_charging_animimg_charging, (const void **) screen_charging_animimg_charging_imgs, 1);
	lv_animimg_set_duration(ui->screen_charging_animimg_charging, 100);
#if EXTERN_ANIMING
	usr_update_animing(ui->screen_charging_animimg_charging, "CHG");
#endif
	lv_animimg_set_repeat_count(ui->screen_charging_animimg_charging, LV_ANIM_REPEAT_INFINITE);
	lv_animimg_start(ui->screen_charging_animimg_charging);
	lv_obj_set_pos(ui->screen_charging_animimg_charging, 0, 0);
	lv_obj_set_size(ui->screen_charging_animimg_charging, 320, 172);

	//Write codes screen_charging_label_charging
	ui->screen_charging_label_charging = lv_label_create(ui->screen_charging_cont_charging);
	lv_label_set_text(ui->screen_charging_label_charging, "90%");
	lv_label_set_long_mode(ui->screen_charging_label_charging, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_charging_label_charging, 110, 76);
	lv_obj_set_size(ui->screen_charging_label_charging, 100, 32);

	//Write style for screen_charging_label_charging, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_charging_label_charging, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_charging_label_charging, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_charging_label_charging, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_charging_label_charging, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_charging_label_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_charging);

	
}


