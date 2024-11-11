#include "custom.h"
#include "usr_pic_index.h"
#include "lv_demo_time/time_api.h"

/*
 * @简要说明：
 * ### 本demo支持弧形菜单、循环显示、记忆功能、缩放功能单独开关 ###
 * 用户需要配置图标属性，布局属性，圆弧属性，缩放配置，循环配置，记忆配置和逻辑相关配置
 * 
 * 其中：
 * @ 图标属性：
 *  1.图标宽高
 *  2.图标数量，按照图标图片数量来填即可
 *  3.图标间隔，若觉得图标x轴方向上的距离过近，可以稍微调大一些
 *  4.图标居中，若开启，图标则默认在布局y轴中心
 *  5.仅居中图标支持页面跳转，若开启MENU_ICON_ONLY_CENTER_CLICKABLE，
 *    则点击除中心图标外的图标均无法进行页面跳转
 * 
 * @ 布局属性：
 *  1.布局宽高
 *  2.开启图片背景
 *  3.菜单透明度变化开关, 需要注意的是MENU_OPA_EN在MENU_CONT_BG_EN为1时无效
 * 
 * @ 圆弧属性
 *  1.圆弧功能使能
 *  2.圆弧半径，MENU_ARC_RADIUS建议设置为比布局高度小一点，以完整显示半圆
 *  3.圆弧圆心y轴偏移，若想把圆弧菜单整体向上或下平移，可以调节该宏
 * 
 * @ 缩放配置
 *  1.缩放使能，开启后边缘图标会变小
 * 
 * @ 循环配置
 *  1.循环使能，开启后在SCROLL_END事件时会重新调整控件链表，来实现无限循环的效果
 *  2.循环项数，若MENU_CIRCLE_ICON_NUM比较小，在惯性还没结束时已经到图标列表边缘了，
 *  此时还没来得及触发SCROLL_END事件，则循环菜单会出现一瞬间断开，再续上的现象，此时
 *  可以适当加大MENU_CIRCLE_ICON_NUM的值，来防止过快到达图标列表边缘，不会影响图标实际
 *  数量，但会增加开销，需要用户自己权衡，需要注意的是，该宏的值必须为MENU_ICON_REAL_NUM
 *  的整数倍
 * 
 * @ 记忆配置
 *  1.记忆使能，开启后页面释放后再初始化，仍然是释放前的图标居中，否则释放后始终为第一个图标居中
 * 
 * @ 逻辑相关配置
 *  1.菜单信息表（menu_icon_info）
 *  icon_id为图标的ID，按顺序从0~N即可
 *  icon_src为图标的图片资源，默认采用资源ID方式，也可以使用路径方式，如"F:/CHI1.bin"
 *  icon_cb为点击图标后的回调函数，默认为页面跳转函数
 * 
 * #由于使用了lvgl底层的滚动逻辑，故惯性之类的需要调整lvgl底层的参数，若想松手后滚动持续时间
 *  长一些，可以调整lv_hal_indev.h里面的LV_INDEV_DEF_SCROLL_THROW，该宏越大，滚动越快停下来
*/

bool screen_menu_loaded;

#if LV_DEMO_MENU_EN

/************************************************重要参数***************************************************/

/****************************用户配置，用户可以修改********************************/

/***************debug*****************/
// 图标改为id，用于调试
#define MENU_ICON_ID_SHOW_TEST      (0)
// log debug宏
#define MENU_DEBUG_EN               (1)

#if MENU_DEBUG_EN
#define MENU_DEBUG   b_printf
#else
#define MENU_DEBUG(...)
#endif
/***************debug*****************/


/**************图标属性****************/
// 菜单图标宽度
#define MENU_ICON_W                         (90)
// 菜单图标高度
#define MENU_ICON_H                         (90)
// 菜单图标x轴间隙
#define MENU_ICON_INTERVAL                  (10)
// 菜单图标真实数量
#define MENU_ICON_REAL_NUM                  (15)
// 菜单图标y轴居中
#define MENU_ICON_Y_CENTER_EN                (1)
// 菜单图标中仅中心图标支持跳转
#define MENU_ICON_ONLY_CENTER_CLICKABLE      (0)
/**************图标属性****************/


/**************布局属性****************/
// 菜单布局宽度
#define MENU_CONT_W             (320)
// 菜单布局高度
#define MENU_CONT_H             (172)
// 上下拉时菜单透明度变化开关
#define MENU_OPA_EN             (1)

// 菜单布局使用背景图片使能(以下两个功能只能2选1)
#define MENU_CONT_BG_EN         (0)
#define BG_IMG_EFFECT           (0)

#if BG_IMG_EFFECT
#define MENU_CONT_BG_EN 0
#endif

#if BG_IMG_EFFECT
#define MENU_CONT_BG_SRC        "d:storage/virfat_flash/C/TEST1.RES"
#endif

