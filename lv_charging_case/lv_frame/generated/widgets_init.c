/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"
#include <stdlib.h>


__attribute__((unused)) void kb_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL){
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb (lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
#if LV_USE_KEYBOARD || LV_USE_ZH_KEYBOARD
    lv_obj_t *ta = lv_event_get_target(e);
#endif
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
    {

#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if(*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if(*min == 60)
    {
        *min = 0;
        if(*hour < 12)
        {
            (*hour)++;
        } else {
            (*hour)++;
            *hour = *hour %12;
        }
    }
}
#endif

const char * screen_loop_img_bg_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"C:\\Users\\12568\\Desktop\\�ͻ�Ŀ¼\\������ͼ��������\\earphone_320x172\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\bg.png",
#else
	"F:/bg.bin",
#endif
 
};

const char * screen_music_animimg_wait_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\wait_0.png",
#else
	"F:/wait_0.bin",
#endif
 
};
const char * screen_wallpaper_animimg_wp_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\wallpaper_00.png",
#else
	"F:/wallpaper_small_00.bin",
#endif
 
};
const lv_img_dsc_t * screen_charging_animimg_charging_imgs[1] = { 
	"F:/charging_00.bin", 
};
const char * screen_poweron_animimg_poweron_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\poweron_00.png",
#else
	"F:/poweron_00.bin",
#endif
 
};
const char * screen_call_animimg_call_bg_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"C:\\Users\\12568\\Desktop\\客户目录\\【内部】彩屏充电仓\\NXP_320x172_公版_新框架\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\bg.png",
#else
	"F:/bg.bin",
#endif
 
};
const char * screen_lock_animimg_lock_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"F:\\charging_case_sdk\\charging_case_ui\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\wallpaper_small_00.png",
#else
	"F:/wallpaper_00.bin",
#endif
 
};
const char * screen_alarm_ring_animimg_ring_bg_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\bg.png",
#else
	"F:/bg.bin",
#endif
 
};
const char * screen_pop_up_animimg_pop_l_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\l_in.jpg",
#else
	"F:/l_in.jpg",
#endif
 
};
const char * screen_pop_up_animimg_pop_r_imgs[1] = { 
#if LV_USE_GUIDER_SIMULATOR
	"F:\\charging_case_sdk\\ui\\charging_case_ui\\earphone_flash\\earphone\\import\\image\\r_in.jpg",
#else
	"F:/r_in.jpg",
#endif
 
};
