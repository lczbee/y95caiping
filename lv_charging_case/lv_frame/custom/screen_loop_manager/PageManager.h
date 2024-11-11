#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "../lvgl/lvgl.h"
#endif

//信息打印
#define UsePrint
#ifdef UsePrint
#include "cpu.h"
#include "custom.h"
#define DEBUG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

// 管理页面大小和位置
#define WIDTH           (320)
#define HEIGHT          (172)
// 页面切换的触发阈值百分比(1-100),越小越容易触发
#define PageLimit       (5) // 20
// 页面切换速度
#define AnimMoveSpeed   1000 // 如果希望滑动页面快速完成可以尝试改为2000
// 页面切换动画模式
#define AnimMoveMode    lv_anim_path_ease_out // lv_anim_path_ease_in_out

// 惯性触发页面滑动
#define EnergyTrigger   1

#if EnergyTrigger
// 惯性判断时长，用于区分快速拖动和慢速拖动
#define EnergyTime      10

#undef AnimMoveSpeed
#define AnimMoveSpeed   3000

// 惯性参数
struct EnergyParam {
    u32 LastTick;       // 记录tick
    u8 ReleasedFlag;    // 抬手标志位
};

// 更新LastTick
u32 PM_Update_LastTick();
// 获取LastTick
u32 PM_Get_LastTick();
// 设置抬手标志位
void PM_Set_ReleasedFlag(u8 flag);
// 获取抬手标志位
u8 PM_Get_ReleasedFlag();
#endif


// 页面状态
enum PageState
{
    // 无效页面
    INVALID = 0,
    // 有效页面
    VALID,
    // 有效并已创建的页面
    VALID_AND_CREATED,
};

// 页面的位置方向
enum PageDir
{
    // 本页面
    PageNone    = 0,
    // 上面的页面
    PageUp      = (1 << 0),
    // 下面的页面
    PageDown    = (1 << 1),
    // 左面的页面
    PageLeft    = (1 << 2),
    // 右面的页面
    PageRight   = (1 << 3),
};

// 页面动画模式
enum MoveMode
{
    // 切换动画方式
    // 0 没有切换方式（此模式应该无法切换）
    LOAD_ANIM_NONE = 0,
    // 1 平推模式
    LOAD_ANIM_MOVE,
    // 2 覆盖模式
    LOAD_ANIM_OVER,
    // 3 离开模式
    LOAD_ANIM_LEAVE,
    // 4 旋转模式
    LOAD_ANIM_ROTATE,
};

enum PageLayer
{
    // 底层页面层
    LAYER_BOTTOM = 0,
    // 中层页面层
    LAYER_MIDDLE,
    // 顶层页面层
    LAYER_TOP,
};

// 页面结构体
typedef struct PageNode {
    enum PageState State;
    lv_obj_t* obj;
    void (*InitPage)    (lv_obj_t* page);
    void (*DeinitPage)  (lv_obj_t* page);
    struct
    {
        struct PageNode* Page;
        enum MoveMode Mode;
    }Up;
    struct
    {
        struct PageNode* Page;
        enum MoveMode Mode;
    }Down;
    struct
    {
        struct PageNode* Page;
        enum MoveMode Mode;
    }Left;
    struct
    {
        struct PageNode* Page;
        enum MoveMode Mode;
    }Right;
    u16 id;
    enum PageLayer Layer;
}PageTypeHandle;

extern struct PM_Custom_Fun PM_Custom_Cb;

// 初始化页面管理器
void PM_Init(void);

// 开始页面管理器
void PM_Start(PageTypeHandle* Page);

// 删除页面管理器
void PM_Deinit(void);

// 添加页面
void PM_AddPage(PageTypeHandle* Page, void (*InitPage)(lv_obj_t* page), void (*DeinitPage)(lv_obj_t* page), enum PageId id, enum PageLayer layer);

// 关闭页面
void PM_ClosePage(PageTypeHandle* SourcePage, enum PageDir Dir);

// 删除页面
void PM_DelPage(PageTypeHandle* SourcePage, enum PageDir Dir);

// 设置主页面
void PM_SetHomePage(PageTypeHandle* Page);

// 设置页面切换
void PM_SetPageMoveMode(PageTypeHandle* SourcePage, enum PageDir Dir, PageTypeHandle* TargetPage, enum MoveMode Mode);

// 页面跳转
void PM_EnterPage(PageTypeHandle* Page);

// 页面切换
void PM_PageMove(enum PageDir Dir);

// 设置公共下页面
void PM_SetPublicDown(PageTypeHandle* Page);

// 获取管理器背景层OBJ指针
lv_obj_t* PM_GetBackGroudObj(void);

// 获取管理器主体OBJ指针
lv_obj_t *PM_GetObj(void);

#define Home        lv_scr_act()
#define Desktop     lv_layer_top()
#define System      lv_layer_sys()

// 自定义函数
struct PM_Custom_Fun {
    void (*status_bar_bottom_update)(enum PageId id); // 底部状态栏更新
    void (*status_bar_top_update)(void); // 顶部状态栏更新
    void (*ble_setting_cmd_send)(u8 data);  // ble命令发送
};

#endif