#if MENU_CONT_BG_EN
// 背景图路径
#define MENU_CONT_BG_SRC        ("F:/bg.bin")
#undef MENU_OPA_EN
#define MENU_OPA_EN             (0)
#endif
/**************布局属性****************/


/**************圆弧属性****************/
// 圆弧菜单使能
#define MENU_ARC_EN             (1)

#if MENU_ARC_EN
// 圆弧半径
#define MENU_ARC_RADIUS         (160)
// 圆弧圆心y轴上的偏移，控制圆弧整体上下位置
#define MENU_ARC_Y_OFFSET       (0)
#endif
/**************圆弧属性****************/


/**************缩放配置****************/
// 图标缩放使能
#define MENU_ZOOM_EN            (1)
/**************缩放配置****************/


/**************循环配置****************/
// 循环菜单使能
#define MENU_CIRCLE_EN          (1)

#if MENU_CIRCLE_EN
// 循环菜单项数，建议稍微大一些，防止列表边界出现卡顿，但数量太多会消耗ram
// 以及导致运算速度变慢
#define MENU_CIRCLE_ICON_NUM    (2 * MENU_ICON_REAL_NUM)
#endif
/**************循环配置****************/


/**************记忆配置****************/
#define MENU_ICON_MEMORY_EN     (1)
/**************记忆配置****************/

/****************************用户配置，用户可以修改********************************/

/*-----------------------------------------------------------------------------------------*/

/**************************系统配置，用户不需要修改********************************/

/**************滚动控制****************/
#define MENU_SCROLL_CONTROL  ((MENU_ZOOM_EN << 1) | (MENU_ARC_EN))

// 弧形菜单缩放
#define MENU_ARC_ZOOM       (0x03)
// 水平菜单缩放
#define MENU_HOR_ZOOM       (0x02)
// 弧形菜单不缩放
#define MENU_ARC_NON_ZOOM   (0x01)
// 水平菜单不缩放
#define MENU_HOR_NON_ZOOM   (0x00)
/**************滚动控制****************/


/************图标数量控制**************/
// 图标索引数量
#define MENU_ICON_INDEX_NUM     MENU_ICON_REAL_NUM

#if MENU_CIRCLE_EN
#define MENU_ICON_SHOW_NUM      MENU_CIRCLE_ICON_NUM
#else
#define MENU_ICON_SHOW_NUM      MENU_ICON_INDEX_NUM
#endif
/************图标数量控制**************/


/************图标记忆控制**************/
#if MENU_ICON_MEMORY_EN

#if MENU_CIRCLE_EN
// 图标循环记忆
#define MENU_CIRCLE_MEMORY_CONTROL      1
#define MENU_NON_CIRCLE_MEMORY_CONTROL  0
#else
// 图标非循环记忆
#define MENU_CIRCLE_MEMORY_CONTROL      0
#define MENU_NON_CIRCLE_MEMORY_CONTROL  1
#endif

#endif
/************图标记忆控制**************/

/**************************系统配置，用户不需要修改********************************/

/************************************************重要参数***************************************************/


/**********************************************逻辑相关配置*************************************************/

/*************页面回调声明************/
void screen_loop_music_enter();
void screen_loop_volume_enter();
void screen_loop_anc_enter();
void screen_loop_equalizer_enter();
void screen_loop_alarm_enter();
void screen_loop_brightness_enter();
void screen_loop_language_enter();
void screen_loop_wallpaper_enter();
void screen_loop_findmy_enter();
void screen_loop_light_enter();
void screen_loop_time_enter();
void screen_loop_tiktokk_enter();
void screen_loop_snap_enter();
void screen_loop_wooden_fish_enter();
void screen_loop_weather_enter();
void screen_loop_setting_enter();
/*************页面回调声明************/

