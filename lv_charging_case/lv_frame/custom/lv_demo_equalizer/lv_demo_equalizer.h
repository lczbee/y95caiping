#ifndef __LV_DEMO_EQUALIZER_H_
#define __LV_DEMO_EQUALIZER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"


typedef enum{
	EQ_NORMAL = 0,
	EQ_ROCK,
	EQ_POP,
	EQ_CLASSIC,
	EQ_JAZZ,
	EQ_MODE_COUNT,
}eq_type;

void screen_equalizer_refresh();
void screen_equalizer_enter();
void screen_equalizer_exist();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_EQUALIZER_H_ */
