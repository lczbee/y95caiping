#ifndef __LV_DEMO_WEATHER_H_
#define __LV_DEMO_WEATHER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

#define LV_DEMO_WEATHER_EN  1

#if LV_DEMO_WEATHER_EN

void screen_weather_enter();
void screen_weather_exit();
void screen_weather_refresh();
void func_attr_weather_info_set(void *priv, u8 attr, u8 *data, u16 len);

#else 

#define screen_weather_enter(...)   do { }while(0)
#define screen_weather_exit(...)    do { }while(0)
#define screen_weather_refresh(...) do { }while(0)

#endif

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_WEATHER_H_ */
