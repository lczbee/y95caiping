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


void setup_scr_screen_time(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_time
	ui->screen_time = lv_obj_create(page);
	lv_obj_set_size(ui->screen_time, 320, 172);

	//Write style for screen_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_time); // 使用页面管理模块时，需对页面进行适配
	// lv_page_manager_preempt_page_bg_adapte(ui->screen_time); // 适配为抢断页面

	//Write codes screen_time_cont_time
	ui->screen_time_cont_time = lv_obj_create(ui->screen_time);
	lv_obj_set_pos(ui->screen_time_cont_time, 0, 0);
	lv_obj_set_size(ui->screen_time_cont_time, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_time_cont_time, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_time_cont_time); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_time_cont_time); // 适配为抢断页面

	//Write style for screen_time_cont_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_label_time_set
	ui->screen_time_label_time_set = lv_label_create(ui->screen_time_cont_time);
	lv_label_set_text(ui->screen_time_label_time_set, "设置");
	lv_label_set_long_mode(ui->screen_time_label_time_set, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_time_label_time_set, 112, 118);
	lv_obj_set_size(ui->screen_time_label_time_set, 100, 32);
	lv_obj_add_flag(ui->screen_time_label_time_set, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_time_label_time_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_label_time_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_label_time_set, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_label_time_set, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_label_time_set, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_time_label_time_set, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_time_label_time_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_label_time_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_label_time_set, 116, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_label_time_set, lv_color_hex(0x96428a), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_label_time_set, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_label_time_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_label_time_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_label_time_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_label_time_set, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_label_YMD
	ui->screen_time_label_YMD = lv_label_create(ui->screen_time_cont_time);
	lv_label_set_text(ui->screen_time_label_YMD, "2023/12/27");
	lv_label_set_long_mode(ui->screen_time_label_YMD, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_time_label_YMD, 0, 40);
	lv_obj_set_size(ui->screen_time_label_YMD, 320, 20);

	//Write style for screen_time_label_YMD, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_label_YMD, lv_color_hex(0xb1b1b1), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_label_YMD, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_time_label_YMD, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_label_YMD, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_label_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_label_HMS
	ui->screen_time_label_HMS = lv_label_create(ui->screen_time_cont_time);
	lv_label_set_text(ui->screen_time_label_HMS, "16:01:02");
	lv_label_set_long_mode(ui->screen_time_label_HMS, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_time_label_HMS, 0, 80);
	lv_obj_set_size(ui->screen_time_label_HMS, 320, 24);

	//Write style for screen_time_label_HMS, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_label_HMS, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_label_HMS, &lv_customer_font_pingfangheiti_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_time_label_HMS, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_label_HMS, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_label_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_time);
}

