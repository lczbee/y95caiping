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


void setup_scr_screen_light(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_light
	ui->screen_light = lv_obj_create(page);
	lv_obj_set_size(ui->screen_light, 320, 172);

	//Write style for screen_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_light); // 使用页面管理模块时，需对页面进行适配
	// lv_page_manager_preempt_page_bg_adapte(ui->screen_light); // 适配为抢断页面

	//Write codes screen_light_cont_light
	ui->screen_light_cont_light = lv_obj_create(ui->screen_light);
	lv_obj_set_pos(ui->screen_light_cont_light, 0, 0);
	lv_obj_set_size(ui->screen_light_cont_light, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_light_cont_light, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_light_cont_light); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_light_cont_light); // 适配为抢断页面

	//Write style for screen_light_cont_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_light_cont_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_light_cont_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_light_cont_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_light_cont_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_light_cont_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_light_cont_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_light_cont_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_light_cont_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_light_label_light_title
	ui->screen_light_label_light_title = lv_label_create(ui->screen_light_cont_light);
	lv_label_set_text(ui->screen_light_label_light_title, "灯光");
	lv_label_set_long_mode(ui->screen_light_label_light_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_light_label_light_title, 0, 35);
	lv_obj_set_size(ui->screen_light_label_light_title, 320, 27);

	//Write style for screen_light_label_light_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_light_label_light_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_light_label_light_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_light_label_light_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_light_label_light_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_light_label_light_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_light_imgbtn_light_on
	ui->screen_light_imgbtn_light_on = lv_imgbtn_create(ui->screen_light_cont_light);
	lv_obj_add_flag(ui->screen_light_imgbtn_light_on, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_light_imgbtn_light_on, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_dakai_pingmudengguang.png", NULL);
	lv_imgbtn_set_src(ui->screen_light_imgbtn_light_on, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_dakai_pingmudengguang.png", NULL);
	lv_imgbtn_set_src(ui->screen_light_imgbtn_light_on, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_dakai_pingmudengguang.png", NULL);
	lv_imgbtn_set_src(ui->screen_light_imgbtn_light_on, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_dakai_pingmudengguang.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_light_imgbtn_light_on, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_dakai_pingmudengguang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_light_imgbtn_light_on, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_dakai_pingmudengguang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_light_imgbtn_light_on, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_dakai_pingmudengguang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_light_imgbtn_light_on, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_dakai_pingmudengguang.bin", NULL);
#endif
	ui->screen_light_imgbtn_light_on_label = lv_label_create(ui->screen_light_imgbtn_light_on);
	lv_label_set_text(ui->screen_light_imgbtn_light_on_label, "打开");
	lv_label_set_long_mode(ui->screen_light_imgbtn_light_on_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_light_imgbtn_light_on_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_light_imgbtn_light_on, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_light_imgbtn_light_on, 97, 80);
	lv_obj_set_size(ui->screen_light_imgbtn_light_on, 124, 40);

	//Write style for screen_light_imgbtn_light_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_light_imgbtn_light_on, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_light_imgbtn_light_on, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_light_imgbtn_light_on, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_light_imgbtn_light_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_light_imgbtn_light_on, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_light_imgbtn_light_on, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_light_imgbtn_light_on, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_light_imgbtn_light_on, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_light_imgbtn_light_on, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_light_imgbtn_light_on, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_light_imgbtn_light_on, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_light_imgbtn_light_on, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_light_imgbtn_light_on, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_light_imgbtn_light_on, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_light_imgbtn_light_on, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_light_imgbtn_light_on, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
	lv_page_manager_obj_adapte(ui->screen_light_imgbtn_light_on); // 传递消息给父控件

	//Write codes screen_light_cont_lighting
	ui->screen_light_cont_lighting = lv_obj_create(ui->screen_light);
	lv_obj_set_pos(ui->screen_light_cont_lighting, 0, 0);
	lv_obj_set_size(ui->screen_light_cont_lighting, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_light_cont_lighting, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_light_cont_lighting, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_light_cont_lighting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_light_cont_lighting, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_light_cont_lighting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_light_cont_lighting, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_light_cont_lighting, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_light_cont_lighting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_light_cont_lighting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_light_cont_lighting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_light_cont_lighting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_light_cont_lighting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_light_cont_lighting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_light_cont_lighting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_light_cont_lighting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_light);

	
}
