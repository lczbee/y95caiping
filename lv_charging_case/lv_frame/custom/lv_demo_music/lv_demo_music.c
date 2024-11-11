#include "custom.h"
#include "usb/usb_phy.h"

/*****************************************************play********************************************************/
// 音乐模式
static const char *music_mode[][MUSIC_TYPE_COUNT] = {{"手机音乐", "SD音乐"},{"Phone Music", "SD Music"}};

// 切换音乐模式时的提示语
static const char *music_mode_tips[][MUSIC_TYPE_COUNT] = {{"即将切换到SD音乐，\n是否确定断开手机蓝牙？", 
														   "即将切换到手机音乐，\n是否确定连接手机蓝牙？"},
														   {"About to switch to SD music, \nare you sure to disconnect \nyour phone's Bluetooth?",
														    "About to switch to phone's music, \nare you sure to connect \nyour phone's Bluetooth?"}
														 };

static const char *music_mode_timeout[] = {"搜索超时，\n是否确定重试？", "Search timeout, \nare you sure to retry?"};

static const char *music_mode_cancel[] = {"取消", "cancel"};

static const char *music_mode_confirm[] = {"确定", "confirm"};

// static const char *music_mode_retry[] = {"重试", "retry"};

static u8 cur_music_mode = 0;

bool screen_music_loaded;
/*****************************************************play********************************************************/

/*************************抢断页面****************************/
static void screen_music_load()
{
	lv_scr_load(guider_ui.screen_music);
}

void screen_music_enter()
{
	screen_list_add(init_screen_music, deinit_screen_music, screen_music_load, screen_music_refresh, SCREEN_PRIO_MUSIC);
}

void screen_music_exist()
{
	screen_list_del(SCREEN_PRIO_MUSIC);
}
/*************************抢断页面****************************/


/*************************************************本地音乐相关*****************************************************/
// #if LOCAL_MUSIC_ENABLE

/***********************************本地播放文件路径接口*******************************************/
// sd卡根目录
#define ROOT_PATH "storage/sd0/C/"
struct dir_info music_dir_info = {
	.deepth = 0,
	.cur_path = ROOT_PATH,
	.sub_path = {0},
};

// 重置音乐文件当前路径为根目录
void music_cur_path_reset()
{
	memset(music_dir_info.cur_path, 0, sizeof(music_dir_info.cur_path));
	memcpy(music_dir_info.cur_path, ROOT_PATH, strlen(ROOT_PATH));
}

// 重置子目录为空
void music_sub_path_reset()
{
	memset(music_dir_info.sub_path, 0, sizeof(music_dir_info.sub_path));
}

// 路径信息重置
void music_dir_info_reset()
{
	music_dir_info.deepth = 0;
	music_cur_path_reset();
	music_sub_path_reset();

	printf("cur p: %s, sub p: %s", music_dir_info.cur_path, music_dir_info.sub_path);
}

// 更新子目录
void music_sub_path_update(char *sub_path)
{
	if (sub_path == NULL) {
		printf("subpath is null");
		return;
	}

	if (strlen(sub_path) > MAX_MUSIC_NAME_LEN)
	{
		printf("len err");
		return;
	}
	memset(music_dir_info.sub_path, 0, sizeof(music_dir_info.sub_path));
	memcpy(music_dir_info.sub_path, sub_path, strlen(sub_path));
}

// 更新当前目录
void music_cur_path_update(char *cur_path)
{
	if (cur_path == NULL) {
		printf("curpath is null");
		return;
	}

	if (strlen(cur_path) > MAX_MUSIC_NAME_LEN)
	{
		printf("len err");
		return;
	}
	memset(music_dir_info.cur_path, 0, sizeof(music_dir_info.cur_path));
	memcpy(music_dir_info.cur_path, cur_path, strlen(cur_path));
}

// 更新当前目录
void music_path_update(char *cur_path, char *sub_path)
{
	music_cur_path_update(cur_path);
	music_sub_path_update(sub_path);
}

// 打印目录信息
void debug_show_path_info()
{
	printf("cur_path: %s", music_dir_info.cur_path);
	printf("sub_path: %s", music_dir_info.sub_path);
}

// 音乐路径进入
void music_dir_enter(const char *sub_path)
{
	path_merge(music_dir_info.cur_path, sub_path);
	music_sub_path_update(sub_path);
}

// 音乐路径退出
void music_dir_exit()
{
	// path_split(music_dir_info.cur_path, music_dir_info.sub_path);
	path_exit(music_dir_info.cur_path);
	music_sub_path_reset();
}
/***********************************本地播放文件路径接口*******************************************/


/***********************************本地播放音乐拨到接口*******************************************/
extern void local_play_music_pp(void);
extern void local_play_music_next(void);
extern void local_play_music_prev(void);
extern void local_play_conn_earphone(void);
extern void local_play_conn_earphone_by_addr(void);
extern void local_play_conn_earphone_by_name(void);
extern void local_play_close_bt(void);
extern void local_play_post_app_core_event(u8 cmd);
extern u8 get_usb_online_status(void);
/***********************************本地播放音乐拨到接口*******************************************/


/************************************音乐模式控制接口*********************************************/
// 设置音乐模式为手机音乐
void lv_music_mode_set_phone_music()
{
	u8 language = box_info_base_cb.lv_language_get();

	cur_music_mode = PHONE_MUSIC;

	if(!guider_ui.screen_music) return;

	lv_img_set_src(guider_ui.screen_music_img_music_logo, "F:/phone_image.bin"); // 切换手机音乐logo
	lv_label_set_text(guider_ui.screen_music_label_music_title, music_mode[0][cur_music_mode]); // 切换标题
	// lv_label_set_text_fmt(guider_ui.screen_music_label_music_title, "%s", music_mode[language][cur_music_mode]); // 切换标题
	lv_obj_add_flag(guider_ui.screen_music_img_music_sd_list, LV_OBJ_FLAG_HIDDEN); // 隐藏音乐列表

#if BT_LYRICS_ENABLE
	lv_obj_clear_flag(guider_ui.screen_music_img_music_lyric, LV_OBJ_FLAG_HIDDEN); // 隐藏音乐歌词列表
#endif
}

