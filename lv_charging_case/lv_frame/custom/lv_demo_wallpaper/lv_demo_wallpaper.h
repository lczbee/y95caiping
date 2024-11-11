#ifndef __LV_DEMO_WALLPAPER_H_
#define __LV_DEMO_WALLPAPER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

// 锁屏动画数量
#define LOCK_NUM    5

#define LOCK_LOOP_ENABLE    1

//extern  char *lock_small_tab[];
extern  char *lock_big_tab[];

void animimg_update_screen_wallpaper();

void screen_wallpaper_refresh();
void screen_wallpaper_enter();
void screen_wallpaper_exist();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_WALLPAPER_H_ */
