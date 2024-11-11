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


void setup_scr_screen_call(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_call
	ui->screen_call = lv_obj_create(page);
	lv_obj_set_size(ui->screen_call, 320, 172);

	//Write style for screen_call, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_cont_call
	ui->screen_call_cont_call = lv_obj_create(ui->screen_call);
	lv_obj_clear_flag(ui->screen_call_cont_call, LV_OBJ_FLAG_SCROLLABLE);	//电话界面-禁止触摸滑动
	lv_obj_set_pos(ui->screen_call_cont_call, 0, 0);
	lv_obj_set_size(ui->screen_call_cont_call, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_call_cont_call, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_call_cont_call, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_call_cont_call, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_call_cont_call, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_call_cont_call, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_img_bg
	ui->screen_call_animimg_call_bg = lv_animimg_create(ui->screen_call_cont_call);
	lv_animimg_set_src(ui->screen_call_animimg_call_bg, (const void **) screen_loop_img_bg_imgs, 1);
	lv_animimg_set_duration(ui->screen_call_animimg_call_bg, 1000);
#if EXTERN_ANIMING
	usr_update_animing(ui->screen_call_animimg_call_bg, "CBG");
#endif
	lv_animimg_set_repeat_count(ui->screen_call_animimg_call_bg, LV_ANIM_REPEAT_INFINITE);
	lv_animimg_start(ui->screen_call_animimg_call_bg);
	lv_obj_set_pos(ui->screen_call_animimg_call_bg, 0, 0);
	lv_obj_set_size(ui->screen_call_animimg_call_bg, 320, 172);

	//Write codes screen_call_cont_call_incoming
	ui->screen_call_cont_call_incoming = lv_obj_create(ui->screen_call_cont_call);
	lv_obj_set_pos(ui->screen_call_cont_call_incoming, 0, 0);
	lv_obj_set_size(ui->screen_call_cont_call_incoming, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_call_cont_call_incoming, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_call_cont_call_incoming, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_call_cont_call_incoming, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_call_cont_call_incoming, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_call_cont_call_incoming, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_call_cont_call_incoming, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_call_cont_call_incoming, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_call_cont_call_incoming, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_call_cont_call_incoming, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_call_cont_call_incoming, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_label_incoming_title
	ui->screen_call_label_incoming_title = lv_label_create(ui->screen_call_cont_call_incoming);
	lv_label_set_text(ui->screen_call_label_incoming_title, "来电");
	lv_label_set_long_mode(ui->screen_call_label_incoming_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_call_label_incoming_title, 105, 16);
	lv_obj_set_size(ui->screen_call_label_incoming_title, 109, 47);

	//Write style for screen_call_label_incoming_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_call_label_incoming_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_call_label_incoming_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_call_label_incoming_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_call_label_incoming_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_call_label_incoming_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_img_incoming_hang_up
	ui->screen_call_img_incoming_hang_up = lv_img_create(ui->screen_call_cont_call_incoming);
	lv_obj_add_flag(ui->screen_call_img_incoming_hang_up, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_call_img_incoming_hang_up, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_guaduan.png");
#else
	lv_img_set_src(ui->screen_call_img_incoming_hang_up, "F:/ic_guaduan.bin");
#endif
	lv_img_set_pivot(ui->screen_call_img_incoming_hang_up, 50,50);
	lv_img_set_angle(ui->screen_call_img_incoming_hang_up, 0);
	lv_obj_set_pos(ui->screen_call_img_incoming_hang_up, 54, 63);
	lv_obj_set_size(ui->screen_call_img_incoming_hang_up, 62, 62);

	//Write style for screen_call_img_incoming_hang_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_call_img_incoming_hang_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_img_incoming_answer
	ui->screen_call_img_incoming_answer = lv_img_create(ui->screen_call_cont_call_incoming);
	lv_obj_add_flag(ui->screen_call_img_incoming_answer, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_call_img_incoming_answer, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jieting.png");
#else
	lv_img_set_src(ui->screen_call_img_incoming_answer, "F:/ic_jieting.bin");
#endif
	lv_img_set_pivot(ui->screen_call_img_incoming_answer, 50,50);
	lv_img_set_angle(ui->screen_call_img_incoming_answer, 0);
	lv_obj_set_pos(ui->screen_call_img_incoming_answer, 206, 63);
	lv_obj_set_size(ui->screen_call_img_incoming_answer, 62, 62);

	//Write style for screen_call_img_incoming_answer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_call_img_incoming_answer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_cont_call_answering
	ui->screen_call_cont_call_answering = lv_obj_create(ui->screen_call_cont_call);
	lv_obj_set_pos(ui->screen_call_cont_call_answering, 0, 0);
	lv_obj_set_size(ui->screen_call_cont_call_answering, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_call_cont_call_answering, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_call_cont_call_answering, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_call_cont_call_answering, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_call_cont_call_answering, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_call_cont_call_answering, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_call_cont_call_answering, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_call_cont_call_answering, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_call_cont_call_answering, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_call_cont_call_answering, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_call_cont_call_answering, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_call_cont_call_answering, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_img_answering_hang_up
	ui->screen_call_img_answering_hang_up = lv_img_create(ui->screen_call_cont_call_answering);
	lv_obj_add_flag(ui->screen_call_img_answering_hang_up, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_call_img_answering_hang_up, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_guaduan.png");
#else
	lv_img_set_src(ui->screen_call_img_answering_hang_up, "F:/ic_guaduan.bin");
#endif
	lv_img_set_pivot(ui->screen_call_img_answering_hang_up, 50,50);
	lv_img_set_angle(ui->screen_call_img_answering_hang_up, 0);
	lv_obj_set_pos(ui->screen_call_img_answering_hang_up, 54, 63);
	lv_obj_set_size(ui->screen_call_img_answering_hang_up, 62, 62);

	//Write style for screen_call_img_answering_hang_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_call_img_answering_hang_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_img_answering_mute
	ui->screen_call_img_answering_mute = lv_img_create(ui->screen_call_cont_call_answering);
	lv_obj_add_flag(ui->screen_call_img_answering_mute, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_call_img_answering_mute, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jingyin.png");
#else
	lv_img_set_src(ui->screen_call_img_answering_mute, "F:/ic_jingyin.bin");
#endif
	lv_img_set_pivot(ui->screen_call_img_answering_mute, 50,50);
	lv_img_set_angle(ui->screen_call_img_answering_mute, 0);
	lv_obj_set_pos(ui->screen_call_img_answering_mute, 206, 63);
	lv_obj_set_size(ui->screen_call_img_answering_mute, 62, 62);

	//Write style for screen_call_img_answering_mute, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_call_img_answering_mute, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_call_answering_time
	ui->screen_call_answering_time = lv_label_create(ui->screen_call_cont_call_answering);
	lv_label_set_text(ui->screen_call_answering_time, "0:30");
	lv_label_set_long_mode(ui->screen_call_answering_time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_call_answering_time, 113, 52);
	lv_obj_set_size(ui->screen_call_answering_time, 100, 32);

	//Write style for screen_call_answering_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_call_answering_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_call_answering_time, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_call_answering_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_call_answering_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_call_answering_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_call);

	
}