// 设置音乐模式为sd音乐
void lv_music_mode_set_sd_music()
{
	u8 language = box_info_base_cb.lv_language_get();

	cur_music_mode = SD_MUSIC;

	if(!guider_ui.screen_music) return;
	
	lv_img_set_src(guider_ui.screen_music_img_music_logo, "F:/sd_image.bin"); // 切换SD音乐logo
	// lv_label_set_text_fmt(guider_ui.screen_music_label_music_title, "%s", music_mode[language][cur_music_mode]); // 切换标题
	lv_label_set_text(guider_ui.screen_music_label_music_title, music_mode[0][cur_music_mode]); // 切换标题
	lv_obj_clear_flag(guider_ui.screen_music_img_music_sd_list, LV_OBJ_FLAG_HIDDEN); // 显示音乐列表

#if (!BT_LYRICS_ENABLE && !TCFG_LRC_LYRICS_ENABLE)
	lv_obj_add_flag(guider_ui.screen_music_img_music_lyric, LV_OBJ_FLAG_HIDDEN); // 隐藏音乐列表
#endif
}

// 获取当前音乐模式
u8 lv_music_mode_get()
{
	return cur_music_mode;
}
/************************************音乐模式控制接口*********************************************/


/***********************************本地播放音乐控件样式*******************************************/
// 本地音乐列表
static lv_obj_t * list;
// 本地音乐列表容器
static lv_obj_t * cont_list;
// 滑动条样式
static lv_style_t style_scrollbar;
// 音乐文件标题样式
static lv_style_t style_title;
// 按钮样式
static lv_style_t style_btn;
// 按钮按下样式
static lv_style_t style_btn_pr;
// 按钮选中样式
static lv_style_t style_btn_chk;
// 按钮失能样式
static lv_style_t style_btn_dis;

// 歌词容器
static lv_obj_t * lyrics;
// 歌词标题
static lv_obj_t * lyrics_title;
// 歌词艺术家
static lv_obj_t * lyrics_artist;
// 歌词内容
static lv_obj_t * lyrics_data;
// 歌词标题样式
static lv_style_t style_lyrics_title;
// 歌词艺术家样式
static lv_style_t style_lyrics_artist;
// 歌词非高亮样式
static lv_style_t style_lyrics_not_hightlight;
// 歌词高亮样式
static lv_style_t style_lyrics_hightlight;
/***********************************本地播放音乐控件样式*******************************************/

// #endif

/***********************************本地播放布局跳转相关*******************************************/
#if EMITTER_TEST
lv_timer_t *emitter_test_timer = NULL;

void test_timer_cb()
{
	extern void lvgl_br_status_update(u8 br_status);
	u8 emitter_status = BR_CONNECTED;
	// u8 emitter_status = BR_PAGE_TIMEROUT;
	b_printf("send emitter_status = %d", emitter_status);
	lvgl_br_status_update(emitter_status);

	if(emitter_test_timer) {
		lv_timer_del(emitter_test_timer);
		emitter_test_timer = NULL;
	}
}
#endif

// 提醒页面超时定时器
lv_timer_t *wait_timeout_timer = NULL;

// 提醒页面超时回调
void wait_timeout_cb()
{
	printf("func: %s, line: %d", __func__, __LINE__);
	u8 emitter_state = box_info_base_cb.lv_emitter_state_get();
	u8 language = box_info_base_cb.lv_language_get();

	if(cur_music_mode == PHONE_MUSIC) {
		b_printf("emitter_state: %d", emitter_state);
		switch (emitter_state)
		{
			case BR_CONNECTED:
				
				break;
			case BR_DISCONNECTED:
				
				break;
			
			// 若超时或者其他值均显示超时
			case BR_PAGE_TIMEROUT:
			default:
				lv_label_set_text(guider_ui.screen_music_label_tip, music_mode_timeout[0]);
				// lv_label_set_text_fmt(guider_ui.screen_music_label_tip, "%s", music_mode_timeout[language]);
				lv_tip_wait_to_confirm();
				break;
			
			if(wait_timeout_timer){
				lv_timer_del(wait_timeout_timer);
				wait_timeout_timer = NULL;
			}
		}
	}

}

// 隐藏等待动画
void lv_hide_anim_wait()
{
#if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
	// if(!screen_music_loaded) {return;}
	lv_obj_add_flag(guider_ui.screen_music_animimg_wait, LV_OBJ_FLAG_HIDDEN);

#else
	lv_obj_add_flag(guider_ui.screen_music_spinner_wait, LV_OBJ_FLAG_HIDDEN);
#endif
}

// 显示等待动画
void lv_show_anim_wait()
{
#if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
	// if(!screen_music_loaded) {return;}
	lv_obj_clear_flag(guider_ui.screen_music_animimg_wait, LV_OBJ_FLAG_HIDDEN);

#else
	lv_obj_clear_flag(guider_ui.screen_music_spinner_wait, LV_OBJ_FLAG_HIDDEN);
#endif
}

