#ifndef __LV_DEMO_VOLUME_H_
#define __LV_DEMO_VOLUME_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

void lv_vloume_status_update(void);

void screen_volume_refresh();
void screen_volume_enter();
void screen_volume_exist();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_VOLUME_H_ */
