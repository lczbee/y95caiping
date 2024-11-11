#include "custom.h"

static const char *squelch_title[] = {"静噪", "Squelch"};
static const char *squelching_title[] = {"静噪中", "Squelching"};

static void screen_squelch_imgbtn_sq_start_event_handler (lv_event_t *e)
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
static void screen_squelch_imgbtn_sq_ing_cancel_event_handler (lv_event_t *e)
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

void events_init_screen_squelch(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_squelch_imgbtn_sq_start, screen_squelch_imgbtn_sq_start_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_squelch_imgbtn_sq_ing_cancel, screen_squelch_imgbtn_sq_ing_cancel_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_squelch_loaded;
void screen_squelch_refresh()
{
	//判断页面存活
	if(!screen_squelch_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	lv_label_set_text(guider_ui.screen_squelch_label_sq_title,  squelch_title[0]);
    lv_label_set_text(guider_ui.screen_squelch_label_sq_ing_title, squelching_title[0]);
#else
	lv_label_set_text_fmt(guider_ui.screen_squelch_label_sq_title, "%s", squelch_title[language]);
    lv_label_set_text_fmt(guider_ui.screen_squelch_label_sq_ing_title, "%s", squelching_title[language]);
#endif
	switch (language) {
		case CHINESE:
            lv_label_set_text_fmt(guider_ui.screen_squelch_label_sq_time, "%d%s", 30, "分钟");
            lv_label_set_text_fmt(guider_ui.screen_squelch_label_sleep_time, "%d%s", 30, "分钟");
            // lv_img_set_src(guider_ui.screen_squelch_imgbtn_sq_start, "F:/ic_kaishi.bin");
            // lv_img_set_src(guider_ui.screen_squelch_imgbtn_sq_ing_cancel, "F:/ic_quxiao.bin");
			break;
		case ENGLISH:
            lv_img_set_src(guider_ui.screen_squelch_imgbtn_sq_start, "F:/ic_kaishi_eng.bin");
            lv_img_set_src(guider_ui.screen_squelch_imgbtn_sq_ing_cancel, "F:/ic_quxiao.bin");
            // lv_label_set_text_fmt(guider_ui.screen_squelch_label_sq_time, "%d%s", 30, "min");
            // lv_label_set_text_fmt(guider_ui.screen_squelch_label_sleep_time, "%d%s", 30, "min");
			break;
		default:
			break;
	}

    //使能状态刷新
	u8 phone_state = box_info_base_cb.lv_phone_state_get();
	u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	if(contorl_enable){
        lv_obj_clear_state(guider_ui.screen_squelch_imgbtn_sq_start, LV_STATE_DISABLED);
	}else{
        lv_obj_add_state(guider_ui.screen_squelch_imgbtn_sq_start, LV_STATE_DISABLED);
	}

	// //状态刷新
	// if(contorl_enable){
	// }
}