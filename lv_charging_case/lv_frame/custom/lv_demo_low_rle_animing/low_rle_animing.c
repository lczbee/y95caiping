/**
 * @file lv_animimg.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"
#include "imb2lvgl.h"
#include "low_rle_animing.h"
#include "src/misc/lv_gc.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void draw_cleanup(_lv_img_cache_entry_t * cache)
{
    /*Automatically close images with no caching*/
#if LV_IMG_CACHE_DEF_SIZE == 0
    lv_img_decoder_close(&cache->dec_dsc);
#else
    LV_UNUSED(cache);
#endif
}

static void del_pre_animal(char * imgsrc){
    lv_anim_t * a        = _lv_ll_get_head(&LV_GC_ROOT(_lv_anim_ll));
    while(a != NULL) {
        if(a->var){
            if(lv_obj_has_class(a->var, &lv_img_class)){
                lv_img_t * aimg = a->var;
                if(aimg->src_type == LV_IMG_SRC_FILE) {
                    r_printf("%s %s", aimg->src, imgsrc);
                    if(!strcmp(aimg->src, imgsrc)) {
                        lv_anim_del(a->var, NULL);
                        a        = _lv_ll_get_head(&LV_GC_ROOT(_lv_anim_ll));
                        continue;
                    }
                }
            }
        }

        a = _lv_ll_get_next(&LV_GC_ROOT(_lv_anim_ll), a);
    }
}

void change_anim_index(lv_obj_t * obj, int32_t index){
    lv_img_t * img = obj;

    // printf("%s %d", __func__, index);

    lv_color_t recolor;
    recolor.full = 0;
    if(!img || !img->src) return;
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(img->src, recolor, 0);
    if(cdsc == NULL) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;

    if(usr_data->img_file.format != PIXEL_FMT_GIF && usr_data->img_file.format != PIXEL_FMT_JPEG){


        return;
    }

    if(usr_data->img_file.format == PIXEL_FMT_JPEG){
        usr_data->nowid = index;
        lv_obj_invalidate(obj);
        draw_cleanup(cdsc);
        return;
    }

    usr_data->nowindex = index;
    read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &(usr_data->dframe), usr_data->nowindex, usr_data->gifinfo.version);
    if(usr_data->dframe.base_index != usr_data->bframe.curr_index){
        read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &(usr_data->bframe), usr_data->dframe.base_index, usr_data->gifinfo.version);
        if(usr_data->bframe.flag&BIT(0)){
            read_image_data(0, usr_data->fd, &(usr_data->img_file), usr_data->btub, 256 * 4, usr_data->bframe.addr);
        }
    }

    // g_printf("dframe delay %d",usr_data->dframe.delay);

    if(usr_data->dframe.delay) {
        // lv_anim_set_delay(usr_data->dframe.delay)   ;
    }

    static int last_time = 0;
    if(last_time == 0){last_time = lv_tick_get();}
    // printf("当前时间撮 %d 与上次差值 %d 下一帧间隔 ：%d ", lv_tick_get(), lv_tick_elaps(last_time), usr_data->dframe.delay);
    last_time = lv_tick_get();
    // usr_data->nowindex = index;//(usr_data->nowindex % usr_data->gifinfo.frame_num) + 1;

    lv_obj_invalidate(obj);

    draw_cleanup(cdsc);
}

void change_anim_index2(lv_obj_t * obj, int32_t index){
    // lv_img_t * img = obj;
    void * src = lv_obj_get_style_bg_img_src(obj, 0);
    // printf("%s %d", __func__, index);

    lv_color_t recolor;
    recolor.full = 0;
    if(!src || !src) return;
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(src, recolor, 0);
    if(cdsc == NULL) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;

    if(usr_data->img_file.format != PIXEL_FMT_GIF && usr_data->img_file.format != PIXEL_FMT_JPEG){


        return;
    }

    if(usr_data->img_file.format == PIXEL_FMT_JPEG){
        usr_data->nowid = index;
        lv_obj_invalidate(obj);
        draw_cleanup(cdsc);
        return;
    }

    usr_data->nowindex = index;
    read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &(usr_data->dframe), usr_data->nowindex, usr_data->gifinfo.version);
    if(usr_data->dframe.base_index != usr_data->bframe.curr_index){
        read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &(usr_data->bframe), usr_data->dframe.base_index, usr_data->gifinfo.version);
        if(usr_data->bframe.flag&BIT(0)){
            read_image_data(0, usr_data->fd, &(usr_data->img_file), usr_data->btub, 256 * 4, usr_data->bframe.addr);
        }
    }

    // g_printf("dframe delay %d",usr_data->dframe.delay);

    if(usr_data->dframe.delay) {
        // lv_anim_set_delay(usr_data->dframe.delay)   ;
    }

    static int last_time = 0;
    if(last_time == 0){last_time = lv_tick_get();}
    // printf("当前时间撮 %d 与上次差值 %d 下一帧间隔 ：%d ", lv_tick_get(), lv_tick_elaps(last_time), usr_data->dframe.delay);
    last_time = lv_tick_get();
    // usr_data->nowindex = index;//(usr_data->nowindex % usr_data->gifinfo.frame_num) + 1;

    lv_obj_invalidate(obj);

    draw_cleanup(cdsc);
}

