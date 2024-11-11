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


void setup_scr_screen_snap(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_snap
	ui->screen_snap = lv_obj_create(page);
	lv_obj_set_size(ui->screen_snap, 320, 172);

	//Write style for screen_snap, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_snap); // 使用页面管理模块时，需对页面进行适配

	//Write codes screen_snap_cont_snap
	ui->screen_snap_cont_snap = lv_obj_create(ui->screen_snap);
	lv_obj_set_pos(ui->screen_snap_cont_snap, 0, 0);
	lv_obj_set_size(ui->screen_snap_cont_snap, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_snap_cont_snap, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_snap_cont_snap); // 使用页面管理模块时，需要对容器进行适配

	//Write style for screen_snap_cont_snap, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_snap_cont_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_snap_cont_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_snap_cont_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_snap_cont_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_snap_cont_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_snap_cont_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_snap_cont_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_snap_cont_snap, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_snap_img_snap
	ui->screen_snap_img_snap = lv_img_create(ui->screen_snap_cont_snap);
	lv_obj_add_flag(ui->screen_snap_img_snap, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_snap_img_snap, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\takephoto.png");
#else
	lv_img_set_src(ui->screen_snap_img_snap, "F:/takephoto.bin");
#endif
	lv_img_set_pivot(ui->screen_snap_img_snap, 50,50);
	lv_img_set_angle(ui->screen_snap_img_snap, 0);
	lv_obj_set_pos(ui->screen_snap_img_snap, 105, 29);
	lv_obj_set_size(ui->screen_snap_img_snap, 120, 120);

	//Write style for screen_snap_img_snap, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_snap_img_snap, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_snap_img_snap); // 传递消息给父控件

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_snap);

	
}