struct icon_info_t menu_icon_info[MENU_ICON_INDEX_NUM] = {
    {
        .icon_id = 0,
        .icon_src = ID_menu_icon_music,
        .icon_cb = screen_loop_music_enter,
        .icon_name = "音乐",
        // .icon_name = "music",
    },
    {
        .icon_id = 1,
        .icon_src = ID_menu_icon_volume,
        .icon_cb = screen_loop_volume_enter,
        .icon_name = "音量",
        // .icon_name = "volume",
    },
    {
        .icon_id = 2,
        .icon_src = ID_menu_icon_anc,
        .icon_cb = screen_loop_anc_enter,
        .icon_name = "降噪",
        // .icon_name = "anc",
    },
    {
        .icon_id = 3,
        .icon_src = ID_menu_icon_eq,
        .icon_cb = screen_loop_equalizer_enter,
        .icon_name = "均衡",
        // .icon_name = "equalizer",
    },
    {
        .icon_id = 4,
        .icon_src = ID_menu_icon_clock,
        .icon_cb = screen_loop_alarm_enter,
        .icon_name = "闹钟",
        // .icon_name = "alarm",
    },
    {
        .icon_id = 5,
        .icon_src = ID_menu_icon_brightness,
        .icon_cb = screen_loop_brightness_enter,
        .icon_name = "亮度",
        // .icon_name = "brightness",
    },
    {
        .icon_id = 6,
        .icon_src = ID_menu_icon_language,
        .icon_cb = screen_loop_language_enter,
        .icon_name = "语言",
        // .icon_name = "language",
    },
    {
        .icon_id = 7,
        .icon_src = ID_menu_icon_wallpaper,
        .icon_cb = screen_loop_wallpaper_enter,
        .icon_name = "壁纸",
        // .icon_name = "wallpaper",
    },
    {
        .icon_id = 8,
        .icon_src = ID_menu_icon_search,
        .icon_cb = screen_loop_findmy_enter,
        .icon_name = "查找耳机",
        // .icon_name = "findmy",
    },
    {
        .icon_id = 9,
        .icon_src = ID_menu_icon_flashlight,
        .icon_cb = screen_loop_light_enter,
        .icon_name = "灯光",
        // .icon_name = "light",
    },
    {
        .icon_id = 10,
        .icon_src = ID_menu_icon_time,
        .icon_cb = screen_loop_time_enter,
        .icon_name = "时钟",
        // .icon_name = "time",
    },
    {
        .icon_id = 11,
        .icon_src = ID_menu_icon_tiktok,
        .icon_cb = screen_loop_tiktokk_enter,
        .icon_name = "抖音",
        // .icon_name = "tiktok",
    },
    {
        .icon_id = 12,
        .icon_src = ID_menu_icon_photograph,
        .icon_cb = screen_loop_snap_enter,
        .icon_name = "拍照",
        // .icon_name = "snap",
    },
    {
        .icon_id = 13,
        .icon_src = ID_menu_icon_muyu,
        .icon_cb = screen_loop_wooden_fish_enter,
        .icon_name = "木鱼",
        // .icon_name = "wooden_fish",
    },
    // {
    //     .icon_id = 14,
    //     .icon_src = ID_menu_icon_weather,
    //     .icon_cb = screen_loop_weather_enter,
    //     .icon_name = "天气",
    //     // .icon_name = "weather",
    // },
    {
        .icon_id = 14,
        .icon_src = ID_menu_icon_setting,
        .icon_cb = screen_loop_setting_enter,
        .icon_name = "设置",
        // .icon_name = "weather",
    }
};

static lv_obj_t * menu_text_obj;

/*************页面回调定义************/

void screen_preempt_enter_page_by_id(u8 id)
{
    switch (id)
    {
    case SCREEN_PRIO_MUSIC:
        screen_music_enter();
        break;
    case SCREEN_PRIO_VOLUME:
        screen_volume_enter();
        break;
    case SCREEN_PRIO_ANC:
        screen_anc_enter();
        break;
    case SCREEN_PRIO_EQUALIZER:
        screen_equalizer_enter();
        break;
    case SCREEN_PRIO_ALARM:
        screen_alarm_enter();
        break;
    case SCREEN_PRIO_BRIGHTNESS:
        screen_brightness_enter();
        break;
    case SCREEN_PRIO_LANGUAGE:
        screen_language_enter();
        break;
    case SCREEN_PRIO_WALLPAPER:
        screen_wallpaper_enter();
        break;
    case SCREEN_PRIO_FINDMY:
        screen_findmy_enter();
        break;
    case SCREEN_PRIO_LIGHT:
        screen_light_enter();
        break;
    case SCREEN_PRIO_TIME:
        screen_time_enter();
        break;
    case SCREEN_PRIO_TIKTOK:
        screen_tiktok_enter();
        break;
    case SCREEN_PRIO_SNAP:
        screen_snap_enter();
        break;
    
    default:
        break;
    }
    
    screen_loop_refresh();
    lv_upadate_status_bar_bottom_by_id(id);

}

void screen_loop_music_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_MUSIC);
}
void screen_loop_volume_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_VOLUME);
}
void screen_loop_anc_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_ANC);
}
void screen_loop_equalizer_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_EQUALIZER);
}
void screen_loop_alarm_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_ALARM);
    // screen_preempt_enter_page_by_id(SCREEN_PRIO_ALARM);
}
void screen_loop_brightness_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_BRIGHTNESS);
    // screen_preempt_enter_page_by_id(SCREEN_PRIO_BRIGHTNESS);
}
void screen_loop_language_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_LANGUAGE);
    // screen_preempt_enter_page_by_id(SCREEN_PRIO_LANGUAGE);
}
void screen_loop_wallpaper_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_WALLPAPER);
    // screen_preempt_enter_page_by_id(SCREEN_PRIO_WALLPAPER);
}
void screen_loop_findmy_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_FINDMY);
    // screen_preempt_enter_page_by_id(SCREEN_PRIO_FINDMY);
}
void screen_loop_light_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_LIGHT);
    // screen_preempt_enter_page_by_id(SCREEN_PRIO_LIGHT);
}
void screen_loop_time_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_TIME);
    // screen_preempt_enter_page_by_id(SCREEN_PRIO_TIME);
}
void screen_loop_tiktokk_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_TIKTOK);
}
void screen_loop_snap_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_loop_enter_page_by_id(ID_SCREEN_SNAP);
}
void screen_loop_wooden_fish_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_wooden_fish_enter(SCREEN_PRIO_WOODEN_FISH);
}
void screen_loop_weather_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_weather_enter();
}
void screen_loop_setting_enter()
{
    MENU_DEBUG("[menu] icon_cb: %s", __func__);
    screen_poweroff_enter();
}
/*************页面回调定义************/

