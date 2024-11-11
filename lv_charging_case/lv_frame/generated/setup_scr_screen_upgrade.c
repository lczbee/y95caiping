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


void setup_scr_screen_upgrade(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_upgrade
	ui->screen_upgrade = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_upgrade, 320, 172);

	//Write style for screen_upgrade, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_upgrade, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_upgrade); // 使用页面管理模块时，需对页面进行适配
	lv_page_manager_preempt_page_bg_adapte(ui->screen_upgrade); // 适配为抢断页面

	//Write codes screen_upgrade_cont_upgarde
	ui->screen_upgrade_cont_upgarde = lv_obj_create(ui->screen_upgrade);
	lv_obj_set_pos(ui->screen_upgrade_cont_upgarde, 0, 0);
	lv_obj_set_size(ui->screen_upgrade_cont_upgarde, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_upgrade_cont_upgarde, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_upgrade_cont_upgarde); // 使用页面管理模块时，需要对容器进行适配
	lv_page_manager_preempt_page_cont_adapte(ui->screen_upgrade_cont_upgarde); // 适配为抢断页面

	//Write style for screen_upgrade_cont_upgarde, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_upgrade_cont_upgarde, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_upgrade_cont_upgarde, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_upgrade_cont_upgarde, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_upgrade_cont_upgarde, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_upgrade_cont_upgarde, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_upgrade_cont_upgarde, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_upgrade_cont_upgarde, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_upgrade_cont_upgarde, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_upgrade_cont_upgarde, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_upgrade_spinner_upgrade
	ui->screen_upgrade_spinner_upgrade = lv_spinner_create(ui->screen_upgrade_cont_upgarde, 1000, 60);
	lv_obj_set_pos(ui->screen_upgrade_spinner_upgrade, 97, 27);
	lv_obj_set_size(ui->screen_upgrade_spinner_upgrade, 127, 119);

	//Write style for screen_upgrade_spinner_upgrade, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_pad_top(ui->screen_upgrade_spinner_upgrade, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_upgrade_spinner_upgrade, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_upgrade_spinner_upgrade, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_upgrade_spinner_upgrade, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_upgrade_spinner_upgrade, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->screen_upgrade_spinner_upgrade, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_upgrade_spinner_upgrade, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_upgrade_spinner_upgrade, lv_color_hex(0xd5d6de), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_upgrade_spinner_upgrade, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_upgrade_spinner_upgrade, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->screen_upgrade_spinner_upgrade, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->screen_upgrade_spinner_upgrade, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->screen_upgrade_spinner_upgrade, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_upgrade_label_upgrade_process
	ui->screen_upgrade_label_upgrade_process = lv_label_create(ui->screen_upgrade_cont_upgarde);
	lv_label_set_text(ui->screen_upgrade_label_upgrade_process, "0%");
	lv_label_set_long_mode(ui->screen_upgrade_label_upgrade_process, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_upgrade_label_upgrade_process, 122, 81);
	lv_obj_set_size(ui->screen_upgrade_label_upgrade_process, 69, 20);
	lv_obj_add_flag(ui->screen_upgrade_label_upgrade_process, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_upgrade_label_upgrade_process, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_upgrade_label_upgrade_process, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_upgrade_label_upgrade_process, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_upgrade_label_upgrade_process, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_upgrade_label_upgrade_process, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_upgrade_label_upgrade_process, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_upgrade_label_uograde_tips
	ui->screen_upgrade_label_uograde_tips = lv_label_create(ui->screen_upgrade_cont_upgarde);
	lv_label_set_text(ui->screen_upgrade_label_uograde_tips, "upgrading...");
	lv_label_set_long_mode(ui->screen_upgrade_label_uograde_tips, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_upgrade_label_uograde_tips, 0, 147);
	lv_obj_set_size(ui->screen_upgrade_label_uograde_tips, 320, 20);

	//Write style for screen_upgrade_label_uograde_tips, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_upgrade_label_uograde_tips, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_upgrade_label_uograde_tips, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_upgrade_label_uograde_tips, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_upgrade_label_uograde_tips, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_upgrade_label_uograde_tips, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_upgrade);

	
}
