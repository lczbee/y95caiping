#include "custom.h"

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<内部亮灭屏>>>>>>>>>>>>>>>>>>>>>>>>>>> */
const int FULL_FLASH       =    1;//0;      //  1：一直全屏刷新
const int IDLE_AUTO_SLEEP  =    0 ; //1暂时有bug    //  1：空闲状态自动释放线程，支持LV低功耗定时器。0：灭屏释放线程，低功耗定时器不跑
#define INACTIVE_TIMEOUT    100         //  输入响应超时释放线程时间
int auto_sleep_time     =   30000;      //  自动息屏时间30s，
u8  always_run     =   0;               //  是否常亮
void lv_enter_sleep();                //  亮屏指令，可以跨线程使用
void lv_exit_sleep();                 //  灭屏指令，可以跨线程使用
void usr_bl_update(u8 level);           //  背光调节

// 用于区分按键亮屏
u8 screen_on_source = SCREEN_ON_SOURCE_NONE;

void screen_on_source_reset()
{
    screen_on_source = SCREEN_ON_SOURCE_NONE;
}

extern lv_indev_t *indev_touchpad;
extern lv_indev_t * indev_keypad;


void usr_screen_on(u8 on)
{
    u32 rets;
    __asm__ volatile("%0 = rets":"=r"(rets));
    printf("__func__ %s %x\n", __func__, rets);

    static bool animimg_wp_playing = false;
    static bool animimg_poweron_playing = false;
    static bool animimg_charging_playing = false;
    static bool animimg_lock_playing = false;

    if(!on) {
        // lcd_clear(0, 320, 34, 354, 0); // 清屏
        lcd_full_clear(0); // 清屏
        // lv_obj_add_flag(guider_ui.screen_loop_cont_screen_lock, LV_OBJ_FLAG_HIDDEN); // 进休眠统一隐藏锁屏，退出休眠再设置
        // lv_timer_pause(lv_disp_get_default()->refr_timer);  //  暂停绘制，实际控制不了
        // lv_timer_pause(indev_touchpad->driver->read_timer); //  暂停触摸
        // lv_timer_pause(indev_keypad->driver->read_timer);   //  暂停按键

        // 记录正在运行的动画
        if(guider_ui.screen_wallpaper){
            animimg_wp_playing = lv_anim_get(guider_ui.screen_wallpaper_animimg_wp, NULL) ? true : false;
        }
        if(guider_ui.screen_poweron){
            animimg_poweron_playing = lv_anim_get(guider_ui.screen_poweron_animimg_poweron, NULL) ? true : false;
        }
        if(guider_ui.screen_charging){
            animimg_charging_playing = lv_anim_get(guider_ui.screen_charging_animimg_charging, NULL) ? true : false;
        }
        if(guider_ui.screen_lock){
            animimg_lock_playing = lv_anim_get(guider_ui.screen_lock_animimg_lock, NULL) ? true : false;
        }
        printf("animimg_wp_playing : %d", animimg_wp_playing);
        printf("animimg_poweron_playing : %d", animimg_poweron_playing);
        printf("animimg_charging_playing : %d", animimg_charging_playing);
        printf("animimg_lock_playing : %d", animimg_lock_playing);

#if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
        //息屏时暂停所有动画，节省资源
        //lv_anim_del_all();
#endif

        // lv_task_handler();
    }
    lcd_sleep_ctrl(!on);
    if (on)
    {
        lv_obj_invalidate(lv_scr_act()); //  全屏重绘一次
        // lcd_clear(0, 320, 34, 354, 0); // 清屏

        //亮屏恢复动画
        printf("animimg_wp_playing : %d", animimg_wp_playing);
        printf("animimg_poweron_playing : %d", animimg_poweron_playing);
        printf("animimg_charging_playing : %d", animimg_charging_playing);
        printf("animimg_lock_playing : %d", animimg_lock_playing);
        if(guider_ui.screen_wallpaper && animimg_wp_playing){
            lv_animimg_start(guider_ui.screen_wallpaper_animimg_wp);
        }
        if(guider_ui.screen_poweron && animimg_poweron_playing){
            lv_animimg_start(guider_ui.screen_poweron_animimg_poweron);
        }
        if(guider_ui.screen_charging && animimg_charging_playing){
            lv_animimg_start(guider_ui.screen_charging_animimg_charging);
        }
        if(guider_ui.screen_lock && animimg_lock_playing){
            lv_animimg_start(guider_ui.screen_lock_animimg_lock);
        }

        // lv_timer_resume(lv_disp_get_default()->refr_timer);
        // lv_timer_resume(indev_touchpad->driver->read_timer);
        // lv_timer_resume(indev_keypad->driver->read_timer);
#if LV_DEMO_POP_UP_EN
        // 开启弹窗动画功能则只有按键唤醒显示锁屏
        if(screen_on_source == SCCEEN_ON_SOURCE_KEY || screen_on_source == SCREEN_ON_SOURCE_TOUCH) {
            screen_lock_enter(); // 退出休眠，设置锁屏
        }
#else
        screen_lock_enter(); // 退出休眠，设置锁屏
#endif

        // extern void screen_list_refresh();
        // screen_list_refresh();

        // lv_task_handler();

        lcd_mcpwm_init();
        u8 level = box_info_base_cb.lv_ui_bl_levl_get();
        usr_bl_update(level);  
        printf("func:%s , line:%d \n" , __func__ , __LINE__);

        // 重置亮屏源
        screen_on_source_reset();  

        // extern void soc_disp();
        // soc_disp();
        extern int now_soc_trim_info;
        if(now_soc_trim_info==200){
            extern void soc_disp();
            soc_disp();            
        }
    }
}

