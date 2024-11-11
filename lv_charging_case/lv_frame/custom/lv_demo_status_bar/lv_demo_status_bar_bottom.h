#ifndef __LV_STATUS_BAR_BOTTOM_H_
#define __LV_STATUS_BAR_BOTTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

typedef struct {
    lv_obj_t *cont;                // 容器

    lv_obj_t *img_slider_bottom;   // 底部页面进度条
}lv_status_bar_bottom;

extern lv_status_bar_bottom status_bar_bottom;

void lv_status_bar_bottom_init(lv_obj_t *page);

// 根据页面id设置底部进度条，在页面居中后调用
void lv_upadate_status_bar_bottom_by_id(enum PageId id);

// 显示下状态栏
void lv_status_bar_bottom_show();

// 隐藏下状态栏
void lv_status_bar_bottom_hide();

void status_bar_bottom_refresh();


#ifdef __cplusplus
}
#endif
#endif /* __LV_STATUS_BAR_BOTTOM_H_ */
