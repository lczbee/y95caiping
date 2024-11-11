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


void setup_scr_screen_weather(lv_ui *ui, lv_obj_t *page)
{
	//Write codes screen_weather
	ui->screen_weather = lv_obj_create(page);
	lv_obj_set_size(ui->screen_weather, 320, 172);

	//Write style for screen_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_cont_weather
	ui->screen_weather_cont_weather = lv_obj_create(ui->screen_weather);
	lv_obj_set_pos(ui->screen_weather_cont_weather, 0, 0);
	lv_obj_set_size(ui->screen_weather_cont_weather, 320, 172);
	lv_obj_set_scrollbar_mode(ui->screen_weather_cont_weather, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_weather_cont_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_weather_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_weather_cont_weather, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_clear_flag(ui->screen_weather_cont_weather, LV_OBJ_FLAG_GESTURE_BUBBLE);

	//Write codes screen_weather_img_weather
	ui->screen_weather_img_weather = lv_img_create(ui->screen_weather_cont_weather);
	lv_obj_add_flag(ui->screen_weather_img_weather, LV_OBJ_FLAG_CLICKABLE);
	lv_obj_add_flag(ui->screen_weather_img_weather, LV_OBJ_FLAG_GESTURE_BUBBLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_weather_img_weather, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\bg_day.png");
#else
	lv_img_set_src(ui->screen_weather_img_weather, "F:/bg_day.bin");
#endif
	lv_img_set_pivot(ui->screen_weather_img_weather, 50,50);
	lv_img_set_angle(ui->screen_weather_img_weather, 0);
	lv_obj_set_pos(ui->screen_weather_img_weather, 0, 0);
	lv_obj_set_size(ui->screen_weather_img_weather, 320, 172);

	//Write style for screen_weather_img_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_weather_img_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_label_temperature
	ui->screen_weather_label_temperature = lv_label_create(ui->screen_weather_cont_weather);
	lv_label_set_text(ui->screen_weather_label_temperature, "23°");
	lv_label_set_long_mode(ui->screen_weather_label_temperature, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_weather_label_temperature, 98, 27);
	lv_obj_set_size(ui->screen_weather_label_temperature, 114, 51);

	//Write style for screen_weather_label_temperature, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_weather_label_temperature, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_weather_label_temperature, &lv_customer_font_pingfangheiti_bold_56, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_weather_label_temperature, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_weather_label_temperature, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_weather_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_label_weather
	ui->screen_weather_label_weather = lv_label_create(ui->screen_weather_cont_weather);
	lv_label_set_text(ui->screen_weather_label_weather, "晴");
	lv_label_set_long_mode(ui->screen_weather_label_weather, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_weather_label_weather, 157, 59);
	lv_obj_set_size(ui->screen_weather_label_weather, 106, 17);

	//Write style for screen_weather_label_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_weather_label_weather, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_weather_label_weather, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_weather_label_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_weather_label_weather, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_weather_label_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_img_wind
	ui->screen_weather_img_wind = lv_img_create(ui->screen_weather_cont_weather);
	lv_obj_add_flag(ui->screen_weather_img_wind, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_weather_img_wind, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\wind.png");
#else
	lv_img_set_src(ui->screen_weather_img_wind, "F:/wind.bin");
#endif
	lv_img_set_pivot(ui->screen_weather_img_wind, 50,50);
	lv_img_set_angle(ui->screen_weather_img_wind, 0);
	lv_obj_set_pos(ui->screen_weather_img_wind, 252, 98);
	lv_obj_set_size(ui->screen_weather_img_wind, 20, 20);

	//Write style for screen_weather_img_wind, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_weather_img_wind, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_img_location
	ui->screen_weather_img_location = lv_img_create(ui->screen_weather_cont_weather);
	lv_obj_add_flag(ui->screen_weather_img_location, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_weather_img_location, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\pos_1.png");
#else
	lv_img_set_src(ui->screen_weather_img_location, "F:/location.bin");
#endif
	lv_img_set_pivot(ui->screen_weather_img_location, 50,50);
	lv_img_set_angle(ui->screen_weather_img_location, 0);
	lv_obj_set_pos(ui->screen_weather_img_location, 79, 98);
	lv_obj_set_size(ui->screen_weather_img_location, 20, 20);

	//Write style for screen_weather_img_location, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_weather_img_location, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_img_humidness
	ui->screen_weather_img_humidness = lv_img_create(ui->screen_weather_cont_weather);
	lv_obj_add_flag(ui->screen_weather_img_humidness, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_weather_img_humidness, "F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\temperature.png");
#else
	lv_img_set_src(ui->screen_weather_img_humidness, "F:/temperature.bin");
#endif
	lv_img_set_pivot(ui->screen_weather_img_humidness, 50,50);
	lv_img_set_angle(ui->screen_weather_img_humidness, 0);
	lv_obj_set_pos(ui->screen_weather_img_humidness, 7, 98);
	lv_obj_set_size(ui->screen_weather_img_humidness, 20, 20);

	//Write style for screen_weather_img_humidness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_weather_img_humidness, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_label_location
	ui->screen_weather_label_location = lv_label_create(ui->screen_weather_cont_weather);
	lv_label_set_text(ui->screen_weather_label_location, "广东省/深圳市");
	lv_label_set_long_mode(ui->screen_weather_label_location, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_weather_label_location, 103, 96);
	lv_obj_set_size(ui->screen_weather_label_location, 138, 21);

	//Write style for screen_weather_label_location, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_weather_label_location, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_weather_label_location, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_weather_label_location, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_weather_label_location, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_weather_label_location, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_label_humidness
	ui->screen_weather_label_humidness = lv_label_create(ui->screen_weather_cont_weather);
	lv_label_set_text(ui->screen_weather_label_humidness, "25%");
	lv_label_set_long_mode(ui->screen_weather_label_humidness, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_weather_label_humidness, 31, 96);
	lv_obj_set_size(ui->screen_weather_label_humidness, 49, 24);

	//Write style for screen_weather_label_humidness, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_weather_label_humidness, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_weather_label_humidness, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_weather_label_humidness, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_weather_label_humidness, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_weather_label_humidness, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_weather_label_wind
	ui->screen_weather_label_wind = lv_label_create(ui->screen_weather_cont_weather);
	lv_label_set_text(ui->screen_weather_label_wind, "1级");
	lv_label_set_long_mode(ui->screen_weather_label_wind, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_weather_label_wind, 274, 96);
	lv_obj_set_size(ui->screen_weather_label_wind, 38, 19);

	//Write style for screen_weather_label_wind, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_weather_label_wind, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_weather_label_wind, &myFont, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_weather_label_wind, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_weather_label_wind, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_weather_label_wind, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_weather);

	
}
