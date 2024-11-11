#include "custom.h"

/*****************************************************tiktok******************************************************/
// 抖音点赞缩放定时器
lv_timer_t *tiktok_timer = NULL;
// 抖音点赞缩放比例
const float tiktok_zoom_tab[TIKTOK_PLAY_NUM] = {1.0, 1.2, 1.6, 1.3, 1.2};
/*****************************************************tiktok******************************************************/

/*************************抢断页面****************************/
static void screen_tiktok_load()
{
	lv_scr_load(guider_ui.screen_tiktok);
}

void screen_tiktok_enter()
{
	screen_list_add(init_screen_tiktok, deinit_screen_tiktok, screen_tiktok_load, screen_tiktok_refresh, SCREEN_PRIO_TIKTOK);
}

void screen_tiktok_exist()
{
	screen_list_del(SCREEN_PRIO_TIKTOK);
}
/*************************抢断页面****************************/

static void screen_tiktok_cont_tiktok_event_handler (lv_event_t *e)
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
			screen_list_del(SCREEN_PRIO_TIKTOK);
            break;
        }
		break;
	}
	default:
		break;
	}
}

/**
 * @brief UI效果：连接耳机后，点击中心的心形点赞按钮，心形点赞按钮变成红色，并逐渐放大后缩小
 * 
 */

/**
 * @brief 抖音控制界面跳转调整界面
 * 
 */
static void lv_tiktok_to_rejust()
{
	lv_status_bar_bottom_hide();
	lv_status_bar_top_hide();
	lv_obj_add_flag(guider_ui.screen_tiktok_cont_tiktok, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_tiktok_cont_rejust, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @brief 调整界面跳转抖音控制界面
 * 
 */
static void lv_rejust_to_tiktok()
{
	lv_status_bar_bottom_show();
	lv_status_bar_top_show();
	lv_obj_add_flag(guider_ui.screen_tiktok_cont_rejust, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_tiktok_cont_tiktok, LV_OBJ_FLAG_HIDDEN);
}

// 点赞缩放定时器回调
static void tiktok_timer_cb()
{
	static u8 enter_num = 0;

	int zoom = (int)(tiktok_zoom_tab[enter_num] * LV_IMG_ZOOM_NONE); // 256为不缩放，在此基础上放大再缩小

	lv_img_set_zoom(guider_ui.screen_tiktok_img_tiktok_like, zoom);

	enter_num++;

	if (enter_num >= TIKTOK_PLAY_NUM) {
		lv_img_set_zoom(guider_ui.screen_tiktok_img_tiktok_like, 256);
		lv_img_set_src(guider_ui.screen_tiktok_img_tiktok_like, "F:/ic_dianzan.bin");
		enter_num = 0;
		lv_timer_del(tiktok_timer);
		tiktok_timer = NULL;
	}
}

static void screen_tiktok_img_tiktok_like_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		// 抖音点赞
		printf("like");
		lv_img_set_src(guider_ui.screen_tiktok_img_tiktok_like, "F:/ic_yidianzan.bin");	
		box_info_send_cb.lv_tiktok_like_cmd_send();
		if (tiktok_timer) {
			lv_timer_del(tiktok_timer);
			tiktok_timer = NULL;
		}
		if (!tiktok_timer) {
			tiktok_timer = lv_timer_create(tiktok_timer_cb, TIKTOK_INTERVAL, NULL);
		}	
		break;
	}
	default:
		break;
	}
}

static void screen_tiktok_imgbtn_tiktok_pre_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		// 抖音上一个
		printf("tiktok pre");
		box_info_send_cb.lv_tiktok_pre_cmd_send();
		break;
	}
	default:
		break;
	}
}

static void screen_tiktok_imgbtn_tiktok_next_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		// 抖音下一个
		printf("tiktok next");
		box_info_send_cb.lv_tiktok_next_cmd_send();
		break;
	}
	default:
		break;
	}
}

static void screen_tiktok_label_tiktok_like_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		// 跳转到调整界面
		lv_tiktok_to_rejust();
		break;
	}
	default:
		break;
	}
}

void events_init_screen_tiktok(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_tiktok_img_tiktok_like, screen_tiktok_img_tiktok_like_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_tiktok_imgbtn_tiktok_pre, screen_tiktok_imgbtn_tiktok_pre_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui-> screen_tiktok_imgbtn_tiktok_next, screen_tiktok_imgbtn_tiktok_next_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui-> screen_tiktok_label_tiktok_like, screen_tiktok_label_tiktok_like_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui-> screen_tiktok_cont_tiktok, screen_tiktok_cont_tiktok_event_handler, LV_EVENT_ALL, NULL);
}

static void screen_tiktok_img_up_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		printf("[tiktok rejust]: up");
		break;
	}
	default:
		break;
	}
}
static void screen_tiktok_img_down_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		printf("[tiktok rejust]: down");
		break;
	}
	default:
		break;
	}
}

static void screen_tiktok_img_right_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		printf("[tiktok rejust]: right");
		break;
	}
	default:
		break;
	}
}

static void screen_tiktok_img_left_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		printf("[tiktok rejust]: left");
		break;
	}
	default:
		break;
	}
}

static void screen_tiktok_img_reset_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		printf("[tiktok rejust]: reset");
		break;
	}
	default:
		break;
	}
}

static void screen_tiktok_cont_rejust_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_GESTURE:
	{
        lv_indev_wait_release(lv_indev_get_act());
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir){
        case LV_DIR_LEFT:
            break;
        case LV_DIR_RIGHT:
			// 右滑返回抖音控制界面
			lv_rejust_to_tiktok();
			b_printf("return to tiktok");
			break;
        }
		break;
	}
	default:
		break;
	}
}

void events_init_screen_tiktok_rejust(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_tiktok_img_up, screen_tiktok_img_up_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_tiktok_img_down, screen_tiktok_img_down_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui-> screen_tiktok_img_right, screen_tiktok_img_right_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui-> screen_tiktok_img_left, screen_tiktok_img_left_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui-> screen_tiktok_img_reset, screen_tiktok_img_reset_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui-> screen_tiktok_cont_rejust, screen_tiktok_cont_rejust_event_handler, LV_EVENT_ALL, NULL);
}


bool screen_tiktok_loaded;
void screen_tiktok_refresh()
{
	//判断页面存活
	if(!screen_tiktok_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	switch (language) {
		case CHINESE:
			lv_label_set_text(guider_ui.screen_tiktok_label_tiktok_like, "点赞");
			break;
		case ENGLISH:
			lv_label_set_text(guider_ui.screen_tiktok_label_tiktok_like, "Like");
			break;
		default:
			break;
	}
	
    //使能状态刷新
	u8 phone_state = box_info_base_cb.lv_phone_state_get();
	u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	if(contorl_enable){
		lv_obj_clear_state(guider_ui.screen_tiktok_img_tiktok_like, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_tiktok_imgbtn_tiktok_pre, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_tiktok_imgbtn_tiktok_next, LV_STATE_DISABLED);
	}else{
		lv_obj_add_state(guider_ui.screen_tiktok_img_tiktok_like, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_tiktok_imgbtn_tiktok_pre, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_tiktok_imgbtn_tiktok_next, LV_STATE_DISABLED);
	}

	// //状态刷新
	// if(contorl_enable){
	// }
}