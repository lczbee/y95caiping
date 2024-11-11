#include "custom.h"

/***************************************************wallpaper*****************************************************/
const char *lock_week_tab[] = {"MON", "TUES", "WED", "THUR", "FRI", "SAT", "SUN"};
/***************************************************wallpaper*****************************************************/

static void screen_lock_init()
{
	printf("%s\n", __FUNCTION__);

	setup_scr_screen_lock(&guider_ui, NULL);
	events_init_screen_lock(&guider_ui);
	
}

static void screen_lock_deinit()
{
	printf("%s\n", __FUNCTION__);

	// usr_free_state_img(lock_big_tab[cur_lock_index]);
	if(guider_ui.screen_lock) {
		usr_free_animing(guider_ui.screen_lock_animimg_lock, (const void **) screen_lock_animimg_lock_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	}

	lv_obj_del(guider_ui.screen_lock);
	guider_ui.screen_lock = NULL;
}
static void screen_lock_load()
{
	lv_scr_load(guider_ui.screen_lock);
}


static void screen_lock_animimg_lock_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_GESTURE:
	{
        lv_indev_wait_release(lv_indev_get_act());
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir){
        case LV_DIR_LEFT:
            break;
        case LV_DIR_RIGHT:
			// 右滑隐藏锁屏壁纸（大）
			screen_list_del(SCREEN_PRIO_LOCK);
			break;
        }
		break;
	}
	default:
		break;
	}
}


void events_init_screen_lock(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_lock_animimg_lock, screen_lock_animimg_lock_event_handler, LV_EVENT_ALL, NULL);
}


void screen_lock_enter()
{
	screen_list_add(screen_lock_init, screen_lock_deinit, screen_lock_load, screen_lock_refresh, SCREEN_PRIO_LOCK);
}

void screen_lock_refresh()
{
	struct sys_time time = {0};

	sbox_get_sys_time(&time);
	// 更新锁屏时间
//    lv_label_set_text_fmt(guider_ui.screen_lock_label_lock_hour, "%02d", time.hour);
//    lv_label_set_text_fmt(guider_ui.screen_lock_label_lock_min, "%02d", time.min);
//    lv_label_set_text_fmt(guider_ui.screen_lock_label_lock_MD, "%02d/%02d", time.month, time.day);

	extern u8 rtc_calculate_week_val(struct sys_time *data_time);
	u8 week_day = rtc_calculate_week_val(&time);
	week_day = (week_day - 1 + 7) % 7;
//    lv_label_set_text_fmt(guider_ui.screen_lock_label_lock_week, "%s", lock_week_tab[week_day]);
}
