#include "custom.h"

/**
 * @brief 闹钟响铃界面（属于抢断页面）
 * 
 */

static void screen_alarm_ring_init()
{
	printf("%s\n", __FUNCTION__);

	setup_scr_screen_alarm_ring(&guider_ui, NULL);
	events_init_screen_alarm_ring(&guider_ui);

}
static void screen_alarm_ring_deinit()
{
	printf("%s\n", __FUNCTION__);

	if(guider_ui.screen_alarm_ring) {
		usr_free_animing(guider_ui.screen_alarm_ring_animimg_ring_bg, (const void **) screen_loop_img_bg_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	}

	lv_obj_del(guider_ui.screen_alarm_ring);
	guider_ui.screen_alarm_ring = NULL;
}
static void screen_alarm_ring_load()
{
	lv_scr_load(guider_ui.screen_alarm_ring);
}
void screen_alarm_ring_refresh()
{
	//判断页面存活
	if(!guider_ui.screen_alarm_ring){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	lv_label_set_text_fmt(guider_ui.screen_alarm_ring_imgbtn_alarm_stop_label, "%s", clock_stop[language]);
	lv_label_set_text_fmt(guider_ui.screen_alarm_ring_imgbtn_alarm_repeat_label, "%s", clock_repeat[language]);
}
void screen_alarm_ring_enter()
{
	screen_list_add(screen_alarm_ring_init, screen_alarm_ring_deinit, screen_alarm_ring_load, screen_alarm_ring_refresh, SCREEN_PRIO_ALARM_RING);
}

static void screen_alarm_ring_imgbtn_alarm_repeat_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		alarm_start(clock_time[clock_time_index] * 60);

		screen_list_del(SCREEN_PRIO_ALARM_RING); // 退出闹钟提醒页面

		break;
	}
	default:
		break;
	}
}
static void screen_alarm_ring_imgbtn_alarm_stop_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		alarm_ring_off();

		lv_cont_alarm_reset();

		screen_list_del(SCREEN_PRIO_ALARM_RING); // 退出闹钟提醒页面

		break;
	}
	default:
		break;
	}
}
void events_init_screen_alarm_ring(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_alarm_ring_imgbtn_alarm_repeat, screen_alarm_ring_imgbtn_alarm_repeat_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_ring_imgbtn_alarm_stop, screen_alarm_ring_imgbtn_alarm_stop_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_alarm_ring_loaded;
