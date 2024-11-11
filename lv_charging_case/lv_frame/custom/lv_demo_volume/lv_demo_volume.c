#include "custom.h"

static const char *vol_title[] = {"音量调节", "Volume Adjusting"};

/*************************抢断页面****************************/
static void screen_volume_load()
{
	lv_scr_load(guider_ui.screen_volume);
}

void screen_volume_enter()
{
	screen_list_add(init_screen_volume, deinit_screen_volume, screen_volume_load, screen_volume_refresh, SCREEN_PRIO_VOLUME);
}

void screen_volume_exist()
{
	screen_list_del(SCREEN_PRIO_VOLUME);
}
/*************************抢断页面****************************/

static void screen_volume_cont_vol_event_handler (lv_event_t *e)
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
			screen_list_del(SCREEN_PRIO_VOLUME);
            break;
        }
		break;
	}
	default:
		break;
	}
}

// 音量减小
static void screen_volume_imgbtn_vol_down_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		// 发送音量减小命令
		box_info_send_cb.lv_volume_down_cmd_send();
		break;
	}
	default:
		break;
	}
}

// 音量增加
static void screen_volume_imgbtn_vol_up_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		// 发送音量增加命令
		box_info_send_cb.lv_volume_up_cmd_send();
		break;
	}
	default:
		break;
	}
}

void events_init_screen_volume(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_volume_imgbtn_vol_down, screen_volume_imgbtn_vol_down_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_volume_imgbtn_vol_up, screen_volume_imgbtn_vol_up_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_volume_cont_vol, screen_volume_cont_vol_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_volume_loaded;
void screen_volume_refresh()
{
	//判断页面存活
	if(!screen_volume_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_volume_label_vol_title, vol_title[0]);
	}
#else
	lv_label_set_text_fmt(guider_ui.screen_volume_label_vol_title, "%s", vol_title[language]);
#endif
	// lv_label_set_text_fmt(guider_ui.screen_volume_label_vol_title, "%s", vol_title[language]);
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
		lv_obj_clear_state(guider_ui.screen_volume_imgbtn_vol_up, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_volume_imgbtn_vol_down, LV_STATE_DISABLED);
	}else{
		lv_obj_add_state(guider_ui.screen_volume_imgbtn_vol_up, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_volume_imgbtn_vol_down, LV_STATE_DISABLED);
	}

	//状态刷新
	if(contorl_enable){
		int earphone_vol = box_info_base_cb.lv_earphone_vol_get();
		// printf("%s %d earphone_vol:%d\n", __FUNCTION__, __LINE__, earphone_vol);
		
		lv_label_set_text_fmt(guider_ui.screen_volume_label_vol, "%d", earphone_vol);
	}
}