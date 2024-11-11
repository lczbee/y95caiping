#ifndef __LV_DEMO_LANGUAGE_H_
#define __LV_DEMO_LANGUAGE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

typedef enum
{
  CHINESE = 0,      // 中文简体
  ENGLISH,          // 英语
  LANGUAGE_COUNT    // 用于记录语言数量
}LANGUAGE_ID;

void screen_language_refresh();
void screen_language_enter();
void screen_language_exist();

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_LANGUAGE_H_ */
