#ifndef __LV_DEMO_LOCK_H_
#define __LV_DEMO_LOCK_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

extern int cur_lock_index;

void screen_lock_enter();

void screen_lock_refresh();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_LOCK_H_ */
