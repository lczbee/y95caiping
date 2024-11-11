#ifndef __MSG_ACTION__
#define __MSG_ACTION__

#include "cpu.h"
//  跨线程触发ui执行void (*func)(void)
int send_to_trig_ui_vcb(void (*func)(void));
//  跨线程触发appcore执行void (*func)(void)
int send_to_trig_app_core_vcb(void (*func)(void));
//  拦截消息
void usr_hinder_msg(u8 i);


#endif