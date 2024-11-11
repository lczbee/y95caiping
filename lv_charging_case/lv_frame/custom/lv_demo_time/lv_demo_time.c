#include "custom.h"


bool screen_time_loaded;
bool screen_time_cont_set_loaded;

static const char *time_setting[] = {"设置", "setting"};

static const char *return_tetx[] = {"返回","Return",};
static const char *save_text[] = {"保存","Save",};

/*************************抢断页面****************************/
static void screen_time_load()
{
	lv_scr_load(guider_ui.screen_time);
}

void screen_time_enter()
{
	screen_list_add(init_screen_time, deinit_screen_time, screen_time_load, screen_time_refresh, SCREEN_PRIO_TIME);
}

void screen_time_exist()
{
	screen_list_del(SCREEN_PRIO_TIME);
}
/*************************抢断页面****************************/

static void screen_time_cont_time_event_handler (lv_event_t *e)
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
			screen_list_del(SCREEN_PRIO_TIME);
            break;
        }
		break;
	}
	default:
		break;
	}
}

// 保存时分秒设置
static void screen_time_label_HMS_save_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.screen_time_cont_time, LV_OBJ_FLAG_HIDDEN); // 显示HMS页面
		lv_obj_add_flag(guider_ui.screen_time_cont_set_HMS, LV_OBJ_FLAG_HIDDEN); // 隐藏YMD页面

		struct sys_time time = {0};
		sbox_get_sys_time(&time);
		char buf[5];
		
		lv_roller_get_selected_str(guider_ui.screen_time_roller_hour, buf, sizeof(buf));
		time.hour = a2i(buf);
		lv_roller_get_selected_str(guider_ui.screen_time_roller_min, buf, sizeof(buf));
		time.min = a2i(buf);
		lv_roller_get_selected_str(guider_ui.screen_time_roller_sec, buf, sizeof(buf));
		time.sec = a2i(buf);

		printf("H:M:S = {%d:%d:%d}", time.hour, time.min, time.sec);
		sbox_set_sys_time(&time);
		// lv_label_set_text_fmt(guider_ui.screen_time_label_time, "%02d:%02d", time.hour, time.min);
		lv_label_set_text_fmt(guider_ui.screen_time_label_HMS, "%02d:%02d:%02d", time.hour, time.min, time.sec);
		lv_label_set_text_fmt(guider_ui.screen_time_label_YMD, "%04d/%02d/%02d", time.year, time.month, time.day);

		break;
	}
	default:
		break;
	}
}

// 点击时分秒界面返回按钮
static void screen_time_label_HMS_return_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_time_cont_set_HMS, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_time_cont_set_YMD, LV_OBJ_FLAG_HIDDEN); // 恢复YMD页面
		break;
	}
	default:
		break;
	}
}

// 时分秒界面右滑返回
static void screen_time_cont_set_HMS_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

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
			// 右滑隐藏HMS设置页面
			printf("cont_set_HMS to right\n");
			lv_obj_add_flag(guider_ui.screen_time_cont_set_HMS, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_time_cont_set_YMD, LV_OBJ_FLAG_HIDDEN); // 恢复YMD设置页面
            break;
        }
		break;
	}
	default:
		break;
	}
}

// 年月日界面保存设置
static void screen_time_label_YMD_save_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// lv_obj_clear_flag(guider_ui.screen_time_tileview_loop, LV_OBJ_FLAG_SCROLLABLE); // 取消滚动
		lv_obj_clear_flag(guider_ui.screen_time_cont_set_HMS, LV_OBJ_FLAG_HIDDEN); // 显示HMS页面
		lv_obj_add_flag(guider_ui.screen_time_cont_set_YMD, LV_OBJ_FLAG_HIDDEN); // 隐藏YMD页面

		struct sys_time time = {0};
		sbox_get_sys_time(&time);
		char buf[5];
		
		lv_roller_get_selected_str(guider_ui.screen_time_roller_year, buf, sizeof(buf));
		printf("%s", buf);
		time.year = a2i(buf);
		lv_roller_get_selected_str(guider_ui.screen_time_roller_month, buf, sizeof(buf));
		time.month = a2i(buf);
		lv_roller_get_selected_str(guider_ui.screen_time_roller_day, buf, sizeof(buf));
		time.day = a2i(buf);

		printf("Y:M:D = {%d:%d:%d}", time.year, time.month, time.day);
		sbox_set_sys_time(&time);
		lv_label_set_text_fmt(guider_ui.screen_time_label_YMD, "%04d/%02d/%02d", time.year, time.month, time.day);

		break;
	}
	default:
		break;
	}
}

// 点击年月日界面返回按钮
static void screen_time_label_YMD_return_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_time_cont_set_YMD, LV_OBJ_FLAG_HIDDEN); // 隐藏YMD页面
		lv_obj_clear_flag(guider_ui.screen_time_cont_time, LV_OBJ_FLAG_HIDDEN); // 恢复时间设置页面
		// lv_obj_clear_flag(guider_ui.screen_time_slider_buttom, LV_OBJ_FLAG_HIDDEN); // 隐藏底部进度点
		break;
	}
	default:
		break;
	}
}

