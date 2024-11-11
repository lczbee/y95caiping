#include "lv_demo_screen_loop.h"
#include "screen_loop_manager/page_adapter.h"
#include "usr_pic_index.h"
#include "widgets_init.h"
#include "custom.h"

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#else
#endif

static void PageManagerInit(void);
static void screen_loop_init();
static void screen_loop_deinit();

void CreateBackgroud(enum BackGroundMode Mode, lv_obj_t* background);

/***********************************************页面顺序*****************************************************/
/**
 * 1.screen_music                   蓝牙音乐播放&本地音乐播放
 * 2.screen_volume                  音量控制
 * 3.screen_anc                     降噪
 * 4.screen_equalizer               eq
 * 5.screen_alarm                   闹钟提醒
 * 6.screen_brightness              亮度等级控制
 * 7.screen_language                语言选择
 * 8.screen_wallpaper               锁屏壁纸选择
 * 9.screen_findmy                  查找我的耳机
 * 10.screen_light                  手电筒灯光
 * 11.screen_time                   时间设置
 * 12.screen_tiktok                 抖音控制
 * 13.screen_snap                   拍照
*/
/***********************************************页面顺序*****************************************************/
PageTypeHandle screen_music;
PageTypeHandle screen_volume;
PageTypeHandle screen_anc;
PageTypeHandle screen_equalizer;
PageTypeHandle screen_alarm;
PageTypeHandle screen_brightness;
PageTypeHandle screen_language;
PageTypeHandle screen_wallpaper;
PageTypeHandle screen_squelch;
PageTypeHandle screen_findmy;
PageTypeHandle screen_light;
PageTypeHandle screen_time;
PageTypeHandle screen_tiktok;
PageTypeHandle screen_snap;
PageTypeHandle screen_product_test;
PageTypeHandle screen_pc_mode;
PageTypeHandle screen_menu;


static void screen_loop_init()
{
    //必须存在该接口
}

static void screen_loop_deinit()
{
    //必须存在该接口
}

static void screen_loop_load()
{
    lv_scr_load(PM_GetObj());
}

void screen_loop_refresh()
{
    screen_equalizer_refresh();


    screen_findmy_refresh();
    screen_light_refresh();
    screen_language_refresh();
    screen_brightness_refresh();
    screen_wallpaper_refresh();


    screen_music_refresh();
    screen_anc_refresh();


    screen_time_refresh();


    status_bar_top_refresh();
    status_bar_bottom_refresh();
    screen_snap_refresh();
    screen_tiktok_refresh();


    screen_alarm_refresh();


    screen_volume_refresh();
    screen_pc_mode_refresh();
    
	//全屏刷新,确保DISABLE状态能够刷新
	lv_obj_invalidate(lv_scr_act()); 
}

void screen_loop_enter()
{
    // 初始化页面管理器
    PageManagerInit();


    
    screen_list_add(screen_loop_init, screen_loop_deinit, screen_loop_load, screen_loop_refresh, SCREEN_PRIO_LOOP);
}

extern void PM_EnterPage(PageTypeHandle* Page); 

void screen_loop_enter_page_by_id(u8 id)
{
    switch (id)
    {
    case ID_SCREEN_MUSIC:
        PM_EnterPage(&screen_music);
        // PM_PageMove(PageDown);
        // AnimToPage(PageDown, 172);
        break;
    case ID_SCREEN_VOLUME:
        PM_EnterPage(&screen_volume);
        break;
    case ID_SCREEN_ANC:
        PM_EnterPage(&screen_anc);
        break;
    case ID_SCREEN_EQUALIZER:
        PM_EnterPage(&screen_equalizer);
        break;
    case ID_SCREEN_ALARM:
        PM_EnterPage(&screen_alarm);
        break;
    case ID_SCREEN_BRIGHTNESS:
        PM_EnterPage(&screen_brightness);
        break;
    case ID_SCREEN_LANGUAGE:
        PM_EnterPage(&screen_language);
        break;
    case ID_SCREEN_WALLPAPER:
        PM_EnterPage(&screen_wallpaper);
        break;
    case ID_SCREEN_FINDMY:
        PM_EnterPage(&screen_findmy);
        break;
    case ID_SCREEN_LIGHT:
        PM_EnterPage(&screen_light);
        break;
    case ID_SCREEN_TIME:
        PM_EnterPage(&screen_time);
        break;
    case ID_SCREEN_TIKTOK:
        PM_EnterPage(&screen_tiktok);
        break;
    case ID_SCREEN_SNAP:
        PM_EnterPage(&screen_snap);
        break;
    case ID_SCREEN_PC_MODE:
        PM_EnterPage(&screen_pc_mode);
        break;
    
    default:
        break;
    }
    
    screen_loop_refresh();
    lv_upadate_status_bar_bottom_by_id(id);
}

