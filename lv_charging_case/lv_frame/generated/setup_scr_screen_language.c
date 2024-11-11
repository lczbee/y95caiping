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


void setup_scr_screen_language(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_language
	ui->screen_language = lv_obj_create(page);
	lv_obj_set_size(ui->screen_language, 320, 172);

	//Write style for screen_language, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_language, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_language); // 使用页面管理模块时，需对页面进行适配
	// lv_page_manager_preempt_page_bg_adapte(ui->screen_language); // 适配为抢断页面

	//Write codes screen_language_cont_lang
	ui->screen_language_cont_lang = lv_obj_create(ui->screen_language);
	lv_obj_set_pos(ui->screen_language_cont_lang, 0, 0);
	lv_obj_set_size(ui->screen_language_cont_lang, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_language_cont_lang, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_language_cont_lang); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_language_cont_lang); // 适配为抢断页面

	//Write style for screen_language_cont_lang, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_language_cont_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_language_cont_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_language_cont_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_language_cont_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_language_cont_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_language_cont_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_language_cont_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_language_cont_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_language_imgbtn_lang_next
	ui->screen_language_imgbtn_lang_next = lv_imgbtn_create(ui->screen_language_cont_lang);
	lv_obj_add_flag(ui->screen_language_imgbtn_lang_next, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_next, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia.png", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_next, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_next, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia.png", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_next, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_next, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_xia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_next, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_xia_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_next, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_xia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_next, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_xia_anxia.bin", NULL);
#endif
	ui->screen_language_imgbtn_lang_next_label = lv_label_create(ui->screen_language_imgbtn_lang_next);
	lv_label_set_text(ui->screen_language_imgbtn_lang_next_label, "");
	lv_label_set_long_mode(ui->screen_language_imgbtn_lang_next_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_language_imgbtn_lang_next_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_language_imgbtn_lang_next, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_language_imgbtn_lang_next, 233, 71);
	lv_obj_set_size(ui->screen_language_imgbtn_lang_next, 60, 60);

	//Write style for screen_language_imgbtn_lang_next, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_language_imgbtn_lang_next, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_language_imgbtn_lang_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_language_imgbtn_lang_next, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_language_imgbtn_lang_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_language_imgbtn_lang_next); // 传递消息给父控件

	//Write style for screen_language_imgbtn_lang_next, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_language_imgbtn_lang_next, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_language_imgbtn_lang_next, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_language_imgbtn_lang_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_language_imgbtn_lang_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_language_imgbtn_lang_next, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_language_imgbtn_lang_next, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_language_imgbtn_lang_next, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_language_imgbtn_lang_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_language_imgbtn_lang_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_language_imgbtn_lang_next, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_language_imgbtn_lang_next, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_language_imgbtn_lang_pre
	ui->screen_language_imgbtn_lang_pre = lv_imgbtn_create(ui->screen_language_cont_lang);
	lv_obj_add_flag(ui->screen_language_imgbtn_lang_pre, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_pre, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang.png", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_pre, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_pre, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang.png", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_pre, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_pre, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_shang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_pre, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_shang_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_pre, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_shang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_language_imgbtn_lang_pre, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_shang_anxia.bin", NULL);
#endif
	ui->screen_language_imgbtn_lang_pre_label = lv_label_create(ui->screen_language_imgbtn_lang_pre);
	lv_label_set_text(ui->screen_language_imgbtn_lang_pre_label, "");
	lv_label_set_long_mode(ui->screen_language_imgbtn_lang_pre_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_language_imgbtn_lang_pre_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_language_imgbtn_lang_pre, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_language_imgbtn_lang_pre, 27, 71);
	lv_obj_set_size(ui->screen_language_imgbtn_lang_pre, 60, 60);

	//Write style for screen_language_imgbtn_lang_pre, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_language_imgbtn_lang_pre, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_language_imgbtn_lang_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_language_imgbtn_lang_pre, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_language_imgbtn_lang_pre, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_language_imgbtn_lang_pre); // 传递消息给父控件

	//Write style for screen_language_imgbtn_lang_pre, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_language_imgbtn_lang_pre, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_language_imgbtn_lang_pre, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_language_imgbtn_lang_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_language_imgbtn_lang_pre, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_language_imgbtn_lang_pre, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_language_imgbtn_lang_pre, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_language_imgbtn_lang_pre, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_language_imgbtn_lang_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_language_imgbtn_lang_pre, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_language_imgbtn_lang_pre, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_language_imgbtn_lang_pre, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_language_label_lang
	ui->screen_language_label_lang = lv_label_create(ui->screen_language_cont_lang);
	lv_label_set_text(ui->screen_language_label_lang, "简体中文");
	lv_label_set_long_mode(ui->screen_language_label_lang, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_language_label_lang, 95, 86);
	lv_obj_set_size(ui->screen_language_label_lang, 129, 44);

	//Write style for screen_language_label_lang, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_language_label_lang, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_language_label_lang, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_language_label_lang, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_language_label_lang, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_language_label_lang, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_language_label_lang_title
	ui->screen_language_label_lang_title = lv_label_create(ui->screen_language_cont_lang);
	lv_label_set_text(ui->screen_language_label_lang_title, "语言切换");
	lv_label_set_long_mode(ui->screen_language_label_lang_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_language_label_lang_title, 0, 35);
	lv_obj_set_size(ui->screen_language_label_lang_title, 320, 24);

	//Write style for screen_language_label_lang_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_language_label_lang_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_language_label_lang_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_language_label_lang_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_language_label_lang_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_language_label_lang_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_language);

	
}