/**********************************************逻辑相关配置*************************************************/


/**************************重要全局变量*******************************/
// char *menu_icon_tab[] = {ID_chi1, ID_chi2, ID_chi3, ID_chi4, ID_chi5, ID_chi6, ID_chi7, ID_chi8, ID_chi9, ID_chi10};

// 图标记忆项
int menu_icon_mem = 0;
// 菜单布局句柄
lv_obj_t * menu_cont;
/**************************重要全局变量*******************************/


/**************************重要接口声明*******************************/
static void hor_scroll_event_cb(lv_event_t * e);

static void arc_menu_refresh(lv_event_t * e);

static void hor_menu_zoom_refresh(lv_event_t * e);

static void circle_menu_refresh(lv_event_t * e);

u8 menu_update_icon_memory_id(lv_event_t * e);
/**************************重要接口声明*******************************/

static void test_cont_event_cb(lv_event_t* event)
{
    lv_obj_t* container = lv_event_get_current_target(event);

    //  找到当前的子

    lv_obj_t* btn = NULL;
    int all_chid = lv_obj_get_child_cnt(container);

    for(int i = 0; i < all_chid; i++) {
        lv_obj_t * b = lv_obj_get_child(container, i);
        if(lv_obj_is_visible(b)){
            btn = lv_obj_get_child(container, i+1);
            break;
        }
    }

    if(!btn) return;

    //  差多少补多少，尽量保持居中

    uint32_t mid_btn_index = (all_chid - 1) / 2 - 1;
    uint32_t current_btn_index = lv_obj_get_index(btn);

    r_printf("%d %d", mid_btn_index, current_btn_index);

    lv_area_t child_a;
    lv_obj_get_coords(container, &child_a);
    lv_coord_t cont_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;

    lv_obj_get_coords(btn, &child_a);
    lv_coord_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;

    if (current_btn_index > mid_btn_index)
    {
        for(u8 i = 0; i < current_btn_index-mid_btn_index; i++){
            // lv_obj_move_children_by(container, +lv_area_get_width(&child_a), 0, 0);
            // lv_obj_scroll_by(container, +lv_area_get_width(&child_a), 0, 0);
            lv_obj_move_to_index(lv_obj_get_child(container, 0), -1);
            // _lv_obj_scroll_by_raw(container, +lv_area_get_width(&child_a), 0);
        }
    }
    else if (current_btn_index < mid_btn_index)
    {
        for(u8 i = 0; i < mid_btn_index-current_btn_index; i++){
            // lv_obj_move_children_by(container, -lv_area_get_width(&child_a), 0, 0);
            // lv_obj_scroll_by(container, -lv_area_get_width(&child_a), 0, 0);
            lv_obj_move_to_index(lv_obj_get_child(container, -1), 0);
            // _lv_obj_scroll_by_raw(container, -lv_area_get_width(&child_a), 0);
        }
    }

#if (MENU_SCROLL_CONTROL == MENU_ARC_ZOOM || MENU_SCROLL_CONTROL == MENU_ARC_NON_ZOOM)
    arc_menu_refresh(event);
#elif(MENU_SCROLL_CONTROL == MENU_HOR_ZOOM )
    hor_menu_zoom_refresh(event);
#endif 
}

/**
 * @brief 根据src获取图标信息句柄
 * 
 * @param src 
 * @return struct icon_info_t* 
 */
static struct icon_info_t *menu_get_icon_info_by_src(char *src)
{
    if(!src) {
        MENU_DEBUG("[menu] func: %s, line: %d, src is null", __func__, __LINE__);
        return NULL;
    }

    for(int i = 0; i < MENU_ICON_INDEX_NUM; i++) {
        if(!memcmp(menu_icon_info[i].icon_src, src, strlen(src))) {
            return &menu_icon_info[i];
        }
    }

    MENU_DEBUG("[menu] src %s could not be found!");
    return NULL;
}

/**
 * @brief 更新记忆项
 * 
 * @param e 
 * @return u8 
 */
u8 menu_update_icon_memory_id(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e); // 获取事件的初始对象
    lv_coord_t child_cnt = lv_obj_get_child_cnt(cont); // 获取图标的数量

