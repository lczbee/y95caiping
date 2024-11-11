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


void setup_scr_screen_wallpaper(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_wallpaper
	ui->screen_wallpaper = lv_obj_create(page);
	lv_obj_set_size(ui->screen_wallpaper, 320, 172);

	//Write style for screen_wallpaper, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wallpaper, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_page_adapte(ui->screen_wallpaper); // 使用页面管理模块时，需对页面进行适配
	// lv_page_manager_preempt_page_bg_adapte(ui->screen_wallpaper); // 适配为抢断页面

	//Write codes screen_wallpaper_cont_wp
	ui->screen_wallpaper_cont_wp = lv_obj_create(ui->screen_wallpaper);
	lv_obj_set_pos(ui->screen_wallpaper_cont_wp, 0, 0);
	lv_obj_set_size(ui->screen_wallpaper_cont_wp, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_wallpaper_cont_wp, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_cont_adapte(ui->screen_wallpaper_cont_wp); // 使用页面管理模块时，需要对容器进行适配
	// lv_page_manager_preempt_page_cont_adapte(ui->screen_wallpaper_cont_wp); // 适配为抢断页面

	//Write style for screen_wallpaper_cont_wp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wallpaper_cont_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wallpaper_cont_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wallpaper_cont_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wallpaper_cont_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wallpaper_cont_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wallpaper_cont_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wallpaper_cont_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_cont_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wallpaper_imgbtn_wp_next
	ui->screen_wallpaper_imgbtn_wp_next = lv_imgbtn_create(ui->screen_wallpaper_cont_wp);
	lv_obj_add_flag(ui->screen_wallpaper_imgbtn_wp_next, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_next, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia.png", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_next, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_next, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia.png", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_next, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_xia_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_next, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_xia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_next, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_xia_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_next, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_xia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_next, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_xia_anxia.bin", NULL);
#endif
	ui->screen_wallpaper_imgbtn_wp_next_label = lv_label_create(ui->screen_wallpaper_imgbtn_wp_next);
	lv_label_set_text(ui->screen_wallpaper_imgbtn_wp_next_label, "");
	lv_label_set_long_mode(ui->screen_wallpaper_imgbtn_wp_next_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_wallpaper_imgbtn_wp_next_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_wallpaper_imgbtn_wp_next, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_wallpaper_imgbtn_wp_next, 243, 67);
	lv_obj_set_size(ui->screen_wallpaper_imgbtn_wp_next, 60, 60);

	//Write style for screen_wallpaper_imgbtn_wp_next, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_wallpaper_imgbtn_wp_next, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wallpaper_imgbtn_wp_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wallpaper_imgbtn_wp_next, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_imgbtn_wp_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_wallpaper_imgbtn_wp_next); // 传递消息给父控件

	//Write style for screen_wallpaper_imgbtn_wp_next, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_wallpaper_imgbtn_wp_next, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_wallpaper_imgbtn_wp_next, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_wallpaper_imgbtn_wp_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_imgbtn_wp_next, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_wallpaper_imgbtn_wp_next, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_wallpaper_imgbtn_wp_next, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_wallpaper_imgbtn_wp_next, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_wallpaper_imgbtn_wp_next, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_imgbtn_wp_next, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_wallpaper_imgbtn_wp_next, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_wallpaper_imgbtn_wp_next, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_wallpaper_imgbtn_wp_pre
	ui->screen_wallpaper_imgbtn_wp_pre = lv_imgbtn_create(ui->screen_wallpaper_cont_wp);
	lv_obj_add_flag(ui->screen_wallpaper_imgbtn_wp_pre, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_pre, LV_IMGBTN_STATE_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang.png", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_pre, LV_IMGBTN_STATE_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang_anxia.png", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_pre, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang.png", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_pre, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_shang_anxia.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_pre, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_shang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_pre, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_shang_anxia.bin", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_pre, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_shang.bin", NULL);
	lv_imgbtn_set_src(ui->screen_wallpaper_imgbtn_wp_pre, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_shang_anxia.bin", NULL);
#endif
	ui->screen_wallpaper_imgbtn_wp_pre_label = lv_label_create(ui->screen_wallpaper_imgbtn_wp_pre);
	lv_label_set_text(ui->screen_wallpaper_imgbtn_wp_pre_label, "");
	lv_label_set_long_mode(ui->screen_wallpaper_imgbtn_wp_pre_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_wallpaper_imgbtn_wp_pre_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_wallpaper_imgbtn_wp_pre, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_wallpaper_imgbtn_wp_pre, 18, 68);
	lv_obj_set_size(ui->screen_wallpaper_imgbtn_wp_pre, 60, 60);

	//Write style for screen_wallpaper_imgbtn_wp_pre, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_wallpaper_imgbtn_wp_pre, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wallpaper_imgbtn_wp_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wallpaper_imgbtn_wp_pre, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_imgbtn_wp_pre, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_wallpaper_imgbtn_wp_pre); // 传递消息给父控件

	//Write style for screen_wallpaper_imgbtn_wp_pre, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_wallpaper_imgbtn_wp_pre, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_wallpaper_imgbtn_wp_pre, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_wallpaper_imgbtn_wp_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_imgbtn_wp_pre, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_wallpaper_imgbtn_wp_pre, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_wallpaper_imgbtn_wp_pre, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_wallpaper_imgbtn_wp_pre, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_wallpaper_imgbtn_wp_pre, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_imgbtn_wp_pre, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_wallpaper_imgbtn_wp_pre, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_wallpaper_imgbtn_wp_pre, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_wallpaper_label_wp_title
	ui->screen_wallpaper_label_wp_title = lv_label_create(ui->screen_wallpaper_cont_wp);
	lv_label_set_text(ui->screen_wallpaper_label_wp_title, "锁屏壁纸");
	lv_label_set_long_mode(ui->screen_wallpaper_label_wp_title, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->screen_wallpaper_label_wp_title, 0, 33);
	lv_obj_set_size(ui->screen_wallpaper_label_wp_title, 320, 35);

	//Write style for screen_wallpaper_label_wp_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wallpaper_label_wp_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wallpaper_label_wp_title, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wallpaper_label_wp_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wallpaper_label_wp_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_label_wp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	
	//自己创建一个静态壁纸界面
	ui->screen_wallpaper_jt = lv_img_create(ui->screen_wallpaper_cont_wp);
	lv_obj_add_flag(ui->screen_wallpaper_jt, LV_OBJ_FLAG_CHECKABLE);

	lv_img_set_src(ui->screen_wallpaper_jt, "F:/test1.bin");
	lv_img_set_pivot(ui->screen_wallpaper_jt, 50,50);
	lv_img_set_angle(ui->screen_wallpaper_jt, 0);
	lv_obj_set_pos(ui->screen_wallpaper_jt, 90, 68);
	lv_obj_set_size(ui->screen_wallpaper_jt, 140, 60);

	lv_obj_set_style_img_opa(ui->screen_wallpaper_jt, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_page_manager_obj_adapte(ui->screen_wallpaper_jt);


	// ui->screen_wallpaper_jt_tp = lv_imgbtn_create(ui->screen_wallpaper_cont_wp);
	// lv_obj_add_flag(ui->screen_wallpaper_jt_tp, LV_OBJ_FLAG_CHECKABLE);

	// lv_img_set_src(ui->screen_wallpaper_jt_tp, "F:/test1.bin");
	// lv_img_set_pivot(ui->screen_wallpaper_jt_tp, 50,50);
	// lv_img_set_angle(ui->screen_wallpaper_jt_tp, 0);
	// lv_obj_set_pos(ui->screen_wallpaper_jt_tp, 90, 68);
	// lv_obj_set_size(ui->screen_wallpaper_jt_tp, 140, 60);

	// lv_obj_set_style_img_opa(ui->screen_wallpaper_jt_tp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_page_manager_obj_adapte(ui->screen_wallpaper_jt_tp);
	
/*
	//留存之前的代码
	//Write codes screen_wallpaper_cont_anim_wp
	ui->screen_wallpaper_cont_anim_wp = lv_obj_create(ui->screen_wallpaper_cont_wp);
	lv_obj_set_pos(ui->screen_wallpaper_cont_anim_wp, 94, 64);
	lv_obj_set_size(ui->screen_wallpaper_cont_anim_wp, 140, 60);
	lv_obj_set_scrollbar_mode(ui->screen_wallpaper_cont_anim_wp, LV_SCROLLBAR_MODE_OFF);
	lv_page_manager_obj_adapte(ui->screen_wallpaper_cont_anim_wp); // 传递消息给父控件

	lv_obj_clear_flag(ui->screen_wallpaper_cont_anim_wp, LV_OBJ_FLAG_SCROLLABLE);

	//Write style for screen_wallpaper_cont_anim_wp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wallpaper_cont_anim_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wallpaper_cont_anim_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wallpaper_cont_anim_wp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wallpaper_cont_anim_wp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wallpaper_cont_anim_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wallpaper_cont_anim_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wallpaper_cont_anim_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wallpaper_cont_anim_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wallpaper_cont_anim_wp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wallpaper_animimg_wp
	ui->screen_wallpaper_animimg_wp = lv_animimg_create(ui->screen_wallpaper_cont_anim_wp);
	lv_animimg_set_src(ui->screen_wallpaper_animimg_wp, (const void **) screen_wallpaper_animimg_wp_imgs, 1);
	lv_animimg_set_duration(ui->screen_wallpaper_animimg_wp, 100);
#if EXTERN_ANIMING
	// usr_update_animing(ui->screen_wallpaper_animimg_wp, "L1S");
	// usr_free_animing(ui->screen_wallpaper_animimg_wp, (const void **) screen_wallpaper_animimg_wp_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	// usr_update_animing(ui->screen_wallpaper_animimg_wp, lock_small_tab[cur_lock_index]);
#endif
	lv_animimg_set_repeat_count(ui->screen_wallpaper_animimg_wp, LV_ANIM_REPEAT_INFINITE);
	lv_animimg_start(ui->screen_wallpaper_animimg_wp);
	lv_obj_set_pos(ui->screen_wallpaper_animimg_wp, 0, 0);
	lv_obj_set_size(ui->screen_wallpaper_animimg_wp, 140, 60);
	lv_obj_add_flag(ui->screen_wallpaper_animimg_wp, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_clear_flag(ui->screen_wallpaper_animimg_wp, LV_OBJ_FLAG_SCROLLABLE);
	lv_page_manager_obj_adapte(ui->screen_wallpaper_animimg_wp); // 传递消息给父控件
	
	// lv_obj_set_style_transform_zoom(ui->screen_wallpaper_cont_anim_wp, 120, 0);
	// lv_obj_set_style_transform_pivot_x(ui->screen_wallpaper_cont_anim_wp, 160, 0);s
	// lv_obj_set_style_transform_pivot_y(ui->screen_wallpaper_cont_anim_wp, 105, 0);
*/
	//Update current screen layout.
	lv_obj_update_layout(ui->screen_wallpaper);

	
}