/* 系统消息回调 */
void lv_os_event_handle(int msg[]) {
    /* 自动息屏 */
    if(always_run == 1) {
        lv_disp_trig_activity(NULL);
    }
    if(lv_disp_get_inactive_time(NULL) > auto_sleep_time && !lcd_sleep_status()){
        usr_screen_on(0);
    }      

    if (IDLE_AUTO_SLEEP){
        /* 输入设备活跃超时 */
        if(lv_disp_get_inactive_time(NULL) > INACTIVE_TIMEOUT ) {
            lv_timer_pause(indev_touchpad->driver->read_timer);
            lv_timer_pause(indev_keypad->driver->read_timer);        
        }

    }

    if(msg==NULL) return;

    // printf("msg %d %d", msg[0],msg[1]);
    lv_disp_trig_activity(NULL);

    if(IDLE_AUTO_SLEEP){
        lv_timer_resume(indev_touchpad->driver->read_timer);
        lv_timer_resume(indev_keypad->driver->read_timer); 
    }

    switch(msg[0]) {
        case UI_MSG_HIDE:
            if(!lcd_sleep_status()) usr_screen_on(0);
            break;
        case UI_MSG_SHOW:
            if(lcd_sleep_status()) usr_screen_on(1);
            break;
        case UI_MSG_KEY:
            if(msg[1] == 64){
                if(lcd_sleep_status()){
                    screen_on_source = SCCEEN_ON_SOURCE_KEY;
                    lv_exit_sleep();
                } else {
                    lv_enter_sleep();
                }
            }
            
            break;
        case UI_MSG_UPDATE:
            switch(msg[1]) {
                case UI_UPDATE_TIME:
                    // struct sys_time *time = (struct sys_time *)&msg[2];
                    // sbox_set_sys_time(time);
                    break;
                case UI_UPDATE_BR_STATUS:
                    g_printf("HJY %s[line:%d ]\n",__func__,__LINE__, msg[2]);
                    u8 emitter_status = msg[2];
                    box_info_base_cb.lv_emitter_state_set(emitter_status);
                    switch(emitter_status) {
                        // 已连接
                        case BR_CONNECTED:
                            lv_music_mode_set_sd_music();
                            lv_tip_wait_to_music_play();
                            extern lv_timer_t *wait_timeout_timer;
                            if(wait_timeout_timer){
                                lv_timer_del(wait_timeout_timer);
                                wait_timeout_timer = NULL;
                            }
                            break;
                        // 断开连接
                        case BR_DISCONNECTED:

                            break;
                        // 连接超时
                        case BR_PAGE_TIMEROUT:

                            break;
                    }
                    
                    break;
            }
            break;
    }



}



/* 自动灭屏使能 */
void lv_auto_sleep_enable(bool enable)
{
    // u32 rets;
    // __asm__ volatile("%0 = rets":"=r"(rets));
    // printf("__func__ %s %x\n", __func__, rets);
    printf("always_run: %d", always_run);
    always_run = !enable;
}


/* 灭屏指令 */
void lv_enter_sleep()
{
    int msg[8];
    msg[0] = UI_MSG_HIDE;
    post_ui_msg(msg, 1);
}

/* 亮屏指令 */
void lv_exit_sleep()
{
    u32 rets;//, reti;
    __asm__ volatile("%0 = rets":"=r"(rets));
    printf("__func__ %s %x\n", __func__, rets);
    int msg[8];
    msg[0] = UI_MSG_SHOW;
    post_ui_msg(msg, 1);    
}

void lv_key_active()
{
    int msg[8];
    msg[0] = UI_MSG_KEY;
    post_ui_msg(msg, 1);    
}

void lv_touch_active()
{
    int msg[8];
    msg[0] = UI_MSG_TOUCH;
    post_ui_msg(msg, 1);   
    screen_on_source = SCREEN_ON_SOURCE_TOUCH; 
}


void hw_sleep_ctrl()
{
    /* 初始化VM */
    lv_disp_trig_activity(NULL);


    /* 初始化背光 */
    u8 level = box_info_base_cb.lv_ui_bl_levl_get();
    usr_bl_update(level);

#if LV_SOC_CHECK
    static u8 flag = 0;
    extern int send_to_trig_vcb(void (*func)(void), char*taskname);
    extern void soc_check_init();
    if(flag == 0){
        flag = 1;
        send_to_trig_vcb(soc_check_init, "app_core");
    }    
#endif
}

#include "lvgl.h"
#define LIGHT_LEVEL_MAX    100 // 亮度最大等级
#define LIGHT_LEVEL_MIN    10	// 亮度最小等级

    
void usr_bl_update(u8 level)
{
    u8 percent = lv_map(level, 0, 100, LIGHT_LEVEL_MIN, LIGHT_LEVEL_MAX);
    extern int lcd_drv_backlight_ctrl_base(u8 percent);
    lcd_drv_backlight_ctrl_base(percent);
}


