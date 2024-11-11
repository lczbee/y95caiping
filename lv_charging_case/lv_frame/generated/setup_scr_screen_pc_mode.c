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


void setup_scr_screen_pc_mode(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_pc_mode
	ui->screen_pc_mode = lv_obj_create(page);
	lv_obj_set_size(ui->screen_pc_mode, 320, 172);

	//Write style for screen_pc_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_pc_mode); // 使用页面管理模块时，需对页面进行适配

	//Write codes screen_pc_mode_cont_pc_mode
	ui->screen_pc_mode_cont_pc_mode = lv_obj_create(ui->screen_pc_mode);
	lv_obj_set_pos(ui->screen_pc_mode_cont_pc_mode, 0, 0);
	lv_obj_set_size(ui->screen_pc_mode_cont_pc_mode, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_pc_mode_cont_pc_mode, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_pc_mode_cont_pc_mode); // 使用页面管理模块时，需要对容器进行适配

	//Write style for screen_pc_mode_cont_pc_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pc_mode_cont_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pc_mode_cont_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pc_mode_cont_pc_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pc_mode_cont_pc_mode, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pc_mode_cont_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pc_mode_cont_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pc_mode_cont_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pc_mode_cont_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pc_mode_cont_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pc_mode_cont_plug_in_tip
	ui->screen_pc_mode_cont_plug_in_tip = lv_obj_create(ui->screen_pc_mode_cont_pc_mode);
	lv_obj_set_pos(ui->screen_pc_mode_cont_plug_in_tip, 0, 0);
	lv_obj_set_size(ui->screen_pc_mode_cont_plug_in_tip, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_pc_mode_cont_plug_in_tip, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_pc_mode_cont_plug_in_tip); // 使用页面管理模块时，需要对容器进行适配

	//Write style for screen_pc_mode_cont_plug_in_tip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pc_mode_cont_plug_in_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pc_mode_cont_plug_in_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pc_mode_cont_plug_in_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pc_mode_cont_plug_in_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pc_mode_cont_plug_in_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pc_mode_cont_plug_in_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pc_mode_cont_plug_in_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pc_mode_cont_plug_in_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pc_mode_img_usb
	ui->screen_pc_mode_img_usb = lv_img_create(ui->screen_pc_mode_cont_plug_in_tip);
	lv_obj_add_flag(ui->screen_pc_mode_img_usb, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_pc_mode_img_usb, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\usb.png");
#else
	lv_img_set_src(ui->screen_pc_mode_img_usb, "F:/usb.bin");
#endif
	lv_img_set_pivot(ui->screen_pc_mode_img_usb, 50,50);
	lv_img_set_angle(ui->screen_pc_mode_img_usb, 0);
	lv_obj_set_pos(ui->screen_pc_mode_img_usb, 128, 95);
	lv_obj_set_size(ui->screen_pc_mode_img_usb, 60, 60);
	lv_page_manager_obj_adapte(ui->screen_pc_mode_img_usb); // 传递消息给父控件

	//Write style for screen_pc_mode_img_usb, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_pc_mode_img_usb, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pc_mode_label_usb_tip
	ui->screen_pc_mode_label_usb_tip = lv_label_create(ui->screen_pc_mode_cont_plug_in_tip);
	lv_label_set_text(ui->screen_pc_mode_label_usb_tip, "请插入usb");
	lv_label_set_long_mode(ui->screen_pc_mode_label_usb_tip, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_pc_mode_label_usb_tip, 0, 38);
	lv_obj_set_size(ui->screen_pc_mode_label_usb_tip, 320, 32);

	//Write style for screen_pc_mode_label_usb_tip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_pc_mode_label_usb_tip, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_pc_mode_label_usb_tip, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_pc_mode_label_usb_tip, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_pc_mode_label_usb_tip, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pc_mode_label_usb_tip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pc_mode_cont_file
	ui->screen_pc_mode_cont_file = lv_obj_create(ui->screen_pc_mode_cont_pc_mode);
	lv_obj_set_pos(ui->screen_pc_mode_cont_file, 0, 0);
	lv_obj_set_size(ui->screen_pc_mode_cont_file, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_pc_mode_cont_file, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_pc_mode_cont_file, LV_OBJ_FLAG_HIDDEN);
	lv_page_manager_cont_adapte(ui->screen_pc_mode_cont_file); // 使用页面管理模块时，需要对容器进行适配

	//Write style for screen_pc_mode_cont_file, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pc_mode_cont_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pc_mode_cont_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pc_mode_cont_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pc_mode_cont_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pc_mode_cont_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pc_mode_cont_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pc_mode_cont_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pc_mode_cont_file, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pc_mode_img_file_transfer
	ui->screen_pc_mode_img_file_transfer = lv_img_create(ui->screen_pc_mode_cont_file);
	lv_obj_add_flag(ui->screen_pc_mode_img_file_transfer, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_pc_mode_img_file_transfer, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\file_transfer.png");
#else
	lv_img_set_src(ui->screen_pc_mode_img_file_transfer, "F:/file_transfer.bin");
#endif
	lv_img_set_pivot(ui->screen_pc_mode_img_file_transfer, 50,50);
	lv_img_set_angle(ui->screen_pc_mode_img_file_transfer, 0);
	lv_obj_set_pos(ui->screen_pc_mode_img_file_transfer, 120, 43);
	lv_obj_set_size(ui->screen_pc_mode_img_file_transfer, 80, 80);
	lv_page_manager_obj_adapte(ui->screen_pc_mode_img_file_transfer); // 传递消息给父控件

	//Write style for screen_pc_mode_img_file_transfer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_pc_mode_img_file_transfer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pc_mode_label_file_transfer
	ui->screen_pc_mode_label_file_transfer = lv_label_create(ui->screen_pc_mode_cont_file);
	lv_label_set_text(ui->screen_pc_mode_label_file_transfer, "文件传输");
	lv_label_set_long_mode(ui->screen_pc_mode_label_file_transfer, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_pc_mode_label_file_transfer, 0, 13);
	lv_obj_set_size(ui->screen_pc_mode_label_file_transfer, 320, 30);

	//Write style for screen_pc_mode_label_file_transfer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_pc_mode_label_file_transfer, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_pc_mode_label_file_transfer, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_pc_mode_label_file_transfer, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_pc_mode_label_file_transfer, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pc_mode_label_file_transfer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pc_mode_sw_pc_mode
	ui->screen_pc_mode_sw_pc_mode = lv_switch_create(ui->screen_pc_mode_cont_file);
	lv_obj_set_pos(ui->screen_pc_mode_sw_pc_mode, 135, 131);
	lv_obj_set_size(ui->screen_pc_mode_sw_pc_mode, 50, 30);
	lv_page_manager_obj_adapte(ui->screen_pc_mode_sw_pc_mode); // 传递消息给父控件

	//Write style for screen_pc_mode_sw_pc_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pc_mode_sw_pc_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pc_mode_sw_pc_mode, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_pc_mode_sw_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pc_mode_sw_pc_mode, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pc_mode_sw_pc_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_pc_mode_sw_pc_mode, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
	lv_obj_set_style_bg_opa(ui->screen_pc_mode_sw_pc_mode, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->screen_pc_mode_sw_pc_mode, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->screen_pc_mode_sw_pc_mode, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style for screen_pc_mode_sw_pc_mode, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pc_mode_sw_pc_mode, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pc_mode_sw_pc_mode, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_pc_mode_sw_pc_mode, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pc_mode_sw_pc_mode, 15, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_pc_mode);

	
}
