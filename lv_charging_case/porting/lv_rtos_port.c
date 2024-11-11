/*--------------------------------------------------------------------------*/
/**@file    UI_common.c
   @brief   UI 显示公共函数
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC319N
*/
/*----------------------------------------------------------------------------*/
#include "app_config.h"
#include "includes.h"
/* #include "ui/ui_api.h" */
/* #include "ui/ui.h" */
#include "typedef.h"
#include "clock_cfg.h"
#include "app_task.h"
#include "key_event_deal.h"
#include "ui/lcd_spi/lcd_drive.h"

#include "lvgl.h"
#include "lv_port_disp.h"

#include "usr_pic_index.h"


#if 1//LVGL_TEST_ENABLE

#define UI_TASK_NAME 	"ui"

// void lv_demo_widgets(void);
// void lv_demo_stress(void);
// void lv_demo_music(void);

// 鼠标对象
lv_obj_t * cursor_obj = NULL;

#define IS_HALL_TICK    1   //硬件时间戳

#if LV_USE_LOG && LV_LOG_PRINTF
static void lv_rt_log(const char *buf)
{
    printf(buf);
}
#endif



void rounder_cb(lv_disp_drv_t *disp_drv, lv_area_t *area) {
    // area->x1 = (area->x1 / 2) * 2; // Round down x1 to the nearest multiple of 2
    // area->x2 = (area->x2 / 2) * 2 + 1; // Round down x2 to the nearest multiple of 2
    // area->y1 = (area->y1 / 2) * 2; // Round down x1 to the nearest multiple of 2
    // area->y2 = (area->y2 / 2) * 2 + 1; // Round down x2 to the nearest multiple of 2
}
void render_start_cb(struct _lv_disp_drv_t * disp_drv){
    // extern void lcd_wait_te();
    //  lcd_wait_te();
}

#include "../lv_frame/generated/gui_guider.h"
#include "../lv_frame/generated/events_init.h"
#include "../lv_frame/custom/custom.h"
lv_ui guider_ui;

// #include "ui.h"
// #include "ui_helpers.h"


#if IS_HALL_TICK
static void lvgl_test_tick(void *param)
{
    if(!lcd_sleep_status()){
        lv_tick_inc(5);
    }
    // wdt_clear();
}
#endif
#if LV_LOW_POWER_EN
static u8 tp_init = false;
#endif

#include "events_adapter.h"
static void lvgl_task(void *p)
{
    printf("++++++++++++++++++++++++lvgl_task++++++++++++++++++++++++++++++++");

    extern void poweron_json_init();
    poweron_json_init();

    r_printf("%s", getselectwallper());

    char ver[20] = {0};
#if !BETA_VERSION
    sprintf(ver, "ver formal %d.%d.%d", FORMAL_F_VERSION_NUMBER, FORMAL_L_VERSION_NUMBER, TEST_VERSION);
#else
    sprintf(ver, "ver beta %d.%d", FORMAL_L_VERSION_NUMBER, TEST_VERSION);
#endif
    printf("color screen sdk: %s", ver);

// extern int fifo_main() ;
// fifo_main() ;

#if 0//TCFG_SD0_ENABLE
    extern void sd_test();
    sd_test();
#endif

    int msg[32];
    int ret;

#if LV_USE_LOG && LV_LOG_PRINTF
    lv_log_register_print_cb(lv_rt_log);
#endif

    lv_init();

    lv_port_disp_init(p);

#if !LV_LOW_POWER_EN
    //  等待模式任务启动再启动LVGL
    while(!app_get_curr_task()){
        printf("checks");
        os_time_dly(10);
    }
#endif
    lcd_sleep_ctrl(0);
    lcd_get_hdl()->backlight_ctrl(0);

    lv_port_indev_init();

#if IS_HALL_TICK
    sys_s_hi_timer_add(NULL, lvgl_test_tick, 5);
#endif

    lv_port_fs_init();

#if LV_USE_DEMO_WIDGETS
    lv_demo_widgets();
#endif /* #if LV_USE_DEMO_WIDGETS */

#if LV_USE_DEMO_STRESS
    lv_demo_stress();
#endif /* #if LV_USE_DEMO_STRESS */

#if LV_USE_DEMO_MUSIC
    // lv_demo_music();
#endif /* #if LV_USE_DEMO_MUSIC */

    

   
    extern volatile u8 usr_wait_te;
    usr_wait_te = 0;//0;

    //  用户动态控制是否推psram刷屏
    extern volatile u8 usr_full_screen;
    usr_full_screen = 0;//0;

    static int last_time = 0;
    int time_till_next = 0; //  距离下一次执行时间，此时间与待机低功耗相关

    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    extern lv_indev_t *indev_touchpad;
    cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, ID_ic_xia);           /*Set the image source*/
    lv_indev_set_cursor(indev_touchpad, cursor_obj);             /*Connect the image  object to the driver*/
    lv_obj_add_flag(cursor_obj, LV_OBJ_FLAG_HIDDEN);


    // static u8 bufout[10000*4];
    // static u8 bufin[10000*3];
    // int j;
    // int a = jiffies_half_msec();
    // int key = 0;
    // for(j=0;j<1000 ;j++){
    //     int i;
    //     for(i=0;i<10000;i++){
    //         memcpy(bufout[i*4], bufin[i*3], 3);
    //         key = 1;
    //     }
    //     // putchar('2');
        
    // }
    // int b = jiffies_half_msec();

    // printf(">>>>10000 %d 1/2   %d=",b-a,key);

    // // // // /*Create a GUI-Guider app */
    void setup_ui(lv_ui *ui);
    
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);

