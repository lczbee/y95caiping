#include "lvgl.h"
#include "cpu.h"

const u8 flex_dir = LV_FLEX_FLOW_ROW;
const u8 scoll_dir = LV_DIR_HOR;
const u8  MAX_PAGE = 13;

static u8 now_id = 0;


lv_obj_t * mpage[MAX_PAGE];

lv_obj_t * jl_tileview_create(lv_obj_t * parent);

lv_obj_t * jl_tileview_add_tile(lv_obj_t * tv, uint8_t col_id, uint8_t row_id, lv_dir_t dir);

void jl_obj_set_tile(lv_obj_t * tv, lv_obj_t * tile_obj, lv_anim_enable_t anim_en);
void jl_obj_set_tile_id(lv_obj_t * tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en);

lv_obj_t * jl_tileview_get_tile_act(lv_obj_t * obj);

static void obj_event (lv_event_t * event);

lv_obj_t * jl_tileview_create(lv_obj_t * parent){
    lv_obj_t * screen_tv_card = lv_obj_create(parent);
    lv_obj_remove_style_all(screen_tv_card);
    lv_obj_set_size(screen_tv_card, lv_area_get_width(&parent->coords), lv_area_get_height(&parent->coords));
    lv_obj_set_scroll_snap_x(screen_tv_card, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_flex_flow(screen_tv_card, flex_dir);
    lv_obj_align(screen_tv_card, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_scroll_dir(screen_tv_card, scoll_dir);
    lv_obj_set_scrollbar_mode(screen_tv_card, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(screen_tv_card, LV_OPA_0, 0);
    for(u8 i = 0; i<MAX_PAGE; i++) {
        mpage[i] = lv_obj_create(screen_tv_card);
        lv_obj_remove_style_all(mpage[i]);
        lv_obj_set_size(mpage[i], 320, 172);
    }
    lv_obj_update_snap(screen_tv_card, LV_ANIM_ON);
    lv_obj_add_flag(screen_tv_card, LV_OBJ_FLAG_SCROLL_ONE);
    lv_obj_add_flag(screen_tv_card, LV_OBJ_FLAG_SCROLL_MOMENTUM);
    lv_obj_scroll_to_view(lv_obj_get_child(screen_tv_card, 0), 0);
    lv_event_t _event={0};
    _event.target = screen_tv_card;
    _event.code   = LV_EVENT_SCROLL_END;
    obj_event(&_event);
    lv_obj_add_event_cb(screen_tv_card, obj_event, LV_EVENT_ALL, 0);
    return screen_tv_card;
}
    
lv_obj_t * jl_tileview_add_tile(lv_obj_t * tv, uint8_t col_id, uint8_t row_id, lv_dir_t dir){
    int index = 0;
    if(flex_dir == LV_FLEX_FLOW_ROW){
        index = col_id;
    }else if(flex_dir == LV_FLEX_FLOW_COLUMN){
        index = row_id;
    } else return NULL;

    if(index < lv_obj_get_child_cnt(tv)){
        return lv_obj_get_child(tv, index);
    } else {
        printf(">>>>>>>>>>>>>PAGE NUM OVER ERROR: now %d MAX %d<<<<<<<<<<<<<<", index, MAX_PAGE);
        os_time_dly(1);
        ASSERT(0);
        return NULL;
    }
}

static void obj_event (lv_event_t * event){

    lv_event_code_t code = lv_event_get_code(event);
    lv_obj_t * obj = lv_event_get_target(event);

    if(code == LV_EVENT_SCROLL_END) {
        lv_event_send(obj, LV_EVENT_VALUE_CHANGED, NULL);
        lv_indev_t * indev = lv_indev_get_act();
        if(indev && indev->proc.state == LV_INDEV_STATE_PRESSED) {
            return;
        }

        lv_coord_t w = lv_obj_get_content_width(obj);
        lv_coord_t h = lv_obj_get_content_height(obj);

        lv_point_t scroll_end;
        lv_obj_get_scroll_end(obj, &scroll_end);
        lv_coord_t left = scroll_end.x;
        lv_coord_t top = scroll_end.y;

        lv_coord_t tx = ((left + (w / 2)) / w) * w;
        lv_coord_t ty = ((top + (h / 2)) / h) * h;

        lv_obj_t*head = NULL;
        lv_obj_t*tail = NULL;
        lv_obj_t*now  = NULL;

        uint32_t i;
        for(i = 0; i < lv_obj_get_child_cnt(obj); i++) {
            lv_obj_t * tile_obj = lv_obj_get_child(obj, i);
            lv_coord_t x = lv_obj_get_x(tile_obj);
            lv_coord_t y = lv_obj_get_y(tile_obj);
        
            if(i==0)head = tile_obj;
            if(i==lv_obj_get_child_cnt(obj)-1)tail = tile_obj;

            if(x == tx && y == ty && (tile_obj->coords.x1 == 0)) {
                now = tile_obj;

            }

        }

        int n = 0;
        for(n=0;n<lv_obj_get_child_cnt(obj);n++){
            if(mpage[n] == now){
                printf("NOW PAGE ID: %d\n", n);
                now_id = n;
                break;
            }
        }

        if(!head || !tail){
            return;
        }

        if(now == tail){
            lv_obj_move_to_index(head, -1);  //第一个移到后景
            lv_obj_scroll_to_view(now, 0); //切到当前显示的
            lv_obj_invalidate(obj);
        }

        if(now == head){
            lv_obj_move_to_index(tail, 0);  //最后移到前景
            lv_obj_scroll_to_view(now, 0); //切到当前显示的    
            lv_obj_invalidate(obj);            
        }
    }
}

void jl_obj_set_tile(lv_obj_t * tv, lv_obj_t * tile_obj, lv_anim_enable_t anim_en){
    lv_obj_scroll_to_view(tile_obj, anim_en); //切到当前显示的
    if(!anim_en){
        lv_event_t _event={0};
        _event.target = tv;
        _event.code   = LV_EVENT_SCROLL_END;
        obj_event(&_event);
    }
}

void jl_obj_set_tile_id(lv_obj_t * tv, uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en){
    u8 index = 0;
    if(flex_dir == LV_FLEX_FLOW_ROW){
        index = col_id;
    }else if(flex_dir == LV_FLEX_FLOW_COLUMN){
        index = row_id;
    } else return;

    if(index < lv_obj_get_child_cnt(tv)){
        lv_obj_t * targe =  lv_obj_get_child(tv, index);
        jl_obj_set_tile(tv, targe, anim_en);
    }
}

lv_obj_t * jl_tileview_get_tile_act(lv_obj_t * obj){
    lv_coord_t w = lv_obj_get_content_width(obj);
    lv_coord_t h = lv_obj_get_content_height(obj);

    lv_point_t scroll_end;
    lv_obj_get_scroll_end(obj, &scroll_end);
    lv_coord_t left = scroll_end.x;
    lv_coord_t top = scroll_end.y;

    lv_coord_t tx = ((left + (w / 2)) / w) * w;
    lv_coord_t ty = ((top + (h / 2)) / h) * h;

    lv_dir_t dir = LV_DIR_ALL;
    uint32_t i;
    for(i = 0; i < lv_obj_get_child_cnt(obj); i++) {
        lv_obj_t * tile_obj = lv_obj_get_child(obj, i);
        lv_coord_t x = lv_obj_get_x(tile_obj);
        lv_coord_t y = lv_obj_get_y(tile_obj);
        if(x == tx && y == ty) {
            return tile_obj;
            break;
        }
    }

    return NULL;
}