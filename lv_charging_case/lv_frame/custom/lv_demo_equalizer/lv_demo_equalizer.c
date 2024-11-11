#include "custom.h"

static const char *eq_title[] = {"均衡器", "Equalizer"};
static const char *eq_mode_list[][EQ_MODE_COUNT] = {{"标准", "摇滚", "流行", "经典", "爵士"},{"normal", "rock", "pop", "classic", "jazz"}};

/*************************抢断页面****************************/
static void screen_equalizer_load()
{
	lv_scr_load(guider_ui.screen_equalizer);
}

void screen_equalizer_enter()
{
	screen_list_add(init_screen_equalizer, deinit_screen_equalizer, screen_equalizer_load, screen_equalizer_refresh, SCREEN_PRIO_EQUALIZER);
}

void screen_equalizer_exist()
{
	screen_list_del(SCREEN_PRIO_EQUALIZER);
}
/*************************抢断页面****************************/

static void screen_equalizer_cont_eq_event_handler (lv_event_t *e)
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
			screen_list_del(SCREEN_PRIO_EQUALIZER);
            break;
        }
		break;
	}
	default:
		break;
	}
}

static void screen_equalizer_imgbtn_eq_pre_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		int eq_mode = box_info_base_cb.lv_eq_mode_get();
		int language = box_info_base_cb.lv_language_get();
		eq_mode = eq_mode > EQ_NORMAL ? eq_mode - 1 : EQ_NORMAL;
		box_info_send_cb.lv_eq_mode_cmd_send(eq_mode);
		box_info_base_cb.lv_eq_mode_set(eq_mode);
		lv_label_set_text(guider_ui.screen_equalizer_label_eq_mode, eq_mode_list[0][eq_mode]);
		break;
	}
	default:
		break;
	}
}

static void screen_equalizer_imgbtn_eq_next_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		int eq_mode = box_info_base_cb.lv_eq_mode_get();
		int language = box_info_base_cb.lv_language_get();
		eq_mode = eq_mode < EQ_JAZZ ? eq_mode + 1 : EQ_JAZZ;
		box_info_send_cb.lv_eq_mode_cmd_send(eq_mode);
		box_info_base_cb.lv_eq_mode_set(eq_mode);
		lv_label_set_text(guider_ui.screen_equalizer_label_eq_mode, eq_mode_list[0][eq_mode]);
		break;
	}
	default:
		break;
	}
}


void events_init_screen_equalizer(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_equalizer_imgbtn_eq_pre, screen_equalizer_imgbtn_eq_pre_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_equalizer_imgbtn_eq_next, screen_equalizer_imgbtn_eq_next_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_equalizer_cont_eq, screen_equalizer_cont_eq_event_handler, LV_EVENT_ALL, NULL);
}


bool screen_equalizer_loaded;
void screen_equalizer_refresh()
{
	//判断页面存活
	if(!screen_equalizer_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	u8 eq_mode = box_info_base_cb.lv_eq_mode_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_equalizer_label_eq_title, eq_title[0]);
		lv_label_set_text(guider_ui.screen_equalizer_label_eq_mode, eq_mode_list[0][eq_mode]);

	}
#else
	lv_label_set_text_fmt(guider_ui.screen_equalizer_label_eq_title, "%s", eq_title[language]);
	lv_label_set_text_fmt(guider_ui.screen_equalizer_label_eq_mode, "%s", eq_mode_list[language][eq_mode]);
#endif
	// lv_label_set_text_fmt(guider_ui.screen_equalizer_label_eq_title, "%s", eq_title[language]);
	// lv_label_set_text_fmt(guider_ui.screen_equalizer_label_eq_mode, "%s", eq_mode_list[language][eq_mode]);
	// switch (language) {
	// 	case CHINESE:
	// 		break;
	// 	case ENGLISH:
	// 		break;
	// 	default:
	// 		break;
	// }


    //使能状态刷新
	u8 phone_state = box_info_base_cb.lv_phone_state_get();
	u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	if(contorl_enable){
		lv_obj_clear_state(guider_ui.screen_equalizer_imgbtn_eq_pre, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_equalizer_imgbtn_eq_next, LV_STATE_DISABLED);
	}else{
		lv_obj_add_state(guider_ui.screen_equalizer_imgbtn_eq_pre, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_equalizer_imgbtn_eq_next, LV_STATE_DISABLED);
	}


	// //状态刷新(不响应蓝牙，开机只跑一遍初始化状态)
	// static bool poweron_status_init = true;
	// if(poweron_status_init){
	// 	poweron_status_init = false;
	// }else{
	// 	return;
	// }

	// if(contorl_enable){
	// 	int eq_mode = box_info_base_cb.lv_eq_mode_get();
	// 	// printf("%s %d eq_mode:%d\n", __FUNCTION__, __LINE__, eq_mode);

	// 	lv_label_set_text_fmt(guider_ui.screen_equalizer_label_eq_mode, "%s", eq_mode_list[language][eq_mode]);
	// }

}
