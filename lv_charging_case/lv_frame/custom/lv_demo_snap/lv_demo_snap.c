#include "custom.h"

/***************************************************take photo****************************************************/
// 拍照旋转定时器
lv_timer_t *snap_timer = NULL;
/***************************************************take photo****************************************************/

/*************************抢断页面****************************/
static void screen_snap_load()
{
	lv_scr_load(guider_ui.screen_snap);
}

void screen_snap_enter()
{
	screen_list_add(init_screen_snap, deinit_screen_snap, screen_snap_load, screen_snap_refresh, SCREEN_PRIO_SNAP);
}

void screen_snap_exist()
{
	screen_list_del(SCREEN_PRIO_SNAP);
}
/*************************抢断页面****************************/

static void screen_snap_cont_snap_event_handler (lv_event_t *e)
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
			screen_list_del(SCREEN_PRIO_SNAP);
            break;
        }
		break;
	}
	default:
		break;
	}
}

/**
 * @brief  UI效果：连接耳机后点击拍照，照相机图片会安装预设的ANG1和ANG2摇晃
 * 
 */

static void snap_timer_cb()
{
	static u8 enter_num = 0;
	if (enter_num % 2 == 0) {
		lv_img_set_angle(guider_ui.screen_snap_img_snap, TAKEPHOTO_ANG_1);
	} else {
		lv_img_set_angle(guider_ui.screen_snap_img_snap, TAKEPHOTO_ANG_2);
	}

	enter_num++;

	if (enter_num >= TAKEPHOTO_PLAY_NUM) {
		lv_img_set_angle(guider_ui.screen_snap_img_snap, 0);
		enter_num = 0;
		lv_timer_del(snap_timer);
		snap_timer = NULL;
	}
}
static void screen_snap_img_snap_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		if (snap_timer) {
			lv_timer_del(snap_timer);
			snap_timer = NULL;
		}
		if (!snap_timer) {
			snap_timer = lv_timer_create(snap_timer_cb, TAKEPHOTO_INTERVAL, NULL);
		}
		// 拍照
		box_info_send_cb.lv_snap_cmd_send();

		break;
	}
	default:
		break;
	}
}

void events_init_screen_snap(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_snap_img_snap, screen_snap_img_snap_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_snap_cont_snap, screen_snap_cont_snap_event_handler, LV_EVENT_ALL, NULL);
}

bool screen_snap_loaded;
void screen_snap_refresh()
{
	//判断页面存活
	if(!screen_snap_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	// //语言更新
	// u8 language = box_info_base_cb.lv_language_get();
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
		lv_obj_clear_state(guider_ui.screen_snap_img_snap, LV_STATE_DISABLED);
	}else{
		lv_obj_add_state(guider_ui.screen_snap_img_snap, LV_STATE_DISABLED);
	}

	// //状态刷新
	// if(contorl_enable){
	// }
}