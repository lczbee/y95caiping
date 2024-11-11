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


void setup_scr_screen_findmy(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_findmy
	ui->screen_findmy = lv_obj_create(page);
	lv_obj_set_size(ui->screen_findmy, 320, 172);

	//Write style for screen_findmy, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_findmy); // 使用页面管理模块时，需对页面进行适配
	// lv_page_manager_preempt_page_bg_adapte(ui->screen_findmy); // 适配为抢断页面

	//Write codes screen_findmy_cont_findmy
	ui->screen_findmy_cont_findmy = lv_obj_create(ui->screen_findmy);
	lv_obj_set_pos(ui->screen_findmy_cont_findmy, 0, 0);
	lv_obj_set_size(ui->screen_findmy_cont_findmy, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_findmy_cont_findmy, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_findmy_cont_findmy); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_findmy_cont_findmy); // 适配为抢断页面

	//Write style for screen_findmy_cont_findmy, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_findmy_cont_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_findmy_cont_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_findmy_cont_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_findmy_cont_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_findmy_cont_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_findmy_cont_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_findmy_cont_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_findmy_cont_findmy, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_findmy_imgbtn_findmy_left
	ui->screen_findmy_imgbtn_findmy_left = lv_imgbtn_create(ui->screen_findmy_cont_findmy);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_zuoer_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_kaishizhaoerji.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_zuoer_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);

	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_zuoer_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_zuoer_weilianjie.bin", NULL);
#endif
	ui->screen_findmy_imgbtn_findmy_left_label = lv_label_create(ui->screen_findmy_imgbtn_findmy_left);
	lv_label_set_text(ui->screen_findmy_imgbtn_findmy_left_label, "");
	lv_label_set_long_mode(ui->screen_findmy_imgbtn_findmy_left_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_findmy_imgbtn_findmy_left_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_findmy_imgbtn_findmy_left, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_findmy_imgbtn_findmy_left, 52, 69);
	lv_obj_set_size(ui->screen_findmy_imgbtn_findmy_left, 90, 48);

	//Write style for screen_findmy_imgbtn_findmy_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_left, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_left, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_findmy_imgbtn_findmy_left, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_findmy_imgbtn_findmy_left); // 传递消息给父控件

	//Write style for screen_findmy_imgbtn_findmy_left, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_left, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_left, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_left, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_left, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_findmy_imgbtn_findmy_left, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_left, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_left, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_left, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_left, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_findmy_imgbtn_findmy_left, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_left, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_findmy_label_findmy_title
	ui->screen_findmy_label_findmy_title = lv_label_create(ui->screen_findmy_cont_findmy);
	lv_label_set_text(ui->screen_findmy_label_findmy_title, "找到我的耳机");
	lv_label_set_long_mode(ui->screen_findmy_label_findmy_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_findmy_label_findmy_title, 0, 35);
	lv_obj_set_size(ui->screen_findmy_label_findmy_title, 320, 28);

	//Write style for screen_findmy_label_findmy_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_findmy_label_findmy_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_findmy_label_findmy_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_findmy_label_findmy_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_findmy_label_findmy_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_findmy_label_findmy_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_findmy_imgbtn_findmy_right
	ui->screen_findmy_imgbtn_findmy_right = lv_imgbtn_create(ui->screen_findmy_cont_findmy);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_youer_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_kaishizhaoerji.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_youer_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);

	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_youer_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_youer_weilianjie.bin", NULL);
#endif
	ui->screen_findmy_imgbtn_findmy_right_label = lv_label_create(ui->screen_findmy_imgbtn_findmy_right);
	lv_label_set_text(ui->screen_findmy_imgbtn_findmy_right_label, "");
	lv_label_set_long_mode(ui->screen_findmy_imgbtn_findmy_right_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_findmy_imgbtn_findmy_right_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_findmy_imgbtn_findmy_right, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_findmy_imgbtn_findmy_right, 183, 69);
	lv_obj_set_size(ui->screen_findmy_imgbtn_findmy_right, 90, 48);

	//Write style for screen_findmy_imgbtn_findmy_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_right, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_right, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_findmy_imgbtn_findmy_right, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_findmy_imgbtn_findmy_right); // 传递消息给父控件

	//Write style for screen_findmy_imgbtn_findmy_right, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_right, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_right, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_right, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_right, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_findmy_imgbtn_findmy_right, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_right, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_right, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_right, &lv_font_pingfangheiti_bold_16, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_right, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_findmy_imgbtn_findmy_right, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_right, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_findmy_cont_findmy_confirm
	ui->screen_findmy_cont_findmy_confirm = lv_obj_create(ui->screen_findmy);
	lv_obj_set_pos(ui->screen_findmy_cont_findmy_confirm, 0, 0);
	lv_obj_set_size(ui->screen_findmy_cont_findmy_confirm, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_findmy_cont_findmy_confirm, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_findmy_cont_findmy_confirm, LV_OBJ_FLAG_HIDDEN);
	lv_page_manager_cont_adapte(ui->screen_findmy_cont_findmy_confirm); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_findmy_cont_findmy_confirm); // 适配为抢断页面

	//Write style for screen_findmy_cont_findmy_confirm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_findmy_cont_findmy_confirm, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_findmy_cont_findmy_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_findmy_cont_findmy_confirm, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_findmy_cont_findmy_confirm, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_findmy_cont_findmy_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_findmy_cont_findmy_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_findmy_cont_findmy_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_findmy_cont_findmy_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_findmy_cont_findmy_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_findmy_cont_findmy_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_findmy_cont_findmy_confirm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_findmy_imgbtn_findmy_cancel
	ui->screen_findmy_imgbtn_findmy_cancel = lv_imgbtn_create(ui->screen_findmy_cont_findmy_confirm);
	lv_obj_add_flag(ui->screen_findmy_imgbtn_findmy_cancel, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_cancel, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_quxiao.png", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_cancel, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_quxiao.png", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_cancel, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_quxiao.png", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_cancel, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_quxiao.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_cancel, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_quxiao.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_cancel, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_quxiao.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_cancel, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_quxiao.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_cancel, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_quxiao.bin", NULL);
