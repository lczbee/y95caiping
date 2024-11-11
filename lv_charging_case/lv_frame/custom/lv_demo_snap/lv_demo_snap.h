#ifndef __LV_DEMO_SNAP_H_
#define __LV_DEMO_SNAP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

// 定时器间隔
#define TAKEPHOTO_INTERVAL (250)
// 定时器调用次数
#define TAKEPHOTO_PLAY_NUM (5)
// 旋转角度1
#define TAKEPHOTO_ANG_1		(250)
// 旋转角度2
#define TAKEPHOTO_ANG_2		(3600 - TAKEPHOTO_ANG_1)

extern lv_timer_t *snap_timer;

void screen_snap_refresh();
void screen_snap_enter();
void screen_snap_exist();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_SNAP_H_ */
