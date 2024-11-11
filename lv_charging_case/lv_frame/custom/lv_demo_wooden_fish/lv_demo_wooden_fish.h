#ifndef __LV_DEMO_WOODEN_FISH_H_
#define __LV_DEMO_WOODEN_FISH_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

#define LV_DEMO_WOODEN_FISH_EN      1

#if LV_DEMO_WOODEN_FISH_EN

void screen_wooden_fish_enter();

#else

#define screen_wooden_fish_enter(...)   do { }while(0)

#endif


#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_CALL_H_ */


