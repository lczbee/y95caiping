/*
 * @Description: 
 * @Author: HJY
 * @Date: 2024-02-24 09:42:07
 * @LastEditTime: 2024-03-06 14:58:26
 * @LastEditors: HJY
 */
/*
 * @Description: 
 * @Author: HJY
 * @Date: 2024-01-03 16:54:00

 * @LastEditTime: 2024-02-18 17:14:37
 * @LastEditors: HJY
 */
#include "app_config.h"
#include "app_action.h"
#include "system/timer.h"
#include "key_event_deal.h"
#include "audio_config.h"
#include "jiffies.h"
#include "audio_dec.h"
#include "audio_dec_file.h"
#include "music/music_player.h"
#include "btstack/avctp_user.h"
#include "bt_emitter.h"
#include "soundbox.h"
#include "ble_user.h"
#include "bt/bt.h"
#include "music/music.h"
#include "key_event_deal.h"
#include "bt_emitter.h"
#include "audio_dec.h"
#include "audio_dec_file.h"
#include "music/music_player.h"
#include "smartbox_user_app.h"
#include "app_task.h"
#include "events_adapter.h"

#undef _DEBUG_H_
#define LOG_TAG_CONST       LOCAL_PLAY          //修改成文件名
#define LOG_TAG             "[LOCAL_PLAY]"
#include "debug.h"
#define LOG_v(t)  log_tag_const_v_ ## t
#define LOG_i(t)  log_tag_const_i_ ## t
#define LOG_d(t)  log_tag_const_d_ ## t
#define LOG_w(t)  log_tag_const_w_ ## t
#define LOG_e(t)  log_tag_const_e_ ## t
#define LOG_c(t)  log_tag_const_c_ ## t
#define LOG_tag(tag, n) n(tag)
const char LOG_tag(LOG_TAG_CONST,LOG_v) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_i) AT(.LOG_TAG_CONST) = 1; //log_info
const char LOG_tag(LOG_TAG_CONST,LOG_d) AT(.LOG_TAG_CONST) = 1; //log_debug
const char LOG_tag(LOG_TAG_CONST,LOG_w) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_e) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_c) AT(.LOG_TAG_CONST) = 1;


#define BS_DIR_TYPE_FORLDER   	0
#define BS_DIR_TYPE_FILE   		1

static u8 emitter_status = BR_EXIT;

void lvgl_br_status_update(u8 br_status)
{
    g_printf("%s[line:%d, emitter_status:%d, br_status:%d]\n",__func__,__LINE__, emitter_status, br_status);
    if(br_status == emitter_status){
        return;
    }
    emitter_status = br_status;
    int msg[8];
    msg[0] = UI_MSG_UPDATE;
    msg[1] = UI_UPDATE_BR_STATUS;
    msg[2] = emitter_status;
    // b_printf("update YMS HMS: %d/%d/%d %d=%d-%d", time->year, time->month, time->day, time->hour, time->month, time->sec);
    post_ui_msg(msg, 8);    
}

u8 get_emitter_status(void)
{
    return emitter_status;
}

extern u8 get_spk_stream_status();
/**
 * @description: 本地音乐是否处于播放状态
 * @return 1： 播放中 0：暂停中
 */
int local_music_is_play(void)
{
#if PC_AUDIO_EMITTER
    if(get_usb_online_status()){
        return get_spk_stream_status();
    }
#endif /* PC_AUDIO_EMITTER */
#if TCFG_APP_MUSIC_EN
    if (app_get_curr_task() == APP_MUSIC_TASK) {
        if (music_player_get_play_status() == FILE_DEC_STATUS_PLAY) {
            return true;
        }
    } else
#endif /* #if TCFG_APP_MUSIC_EN */
    {
        if (bt_media_is_running()) {
            return true;
        }
    }
    return false;
}


/**
 * @description: 本地音乐播放暂停
 * @return {*}
 */
void local_play_music_pp(void)
{

    log_debug("%s[line:%d]\n",__func__,__LINE__);
        
#if TCFG_APP_MUSIC_EN
    if (bt_get_music_device_style() == SET_MUSIC_IN_WATCH) {
        if (app_get_curr_task() != APP_MUSIC_TASK) {
                        music_set_start_auto_play(1);
            app_task_switch_to(APP_MUSIC_TASK);
        } else {
                        app_task_put_key_msg(KEY_MUSIC_PP, 0);
        }
    }
#endif /* #if TCFG_APP_MUSIC_EN */
        if (bt_get_music_device_style() == SET_MUSIC_IN_PHONE) {
        if (app_get_curr_task() != APP_BT_TASK) {
        app_task_switch_to(APP_BT_TASK);
        }
            bt_key_music_pp();
        }

}


