#include "custom.h"

static const char *income_title[] = {"来电", "Income"};


static lv_timer_t * call_timer = NULL;
static int call_count = 0;

static void screen_call_init()
{
	printf("%s\n", __FUNCTION__);
	// lv_status_bar_top_hide();
	setup_scr_screen_call(&guider_ui, NULL);
	events_init_screen_call(&guider_ui);

}
static void screen_call_deinit()
{
	printf("%s\n", __FUNCTION__);

	if(guider_ui.screen_call) {
		usr_free_animing(guider_ui.screen_call_animimg_call_bg, (const void **) screen_loop_img_bg_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	}

	lv_obj_del(guider_ui.screen_call);
	// lv_status_bar_top_show();
	guider_ui.screen_call = NULL;
}
static void screen_call_load()
{
	lv_scr_load(guider_ui.screen_call);
}



static void call_timer_cb(lv_timer_t *timer)
{
	call_count++;

	int hour = call_count / 3600;
	int min = (call_count % 3600) / 60;
	int sec = call_count % 60;
	lv_label_set_text_fmt(guider_ui.screen_call_answering_time, "%02d:%02d:%02d", hour, min, sec);
}
static void screen_call_img_incoming_hang_up_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// 来电中，挂断电话
		box_info_send_cb.lv_call_status_cmd_send(CALL_CONTROL_HANG_UP);
		box_info_base_cb.lv_phone_call_state_set(CALL_STATUS_HANGUP);
		break;
	}
	default:
		break;
	}
}
static void screen_call_img_incoming_answer_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// 来电中，接听电话
		box_info_send_cb.lv_call_status_cmd_send(CALL_CONTROL_ANSWER);
		box_info_base_cb.lv_phone_call_state_set(CALL_STATUS_ACTIVE);
		break;
	}
	default:
		break;
	}
}
static void screen_call_img_answering_hang_up_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// 通话中，挂断电话
		box_info_send_cb.lv_call_status_cmd_send(CALL_CONTROL_HANG_UP);
		box_info_base_cb.lv_phone_call_state_set(CALL_STATUS_HANGUP);
		break;
	}
	default:
		break;
	}
}
static void screen_call_img_answering_mute_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		break;
	}
	default:
		break;
	}
}
void events_init_screen_call(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_call_img_incoming_hang_up, screen_call_img_incoming_hang_up_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_call_img_incoming_answer, screen_call_img_incoming_answer_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_call_img_answering_hang_up, screen_call_img_answering_hang_up_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_call_img_answering_mute, screen_call_img_answering_mute_event_handler, LV_EVENT_ALL, NULL);
}



void screen_call_check()
{
	// printf("%s\n", __FUNCTION__);

	u8 phone_call_state = box_info_base_cb.lv_phone_call_state_get();
	if(phone_call_state == CALL_STATUS_INCOME){
		screen_list_add(screen_call_init, screen_call_deinit, screen_call_load, screen_call_refresh, SCREEN_PRIO_CALL);
		return;
	}
}

void screen_call_refresh()
{
	//判断页面存活
	if(!guider_ui.screen_call){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_call_label_incoming_title, income_title[0]);
	}
#else
	lv_label_set_text_fmt(guider_ui.screen_call_label_incoming_title, "%s", income_title[language]);
#endif
    // lv_label_set_text_fmt(guider_ui.screen_call_label_incoming_title, "%s", income_title[language]);
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
	}else{
	}


	// 状态刷新
	if(contorl_enable){

        int phone_state = box_info_base_cb.lv_phone_state_get();
        int phone_call_state = box_info_base_cb.lv_phone_call_state_get();
        // printf("%s %d phone_state:%d\n", __FUNCTION__, __LINE__, phone_state);
        // printf("%s %d phone_call_state:%d\n", __FUNCTION__, __LINE__, phone_call_state);

        //手机断连时，退出通话界面
        if(!phone_state){
            phone_call_state = CALL_STATUS_HANGUP;
            box_info_base_cb.lv_phone_call_state_set(CALL_STATUS_HANGUP);
        }

        //更新通话状态
        switch (phone_call_state) {
		case CALL_STATUS_INCOME:{
			//跳转来电页面
			if(lv_obj_has_flag(guider_ui.screen_call_cont_call_incoming, LV_OBJ_FLAG_HIDDEN))
			{
				lv_auto_sleep_enable(false);

				lv_obj_clear_flag(guider_ui.screen_call_cont_call_incoming, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.screen_call_cont_call_answering, LV_OBJ_FLAG_HIDDEN);
			}
			break;
		}

		case CALL_STATUS_ACTIVE:{
			//切换通话中
			if(lv_obj_has_flag(guider_ui.screen_call_cont_call_answering, LV_OBJ_FLAG_HIDDEN))
			{
				lv_auto_sleep_enable(false);

				//计时初始化
				call_count = 0;
				int hour = call_count / 3600;
				int min = (call_count % 3600) / 60;
				int sec = call_count % 60;
				lv_label_set_text_fmt(guider_ui.screen_call_answering_time, "%02d:%02d:%02d", hour, min, sec);

				//开始通话计时
				call_timer = lv_timer_create(call_timer_cb, 1000, NULL);

				lv_obj_add_flag(guider_ui.screen_call_cont_call_incoming, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.screen_call_cont_call_answering, LV_OBJ_FLAG_HIDDEN);
			}
			break;
		}

		case CALL_STATUS_HANGUP:{
			lv_auto_sleep_enable(true);

			//停止计时
			if(call_timer){
				lv_timer_del(call_timer);
				call_timer = NULL;
			}

			screen_list_del(SCREEN_PRIO_CALL);
			break;
		}
		default:
			break;
        }
	}
}