#endif
	ui->screen_findmy_imgbtn_findmy_cancel_label = lv_label_create(ui->screen_findmy_imgbtn_findmy_cancel);
	lv_label_set_text(ui->screen_findmy_imgbtn_findmy_cancel_label, "取消");
	lv_label_set_long_mode(ui->screen_findmy_imgbtn_findmy_cancel_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_findmy_imgbtn_findmy_cancel_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_findmy_imgbtn_findmy_cancel, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_findmy_imgbtn_findmy_cancel, 46, 100);
	lv_obj_set_size(ui->screen_findmy_imgbtn_findmy_cancel, 82, 36);

	//Write style for screen_findmy_imgbtn_findmy_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_cancel, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_findmy_imgbtn_findmy_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_findmy_imgbtn_findmy_cancel, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_cancel, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_cancel, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_cancel, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_cancel, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_findmy_imgbtn_findmy_cancel, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_cancel, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_cancel, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_cancel, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_cancel, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_findmy_imgbtn_findmy_cancel, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_cancel, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_findmy_imgbtn_findmy_start
	ui->screen_findmy_imgbtn_findmy_start = lv_imgbtn_create(ui->screen_findmy_cont_findmy_confirm);
	lv_obj_add_flag(ui->screen_findmy_imgbtn_findmy_start, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_start, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\xic_kaishi_chazhaoerji.png", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_start, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\xic_kaishi_chazhaoerji.png", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_start, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\xic_kaishi_chazhaoerji.png", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_start, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\xic_kaishi_chazhaoerji.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_start, LV_IMGBTN_STATE_RELEASED, NULL, "F:/xic_kaishi_chazhaoerji.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_start, LV_IMGBTN_STATE_PRESSED, NULL, "F:/xic_kaishi_chazhaoerji.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_start, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/xic_kaishi_chazhaoerji.bin", NULL);
	lv_imgbtn_set_src(ui->screen_findmy_imgbtn_findmy_start, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/xic_kaishi_chazhaoerji.bin", NULL);
#endif
	ui->screen_findmy_imgbtn_findmy_start_label = lv_label_create(ui->screen_findmy_imgbtn_findmy_start);
	lv_label_set_text(ui->screen_findmy_imgbtn_findmy_start_label, "开始");
	lv_label_set_long_mode(ui->screen_findmy_imgbtn_findmy_start_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_findmy_imgbtn_findmy_start_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_findmy_imgbtn_findmy_start, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_findmy_imgbtn_findmy_start, 190, 100);
	lv_obj_set_size(ui->screen_findmy_imgbtn_findmy_start, 82, 36);

	//Write style for screen_findmy_imgbtn_findmy_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_start, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_start, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_findmy_imgbtn_findmy_start, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_findmy_imgbtn_findmy_start, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_start, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_start, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_start, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_start, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_findmy_imgbtn_findmy_start, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_start, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_findmy_imgbtn_findmy_start, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_findmy_imgbtn_findmy_start, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_findmy_imgbtn_findmy_start, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_findmy_imgbtn_findmy_start, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_findmy_imgbtn_findmy_start, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_findmy_img_findmy_confirm
	ui->screen_findmy_img_findmy_confirm = lv_img_create(ui->screen_findmy_cont_findmy_confirm);
	lv_obj_add_flag(ui->screen_findmy_img_findmy_confirm, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_findmy_img_findmy_confirm, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_zhaixiaerji.png");
#else
	lv_img_set_src(ui->screen_findmy_img_findmy_confirm, "F:/ic_zhaixiaerji.bin");
#endif
	lv_img_set_pivot(ui->screen_findmy_img_findmy_confirm, 50,50);
	lv_img_set_angle(ui->screen_findmy_img_findmy_confirm, 0);
	lv_obj_set_pos(ui->screen_findmy_img_findmy_confirm, 104, 66);
	lv_obj_set_size(ui->screen_findmy_img_findmy_confirm, 110, 34);

	//Write style for screen_findmy_img_findmy_confirm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_findmy_img_findmy_confirm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_findmy_label_findmy_confirm_title
	ui->screen_findmy_label_findmy_confirm_title = lv_label_create(ui->screen_findmy_cont_findmy_confirm);
	lv_label_set_text(ui->screen_findmy_label_findmy_confirm_title, "摘下耳机");
	lv_label_set_long_mode(ui->screen_findmy_label_findmy_confirm_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_findmy_label_findmy_confirm_title, 0, 35);
	lv_obj_set_size(ui->screen_findmy_label_findmy_confirm_title, 320, 28);

	//Write style for screen_findmy_label_findmy_confirm_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_findmy_label_findmy_confirm_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_findmy_label_findmy_confirm_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_findmy_label_findmy_confirm_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_findmy_label_findmy_confirm_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_findmy_label_findmy_confirm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_findmy);

	
}