// 隐藏提示界面label
void lv_hide_tip_label()
{
	// if(!screen_music_loaded) {return;}
	lv_obj_add_flag(guider_ui.screen_music_label_tip, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_btn_cancel_label, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(guider_ui.screen_music_btn_confirm_label, LV_OBJ_FLAG_HIDDEN);

}

// 显示提示界面label
void lv_show_tip_label()
{
	// if(!screen_music_loaded) {return;}
	lv_obj_clear_flag(guider_ui.screen_music_label_tip, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_btn_cancel_label, LV_OBJ_FLAG_HIDDEN);
	lv_obj_clear_flag(guider_ui.screen_music_btn_confirm_label, LV_OBJ_FLAG_HIDDEN);

}

// 等待页面到提醒页面
void lv_tip_wait_to_confirm()
{
	if(!screen_music_loaded) {return;}
	
	lv_show_tip_label();

	lv_hide_anim_wait();

}

// 提醒页面到等待页面
void lv_tip_confirm_to_wait()
{
	if(!screen_music_loaded) {return;}

	// 隐藏提示文字
	lv_hide_tip_label();

	// 显示动画控件
	lv_show_anim_wait();
	
#if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
	// 开启动画播放
	lv_animimg_start(guider_ui.screen_music_animimg_wait);
#endif

	// 创建搜索超时定时器
	if(!wait_timeout_timer) {
		wait_timeout_timer = lv_timer_create(wait_timeout_cb, WAIT_FOR_CONNECT_TIME, NULL);
	}

#if EMITTER_TEST
	if(!emitter_test_timer) {
		emitter_test_timer = lv_timer_create(test_timer_cb, 2000, NULL);
	}
#endif

}

// 等待页面到音乐播放页面
void lv_tip_wait_to_music_play()
{
	if(!screen_music_loaded) {return;}

	// 显示提示文字
	lv_show_tip_label();
	// 隐藏动画控件
	lv_hide_anim_wait();

	// 跳转播放界面
	lv_tip_to_music_play();
}

// 音乐播放界面跳转文件列表
void lv_music_play_to_files_list()
{
	if(!screen_music_loaded) {return;}
	// 隐藏音乐播放
	lv_obj_add_flag(guider_ui.screen_music_cont_music, LV_OBJ_FLAG_HIDDEN);

	// 隐藏上下状态栏
	lv_status_bar_bottom_hide();
	lv_status_bar_top_hide();

	// 显示文件列表
	lv_obj_clear_flag(guider_ui.screen_music_cont_music_list, LV_OBJ_FLAG_HIDDEN);
}

// 文件列表返回音乐播放界面
void lv_files_list_to_music_play()
{
	if(!screen_music_loaded) {return;}
	// 隐藏本地音乐列表
	lv_obj_add_flag(guider_ui.screen_music_cont_music_list, LV_OBJ_FLAG_HIDDEN);

	// 显示上下状态栏
	lv_status_bar_bottom_show();
	lv_status_bar_top_show();

	// 显示播放容器
	lv_obj_clear_flag(guider_ui.screen_music_cont_music, LV_OBJ_FLAG_HIDDEN);
}

// 播放界面跳转提示界面
void lv_music_play_to_tip()
{
	if(!screen_music_loaded) {return;}
	// 隐藏播放容器
	lv_obj_add_flag(guider_ui.screen_music_cont_music, LV_OBJ_FLAG_HIDDEN);

	// 隐藏上下状态栏
	lv_status_bar_bottom_hide();
	lv_status_bar_top_hide();

	// 显示提示容器
	lv_obj_clear_flag(guider_ui.screen_music_cont_tip, LV_OBJ_FLAG_HIDDEN);
}

// 提示界面跳转音乐播放界面
void lv_tip_to_music_play()
{
	if(!screen_music_loaded) {return;}
	// 隐藏提示容器
	lv_obj_add_flag(guider_ui.screen_music_cont_tip, LV_OBJ_FLAG_HIDDEN);

	// 显示上下状态栏
	lv_status_bar_bottom_show();
	lv_status_bar_top_show();

	// 显示播放容器
	lv_obj_clear_flag(guider_ui.screen_music_cont_music, LV_OBJ_FLAG_HIDDEN);
}
/***********************************本地播放布局跳转相关*******************************************/


/***********************************本地播放相关控件回调*******************************************/
static void screen_music_cont_music_event_handler (lv_event_t *e)
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
			screen_list_del(SCREEN_PRIO_MUSIC);
            break;
        }
		break;
	}
	default:
		break;
	}
}

// 点击等待动画
static void screen_music_animimg_wait_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		// printf("wait anim click");
		lv_tip_wait_to_music_play(); // 点击等待动画终止搜索
		
		break;
	}
	default:
		break;
	}
}

// 歌曲列表列表
static void screen_music_cont_music_list_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		break;
	}
	case LV_EVENT_GESTURE:
	{
		lv_indev_wait_release(lv_indev_get_act());
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir){
        case LV_DIR_LEFT:
            break;
        case LV_DIR_RIGHT:
			// 右滑隐藏音乐列表页面
			printf("gesture right, ");
			
			printf("deepth: %d", music_dir_info.deepth);

			// 目录深度大于0，即还没回到根目录
			if(music_dir_info.deepth > 0) {
				// 路径退出
				music_dir_exit();
				// 重新获取路径信息
				int file_num = open_music_file_by_path(music_dir_info.cur_path);

				// 路径有效
				if(file_num >= 0) {
					music_dir_info.deepth--; // 退出目录，目录深度自减
					if(cont_list) {
						lv_obj_del(cont_list); // 删除列表容器
						cont_list = NULL;
						/* printf("del list"); */
						// 重新创建音乐列表容器，刷新路径信息
						cont_list = lv_music_list_create(guider_ui.screen_music_cont_music_list, file_num);
					}
				} else {
					printf("open music files failed! func: %s, line: %d", __func__, __LINE__);
					// music_files_reset(); // 释放音乐文件资源
					lv_sd_music_list_deinit();
					lv_files_list_to_music_play();
					return;
				}
			} else if(music_dir_info.deepth == 0) {
				lv_files_list_to_music_play();
			} else {
				printf("err! music_dir_info.deepth < 0!");
			}
			// 打印路径信息
			debug_show_path_info();
            break;
        }

		break;
	}
	default:
		break;
	}
}