// 滚动月列表
static void screen_time_roller_month_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		char buf[5];
		lv_roller_get_selected_str(guider_ui.screen_time_roller_year, buf, sizeof(buf));
		int year = a2i(buf);
		lv_roller_get_selected_str(guider_ui.screen_time_roller_month, buf, sizeof(buf));
		int month = a2i(buf);
		lv_roller_get_selected_str(guider_ui.screen_time_roller_day, buf, sizeof(buf));
		int day = a2i(buf);
		printf("day: %d", day);


		u8 day_max = get_day_max(year, month);
		printf("year: %d, month: %d day_max: %d", year, month, day_max);

		switch (day_max)
		{
		case 31:
			lv_roller_set_options(guider_ui.screen_time_roller_day, roller_day_31, LV_ROLLER_MODE_INFINITE);
			break;
		case 30:
			lv_roller_set_options(guider_ui.screen_time_roller_day, roller_day_30, LV_ROLLER_MODE_INFINITE);
			break;
		case 29:
			lv_roller_set_options(guider_ui.screen_time_roller_day, roller_day_29, LV_ROLLER_MODE_INFINITE);
			break;
		case 28:
			lv_roller_set_options(guider_ui.screen_time_roller_day, roller_day_28, LV_ROLLER_MODE_INFINITE);
			break;
		
		default:
			printf("[error] please check get_day_max func: %s, line: %d", __func__, __LINE__);
			break;
		}

		// 限制最大天数
		if (day > day_max) {
			day = day_max;
		}

		lv_roller_set_selected(guider_ui.screen_time_roller_day, day - 1, LV_ANIM_OFF); // 日期转id需要 -1

		break;
	}
	default:
		break;
	}
}

// 从年月日界面右滑返回
static void screen_time_cont_set_YMD_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

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
			// 右滑隐藏YMD设置页面
			printf("cont_set_YMD to right\n");
			// lv_obj_add_flag(guider_ui.screen_time_tileview_loop, LV_OBJ_FLAG_SCROLLABLE); // 恢复滚动
			lv_obj_add_flag(guider_ui.screen_time_cont_set_YMD, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_time_cont_time, LV_OBJ_FLAG_HIDDEN); // 恢复时间设置页面
			// lv_obj_clear_flag(guider_ui.screen_time_slider_buttom, LV_OBJ_FLAG_HIDDEN); // 隐藏底部进度点
            break;
        }
		break;
	}
	default:
		break;
	}
}

// 点击时间设置
static void screen_time_label_time_set_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		if(!screen_time_cont_set_loaded){
			setup_scr_screen_time_cont_set(&guider_ui, NULL);
			events_init_screen_time_cont_set(&guider_ui);
			screen_time_cont_set_loaded = true;
		}

		if(screen_time_cont_set_loaded){
			// lv_obj_clear_flag(guider_ui.screen_time_tileview_loop, LV_OBJ_FLAG_SCROLLABLE); // 取消滚动
			lv_obj_clear_flag(guider_ui.screen_time_cont_set_YMD, LV_OBJ_FLAG_HIDDEN); // 显示YMD页面
			lv_obj_add_flag(guider_ui.screen_time_cont_time, LV_OBJ_FLAG_HIDDEN); // 隐藏时间设置页面
			// lv_obj_add_flag(guider_ui.screen_time_slider_buttom, LV_OBJ_FLAG_HIDDEN); // 隐藏底部进度点
		}
		break;
	}
	default:
		break;
	}
}

void events_init_screen_time(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_time_label_time_set, screen_time_label_time_set_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_time_cont_time, screen_time_cont_time_event_handler, LV_EVENT_ALL, NULL);
}

void events_init_screen_time_cont_set(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_time_label_HMS_save, screen_time_label_HMS_save_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_time_label_HMS_return, screen_time_label_HMS_return_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_time_cont_set_HMS, screen_time_cont_set_HMS_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_time_label_YMD_save, screen_time_label_YMD_save_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_time_label_YMD_return, screen_time_label_YMD_return_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_time_cont_set_YMD, screen_time_cont_set_YMD_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_time_roller_month, screen_time_roller_month_event_handler, LV_EVENT_ALL, NULL);
}

void screen_time_refresh()
{
	//判断页面存活
	if(!screen_time_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_time_label_time_set, time_setting[0]);
	}
#else
	lv_label_set_text(guider_ui.screen_time_label_time_set, time_setting[language]);
#endif
	// lv_label_set_text(guider_ui.screen_time_label_time_set, time_setting[language]);
	if(screen_time_cont_set_loaded){
		lv_label_set_text(guider_ui.screen_time_label_YMD_return, return_tetx[0]);
		lv_label_set_text(guider_ui.screen_time_label_YMD_save, save_text[0]);
		lv_label_set_text(guider_ui.screen_time_label_HMS_return, return_tetx[0]);
		lv_label_set_text(guider_ui.screen_time_label_HMS_save, save_text[0]);
	}
	// switch (language) {
	// 	case CHINESE:
	// 		break;
	// 	case ENGLISH:
	// 		break;
	// 	default:
	// 		break;
	// }
	
    // //使能状态刷新
	// u8 phone_state = box_info_base_cb.lv_phone_state_get();
	// u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	// u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	// if(contorl_enable){
	// }else{
	// }

	// //状态刷新
	// if(contorl_enable){
	// }
	
	
	struct sys_time time = {0};

	sbox_get_sys_time(&time);
	lv_label_set_text_fmt(guider_ui.screen_time_label_HMS, "%02d:%02d:%02d", time.hour, time.min, time.sec);
	lv_label_set_text_fmt(guider_ui.screen_time_label_YMD, "%04d/%02d/%02d", time.year, time.month, time.day);


	
}