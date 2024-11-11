#include "smartbox_user_app.h"
#include "ble_user.h"
#include "btstack/le/att.h"
#define LOG_TAG     		"[SYS-sbox]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"
#include "ui/ui.h"
#include "lv_demo_music/lv_demo_music.h"
#include "lv_demo_pop_up/lv_demo_pop_up.h"

struct s_box_info box_info={
    // .l_ear_bat = 0xff,
    // .r_ear_bat = 0xff,
    // .box_bat =   0xff,
    // .earphone_vol = 16,
    // .ui_bl_levl = 100,
    .phone_state        = 0,
    .earphone_state     = 0,
    .l_ear_bat          = 0,
    .r_ear_bat          = 0,
    .l_inbox            = 0,     //左耳是否入仓
    .r_inbox            = 0,
    .box_bat            = -1,
    .music_state        = 2, // 默认配置为暂停状态
    .earphone_vol       = 0,
    .anc_mode           = 0,
    .eq_mode            = 0,
    .ui_bl_levl         = 50,
    .l_charging         = 0,
    .r_charging         = 0,
    .box_charging       = 0,
    .l_finding          = 0,
    .r_finding          = 0,
    .box_clid_status    = 0,
    .language           = 0,
    .low_power          = 0,
    .phone_call_state   = 0,
    .phone_call_mute    = 0,
    .local_page         = 0,
    .emitter_status     = 0, // 默认配置为手机音乐 0：手机音乐 1：SD音乐

};
struct custom_music_info local_music_info;
static custom_edr_info s_emitter_info;
#if 1
#define log_info(x, ...)       y_printf("[sbox_data]" x " ", ## __VA_ARGS__)
#define log_info_hexdump       put_buf
#else
#define log_info(...)
#define log_info_hexdump(...)
#endif
void custom_ble_client_write_no_respond(u8 cmd, u8 *data, u8 len);
u8 sbox_get_box_charging(void)
{
    return box_info.box_charging;
}

void sbox_bt_connect_flag_set(u8 bt_connect_flag)
{
    box_info.phone_state = bt_connect_flag;
}
u8 sbox_bt_connect_flag_get(void)
{
    return box_info.phone_state;
}
void sbox_ble_connect_flag_set(u8 ble_connect_flag)
{
    // y_printf("sbox_ble_connect_flag_set %d\n",ble_connect_flag);
    box_info.earphone_state = ble_connect_flag;
}
u8 sbox_ble_connect_flag_get(void)
{
    return box_info.earphone_state;
}
void sbox_battery_left_set(u8 battery_left)
{
    if(battery_left>100 || battery_left<0)
    {
        return;
    }
    box_info.l_ear_bat = battery_left;
}
u8 sbox_battery_left_get(void)
{
    return box_info.l_ear_bat;
}
void sbox_battery_right_set(u8 battery_right)
{
    if(battery_right>100 || battery_right<0){
        return;
    }
    box_info.r_ear_bat = battery_right;
}
u8 sbox_battery_right_get(void)
{
    return box_info.r_ear_bat;
}
void sbox_battery_box_set(u8 battery_box)
{
    box_info.box_bat = battery_box;
}
u8 sbox_battery_box_get(void)
{
    return box_info.box_bat;
}
void sbox_language_ui_set(u8 language)
{
    box_info.language = language;
}
u8 sbox_language_ui_get(void)
{
    return box_info.language;
}
void sbox_music_ui_state_set(u8 music)
{
    box_info.music_state = music;
}
u8 sbox_music_ui_state_get(void) // 0:index 0
{
    return box_info.music_state;
}

void sbox_volume_set(u8 volume)
{
    box_info.earphone_vol = volume;
}   
u8 sbox_volume_get(void)
{
    return box_info.earphone_vol;
}

 // 1 隐藏 2来电 3通话中
void sbox_call_state_set(u8 flag)
{
    box_info.phone_call_state = flag; 
}
u8 sbox_call_state_get(void)
{
    return box_info.phone_call_state; 
}

void sbox_equalizer_mode_set(u8 equalizer_mode)
{
    box_info.eq_mode = equalizer_mode;
}
u8 sbox_equalizer_mode_get(void)
{
    return box_info.eq_mode;
}

