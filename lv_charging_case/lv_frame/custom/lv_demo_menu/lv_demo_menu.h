#ifndef __LV_DEMO_MENU_H_
#define __LV_DEMO_MENU_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

// 图标信息
struct icon_info_t {
    // 图标id
    u8 icon_id;
    // 图标图片源
    char *icon_src;
    // 图标回调
    void (*icon_cb)(void);
    char * icon_name;
};

#define LV_DEMO_MENU_EN 1

#if LV_DEMO_MENU_EN

// 菜单图标记忆项
extern int menu_icon_mem;

void screen_menu_refresh();
void lv_menu_init(lv_obj_t *page);
void lv_menu_deinit();

void screen_menu_hide_near_page(enum PageId id);
void screen_menu_show_near_page(enum PageId id);

#else

#define screen_menu_refresh(...)        do { }while(0)
#define lv_menu_init(...)               do { }while(0)  
#define lv_menu_deinit(...)             do { }while(0)
#define events_init_screen_menu(...)    do { }while(0)

#endif

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_MENU_H_ */
