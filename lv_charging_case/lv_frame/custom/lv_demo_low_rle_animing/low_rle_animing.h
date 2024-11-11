#ifndef __LOW_RLE_ANIM__
#define __LOW_RLE_ANIM__

#include "lvgl.h"

//  播放动画
void low_rle_anim_start(lv_obj_t * obj, int cnt, int enddly, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb);

//  停止动画
void low_rle_anim_stop(lv_obj_t * obj, lv_anim_exec_xcb_t exec_cb);

//  自定义显示第几张
void change_anim_index(lv_obj_t * obj, int32_t index);

void low_rle_anim_start2(lv_obj_t * obj, int cnt, int enddly, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb);

#endif