// sd卡文件列表跳转按钮
static void screen_music_img_music_sd_list_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		// 如果sd卡不在线则清除列表
		if(is_sd_card_online() == 0) {
			lv_sd_music_list_deinit(); // 如果设备不在线则反初始化
		} else {
			if(!cont_list) {
				lv_sd_music_list_init(); // 如果设备在线且cont_list被删除则重新初始化
			}
		}
		
		lv_music_play_to_files_list();

		break;
	}
	default:
		break;
	}
}

// 手机音乐/蓝牙音乐切换按钮
static void screen_music_img_music_change_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		lv_sd_music_list_init();

#if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
		usr_update_animing(guider_ui.screen_music_animimg_wait, "WAT");
#endif
		
		int language = box_info_base_cb.lv_language_get();
		// if(cur_music_mode == SD_MUSIC) {
		// 	cur_music_mode = PHONE_MUSIC;
		// 	lv_img_set_src(guider_ui.screen_music_img_music_logo, "F:/phone_image.bin"); // 切换手机音乐logo
		// 	lv_obj_add_flag(guider_ui.screen_music_img_music_sd_list, LV_OBJ_FLAG_HIDDEN); // 隐藏音乐列表
		// } else {
		// 	cur_music_mode = SD_MUSIC;
		// 	lv_img_set_src(guider_ui.screen_music_img_music_logo, "F:/sd_image.bin"); // 切换SD音乐logo
		// 	lv_obj_clear_flag(guider_ui.screen_music_img_music_sd_list, LV_OBJ_FLAG_HIDDEN); // 显示音乐列表
		// }
		// lv_label_set_text_fmt(guider_ui.screen_music_label_music_title, "%s", music_mode[language][cur_music_mode]);
		lv_label_set_text(guider_ui.screen_music_label_tip,  music_mode_tips[0][cur_music_mode]); // 根据当前模式切换提示语
		lv_label_set_text(guider_ui.screen_music_btn_cancel_label, music_mode_cancel[0]); // 根据语言切换取消标语
		lv_label_set_text(guider_ui.screen_music_btn_confirm_label, music_mode_confirm[0]); // 根据语言切换确定标语
		// lv_label_set_text_fmt(guider_ui.screen_music_label_tip, "%s", music_mode_tips[language][cur_music_mode]); // 根据当前模式切换提示语
		// lv_label_set_text_fmt(guider_ui.screen_music_btn_cancel_label, "%s", music_mode_cancel[language]); // 根据语言切换取消标语
		// lv_label_set_text_fmt(guider_ui.screen_music_btn_confirm_label, "%s", music_mode_confirm[language]); // 根据语言切换确定标语

		lv_music_play_to_tip();
		break;
	}
	default:
		break;
	}
}

// 提示界面确定按钮
static void screen_music_btn_confirm_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		if(cur_music_mode == PHONE_MUSIC) {
			// 断开手机蓝牙，打开发射器
			local_play_conn_earphone_by_addr();
			// extern void local_play_conn_earphone_by_name(void);
			// local_play_conn_earphone_by_name();
#if PC_AUDIO_EMITTER
			local_play_post_app_core_event(LOCAL_PLAY_PC_START);
#endif
			// 跳转等待界面
			lv_tip_confirm_to_wait();

		} else if(cur_music_mode == SD_MUSIC) {
			// 回连手机蓝牙
			local_play_close_bt();
#if PC_AUDIO_EMITTER
			local_play_post_app_core_event(LOCAL_PLAY_PC_STOP);
#endif
			// 跳转播放界面
			lv_tip_to_music_play();
			lv_music_mode_set_phone_music();
		} else {
			printf("music mode err!");
		}
		break;
	}
	default:
		break;
	}
}

// 提示界面取消按钮
static void screen_music_btn_cancel_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_tip_to_music_play();
		break;
	}
	default:
		break;
	}
}
/***********************************本地播放相关控件回调*******************************************/


/***********************************歌词显示布局跳转回调*******************************************/
// 歌曲播放跳转歌词显示
void lv_music_play_to_lyrics()
{
	if(!screen_music_loaded) {return;}
	// 隐藏播放容器
	lv_obj_add_flag(guider_ui.screen_music_cont_music, LV_OBJ_FLAG_HIDDEN);

	// 隐藏上下状态栏
	lv_status_bar_bottom_hide();
	lv_status_bar_top_hide();

	// 显示歌词容器
	lv_obj_clear_flag(guider_ui.screen_music_cont_lyrics, LV_OBJ_FLAG_HIDDEN);
}

// 歌词显示跳转歌曲播放
void lv_lyrics_to_music_play()
{
	if(!screen_music_loaded) {return;}
	// 隐藏歌词容器
	lv_obj_add_flag(guider_ui.screen_music_cont_lyrics, LV_OBJ_FLAG_HIDDEN);

	// 显示上下状态栏
	lv_status_bar_bottom_show();
	lv_status_bar_top_show();

	// 显示播放容器
	lv_obj_clear_flag(guider_ui.screen_music_cont_music, LV_OBJ_FLAG_HIDDEN);
}
/***********************************歌词显示布局跳转回调*******************************************/


