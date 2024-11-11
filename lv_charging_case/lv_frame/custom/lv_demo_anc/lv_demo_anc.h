#ifndef __LV_DEMO_ANC_H_
#define __LV_DEMO_ANC_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

void screen_anc_refresh();
void screen_anc_enter();
void screen_anc_exist();

void lv_anc_mode_update(int anc_mode);



#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_ANC_H_ */
