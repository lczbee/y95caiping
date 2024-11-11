#ifndef __TIME_API_H_
#define __TIME_API_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "cpu.h"

extern const char *roller_year;
extern const char *roller_month;
extern const char *roller_day_31;
extern const char *roller_day_30;
extern const char *roller_day_29;
extern const char *roller_day_28;
extern const char *roller_hour_24;
extern const char *roller_hour_12;
extern const char *roller_min_sec;
extern const u8 month_max_leap[];
extern const u8 month_max[];

int a2i(const char* str);
void lvgl_time_update(struct sys_time *time);
void sbox_get_sys_time(struct sys_time *time);
void sbox_set_sys_time(struct sys_time *time);
int is_leap_year(int year);
u8 get_day_max(int year, int month);

#ifdef __cplusplus
}
#endif
#endif /* __TIME_API_H_ */
