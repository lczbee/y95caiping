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


void setup_scr_screen_volume(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_volume
	ui->screen_volume = lv_obj_create(page);
	lv_obj_set_size(ui->screen_volume, 320, 172);

	//Write style for screen_volume, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_volume, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_volume); // 使用页面管理模块时，需对页面进行适配

	//Write codes screen_volume_cont_vol
	ui->screen_volume_cont_vol = lv_obj_create(ui->screen_volume);
	lv_obj_set_pos(ui->screen_volume_cont_vol, 0, 0);
	lv_obj_set_size(ui->screen_volume_cont_vol, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_volume_cont_vol, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_volume_cont_vol); // 使用页面管理模块时，需要对容器进行适配

	//Write style for screen_volume_cont_vol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_volume_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_volume_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_volume_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_volume_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_volume_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_volume_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_volume_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_volume_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_imgbtn_vol_down
	ui->screen_volume_imgbtn_vol_down = lv_imgbtn_create(ui->screen_volume_cont_vol);
	lv_obj_add_flag(ui->screen_volume_imgbtn_vol_down, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jianyinliang.png", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jianyinliang_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jianyinliang.png", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jianyinliang_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_jianyinliang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_jianyinliang_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_jianyinliang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_jianyinliang_anxia.bin", NULL);

	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_jianyinliang_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_down, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_jianyinliang_weilianjie.bin", NULL);
#endif
	ui->screen_volume_imgbtn_vol_down_label = lv_label_create(ui->screen_volume_imgbtn_vol_down);
	lv_label_set_text(ui->screen_volume_imgbtn_vol_down_label, "");
	lv_label_set_long_mode(ui->screen_volume_imgbtn_vol_down_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_volume_imgbtn_vol_down_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_volume_imgbtn_vol_down, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_volume_imgbtn_vol_down, 33, 67);
	lv_obj_set_size(ui->screen_volume_imgbtn_vol_down, 60, 60);

	//Write style for screen_volume_imgbtn_vol_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_volume_imgbtn_vol_down, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_volume_imgbtn_vol_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_volume_imgbtn_vol_down, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_volume_imgbtn_vol_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_volume_imgbtn_vol_down); // 传递消息给父控件

	//Write style for screen_volume_imgbtn_vol_down, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_volume_imgbtn_vol_down, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_volume_imgbtn_vol_down, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_volume_imgbtn_vol_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_volume_imgbtn_vol_down, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_volume_imgbtn_vol_down, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_volume_imgbtn_vol_down, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_volume_imgbtn_vol_down, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_volume_imgbtn_vol_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_volume_imgbtn_vol_down, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_volume_imgbtn_vol_down, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_volume_imgbtn_vol_down, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_volume_imgbtn_vol_up
	ui->screen_volume_imgbtn_vol_up = lv_imgbtn_create(ui->screen_volume_cont_vol);
	lv_obj_add_flag(ui->screen_volume_imgbtn_vol_up, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jiayinliang.png", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jiayinliang_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jiayinliang.png", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jiayinliang_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_jiayinliang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_jiayinliang_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_jiayinliang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_jiayinliang_anxia.bin", NULL);

	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_jiayinliang_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_volume_imgbtn_vol_up, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_jiayinliang_weilianjie.bin", NULL);
#endif
	ui->screen_volume_imgbtn_vol_up_label = lv_label_create(ui->screen_volume_imgbtn_vol_up);
	lv_label_set_text(ui->screen_volume_imgbtn_vol_up_label, "");
	lv_label_set_long_mode(ui->screen_volume_imgbtn_vol_up_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_volume_imgbtn_vol_up_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_volume_imgbtn_vol_up, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_volume_imgbtn_vol_up, 229, 67);
	lv_obj_set_size(ui->screen_volume_imgbtn_vol_up, 60, 60);

	//Write style for screen_volume_imgbtn_vol_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_volume_imgbtn_vol_up, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_volume_imgbtn_vol_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_volume_imgbtn_vol_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_volume_imgbtn_vol_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_volume_imgbtn_vol_up); // 传递消息给父控件

	//Write style for screen_volume_imgbtn_vol_up, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_volume_imgbtn_vol_up, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_volume_imgbtn_vol_up, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_volume_imgbtn_vol_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_volume_imgbtn_vol_up, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_volume_imgbtn_vol_up, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_volume_imgbtn_vol_up, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_volume_imgbtn_vol_up, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_volume_imgbtn_vol_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_volume_imgbtn_vol_up, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_volume_imgbtn_vol_up, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_volume_imgbtn_vol_up, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_volume_label_vol
	ui->screen_volume_label_vol = lv_label_create(ui->screen_volume_cont_vol);
	lv_label_set_text(ui->screen_volume_label_vol, "10");
	lv_label_set_long_mode(ui->screen_volume_label_vol, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_volume_label_vol, 122, 80);
	lv_obj_set_size(ui->screen_volume_label_vol, 73, 50);

	//Write style for screen_volume_label_vol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_volume_label_vol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_volume_label_vol, &lv_customer_font_arial_unicode_32, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_volume_label_vol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_volume_label_vol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_volume_label_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_volume_label_vol_title
	ui->screen_volume_label_vol_title = lv_label_create(ui->screen_volume_cont_vol);
	lv_label_set_text(ui->screen_volume_label_vol_title, "音量调节");
	lv_label_set_long_mode(ui->screen_volume_label_vol_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_volume_label_vol_title, 0, 35);
	lv_obj_set_size(ui->screen_volume_label_vol_title, 320, 19);

	//Write style for screen_volume_label_vol_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_volume_label_vol_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_volume_label_vol_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_volume_label_vol_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_volume_label_vol_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_volume_label_vol_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_volume);

	
}
