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


void setup_scr_screen_alarm_ring(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_alarm_ring
	ui->screen_alarm_ring = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_alarm_ring, 320, 172);

	//Write style for screen_alarm_ring, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_alarm_ring_cont_alarm_ring
	ui->screen_alarm_ring_cont_alarm_ring = lv_obj_create(ui->screen_alarm_ring);
	lv_obj_set_pos(ui->screen_alarm_ring_cont_alarm_ring, 0, 0);
	lv_obj_set_size(ui->screen_alarm_ring_cont_alarm_ring, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_alarm_ring_cont_alarm_ring, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_alarm_ring_cont_alarm_ring, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_alarm_ring_cont_alarm_ring, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_alarm_ring_cont_alarm_ring, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_ring_cont_alarm_ring, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_alarm_ring_animimg_ring_bg
	ui->screen_alarm_ring_animimg_ring_bg = lv_animimg_create(ui->screen_alarm_ring_cont_alarm_ring);
	lv_animimg_set_src(ui->screen_alarm_ring_animimg_ring_bg, (const void **) screen_alarm_ring_animimg_ring_bg_imgs, 1);
	lv_animimg_set_duration(ui->screen_alarm_ring_animimg_ring_bg, 30*1);
	lv_animimg_set_repeat_count(ui->screen_alarm_ring_animimg_ring_bg, LV_ANIM_REPEAT_INFINITE);
	lv_img_set_src(ui->screen_alarm_ring_animimg_ring_bg, screen_alarm_ring_animimg_ring_bg_imgs[0]);
	lv_obj_set_pos(ui->screen_alarm_ring_animimg_ring_bg, 0, 0);
	lv_obj_set_size(ui->screen_alarm_ring_animimg_ring_bg, 320, 172);

	//Write codes screen_alarm_ring_imgbtn_alarm_repeat
	ui->screen_alarm_ring_imgbtn_alarm_repeat = lv_imgbtn_create(ui->screen_alarm_ring_cont_alarm_ring);
	lv_obj_add_flag(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_RELEASED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_chongfu.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_PRESSED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_chongfu.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_chongfu.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_chongfu.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_chongfu.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_chongfu.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_chongfu.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_chongfu.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_chongfu.bin", NULL);
#endif
	ui->screen_alarm_ring_imgbtn_alarm_repeat_label = lv_label_create(ui->screen_alarm_ring_imgbtn_alarm_repeat);
	lv_label_set_text(ui->screen_alarm_ring_imgbtn_alarm_repeat_label, "重复");
	lv_label_set_long_mode(ui->screen_alarm_ring_imgbtn_alarm_repeat_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_alarm_ring_imgbtn_alarm_repeat_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_alarm_ring_imgbtn_alarm_repeat, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_alarm_ring_imgbtn_alarm_repeat, 50, 100);
	lv_obj_set_size(ui->screen_alarm_ring_imgbtn_alarm_repeat, 82, 36);

	//Write style for screen_alarm_ring_imgbtn_alarm_repeat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_alarm_ring_imgbtn_alarm_repeat, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_ring_imgbtn_alarm_repeat, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_ring_imgbtn_alarm_repeat, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_ring_imgbtn_alarm_repeat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_alarm_ring_imgbtn_alarm_repeat, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_alarm_ring_imgbtn_alarm_repeat, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_alarm_ring_imgbtn_alarm_repeat, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_alarm_ring_imgbtn_alarm_repeat, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_ring_imgbtn_alarm_repeat, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_alarm_ring_imgbtn_alarm_repeat, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_alarm_ring_imgbtn_alarm_repeat, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_alarm_ring_imgbtn_alarm_repeat, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_alarm_ring_imgbtn_alarm_repeat, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_ring_imgbtn_alarm_repeat, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_alarm_ring_imgbtn_alarm_repeat, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_alarm_ring_imgbtn_alarm_repeat, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_alarm_ring_imgbtn_alarm_stop
	ui->screen_alarm_ring_imgbtn_alarm_stop = lv_imgbtn_create(ui->screen_alarm_ring_cont_alarm_ring);
	lv_obj_add_flag(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_OBJ_FLAG_CHECKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_RELEASED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_tingzhi.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_PRESSED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_tingzhi.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_tingzhi.png", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "E:\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\ic_tingzhi.png", NULL);
#else
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_dingshishezhi.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_dingshishezhi.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_dingshishezhi.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "F:/ic_dingshishezhi.bin", NULL);
	lv_imgbtn_set_src(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_IMGBTN_STATE_DISABLED, NULL, "F:/ic_dingshishezhi.bin", NULL);
#endif
	ui->screen_alarm_ring_imgbtn_alarm_stop_label = lv_label_create(ui->screen_alarm_ring_imgbtn_alarm_stop);
	lv_label_set_text(ui->screen_alarm_ring_imgbtn_alarm_stop_label, "停止");
	lv_label_set_long_mode(ui->screen_alarm_ring_imgbtn_alarm_stop_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_alarm_ring_imgbtn_alarm_stop_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_alarm_ring_imgbtn_alarm_stop, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_alarm_ring_imgbtn_alarm_stop, 188, 100);
	lv_obj_set_size(ui->screen_alarm_ring_imgbtn_alarm_stop, 82, 36);

	//Write style for screen_alarm_ring_imgbtn_alarm_stop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_alarm_ring_imgbtn_alarm_stop, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_alarm_ring_imgbtn_alarm_stop, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_alarm_ring_imgbtn_alarm_stop, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_alarm_ring_imgbtn_alarm_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_alarm_ring_imgbtn_alarm_stop, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
	lv_obj_set_style_img_opa(ui->screen_alarm_ring_imgbtn_alarm_stop, 255, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->screen_alarm_ring_imgbtn_alarm_stop, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->screen_alarm_ring_imgbtn_alarm_stop, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_ring_imgbtn_alarm_stop, 0, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style for screen_alarm_ring_imgbtn_alarm_stop, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
	lv_obj_set_style_img_opa(ui->screen_alarm_ring_imgbtn_alarm_stop, 255, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_color(ui->screen_alarm_ring_imgbtn_alarm_stop, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_text_font(ui->screen_alarm_ring_imgbtn_alarm_stop, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_obj_set_style_shadow_width(ui->screen_alarm_ring_imgbtn_alarm_stop, 0, LV_PART_MAIN|LV_STATE_CHECKED);

	//Write style for screen_alarm_ring_imgbtn_alarm_stop, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
	lv_obj_set_style_img_opa(ui->screen_alarm_ring_imgbtn_alarm_stop, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

	//Write codes screen_alarm_ring_img_alarm_ring
	ui->screen_alarm_ring_img_alarm_ring = lv_img_create(ui->screen_alarm_ring_cont_alarm_ring);
	lv_obj_add_flag(ui->screen_alarm_ring_img_alarm_ring, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_alarm_ring_img_alarm_ring, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\naozhong.png");
#else
	lv_img_set_src(ui->screen_alarm_ring_img_alarm_ring, "F:/naozhong.bin");
#endif
	lv_img_set_pivot(ui->screen_alarm_ring_img_alarm_ring, 50,50);
	lv_img_set_angle(ui->screen_alarm_ring_img_alarm_ring, 0);
	lv_obj_set_pos(ui->screen_alarm_ring_img_alarm_ring, 135, 40);
	lv_obj_set_size(ui->screen_alarm_ring_img_alarm_ring, 50, 50);

	//Write style for screen_alarm_ring_img_alarm_ring, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_alarm_ring_img_alarm_ring, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_alarm_ring);

	
}