/***********************************本地音乐文件列表构建******************************************/
// 音乐列表点击事件回调
void btn_click_event_cb(lv_event_t * e)
{
	lv_obj_t * btn = lv_event_get_target(e);
    u32 id = lv_obj_get_index(btn);
	printf("music file id: %d", id);

	u8 dir_type = get_music_file_dir_type_by_id(id);

	// 如果当前点击的是目录则进入下一级子目录
	if(dir_type == DIR_TYPE_FOLDER) {
		// 获取当前点击文件夹名称
		const char *title = get_music_file_title_by_id(id);
		/* printf("cur_p: %s", music_dir_info.cur_path); */
		printf("title: %s", title);
		
		// 根据子目录名进入目录
		music_dir_enter(title);
		// 打印目录信息
		debug_show_path_info();

		// 重新获取目录信息
		int file_num = open_music_file_by_path(music_dir_info.cur_path);

		// 路径有效
		if(file_num >= 0) {
			music_dir_info.deepth++; // 进入目录，目录深度自增
			printf("deepth: %d", music_dir_info.deepth);
			if(cont_list) {
				lv_obj_del(cont_list); // 删除音乐列表容器
				cont_list = NULL;
				/* printf("del list"); */

				// 重新创建音乐列表容器
				cont_list = lv_music_list_create(guider_ui.screen_music_cont_music_list, file_num);
			}
		} else {
			printf("open music files failed! func: %s, line: %d", __func__, __LINE__);
			// music_files_reset(); // 释放音乐文件资源
			music_dir_exit(); // 退出目录
			return;
		}
	// 如果当前点击的是文件则播放
	} else if(dir_type == DIR_TYPE_FILE) {
		// 播放
		u32 clust = get_music_file_clust_by_id(id);

		// 根据簇号播放音乐
		extern void local_play_by_sclust(u32 sclust);
		local_play_by_sclust(clust);
		printf("clust: %d", clust);

#if LOCAL_MUSIC_FILE_PRESSED_RETURN
		lv_files_list_to_music_play();
		music_dir_info_reset();

		int file_num = open_music_file_handler();

		// 路径有效
		if(file_num >= 0) {
			if(cont_list) {
				lv_obj_del(cont_list); // 删除列表容器
				cont_list = NULL;
				/* printf("del list"); */
				// 重新创建音乐列表容器，刷新路径信息
				cont_list = lv_music_list_create(guider_ui.screen_music_cont_music_list, file_num);
			}
		}
#endif
	} else {
		printf("no such type");
	}
	
}

