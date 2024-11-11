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


void setup_scr_screen_product_test(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_product_test
	ui->screen_product_test = lv_obj_create(page);
	lv_obj_set_size(ui->screen_product_test, 320, 172);

	//Write style for screen_product_test, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_product_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_cont_product_test
	ui->screen_product_test_cont_product_test = lv_obj_create(ui->screen_product_test);
	lv_obj_set_pos(ui->screen_product_test_cont_product_test, 0, 0);
	lv_obj_set_size(ui->screen_product_test_cont_product_test, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_product_test_cont_product_test, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_product_test_cont_product_test, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_product_test_cont_product_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_cont_product_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_product_test_cont_product_test, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_cont_product_test, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_product_test_cont_product_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_product_test_cont_product_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_product_test_cont_product_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_product_test_cont_product_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_cont_product_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_cont_product_test_menu
	ui->screen_product_test_cont_product_test_menu = lv_obj_create(ui->screen_product_test_cont_product_test);
	lv_obj_set_pos(ui->screen_product_test_cont_product_test_menu, 0, 0);
	lv_obj_set_size(ui->screen_product_test_cont_product_test_menu, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_product_test_cont_product_test_menu, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_product_test_cont_product_test_menu, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_clear_flag(ui->screen_product_test_cont_product_test_menu, LV_OBJ_FLAG_GESTURE_BUBBLE);

	//Write style for screen_product_test_cont_product_test_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_product_test_cont_product_test_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_cont_product_test_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_product_test_cont_product_test_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_cont_product_test_menu, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_product_test_cont_product_test_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_product_test_cont_product_test_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_product_test_cont_product_test_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_product_test_cont_product_test_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_cont_product_test_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	// lv_obj_set_style_base_dir(ui->screen_product_test_cont_product_test_menu, LV_BASE_DIR_LTR, 0);
	// lv_obj_set_flex_flow(ui->screen_product_test_cont_product_test_menu, LV_FLEX_FLOW_ROW_WRAP);
	// lv_obj_set_style_flex_main_place(ui->screen_product_test_cont_product_test_menu, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
	

	//Write codes screen_product_test_btn_screen
	ui->screen_product_test_btn_screen = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	ui->screen_product_test_btn_screen_label = lv_label_create(ui->screen_product_test_btn_screen);
	lv_label_set_text(ui->screen_product_test_btn_screen_label, "屏幕测试");
	lv_label_set_long_mode(ui->screen_product_test_btn_screen_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_product_test_btn_screen_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_product_test_btn_screen, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_product_test_btn_screen, 6, 9);
	lv_obj_set_size(ui->screen_product_test_btn_screen, 96, 68);

	//Write style for screen_product_test_btn_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_product_test_btn_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_btn_screen, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_product_test_btn_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_btn_screen, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_btn_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_product_test_btn_screen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_product_test_btn_screen, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_product_test_btn_screen, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_btn_tp
	ui->screen_product_test_btn_tp = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	ui->screen_product_test_btn_tp_label = lv_label_create(ui->screen_product_test_btn_tp);
	lv_label_set_text(ui->screen_product_test_btn_tp_label, "触摸测试");
	lv_label_set_long_mode(ui->screen_product_test_btn_tp_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_product_test_btn_tp_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_product_test_btn_tp, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_product_test_btn_tp, 110, 9);
	lv_obj_set_size(ui->screen_product_test_btn_tp, 96, 68);

	//Write style for screen_product_test_btn_tp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_product_test_btn_tp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_btn_tp, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_product_test_btn_tp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_btn_tp, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_btn_tp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_product_test_btn_tp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_product_test_btn_tp, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_product_test_btn_tp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_btn_connect
	ui->screen_product_test_btn_connect = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	ui->screen_product_test_btn_connect_label = lv_label_create(ui->screen_product_test_btn_connect);
	lv_label_set_text(ui->screen_product_test_btn_connect_label, "连接测试");
	lv_label_set_long_mode(ui->screen_product_test_btn_connect_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_product_test_btn_connect_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_product_test_btn_connect, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_product_test_btn_connect, 214, 9);
	lv_obj_set_size(ui->screen_product_test_btn_connect, 96, 68);

	//Write style for screen_product_test_btn_connect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_product_test_btn_connect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_btn_connect, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_product_test_btn_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_btn_connect, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_btn_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_product_test_btn_connect, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_product_test_btn_connect, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_product_test_btn_connect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_btn_reset
	ui->screen_product_test_btn_reset = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	ui->screen_product_test_btn_reset_label = lv_label_create(ui->screen_product_test_btn_reset);
	lv_label_set_text(ui->screen_product_test_btn_reset_label, "复位");
	lv_label_set_long_mode(ui->screen_product_test_btn_reset_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_product_test_btn_reset_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_product_test_btn_reset, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_product_test_btn_reset, 110, 97);
	lv_obj_set_size(ui->screen_product_test_btn_reset, 96, 68);

	//Write style for screen_product_test_btn_reset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_product_test_btn_reset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_btn_reset, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_product_test_btn_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_btn_reset, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_btn_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_product_test_btn_reset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_product_test_btn_reset, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_product_test_btn_reset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_btn_pc
	ui->screen_product_test_btn_pc = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	ui->screen_product_test_btn_pc_label = lv_label_create(ui->screen_product_test_btn_pc);
	lv_label_set_text(ui->screen_product_test_btn_pc_label, "PC按钮");
	lv_label_set_long_mode(ui->screen_product_test_btn_pc_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_product_test_btn_pc_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_product_test_btn_pc, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_product_test_btn_pc, 6, 97);
	lv_obj_set_size(ui->screen_product_test_btn_pc, 96, 68);
	lv_obj_add_flag(ui->screen_product_test_btn_pc, LV_OBJ_FLAG_CHECKABLE);

	//Write style for screen_product_test_btn_pc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_product_test_btn_pc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_btn_pc, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_product_test_btn_pc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_btn_pc, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_btn_pc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_product_test_btn_pc, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_product_test_btn_pc, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_product_test_btn_pc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_btn_storage_mode
	ui->screen_product_test_btn_storage_mode = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	ui->screen_product_test_btn_storage_mode_label = lv_label_create(ui->screen_product_test_btn_storage_mode);
	lv_label_set_text(ui->screen_product_test_btn_storage_mode_label, "仓储模式");
	lv_label_set_long_mode(ui->screen_product_test_btn_storage_mode_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_product_test_btn_storage_mode_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_product_test_btn_storage_mode, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_product_test_btn_storage_mode, 214, 97);
	lv_obj_set_size(ui->screen_product_test_btn_storage_mode, 96, 68);

	//Write style for screen_product_test_btn_storage_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_product_test_btn_storage_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_btn_storage_mode, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_product_test_btn_storage_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_btn_storage_mode, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_btn_storage_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_product_test_btn_storage_mode, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_product_test_btn_storage_mode, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_product_test_btn_storage_mode, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	// //Write codes screen_product_test_btn_reserve2
	// ui->screen_product_test_btn_reserve2 = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	// ui->screen_product_test_btn_reserve2_label = lv_label_create(ui->screen_product_test_btn_reserve2);
	// lv_label_set_text(ui->screen_product_test_btn_reserve2_label, "reserve");
	// lv_label_set_long_mode(ui->screen_product_test_btn_reserve2_label, LV_LABEL_LONG_WRAP);
	// lv_obj_align(ui->screen_product_test_btn_reserve2_label, LV_ALIGN_CENTER, 0, 0);
	// lv_obj_set_style_pad_all(ui->screen_product_test_btn_reserve2, 0, LV_STATE_DEFAULT);
	// lv_obj_set_pos(ui->screen_product_test_btn_reserve2, 25, 30);
	// lv_obj_set_size(ui->screen_product_test_btn_reserve2, 96, 68);

	// //Write style for screen_product_test_btn_reserve2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	// lv_obj_set_style_bg_opa(ui->screen_product_test_btn_reserve2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_bg_color(ui->screen_product_test_btn_reserve2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_border_width(ui->screen_product_test_btn_reserve2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_radius(ui->screen_product_test_btn_reserve2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_shadow_width(ui->screen_product_test_btn_reserve2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_color(ui->screen_product_test_btn_reserve2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_font(ui->screen_product_test_btn_reserve2, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_align(ui->screen_product_test_btn_reserve2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	// //Write codes screen_product_test_btn_bat
	// ui->screen_product_test_btn_bat = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	// ui->screen_product_test_btn_bat_label = lv_label_create(ui->screen_product_test_btn_bat);
	// lv_label_set_text(ui->screen_product_test_btn_bat_label, "电量测试");
	// lv_label_set_long_mode(ui->screen_product_test_btn_bat_label, LV_LABEL_LONG_WRAP);
	// lv_obj_align(ui->screen_product_test_btn_bat_label, LV_ALIGN_CENTER, 0, 0);
	// lv_obj_set_style_pad_all(ui->screen_product_test_btn_bat, 0, LV_STATE_DEFAULT);
	// lv_obj_set_pos(ui->screen_product_test_btn_bat, 21, 33);
	// lv_obj_set_size(ui->screen_product_test_btn_bat, 96, 68);

	// lv_obj_add_flag(ui->screen_product_test_btn_bat, LV_OBJ_FLAG_CHECKABLE);
	// extern int now_soc_trim_info;
	// if(now_soc_trim_info==200){
	// 	lv_obj_add_state(ui->screen_product_test_btn_bat, LV_STATE_CHECKED);
	// } else {
	// 	lv_obj_clear_state(ui->screen_product_test_btn_bat, LV_STATE_CHECKED);
	// }

	// //Write style for screen_product_test_btn_bat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	// lv_obj_set_style_bg_opa(ui->screen_product_test_btn_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_bg_color(ui->screen_product_test_btn_bat, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_border_width(ui->screen_product_test_btn_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_radius(ui->screen_product_test_btn_bat, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_shadow_width(ui->screen_product_test_btn_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_color(ui->screen_product_test_btn_bat, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_font(ui->screen_product_test_btn_bat, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_align(ui->screen_product_test_btn_bat, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);


	// //Write codes screen_product_test_btn_reserve1
	// ui->screen_product_test_btn_reserve1 = lv_btn_create(ui->screen_product_test_cont_product_test_menu);
	// ui->screen_product_test_btn_reserve1_label = lv_label_create(ui->screen_product_test_btn_reserve1);
	// lv_label_set_text(ui->screen_product_test_btn_reserve1_label, "reserve");
	// lv_label_set_long_mode(ui->screen_product_test_btn_reserve1_label, LV_LABEL_LONG_WRAP);
	// lv_obj_align(ui->screen_product_test_btn_reserve1_label, LV_ALIGN_CENTER, 0, 0);
	// lv_obj_set_style_pad_all(ui->screen_product_test_btn_reserve1, 0, LV_STATE_DEFAULT);
	// lv_obj_set_pos(ui->screen_product_test_btn_reserve1, 9, 34);
	// lv_obj_set_size(ui->screen_product_test_btn_reserve1, 96, 68);

	// //Write style for screen_product_test_btn_reserve1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	// lv_obj_set_style_bg_opa(ui->screen_product_test_btn_reserve1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_bg_color(ui->screen_product_test_btn_reserve1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_border_width(ui->screen_product_test_btn_reserve1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_radius(ui->screen_product_test_btn_reserve1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_shadow_width(ui->screen_product_test_btn_reserve1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_color(ui->screen_product_test_btn_reserve1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_font(ui->screen_product_test_btn_reserve1, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_text_align(ui->screen_product_test_btn_reserve1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_cont_tp_test
	ui->screen_product_test_cont_tp_test = lv_obj_create(ui->screen_product_test_cont_product_test);
	lv_obj_set_pos(ui->screen_product_test_cont_tp_test, 0, 0);
	lv_obj_set_size(ui->screen_product_test_cont_tp_test, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_product_test_cont_tp_test, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_product_test_cont_tp_test, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui->screen_product_test_cont_tp_test, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_clear_flag(ui->screen_product_test_cont_tp_test, LV_OBJ_FLAG_GESTURE_BUBBLE);

	//Write style for screen_product_test_cont_tp_test, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_product_test_cont_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_cont_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_product_test_cont_tp_test, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_cont_tp_test, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_product_test_cont_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_product_test_cont_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_product_test_cont_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_product_test_cont_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_cont_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_product_test_btnm_tp_test
	ui->screen_product_test_btnm_tp_test = lv_btnmatrix_create(ui->screen_product_test_cont_tp_test);
	static const char *screen_product_test_btnm_tp_test_text_map[] = {"1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "",};
	lv_btnmatrix_set_map(ui->screen_product_test_btnm_tp_test, screen_product_test_btnm_tp_test_text_map);
	lv_obj_set_pos(ui->screen_product_test_btnm_tp_test, 0, 0);
	lv_obj_set_size(ui->screen_product_test_btnm_tp_test, 320, 172);

	//Write style for screen_product_test_btnm_tp_test, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_product_test_btnm_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_product_test_btnm_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_product_test_btnm_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_product_test_btnm_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_product_test_btnm_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui->screen_product_test_btnm_tp_test, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui->screen_product_test_btnm_tp_test, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_btnm_tp_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_product_test_btnm_tp_test, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_btnm_tp_test, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_product_test_btnm_tp_test, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_product_test_btnm_tp_test, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_product_test_btnm_tp_test, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_product_test_btnm_tp_test, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_product_test_btnm_tp_test, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_product_test_btnm_tp_test, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_product_test_btnm_tp_test, &lv_font_pingfangheiti_bold_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_btnm_tp_test, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_product_test_btnm_tp_test, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_btnm_tp_test, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_btnm_tp_test, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes screen_product_test_cont_screen_test
	ui->screen_product_test_cont_screen_test = lv_obj_create(ui->screen_product_test_cont_product_test);
	lv_obj_set_pos(ui->screen_product_test_cont_screen_test, 0, 0);
	lv_obj_set_size(ui->screen_product_test_cont_screen_test, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_product_test_cont_screen_test, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_product_test_cont_screen_test, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(ui->screen_product_test_cont_screen_test, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_clear_flag(ui->screen_product_test_cont_screen_test, LV_OBJ_FLAG_GESTURE_BUBBLE);

	//Write style for screen_product_test_cont_screen_test, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_product_test_cont_screen_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_product_test_cont_screen_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_product_test_cont_screen_test, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_product_test_cont_screen_test, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_product_test_cont_screen_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_product_test_cont_screen_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_product_test_cont_screen_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_product_test_cont_screen_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_product_test_cont_screen_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_product_test);

	
}