void change_anim_index3(lv_obj_t * obj, int32_t index){
    // lv_img_t * img = obj;
    // void * src = lv_obj_get_style_bg_img_src(obj, 0);

    void * src = ((lv_animimg_t * )obj)->img.src;
    printf("%s %d %s", __func__, index, src);

    lv_color_t recolor;
    recolor.full = 0;
    if(!src || !src) return;
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(src, recolor, 0);
    if(cdsc == NULL) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;

    if(usr_data->img_file.format != PIXEL_FMT_GIF && usr_data->img_file.format != PIXEL_FMT_JPEG){


        return;
    }

    if(usr_data->img_file.format == PIXEL_FMT_JPEG){
        usr_data->nowid = index;
        lv_obj_invalidate(obj);
        draw_cleanup(cdsc);
        return;
    }

    usr_data->nowindex = index;
    read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &(usr_data->dframe), usr_data->nowindex, usr_data->gifinfo.version);
    if(usr_data->dframe.base_index != usr_data->bframe.curr_index){
        read_gif_file_frame(0, usr_data->fd, &(usr_data->img_file), &(usr_data->bframe), usr_data->dframe.base_index, usr_data->gifinfo.version);
        if(usr_data->bframe.flag&BIT(0)){
            read_image_data(0, usr_data->fd, &(usr_data->img_file), usr_data->btub, 256 * 4, usr_data->bframe.addr);
        }
    }

    g_printf("dframe delay %d",usr_data->dframe.delay);

    if(usr_data->dframe.delay) {
        // lv_anim_set_delay(usr_data->dframe.delay)   ;
    }

    static int last_time = 0;
    if(last_time == 0){last_time = lv_tick_get();}
    printf("当前时间撮 %d 与上次差值 %d 下一帧间隔 ：%d ", lv_tick_get(), lv_tick_elaps(last_time), usr_data->dframe.delay);
    last_time = lv_tick_get();
    // usr_data->nowindex = index;//(usr_data->nowindex % usr_data->gifinfo.frame_num) + 1;

    lv_obj_invalidate(obj);

    draw_cleanup(cdsc);
}

// static void start_cb(struct _lv_anim_t * st){

// }

// static void ready_cb(struct _lv_anim_t * st){

// }

static void deleted_cb(struct _lv_anim_t * tt){
    lv_img_t * obj = tt->var;
    printf("!!!!!!!!!img_deleted_cb_auto_relase!!!!!!!!!DANMU RELASE  obj %x", obj);
    // if(lv_obj_is_valid(obj)){   //  animal 的del OBJ基本存活
    //     lv_img_cache_invalidate_src(obj->src);
    // }

    struct myframedata * _allframeinfo = tt->user_data;
    if(_allframeinfo){
        free(_allframeinfo);
    }
}