// 添加按钮控件
static lv_obj_t * add_list_btn(lv_obj_t * parent, uint32_t track_id)
{
	// 根据id获取音乐文件名
    const char * title = get_music_file_title_by_id(track_id);

    lv_obj_t * btn = lv_obj_create(parent);
    lv_obj_remove_style_all(btn);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_size(btn, 320, 60);

    lv_obj_add_style(btn, &style_btn, 0);
    lv_obj_add_style(btn, &style_btn_pr, LV_STATE_PRESSED);
    lv_obj_add_style(btn, &style_btn_chk, LV_STATE_CHECKED);
    lv_obj_add_style(btn, &style_btn_dis, LV_STATE_DISABLED);
    lv_obj_add_event_cb(btn, btn_click_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * icon = lv_img_create(btn);

	// 根据文件类型切图
	if (get_music_file_dir_type_by_id(track_id) == DIR_TYPE_FILE) {
		lv_img_set_src(icon, "F:/music_file_image.bin");
	} else if (get_music_file_dir_type_by_id(track_id) == DIR_TYPE_FOLDER) {
		lv_img_set_src(icon, "F:/music_folder_image.bin");
	}
    
	// 将图标放在第一列
    lv_obj_set_grid_cell(icon, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    lv_obj_t * title_label = lv_label_create(btn);
    lv_obj_set_style_text_color(title_label, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_label_set_text(title_label, title);
	lv_obj_set_size(title_label, 260, 60);
    // lv_obj_clear_flag(title_label, LV_OBJ_FLAG_SCROLLABLE);
    lv_label_set_long_mode(title_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
	// 将标题放在第二列
    lv_obj_set_grid_cell(title_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_add_style(title_label, &style_title, 0);

    return btn;
}

void lv_music_list_style_init()
{
	static u8 init_flag = 0;

	// 只初始化一次
	if(!init_flag) {
		init_flag = 1;
	} else {
		return;
	}

	static const lv_coord_t grid_rows[] = {60, LV_GRID_TEMPLATE_LAST};
    static const lv_coord_t grid_cols[] = {60, 260, LV_GRID_TEMPLATE_LAST};

    lv_style_init(&style_scrollbar);
    lv_style_set_width(&style_scrollbar,  4);
    lv_style_set_bg_opa(&style_scrollbar, LV_OPA_COVER);
    lv_style_set_bg_color(&style_scrollbar, lv_color_hex3(0xeee));
    lv_style_set_radius(&style_scrollbar, LV_RADIUS_CIRCLE);
    lv_style_set_pad_right(&style_scrollbar, 4);

    lv_style_init(&style_btn);
    lv_style_set_bg_opa(&style_btn, LV_OPA_TRANSP);

	// 构建一个一行两列的网格布局
    lv_style_set_grid_column_dsc_array(&style_btn, grid_cols);
    lv_style_set_grid_row_dsc_array(&style_btn, grid_rows);
    lv_style_set_grid_row_align(&style_btn, LV_GRID_ALIGN_CENTER);
    lv_style_set_layout(&style_btn, LV_LAYOUT_GRID);
    lv_style_set_radius(&style_btn, 5);
    lv_style_set_bg_color(&style_btn, lv_color_hex(0x3c3440));
    lv_style_set_border_width(&style_btn, 2);

    lv_style_set_pad_right(&style_btn, 10);

    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, &myFont);
    lv_style_set_text_color(&style_title, lv_color_hex(0xffffff));

    lv_style_init(&style_btn_pr);
    lv_style_set_bg_opa(&style_btn_pr, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn_pr,  lv_color_hex(0x4c4965));

    lv_style_init(&style_btn_chk);
    lv_style_set_bg_opa(&style_btn_chk, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn_chk, lv_color_hex(0x4c4965));

    lv_style_init(&style_btn_dis);
    lv_style_set_text_opa(&style_btn_dis, LV_OPA_40);
    lv_style_set_img_opa(&style_btn_dis, LV_OPA_40);
}

// 创建音乐文件列表
lv_obj_t *lv_music_list_create(lv_obj_t *parent, int file_num)
{
    printf("func: %s", __func__);

    list = lv_obj_create(parent);
    lv_obj_remove_style_all(list);
    lv_obj_set_size(list, 320, 172);
    lv_obj_set_y(list, 0);
    lv_obj_add_style(list, &style_scrollbar, LV_PART_SCROLLBAR);
    lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);

	// 根据文件数创建对应数量的文件栏目
    for(int id = 0; id < file_num; id++) {
        add_list_btn(list, id);
    }

    return list;
}

// 文件列表初始化
void lv_sd_music_list_init()
{
	int file_num = open_music_file_handler();
	printf("file_num: %d", file_num);

	if(file_num < 0) {
		printf("open music files failed! func: %s, line: %d", __func__, __LINE__);
		music_dir_info_reset();
		return;
	}

	// 音乐列表样式初始化
	lv_music_list_style_init();
	mem_stats();
	cont_list = lv_music_list_create(guider_ui.screen_music_cont_music_list, file_num);
	mem_stats();
}

// 文件列表反初始化
void lv_sd_music_list_deinit()
{
	mem_stats();
	music_files_reset(); // 释放音乐文件资源
	mem_stats();
	if(cont_list) {
		lv_obj_del(cont_list); // 删除音乐列表容器
		cont_list = NULL;
	}
}

#if 0
void lv_lyrics_update_test()
{
	lv_label_set_text(lyrics_title, "123");
	lv_label_set_text(lyrics_artist, "456");
	lv_label_set_text(lyrics_data, "adsf");
	lv_label_set_text(lyrics_second_row, "你好");
	lv_label_set_text(lyrics_third_row, "hello world");

	// lv_obj_scroll_to_view(lv_obj_get_child(lyrics, 0), 1);
}

void lv_lyrics_update_title(char *input_str)
{
	if(input_str != NULL && strlen(input_str) < STR_MAX_SIZE) {
		lv_label_set_text(lyrics_title, input_str);
	}
}

void lv_lyrics_update_artist(char *input_str)
{
	if(input_str != NULL && strlen(input_str) < STR_MAX_SIZE) {
		lv_label_set_text(lyrics_artist, input_str);
	}
}

void lv_lyrics_update_content()
{
	lv_label_set_text(lyrics_data, lyrics_queue[2]);
	lv_label_set_text(lyrics_second_row, lyrics_queue[1]);
	lv_label_set_text(lyrics_third_row, lyrics_queue[0]);

	lv_obj_invalidate(lv_scr_act());
}

void lv_lyrics_create(lv_obj_t *parent)
{
	static const lv_coord_t grid_rows[] = {30, 30, 30, 30, 40, LV_GRID_TEMPLATE_LAST};
    static const lv_coord_t grid_cols[] = {320,  LV_GRID_TEMPLATE_LAST};

	lyrics = lv_obj_create(parent);
	lv_obj_remove_style_all(lyrics);
	lv_obj_set_style_bg_opa(lyrics, LV_OPA_TRANSP, 0);
	lv_obj_set_style_grid_column_dsc_array(lyrics, grid_cols, 0);
    lv_obj_set_style_grid_row_dsc_array(lyrics, grid_rows, 0);
	lv_obj_set_layout(lyrics, LV_LAYOUT_GRID);
    lv_obj_set_size(lyrics, 320, 172);
	lv_obj_set_y(lyrics, 0);

	// 标题
	lyrics_title = lv_label_create(lyrics);
	lv_obj_add_style(lyrics_title, &style_lyrics_title, 0);
	lv_obj_set_grid_cell(lyrics_title, LV_GRID_ALIGN_CENTER, 0, 1,
                                  		LV_GRID_ALIGN_CENTER, 0, 1);

	// 艺术家
	lyrics_artist = lv_label_create(lyrics);
	lv_obj_add_style(lyrics_artist, &style_lyrics_artist, 0);
	lv_obj_set_grid_cell(lyrics_artist, LV_GRID_ALIGN_CENTER, 0, 1,
                                  		LV_GRID_ALIGN_CENTER, 1, 1);

	lyrics_data = lv_label_create(lyrics);
	lv_obj_add_style(lyrics_data, &style_lyrics_not_hightlight, 0);
	lv_obj_set_grid_cell(lyrics_data, LV_GRID_ALIGN_CENTER, 0, 1,
                                  		LV_GRID_ALIGN_CENTER, 2, 1);

	lyrics_second_row = lv_label_create(lyrics);
	lv_obj_add_style(lyrics_second_row, &style_lyrics_not_hightlight, 0);
	lv_obj_set_grid_cell(lyrics_second_row, LV_GRID_ALIGN_CENTER, 0, 1,
                                  		LV_GRID_ALIGN_CENTER, 3, 1);

	lyrics_third_row = lv_label_create(lyrics);
	lv_obj_add_style(lyrics_third_row, &style_lyrics_hightlight, 0);
	lv_obj_set_grid_cell(lyrics_third_row, LV_GRID_ALIGN_CENTER, 0, 1,
                                  		LV_GRID_ALIGN_CENTER, 4, 1);
}

// 歌词显示样式初始化
void lv_lyrics_style_init()
{
	static u8 init_flag = 0;

	// 只初始化一次
	if(!init_flag) {
		init_flag = 1;
	} else {
		return;
	}

    lv_style_init(&style_lyrics_title);
    lv_style_set_text_font(&style_lyrics_title, &myFont);
    lv_style_set_text_color(&style_lyrics_title, lv_color_hex(0xededed));
	lv_style_set_bg_opa(&style_lyrics_title, LV_OPA_TRANSP);
	lv_style_set_transform_zoom(&style_lyrics_title, 0.8 * LV_IMG_ZOOM_NONE);

    lv_style_init(&style_lyrics_artist);
    lv_style_set_text_font(&style_lyrics_artist, &myFont);
    lv_style_set_text_color(&style_lyrics_artist, lv_color_hex(0xededed));
	lv_style_set_bg_opa(&style_lyrics_artist, LV_OPA_TRANSP);
	lv_style_set_transform_zoom(&style_lyrics_artist, 0.8 * LV_IMG_ZOOM_NONE);

    lv_style_init(&style_lyrics_not_hightlight);
    lv_style_set_text_font(&style_lyrics_not_hightlight, &myFont);
    lv_style_set_text_color(&style_lyrics_not_hightlight, lv_color_hex(0xededed));
	lv_style_set_bg_opa(&style_lyrics_not_hightlight, LV_OPA_TRANSP);
	lv_style_set_transform_zoom(&style_lyrics_not_hightlight, 0.8 * LV_IMG_ZOOM_NONE);

    lv_style_init(&style_lyrics_hightlight);
    lv_style_set_text_font(&style_lyrics_hightlight, &myFont);
    lv_style_set_text_color(&style_lyrics_hightlight, lv_color_hex(0xffffff));
	lv_style_set_bg_opa(&style_lyrics_hightlight, LV_OPA_TRANSP);
}

void lv_music_lyrics_init()
{
	lv_lyrics_style_init();
	lv_lyrics_create(guider_ui.screen_music_cont_lyrics);

	lv_lyrics_update_test();
}

void lv_music_lyrics_deinit()
{
	if(lv_obj_is_valid(lyrics)) {
		lv_obj_del(lyrics); // 删除歌词容器
	}
}
#endif

/***********************************本地音乐文件列表构建******************************************/

/*************************************************本地音乐相关*****************************************************/


/*************************************************歌词显示相关*****************************************************/

/*************************************歌词显示相关接口********************************************/
char lyrics_content_array[STR_MAX_SIZE] = {0};
char lyrics_artist_name_array[STR_MAX_SIZE] = {0};

void lv_lyrics_data_update()
{
	// printf(">>>>>>>>>>>>>>lv_lyrics_data_update\n");
	lv_label_set_text_fmt(lyrics_data, "%s", lyrics_content_array);
	lv_label_set_text_fmt(lyrics_artist, "%s", lyrics_artist_name_array);
}

void lv_lyrics_create(lv_obj_t *parent)
{
	lyrics_data = lv_label_create(parent);
	lv_obj_set_size(lyrics_data, 320, 50);
	lv_obj_set_pos(lyrics_data, 0, 70);
	lv_label_set_text(lyrics_data, "");
	lv_label_set_long_mode(lyrics_data, LV_LABEL_LONG_WRAP);
	lv_obj_add_style(lyrics_data, &style_lyrics_hightlight, 0);
	lv_obj_set_style_text_align(lyrics_data, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);


	lyrics_artist = lv_label_create(parent);
	lv_obj_set_size(lyrics_artist, 0.8 * 320, 50);
	lv_obj_set_pos(lyrics_artist, (1 - 0.8) * 320, 10);
	lv_label_set_text(lyrics_artist, "");
	lv_label_set_long_mode(lyrics_artist, LV_LABEL_LONG_WRAP);
	lv_obj_add_style(lyrics_artist, &style_lyrics_artist, 0);
	lv_obj_set_style_text_align(lyrics_artist, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
}

// 歌词显示样式初始化
void lv_lyrics_style_init()
{
	static u8 init_flag = 0;

	// 只初始化一次
	if(!init_flag) {
		init_flag = 1;
	} else {
		return;
	}

    lv_style_init(&style_lyrics_hightlight);
    lv_style_set_text_font(&style_lyrics_hightlight, &myFont);
    lv_style_set_text_color(&style_lyrics_hightlight, lv_color_hex(0xffffff));
	lv_style_set_bg_opa(&style_lyrics_hightlight, LV_OPA_TRANSP);

	lv_style_init(&style_lyrics_artist);
    lv_style_set_text_font(&style_lyrics_artist, &myFont);
    lv_style_set_text_color(&style_lyrics_artist, lv_color_hex(0xffffff));
	lv_style_set_bg_opa(&style_lyrics_artist, LV_OPA_TRANSP);
	lv_style_set_transform_zoom(&style_lyrics_artist, 0.8 * LV_IMG_ZOOM_NONE);
}

void lv_music_lyrics_init()
{
	lv_lyrics_style_init();
	lv_lyrics_create(guider_ui.screen_music_cont_lyrics);

}
/*************************************歌词显示相关接口********************************************/


/***********************************歌词显示相关控件回调*******************************************/
// 歌词显示回调
static void screen_music_img_music_lyric_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		lv_music_play_to_lyrics();
		break;
	}
	default:
		break;
	}
}

// 歌曲列表列表
static void screen_music_cont_lyrics_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		break;
	}
	case LV_EVENT_GESTURE:
	{
		lv_indev_wait_release(lv_indev_get_act());
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir){
        case LV_DIR_LEFT:
            break;
        case LV_DIR_RIGHT:
			// 右滑隐藏歌词显示页面
			printf("gesture right, ");
			lv_lyrics_to_music_play();
            break;
        }

		break;
	}
	default:
		break;
	}
}
/***********************************歌词显示相关控件回调*******************************************/