#if MENU_CIRCLE_MEMORY_CONTROL
    lv_coord_t mid_btn_index = (child_cnt - 1) / 2;    // 中间图标的位置
    lv_obj_t *child = lv_obj_get_child(cont, mid_btn_index);

    char *icon_src = (void *)lv_img_get_src(child);

    struct icon_info_t *icon_info = menu_get_icon_info_by_src(icon_src);

    menu_icon_mem = icon_info->icon_id;

#elif MENU_NON_CIRCLE_MEMORY_CONTROL
    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);                                                   // 获取布局坐标信息
    lv_coord_t cont_x_center = cont_a.x1 + lv_area_get_width(&cont_a) / 2;              // 获取布局y轴的中心坐标

    for (lv_coord_t i = 0; i < child_cnt; i++) {
        lv_obj_t *child = lv_obj_get_child(cont, i);                                    // 通过索引获取图标

        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);
        lv_coord_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;       // 获取图标x轴中心
        
        // 判断图标是否处于布局中心，若处于布局中心则判断为显示中心图标
        if (child_x_center >= cont_x_center - 10 && child_x_center <= cont_x_center + 10)
        {
            // 获取当前图标的索引
            menu_icon_mem = lv_obj_get_child_id(child);
        }
    }
#endif
    MENU_DEBUG("[menu] func: %s, menu_icon_mem: %d, icon_name: %s", __func__, menu_icon_mem, icon_info->icon_name);
    if(icon_info && menu_text_obj){
        if (!lv_obj_is_scrolling(cont))
        {
            lv_label_set_text(menu_text_obj, icon_info->icon_name);
        }
    }
    return menu_icon_mem;

}

/**
 * @brief 循环菜单更新
 * 
 * @param e 
 */
static void circle_menu_refresh(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e); // 获取事件的初始对象
        
    // 判断是否在滚动中 
    if (lv_obj_is_scrolling(cont))
    {
        return;
    }
    lv_coord_t child_cnt = lv_obj_get_child_cnt(cont); // 获取图标的数量
    lv_coord_t mid_btn_index = (child_cnt - 1) / 2;    // 中间图标的位置

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);                                                   // 获取布局坐标信息
    lv_coord_t cont_x_center = cont_a.x1 + lv_area_get_width(&cont_a) / 2;              // 获取布局y轴的中心坐标

    // 遍历图标
    for (lv_coord_t i = 0; i < child_cnt; i++) {
        lv_obj_t *child = lv_obj_get_child(cont, i);                                    // 通过索引获取图标

        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);
        lv_coord_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;       // 获取图标x轴中心
        // MENU_DEBUG("[menu] child_x_center: %d, cont_x_center: %d", child_x_center, cont_x_center);
        
        // 判断图标是否处于布局中心，若处于布局中心则判断为显示中心图标
        if (child_x_center >= cont_x_center - 10 && child_x_center <= cont_x_center + 10)
        {
            // 获取当前图标的索引
            lv_coord_t current_btn_index = lv_obj_get_child_id(child);
            // MENU_DEBUG("current_btn_index: %d", current_btn_index);

            // 计算显示中心图标与索引中心图标的索引差，并通过通过图标在链表上的移动
            // 将显示中心图标移动到索引中心图标的位置
            lv_coord_t move_btn_quantity = LV_ABS(current_btn_index - mid_btn_index);
            for (lv_coord_t j = 0; j < move_btn_quantity; j++)
            {
                if (current_btn_index < mid_btn_index)
                {
                    lv_obj_move_background(lv_obj_get_child(cont, child_cnt - 1));
                    lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);
                }
                if (current_btn_index > mid_btn_index)
                {
                    lv_obj_move_foreground(lv_obj_get_child(cont, 0));
                    lv_obj_scroll_to_view(lv_obj_get_child(cont, mid_btn_index), LV_ANIM_OFF);
                }
            }
            // 保证图标居中显示
            lv_obj_set_style_translate_x(lv_obj_get_child(cont, mid_btn_index), 0, 0);
            break;
        }
    } 
}

/**
 * @brief 水平菜单缩放更新
 * 
 * @param e 
 */
