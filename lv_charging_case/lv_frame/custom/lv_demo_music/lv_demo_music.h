/*
 * @Description: 
 * @Author: HJY
 * @Date: 2024-01-23 18:32:37
 * @LastEditTime: 2024-01-23 18:47:14
 * @LastEditors: HJY
 */
#ifndef __LV_DEMO_MUSIC_H_
#define __LV_DEMO_MUSIC_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"
#include "sd_music_api.h"

void lv_music_status_update();

void screen_music_enter();
void screen_music_exist();

// 本地音乐开关
#define LOCAL_MUSIC_ENABLE	1

#if LOCAL_MUSIC_ENABLE

// 动画模式（不耗ram，跟自己使用的动画有关）
#define WAIT_ANIMIMG	0
// SPINNER模式（耗ram，约耗多20k，动感强一些）
#define WAIT_SPINNER	1

#define WAIT_ANIM_SELECT	WAIT_ANIMIMG

// 按下歌曲文件返回播放界面开关
#define LOCAL_MUSIC_FILE_PRESSED_RETURN	1

#endif

// 蓝牙歌词显示开关
#define BT_LYRICS_ENABLE	1

// 等待连接时间
#define WAIT_FOR_CONNECT_TIME	8000

// 发射器测试模式（通过定时器模拟发射器返回状态，仅作为UI测试使用）
#define EMITTER_TEST	1

// 音乐模式
enum{
	PHONE_MUSIC = 0, // 手机音乐
	SD_MUSIC,		 // SD卡音乐
	MUSIC_TYPE_COUNT,
};

// #if LOCAL_MUSIC_ENABLE
/**************************************本地播放相关******************************************/
// 目录信息
struct dir_info {
	u8 deepth;			// 目录深度，基于根目录，在根目录时deepth为0，每进入一级子目录递增1
	char sub_path[MAX_MUSIC_NAME_LEN];	// 用于储存上一级目录，预留，未实际应用到
	char cur_path[MAX_MUSIC_NAME_LEN];  // 用于储存当前目录
};

// 设置音乐模式为手机音乐
void lv_music_mode_set_phone_music();

// 设置音乐模式为sd音乐
void lv_music_mode_set_sd_music();

// 获取当前音乐模式
u8 lv_music_mode_get();

// 等待页面到提醒页面
void lv_tip_wait_to_confirm();

// 提醒页面到等待页面
void lv_tip_confirm_to_wait();

// 等待页面到音乐播放页面
void lv_tip_wait_to_music_play();

// 音乐播放界面跳转文件列表
void lv_music_play_to_files_list();

// 文件列表返回音乐播放界面
void lv_files_list_to_music_play();

// 播放界面跳转提示界面
void lv_music_play_to_tip();

// 提示界面跳转音乐播放界面
void lv_tip_to_music_play();

// sd音乐列表构建
lv_obj_t *lv_music_list_create(lv_obj_t *parent, int file_num);

// sd音乐列表初始化
void lv_sd_music_list_init();

// sd音乐列表反初始化
void lv_sd_music_list_deinit();

#define LYRICS_MAX_SIZE 256
#define LYRICS_MAX_NUM  3

#define STR_MAX_SIZE    LYRICS_MAX_SIZE
#define STR_MAX_NUM     LYRICS_MAX_NUM

extern char lyrics_content_array[STR_MAX_SIZE];
extern char lyrics_artist_name_array[STR_MAX_SIZE];

// 歌词初始化
void lv_music_lyrics_init();

// 歌词内容更新
void lv_lyrics_data_update();


void screen_music_refresh();
/**************************************本地播放相关******************************************/
// #endif

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_MUSIC_H_ */
