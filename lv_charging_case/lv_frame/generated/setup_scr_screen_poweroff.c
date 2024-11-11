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


void setup_scr_screen_poweroff(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_poweroff
	ui->screen_poweroff = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_poweroff, 320, 172);

	//Write style for screen_poweroff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_poweroff); // 使用页面管理模块时，需对页面进行适配
	lv_page_manager_preempt_page_bg_adapte(ui->screen_poweroff); // 适配为抢断页面

	//Write codes screen_poweroff_cont_poweroff
	ui->screen_poweroff_cont_poweroff = lv_obj_create(ui->screen_poweroff);
	lv_obj_set_pos(ui->screen_poweroff_cont_poweroff, 0, 0);
	lv_obj_set_size(ui->screen_poweroff_cont_poweroff, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_poweroff_cont_poweroff, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_poweroff_cont_poweroff); // 使用页面管理模块时，需要对容器进行适配
	lv_page_manager_preempt_page_cont_adapte(ui->screen_poweroff_cont_poweroff); // 适配为抢断页面

	//Write style for screen_poweroff_cont_poweroff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_poweroff_cont_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_poweroff_cont_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_poweroff_cont_poweroff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_poweroff_cont_poweroff, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_poweroff_cont_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_poweroff_cont_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_poweroff_cont_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_poweroff_cont_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_poweroff_cont_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_poweroff_img_sys_poweroff
	ui->screen_poweroff_img_sys_poweroff = lv_img_create(ui->screen_poweroff_cont_poweroff);
	lv_obj_add_flag(ui->screen_poweroff_img_sys_poweroff, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_poweroff_img_sys_poweroff, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\sys_poweroff.png");
#else
	lv_img_set_src(ui->screen_poweroff_img_sys_poweroff, "F:/sys_poweroff.bin");
#endif
	lv_img_set_pivot(ui->screen_poweroff_img_sys_poweroff, 50,50);
	lv_img_set_angle(ui->screen_poweroff_img_sys_poweroff, 0);
	lv_obj_set_pos(ui->screen_poweroff_img_sys_poweroff, 181, 50);
	lv_obj_set_size(ui->screen_poweroff_img_sys_poweroff, 75, 75);

	//Write style for screen_poweroff_img_sys_poweroff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_poweroff_img_sys_poweroff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_poweroff_img_sys_reset
	ui->screen_poweroff_img_sys_reset = lv_img_create(ui->screen_poweroff_cont_poweroff);
	lv_obj_add_flag(ui->screen_poweroff_img_sys_reset, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_poweroff_img_sys_reset, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\sys_reset.png");
#else
	lv_img_set_src(ui->screen_poweroff_img_sys_reset, "F:/sys_reset.bin");
#endif
	lv_img_set_pivot(ui->screen_poweroff_img_sys_reset, 50,50);
	lv_img_set_angle(ui->screen_poweroff_img_sys_reset, 0);
	lv_obj_set_pos(ui->screen_poweroff_img_sys_reset, 57, 50);
	lv_obj_set_size(ui->screen_poweroff_img_sys_reset, 75, 75);

	//Write style for screen_poweroff_img_sys_reset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_poweroff_img_sys_reset, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_poweroff_label_sys_reset
	ui->screen_poweroff_label_sys_reset = lv_label_create(ui->screen_poweroff_cont_poweroff);
	lv_label_set_text(ui->screen_poweroff_label_sys_reset, "重启");
	lv_label_set_long_mode(ui->screen_poweroff_label_sys_reset, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_set_pos(ui->screen_poweroff_label_sys_reset, 44, 134);
	lv_obj_set_size(ui->screen_poweroff_label_sys_reset, 100, 20);

	//Write style for screen_poweroff_label_sys_reset, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_poweroff_label_sys_reset, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_poweroff_label_sys_reset, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_poweroff_label_sys_reset, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_poweroff_label_sys_reset, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_poweroff_label_sys_reset, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_poweroff_label_sys_poweroff
	ui->screen_poweroff_label_sys_poweroff = lv_label_create(ui->screen_poweroff_cont_poweroff);
	lv_label_set_text(ui->screen_poweroff_label_sys_poweroff, "关机");
	lv_label_set_long_mode(ui->screen_poweroff_label_sys_poweroff, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_set_pos(ui->screen_poweroff_label_sys_poweroff, 170, 134);
	lv_obj_set_size(ui->screen_poweroff_label_sys_poweroff, 100, 20);

	//Write style for screen_poweroff_label_sys_poweroff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_poweroff_label_sys_poweroff, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_poweroff_label_sys_poweroff, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_poweroff_label_sys_poweroff, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_poweroff_label_sys_poweroff, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_poweroff_label_sys_poweroff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_poweroff);

	
}
