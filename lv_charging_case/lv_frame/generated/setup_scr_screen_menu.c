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


void setup_scr_screen_menu(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_menu
	ui->screen_menu = lv_obj_create(page);
	lv_obj_set_size(ui->screen_menu, 320, 172);

	//Write style for screen_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_menu); // 使用页面管理模块时，需对页面进行适配
#if 0
	//Write codes screen_menu_cont_menu
	ui->screen_menu_cont_menu = lv_obj_create(ui->screen_menu);
	lv_obj_set_pos(ui->screen_menu_cont_menu, 0, 0);
	lv_obj_set_size(ui->screen_menu_cont_menu, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_menu_cont_menu, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_menu_cont_menu); // 使用页面管理模块时，需要对容器进行适配

	//Write style for screen_menu_cont_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_menu_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_menu_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_menu_cont_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_menu_cont_menu, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_menu_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_menu_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_menu_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_menu_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_menu_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
#endif

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_menu);

	
}