/*************************************************歌词显示相关*****************************************************/


/***********************************本地&蓝牙音乐事件回调******************************************/
// 暂停/播放
static void screen_music_imgbtn_music_play_or_stop_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		b_printf("func: %s, line: %d, music_mode: %d", __func__, __LINE__, cur_music_mode);
		if(cur_music_mode == SD_MUSIC) {
#if PC_AUDIO_EMITTER			
			if(get_usb_online_status()){
				extern_app_ctrl_pc_key(KEY_MUSIC_PP);
			}else
#endif
			{
				local_play_music_pp(); // 本地播放暂停接口
			}
		}else{
int music_status = box_info_base_cb.lv_music_state_get();
			b_printf("func: %s, line: %d, music_state: %d", __func__, __LINE__);
			switch (music_status)
			{
				case MUSIC_STATE_PLAY:
			box_info_send_cb.lv_music_pause_cmd_send();
			box_info_base_cb.lv_music_state_set(MUSIC_STATE_PAUSE);
			break;
				
			case MUSIC_STATE_PAUSE:
			box_info_send_cb.lv_music_play_cmd_send();
			box_info_base_cb.lv_music_state_set(MUSIC_STATE_PLAY);
			break;

			default:
					
			break;

			}
		}
		
		
		break;
	}
	default:
		break;
	}
}

