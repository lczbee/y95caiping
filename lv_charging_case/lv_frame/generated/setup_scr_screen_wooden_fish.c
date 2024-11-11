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


void setup_scr_screen_wooden_fish(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_wooden_fish
	ui->screen_wooden_fish = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_wooden_fish, 320, 172);

	//Write style for screen_wooden_fish, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wooden_fish, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wooden_fish_cont_wooden_fish
	ui->screen_wooden_fish_cont_wooden_fish = lv_obj_create(ui->screen_wooden_fish);
	lv_obj_set_pos(ui->screen_wooden_fish_cont_wooden_fish, 0, 0);
	lv_obj_set_size(ui->screen_wooden_fish_cont_wooden_fish, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_wooden_fish_cont_wooden_fish, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_wooden_fish_cont_wooden_fish, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wooden_fish_cont_wooden_fish, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wooden_fish_cont_wooden_fish, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wooden_fish_cont_wooden_fish, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wooden_fish_cont_wooden_fish, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wooden_fish_cont_wooden_fish, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wooden_fish_cont_wooden_fish, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wooden_fish_cont_wooden_fish, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wooden_fish_cont_wooden_fish, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wooden_fish_cont_wooden_fish, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wooden_fish_label_virtue_title
	ui->screen_wooden_fish_label_virtue_title = lv_label_create(ui->screen_wooden_fish_cont_wooden_fish);
	lv_label_set_text(ui->screen_wooden_fish_label_virtue_title, "今日功德");
	lv_label_set_long_mode(ui->screen_wooden_fish_label_virtue_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_wooden_fish_label_virtue_title, 35, 5);
	lv_obj_set_size(ui->screen_wooden_fish_label_virtue_title, 150, 22);

	//Write style for screen_wooden_fish_label_virtue_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wooden_fish_label_virtue_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wooden_fish_label_virtue_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wooden_fish_label_virtue_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wooden_fish_label_virtue_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wooden_fish_label_virtue_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wooden_fish_label_virtue_num
	ui->screen_wooden_fish_label_virtue_num = lv_label_create(ui->screen_wooden_fish_cont_wooden_fish);
	lv_label_set_text(ui->screen_wooden_fish_label_virtue_num, "000");
	lv_label_set_long_mode(ui->screen_wooden_fish_label_virtue_num, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_wooden_fish_label_virtue_num, 180, 5);
	lv_obj_set_size(ui->screen_wooden_fish_label_virtue_num, 100, 22);

	//Write style for screen_wooden_fish_label_virtue_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wooden_fish_label_virtue_num, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wooden_fish_label_virtue_num, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wooden_fish_label_virtue_num, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wooden_fish_label_virtue_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wooden_fish_label_virtue_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wooden_fish_label_cumulate1
	ui->screen_wooden_fish_label_cumulate1 = lv_label_create(ui->screen_wooden_fish_cont_wooden_fish);
	lv_label_set_text(ui->screen_wooden_fish_label_cumulate1, "功德+1");
	lv_label_set_long_mode(ui->screen_wooden_fish_label_cumulate1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_wooden_fish_label_cumulate1, 13, 87);
	lv_obj_set_size(ui->screen_wooden_fish_label_cumulate1, 100, 22);
	lv_obj_add_flag(ui->screen_wooden_fish_label_cumulate1, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_wooden_fish_label_cumulate1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wooden_fish_label_cumulate1, lv_color_hex(0xe4d600), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wooden_fish_label_cumulate1, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wooden_fish_label_cumulate1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wooden_fish_label_cumulate1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wooden_fish_label_cumulate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wooden_fish_label_cumulate2
	ui->screen_wooden_fish_label_cumulate2 = lv_label_create(ui->screen_wooden_fish_cont_wooden_fish);
	lv_label_set_text(ui->screen_wooden_fish_label_cumulate2, "功德+1");
	lv_label_set_long_mode(ui->screen_wooden_fish_label_cumulate2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_wooden_fish_label_cumulate2, 13, 64);
	lv_obj_set_size(ui->screen_wooden_fish_label_cumulate2, 100, 22);
	lv_obj_add_flag(ui->screen_wooden_fish_label_cumulate2, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_wooden_fish_label_cumulate2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wooden_fish_label_cumulate2, lv_color_hex(0xe4d600), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wooden_fish_label_cumulate2, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wooden_fish_label_cumulate2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wooden_fish_label_cumulate2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wooden_fish_label_cumulate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wooden_fish_label_cumulate3
	ui->screen_wooden_fish_label_cumulate3 = lv_label_create(ui->screen_wooden_fish_cont_wooden_fish);
	lv_label_set_text(ui->screen_wooden_fish_label_cumulate3, "功德+1");
	lv_label_set_long_mode(ui->screen_wooden_fish_label_cumulate3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_wooden_fish_label_cumulate3, 13, 53);
	lv_obj_set_size(ui->screen_wooden_fish_label_cumulate3, 100, 22);
	lv_obj_add_flag(ui->screen_wooden_fish_label_cumulate3, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_wooden_fish_label_cumulate3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wooden_fish_label_cumulate3, lv_color_hex(0xe4d600), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wooden_fish_label_cumulate3, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wooden_fish_label_cumulate3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wooden_fish_label_cumulate3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wooden_fish_label_cumulate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wooden_fish_label_cumulate4
	ui->screen_wooden_fish_label_cumulate4 = lv_label_create(ui->screen_wooden_fish_cont_wooden_fish);
	lv_label_set_text(ui->screen_wooden_fish_label_cumulate4, "功德+1");
	lv_label_set_long_mode(ui->screen_wooden_fish_label_cumulate4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_wooden_fish_label_cumulate4, 13, 49);
	lv_obj_set_size(ui->screen_wooden_fish_label_cumulate4, 100, 22);
	lv_obj_add_flag(ui->screen_wooden_fish_label_cumulate4, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_wooden_fish_label_cumulate4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wooden_fish_label_cumulate4, lv_color_hex(0xe4d600), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wooden_fish_label_cumulate4, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wooden_fish_label_cumulate4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wooden_fish_label_cumulate4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wooden_fish_label_cumulate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wooden_fish_img_wooden_fish
	ui->screen_wooden_fish_img_wooden_fish = lv_img_create(ui->screen_wooden_fish_cont_wooden_fish);
	lv_obj_add_flag(ui->screen_wooden_fish_img_wooden_fish, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_wooden_fish_img_wooden_fish, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\wooden_fish.png");
#else
	lv_img_set_src(ui->screen_wooden_fish_img_wooden_fish, "F:/wooden_fish1.bin");
#endif
	lv_img_set_pivot(ui->screen_wooden_fish_img_wooden_fish, 50,50);
	lv_img_set_angle(ui->screen_wooden_fish_img_wooden_fish, 0);
	lv_obj_set_pos(ui->screen_wooden_fish_img_wooden_fish, 0, 0);
	lv_obj_set_size(ui->screen_wooden_fish_img_wooden_fish, 320, 172);

	//Write style for screen_wooden_fish_img_wooden_fish, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_wooden_fish_img_wooden_fish, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_clear_flag(ui->screen_wooden_fish_img_wooden_fish, LV_OBJ_FLAG_GESTURE_BUBBLE);
	lv_obj_add_flag(ui->screen_wooden_fish_img_wooden_fish, LV_OBJ_FLAG_CLICKABLE);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_wooden_fish);

	
}
