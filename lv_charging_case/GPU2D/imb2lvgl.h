#include "lvgl.h"
#include "res/resfile.h"
#include "gif/gif.h"


struct gif_file_frame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 curr_index;
    u16 base_index;
    u16 delay;
    u16 flag;
    u32 addr;
    u32 size;
    u32 decsize;
};

struct myframedata {
    int num;
    int delay[0];
};

struct jl_animimg_info {
    lv_obj_t* obj;
    RESFILE * fd;
    struct image_file img_file;
    struct flash_file_info ui_resfile_info;
    struct gif_file_info gifinfo;
    struct gif_file_frame bframe;
    struct gif_file_frame dframe;
    int nowindex;
    int nowid;
    lv_timer_t * nexttime;
    u8 btub[256*4];
    int alltime;
    int endly;
    void (*func)(void *p);
    void * func_data;
    struct myframedata *allframeinfo;

};