void setup_scr_screen_time_cont_set(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_time_cont_set_YMD
	ui->screen_time_cont_set_YMD = lv_obj_create(ui->screen_time);
	lv_obj_set_pos(ui->screen_time_cont_set_YMD, 0, 0);
	lv_obj_set_size(ui->screen_time_cont_set_YMD, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_time_cont_set_YMD, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_time_cont_set_YMD, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_time_cont_set_YMD, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_cont_set_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_cont_set_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_cont_set_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_cont_set_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_cont_set_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_cont_set_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_cont_set_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_cont_set_YMD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_label_YMD_return
	ui->screen_time_label_YMD_return = lv_label_create(ui->screen_time_cont_set_YMD);
	lv_label_set_text(ui->screen_time_label_YMD_return, "返回");
	lv_label_set_long_mode(ui->screen_time_label_YMD_return, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_time_label_YMD_return, 41, 133);
	lv_obj_set_size(ui->screen_time_label_YMD_return, 100, 32);
	lv_obj_add_flag(ui->screen_time_label_YMD_return, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_time_label_YMD_return, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_label_YMD_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_label_YMD_return, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_label_YMD_return, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_label_YMD_return, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_time_label_YMD_return, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_time_label_YMD_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_label_YMD_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_label_YMD_return, 130, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_label_YMD_return, lv_color_hex(0x5a4b4e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_label_YMD_return, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_label_YMD_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_label_YMD_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_label_YMD_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_label_YMD_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_label_YMD_save
	ui->screen_time_label_YMD_save = lv_label_create(ui->screen_time_cont_set_YMD);
	lv_label_set_text(ui->screen_time_label_YMD_save, "保存");
	lv_label_set_long_mode(ui->screen_time_label_YMD_save, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_time_label_YMD_save, 163, 133);
	lv_obj_set_size(ui->screen_time_label_YMD_save, 100, 32);
	lv_obj_add_flag(ui->screen_time_label_YMD_save, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_time_label_YMD_save, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_label_YMD_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_label_YMD_save, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_label_YMD_save, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_label_YMD_save, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_time_label_YMD_save, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_time_label_YMD_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_label_YMD_save, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_label_YMD_save, 163, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_label_YMD_save, lv_color_hex(0xff9600), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_label_YMD_save, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_label_YMD_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_label_YMD_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_label_YMD_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_label_YMD_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_roller_year
	ui->screen_time_roller_year = lv_roller_create(ui->screen_time_cont_set_YMD);
	lv_roller_set_options(ui->screen_time_roller_year, roller_year, LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->screen_time_roller_year, 3);
	lv_obj_set_pos(ui->screen_time_roller_year, 12, 30);
	lv_obj_set_width(ui->screen_time_roller_year, 90);

	//Write style for screen_time_roller_year, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->screen_time_roller_year, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_roller_year, 13, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_year, lv_color_hex(0xd826cd), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_year, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_year, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_year, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_time_roller_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_roller_year, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_time_roller_year, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_time_roller_year, 115, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_year, lv_color_hex(0x75468b), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_year, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_year, &lv_font_pingfangheiti_bold_16, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_year, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write codes screen_time_roller_month
	ui->screen_time_roller_month = lv_roller_create(ui->screen_time_cont_set_YMD);
	lv_roller_set_options(ui->screen_time_roller_month, roller_month, LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->screen_time_roller_month, 3);
	lv_obj_set_pos(ui->screen_time_roller_month, 112, 30);
	lv_obj_set_width(ui->screen_time_roller_month, 90);

	//Write style for screen_time_roller_month, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->screen_time_roller_month, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_roller_month, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_month, lv_color_hex(0xD826CD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_month, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_month, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_month, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_time_roller_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_roller_month, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_time_roller_month, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_time_roller_month, 115, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_month, lv_color_hex(0x75468B), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_month, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_month, &lv_font_pingfangheiti_bold_16, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_month, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write codes screen_time_roller_day
	ui->screen_time_roller_day = lv_roller_create(ui->screen_time_cont_set_YMD);
	lv_roller_set_options(ui->screen_time_roller_day, roller_day_31, LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->screen_time_roller_day, 3);
	lv_obj_set_pos(ui->screen_time_roller_day, 213, 30);
	lv_obj_set_width(ui->screen_time_roller_day, 90);

	//Write style for screen_time_roller_day, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->screen_time_roller_day, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_roller_day, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_day, lv_color_hex(0xD826CD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_day, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_day, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_day, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_time_roller_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_roller_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_time_roller_day, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_time_roller_day, 115, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_day, lv_color_hex(0x75468B), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_day, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_day, &lv_font_pingfangheiti_bold_16, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_day, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write codes screen_time_cont_set_HMS
	ui->screen_time_cont_set_HMS = lv_obj_create(ui->screen_time);
	lv_obj_set_pos(ui->screen_time_cont_set_HMS, 0, 0);
	lv_obj_set_size(ui->screen_time_cont_set_HMS, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_time_cont_set_HMS, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_time_cont_set_HMS, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_time_cont_set_HMS, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_cont_set_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_cont_set_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_cont_set_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_cont_set_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_cont_set_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_cont_set_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_cont_set_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_cont_set_HMS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_label_HMS_return
	ui->screen_time_label_HMS_return = lv_label_create(ui->screen_time_cont_set_HMS);
	lv_label_set_text(ui->screen_time_label_HMS_return, "返回");
	lv_label_set_long_mode(ui->screen_time_label_HMS_return, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_time_label_HMS_return, 36, 135);
	lv_obj_set_size(ui->screen_time_label_HMS_return, 100, 32);
	lv_obj_add_flag(ui->screen_time_label_HMS_return, LV_OBJ_FLAG_CLICKABLE);


	//Write style for screen_time_label_HMS_return, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_label_HMS_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_label_HMS_return, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_label_HMS_return, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_label_HMS_return, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_time_label_HMS_return, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_time_label_HMS_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_label_HMS_return, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_label_HMS_return, 130, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_label_HMS_return, lv_color_hex(0x5a4b4e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_label_HMS_return, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_label_HMS_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_label_HMS_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_label_HMS_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_label_HMS_return, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_label_HMS_save
	ui->screen_time_label_HMS_save = lv_label_create(ui->screen_time_cont_set_HMS);
	lv_label_set_text(ui->screen_time_label_HMS_save, "保存");
	lv_label_set_long_mode(ui->screen_time_label_HMS_save, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_time_label_HMS_save, 179, 136);
	lv_obj_set_size(ui->screen_time_label_HMS_save, 100, 32);
	lv_obj_add_flag(ui->screen_time_label_HMS_save, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_time_label_HMS_save, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_time_label_HMS_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_time_label_HMS_save, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_label_HMS_save, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_label_HMS_save, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_time_label_HMS_save, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_time_label_HMS_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_label_HMS_save, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_label_HMS_save, 163, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_label_HMS_save, lv_color_hex(0xff9600), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_time_label_HMS_save, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_time_label_HMS_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_time_label_HMS_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_time_label_HMS_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_label_HMS_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_time_roller_sec
	ui->screen_time_roller_sec = lv_roller_create(ui->screen_time_cont_set_HMS);
	lv_roller_set_options(ui->screen_time_roller_sec, roller_min_sec, LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->screen_time_roller_sec, 3);
	lv_obj_set_pos(ui->screen_time_roller_sec, 212, 29);
	lv_obj_set_width(ui->screen_time_roller_sec, 70);

	//Write style for screen_time_roller_sec, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->screen_time_roller_sec, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_roller_sec, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_sec, lv_color_hex(0xD826CD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_sec, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_sec, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_sec, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_time_roller_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_roller_sec, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_time_roller_sec, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_time_roller_sec, 115, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_sec, lv_color_hex(0x75468B), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_sec, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_sec, &lv_font_pingfangheiti_bold_16, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_sec, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write codes screen_time_roller_min
	ui->screen_time_roller_min = lv_roller_create(ui->screen_time_cont_set_HMS);
	lv_roller_set_options(ui->screen_time_roller_min, roller_min_sec, LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->screen_time_roller_min, 3);
	lv_obj_set_pos(ui->screen_time_roller_min, 135, 30);
	lv_obj_set_width(ui->screen_time_roller_min, 70);

	//Write style for screen_time_roller_min, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->screen_time_roller_min, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_roller_min, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_min, lv_color_hex(0xD826CD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_min, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_min, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_min, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_time_roller_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_roller_min, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_time_roller_min, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_time_roller_min, 115, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_min, lv_color_hex(0x75468B), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_min, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_min, &lv_font_pingfangheiti_bold_16, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_min, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write codes screen_time_roller_hour
	ui->screen_time_roller_hour = lv_roller_create(ui->screen_time_cont_set_HMS);
	lv_roller_set_options(ui->screen_time_roller_hour, roller_hour_24, LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->screen_time_roller_hour, 3);
	lv_obj_set_pos(ui->screen_time_roller_hour, 58, 30);
	lv_obj_set_width(ui->screen_time_roller_hour, 70);

	//Write style for screen_time_roller_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->screen_time_roller_hour, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_roller_hour, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_hour, lv_color_hex(0xD826CD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_hour, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_hour, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_hour, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_time_roller_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_roller_hour, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_time_roller_hour, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_time_roller_hour, 115, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_hour, lv_color_hex(0x75468B), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_hour, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_hour, &lv_font_pingfangheiti_bold_16, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_hour, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Write codes screen_time_roller_ampm
	ui->screen_time_roller_ampm = lv_roller_create(ui->screen_time_cont_set_HMS);
	lv_roller_set_options(ui->screen_time_roller_ampm, "AM\nPM", LV_ROLLER_MODE_NORMAL);
	lv_roller_set_visible_row_count(ui->screen_time_roller_ampm, 2);
	lv_obj_set_pos(ui->screen_time_roller_ampm, 0, 46);
	lv_obj_set_width(ui->screen_time_roller_ampm, 50);
	lv_obj_add_flag(ui->screen_time_roller_ampm, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_time_roller_ampm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->screen_time_roller_ampm, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_time_roller_ampm, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_ampm, lv_color_hex(0xD826CD), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_ampm, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_ampm, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_ampm, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_time_roller_ampm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_time_roller_ampm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_time_roller_ampm, Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_time_roller_ampm, 115, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_time_roller_ampm, lv_color_hex(0x75468B), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_time_roller_ampm, lv_color_hex(0xFFFFFF), LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_time_roller_ampm, &lv_font_pingfangheiti_bold_16, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_time_roller_ampm, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_time);

	
}