void sbox_backlight_level_set(u8 backlight_level)
{
    box_info.ui_bl_levl = backlight_level;

    extern void usr_bl_update(u8 level);
    usr_bl_update(backlight_level);
}
u8 sbox_backlight_level_get(void)
{
    return box_info.ui_bl_levl;
}

void sbox_left_charging_set(u8 charging)
{
    box_info.l_charging = charging;
}
u8 sbox_left_charging_get(void)
{
    return box_info.l_charging;
}

void sbox_right_charging_set(u8 charging)
{
    box_info.r_charging = charging;
}
u8 sbox_right_charging_get(void)
{
    return box_info.r_charging;
}

void sbox_box_charging_set(u8 charging)
{
    box_info.box_charging = charging;
}
u8 sbox_box_charging_get(void)
{
    return box_info.box_charging;
}

void sbox_left_finding_set(u8 finding)
{
    box_info.l_finding= finding;
}
u8 sbox_left_finding_get(void)
{
    return box_info.l_finding;
}

void sbox_right_finding_set(u8 finding)
{
    box_info.r_finding = finding;
}
u8 sbox_right_finding_get(void)
{
    return box_info.r_finding;
}

void sbox_box_clid_status_set(u8 status)
{
    box_info.box_clid_status = status;
}
u8 sbox_box_clid_status_get(void)
{
    return box_info.box_clid_status;
}

void sbox_low_power_set(u8 low_power)
{
    box_info.low_power = low_power;
}
u8 sbox_low_power_get(void)
{
    return box_info.low_power;
}

void sbox_phone_call_state_set(u8 state)
{
    box_info.phone_call_state = state;
}
u8 sbox_phone_call_state_get(void)
{
    return box_info.phone_call_state;
}

void sbox_phone_call_mute_set(u8 mute)
{
    box_info.phone_call_mute = mute;
}
u8 sbox_phone_call_mute_get(void)
{
    return box_info.phone_call_mute;
}

void sbox_box_year_set(u8 year)
{
    box_info.phone_time.year = year;
}
u8 sbox_box_year_get(void)
{
    return box_info.phone_time.year;
}

void sbox_box_month_set(u8 month)
{
    box_info.phone_time.month = month;
}
u8 sbox_box_month_get(void)
{
    return box_info.phone_time.month;
}
void sbox_box_day_set(u8 day)
{
    box_info.phone_time.day = day;
}
u8 sbox_box_day_get(void)
{
    return box_info.phone_time.day;
}
void sbox_box_hour_set(u8 hour)
{
    box_info.phone_time.hour = hour;
}
u8 sbox_box_hour_get(void)
{
    return box_info.phone_time.hour;
}

void sbox_box_minute_set(u8 minute)
{
    box_info.phone_time.min = minute;
}
u8 sbox_box_minute_get(void)
{
    return box_info.phone_time.min;
}
void sbox_box_second_set(u8 sec)
{
    box_info.phone_time.sec = sec;
}
u8 sbox_box_second_get(void)
{
    return box_info.phone_time.sec;
}

u8 sbox_box_time_get(struct sys_time *time)
{
    if (time == NULL) {
        printf("time is null, please check! func: %s, line: %d", __func__, __LINE__);
        return -1;
    }

    time->year = box_info.phone_time.year;
    time->month = box_info.phone_time.month;
    time->day = box_info.phone_time.day;
    time->hour = box_info.phone_time.hour;
    time->min = box_info.phone_time.min;
    time->sec = box_info.phone_time.sec;
    return 0;
}

void sbox_local_page_set(u8 page)
{
    box_info.local_page = page;
}
u8 sbox_local_page_get(void)
{
    return box_info.local_page;
}


void sbox_anc_mode_set(u8 mode)
{
    // log_info("sbox_anc_mode_set %d\n",mode);
    box_info.anc_mode = mode;
    // extern void update_all_state(int i);
	// update_all_state(0);
}

u8 sbox_anc_mode_get(void)
{
    return box_info.anc_mode;
}

void sbox_emitter_state_set(u8 state)
{
    box_info.emitter_status = state;
}

u8 sbox_emitter_state_get(void)
{
    return box_info.emitter_status;
}

void set_emitter_info(void)
{
    memcpy(s_emitter_info.emitter_addr, (void *)bt_get_mac_addr(), 6);
    // log_info("%s[line:%d]\n",__func__,__LINE__);
    // put_buf(s_emitter_info.emitter_addr, 6);
    
    
}