/**
 * @description: 指定文件序号播放
 * @return {*}
 * @param {u32} sclust  序号值
 */
void local_play_by_sclust(u32 sclust)
{
#if TCFG_APP_MUSIC_EN
    log_debug("%s[line:%d]\n",__func__,__LINE__);
    if (app_get_curr_task() != APP_MUSIC_TASK) {
            music_task_set_parm(MUSIC_TASK_START_BY_SCLUST, sclust);
            /* dev_manager_set_active_by_logo(dev_logo); */
            log_debug("%s[line:%d]\n",__func__,__LINE__);
            music_set_start_auto_play(1);
            app_task_switch_to(APP_MUSIC_TASK);
        } else {
            log_debug("%s[line:%d]\n",__func__,__LINE__);
            app_task_put_key_msg(KEY_MUSIC_PLAYE_BY_DEV_SCLUST, sclust);
        }
#endif //TCFG_APP_MUSIC_EN
}

/**
 * @description: 上一曲
 * @return {*}
 */
void local_play_music_prev(void)
{
    log_debug("%s[line:%d]\n",__func__,__LINE__);
    app_task_put_key_msg(KEY_MUSIC_PREV, 0);
}

/**
 * @description: 下一曲
 * @return {*}
 */
void local_play_music_next(void)
{
    log_debug("%s[line:%d]\n",__func__,__LINE__);
    app_task_put_key_msg(KEY_MUSIC_NEXT, 0);
}

/**
 * @description:搜索蓝牙名根据名字匹配链接
 * @return {*}
 */
void local_play_conn_earphone_by_name(void)
{
    log_debug("%s[line:%d]\n",__func__,__LINE__);
    bt_emitter_start_search_device();
    
}

/**
 * @description: 根据地址回连耳机
 * @return {*}
 */
extern u8 custom_remote_addr[6];
void local_play_conn_earphone_by_addr(void)
{

    log_debug("%s[line:%d]\n",__func__,__LINE__);
    u8 ear_addr[6];
    delete_last_device_from_vm();
    user_send_cmd_prepare(USER_CTRL_DEL_ALL_REMOTE_INFO, 0, NULL);
    // u8 mac[6] = {0x86, 0x96, 0xAE, 0x23, 0xEF, 0x7E};
    // u8 mac[6] = {0xFA, 0x0D, 0x20, 0x42, 0x5F, 0x2A };
    memcpy(ear_addr, custom_remote_addr, 6);
    // ear_addr[5] = ~ear_addr[5];
    // custom_client_send_ctrl_edr_info();
    // os_time_dly(100);
    custom_client_send_ctrl_edr_conn(1);

    
    emitter_bt_connect(ear_addr);  
    put_buf(ear_addr, 6);
    lvgl_br_status_update(BR_INIT);
}
static void br_disconn_deal(void)
{
    g_printf("%s[line:%d]\n",__func__,__LINE__);
    
    if(emitter_status == BR_CONNECTED){
        sys_timeout_add(NULL, br_disconn_deal, 200);

    }else{
            bt_close_bredr();
        lvgl_br_status_update(BR_EXIT);
        custom_client_send_ctrl_edr_conn(2);
    }
}

/**
 * @description: 关闭本地发射
 * @return {*}
 */
void local_play_close_bt(void)
{
    log_debug("%s[line:%d]\n",__func__,__LINE__);   
    delete_last_device_from_vm();
    user_send_cmd_prepare(USER_CTRL_DEL_ALL_REMOTE_INFO, 0, NULL);
    // user_send_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);
    user_send_cmd_prepare(USER_CTRL_DISCONNECTION_HCI, 0, NULL);
    
    // while (emitter_status == BR_CONNECTED)
    // {
    //     printf("HJY wait disconn\n");
    //     os_time_dly(200);
    // }
    sys_timeout_add(NULL, br_disconn_deal, 200);

    
    
}


/**
 * @description: 蓝牙状态回调函数
 * @return {*}
 * @param {char} *type 蓝牙事件类型
 * @param {u32} arg 蓝牙事件值
 */
