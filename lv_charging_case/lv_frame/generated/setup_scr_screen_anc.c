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


void setup_scr_screen_anc(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_anc
	ui->screen_anc = lv_obj_create(page);
	lv_obj_set_size(ui->screen_anc, 320, 172);

	//Write style for screen_anc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_anc); // 使用页面管理模块时，需对页面进行适配

	//Write codes screen_anc_cont_anc
	ui->screen_anc_cont_anc = lv_obj_create(ui->screen_anc);
	lv_obj_set_pos(ui->screen_anc_cont_anc, 0, 0);
	lv_obj_set_size(ui->screen_anc_cont_anc, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_anc_cont_anc, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_anc_cont_anc); // 使用页面管理模块时，需要对容器进行适配

	//Write style for screen_anc_cont_anc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_anc_cont_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_anc_cont_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_anc_cont_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_anc_cont_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_anc_cont_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_anc_cont_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_anc_cont_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_anc_cont_anc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_anc_imgbtn_anc_close
	ui->screen_anc_imgbtn_anc_close = lv_imgbtn_create(ui->screen_anc_cont_anc);
	// lv_obj_add_flag(ui->screen_anc_imgbtn_anc_close, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_guan_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_guan_weilianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_guan_xuanzhong.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_guan_weilianjie.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_guan_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_guan_xuanzhong.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_close, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
#endif
	ui->screen_anc_imgbtn_anc_close_label = lv_label_create(ui->screen_anc_imgbtn_anc_close);
	lv_label_set_text(ui->screen_anc_imgbtn_anc_close_label, "关闭");
	lv_label_set_long_mode(ui->screen_anc_imgbtn_anc_close_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_anc_imgbtn_anc_close_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_anc_imgbtn_anc_close, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_anc_imgbtn_anc_close, 17, 76);
	lv_obj_set_size(ui->screen_anc_imgbtn_anc_close, 61, 41);

	//Write style for screen_anc_imgbtn_anc_close, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_close, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_close, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_anc_imgbtn_anc_close, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_close, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_anc_imgbtn_anc_close); // 传递消息给父控件

	//Write style for screen_anc_imgbtn_anc_close, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_close, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_close, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_close, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_close, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_anc_imgbtn_anc_close, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_close, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_close, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_close, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_close, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_anc_imgbtn_anc_close, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_close, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_anc_imgbtn_anc_open
	ui->screen_anc_imgbtn_anc_open = lv_imgbtn_create(ui->screen_anc_cont_anc);
	// lv_obj_add_flag(ui->screen_anc_imgbtn_anc_open, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_kai_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_kai_weilianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_kai_xuanzhong.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_kai_lianjie.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_guan_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_guan_xuanzhong.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_open, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
#endif
	ui->screen_anc_imgbtn_anc_open_label = lv_label_create(ui->screen_anc_imgbtn_anc_open);
	lv_label_set_text(ui->screen_anc_imgbtn_anc_open_label, "降噪");
	lv_label_set_long_mode(ui->screen_anc_imgbtn_anc_open_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_anc_imgbtn_anc_open_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_anc_imgbtn_anc_open, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_anc_imgbtn_anc_open, 131, 76);
	lv_obj_set_size(ui->screen_anc_imgbtn_anc_open, 61, 41);

	//Write style for screen_anc_imgbtn_anc_open, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_open, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_open, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_anc_imgbtn_anc_open, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_open, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_anc_imgbtn_anc_open); // 传递消息给父控件

	//Write style for screen_anc_imgbtn_anc_open, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_open, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_open, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_open, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_open, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_anc_imgbtn_anc_open, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_open, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_open, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_open, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_open, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_anc_imgbtn_anc_open, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_open, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_anc_imgbtn_anc_transparent
	ui->screen_anc_imgbtn_anc_transparent = lv_imgbtn_create(ui->screen_anc_cont_anc);
	// lv_obj_add_flag(ui->screen_anc_imgbtn_anc_transparent, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_tongtou_lianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_tongtou_weilianjie.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_tongtou_xuanzhong.png", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_tongtou_lianjie.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_guan_lianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_guan_xuanzhong.bin", NULL);
	lv_imgbtn_set_src(ui->screen_anc_imgbtn_anc_transparent, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_guan_weilianjie.bin", NULL);
#endif
	ui->screen_anc_imgbtn_anc_transparent_label = lv_label_create(ui->screen_anc_imgbtn_anc_transparent);
	lv_label_set_text(ui->screen_anc_imgbtn_anc_transparent_label, "通透");
	lv_label_set_long_mode(ui->screen_anc_imgbtn_anc_transparent_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_anc_imgbtn_anc_transparent_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_anc_imgbtn_anc_transparent, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_anc_imgbtn_anc_transparent, 239, 76);
	lv_obj_set_size(ui->screen_anc_imgbtn_anc_transparent, 61, 41);

	//Write style for screen_anc_imgbtn_anc_transparent, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_transparent, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_transparent, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_anc_imgbtn_anc_transparent, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_transparent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_anc_imgbtn_anc_transparent); // 传递消息给父控件

	//Write style for screen_anc_imgbtn_anc_transparent, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_transparent, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_transparent, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_transparent, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_transparent, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_anc_imgbtn_anc_transparent, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_transparent, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_anc_imgbtn_anc_transparent, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_anc_imgbtn_anc_transparent, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_anc_imgbtn_anc_transparent, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_anc_imgbtn_anc_transparent, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_anc_imgbtn_anc_transparent, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_anc_label_anc_title
	ui->screen_anc_label_anc_title = lv_label_create(ui->screen_anc_cont_anc);
	lv_label_set_text(ui->screen_anc_label_anc_title, "降噪");
	lv_label_set_long_mode(ui->screen_anc_label_anc_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_anc_label_anc_title, 0, 35);
	lv_obj_set_size(ui->screen_anc_label_anc_title, 320, 25);

	//Write style for screen_anc_label_anc_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_anc_label_anc_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_anc_label_anc_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_anc_label_anc_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_anc_label_anc_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_anc_label_anc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_anc);

	
}