static void hor_menu_zoom_refresh(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);

    lv_area_t cont_a;

    // 获取布局坐标信息
    lv_obj_get_coords(cont, &cont_a);
    // 计算布局x轴中心坐标
    lv_coord_t cont_x_center = cont_a.x1 + lv_area_get_width(&cont_a) / 2;

    lv_coord_t r = MENU_CONT_W / 2;

    // 获取图标数量
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);

    for(uint32_t i = 0; i < child_cnt; i++) {
        // 按顺序获取图标句柄
        lv_obj_t * child = lv_obj_get_child(cont, i);

        lv_area_t child_a;
        // 获取图标坐标信息
        lv_obj_get_coords(child, &child_a);

        // 计算图标x轴中心坐标
        lv_coord_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;

        // 计算图标x轴中心坐标与布局x轴中心坐标距离
        lv_coord_t diff_x = child_x_center - cont_x_center;
        diff_x = LV_ABS(diff_x);

        // 限制diff_x，使diff_x不超过半径
        if(diff_x >= r) {
            diff_x = r;
        }

        // MENU_DEBUG("[menu] diff_x: %d, r: %d", diff_x, r);

        // 规避除零错误
        if(r != 0) {
            // MENU_DEBUG("diff_x / r: %f", (float)diff_x / r);
            // 计算缩放比例
            lv_coord_t zoom = LV_IMG_ZOOM_NONE - LV_IMG_ZOOM_NONE * easeInCirc((float)diff_x / r);
            // 设置缩放系数
            lv_img_set_zoom(child, zoom);
        }
    }
}

#if MENU_ARC_EN
/**
 * @brief 弧形菜单更新
 * 
 * @param e 
 */
static void arc_menu_refresh(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);

    lv_area_t cont_a;

    // 获取布局坐标信息
    lv_obj_get_coords(cont, &cont_a);
    // 计算布局x轴中心坐标
    lv_coord_t cont_x_center = cont_a.x1 + lv_area_get_width(&cont_a) / 2;

    // 配置圆弧半径
    lv_coord_t r = MENU_ARC_RADIUS;
    // 获取图标数量
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);

    int min_x = 2147483647;
    int min_icon_id = 0;

    for(uint32_t i = 0; i < child_cnt; i++) {
        // 按顺序获取图标句柄
        lv_obj_t * child = lv_obj_get_child(cont, i);

        lv_area_t child_a;
        // 获取图标坐标信息
        lv_obj_get_coords(child, &child_a);

        // 计算图标x轴中心坐标
        lv_coord_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;

        // 计算图标x轴中心坐标与布局x轴中心坐标距离
        lv_coord_t diff_x = child_x_center - cont_x_center;
        diff_x = LV_ABS(diff_x);

        if(diff_x < min_x){
            min_x = diff_x;
            min_icon_id = i;
        }

        lv_coord_t y;
        lv_sqrt_res_t res;
        // 限制y，使y的变化值不超过半径
        if(diff_x >= r) {
            y = r;
        } else {
            // 根据勾股定理算出y^2
            lv_coord_t y_sqr = r * r - diff_x * diff_x;
            
            // 使用lvgl内置求根公式算出y值
            lv_sqrt(y_sqr, &res, 0x8000);
            // 计算图标y轴上偏移
            y = r - res.i;
        }

#if (MENU_SCROLL_CONTROL == MENU_ARC_ZOOM)
        // 规避除零错误
        if(r != 0) {
            // 计算图标中心到圆心距离在y轴上的投影值
            lv_coord_t icon_y = (res.i > r) ? (r) : (res.i);
            // 计算缩放比例
            lv_coord_t zoom = LV_IMG_ZOOM_NONE * icon_y / r;
            // MENU_DEBUG("[menu] zoom: %d, icon_y: %d, r: %d, y: %d", zoom, icon_y, r, y);

            // 只设置屏幕内图标缩放系数
            if(y != r) {
                // 设置缩放系数
                lv_img_set_zoom(child, zoom+32);
            }
        }
#endif

        // 设置y轴偏移
        y = y + MENU_ARC_Y_OFFSET;
        
        // 在y轴上对图标移动相应距离，使其贴合圆弧滑动
        lv_obj_set_style_translate_y(child, y, 0);

    }

    static u8 last_min_icon_id = -1;
    if(min_icon_id != last_min_icon_id){
        last_min_icon_id = min_icon_id;
        lv_obj_t *icon = lv_obj_get_child(cont, min_icon_id);
        u32 icon_real_id = lv_obj_get_index(icon);
        char *icon_src = (void *)lv_img_get_src(icon);
        struct icon_info_t *icon_info = menu_get_icon_info_by_src(icon_src);
        if(icon_info && menu_text_obj){
            lv_label_set_text(menu_text_obj, icon_info->icon_name) ;
        }
    }

}

#endif

/**
 * @brief 菜单滚动结束回调
 * 
 * @param e 
 */
static void scroll_end_event(lv_event_t * e)
{
    // 获取事件的事件代码
    if(lv_event_get_code(e) == LV_EVENT_SCROLL_END) 
    {  
#if MENU_CIRCLE_EN
        circle_menu_refresh(e);
#endif
  
#if (MENU_SCROLL_CONTROL == MENU_ARC_ZOOM || MENU_SCROLL_CONTROL == MENU_ARC_NON_ZOOM)
        // 刷新圆弧菜单
        arc_menu_refresh(e);
#elif(MENU_SCROLL_CONTROL == MENU_HOR_ZOOM )
        // 刷新水平菜单
        hor_menu_zoom_refresh(e);
#endif  

#if MENU_ICON_MEMORY_EN
    menu_update_icon_memory_id(e);
#endif
    }
}

