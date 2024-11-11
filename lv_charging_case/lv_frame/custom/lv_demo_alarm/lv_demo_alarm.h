#ifndef __LV_DEMO_ALARM_H_
#define __LV_DEMO_ALARM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

extern const char *clock_stop[];
extern const char *clock_repeat[];
extern const char clock_time[];

extern const int clock_time_num;

extern int clock_time_index; // 闹钟常用设置索引


void screen_alarm_refresh();
void screen_alarm_enter();
void screen_alarm_exist();

void lv_cont_alarm_reset();



#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_ALARM_H_ */