void local_play_bt_status_handler(const char *type, u32 arg)
{
    log_debug("%s[line:%d, arg:%d]\n",__func__,__LINE__, arg);
    if(type == NULL){
        r_printf("%s[line:%d err!!!]\n",__func__,__LINE__);
        return;

    }

    if (!strcmp(type, "event")) {
        log_debug("%s[line:%d]\n",__func__,__LINE__);
        
        switch (arg) {
        case BT_STATUS_SECOND_CONNECTED:
        case BT_STATUS_FIRST_CONNECTED:
        case BT_STATUS_CONN_A2DP_CH:
            r_printf("bt is connected!!!!");
            lvgl_br_status_update(BR_CONNECTED);
            
            
            // ui_pic_show_image_by_id(SIDEBAR_BLUETOOTH_PIC, 1);
            break;
        case BT_STATUS_FIRST_DISCONNECT:
        case BT_STATUS_SECOND_DISCONNECT:
            r_printf("bt is disconnected!!!!");

            lvgl_br_status_update(BR_DISCONNECTED);
            
            // ui_pic_show_image_by_id(SIDEBAR_BLUETOOTH_PIC, 0);
            break;
        }
    }else if (!strcmp(type, "hci_value"))
    {
        log_debug("%s[line:%d]\n",__func__,__LINE__);
        
        switch (arg) {
            case ERROR_CODE_PIN_OR_KEY_MISSING:
            case ERROR_CODE_PAGE_TIMEOUT:
                r_printf("bt connecting fail!!!");
                lvgl_br_status_update(BR_PAGE_TIMEROUT);
                break;
            }
    }else if(!strcmp(type, "hci_event")){
        log_debug("%s[line:%d]\n",__func__,__LINE__);
        
        switch (arg) {
            case HCI_EVENT_DISCONNECTION_COMPLETE:
                lvgl_br_status_update(BR_DISCONNECTED);
                r_printf("bt hci is disconnected!!!!");
                break;
            }
    }else{
        r_printf("%s[line:%d, err!!!!]\n",__func__,__LINE__);
        
    }
    
    
}
#if PC_AUDIO_EMITTER

void local_play_post_app_core_event(u8 cmd)
{
    struct sys_event e;
    e.type = SYS_DEVICE_EVENT;
    e.arg  = (void *)DEVICE_EVENT_FROM_LOP;
    e.u.dev.event = DEVICE_EVENT_CHANGE;
    e.u.dev.value = cmd;
    
    sys_event_notify(&e);
}
extern void usb_start();
extern void usb_stop();
extern void set_change_usb_mode(u8 mode);
void local_play_event_handler(struct sys_event *e)
{
    g_printf("HJY %s[line:%d]\n",__func__,__LINE__);

    if ((u32)e->arg == DEVICE_EVENT_FROM_LOP) {
        switch (e->u.dev.value)
        {
        case LOCAL_PLAY_PC_MUSIC_PREV:
            extern_app_ctrl_pc_key(KEY_MUSIC_PREV);
            break;
        
        case LOCAL_PLAY_PC_MUSIC_PP:
            extern_app_ctrl_pc_key(KEY_MUSIC_PP);
            break;
        case LOCAL_PLAY_PC_CLOSE:
            usb_stop();
            bt_emitter_pp(0);
            sys_timeout_add(NULL, usb_start, 1000);
            break;
        case LOCAL_PLAY_PC_START:
    		usb_start();
            break;
        case LOCAL_PLAY_PC_STOP:
    		usb_stop();
            break;
        case LOCAL_PLAY_MUSIC_MODE:
            g_printf("HJY %s[line:%d, LOCAL_PLAY_MUSIC_MODE]\n",__func__,__LINE__);
            
            usb_stop();
            set_change_usb_mode(0);
            if(lv_music_mode_get() == SD_MUSIC){
                sys_timeout_add(NULL, usb_start, 1000);

            }
            break;
        case LOCAL_PLAY_MASK_MODE:
            g_printf("HJY %s[line:%d, LOCAL_PLAY_MASK_MODE]\n",__func__,__LINE__);
            
            usb_stop();
            set_change_usb_mode(1);
            sys_timeout_add(NULL, usb_start, 1000);
            break;

        default:
            break;
        }
    }

    

}

// void conn_earphone_test(void)
// {
	
// 	extern void local_play_conn_earphone_by_name(void);
// 	if(emitter_status != BR_CONNECTED){
//         r_printf("11111\n");
//         local_play_conn_earphone_by_name();
// 	    local_play_post_app_core_event(LOCAL_PLAY_PC_START);
		
// 	}else
//     {
//         if(get_usb_online_status()){
//                  r_printf("11112\n");
// 				extern_app_ctrl_pc_key(KEY_MUSIC_PP);
// 			}else{
//                  r_printf("11113\n");
// 				local_play_music_pp(); // 本地播放暂停接口
// 			}

//     }
	
// }
#endif  /* PC_AUDIO_EMITTER */