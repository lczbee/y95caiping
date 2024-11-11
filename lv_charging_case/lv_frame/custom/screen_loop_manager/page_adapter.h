#ifndef __PAGE_ADAPTER_H__
#define __PAGE_ADAPTER_H__

#include "lvgl.h"

// 页面ID表
enum PageId{
    ID_SCREEN_MUSIC,
    ID_SCREEN_VOLUME,
    ID_SCREEN_ANC,
    ID_SCREEN_EQUALIZER,
    ID_SCREEN_ALARM,
    ID_SCREEN_BRIGHTNESS,
    ID_SCREEN_LANGUAGE,
    ID_SCREEN_WALLPAPER,
    ID_SCREEN_FINDMY,
    ID_SCREEN_LIGHT,
    ID_SCREEN_TIME,
    ID_SCREEN_TIKTOK,
    ID_SCREEN_SNAP,
    ID_SCREEN_PC_MODE,
    ID_SCREEN_MENU,
};

/**
 * @brief 页面适配函数
 * 基于页面管理模块配置的页面派生出来的控件，必须调用该接口进行适配，否则会出现边框，以及页面无法滑动等现象
 * eg. 页面管理模块创建对象PageTypeHandle screen_music，此时screen_music会创建page作为
 *     父控件，而调用setup_scr_screen_music会基于page创建ui->screen_music，再基于ui->screen_music
 *     会创建容器ui->screen_music_cont_music，整个控件父子关系如下：
 *     (page)->(ui->screen_music)->(ui->screen_music_cont_music)，此时基于ui->screen_music层级的需要调用
 *     lv_page_manager_page_adapte，而基于ui->screen_music_cont_music层级的需要调用lv_page_manager_cont_adapte
 * @param page 基于页面管理模块创建的控件
 */
void lv_page_manager_page_adapte(lv_obj_t *page);
void lv_page_manager_cont_adapte(lv_obj_t *page);
void lv_page_manager_preempt_page_bg_adapte(lv_obj_t *page);
void lv_page_manager_preempt_page_cont_adapte(lv_obj_t *page);

/**
 * @brief 按钮适配函数
 * 基于页面关卡模块配置页面派生出来的控件，可以选择性使用该接口，针对imgbtn和btn使用
 * 一般情况下，在btn或者imgbtn上滑动无法触发页面滑动，若想触发页面滑动，可以在初始化时调用该接口
 * 将消息传递给父控件
 * @param btn 
 */
void lv_page_manager_obj_adapte(lv_obj_t *btn);

// 页面布局初始化函数

void init_screen_language(lv_obj_t *page);
void init_screen_findmy(lv_obj_t *page);
void init_screen_equalizer(lv_obj_t *page);
void init_screen_brightness(lv_obj_t *page);
void init_screen_light(lv_obj_t *page);
void init_screen_wallpaper(lv_obj_t *page);
void init_screen_music(lv_obj_t *page);
void init_screen_anc(lv_obj_t *page);
void init_screen_time(lv_obj_t *page);
void init_screen_squelch(lv_obj_t *page);
void init_screen_snap(lv_obj_t *page);
void init_screen_tiktok(lv_obj_t *page);
void init_screen_alarm(lv_obj_t *page);
void init_screen_volume(lv_obj_t *page);
void init_screen_pc_mode(lv_obj_t *page);
void init_screen_menu(lv_obj_t *page);

// 页面布局反初始化函数
void deinit_screen_language(lv_obj_t *page);
void deinit_screen_findmy(lv_obj_t *page);
void deinit_screen_equalizer(lv_obj_t *page);
void deinit_screen_brightness(lv_obj_t *page);
void deinit_screen_light(lv_obj_t *page);
void deinit_screen_wallpaper(lv_obj_t *page);
void deinit_screen_music(lv_obj_t *page);
void deinit_screen_anc(lv_obj_t *page);
void deinit_screen_time(lv_obj_t *page);
void deinit_screen_squelch(lv_obj_t *page);
void deinit_screen_snap(lv_obj_t *page);
void deinit_screen_tiktok(lv_obj_t *page);
void deinit_screen_alarm(lv_obj_t *page);
void deinit_screen_volume(lv_obj_t *page);
void deinit_screen_pc_mode(lv_obj_t *page);
void deinit_screen_menu(lv_obj_t *page);

#endif