#if MENU_SCROLL_CONTROL
/**
 * @brief 水平菜单滚动回调
 * 
 * @param e 
 */
static void hor_scroll_event_cb(lv_event_t * e)
{
#if (MENU_SCROLL_CONTROL == MENU_ARC_ZOOM || MENU_SCROLL_CONTROL == MENU_ARC_NON_ZOOM)
    arc_menu_refresh(e);
#elif(MENU_SCROLL_CONTROL == MENU_HOR_ZOOM )
    hor_menu_zoom_refresh(e);
#endif 

#if BG_IMG_EFFECT
    lv_obj_t * cont = lv_event_get_target(e);
    lv_obj_t * child = lv_obj_get_child(cont, 2);
    lv_area_t cont_a;
    lv_obj_get_coords(child, &cont_a);
    lv_coord_t cont_x_center = cont_a.x1 + lv_area_get_width(&cont_a) / 2;
    static lv_coord_t last_cont_x_center = -1;
    static lv_coord_t now_bg_x = 0;

    if(LV_ABS(last_cont_x_center - cont_x_center) < 200){
        now_bg_x -= last_cont_x_center - cont_x_center;
        now_bg_x = now_bg_x;
    }

    printf("%d", cont_x_center);

    last_cont_x_center = cont_x_center ;

    lv_img_t * bgimg = lv_event_get_user_data(e); 
    if(bgimg) {
        if(bgimg->w){
            lv_img_set_offset_x(bgimg, (now_bg_x/10)%320);
        }
    }
#endif
}
#endif

/**
 * @brief 图标点击回调
 * 
 * @param e 
 */
void menu_icon_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		lv_obj_t *icon = lv_event_get_target(e);

#if MENU_ICON_ONLY_CENTER_CLICKABLE
        lv_area_t icon_a;
        // 获取图标坐标信息
        lv_obj_get_coords(icon, &icon_a);

        if(!(icon_a.x1 < MENU_CONT_W / 2 && icon_a.x2 >= MENU_CONT_W / 2)) {
            return;
        }
#endif

        // 获取图标真实id，即在链表中的索引
        u32 icon_real_id = lv_obj_get_index(icon);
        // 获取图片源
        char *icon_src = (void *)lv_img_get_src(icon);
        // 字符串转数字
        u32 icon_show_id = a2i(icon_src);

        struct icon_info_t *icon_info = menu_get_icon_info_by_src(icon_src);

        if(icon_info && icon_info->icon_cb) {
            icon_info->icon_cb();
        }

        MENU_DEBUG("icon_real_id: %d, icon_show_id: %d", icon_real_id, icon_show_id);

        break;
    }
	default:
		break;
	}
}

/**
 * @brief 菜单初始化
 * 
 * @param page 
 */
