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


void setup_scr_screen_tiktok(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_tiktok
	ui->screen_tiktok = lv_obj_create(page);
	lv_obj_set_size(ui->screen_tiktok, 320, 172);

	//Write style for screen_tiktok, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_tiktok); // 使用页面管理模块时，需对页面进行适配

	//Write codes screen_tiktok_cont_tiktok
	ui->screen_tiktok_cont_tiktok = lv_obj_create(ui->screen_tiktok);
	lv_obj_set_pos(ui->screen_tiktok_cont_tiktok, 0, 0);
	lv_obj_set_size(ui->screen_tiktok_cont_tiktok, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_tiktok_cont_tiktok, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_tiktok_cont_tiktok); // 使用页面管理模块时，需要对容器进行适配

	//Write style for screen_tiktok_cont_tiktok, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_tiktok_cont_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_tiktok_cont_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_tiktok_cont_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_tiktok_cont_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_tiktok_cont_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_tiktok_cont_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_tiktok_cont_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_cont_tiktok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_tiktok_img_tiktok_like
	ui->screen_tiktok_img_tiktok_like = lv_img_create(ui->screen_tiktok_cont_tiktok);
	lv_obj_add_flag(ui->screen_tiktok_img_tiktok_like, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_tiktok_img_tiktok_like, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_dianzan.png");
#else
	lv_img_set_src(ui->screen_tiktok_img_tiktok_like, "F:/ic_dianzan.bin");
#endif
	lv_img_set_pivot(ui->screen_tiktok_img_tiktok_like, 50,50);
	lv_img_set_angle(ui->screen_tiktok_img_tiktok_like, 0);
	lv_obj_set_pos(ui->screen_tiktok_img_tiktok_like, 130, 57);
	lv_obj_set_size(ui->screen_tiktok_img_tiktok_like, 60, 60);

	//Write style for screen_tiktok_img_tiktok_like, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_tiktok_img_tiktok_like, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_tiktok_img_tiktok_like); // 传递消息给父控件

	//Write codes screen_tiktok_imgbtn_tiktok_pre
	ui->screen_tiktok_imgbtn_tiktok_pre = lv_imgbtn_create(ui->screen_tiktok_cont_tiktok);
	lv_obj_add_flag(ui->screen_tiktok_imgbtn_tiktok_pre, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang.png", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang.png", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_shang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_shang_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_shang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_shang_anxia.bin", NULL);

	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_shang_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_pre, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_shang_weilianjie.bin", NULL);
#endif
	ui->screen_tiktok_imgbtn_tiktok_pre_label = lv_label_create(ui->screen_tiktok_imgbtn_tiktok_pre);
	lv_label_set_text(ui->screen_tiktok_imgbtn_tiktok_pre_label, "");
	lv_label_set_long_mode(ui->screen_tiktok_imgbtn_tiktok_pre_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_tiktok_imgbtn_tiktok_pre_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_tiktok_imgbtn_tiktok_pre, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_tiktok_imgbtn_tiktok_pre, 28, 55);
	lv_obj_set_size(ui->screen_tiktok_imgbtn_tiktok_pre, 60, 60);

	//Write style for screen_tiktok_imgbtn_tiktok_pre, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_tiktok_imgbtn_tiktok_pre, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_tiktok_imgbtn_tiktok_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_tiktok_imgbtn_tiktok_pre, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_imgbtn_tiktok_pre, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_tiktok_imgbtn_tiktok_pre); // 传递消息给父控件

	//Write style for screen_tiktok_imgbtn_tiktok_pre, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_tiktok_imgbtn_tiktok_pre, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_tiktok_imgbtn_tiktok_pre, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_tiktok_imgbtn_tiktok_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_imgbtn_tiktok_pre, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_tiktok_imgbtn_tiktok_pre, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_tiktok_imgbtn_tiktok_pre, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_tiktok_imgbtn_tiktok_pre, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_tiktok_imgbtn_tiktok_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_imgbtn_tiktok_pre, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_tiktok_imgbtn_tiktok_pre, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_tiktok_imgbtn_tiktok_pre, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_tiktok_imgbtn_tiktok_next
	ui->screen_tiktok_imgbtn_tiktok_next = lv_imgbtn_create(ui->screen_tiktok_cont_tiktok);
	lv_obj_add_flag(ui->screen_tiktok_imgbtn_tiktok_next, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia.png", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia.png", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_xia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_xia_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_xia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_xia_anxia.bin", NULL);

	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_xia_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_tiktok_imgbtn_tiktok_next, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_xia_weilianjie.bin", NULL);
#endif
	ui->screen_tiktok_imgbtn_tiktok_next_label = lv_label_create(ui->screen_tiktok_imgbtn_tiktok_next);
	lv_label_set_text(ui->screen_tiktok_imgbtn_tiktok_next_label, "");
	lv_label_set_long_mode(ui->screen_tiktok_imgbtn_tiktok_next_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_tiktok_imgbtn_tiktok_next_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_tiktok_imgbtn_tiktok_next, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_tiktok_imgbtn_tiktok_next, 235, 55);
	lv_obj_set_size(ui->screen_tiktok_imgbtn_tiktok_next, 60, 60);

	//Write style for screen_tiktok_imgbtn_tiktok_next, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_tiktok_imgbtn_tiktok_next, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_tiktok_imgbtn_tiktok_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_tiktok_imgbtn_tiktok_next, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_imgbtn_tiktok_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_tiktok_imgbtn_tiktok_next); // 传递消息给父控件

	//Write style for screen_tiktok_imgbtn_tiktok_next, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_tiktok_imgbtn_tiktok_next, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_tiktok_imgbtn_tiktok_next, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_tiktok_imgbtn_tiktok_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_imgbtn_tiktok_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_tiktok_imgbtn_tiktok_next, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_tiktok_imgbtn_tiktok_next, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_tiktok_imgbtn_tiktok_next, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_tiktok_imgbtn_tiktok_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_imgbtn_tiktok_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_tiktok_imgbtn_tiktok_next, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_tiktok_imgbtn_tiktok_next, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_tiktok_label_tiktok_like
	ui->screen_tiktok_label_tiktok_like = lv_label_create(ui->screen_tiktok_cont_tiktok);
	lv_label_set_text(ui->screen_tiktok_label_tiktok_like, "点赞");
	lv_label_set_long_mode(ui->screen_tiktok_label_tiktok_like, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_tiktok_label_tiktok_like, 0, 30);
	lv_obj_set_size(ui->screen_tiktok_label_tiktok_like, 320, 32);
	lv_obj_add_flag(ui->screen_tiktok_label_tiktok_like, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_tiktok_label_tiktok_like, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_tiktok_label_tiktok_like, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_tiktok_label_tiktok_like, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_tiktok_label_tiktok_like, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_tiktok_label_tiktok_like, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_label_tiktok_like, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_tiktok);

	
}

void setup_scr_screen_tiktok_rejust(lv_ui *ui)
{
	//Write codes screen_tiktok_cont_rejust
	ui->screen_tiktok_cont_rejust = lv_obj_create(ui->screen_tiktok);
	lv_obj_set_pos(ui->screen_tiktok_cont_rejust, 0, 0);
	lv_obj_set_size(ui->screen_tiktok_cont_rejust, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_tiktok_cont_rejust, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_tiktok_cont_rejust, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(ui->screen_tiktok_cont_rejust, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_clear_flag(ui->screen_tiktok_cont_rejust, LV_OBJ_FLAG_GESTURE_BUBBLE);

	//Write style for screen_tiktok_cont_rejust, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_tiktok_cont_rejust, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_tiktok_cont_rejust, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_tiktok_cont_rejust, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_tiktok_cont_rejust, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_tiktok_cont_rejust, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_tiktok_cont_rejust, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_tiktok_cont_rejust, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_tiktok_cont_rejust, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_tiktok_img_left
	ui->screen_tiktok_img_left = lv_img_create(ui->screen_tiktok_cont_rejust);
	lv_obj_add_flag(ui->screen_tiktok_img_left, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_tiktok_img_left, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\left.png");
#else
	lv_img_set_src(ui->screen_tiktok_img_left, "F:/left.bin");
#endif
	lv_img_set_pivot(ui->screen_tiktok_img_left, 50,50);
	lv_img_set_angle(ui->screen_tiktok_img_left, 0);
	lv_obj_set_pos(ui->screen_tiktok_img_left, 0, 50);
	lv_obj_set_size(ui->screen_tiktok_img_left, 70, 70);

	//Write style for screen_tiktok_img_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_tiktok_img_left, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_tiktok_img_tiktok_like); // 传递消息给父控件

	//Write codes screen_tiktok_img_reset
	ui->screen_tiktok_img_reset = lv_img_create(ui->screen_tiktok_cont_rejust);
	lv_obj_add_flag(ui->screen_tiktok_img_reset, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_tiktok_img_reset, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\reset.png");
#else
	lv_img_set_src(ui->screen_tiktok_img_reset, "F:/reset.bin");
#endif
	lv_img_set_pivot(ui->screen_tiktok_img_reset, 50,50);
	lv_img_set_angle(ui->screen_tiktok_img_reset, 0);
	lv_obj_set_pos(ui->screen_tiktok_img_reset, 243, 7);
	lv_obj_set_size(ui->screen_tiktok_img_reset, 70, 70);

	//Write style for screen_tiktok_img_reset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_tiktok_img_reset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_tiktok_img_tiktok_like); // 传递消息给父控件

	//Write codes screen_tiktok_img_up
	ui->screen_tiktok_img_up = lv_img_create(ui->screen_tiktok_cont_rejust);
	lv_obj_add_flag(ui->screen_tiktok_img_up, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_tiktok_img_up, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\up.png");
#else
	lv_img_set_src(ui->screen_tiktok_img_up, "F:/up.bin");
#endif
	lv_img_set_pivot(ui->screen_tiktok_img_up, 50,50);
	lv_img_set_angle(ui->screen_tiktok_img_up, 0);
	lv_obj_set_pos(ui->screen_tiktok_img_up, 75, 0);
	lv_obj_set_size(ui->screen_tiktok_img_up, 70, 70);

	//Write style for screen_tiktok_img_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_tiktok_img_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_tiktok_img_tiktok_like); // 传递消息给父控件

	//Write codes screen_tiktok_img_right
	ui->screen_tiktok_img_right = lv_img_create(ui->screen_tiktok_cont_rejust);
	lv_obj_add_flag(ui->screen_tiktok_img_right, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_tiktok_img_right, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\right.png");
#else
	lv_img_set_src(ui->screen_tiktok_img_right, "F:/right.bin");
#endif
	lv_img_set_pivot(ui->screen_tiktok_img_right, 50,50);
	lv_img_set_angle(ui->screen_tiktok_img_right, 0);
	lv_obj_set_pos(ui->screen_tiktok_img_right, 150, 50);
	lv_obj_set_size(ui->screen_tiktok_img_right, 70, 70);

	//Write style for screen_tiktok_img_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_tiktok_img_right, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_tiktok_img_tiktok_like); // 传递消息给父控件

	//Write codes screen_tiktok_img_down
	ui->screen_tiktok_img_down = lv_img_create(ui->screen_tiktok_cont_rejust);
	lv_obj_add_flag(ui->screen_tiktok_img_down, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_tiktok_img_down, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\down.png");
#else
	lv_img_set_src(ui->screen_tiktok_img_down, "F:/down.bin");
#endif
	lv_img_set_pivot(ui->screen_tiktok_img_down, 50,50);
	lv_img_set_angle(ui->screen_tiktok_img_down, 0);
	lv_obj_set_pos(ui->screen_tiktok_img_down, 75, 100);
	lv_obj_set_size(ui->screen_tiktok_img_down, 70, 70);

	//Write style for screen_tiktok_img_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_tiktok_img_down, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_tiktok_img_tiktok_like); // 传递消息给父控件

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_tiktok);
}
