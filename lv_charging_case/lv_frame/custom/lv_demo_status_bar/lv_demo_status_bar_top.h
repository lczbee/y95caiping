

#ifndef __LV_DEMO_STATUS_BAR_TOP_H_
#define __LV_DEMO_STATUS_BAR_TOP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

typedef struct {
    lv_obj_t *cont;                 // 容器

    lv_obj_t *label_battery_left;   // L耳机电量
    lv_obj_t *label_battery_right;  // R耳机电量
    lv_obj_t *label_battery_box;    // 仓电量
    lv_obj_t *label_time;           // 时间显示

    lv_obj_t *img_bt_state;         // 蓝牙连接状态
    lv_obj_t *img_right_bat;        // R耳机充电图标
    lv_obj_t *img_left_bat;         // L耳机充电图标
    lv_obj_t *img_box_bat;          // 仓充电图标
}lv_status_bar_top;

extern lv_status_bar_top status_bar_top;

void lv_status_bar_top_init(lv_obj_t *page);

// 显示上状态栏
void lv_status_bar_top_show();

// 隐藏上状态栏
void lv_status_bar_top_hide();

void status_bar_top_refresh();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_STATUS_BAR_TOP_H_ */
