#include "custom.h"

static const char *lock_title[] = {"锁屏壁纸", "Screen Lock"};

/*************************************************动画相关*********************************************************/
// 锁屏壁纸（小）
 char *lock_small_mytab[] = {"F:/test1.bin", "F:/test2.bin", "F:/test3.bin", "F:/test4.bin", "F:/test5.bin"};

// 锁屏壁纸（大）
 char *lock_big_tab[] = {"d:storage/virfat_flash/C/MYLOCK.RES", "L2B", "L3B", "L4B", "L5B"};

// 当前锁屏索引
int cur_lock_index = 0;
/*************************************************动画相关*********************************************************/

/**********************************************产测模式说明********************************************************/
/**
 * 在锁屏壁纸界面，快速点5下切下一个壁纸的按钮，每次间隔在300ms以内
 * 点击5次以上后，在2s内长按壁纸缩略图400ms会进入产测菜单界面，其中：
 * @ 屏幕测试：进入后，点击屏幕会进行颜色切换，右滑退出
 * @ tp测试：进入后，会出现鼠标，以及九宫格，点击九宫格会有反应，鼠标跟随触摸移动，右滑单号
 * @ 连接测试：点击后主动发起耳机连接
 * @ PC按钮：点击后进入PC模式
 * @ 复位：点击后直接复位
 * @ 仓储模式：点击后关机，关闭rtc，进入极低功耗模式
*/
/**********************************************产测模式说明********************************************************/

/*************************抢断页面****************************/
static void screen_wallpaper_load()
{
	lv_scr_load(guider_ui.screen_wallpaper);
}

void screen_wallpaper_enter()
{
	screen_list_add(init_screen_wallpaper, deinit_screen_wallpaper, screen_wallpaper_load, screen_wallpaper_refresh, SCREEN_PRIO_WALLPAPER);
}

void screen_wallpaper_exist()
{
	screen_list_del(SCREEN_PRIO_WALLPAPER);
}
/*************************抢断页面****************************/

static void screen_wallpaper_cont_wp_event_handler (lv_event_t *e)
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
			screen_list_del(SCREEN_PRIO_WALLPAPER);
            break;
        }
		break;
	}
	default:
		break;
	}
}

static int last_click_tick = 0;
static int click_cnt = 0;

static void screen_wallpaper_imgbtn_wp_next_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

#if LOCK_LOOP_ENABLE
		cur_lock_index = cur_lock_index < LOCK_NUM - 1 ? cur_lock_index + 1 : 0;
#else
		cur_lock_index = cur_lock_index < LOCK_NUM - 1 ? cur_lock_index + 1 : LOCK_NUM - 1;
#endif
		printf("cur_wallpaper_index cur_wallpaper_index cur_wallpaper_index: %d ", cur_lock_index);
		printf("1111111111111111111111111 %s", lock_small_mytab[cur_lock_index]);
		lv_img_set_src(guider_ui.screen_wallpaper_jt, lock_small_mytab[cur_lock_index]);
		
		// 产测连点逻辑
		int duration_time = lv_tick_elaps(last_click_tick);
		if(duration_time < 300) {
			click_cnt++;
		} else {
			click_cnt = 0;
		}
		last_click_tick = lv_tick_get();
		printf("<<<last_click_tick click_cnt: %d>>>", click_cnt);

		break;
	}
	case LV_EVENT_LONG_PRESSED:
	{
		printf("<<<Product test pressed: %d>>>", click_cnt);
		if(click_cnt > 4){
			printf("<<<<<<<<<<lv_tick_elaps(last_click_tick)= %d >>>>>",lv_tick_elaps(last_click_tick));
			if(lv_tick_elaps(last_click_tick) < 3000) {
				screen_product_test_enter();
			}
		}
		click_cnt = 0;
		break;
	}
	// case LV_EVENT_LONG_PRESSED:
	// {
	// 	//避免页面滑动误触
	// 	if(screen_scrolled){screen_scrolled = false;return;};
	// 	screen_product_test_enter();
	// 	break;
	// }
	default:
		break;
	}
}
static void screen_wallpaper_imgbtn_wp_pre_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

#if LOCK_LOOP_ENABLE
		cur_lock_index = cur_lock_index > 0 ? cur_lock_index - 1 : LOCK_NUM - 1;
#else
		cur_lock_index = cur_lock_index > 0 ? cur_lock_index - 1 : 0;
#endif
		printf("lock pre >>> lock_index: %d ", cur_lock_index);
		lv_img_set_src(guider_ui.screen_wallpaper_jt, lock_small_mytab[cur_lock_index]);

		break;
	}
	default:
		break;
	}
}
static void screen_wallpaper_jt_tp_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {

	case LV_EVENT_LONG_PRESSED:
	{
		printf("<<<Product test pressed: %d>>>", click_cnt);
		if(click_cnt > 4){
			if(lv_tick_elaps(last_click_tick) < 2000) {
				// 满足连点条件后2s内长按进入产测模式菜单
				// lv_obj_clear_flag(guider_ui.screen_wallpaper_cont_product_test, LV_OBJ_FLAG_HIDDEN);
				screen_product_test_enter();
			}
		}
		click_cnt = 0;
		break;
	}
	case LV_EVENT_RELEASED:
	{
		printf("<<<Product test released>>>");
		click_cnt = 0;
	}
	default:
		break;
	}
}

void events_init_screen_wallpaper(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_wallpaper_imgbtn_wp_next, screen_wallpaper_imgbtn_wp_next_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->screen_wallpaper_imgbtn_wp_pre, screen_wallpaper_imgbtn_wp_pre_event_handler, LV_EVENT_ALL, NULL);
    //lv_obj_add_event_cb(ui->screen_wallpaper_jt_tp, screen_wallpaper_jt_tp_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_wallpaper_cont_wp, screen_wallpaper_cont_wp_event_handler, LV_EVENT_ALL, NULL);
}

/*
void animimg_update_screen_wallpaper()
{
	if(lv_obj_is_valid(guider_ui.screen_wallpaper_animimg_wp)) {
		// usr_free_animing(guider_ui.screen_wallpaper_cont_anim_wp, (const void **) screen_wallpaper_animimg_wp_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
        // usr_update_animing(guider_ui.screen_wallpaper_animimg_wp, lock_small_tab[cur_lock_index]);
        lv_animimg_start(guider_ui.screen_wallpaper_animimg_wp);
    } else {
        b_printf("screen_wallpaper_animimg_wp is invalid");
    }
}
*/


bool screen_wallpaper_loaded;
void screen_wallpaper_refresh()
{
	//判断页面存活
	if(!screen_wallpaper_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_wallpaper_label_wp_title, lock_title[0]);
	}
#else
	lv_label_set_text(guider_ui.screen_wallpaper_label_wp_title, lock_title[language]);
#endif
	// lv_label_set_text(guider_ui.screen_wallpaper_label_wp_title, lock_title[0]);
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
}