static int32_t low_rle_anim_path_cb(const lv_anim_t * a);
//  obj与SRC进行绑定
// LV_ANIM_REPEAT_INFINITE
void low_rle_anim_start(lv_obj_t * obj, int cnt, int enddly, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb){
    lv_anim_t anim;
    lv_img_t * img = obj;

    lv_color_t recolor;
    recolor.full = 0;
    if(!img || !img->src) return;
    lv_img_cache_invalidate_src(img->src);
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(img->src, recolor, 0);
    if(cdsc == NULL) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;

    if(usr_data->img_file.format != PIXEL_FMT_GIF && usr_data->img_file.format != PIXEL_FMT_JPEG){
        draw_cleanup(cdsc);
        return;
    }

    // usr_data->endly = endly;
    // usr_data->func  = fun;
    // usr_data->func_data = fun_data;

    usr_data->obj = obj;
    int max = usr_data->gifinfo.frame_num;
    int now = usr_data->nowindex;
    int delay =  usr_data->gifinfo.delay;

    if(usr_data->img_file.format == PIXEL_FMT_JPEG){
        max = 373;
        now =1;
        delay = 46;
    }

    int alltime = 0;
    if(usr_data->allframeinfo){
        int idx = 1;
        for(idx = 1; idx <= usr_data->allframeinfo->num; idx++){
            alltime += usr_data->allframeinfo->delay[idx-1];
        }
    }

    struct myframedata * _allframeinfo = zalloc(sizeof(int)*(usr_data->allframeinfo->num)+sizeof(usr_data->allframeinfo->num));
    if(_allframeinfo)memcpy(_allframeinfo, usr_data->allframeinfo, sizeof(int)*(usr_data->allframeinfo->num)+sizeof(usr_data->allframeinfo->num));
    

    draw_cleanup(cdsc);


    printf("%s idx alltime %d %d", __func__, usr_data->allframeinfo->num, alltime);
    
    del_pre_animal(img->src);
    

    lv_anim_init(&anim);
    lv_anim_set_var(&anim, obj);
    lv_anim_set_user_data(&anim, _allframeinfo);
    lv_anim_set_time(&anim, alltime);
    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)change_anim_index);
    lv_anim_set_values(&anim , 1, max);
    lv_anim_set_path_cb(&anim, low_rle_anim_path_cb);
    if(cnt <= 0){
        lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
    } else {
        lv_anim_set_repeat_count(&anim, cnt);
    }
    
    lv_anim_set_playback_time(&anim, 0);
    lv_anim_set_playback_delay(&anim, enddly);

    lv_anim_set_start_cb(&anim, start_cb);
    lv_anim_set_ready_cb(&anim, ready_cb);
    lv_anim_set_deleted_cb(&anim, deleted_cb);

    lv_anim_start(&anim);
}


void low_rle_anim_start2(lv_obj_t * obj, int cnt, int enddly, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb){
    lv_anim_t anim;
    // lv_img_t * img = obj;
    void * src = lv_obj_get_style_bg_img_src(obj, 0);
    lv_color_t recolor;
    recolor.full = 0;
    if(!src || !src) return;
    lv_img_cache_invalidate_src(src);
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(src, recolor, 0);
    if(cdsc == NULL) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;

    if(usr_data->img_file.format != PIXEL_FMT_GIF && usr_data->img_file.format != PIXEL_FMT_JPEG){
        draw_cleanup(cdsc);
        return;
    }

    // usr_data->endly = endly;
    // usr_data->func  = fun;
    // usr_data->func_data = fun_data;

    usr_data->obj = obj;
    int max = usr_data->gifinfo.frame_num;
    int now = usr_data->nowindex;
    int delay =  usr_data->gifinfo.delay;

    if(usr_data->img_file.format == PIXEL_FMT_JPEG){
        max = 373;
        now =1;
        delay = 46;
    }

    int alltime = 0;
    if(usr_data->allframeinfo){
        int idx = 1;
        for(idx = 1; idx <= usr_data->allframeinfo->num; idx++){
            alltime += usr_data->allframeinfo->delay[idx-1];
        }
    }

    struct myframedata * _allframeinfo = zalloc(sizeof(int)*(usr_data->allframeinfo->num)+sizeof(usr_data->allframeinfo->num));
    if(_allframeinfo)memcpy(_allframeinfo, usr_data->allframeinfo, sizeof(int)*(usr_data->allframeinfo->num)+sizeof(usr_data->allframeinfo->num));
    

    draw_cleanup(cdsc);


    printf("%s idx alltime %d %d", __func__, usr_data->allframeinfo->num, alltime);
    
del_pre_animal(src);
    

    lv_anim_init(&anim);
    lv_anim_set_var(&anim, obj);
    lv_anim_set_user_data(&anim, _allframeinfo);
    lv_anim_set_time(&anim, alltime);
    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)change_anim_index2);
    lv_anim_set_values(&anim , 1, max);
    lv_anim_set_path_cb(&anim, low_rle_anim_path_cb);
    if(cnt <= 0){
        lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
    } else {
        lv_anim_set_repeat_count(&anim, cnt);
    }
    
    lv_anim_set_playback_time(&anim, 0);
    lv_anim_set_playback_delay(&anim, enddly);

    lv_anim_set_start_cb(&anim, start_cb);
    lv_anim_set_ready_cb(&anim, ready_cb);
    lv_anim_set_deleted_cb(&anim, deleted_cb);

    lv_anim_start(&anim);
}