void sbox_r_inbox_set(u8 state)
{
    box_info.r_inbox = state;
}

u8 sbox_r_inbox_get(void)
{
    return box_info.r_inbox;
}

void sbox_l_inbox_set(u8 state)
{
    box_info.l_inbox = state;
}

u8 sbox_l_inbox_get(void)
{
    return box_info.l_inbox;
}

//播放模式用于让耳机关机
void custom_client_send_poweroff_earphone(void)
{
    u8 send_data = 1;
    custom_ble_client_write_no_respond(CUSTOM_BLE_PLAY_MODE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}

//播放闹钟
void custom_client_send_alarm_earphone(u8 cmd)
{
    u8 send_data = cmd;
    custom_ble_client_write_no_respond(CUSTOM_BLE_ALARM_CLOCK_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}

//查找耳机
/*  0x10 查找L 
    0x01 查找R 
    0x11 查找LR都查找
    0x03 查找关闭 
    0x12 闹钟响起
    */
void custom_client_send_find_earphone(u8 cmd)
{
    u8 send_data = cmd; // vol up
    custom_ble_client_write_no_respond(CUSTOM_BLE_FINE_EARPHONE_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}

//音量控制
void custom_client_send_volume_up(void)
{
    u8 send_data = 0x01; // vol up
    custom_ble_client_write_no_respond(CUSTOM_BLE_VOL_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
void custom_client_send_volume_down(void)
{
    u8 send_data = 0x02; // vol down
    custom_ble_client_write_no_respond(CUSTOM_BLE_VOL_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}

int status_tick = 0;

//设置音乐状态
#if 1
void custom_client_send_music_play(void)
{
    u8 send_data = 0x01; // play
    status_tick = lv_tick_get();
    custom_ble_client_write_no_respond(CUSTOM_BLE_MUSIC_STATE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
void custom_client_send_music_pause(void)
{
    u8 send_data = 0x02; // pause
    status_tick = lv_tick_get();
    custom_ble_client_write_no_respond(CUSTOM_BLE_MUSIC_STATE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
void custom_client_send_music_prev(void)
{
    u8 send_data = 0x03; // prev
    custom_ble_client_write_no_respond(CUSTOM_BLE_MUSIC_STATE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
void custom_client_send_music_next(void)
{
    u8 send_data = 0x04; // next
    custom_ble_client_write_no_respond(CUSTOM_BLE_MUSIC_STATE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
#endif


//设置anc
#if 1
void custom_client_send_anc_off(void)
{
    u8 send_data = 0x01; // anc off
    custom_ble_client_write_no_respond(CUSTOM_BLE_ANC_MODE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
void custom_client_send_anc_on(void)
{
    u8 send_data = 0x02; // anc on
    custom_ble_client_write_no_respond(CUSTOM_BLE_ANC_MODE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
void custom_client_send_transparency(void)
{
    u8 send_data = 0x03; // 通透
    custom_ble_client_write_no_respond(CUSTOM_BLE_ANC_MODE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
#endif

#if 1
//设置eq
// void custom_client_send_eq_off(void)
// {
//     u8 send_data = 0x00; // 关闭
//     custom_ble_client_write_no_respond(CUSTOM_BLE_EQ_MODE_CONTROL_CMD, &send_data, sizeof(send_data));
// }
void custom_client_send_eq_mode(u8 val)
{
    u8 send_data = val;
    custom_ble_client_write_no_respond(CUSTOM_BLE_EQ_MODE_CONTROL_CMD, &send_data, sizeof(send_data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, send_data);
}
#endif

//设置语言

// void custom_client_send_language(u8 data)
// {
//     u8 send_data = data +1; // 关闭
//     custom_ble_client_write_no_respond(CUSTOM_BLE_SWITCH_LANGUAGE, &send_data, sizeof(send_data));
// }


//设置接听挂断 1接听 2挂断 3mute 4mute off
void custom_client_send_call(u8 data)
{
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, data);
    custom_ble_client_write_no_respond(CUSTOM_BLE_CONTRAL_CALL, &data, sizeof(data));
}

void custom_client_send_ble_settings(u8 data)
{
    
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, data);
    custom_ble_client_write_no_respond(CUSTOM_BLE_VOL_CONTROL_CMD, &data, sizeof(data));
}
//设置耳机BLE进入 no lantacy发送  0xf1 设置 0xf0退出
void custom_client_send_ble_setting(u8 data)
{
    int msg[3];
    int err = 0;

    msg[0] = (int)custom_client_send_ble_settings;
    msg[1] = 1;
    msg[2] = (int)data;

    err = os_taskq_post_type("app_core", Q_CALLBACK, 3, msg);
    if (err) {
        printf("custom_client_send_ble_setting post fail\n");
    }
}

void ear_inbox_state_deal(u8 status)
{
    switch (status)
    {
        case 1:
            box_info.l_inbox=IN_BOX;
            // L_in ui
            y_printf("DDD- L_in");
            break;
        case 2:
            box_info.r_inbox=IN_BOX;
            y_printf("DDD- R_in");
            // R_in ui
            break;
        case 3:
            box_info.l_inbox=OUT_OF_BOX;
            y_printf("DDD- L_out");
            // L_OUT ui
            break;
        case 4:
            box_info.r_inbox=OUT_OF_BOX;
            y_printf("DDD- R_out");
            // R_OUT ui
            break;
    
    default:
        break;
    }
    log_info("ear_inbox_state_deal l:%d r:%d\n",box_info.l_inbox,box_info.r_inbox);
    // if( box_info.l_inbox){
    //     // ui_earin_enter();
    //     b_printf("ui_earin_enter()");
    // }
    
    screen_pop_up_callback_enter_filter();
}

void custom_client_send_box_all_info(void)
{
    u8 data = box_info.local_page;
    custom_ble_client_write_no_respond(CUSTOM_ALL_INFO_CMD, &data,sizeof(data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, data);
}
//0:上滑 1：下滑 2：左滑 3：右滑 4：点赞
void custom_client_send_ctrl_douyin(u8 cmd)
{
    u8 data = cmd;
    custom_ble_client_write_no_respond(CUSTOM_BLE_CONTRAL_DOUYIN, &data,sizeof(data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, data);
}

void custom_client_send_ctrl_photo(u8 cmd)
{
    u8 data = cmd;
    custom_ble_client_write_no_respond(CUSTOM_BLE_CONTRAL_PHOTO, &data,sizeof(data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, data);
}

void custom_client_send_ctrl_edr_conn(u8 cmd)
{
    u8 data = cmd;
    custom_ble_client_write_no_respond(CUSTOM_EDR_CONTRAL_CONN, &data,sizeof(data));
    log_info("%s %d send_data:%d\n", __FUNCTION__, __LINE__, data);
}

void custom_client_send_ctrl_edr_info(void)
{
    custom_ble_client_write_no_respond(CUSTOM_EDR_SYNC_INFO, &s_emitter_info,sizeof(custom_edr_info));
    log_info("%s %d \n", __FUNCTION__, __LINE__);
    // put_buf(&s_emitter_info,sizeof(custom_edr_info));
}

void ble_connect_snyc_info(void)
{
    g_printf("HJY %s[line:%d]\n",__func__,__LINE__);
    
    custom_client_send_ctrl_edr_info();
}

void smartbox_app_receive_handle(u8 cmd,u8* data,u8 len)
{
    log_info("%s cmd:%d len:%d\n",__func__,cmd,len);
    put_buf(data,len);
    switch(cmd) {
        case CUSTOM_CALL_STATE_CMD:
            log_info("CUSTOM_CALL_STATE_CMD data[0]:%d", data[0]);
            if(lcd_sleep_status()){
                lv_exit_sleep();
            }
            sbox_call_state_set(data[0]);
            if(lcd_sleep_status() && data[0] != 1 ){
                lv_exit_sleep();
            }
            break;
        case CUSTOM_ALL_INFO_CMD: { // 0xf
            log_info("CUSTOM_BT_CONNECT_STATE_CMD data[0]:%d", data[0]);
            sbox_bt_connect_flag_set(data[0]);
            sbox_equalizer_mode_set(data[1]);
            sbox_anc_mode_set(data[2]);
            sbox_music_ui_state_set(data[3]);
            sbox_volume_set(data[4]);
            sbox_battery_left_set(data[5]);
            sbox_battery_right_set(data[6]);
            // sbox_language_ui_set(data[7]);
            // UI_MSG_POST("bt_status:status=%4", data[0]); // 往ui task推消息，更新连接状态
            break;
        }
        case CUSTOM_EQ_DATE_CMD: { // 0x5
            log_info("CUSTOM_BT_CONNECT_STATE_CMD data[0]:%d", data[0]);
            sbox_equalizer_mode_set(data[0]);
            // UI_MSG_POST("bt_status:status=%4", data[0]); // 往ui task推消息，更新连接状态
            break;
        }
        case CUSTOM_ANC_DATE_CMD: { // 0x6
            log_info("CUSTOM_BT_CONNECT_STATE_CMD data[0]:%d", data[0]);
            sbox_anc_mode_set(data[0]);
            // UI_MSG_POST("bt_status:status=%4", data[0]); // 往ui task推消息，更新连接状态
            break;
        }
        case CUSTOM_BT_CONNECT_STATE_CMD: { // 0x1
            log_info("CUSTOM_BT_CONNECT_STATE_CMD data[0]:%d", data[0]);
            sbox_bt_connect_flag_set(data[0]);
            // UI_MSG_POST("bt_status:status=%4", data[0]); // 往ui task推消息，更新连接状态
            break;
        }
        case CUSTOM_BLE_CONNECT_STATE_CMD: { // 0x2
            log_info("CUSTOM_BLE_CONNECT_STATE_CMD data[0]:%d", data[0]);
            // UI_MSG_POST("ble_status:status=%4", data[0]);
            break;
        }
        case CUSTOM_BLE_BATTERY_STATE_CMD: { // 0x3
            log_info("CUSTOM_BLE_BATTERY_STATE_CMD data[L]:%d.data[R]:%d", data[0], data[1]);
            // todo  更新电量值
            sbox_battery_left_set(data[0]);
            sbox_battery_right_set(data[1]);
            // UI_MSG_POST("vbat_status");
            break;
        }
        case CUSTOM_BLE_VOLUMEN_CMD: { // 0x4
            log_info("CUSTOM_BLE_VOLUMEN_CMD data[0]:%d", data[0]);
            sbox_volume_set(data[0]);
            // UI_MSG_POST("vol_status:volume=%4", data[0]);
            break;
        }
        case CUSTOM_BLE_TIME_DATE_CMD:
            log_info("CUSTOM_BLE_TIME_DATE_CMD:");
            box_info.phone_time.year = (data[1]<<8) +data[0];
            box_info.phone_time.month = data[2];
            box_info.phone_time.day = data[3];
            box_info.phone_time.hour = data[4];
            box_info.phone_time.min = data[5];
            box_info.phone_time.sec = data[6];
            b_printf("box_info.phone_time.year: %d", (data[1]<<8) +data[0]);

            struct sys_time time = {0};
            time.year = box_info.phone_time.year;
            time.month = box_info.phone_time.month;
            time.day = box_info.phone_time.day;
            time.hour = box_info.phone_time.hour;
            time.min = box_info.phone_time.min;
            time.sec = box_info.phone_time.sec;
            // lvgl_time_update(&time);
            extern void sbox_set_sys_time(struct sys_time *time);
            printf("update YMS HMS: %04d/%d/%d %d-%d-%d", time.year, time.month, time.day, time.hour, time.month, time.sec);
            sbox_set_sys_time(&time);
        //     // todo
            break;
        // }

        case CUSTOM_BLE_MUSIC_STATE_CONTROL_CMD: { // 0x33
            log_info("CUSTOM_BLE_MUSIC_STATE_CONTROL_CMD data[0]:%d", data[0]);
            sbox_music_ui_state_set(data[0]);
        }
        case CUSTOM_BLE_ANC_MODE_CONTROL_CMD: { // 0x34
#if TCFG_AUDIO_ANC_ENABLE
            if (data[0] == 0x01) { // ANC on
                anc_mode_switch(ANC_ON, ANC_USER_TRAIN_TONE_MODE); // 默认需要播提示音
            } else if (data[0] == 0x02) { // 通透
                anc_mode_switch(ANC_TRANSPARENCY, ANC_USER_TRAIN_TONE_MODE);
            } else {
                anc_mode_switch(ANC_OFF, ANC_USER_TRAIN_TONE_MODE);
                log_info("CUSTOM_BLE_ANC_MODE_CONTROL_CMD volue:%x valid!!!!\n", data[0]);
            }
#endif
            break;
        }
        case CUSTOM_BLE_EQ_MODE_CONTROL_CMD: { // 0x35
            // todo
            if (data[0] == 0x01) { // eq效果1

            } else if (data[0] == 0x02) { // eq效果2

            } else if (data[0] == 0x02) { // eq效果3

            } else {
                log_info("CUSTOM_BLE_VOL_CONTROL_CMD volue:%x valid!!!!\n", data[0]);
            }
            break;
        }
        default:
            log_info("ble_notify_recv_data_handler cmd err:%d", cmd);
            break;
    }
}
    // u8 *buffers;
 
int ble_recv_musicdata_handler(uint8_t *buffer, uint16_t buffer_size)
{
    if(buffer[0]==0xee &&buffer[1]==0xbb && buffer[4]==0x2 && buffer[6]==0x3)
    {
        int offset=10;
        struct custom_music_info *local_music_infos=&local_music_info;
        log_info("ble_recv_musicdata_handler\n");
        local_music_infos->type_artist_name = buffer[4];
        local_music_infos->name_len = buffer[5];
        local_music_infos->type_album_name = buffer[6];
        local_music_infos->album_len = buffer[7];
        local_music_infos->type_title = buffer[8];
        local_music_infos->title_len = buffer[9];
        
        memcpy(local_music_infos->artist_name,buffer+offset,local_music_infos->name_len);offset+=local_music_infos->name_len;
        memcpy(local_music_infos->album_name,buffer+offset,local_music_infos->album_len);offset+=local_music_infos->album_len;
        memcpy(local_music_infos->title,buffer+offset,local_music_infos->title_len);offset+=local_music_infos->title_len;

        memset(lyrics_artist_name_array, 0, sizeof(lyrics_artist_name_array));
        memset(lyrics_content_array, 0, sizeof(lyrics_content_array));
        memcpy(lyrics_artist_name_array, local_music_infos->artist_name, local_music_infos->name_len);
        memcpy(lyrics_content_array, local_music_infos->title, local_music_infos->title_len);
        b_printf("\r\nlyrics_content_array: %s\r\nlyrics_artist_name_array: %s", lyrics_content_array, lyrics_artist_name_array);

        log_info("ble_recv_musicdata_handler\n");
        log_info("artist_name:%s\n",local_music_infos->artist_name);
        log_info("album_name:%s\n",local_music_infos->album_name);
        log_info("title:%s\n",local_music_infos->title);

        memset(local_music_infos->artist_name, 0, local_music_infos->name_len);
        memset(local_music_infos->album_name, 0, local_music_infos->album_len);
        memset(local_music_infos->title, 0, local_music_infos->title_len);

#if 0
        str_queue_in(lyrics_queue, local_music_infos->title);
        str_queue_printf();

        extern void lv_lyrics_update_content();

        int msg[2] = {0};
        msg[0] = (int)lv_lyrics_update_content;
        msg[1] = 1;
        do {
            int os_err = os_taskq_post_type("ui", Q_CALLBACK, 2, msg);
            if(os_err) {
                printf("lv_lyrics_update_content fail, err type: %d", os_err);
            }
        } while (0);
#endif
        return 1;
    }
    return 0;
}


#define ATT_CHARACTERISTIC_ae01_01_VALUE_HANDLE 0x0082 // 对应跟耳机uuid WRITE_WITHOUT_RESPONSE VALUE
static u8 send_buf[16];
typedef struct {
    uint16_t read_handle;
    uint16_t read_long_handle;
    uint16_t write_handle;
    uint16_t write_no_respond;
    uint16_t notify_handle;
    uint16_t indicate_handle;
} target_hdl_t;

extern target_hdl_t target_handle[];
extern s8 cur_dev_cid;

int custom_client_write_without_respond_send(void *priv, u8 *data, u16 len)
{
    target_handle[cur_dev_cid].write_no_respond = ATT_CHARACTERISTIC_ae01_01_VALUE_HANDLE;
    return custom_app_send_ble_data(target_handle[cur_dev_cid].write_no_respond, data, len, ATT_OP_WRITE_WITHOUT_RESPOND);
}