void lv_menu_init(lv_obj_t *page)
{
    MENU_DEBUG("[menu] SCROLL MODE: 0x%x,\n"
        "                     ARC_EN:      %d,\n"
        "                     ZOOM_EN:     %d,\n"
        "                     CIRCLE_EN:   %d,\n"
        "                     MEMORY_EN:   %d",
        MENU_SCROLL_CONTROL,
        MENU_ARC_EN,
        MENU_ZOOM_EN,
        MENU_CIRCLE_EN,
        MENU_ICON_MEMORY_EN);
    mem_stats();

    lv_obj_t * bg = NULL;
#if BG_IMG_EFFECT
    bg = lv_img_create(page);
    lv_img_set_src(bg, MENU_CONT_BG_SRC);
    low_rle_anim_start(bg, 0, 0, NULL, NULL);
#endif

    menu_cont = lv_obj_create(page);
    // 配置菜单布局大小
    lv_obj_set_size(menu_cont, MENU_CONT_W, MENU_CONT_H);
    // 配置菜单透明的为不透明
#if BG_IMG_EFFECT
	lv_obj_set_style_bg_opa(menu_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
#else
	lv_obj_set_style_bg_opa(menu_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
#endif
    // 配置菜单背景色为黑色
	lv_obj_set_style_bg_color(menu_cont, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);

#if MENU_CONT_BG_EN
    lv_obj_set_style_bg_img_src(menu_cont, MENU_CONT_BG_SRC, 0);
    low_rle_anim_start2(menu_cont, 0, 0, NULL, NULL);
#endif

    // 适配菜单卡片页面
	lv_page_manager_page_adapte(menu_cont);
    // 菜单布局居中显示
    lv_obj_center(menu_cont);
    
    // 配置弹性布局
    lv_obj_set_flex_flow(menu_cont, LV_FLEX_FLOW_ROW);

#if MENU_SCROLL_CONTROL
    lv_obj_add_event_cb(menu_cont, hor_scroll_event_cb, LV_EVENT_SCROLL, bg);
#endif

    // lv_obj_add_event_cb(menu_cont, test_cont_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(menu_cont, scroll_end_event, LV_EVENT_SCROLL_END, NULL);
    
    /* lv_obj_set_style_clip_corner(menu_cont, true, 0); */
    // 配置图标在x轴上的间隙
    lv_obj_set_style_pad_column(menu_cont, MENU_ICON_INTERVAL, 0);
    // 配置弹性布局滚动方向为水平方向
    lv_obj_set_scroll_dir(menu_cont, LV_DIR_HOR);
    // 配置图标居中
    lv_obj_set_scroll_snap_x(menu_cont, LV_SCROLL_SNAP_CENTER);

#if MENU_ICON_Y_CENTER_EN
    lv_obj_set_flex_align(menu_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
#endif
    // 关闭进度条显示
    lv_obj_set_scrollbar_mode(menu_cont, LV_SCROLLBAR_MODE_OFF);

    uint32_t i;
    for(i = 0; i < MENU_ICON_SHOW_NUM; i++) {

#if MENU_ICON_ID_SHOW_TEST
        lv_obj_t * img_icon = lv_btn_create(menu_cont);
        lv_obj_set_size(img_icon, MENU_ICON_W, MENU_ICON_H);

        lv_obj_t * label = lv_label_create(img_icon);
        lv_label_set_text_fmt(label, "B_ %d", i);
#else
        // 创建图标
        lv_obj_t * img_icon = lv_img_create(menu_cont);
        // 配置图标可点击
        lv_obj_add_flag(img_icon, LV_OBJ_FLAG_CLICKABLE);
		// 配置图标尺寸
		lv_obj_set_size(img_icon, MENU_ICON_W, MENU_ICON_H);

#if MENU_CIRCLE_MEMORY_CONTROL
        u8 index = ((i + menu_icon_mem) % MENU_ICON_INDEX_NUM);
#else
        u8 index = (i % MENU_ICON_INDEX_NUM);
#endif

		lv_img_set_src(img_icon, menu_icon_info[index].icon_src);

		// lv_img_set_src(img_icon, menu_icon_tab[index]);
        lv_obj_add_event_cb(img_icon, menu_icon_event_cb, LV_EVENT_ALL, NULL);
#endif
    }

    menu_text_obj = lv_label_create(page);
    lv_obj_align(menu_text_obj, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_label_set_text(menu_text_obj, "INIT") ;
    lv_obj_set_style_text_color(menu_text_obj, lv_color_make(0xff,0xff,0xff), 0);
    lv_obj_set_style_text_font(menu_text_obj, &lv_customer_font_arial_unicode_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    // 首次主动发送LV_EVENT_SCROLL事件触发hor_scroll_event_cb
    lv_event_send(menu_cont, LV_EVENT_SCROLL, NULL);

#if MENU_NON_CIRCLE_MEMORY_CONTROL
    lv_obj_scroll_to_view(lv_obj_get_child(menu_cont, menu_icon_mem), LV_ANIM_OFF);
#else
    lv_obj_scroll_to_view(lv_obj_get_child(menu_cont, 0), LV_ANIM_OFF);
#endif
}

/**
 * @brief 菜单反初始化
 * 
 */
void lv_menu_deinit()
{
    MENU_DEBUG("[menu] func: %s, line: %d", __func__, __LINE__);
    mem_stats();
    if(menu_cont) {
        lv_obj_del(menu_cont); // 菜单布局
        menu_cont = NULL;
	}
}

#if MENU_OPA_EN
static void screen_menu_page_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *target = lv_event_get_target(e);

	int page_y = lv_obj_get_y(target);
	int page_height = lv_obj_get_height(target);

	switch (code) {
	case LV_EVENT_SIZE_CHANGED :
	{
		/* printf("page_y: %d", lv_obj_get_y(target)); */
		if(menu_cont) {
#if BG_IMG_EFFECT
			// lv_obj_set_style_bg_opa(menu_cont, LV_OPA_COVER - LV_OPA_COVER * LV_ABS(page_y) / page_height, 0);
#else
            lv_obj_set_style_bg_opa(menu_cont, LV_OPA_COVER - LV_OPA_COVER * LV_ABS(page_y) / page_height, 0);
#endif
        }
	
		break;
	}
	default:
		break;
	}
}
#endif

void events_init_screen_menu(lv_ui *ui)
{
#if MENU_OPA_EN
	if(ui->screen_menu->parent) {
		lv_obj_add_event_cb(ui->screen_menu->parent, screen_menu_page_event_handler, LV_EVENT_ALL, NULL);
	}
#endif
}


void screen_menu_refresh()
{
	//判断页面存活
	if(!screen_menu_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();
	// lv_label_set_text_fmt(guider_ui.screen_pc_mode_label_file_transfer, "%s", pc_mode_title[language]);
	// lv_label_set_text_fmt(guider_ui.screen_pc_mode_label_usb_tip, "%s", usb_plug_in_title[language]);

	
}

#endif