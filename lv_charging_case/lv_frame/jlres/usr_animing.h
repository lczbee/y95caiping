#ifndef __USR_ANIMIMG__
#define __USR_ANIMIMG__

#include "lvgl.h"

// void animing_table_update(。);

void usr_update_animing(lv_obj_t * obj, char *res_name);
void usr_free_animing(lv_obj_t * obj, void * orisrc, u8 num, int duration, u16 repeat_count);


void usr_update_state_img(char *res_name);
void * get_state_img_src(char *res_name, u8 idx);
void usr_free_state_img(char *res_name);

#endif