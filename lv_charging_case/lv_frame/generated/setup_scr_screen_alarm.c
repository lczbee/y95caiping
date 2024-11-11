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


void setup_scr_screen_alarm(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_alarm
	ui->screen_alarm = lv_obj_create(page);
	lv_obj_set_size(ui->screen_alarm, 320, 172);

	//Write style for screen_alarm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_alarm); // 使用页面管理模块时，需对页面进行适配
	// lv_page_manager_preempt_page_bg_adapte(ui->screen_alarm); // 适配为抢断页面

	//Write codes screen_alarm_cont_alarm
	ui->screen_alarm_cont_alarm = lv_obj_create(ui->screen_alarm);
	lv_obj_set_pos(ui->screen_alarm_cont_alarm, 0, 0);
	lv_obj_set_size(ui->screen_alarm_cont_alarm, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_alarm_cont_alarm, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_alarm_cont_alarm); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_alarm_cont_alarm); // 适配为抢断页面

	//Write style for screen_alarm_cont_alarm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_alarm_cont_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_alarm_cont_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_alarm_cont_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_alarm_cont_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_alarm_cont_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_alarm_cont_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_alarm_cont_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_cont_alarm, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_alarm_imgbtn_alarm_time_down
	ui->screen_alarm_imgbtn_alarm_time_down = lv_imgbtn_create(ui->screen_alarm_cont_alarm);
	lv_obj_add_flag(ui->screen_alarm_imgbtn_alarm_time_down, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_shang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_shang_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_shang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_shang_anxia.bin", NULL);

	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_shang_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_down, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_shang_weilianjie.bin", NULL);
#endif
	ui->screen_alarm_imgbtn_alarm_time_down_label = lv_label_create(ui->screen_alarm_imgbtn_alarm_time_down);
	lv_label_set_text(ui->screen_alarm_imgbtn_alarm_time_down_label, "");
	lv_label_set_long_mode(ui->screen_alarm_imgbtn_alarm_time_down_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_alarm_imgbtn_alarm_time_down_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_alarm_imgbtn_alarm_time_down, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_alarm_imgbtn_alarm_time_down, 25, 53);
	lv_obj_set_size(ui->screen_alarm_imgbtn_alarm_time_down, 60, 60);

	//Write style for screen_alarm_imgbtn_alarm_time_down, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_time_down, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_time_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_imgbtn_alarm_time_down, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_time_down, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_alarm_imgbtn_alarm_time_down); // 传递消息给父控件
	
	//Write style for screen_alarm_imgbtn_alarm_time_down, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_time_down, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_time_down, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_time_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_time_down, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_alarm_imgbtn_alarm_time_down, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_time_down, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_time_down, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_time_down, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_time_down, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_alarm_imgbtn_alarm_time_down, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_time_down, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_alarm_imgbtn_alarm_time_up
	ui->screen_alarm_imgbtn_alarm_time_up = lv_imgbtn_create(ui->screen_alarm_cont_alarm);
	lv_obj_add_flag(ui->screen_alarm_imgbtn_alarm_time_up, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_xia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_xia_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_xia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_xia_anxia.bin", NULL);

	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_xia_weilianjie.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_time_up, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_xia_weilianjie.bin", NULL);
#endif
	ui->screen_alarm_imgbtn_alarm_time_up_label = lv_label_create(ui->screen_alarm_imgbtn_alarm_time_up);
	lv_label_set_text(ui->screen_alarm_imgbtn_alarm_time_up_label, "");
	lv_label_set_long_mode(ui->screen_alarm_imgbtn_alarm_time_up_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_alarm_imgbtn_alarm_time_up_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_alarm_imgbtn_alarm_time_up, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_alarm_imgbtn_alarm_time_up, 241, 53);
	lv_obj_set_size(ui->screen_alarm_imgbtn_alarm_time_up, 60, 60);

	//Write style for screen_alarm_imgbtn_alarm_time_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_time_up, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_time_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_imgbtn_alarm_time_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_time_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_alarm_imgbtn_alarm_time_up); // 传递消息给父控件

	//Write style for screen_alarm_imgbtn_alarm_time_up, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_time_up, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_time_up, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_time_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_time_up, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_alarm_imgbtn_alarm_time_up, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_time_up, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_time_up, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_time_up, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_time_up, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_alarm_imgbtn_alarm_time_up, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_time_up, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_alarm_label_alarm_time
	ui->screen_alarm_label_alarm_time = lv_label_create(ui->screen_alarm_cont_alarm);
	lv_label_set_text(ui->screen_alarm_label_alarm_time, "5分钟");
	lv_label_set_long_mode(ui->screen_alarm_label_alarm_time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_alarm_label_alarm_time, 98, 67);
	lv_obj_set_size(ui->screen_alarm_label_alarm_time, 129, 34);

	//Write style for screen_alarm_label_alarm_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_alarm_label_alarm_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_label_alarm_time, &lv_customer_font_arial_unicode_32, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_alarm_label_alarm_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_label_alarm_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_label_alarm_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_alarm_imgbtn_alarm_setting
	ui->screen_alarm_imgbtn_alarm_setting = lv_imgbtn_create(ui->screen_alarm_cont_alarm);
	lv_obj_add_flag(ui->screen_alarm_imgbtn_alarm_setting, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_setting, LV_IMGBTN_STATE_RELEASED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_dingshishezhi.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_setting, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_dingshishezhi.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_setting, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_dingshishezhi.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_setting, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_dingshishezhi.bin", NULL);
#endif
	ui->screen_alarm_imgbtn_alarm_setting_label = lv_label_create(ui->screen_alarm_imgbtn_alarm_setting);
	lv_label_set_text(ui->screen_alarm_imgbtn_alarm_setting_label, "设置");
	lv_label_set_long_mode(ui->screen_alarm_imgbtn_alarm_setting_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_alarm_imgbtn_alarm_setting_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_alarm_imgbtn_alarm_setting, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_alarm_imgbtn_alarm_setting, 117, 114);
	lv_obj_set_size(ui->screen_alarm_imgbtn_alarm_setting, 82, 36);

	//Write style for screen_alarm_imgbtn_alarm_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_setting, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_imgbtn_alarm_setting, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_alarm_imgbtn_alarm_setting); // 传递消息给父控件

	//Write style for screen_alarm_imgbtn_alarm_setting, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_setting, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_setting, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_setting, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_alarm_imgbtn_alarm_setting, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_setting, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_setting, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_setting, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_alarm_imgbtn_alarm_setting, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_setting, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_alarm_label_alarm_title
	ui->screen_alarm_label_alarm_title = lv_label_create(ui->screen_alarm_cont_alarm);
	lv_label_set_text(ui->screen_alarm_label_alarm_title, "闹钟");
	lv_label_set_long_mode(ui->screen_alarm_label_alarm_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_alarm_label_alarm_title, 0, 35);
	lv_obj_set_size(ui->screen_alarm_label_alarm_title, 320, 32);

	//Write style for screen_alarm_label_alarm_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_alarm_label_alarm_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_label_alarm_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_alarm_label_alarm_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_label_alarm_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_label_alarm_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_alarm_cont_alarm_count
	ui->screen_alarm_cont_alarm_count = lv_obj_create(ui->screen_alarm);
	lv_obj_set_pos(ui->screen_alarm_cont_alarm_count, 0, 0);
	lv_obj_set_size(ui->screen_alarm_cont_alarm_count, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_alarm_cont_alarm_count, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
	lv_page_manager_cont_adapte(ui->screen_alarm_cont_alarm_count); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_alarm_cont_alarm_count); // 适配为抢断页面
	

	//Write style for screen_alarm_cont_alarm_count, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_alarm_cont_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_alarm_cont_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_alarm_cont_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_alarm_cont_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_alarm_cont_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_alarm_cont_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_alarm_cont_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_cont_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_alarm_label_alarm_count_title
	ui->screen_alarm_label_alarm_count_title = lv_label_create(ui->screen_alarm_cont_alarm_count);
	lv_label_set_text(ui->screen_alarm_label_alarm_count_title, "闹钟");
	lv_label_set_long_mode(ui->screen_alarm_label_alarm_count_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_alarm_label_alarm_count_title, 0, 35);
	lv_obj_set_size(ui->screen_alarm_label_alarm_count_title, 320, 32);

	//Write style for screen_alarm_label_alarm_count_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_alarm_label_alarm_count_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_label_alarm_count_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_alarm_label_alarm_count_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_label_alarm_count_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_label_alarm_count_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);


	//Write codes screen_alarm_imgbtn_alarm_cancel
	ui->screen_alarm_imgbtn_alarm_cancel = lv_imgbtn_create(ui->screen_alarm_cont_alarm_count);
	lv_obj_add_flag(ui->screen_alarm_imgbtn_alarm_cancel, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_cancel, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_quxiao.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_cancel, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_quxiao.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_cancel, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_quxiao.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_imgbtn_alarm_cancel, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, "F:/ic_quxiao.bin", NULL);
#endif
	ui->screen_alarm_imgbtn_alarm_cancel_label = lv_label_create(ui->screen_alarm_imgbtn_alarm_cancel);
	lv_label_set_text(ui->screen_alarm_imgbtn_alarm_cancel_label, "设置");
	lv_label_set_long_mode(ui->screen_alarm_imgbtn_alarm_cancel_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_alarm_imgbtn_alarm_cancel_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_alarm_imgbtn_alarm_cancel, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_alarm_imgbtn_alarm_cancel, 121, 112);
	lv_obj_set_size(ui->screen_alarm_imgbtn_alarm_cancel, 82, 36);

	//Write style for screen_alarm_imgbtn_alarm_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_cancel, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_imgbtn_alarm_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_alarm_imgbtn_alarm_cancel); // 传递消息给父控件

	//Write style for screen_alarm_imgbtn_alarm_cancel, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_cancel, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_cancel, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_cancel, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_alarm_imgbtn_alarm_cancel, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_cancel, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_alarm_imgbtn_alarm_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_alarm_imgbtn_alarm_cancel, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_imgbtn_alarm_cancel, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_alarm_imgbtn_alarm_cancel, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_alarm_imgbtn_alarm_cancel, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);


	//Write codes screen_alarm_label_alarm_count
	ui->screen_alarm_label_alarm_count = lv_label_create(ui->screen_alarm_cont_alarm_count);
	lv_label_set_text(ui->screen_alarm_label_alarm_count, "0:3:45");
	lv_label_set_long_mode(ui->screen_alarm_label_alarm_count, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_alarm_label_alarm_count, 60, 73);
	lv_obj_set_size(ui->screen_alarm_label_alarm_count, 200, 32);

	//Write style for screen_alarm_label_alarm_count, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_alarm_label_alarm_count, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_label_alarm_count, &lv_customer_font_pingfangheiti_bold_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_alarm_label_alarm_count, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_label_alarm_count, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_label_alarm_count, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_alarm);

	
}
