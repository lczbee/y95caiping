#ifndef __LV_DEMO_PC_MODE_H_
#define __LV_DEMO_PC_MODE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

// 上下拉时pc模式透明度变化开关
#define PC_MODE_OPA_ENABLE  1

extern bool pc_mode_on;

void screen_pc_mode_refresh();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_PC_MODE_H_ */
