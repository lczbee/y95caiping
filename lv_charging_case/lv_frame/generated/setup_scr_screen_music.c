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


void setup_scr_screen_music(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_music
	ui->screen_music = lv_obj_create(page);
	lv_obj_set_size(ui->screen_music, 320, 172);

	//Write style for screen_music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_music); // 使用页面管理模块时，需对页面进行适配

	//Write codes screen_music_cont_music
	ui->screen_music_cont_music = lv_obj_create(ui->screen_music);
	lv_obj_set_pos(ui->screen_music_cont_music, 0, 0);
	lv_obj_set_size(ui->screen_music_cont_music, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_music_cont_music, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_music_cont_music); // 使用页面管理模块时，需要对容器进行适配
	// lv_obj_add_flag(ui->screen_music_cont_music, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_music_cont_music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_music_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_music_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_music_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_music_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_music_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_music_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_music_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_imgbtn_music_pre
	ui->screen_music_imgbtn_music_pre = lv_imgbtn_create(ui->screen_music_cont_music);
	lv_obj_add_flag(ui->screen_music_imgbtn_music_pre, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shangyiqu_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shangyiqu_weilianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shangyiqu_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shangyiqu_weilianjie.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_shangyiqu_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_shangyiqu_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_shangyiqu_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_shangyiqu_weilianjie.bin", NULL);

	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_shangyiqu_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_pre, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_shangyiqu_weilianjie.bin", NULL);
#endif
	ui->screen_music_imgbtn_music_pre_label = lv_label_create(ui->screen_music_imgbtn_music_pre);
	lv_label_set_text(ui->screen_music_imgbtn_music_pre_label, "");
	lv_label_set_long_mode(ui->screen_music_imgbtn_music_pre_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_music_imgbtn_music_pre_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_music_imgbtn_music_pre, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_music_imgbtn_music_pre, 37, 55);
	lv_obj_set_size(ui->screen_music_imgbtn_music_pre, 60, 60);
	lv_page_manager_obj_adapte(ui->screen_music_imgbtn_music_pre); // 传递消息给父控件

	//Write style for screen_music_imgbtn_music_pre, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_pre, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_music_imgbtn_music_pre, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_pre, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_music_imgbtn_music_pre, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_pre, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_pre, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_pre, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_music_imgbtn_music_pre, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_pre, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_pre, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_pre, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_music_imgbtn_music_pre, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_pre, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_music_imgbtn_music_next
	ui->screen_music_imgbtn_music_next = lv_imgbtn_create(ui->screen_music_cont_music);
	lv_obj_add_flag(ui->screen_music_imgbtn_music_next, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xiayiquyiqu_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xiayiqu_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xiayiquyiqu_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xiayiqu_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_xiayiquyiqu_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_xiayiqu_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_xiayiquyiqu_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_xiayiqu_anxia.bin", NULL);
	
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_xiayiqu_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_next, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_xiayiqu_weilianjie.bin", NULL);
#endif
	ui->screen_music_imgbtn_music_next_label = lv_label_create(ui->screen_music_imgbtn_music_next);
	lv_label_set_text(ui->screen_music_imgbtn_music_next_label, "");
	lv_label_set_long_mode(ui->screen_music_imgbtn_music_next_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_music_imgbtn_music_next_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_music_imgbtn_music_next, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_music_imgbtn_music_next, 227, 55);
	lv_obj_set_size(ui->screen_music_imgbtn_music_next, 60, 60);
	lv_page_manager_obj_adapte(ui->screen_music_imgbtn_music_next); // 传递消息给父控件
	

	//Write style for screen_music_imgbtn_music_next, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_next, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_music_imgbtn_music_next, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_music_imgbtn_music_next, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_next, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_next, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_music_imgbtn_music_next, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_next, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_next, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_music_imgbtn_music_next, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_next, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_music_imgbtn_music_play_or_stop
	ui->screen_music_imgbtn_music_play_or_stop = lv_imgbtn_create(ui->screen_music_cont_music);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_zanting_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_zanting_weilianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_bofang_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_bofang_weilianjie.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_zanting_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_zanting_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_bofang_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_bofang_weilianjie.bin", NULL);

	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_zanting_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_bofang_weilianjie.bin", NULL);
#endif
	ui->screen_music_imgbtn_music_play_or_stop_label = lv_label_create(ui->screen_music_imgbtn_music_play_or_stop);
	lv_label_set_text(ui->screen_music_imgbtn_music_play_or_stop_label, "");
	lv_label_set_long_mode(ui->screen_music_imgbtn_music_play_or_stop_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_music_imgbtn_music_play_or_stop_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_music_imgbtn_music_play_or_stop, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_music_imgbtn_music_play_or_stop, 132, 56);
	lv_obj_set_size(ui->screen_music_imgbtn_music_play_or_stop, 60, 60);
	lv_page_manager_obj_adapte(ui->screen_music_imgbtn_music_play_or_stop); // 传递消息给父控件

	//Write style for screen_music_imgbtn_music_play_or_stop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_play_or_stop, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_play_or_stop, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_music_imgbtn_music_play_or_stop, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_play_or_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_music_imgbtn_music_play_or_stop, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_play_or_stop, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_play_or_stop, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_play_or_stop, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_play_or_stop, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_music_imgbtn_music_play_or_stop, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_play_or_stop, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_music_imgbtn_music_play_or_stop, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_music_imgbtn_music_play_or_stop, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_music_imgbtn_music_play_or_stop, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_music_imgbtn_music_play_or_stop, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_music_imgbtn_music_play_or_stop, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_music_label_music_title
	ui->screen_music_label_music_title = lv_label_create(ui->screen_music_cont_music);
	lv_label_set_text(ui->screen_music_label_music_title, "手机音乐");
	lv_label_set_long_mode(ui->screen_music_label_music_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_music_label_music_title, 0, 32);
	lv_obj_set_size(ui->screen_music_label_music_title, 320, 18);

	//Write style for screen_music_label_music_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_music_label_music_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_music_label_music_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_music_label_music_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_music_label_music_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_label_music_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_cont_tip
	ui->screen_music_cont_tip = lv_obj_create(ui->screen_music);
	lv_obj_set_pos(ui->screen_music_cont_tip, 0, 0);
	lv_obj_set_size(ui->screen_music_cont_tip, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_music_cont_tip, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_music_cont_tip, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_music_cont_tip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_music_cont_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_music_cont_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_music_cont_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_music_cont_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_music_cont_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_music_cont_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_music_cont_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_cont_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_label_tip
	ui->screen_music_label_tip = lv_label_create(ui->screen_music_cont_tip);
	lv_label_set_text(ui->screen_music_label_tip, "即将切换到SD音乐，\n是否确定断开手机蓝牙？");
	lv_label_set_long_mode(ui->screen_music_label_tip, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_music_label_tip, 0, 30);
	lv_obj_set_size(ui->screen_music_label_tip, 320, 65);

	//Write style for screen_music_label_tip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_music_label_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_music_label_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_music_label_tip, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_music_label_tip, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_music_label_tip, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_music_label_tip, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_music_label_tip, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_music_label_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_music_label_tip, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_music_label_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_music_label_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_music_label_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_label_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

#if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
	//Write codes screen_music_animimg_wait
	ui->screen_music_animimg_wait = lv_animimg_create(ui->screen_music_cont_tip);
	lv_animimg_set_src(ui->screen_music_animimg_wait, (const void **) screen_music_animimg_wait_imgs, 1);
	lv_animimg_set_duration(ui->screen_music_animimg_wait, 30*1);
	lv_animimg_set_repeat_count(ui->screen_music_animimg_wait, LV_ANIM_REPEAT_INFINITE);
	lv_img_set_src(ui->screen_music_animimg_wait, screen_music_animimg_wait_imgs[0]);
	lv_obj_set_pos(ui->screen_music_animimg_wait, 100, 29);
	lv_obj_set_size(ui->screen_music_animimg_wait, 120, 120);
	lv_obj_add_flag(ui->screen_music_animimg_wait, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_HIDDEN);

#else

	//Write codes screen_music_spinner_wait
	ui->screen_music_spinner_wait = lv_spinner_create(ui->screen_music_cont_tip, 1000, 60);
	lv_obj_set_pos(ui->screen_music_spinner_wait, 110, 31);
	lv_obj_set_size(ui->screen_music_spinner_wait, 100, 100);

	//Write style for screen_music_spinner_wait, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->screen_music_spinner_wait, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_music_spinner_wait, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_music_spinner_wait, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_music_spinner_wait, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_music_spinner_wait, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->screen_music_spinner_wait, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_music_spinner_wait, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_music_spinner_wait, lv_color_hex(0xd2d2d2), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_spinner_wait, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_music_spinner_wait, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->screen_music_spinner_wait, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_music_spinner_wait, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_music_spinner_wait, lv_color_hex(0xba4bd3), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_music_spinner_wait, LV_OBJ_FLAG_HIDDEN);
#endif

	//Write codes screen_music_btn_cancel
	ui->screen_music_btn_cancel = lv_btn_create(ui->screen_music_cont_tip);
	ui->screen_music_btn_cancel_label = lv_label_create(ui->screen_music_btn_cancel);
	lv_label_set_text(ui->screen_music_btn_cancel_label, "取消");
	lv_label_set_long_mode(ui->screen_music_btn_cancel_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_music_btn_cancel_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_music_btn_cancel, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_music_btn_cancel, 39, 109);
	lv_obj_set_size(ui->screen_music_btn_cancel, 100, 50);

	//Write style for screen_music_btn_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_music_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_music_btn_cancel, lv_color_hex(0x67008d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_music_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_music_btn_cancel, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_music_btn_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_music_btn_cancel, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_music_btn_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_btn_confirm
	ui->screen_music_btn_confirm = lv_btn_create(ui->screen_music_cont_tip);
	ui->screen_music_btn_confirm_label = lv_label_create(ui->screen_music_btn_confirm);
	lv_label_set_text(ui->screen_music_btn_confirm_label, "确定");
	lv_label_set_long_mode(ui->screen_music_btn_confirm_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_music_btn_confirm_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_music_btn_confirm, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_music_btn_confirm, 175, 109);
	lv_obj_set_size(ui->screen_music_btn_confirm, 100, 50);

	//Write style for screen_music_btn_confirm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_music_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_music_btn_confirm, lv_color_hex(0x67008d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_music_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_music_btn_confirm, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_btn_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_music_btn_confirm, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_music_btn_confirm, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_music_btn_confirm, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	// lv_obj_set_style_transform_zoom(ui->screen_music, 128, 0);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_music);

	
}

void setup_scr_screen_music_local_music(lv_ui *ui)
{
	//Write codes screen_music_img_music_logo
	ui->screen_music_img_music_logo = lv_img_create(ui->screen_music_cont_music);
	lv_obj_add_flag(ui->screen_music_img_music_logo, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_HIDDEN);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_music_img_music_logo, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\phone_image.png");
#else
	lv_img_set_src(ui->screen_music_img_music_logo, "F:/phone_image.bin");
#endif
	lv_img_set_pivot(ui->screen_music_img_music_logo, 50,50);
	lv_img_set_angle(ui->screen_music_img_music_logo, 0);
	lv_obj_set_pos(ui->screen_music_img_music_logo, 5, 0);
	lv_obj_set_size(ui->screen_music_img_music_logo, 20, 20);

	//Write style for screen_music_img_music_logo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_music_img_music_logo, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_img_music_sd_list
	ui->screen_music_img_music_sd_list = lv_img_create(ui->screen_music_cont_music);
	lv_obj_add_flag(ui->screen_music_img_music_sd_list, LV_OBJ_FLAG_CLICKABLE);
	if(lv_music_mode_get() == SD_MUSIC) {
		lv_obj_clear_flag(ui->screen_music_img_music_sd_list, LV_OBJ_FLAG_HIDDEN);
	} else if (lv_music_mode_get() == PHONE_MUSIC) {
		lv_obj_add_flag(ui->screen_music_img_music_sd_list, LV_OBJ_FLAG_HIDDEN);
	}
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_music_img_music_sd_list, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\grid_image.png");
#else
	lv_img_set_src(ui->screen_music_img_music_sd_list, "F:/grid_image.bin");
#endif
	lv_img_set_pivot(ui->screen_music_img_music_sd_list, 50,50);
	lv_img_set_angle(ui->screen_music_img_music_sd_list, 0);
	lv_obj_set_pos(ui->screen_music_img_music_sd_list, 241, 124);
	lv_obj_set_size(ui->screen_music_img_music_sd_list, 30, 30);

	if(box_info_base_cb.lv_emitter_state_get() == PHONE_MUSIC) {
		lv_obj_add_flag(ui->screen_music_img_music_sd_list, LV_OBJ_FLAG_HIDDEN);
	} else if(box_info_base_cb.lv_emitter_state_get() == SD_MUSIC) {
		lv_obj_clear_flag(ui->screen_music_img_music_sd_list, LV_OBJ_FLAG_HIDDEN);
	}

	//Write style for screen_music_img_music_sd_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_music_img_music_sd_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_img_music_change
	ui->screen_music_img_music_change = lv_img_create(ui->screen_music_cont_music);
	lv_obj_add_flag(ui->screen_music_img_music_change, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_music_img_music_change, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\change_image.png");
#else
	lv_img_set_src(ui->screen_music_img_music_change, "F:/change_image.bin");
#endif
	lv_img_set_pivot(ui->screen_music_img_music_change, 50,50);
	lv_img_set_angle(ui->screen_music_img_music_change, 0);
	lv_obj_set_pos(ui->screen_music_img_music_change, 150, 125);
	lv_obj_set_size(ui->screen_music_img_music_change, 25, 25);

	//Write style for screen_music_img_music_change, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_music_img_music_change, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_cont_music_list
	ui->screen_music_cont_music_list = lv_obj_create(ui->screen_music);
	lv_obj_set_pos(ui->screen_music_cont_music_list, 0, 0);
	lv_obj_set_size(ui->screen_music_cont_music_list, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_music_cont_music_list, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_music_cont_music_list, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui->screen_music_cont_music_list, LV_OBJ_FLAG_GESTURE_BUBBLE);
	// lv_page_manager_cont_adapte(ui->screen_music_cont_music_list);

	//Write style for screen_music_cont_music_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_music_cont_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_music_cont_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_music_cont_music_list, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_music_cont_music_list, lv_color_hex(0x360037), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_music_cont_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_music_cont_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_music_cont_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_music_cont_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_cont_music_list, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_music);

	
}

void setup_scr_screen_music_lyrics(lv_ui *ui)
{
	//Write codes screen_music_img_music_lyric
	ui->screen_music_img_music_lyric = lv_img_create(ui->screen_music_cont_music);
	lv_obj_add_flag(ui->screen_music_img_music_lyric, LV_OBJ_FLAG_CLICKABLE);
#if 0
	lv_obj_add_flag(ui->screen_music_img_music_lyric, LV_OBJ_FLAG_HIDDEN);
#endif
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_music_img_music_lyric, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\lyrics_image.png");
#else
	lv_img_set_src(ui->screen_music_img_music_lyric, "F:/lyrics_image.bin");
#endif
	lv_img_set_pivot(ui->screen_music_img_music_lyric, 50,50);
	lv_img_set_angle(ui->screen_music_img_music_lyric, 0);
	lv_obj_set_pos(ui->screen_music_img_music_lyric, 54, 125);
	lv_obj_set_size(ui->screen_music_img_music_lyric, 25, 25);

	if(lv_music_mode_get() == SD_MUSIC) {
		lv_obj_add_flag(ui->screen_music_img_music_lyric, LV_OBJ_FLAG_HIDDEN);
	} else if (lv_music_mode_get() == PHONE_MUSIC) {
		lv_obj_clear_flag(ui->screen_music_img_music_lyric, LV_OBJ_FLAG_HIDDEN);
	}

	//Write style for screen_music_img_music_lyric, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_music_img_music_lyric, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_music_cont_lyrics
	ui->screen_music_cont_lyrics = lv_obj_create(ui->screen_music);
	lv_obj_set_pos(ui->screen_music_cont_lyrics, 0, 0);
	lv_obj_set_size(ui->screen_music_cont_lyrics, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_music_cont_lyrics, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_music_cont_lyrics, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(ui->screen_music_cont_lyrics, LV_OBJ_FLAG_GESTURE_BUBBLE);

	//Write style for screen_music_cont_lyrics, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_music_cont_lyrics, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_music_cont_lyrics, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_music_cont_lyrics, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_music_cont_lyrics, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_music_cont_lyrics, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_music_cont_lyrics, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_music_cont_lyrics, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_music_cont_lyrics, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_music);
}