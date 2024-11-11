#include "custom.h"


static void screen_charging_init()
{
	printf("%s\n", __FUNCTION__);

	// lv_status_bar_top_hide();
	setup_scr_screen_charging(&guider_ui, NULL);
    events_init_screen_charging(&guider_ui);
}

static void screen_charging_deinit()
{
	printf("%s\n", __FUNCTION__);

	if(guider_ui.screen_charging) {
		usr_free_animing(guider_ui.screen_charging_animimg_charging, (const void **) screen_charging_animimg_charging_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	}
	// lv_status_bar_top_show();
	lv_obj_del(guider_ui.screen_charging);
	guider_ui.screen_charging = NULL;
}
static void screen_charging_load()
{
    lv_scr_load(guider_ui.screen_charging);
}



static void screen_charging_cont_charging_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
        screen_list_del(SCREEN_PRIO_CHARGE);
	}
	default:
		break;
	}
}


void events_init_screen_charging(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_charging_cont_charging, screen_charging_cont_charging_event_handler, LV_EVENT_ALL, NULL);
}



void screen_charging_check()
{
	// printf("%s\n", __FUNCTION__);

    static bool charging_reset = true;
    int box_charging = box_info_base_cb.lv_box_charging_get();

	if(box_charging){
		if(charging_reset){
			charging_reset = false;
            screen_list_add(screen_charging_init, screen_charging_deinit, screen_charging_load, screen_charging_refresh, SCREEN_PRIO_CHARGE);
        }
    }else{
		if(!charging_reset){
			screen_list_del(SCREEN_PRIO_CHARGE);
		}
        charging_reset = true;

		pc_mode_on = false; // 拔出充电时标记为pc模式关闭
    }

}


void screen_charging_refresh()
{
	//判断页面存活
	if(!guider_ui.screen_charging){return;}
	// printf("%s\n", __FUNCTION__);

	// 状态刷新
    int box_bat = box_info_base_cb.lv_box_bat_get();
    
	extern int now_soc_trim_info;
	if(box_bat == 255){
		lv_label_set_text_fmt(guider_ui.screen_charging_label_charging, "--%%");
	} else {
		lv_label_set_text_fmt(guider_ui.screen_charging_label_charging, "%d%c", box_bat, '%');
	}
}