// desktop_init(0,0);
// desktop_init(100,30);
    // // // // lv_example_btn_11();
    // // // // extern void lv_demo_music(void);
    // // // // lv_demo_music();

    // extern void usr_ui_deal();
    // usr_ui_deal();

    // void lv_example_label_4(void);
    // lv_example_label_4();

    // lv_example_canvas_1();

    // lv_creat_oj()

    // lv_example_img_1();

    // lv_demo_keypad_encoder();

    // lv_example_imgfont_1();

	//避免开机白屏，延时亮背光
    // delay_2ms(200);

    hw_sleep_ctrl();

    int next=0;
    extern const int IDLE_AUTO_SLEEP;
    extern const int FULL_FLASH;
    while (1)
    {
        memset(msg, 0, sizeof(msg));

        int next=10;   

        //  LVGL
        if(!lcd_sleep_status()){
            next = lv_task_handler() / 15;
        }

        //  延时以及消息处理
        if(!lcd_sleep_status()) {
            if(next>10) next = 10;
            if(next) os_time_dly(next);
            if(!next) wdt_clear();
            ret = os_taskq_accept(ARRAY_SIZE(msg), msg);              
        } else {
            ret = os_taskq_pend(NULL, msg, ARRAY_SIZE(msg));
        }


#if !IS_HALL_TICK
        //  休眠处理
        static u32 lasttime = 0;
        if(lasttime==0)lasttime = jiffies_msec();
        if(!lcd_sleep_status()){
            u32 now = jiffies_msec();
            if(now - lasttime > 200){
                lasttime = now-50;
            }
            u32 dt = now - lasttime;
            lasttime = now;
            lv_tick_inc(dt);   
        } 
#endif

        /* 处理消息 */
        lv_os_event_handle((ret == OS_TASKQ)?msg:NULL);

#if LV_LOW_POWER_EN

#if TCFG_TP_CST816D_ENABLE
    // 标准原理图使用ldo给tp供电（pin_en）。需要提前拉一下io口，否则cst816可能升级失败
    if(!tp_init)
    {
        tp_init = TRUE;
        extern void cst816d_init();
        cst816d_init();
    }
#endif

#endif

    }
}

int lvgl_test_init(void *param)
{
    int err = 0;
    clock_add_set(DEC_UI_CLK);
    err = task_create(lvgl_task, param, UI_TASK_NAME);
    if (err) {
        r_printf("ui task create err:%d \n", err);
    }
    return err;
}


int post_ui_msg(int *msg, u8 len)
{
    int err = 0;
    int count = 0;

__retry:
    err =  os_taskq_post_type(UI_TASK_NAME, msg[0], len - 1, &msg[1]);

    if (cpu_in_irq() || cpu_irq_disabled()) {
        return err;
    }

    if (err) {
        if (!strcmp(os_current_task(), UI_TASK_NAME)) {
            return err;
        }
        if (count > 20) {
            return -1;
        }
        count++;
        os_time_dly(1);
        goto __retry;
    }
    return err;
}
int ui_key_msg_post(int key)
{
    u8 count = 0;
    int msg[8];

    if (key >= 0x80) {
        printf("key need <= 0x80");
        return -1;
    }

    msg[0] = UI_MSG_KEY;
    msg[1] = key;
    /* touch_msg_counter++; */
    return post_ui_msg(msg, 2);
}

static u8 lvgl_idle_query(void)
{
    return lcd_sleep_status();
}

REGISTER_LP_TARGET(lvgl_lp_target) = {
    .name = "lvgl",
    .is_idle = lvgl_idle_query,
};














#endif /* #if LVGL_TEST_ENABLE */
