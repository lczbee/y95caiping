#ifndef __SOC__
#define __SOC__

#include "cpu.h"
//  开机前电压判断
void usr_check_power_on_voltage(void);

//  初始化
void soc_check_init();

// VDDIO上电、update等
void set_soc_first_work(u8 i);

//  电量获取
int get_curr_soc();

#endif