// 上一首
static void screen_music_imgbtn_music_pre_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		// 切换到上一首歌曲
		if(cur_music_mode == SD_MUSIC) {
#if PC_AUDIO_EMITTER
			if(get_usb_online_status()){
				extern_app_ctrl_pc_key(KEY_MUSIC_PREV);
			}else
#endif	/* PC_AUDIO_EMITTER */
			{
				local_play_music_prev();
			}
			// local_play_conn_earphone();
			// local_play_conn_earphone_by_addr();
			// local_play_conn_earphone_by_name();
			
		} else {
			box_info_send_cb.lv_music_prev_cmd_send();
		}

		break;
	}
	default:
		break;
	}
}

// 下一首
static void screen_music_imgbtn_music_next_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		// 切换到下一首歌曲
		if(cur_music_mode == SD_MUSIC) {
local_play_music_next();
// local_play_close_bt();

		} else {
			box_info_send_cb.lv_music_next_cmd_send();
		}
		
		break;
	}
	default:
		break;
	}
}
/***********************************本地&蓝牙音乐事件回调******************************************/


void events_init_screen_music(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_music_imgbtn_music_play_or_stop, screen_music_imgbtn_music_play_or_stop_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_music_imgbtn_music_pre, screen_music_imgbtn_music_pre_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_music_imgbtn_music_next, screen_music_imgbtn_music_next_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_music_cont_music, screen_music_cont_music_event_handler, LV_EVENT_ALL, NULL);
}

void events_init_screen_music_local_music(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_music_cont_music_list, screen_music_cont_music_list_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_music_img_music_sd_list, screen_music_img_music_sd_list_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_music_img_music_change, screen_music_img_music_change_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_music_btn_confirm, screen_music_btn_confirm_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_music_btn_cancel, screen_music_btn_cancel_event_handler, LV_EVENT_ALL, NULL);
#if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
	lv_obj_add_event_cb(ui->screen_music_animimg_wait, screen_music_animimg_wait_event_handler, LV_EVENT_ALL, NULL);
#else
	lv_obj_add_event_cb(ui->screen_music_spinner_wait, screen_music_animimg_wait_event_handler, LV_EVENT_ALL, NULL);
#endif
}

void events_init_screen_music_lyrics(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_music_img_music_lyric, screen_music_img_music_lyric_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_music_cont_lyrics, screen_music_cont_lyrics_event_handler, LV_EVENT_ALL, NULL);
}

void screen_music_refresh()
{
	//判断页面存活
	if(!screen_music_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_music_label_music_title, music_mode[0][cur_music_mode]);
	}
#else
	lv_label_set_text_fmt(guider_ui.screen_music_label_music_title, "%s", music_mode[language][cur_music_mode]);
#endif
	// lv_label_set_text_fmt(guider_ui.screen_music_label_music_title, "%s", music_mode[language][cur_music_mode]);
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
		lv_obj_clear_state(guider_ui.screen_music_imgbtn_music_pre, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_music_imgbtn_music_next, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_STATE_DISABLED);
	}else{
		lv_obj_add_state(guider_ui.screen_music_imgbtn_music_pre, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_music_imgbtn_music_next, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_STATE_DISABLED);
	}

#if BT_LYRICS_ENABLE
	// if(cur_music_mode == PHONE_MUSIC) 
	{
		// 歌词刷新
		// lv_lyrics_data_update();
	}
#endif

	//音乐状态更新
	if(contorl_enable){

		if(cur_music_mode == SD_MUSIC) {
			extern int local_music_is_play(void);
			// 本地音乐是否处于播放状态
			int local_music_state = local_music_is_play();
			printf("%s %d local_music_state:%d\n", __FUNCTION__, __LINE__, local_music_state);

			if(local_music_state == 1) {
				// 切换播放图标
				lv_imgbtn_set_src(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_bofang_lianjie.bin", NULL);
				lv_imgbtn_set_src(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_bofang_weilianjie.bin", NULL);
			} else {
				// 切换暂停图标
				lv_imgbtn_set_src(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_zanting_lianjie.bin", NULL);
				lv_imgbtn_set_src(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_zanting_weilianjie.bin", NULL);
			}
		} else if(cur_music_mode == PHONE_MUSIC) {
			int music_state = box_info_base_cb.lv_music_state_get();
			// printf("%s %d phone_music_state:%d\n", __FUNCTION__, __LINE__, music_state);

			switch (music_state) {
				case MUSIC_STATE_NULL:
					break;
				case MUSIC_STATE_PLAY:
					// 切换播放图标
					lv_imgbtn_set_src(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_bofang_lianjie.bin", NULL);
					lv_imgbtn_set_src(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_bofang_weilianjie.bin", NULL);
					break;
				case MUSIC_STATE_PAUSE:
					// 切换暂停图标
					lv_imgbtn_set_src(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_zanting_lianjie.bin", NULL);
					lv_imgbtn_set_src(guider_ui.screen_music_imgbtn_music_play_or_stop, LV_IMGBTN_STATE_PRESSED, NULL, "F:/ic_zanting_weilianjie.bin", NULL);
					break;
				default:
					break;
			}
		}

	}
}


