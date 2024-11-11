#include "custom.h"

const char *clock_title[] = {"闹钟", "Alarm"};
const char *clock_unit[] = {"分钟", "min"};
const char *clock_setting[] = {"设置", "SET UP"};
const char *clock_cancel[] = {"取消", "CANCEL"};
const char *clock_stop[] = {"停止", "STOP"};
const char *clock_repeat[] = {"重复", "REPEAT"};
const char clock_time[] = {5, 10, 30, 60};


const int clock_time_num = sizeof(clock_time) / sizeof(clock_time[0]);

int clock_time_index = 0; // 闹钟常用设置索引

/*************************抢断页面****************************/
static void screen_alarm_load()
{
	lv_scr_load(guider_ui.screen_alarm);
}

void screen_alarm_enter()
{
	screen_list_add(init_screen_alarm, deinit_screen_alarm, screen_alarm_load, screen_alarm_refresh, SCREEN_PRIO_ALARM);
}

void screen_alarm_exist()
{
	screen_list_del(SCREEN_PRIO_ALARM);
}
/*************************抢断页面****************************/

static void screen_alarm_cont_alarm_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	extern lv_obj_t * cursor_obj;

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		break;
	}
	case LV_EVENT_GESTURE:
	{
        lv_indev_wait_release(lv_indev_get_act());
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir){
        case LV_DIR_LEFT:
			// printf("to left\n");
            break;
        case LV_DIR_RIGHT:
			// 右滑隐藏产测菜单
			printf("func: %s, line: %d, page return", __func__, __LINE__);
			screen_list_del(SCREEN_PRIO_ALARM);
            break;
        }
		break;
	}
	default:
		break;
	}
}


static void screen_alarm_imgbtn_alarm_time_down_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		int language = box_info_base_cb.lv_language_get();
		clock_time_index = clock_time_index > 0 ? clock_time_index - 1 : 0;
		lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_time[clock_time_index], clock_unit[language]);
		break;
	}
	default:
		break;
	}
}
static void screen_alarm_imgbtn_alarm_time_up_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		int language = box_info_base_cb.lv_language_get();
		clock_time_index = clock_time_index < clock_time_num - 1 ? clock_time_index + 1 : clock_time_num - 1;
		lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_time[clock_time_index], clock_unit[language]);
		break;
	}
	default:
		break;
	}
}
static void screen_alarm_imgbtn_alarm_setting_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		alarm_start(clock_time[clock_time_index] * 60);

	  	break;
	}
	default:
		break;
	}
}
static void screen_alarm_imgbtn_alarm_cancel_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		alarm_cancel();

		break;
	}
	default:
		break;
	}
}

void events_init_screen_alarm(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_alarm_imgbtn_alarm_time_down, screen_alarm_imgbtn_alarm_time_down_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_imgbtn_alarm_time_up, screen_alarm_imgbtn_alarm_time_up_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_imgbtn_alarm_setting, screen_alarm_imgbtn_alarm_setting_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_imgbtn_alarm_cancel, screen_alarm_imgbtn_alarm_cancel_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_cont_alarm, screen_alarm_cont_alarm_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_alarm_cont_alarm_count, screen_alarm_cont_alarm_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_alarm_loaded;

// 恢复闹钟设置界面
void lv_cont_alarm_reset()
{
	//判断页面存活
	if(!screen_alarm_loaded){return;}
	lv_obj_clear_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
}

void screen_alarm_refresh()
{
	//判断页面存活
	if(!screen_alarm_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_alarm_label_alarm_title, clock_title[0]);
		lv_label_set_text(guider_ui.screen_alarm_label_alarm_count_title, clock_title[0]);
		lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d分钟", clock_time[clock_time_index]);
		lv_label_set_text(guider_ui.screen_alarm_imgbtn_alarm_setting_label, clock_setting[0]);
		lv_label_set_text(guider_ui.screen_alarm_imgbtn_alarm_cancel_label, clock_cancel[0]);
	} else {
		printf("set language err");
	}

#else
	
	lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_title, "%s", clock_title[language]);
	lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_count_title, "%s", clock_title[language]);
	lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_time, "%d%s", clock_time[clock_time_index], clock_unit[language]);
	lv_label_set_text_fmt(guider_ui.screen_alarm_imgbtn_alarm_setting_label, "%s", clock_setting[language]);
	lv_label_set_text_fmt(guider_ui.screen_alarm_imgbtn_alarm_cancel_label, "%s", clock_cancel[language]);
#endif
	
    //使能状态刷新
	u8 phone_state = box_info_base_cb.lv_phone_state_get();
	u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	contorl_enable = true; // 闹钟测试
	if(contorl_enable){
		lv_obj_clear_state(guider_ui.screen_alarm_imgbtn_alarm_time_down, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_alarm_imgbtn_alarm_time_up, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_alarm_imgbtn_alarm_setting, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_alarm_imgbtn_alarm_cancel, LV_STATE_DISABLED);
	}else{
		lv_obj_add_state(guider_ui.screen_alarm_imgbtn_alarm_time_down, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_alarm_imgbtn_alarm_time_up, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_alarm_imgbtn_alarm_setting, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_alarm_imgbtn_alarm_cancel, LV_STATE_DISABLED);
	}

	//状态刷新
	if(contorl_enable){

		u8 alarm_state = alarm_status_get();

		switch (alarm_state){
		case ALARM_ON:

			alarm_refresh();

			lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
			break;
		case ALARM_RING:
			// lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
			// lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
			break;
		case ALARM_OFF:
			lv_obj_clear_flag(guider_ui.screen_alarm_cont_alarm, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_alarm_cont_alarm_count, LV_OBJ_FLAG_HIDDEN);
			break;
		default:
			break;
		}
	}
}