static void PageManagerInit(void)
{
    // 初始化页面管理器主体
    PM_Init();

    // 初始化背景
    CreateBackgroud(NONE, PM_GetBackGroudObj());

	// 初始化上下状态栏
#if PAGE_MOVE_COVER_MODE
    lv_status_bar_top_init(PM_GetObj());
    lv_status_bar_bottom_init(PM_GetObj());
    enum MoveMode cur_move_mode = LOAD_ANIM_OVER;
#else
    lv_status_bar_top_init(PM_GetBackGroudObj() ); // PM_GetBackGroudObj()
    lv_status_bar_bottom_init(PM_GetBackGroudObj() ); // PM_GetBackGroudObj()
    enum MoveMode cur_move_mode = LOAD_ANIM_MOVE;
#endif

    // 创建页面关系
    PM_AddPage(&screen_music, init_screen_music, deinit_screen_music, ID_SCREEN_MUSIC, LAYER_BOTTOM);
    PM_AddPage(&screen_volume, init_screen_volume, deinit_screen_volume, ID_SCREEN_VOLUME, LAYER_BOTTOM);
    PM_AddPage(&screen_anc, init_screen_anc, deinit_screen_anc, ID_SCREEN_ANC, LAYER_BOTTOM);
    PM_AddPage(&screen_equalizer, init_screen_equalizer, deinit_screen_equalizer, ID_SCREEN_EQUALIZER, LAYER_BOTTOM);


    PM_AddPage(&screen_alarm, init_screen_alarm, deinit_screen_alarm, ID_SCREEN_ALARM, LAYER_BOTTOM);
    PM_AddPage(&screen_brightness, init_screen_brightness, deinit_screen_brightness, ID_SCREEN_BRIGHTNESS, LAYER_BOTTOM);
    PM_AddPage(&screen_language, init_screen_language, deinit_screen_language, ID_SCREEN_LANGUAGE, LAYER_BOTTOM);
    PM_AddPage(&screen_wallpaper, init_screen_wallpaper, deinit_screen_wallpaper, ID_SCREEN_WALLPAPER, LAYER_BOTTOM);
    PM_AddPage(&screen_findmy, init_screen_findmy, deinit_screen_findmy, ID_SCREEN_FINDMY, LAYER_BOTTOM);
    PM_AddPage(&screen_light, init_screen_light, deinit_screen_light, ID_SCREEN_LIGHT, LAYER_BOTTOM);
    PM_AddPage(&screen_time, init_screen_time, deinit_screen_time, ID_SCREEN_TIME, LAYER_BOTTOM);    


    PM_AddPage(&screen_tiktok, init_screen_tiktok, deinit_screen_tiktok, ID_SCREEN_TIKTOK, LAYER_BOTTOM);
    PM_AddPage(&screen_snap, init_screen_snap, deinit_screen_snap, ID_SCREEN_SNAP, LAYER_BOTTOM);
    PM_AddPage(&screen_menu, init_screen_menu, deinit_screen_menu, ID_SCREEN_MENU, LAYER_MIDDLE);




    PM_SetPublicDown(&screen_menu);

    // screen_snap <- screen_music -> screen_volume
    //                      |
    //                screen_pc_mode
    PM_SetPageMoveMode(&screen_music, PageLeft, &screen_snap, cur_move_mode);
    PM_SetPageMoveMode(&screen_music, PageRight, &screen_volume, cur_move_mode);
    PM_SetPageMoveMode(&screen_music, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // PM_SetPageMoveMode(&screen_music, PageDown, &screen_pc_mode, LOAD_ANIM_OVER);

    //                 screen_music
    //                      |
    //                screen_pc_mode
    PM_SetPageMoveMode(&screen_menu, PageUp, &screen_music, LOAD_ANIM_LEAVE);
    // PM_SetPageMoveMode(&screen_pc_mode, PageUp, &screen_music, LOAD_ANIM_LEAVE);

    // screen_music <- screen_volume -> screen_anc
    //                      |
    //                screen_pc_mode
    PM_SetPageMoveMode(&screen_volume, PageLeft, &screen_music, cur_move_mode);
    PM_SetPageMoveMode(&screen_volume, PageRight, &screen_anc, cur_move_mode);
    PM_SetPageMoveMode(&screen_volume, PageDown, &screen_menu, LOAD_ANIM_OVER);

    // screen_volume <- screen_anc -> screen_equalizer
    //                      |
    //                screen_pc_mode
    PM_SetPageMoveMode(&screen_anc, PageLeft, &screen_volume, cur_move_mode);
    PM_SetPageMoveMode(&screen_anc, PageRight, &screen_equalizer, cur_move_mode);
    PM_SetPageMoveMode(&screen_anc, PageDown, &screen_menu, LOAD_ANIM_OVER);

    // screen_anc <- screen_equalizer -> screen_alarm
    PM_SetPageMoveMode(&screen_equalizer, PageLeft, &screen_anc, cur_move_mode);
    PM_SetPageMoveMode(&screen_equalizer, PageRight, &screen_alarm, cur_move_mode);
    PM_SetPageMoveMode(&screen_equalizer, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_equalizer <- screen_alarm -> screen_brightness
    PM_SetPageMoveMode(&screen_alarm, PageLeft, &screen_equalizer, cur_move_mode);
    PM_SetPageMoveMode(&screen_alarm, PageRight, &screen_brightness, cur_move_mode);
    PM_SetPageMoveMode(&screen_alarm, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_alarm <- screen_brightness -> screen_language
    PM_SetPageMoveMode(&screen_brightness, PageLeft, &screen_alarm, cur_move_mode);
    PM_SetPageMoveMode(&screen_brightness, PageRight, &screen_language, cur_move_mode);
    PM_SetPageMoveMode(&screen_brightness, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_brightness <- screen_language -> screen_wallpaper
    PM_SetPageMoveMode(&screen_language, PageLeft, &screen_brightness, cur_move_mode);
    PM_SetPageMoveMode(&screen_language, PageRight, &screen_wallpaper, cur_move_mode);
    PM_SetPageMoveMode(&screen_language, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_language <- screen_wallpaper -> screen_findmy
    PM_SetPageMoveMode(&screen_wallpaper, PageLeft, &screen_language, cur_move_mode);
    PM_SetPageMoveMode(&screen_wallpaper, PageRight, &screen_findmy, cur_move_mode);
    PM_SetPageMoveMode(&screen_wallpaper, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_wallpaper <- screen_findmy -> screen_light
    PM_SetPageMoveMode(&screen_findmy, PageLeft, &screen_wallpaper, cur_move_mode);
    PM_SetPageMoveMode(&screen_findmy, PageRight, &screen_light, cur_move_mode);
    PM_SetPageMoveMode(&screen_findmy, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_findmy <- screen_light -> screen_time
    PM_SetPageMoveMode(&screen_light, PageLeft, &screen_findmy, cur_move_mode);
    PM_SetPageMoveMode(&screen_light, PageRight, &screen_time, cur_move_mode);
    PM_SetPageMoveMode(&screen_light, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_light <- screen_time -> screen_tiktok
    PM_SetPageMoveMode(&screen_time, PageLeft, &screen_light, cur_move_mode);
    PM_SetPageMoveMode(&screen_time, PageRight, &screen_tiktok, cur_move_mode);
    PM_SetPageMoveMode(&screen_time, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_time <- screen_tiktok -> screen_snap
    PM_SetPageMoveMode(&screen_tiktok, PageLeft, &screen_time, cur_move_mode);
    PM_SetPageMoveMode(&screen_tiktok, PageRight, &screen_snap, cur_move_mode);
    PM_SetPageMoveMode(&screen_tiktok, PageDown, &screen_menu, LOAD_ANIM_OVER);
    // screen_tiktok <- screen_snap -> screen_music
    PM_SetPageMoveMode(&screen_snap, PageLeft, &screen_tiktok, cur_move_mode);
    PM_SetPageMoveMode(&screen_snap, PageRight, &screen_music, cur_move_mode);
    PM_SetPageMoveMode(&screen_snap, PageDown, &screen_menu, LOAD_ANIM_OVER);

/*
    // screen_anc <- screen_equalizer -> screen_tiktok
    //                      |
    //                screen_pc_mode
    PM_SetPageMoveMode(&screen_equalizer, PageLeft, &screen_anc, cur_move_mode);
    PM_SetPageMoveMode(&screen_equalizer, PageRight, &screen_tiktok, cur_move_mode);
    PM_SetPageMoveMode(&screen_equalizer, PageDown, &screen_menu, LOAD_ANIM_OVER);

    // screen_equalizer <- screen_tiktok -> screen_snap
    //                      |
    //                screen_pc_mode
    PM_SetPageMoveMode(&screen_tiktok, PageLeft, &screen_equalizer, cur_move_mode);
    PM_SetPageMoveMode(&screen_tiktok, PageRight, &screen_snap, cur_move_mode);
    PM_SetPageMoveMode(&screen_tiktok, PageDown, &screen_menu, LOAD_ANIM_OVER);

    // screen_tiktok <- screen_snap -> screen_music
    //                      |
    //                screen_pc_mode
    PM_SetPageMoveMode(&screen_snap, PageLeft, &screen_tiktok, cur_move_mode);
    PM_SetPageMoveMode(&screen_snap, PageRight, &screen_music, cur_move_mode);
    PM_SetPageMoveMode(&screen_snap, PageDown, &screen_menu, LOAD_ANIM_OVER);
*/

    
    // 页面管理器开始
    PM_Start(&screen_music);
}

static void draw_event_cb(lv_event_t * event);
static void add_data(lv_timer_t * timer);
void CreateBackgroud(enum BackGroundMode Mode, lv_obj_t* background)
{
    switch(Mode)
    {
        case NONE:{
            lv_obj_set_style_bg_color(background, lv_color_black(), 0);
        }break;

        case Mode1:{
            printf("create bg anim");
            lv_obj_t *BgAnim = lv_animimg_create(background);
            lv_animimg_set_src(BgAnim, (const void **) screen_loop_img_bg_imgs, 1);
            lv_animimg_set_duration(BgAnim, 1000);
#if EXTERN_ANIMING
            usr_update_animing(BgAnim, "BG");
#endif
            lv_animimg_set_repeat_count(BgAnim, 1);
            lv_animimg_start(BgAnim);
            lv_obj_set_pos(BgAnim, 0, 0);
            lv_obj_set_size(BgAnim, 320, 172);
            lv_obj_move_background(BgAnim);

            // lv_img_t* BgImg = lv_img_create(background);
            // lv_obj_set_style_radius(BgImg, 0, 0);
            // lv_obj_set_style_pad_all(BgImg, 0, 0);
            // lv_obj_set_style_border_width(BgImg, 0, 0);
            // lv_img_set_src(BgImg, "F:/bg.bin"); // 配置背景图
            // lv_obj_move_background(BgImg);
        }break;

        case Mode2:{
            // 显示点的数量
            #define PointNum    80
            lv_obj_t * chart = lv_chart_create(background);
            lv_obj_set_style_radius(chart, 0, 0);
            lv_obj_set_style_pad_all(chart, 0, 0);
            lv_obj_set_style_border_width(chart, 0, 0);
            lv_obj_set_size(chart, LV_PCT(100), LV_PCT(100));
            lv_obj_align(chart, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_style_bg_color(chart, lv_color_black(), 0);
            lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

            lv_obj_set_style_line_width(chart, 0, LV_PART_ITEMS);
            lv_chart_set_type(chart, LV_CHART_TYPE_SCATTER);

            lv_chart_set_div_line_count(chart, 0, 0);
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_X, 0, (WIDTH * 10));
            lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, (HEIGHT* 10));

            lv_chart_set_point_count(chart, PointNum);

            lv_chart_series_t * ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
            for(uint32_t i = 0; i < PointNum; i++) {
                lv_chart_set_next_value2(chart, lv_chart_get_series_next(chart, NULL), lv_rand(0,(WIDTH * 10)), lv_rand(0,(HEIGHT* 10)));
            }
            lv_timer_create(add_data, 50, chart);
        }break;

        case Mode3:
            lv_obj_t * bg = lv_img_create(background);
            lv_img_set_src(bg, "d:storage/virfat_flash/C/TEST1.RES");
            low_rle_anim_start(bg, 0, 0, NULL, NULL);
            break;
    }
}

static void draw_event_cb(lv_event_t * event)
{
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(event);
    if(dsc->part == LV_PART_ITEMS) {
        lv_obj_t * obj = lv_event_get_target(event);
        lv_chart_series_t * ser = lv_chart_get_series_next(obj, NULL);
        uint32_t cnt = lv_chart_get_point_count(obj);
        /*Make older value more transparent*/
        dsc->rect_dsc->bg_opa = (LV_OPA_COVER *  dsc->id) / (cnt - 1);

        /*Make smaller values blue, higher values red*/
        lv_coord_t * x_array = lv_chart_get_x_array(obj, ser);
        lv_coord_t * y_array = lv_chart_get_y_array(obj, ser);
        /*dsc->id is the tells drawing order, but we need the ID of the point being drawn.*/
        uint32_t start_point = lv_chart_get_x_start_point(obj, ser);
        uint32_t p_act = (start_point + dsc->id) % cnt; /*Consider start point to get the index of the array*/
        lv_opa_t x_opa = (x_array[p_act] * LV_OPA_100) / (WIDTH * 10);
        lv_opa_t y_opa = (y_array[p_act] * LV_OPA_100) / (HEIGHT* 10);

        dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_RED),
                                                lv_palette_main(LV_PALETTE_BLUE),
                                                x_opa + y_opa);
    }
}

static void add_data(lv_timer_t * timer)
{
    LV_UNUSED(timer);
    lv_obj_t * obj = timer->user_data;
    lv_chart_set_next_value2(obj, lv_chart_get_series_next(obj, NULL), lv_rand(0, (WIDTH * 10)), lv_rand(0, (HEIGHT* 10)));
}


bool screen_scrolled = false;
void screen_scroll_check(lv_event_t *e) {

    lv_event_code_t code = lv_event_get_code(e);

    static lv_point_t start_point;
    lv_point_t current_point;

    switch(code) {
        case LV_EVENT_PRESSED:
            // 记录第一次触摸的位置
            lv_indev_get_point(lv_indev_get_act(), &start_point);
            break;
        case LV_EVENT_PRESSING:
            // 获取当前触摸的位置
            lv_indev_get_point(lv_indev_get_act(), &current_point);

            // 计算欧几里得距离
            u32 dx = current_point.x - start_point.x; // x轴上的差值
            u32 dy = current_point.y - start_point.y; // y轴上的差值
            u32 distance = (u32)sqrt(dx * dx + dy * dy);

            // 与 distance 比较的是阈值，用来判断用户的触摸移动足够被认为是滑动，可以根据需求来设置
            screen_scrolled = (distance > 10) ? true : false;

            break;
        case LV_EVENT_PRESS_LOST:
        case LV_EVENT_RELEASED:
            // 用户停止触摸屏幕
            break;
        default:
            break;
    }
}







