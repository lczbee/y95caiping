#ifndef __LV_DEMO_FINDMY_H_
#define __LV_DEMO_FINDMY_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

typedef enum{
	FIND_CLOSE = 0,
	FIND_MY_L,
	FIND_MY_R,
	FIND_MY_LR,
} FIND_MY;

void screen_findmy_refresh();
void screen_findmy_enter();
void screen_findmy_exist();


#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_FINDMY_H_ */