void low_rle_anim_start3(lv_obj_t * obj, int cnt, int enddly, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb){
    lv_anim_t anim;
    // lv_img_t * img = obj;

    void * src = ((lv_animimg_t * )obj)->img.src;

    g_printf("%s %s", __func__, src);

    // void * src = lv_obj_get_style_bg_img_src(obj, 0);
    lv_color_t recolor;
    recolor.full = 0;
    if(!src || !src) return;
    lv_img_cache_invalidate_src(src);
    _lv_img_cache_entry_t * cdsc = _lv_img_cache_open(src, recolor, 0);
    if(cdsc == NULL) return;
    struct jl_animimg_info * usr_data = cdsc->dec_dsc.user_data;
    if(usr_data == NULL) return;
    if(cdsc->dec_dsc.decoder->user_data != 0x314159) return;

    if(usr_data->img_file.format != PIXEL_FMT_GIF && usr_data->img_file.format != PIXEL_FMT_JPEG){
        draw_cleanup(cdsc);
        return;
    }

    // usr_data->endly = endly;
    // usr_data->func  = fun;
    // usr_data->func_data = fun_data;

    usr_data->obj = obj;
    int max = usr_data->gifinfo.frame_num;
    int now = usr_data->nowindex;
    int delay =  usr_data->gifinfo.delay;

    if(usr_data->img_file.format == PIXEL_FMT_JPEG){
        max = 373;
        now =1;
        delay = 46;
    }

    int alltime = 0;
    if(usr_data->allframeinfo){
        int idx = 1;
        for(idx = 1; idx <= usr_data->allframeinfo->num; idx++){
            alltime += usr_data->allframeinfo->delay[idx-1];
        }
    }

    struct myframedata * _allframeinfo = zalloc(sizeof(int)*(usr_data->allframeinfo->num)+sizeof(usr_data->allframeinfo->num));
    if(_allframeinfo)memcpy(_allframeinfo, usr_data->allframeinfo, sizeof(int)*(usr_data->allframeinfo->num)+sizeof(usr_data->allframeinfo->num));
    

    draw_cleanup(cdsc);


    printf("%s idx alltime %d %d", __func__, usr_data->allframeinfo->num, alltime);
    

    del_pre_animal(src);

    lv_anim_init(&anim);
    lv_anim_set_var(&anim, obj);
    lv_anim_set_user_data(&anim, _allframeinfo);
    lv_anim_set_time(&anim, alltime);
    lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)change_anim_index3);
    lv_anim_set_values(&anim , 1, max);
    lv_anim_set_path_cb(&anim, low_rle_anim_path_cb);
    if(cnt <= 0){
        lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
    } else {
        lv_anim_set_repeat_count(&anim, cnt);
    }
    
    lv_anim_set_playback_time(&anim, 0);
    lv_anim_set_playback_delay(&anim, enddly);

    lv_anim_set_start_cb(&anim, start_cb);
    lv_anim_set_ready_cb(&anim, ready_cb);
    lv_anim_set_deleted_cb(&anim, deleted_cb);

    lv_anim_start(&anim);
}

void low_rle_anim_stop(lv_obj_t * obj, lv_anim_exec_xcb_t exec_cb) {
    lv_anim_del(obj, exec_cb);
}


static int32_t low_rle_anim_path_cb(const lv_anim_t * a)
{
    struct myframedata * _allframeinfo = a->user_data;
    if(!_allframeinfo){
        printf("_allframeinfo == NULL");
        return 0;
    }

    int now_idx = 1;
    int frame_time = 0;
    int allnum = _allframeinfo->num;

    for(now_idx = 1; now_idx <= allnum; now_idx++){
        frame_time += _allframeinfo->delay[now_idx-1];
        if(frame_time > a->act_time){
            break;
        }
    }
    
    if(a->act_time >= a->time) now_idx = a->end_value;

    return LV_CLAMP(a->start_value, now_idx, a->end_value);
}

