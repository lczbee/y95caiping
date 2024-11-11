#ifndef __LV_DEMO_TIKTOK_H_
#define __LV_DEMO_TIKTOK_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

#define TIKTOK_INTERVAL (150)
#define TIKTOK_PLAY_NUM (5)

extern lv_timer_t *tiktok_timer;

void screen_tiktok_refresh();
void screen_tiktok_enter();
void screen_tiktok_exist();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_TIKTOK_H_ */
