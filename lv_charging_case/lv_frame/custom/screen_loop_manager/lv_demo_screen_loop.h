#ifndef PAGE_H
#define PAGE_H

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "../lvgl/lvgl.h"
#endif
#include "PageManager.h"

//页面初始化
void screen_loop_enter();
void screen_loop_refresh();

extern bool screen_scrolled;
void screen_scroll_check(lv_event_t *e);

void screen_loop_enter_page_by_id(u8 id);

// 页面覆盖滑动模式
#define PAGE_MOVE_COVER_MODE     (DISABLE)

// 页面背景样式
enum BackGroundMode
{
    // 无背景
    NONE,
    // 图片背景
    Mode1,
    // 散点背景
    Mode2,
    //  APP背景
    Mode3,
};


#define PAGE_GESTURE_FILT   1

#endif
