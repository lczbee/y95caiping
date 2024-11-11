#ifndef __LV_DEMO_POP_UP_H_
#define __LV_DEMO_POP_UP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
#include "screen_loop_manager/page_adapter.h"

#define LV_DEMO_POP_UP_EN   (0)

#if LV_DEMO_POP_UP_EN
void screen_pop_up_refresh();
void pop_up_set_l_inbox_last_status(u8 status);
void pop_up_set_r_inbox_last_status(u8 status);
void pop_up_set_box_clid_last_status(u8 status);
void screen_pop_up_trig();
void screen_pop_up_callback_enter();
void screen_pop_up_callback_enter_filter();
void screen_pop_up_enter();
void screen_pop_up_exit();

#else
#define screen_pop_up_refresh(...)                      do { }while(0)
#define pop_up_set_r_inbox_last_status(...)             do { }while(0)
#define pop_up_set_r_inbox_last_status(...)             do { }while(0)
#define pop_up_set_box_clid_last_status(...)            do { }while(0)
#define screen_pop_up_trig(...)                         do { }while(0)
#define screen_pop_up_callback_enter(...)               do { }while(0)
#define screen_pop_up_callback_enter_filter(...)        do { }while(0)
#define screen_pop_up_enter(...)                        do { }while(0)
#define screen_pop_up_exit(...)                         do { }while(0)

#endif

enum {
    OUT_OF_BOX = 0, // 不在仓
    IN_BOX = 1,     // 在仓
};

enum {
    LID_OPEN = 1,   // 开盖
    LID_CLOSE,      // 关盖
};

#ifdef __cplusplus
}
#endif
#endif /* __LV_DEMO_POP_UP_H_ */
