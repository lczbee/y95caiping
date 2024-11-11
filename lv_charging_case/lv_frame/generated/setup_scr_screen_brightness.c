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


void setup_scr_screen_brightness(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_brightness
	ui->screen_brightness = lv_obj_create(page);
	lv_obj_set_size(ui->screen_brightness, 320, 172);

	//Write style for screen_brightness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_brightness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_brightness); // 使用页面管理模块时，需对页面进行适配
	// lv_page_manager_preempt_page_bg_adapte(ui->screen_brightness); // 适配为抢断页面

	//Write codes screen_brightness_cont_bn
	ui->screen_brightness_cont_bn = lv_obj_create(ui->screen_brightness);
	lv_obj_set_pos(ui->screen_brightness_cont_bn, 0, 0);
	lv_obj_set_size(ui->screen_brightness_cont_bn, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_brightness_cont_bn, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_brightness_cont_bn); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_brightness_cont_bn); // 适配为抢断页面

	//Write style for screen_brightness_cont_bn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_brightness_cont_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_brightness_cont_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_brightness_cont_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_brightness_cont_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_brightness_cont_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_brightness_cont_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_brightness_cont_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_brightness_cont_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_brightness_imgbtn_bn_up
	ui->screen_brightness_imgbtn_bn_up = lv_imgbtn_create(ui->screen_brightness_cont_bn);
	lv_obj_add_flag(ui->screen_brightness_imgbtn_bn_up, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_up, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jia.png", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_up, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jia_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_up, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jia.png", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_up, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jia_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_up, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_jia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_up, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_jia_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_up, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_jia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_up, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_jia_anxia.bin", NULL);
#endif
	ui->screen_brightness_imgbtn_bn_up_label = lv_label_create(ui->screen_brightness_imgbtn_bn_up);
	lv_label_set_text(ui->screen_brightness_imgbtn_bn_up_label, "");
	lv_label_set_long_mode(ui->screen_brightness_imgbtn_bn_up_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_brightness_imgbtn_bn_up_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_brightness_imgbtn_bn_up, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_brightness_imgbtn_bn_up, 250, 61);
	lv_obj_set_size(ui->screen_brightness_imgbtn_bn_up, 60, 60);

	//Write style for screen_brightness_imgbtn_bn_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_brightness_imgbtn_bn_up, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_brightness_imgbtn_bn_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_brightness_imgbtn_bn_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_brightness_imgbtn_bn_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_brightness_imgbtn_bn_up); // 传递消息给父控件

	//Write style for screen_brightness_imgbtn_bn_up, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_brightness_imgbtn_bn_up, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_brightness_imgbtn_bn_up, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_brightness_imgbtn_bn_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_brightness_imgbtn_bn_up, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_brightness_imgbtn_bn_up, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_brightness_imgbtn_bn_up, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_brightness_imgbtn_bn_up, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_brightness_imgbtn_bn_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_brightness_imgbtn_bn_up, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_brightness_imgbtn_bn_up, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_brightness_imgbtn_bn_up, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_brightness_imgbtn_bn_down
	ui->screen_brightness_imgbtn_bn_down = lv_imgbtn_create(ui->screen_brightness_cont_bn);
	lv_obj_add_flag(ui->screen_brightness_imgbtn_bn_down, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_down, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jian.png", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_down, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jian_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_down, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jian.png", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_down, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_jian_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_down, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_jian.bin", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_down, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_jian_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_down, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_jian.bin", NULL);
	lv_imgbtn_set_src(ui->screen_brightness_imgbtn_bn_down, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_jian_anxia.bin", NULL);
#endif
	ui->screen_brightness_imgbtn_bn_down_label = lv_label_create(ui->screen_brightness_imgbtn_bn_down);
	lv_label_set_text(ui->screen_brightness_imgbtn_bn_down_label, "");
	lv_label_set_long_mode(ui->screen_brightness_imgbtn_bn_down_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_brightness_imgbtn_bn_down_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_brightness_imgbtn_bn_down, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_brightness_imgbtn_bn_down, 11, 61);
	lv_obj_set_size(ui->screen_brightness_imgbtn_bn_down, 60, 60);

	//Write style for screen_brightness_imgbtn_bn_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_brightness_imgbtn_bn_down, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_brightness_imgbtn_bn_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_brightness_imgbtn_bn_down, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_brightness_imgbtn_bn_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_brightness_imgbtn_bn_down); // 传递消息给父控件

	//Write style for screen_brightness_imgbtn_bn_down, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_brightness_imgbtn_bn_down, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_brightness_imgbtn_bn_down, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_brightness_imgbtn_bn_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_brightness_imgbtn_bn_down, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_brightness_imgbtn_bn_down, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_brightness_imgbtn_bn_down, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_brightness_imgbtn_bn_down, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_brightness_imgbtn_bn_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_brightness_imgbtn_bn_down, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_brightness_imgbtn_bn_down, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_brightness_imgbtn_bn_down, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_brightness_slider_bn
	ui->screen_brightness_slider_bn = lv_slider_create(ui->screen_brightness_cont_bn);
	lv_obj_clear_flag(ui->screen_brightness_slider_bn, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLLABLE);	//亮度滑动条-禁止触摸滑动
	lv_slider_set_range(ui->screen_brightness_slider_bn, 0, 100);
	lv_slider_set_mode(ui->screen_brightness_slider_bn, LV_SLIDER_MODE_NORMAL);
	int brightness = box_info_base_cb.lv_ui_bl_levl_get();
	lv_slider_set_value(ui->screen_brightness_slider_bn, brightness, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_brightness_slider_bn, 79, 83);
	lv_obj_set_size(ui->screen_brightness_slider_bn, 164, 19);

	//Write style for screen_brightness_slider_bn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_brightness_slider_bn, 56, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_brightness_slider_bn, lv_color_hex(0xa600ff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_brightness_slider_bn, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_brightness_slider_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_brightness_slider_bn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_brightness_slider_bn, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_brightness_slider_bn, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_brightness_slider_bn, lv_color_hex(0xff6500), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	// lv_obj_set_style_bg_grad_dir(ui->screen_brightness_slider_bn, LV_GRAD_DIR_HOR, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	// lv_obj_set_style_bg_grad_color(ui->screen_brightness_slider_bn, lv_color_hex(0xfdd900), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_brightness_slider_bn, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_brightness_slider_bn, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_brightness_slider_bn, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_brightness_slider_bn, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_brightness_label_bn_title
	ui->screen_brightness_label_bn_title = lv_label_create(ui->screen_brightness_cont_bn);
	lv_label_set_text(ui->screen_brightness_label_bn_title, "屏幕亮度");
	lv_label_set_long_mode(ui->screen_brightness_label_bn_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_brightness_label_bn_title, 0, 35);
	lv_obj_set_size(ui->screen_brightness_label_bn_title, 320, 19);

	//Write style for screen_brightness_label_bn_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_brightness_label_bn_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_brightness_label_bn_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_brightness_label_bn_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_brightness_label_bn_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_brightness_label_bn_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_brightness);

	
}


