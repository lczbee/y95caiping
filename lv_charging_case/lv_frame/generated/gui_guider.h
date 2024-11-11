/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_music;
	bool screen_music_del;
	lv_obj_t *screen_music_cont_music;
	lv_obj_t *screen_music_imgbtn_music_pre;
	lv_obj_t *screen_music_imgbtn_music_pre_label;
	lv_obj_t *screen_music_imgbtn_music_next;
	lv_obj_t *screen_music_imgbtn_music_next_label;
	lv_obj_t *screen_music_imgbtn_music_play_or_stop;
	lv_obj_t *screen_music_imgbtn_music_play_or_stop_label;
	lv_obj_t *screen_music_label_music_title;
	lv_obj_t *screen_music_img_music_logo;
	lv_obj_t *screen_music_img_music_sd_list;
	lv_obj_t *screen_music_img_music_lyric;
	lv_obj_t *screen_music_img_music_change;
	lv_obj_t *screen_music_cont_music_list;
	lv_obj_t *screen_music_cont_tip;
	lv_obj_t *screen_music_label_tip;
	lv_obj_t *screen_music_spinner_wait;
	lv_obj_t *screen_music_btn_cancel;
	lv_obj_t *screen_music_btn_cancel_label;
	lv_obj_t *screen_music_btn_confirm;
	lv_obj_t *screen_music_btn_confirm_label;
	lv_obj_t *screen_music_animimg_wait;
	lv_obj_t *screen_music_cont_lyrics;
	lv_obj_t *screen_volume;
	bool screen_volume_del;
	lv_obj_t *screen_volume_cont_vol;
	lv_obj_t *screen_volume_imgbtn_vol_down;
	lv_obj_t *screen_volume_imgbtn_vol_down_label;
	lv_obj_t *screen_volume_imgbtn_vol_up;
	lv_obj_t *screen_volume_imgbtn_vol_up_label;
	lv_obj_t *screen_volume_label_vol;
	lv_obj_t *screen_volume_label_vol_title;
	lv_obj_t *screen_anc;
	bool screen_anc_del;
	lv_obj_t *screen_anc_cont_anc;
	lv_obj_t *screen_anc_imgbtn_anc_close;
	lv_obj_t *screen_anc_imgbtn_anc_close_label;
	lv_obj_t *screen_anc_imgbtn_anc_open;
	lv_obj_t *screen_anc_imgbtn_anc_open_label;
	lv_obj_t *screen_anc_imgbtn_anc_transparent;
	lv_obj_t *screen_anc_imgbtn_anc_transparent_label;
	lv_obj_t *screen_anc_label_anc_title;
	lv_obj_t *screen_equalizer;
	bool screen_equalizer_del;
	lv_obj_t *screen_equalizer_cont_eq;
	lv_obj_t *screen_equalizer_imgbtn_eq_pre;
	lv_obj_t *screen_equalizer_imgbtn_eq_pre_label;
	lv_obj_t *screen_equalizer_imgbtn_eq_next;
	lv_obj_t *screen_equalizer_imgbtn_eq_next_label;
	lv_obj_t *screen_equalizer_label_eq_title;
	lv_obj_t *screen_equalizer_label_eq_mode;
	lv_obj_t *screen_alarm;
	bool screen_alarm_del;
	lv_obj_t *screen_alarm_cont_alarm;
	lv_obj_t *screen_alarm_imgbtn_alarm_time_down;
	lv_obj_t *screen_alarm_imgbtn_alarm_time_down_label;
	lv_obj_t *screen_alarm_imgbtn_alarm_time_up;
	lv_obj_t *screen_alarm_imgbtn_alarm_time_up_label;
	lv_obj_t *screen_alarm_label_alarm_time;
	lv_obj_t *screen_alarm_imgbtn_alarm_setting;
	lv_obj_t *screen_alarm_imgbtn_alarm_setting_label;
	lv_obj_t *screen_alarm_label_alarm_title;
	lv_obj_t *screen_alarm_cont_alarm_count;
	lv_obj_t *screen_alarm_label_alarm_count_title;
	lv_obj_t *screen_alarm_imgbtn_alarm_cancel;
	lv_obj_t *screen_alarm_imgbtn_alarm_cancel_label;
	lv_obj_t *screen_alarm_label_alarm_count;
	lv_obj_t *screen_brightness;
	bool screen_brightness_del;
	lv_obj_t *screen_brightness_cont_bn;
	lv_obj_t *screen_brightness_imgbtn_bn_up;
	lv_obj_t *screen_brightness_imgbtn_bn_up_label;
	lv_obj_t *screen_brightness_imgbtn_bn_down;
	lv_obj_t *screen_brightness_imgbtn_bn_down_label;
	lv_obj_t *screen_brightness_slider_bn;
	lv_obj_t *screen_brightness_label_bn_title;
	lv_obj_t *screen_language;
	bool screen_language_del;
	lv_obj_t *screen_language_cont_lang;
	lv_obj_t *screen_language_imgbtn_lang_next;
	lv_obj_t *screen_language_imgbtn_lang_next_label;
	lv_obj_t *screen_language_imgbtn_lang_pre;
	lv_obj_t *screen_language_imgbtn_lang_pre_label;
	lv_obj_t *screen_language_label_lang;
	lv_obj_t *screen_language_label_lang_title;
	lv_obj_t *screen_wallpaper;
	bool screen_wallpaper_del;
	lv_obj_t *screen_wallpaper_cont_wp;
	lv_obj_t *screen_wallpaper_imgbtn_wp_next;
	lv_obj_t *screen_wallpaper_imgbtn_wp_next_label;
	lv_obj_t *screen_wallpaper_imgbtn_wp_pre;
	lv_obj_t *screen_wallpaper_imgbtn_wp_pre_label;
	lv_obj_t *screen_wallpaper_label_wp_title;
	lv_obj_t *screen_wallpaper_cont_anim_wp;
	lv_obj_t *screen_wallpaper_animimg_wp;
	lv_obj_t *screen_wallpaper_jt;
	lv_obj_t *screen_wallpaper_jt_tp;



	lv_obj_t *screen_squelch;
	bool screen_squelch_del;
	lv_obj_t *screen_squelch_cont_sq;
	lv_obj_t *screen_squelch_imgbtn_sq_start;
	lv_obj_t *screen_squelch_imgbtn_sq_start_label;
	lv_obj_t *screen_squelch_label_sq_time;
	lv_obj_t *screen_squelch_label_sq_title;
	lv_obj_t *screen_squelch_img_sq;
	lv_obj_t *screen_squelch_img_sleep;
	lv_obj_t *screen_squelch_label_sleep_time;
	lv_obj_t *screen_squelch_cont_sq_ing;
	lv_obj_t *screen_squelch_label_sq_ing_title;
	lv_obj_t *screen_squelch_label_sq_ing;
	lv_obj_t *screen_squelch_imgbtn_sq_ing_cancel;
	lv_obj_t *screen_squelch_imgbtn_sq_ing_cancel_label;
	lv_obj_t *screen_findmy;
	bool screen_findmy_del;
	lv_obj_t *screen_findmy_cont_findmy;
	lv_obj_t *screen_findmy_imgbtn_findmy_left;
	lv_obj_t *screen_findmy_imgbtn_findmy_left_label;
	lv_obj_t *screen_findmy_label_findmy_title;
	lv_obj_t *screen_findmy_imgbtn_findmy_right;
	lv_obj_t *screen_findmy_imgbtn_findmy_right_label;
	lv_obj_t *screen_findmy_cont_findmy_confirm;
	lv_obj_t *screen_findmy_imgbtn_findmy_cancel;
	lv_obj_t *screen_findmy_imgbtn_findmy_cancel_label;
	lv_obj_t *screen_findmy_imgbtn_findmy_start;
	lv_obj_t *screen_findmy_imgbtn_findmy_start_label;
	lv_obj_t *screen_findmy_img_findmy_confirm;
	lv_obj_t *screen_findmy_label_findmy_confirm_title;
	lv_obj_t *screen_light;
	bool screen_light_del;
	lv_obj_t *screen_light_cont_light;
	lv_obj_t *screen_light_label_light_title;
	lv_obj_t *screen_light_imgbtn_light_on;
	lv_obj_t *screen_light_imgbtn_light_on_label;
	lv_obj_t *screen_light_cont_lighting;
	lv_obj_t *screen_time;
	bool screen_time_del;
	lv_obj_t *screen_time_cont_time;
	lv_obj_t *screen_time_label_time_set;
	lv_obj_t *screen_time_label_YMD;
	lv_obj_t *screen_time_label_HMS;
	lv_obj_t *screen_time_cont_set_YMD;
	lv_obj_t *screen_time_label_YMD_return;
	lv_obj_t *screen_time_label_YMD_save;
	lv_obj_t *screen_time_roller_year;
	lv_obj_t *screen_time_roller_month;
	lv_obj_t *screen_time_roller_day;
	lv_obj_t *screen_time_cont_set_HMS;
	lv_obj_t *screen_time_label_HMS_return;
	lv_obj_t *screen_time_label_HMS_save;
	lv_obj_t *screen_time_roller_sec;
	lv_obj_t *screen_time_roller_min;
	lv_obj_t *screen_time_roller_hour;
	lv_obj_t *screen_time_roller_ampm;
	lv_obj_t *screen_tiktok;
	bool screen_tiktok_del;
	lv_obj_t *screen_tiktok_cont_tiktok;
	lv_obj_t *screen_tiktok_img_tiktok_like;
	lv_obj_t *screen_tiktok_imgbtn_tiktok_pre;
	lv_obj_t *screen_tiktok_imgbtn_tiktok_pre_label;
	lv_obj_t *screen_tiktok_imgbtn_tiktok_next;
	lv_obj_t *screen_tiktok_imgbtn_tiktok_next_label;
	lv_obj_t *screen_tiktok_label_tiktok_like;
	lv_obj_t *screen_tiktok_cont_rejust;
	lv_obj_t *screen_tiktok_img_left;
	lv_obj_t *screen_tiktok_img_reset;
	lv_obj_t *screen_tiktok_img_up;
	lv_obj_t *screen_tiktok_img_right;
	lv_obj_t *screen_tiktok_img_down;
	lv_obj_t *screen_snap;
	bool screen_snap_del;
	lv_obj_t *screen_snap_cont_snap;
	lv_obj_t *screen_snap_img_snap;
	lv_obj_t *screen_charging;
	bool screen_charging_del;
	lv_obj_t *screen_charging_cont_charging;
	lv_obj_t *screen_charging_animimg_charging;
	lv_obj_t *screen_charging_label_charging;
	lv_obj_t *screen_poweron;
	bool screen_poweron_del;
	lv_obj_t *screen_poweron_cont_poweron;
	lv_obj_t *screen_poweron_animimg_poweron;
	lv_obj_t *screen_call;
	bool screen_call_del;
	lv_obj_t *screen_call_cont_call;
	lv_obj_t *screen_call_animimg_call_bg;
	lv_obj_t *screen_call_cont_call_incoming;
	lv_obj_t *screen_call_label_incoming_title;
	lv_obj_t *screen_call_img_incoming_hang_up;
	lv_obj_t *screen_call_img_incoming_answer;
	lv_obj_t *screen_call_cont_call_answering;
	lv_obj_t *screen_call_img_answering_hang_up;
	lv_obj_t *screen_call_img_answering_mute;
	lv_obj_t *screen_call_answering_time;
	lv_obj_t *screen_lock;
	bool screen_lock_del;
	lv_obj_t *screen_lock_cont_lock;
	lv_obj_t *screen_lock_animimg_lock;
	lv_obj_t *screen_lock_label_lock_hour;
	lv_obj_t *screen_lock_label_lock_min;
	lv_obj_t *screen_lock_label_lock_MD;
	lv_obj_t *screen_lock_label_lock_week;
	lv_obj_t *screen_product_test;
	bool screen_product_test_del;
	lv_obj_t *screen_product_test_cont_product_test;
	lv_obj_t *screen_product_test_cont_product_test_menu;
	lv_obj_t *screen_product_test_btn_screen;
	lv_obj_t *screen_product_test_btn_screen_label;
	lv_obj_t *screen_product_test_btn_tp;
	lv_obj_t *screen_product_test_btn_tp_label;
	lv_obj_t *screen_product_test_btn_connect;
	lv_obj_t *screen_product_test_btn_connect_label;
	lv_obj_t *screen_product_test_btn_reset;
	lv_obj_t *screen_product_test_btn_reset_label;
	lv_obj_t *screen_product_test_btn_pc;
	lv_obj_t *screen_product_test_btn_pc_label;
	lv_obj_t *screen_product_test_btn_storage_mode;
	lv_obj_t *screen_product_test_btn_storage_mode_label;
	lv_obj_t *screen_product_test_btn_reserve2;
	lv_obj_t *screen_product_test_btn_reserve2_label;
	lv_obj_t *screen_product_test_btn_reserve1;
	lv_obj_t *screen_product_test_btn_reserve1_label;
	lv_obj_t *screen_product_test_btn_bat;
	lv_obj_t *screen_product_test_btn_bat_label;
	lv_obj_t *screen_product_test_cont_tp_test;
	lv_obj_t *screen_product_test_btnm_tp_test;
	lv_obj_t *screen_product_test_cont_screen_test;
	lv_obj_t *screen_pc_mode;
	bool screen_pc_mode_del;
	lv_obj_t *screen_pc_mode_cont_pc_mode;
	lv_obj_t *screen_pc_mode_cont_plug_in_tip;
	lv_obj_t *screen_pc_mode_img_usb;
	lv_obj_t *screen_pc_mode_label_usb_tip;
	lv_obj_t *screen_pc_mode_cont_file;
	lv_obj_t *screen_pc_mode_img_file_transfer;
	lv_obj_t *screen_pc_mode_label_file_transfer;
	lv_obj_t *screen_pc_mode_sw_pc_mode;
	lv_obj_t *screen_alarm_ring;
	bool screen_alarm_ring_del;
	lv_obj_t *screen_alarm_ring_cont_alarm_ring;
	lv_obj_t *screen_alarm_ring_animimg_ring_bg;
	lv_obj_t *screen_alarm_ring_imgbtn_alarm_repeat;
	lv_obj_t *screen_alarm_ring_imgbtn_alarm_repeat_label;
	lv_obj_t *screen_alarm_ring_imgbtn_alarm_stop;
	lv_obj_t *screen_alarm_ring_imgbtn_alarm_stop_label;
	lv_obj_t *screen_alarm_ring_img_alarm_ring;
	lv_obj_t *screen_menu;
	bool screen_menu_del;
	lv_obj_t *screen_menu_cont_menu;
	lv_obj_t *screen_wooden_fish;
	bool screen_wooden_fish_del;
	lv_obj_t *screen_wooden_fish_cont_wooden_fish;
	lv_obj_t *screen_wooden_fish_label_virtue_title;
	lv_obj_t *screen_wooden_fish_label_virtue_num;
	lv_obj_t *screen_wooden_fish_label_cumulate1;
	lv_obj_t *screen_wooden_fish_label_cumulate2;
	lv_obj_t *screen_wooden_fish_label_cumulate3;
	lv_obj_t *screen_wooden_fish_label_cumulate4;
	lv_obj_t *screen_wooden_fish_img_wooden_fish;
	lv_obj_t *screen_weather;
	bool screen_weather_del;
	lv_obj_t *screen_weather_cont_weather;
	lv_obj_t *screen_weather_img_weather;
	lv_obj_t *screen_weather_label_temperature;
	lv_obj_t *screen_weather_label_weather;
	lv_obj_t *screen_weather_img_wind;
	lv_obj_t *screen_weather_img_location;
	lv_obj_t *screen_weather_img_humidness;
	lv_obj_t *screen_weather_label_location;
	lv_obj_t *screen_weather_label_humidness;
	lv_obj_t *screen_weather_label_wind;
	lv_obj_t *screen_pop_up;
	bool screen_pop_up_del;
	lv_obj_t *screen_pop_up_cont_pop_up;
	lv_obj_t *screen_pop_up_animimg_pop_l;
	lv_obj_t *screen_pop_up_animimg_pop_r;
	lv_obj_t *screen_poweroff;
	bool screen_poweroff_del;
	lv_obj_t *screen_poweroff_cont_poweroff;
	lv_obj_t *screen_poweroff_img_sys_poweroff;
	lv_obj_t *screen_poweroff_img_sys_reset;
	lv_obj_t *screen_poweroff_label_sys_reset;
	lv_obj_t *screen_poweroff_label_sys_poweroff;
	lv_obj_t *screen_upgrade;
	bool screen_upgrade_del;
	lv_obj_t *screen_upgrade_cont_upgarde;
	lv_obj_t *screen_upgrade_spinner_upgrade;
	lv_obj_t *screen_upgrade_label_upgrade_process;
	lv_obj_t *screen_upgrade_label_uograde_tips;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_screen_music(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_music_local_music(lv_ui *ui);
void setup_scr_screen_music_lyrics(lv_ui *ui);
void setup_scr_screen_volume(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_anc(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_equalizer(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_alarm(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_brightness(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_language(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_wallpaper(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_squelch(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_findmy(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_light(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_time(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_time_cont_set(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_tiktok(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_tiktok_rejust(lv_ui *ui);
void setup_scr_screen_snap(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_charging(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_poweron(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_call(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_lock(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_product_test(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_pc_mode(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_alarm_ring(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_menu(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_wooden_fish(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_weather(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_pop_up(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_poweroff(lv_ui *ui, lv_obj_t *page);
void setup_scr_screen_upgrade(lv_ui *ui, lv_obj_t *page);

LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_pingfangheiti_bold_18)
LV_FONT_DECLARE(lv_font_pingfangheiti_bold_32)
LV_FONT_DECLARE(lv_font_pingfangheiti_bold_22)
LV_FONT_DECLARE(lv_font_pingfangheiti_bold_16)
LV_FONT_DECLARE(lv_customer_font_pingfangheiti_bold_56)
LV_FONT_DECLARE(lv_customer_font_pingfangheiti_bold_24)
LV_FONT_DECLARE(lv_customer_font_arial_unicode_14)
LV_FONT_DECLARE(lv_customer_font_arial_unicode_18)
LV_FONT_DECLARE(lv_customer_font_arial_unicode_32)
LV_FONT_DECLARE(myFont)





#ifdef __cplusplus
}
#endif
#endif
