#ifndef __LV_DEMO_BRIGHTNESS_H_
#define __LV_DEMO_BRIGHTNESS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"


/**************************************************light level****************************************************/
#define LIGHT_LEVEL_MAX    100  // 亮度最大等级
#define LIGHT_LEVEL_MIN    0	// 亮度最小等级
#define LIGHT_LEVEL_STEP   10   // 亮度步进
/**************************************************light level****************************************************/

void screen_brightness_refresh();
void screen_brightness_enter();
void screen_brightness_exist();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_BRIGHTNESS_H_ */
