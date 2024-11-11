#ifndef SMARTBOX_USER_APP_H
#define SMARTBOX_USER_APP_H


#include "app_config.h"
// #include "includes.h" // 注释掉，否则文件系统结构体重定义，与ui冲突
// #include "ui/ui_api.h"
// #include "ui/ui.h"
#include "res/mem_var.h"
#include "typedef.h"
#include "clock_cfg.h"
#include "app_task.h"
#include "btstack/avctp_user.h"
#include "key_event_deal.h"
#include "sys_time.h"

#define SBOX_MENU_TASK_NAME  "sbox_data"

struct s_box_info {
    u8 phone_state ;                // 手机连接状态，0:不连接 1：连接
    u8 earphone_state;              // 耳机连接状态，0:不连接 1：连接
    u8 l_ear_bat ;                  // L耳电量 
    u8 r_ear_bat ;                  // R耳电量
    u8 l_inbox;                     // L耳入仓
    u8 r_inbox;                     // R耳入仓
    s8 box_bat ;                    // 充电仓电量
    u8 music_state;                 // 耳机播放状态
    u8 earphone_vol ;               // 耳机音量
    u8 anc_mode ;                   // anc模式，0关 1开 2通透
    u8 eq_mode;                     // eq模式
    u8 ui_bl_levl;                  // 仓背光亮度
    u8 l_charging;                  // L耳充电状态
    u8 r_charging;                  // R耳充电状态
    u8 box_charging;                // 充电仓充电状态
    u8 l_finding;                   // 查找L耳
    u8 r_finding;                   // 查找R耳
    u8 box_clid_status;             // 充电仓开关盖状态
    u8 language;                    // 语言
    u8 low_power;                   // 低电状态
    u8 phone_call_state;            // 通话状态
    u8 phone_call_mute;             // 通话是否静音
    u8 local_page;                  // 本地页面记录
    u8 emitter_status;              // 蓝牙发射器状态
    struct sys_time phone_time;     // 系统时间
};
struct custom_music_info{
    u16 time;
    u8 type_artist_name;
    u8 name_len;
    u8 type_album_name;
    u8 album_len;
    u8 type_title;
    u8 title_len;
    u8 artist_name[256];
    u8 album_name[256];
    u8 title[256];
};
typedef struct __custom_edr_info
{
    u8 emitter_addr[6];

}custom_edr_info __attribute__((aligned(4)));

extern struct s_box_info box_info;
extern struct custom_music_info local_music_info;
/*----------------协议格式--------------------*/
#define CUSTOM_BLE_PROTOCOL_HEADER1     0x5a
#define CUSTOM_BLE_PROTOCOL_HEADER2     0xa5
#define CUSTOM_BLE_PROTOCOL_HEADER      0 // 2Byte
#define CUSTOM_BLE_PROTOCOL_LENGTH      2 // 1Byte
#define CUSTOM_BLE_PROTOCOL_CMD         3 // 1Byte
#define CUSTOM_BLE_PROTOCOL_VALUE       4 // nByte
/*----------------协议格式--------------------*/

/*-------------------CMD start----------------------*/
#define CUSTOM_ALL_INFO_CMD                             0xff  // 所有信息
#define CUSTOM_BT_CONNECT_STATE_CMD                     0x1  // bt连接状态
#define CUSTOM_BLE_CONNECT_STATE_CMD                    0x2  // ble连接状态
#define CUSTOM_BLE_BATTERY_STATE_CMD                    0x3  // 电量信息
#define CUSTOM_BLE_VOLUMEN_CMD                          0x4  // 音量信息
#define CUSTOM_BLE_TIME_DATE_CMD                        0x5  // 时间信息
#define CUSTOM_EQ_DATE_CMD                              0x6  // EQ信息
#define CUSTOM_ANC_DATE_CMD                             0x7  // ANC信息
#define CUSTOM_CALL_STATE_CMD                           0x8  //通话状态获取
#define CUSTOM_MUSIC_INFO_CMD                           0x9    //播放音乐信息

#define CUSTOM_BLE_VOL_CONTROL_CMD                      0x32 // 音量控制
#define CUSTOM_BLE_MUSIC_STATE_CONTROL_CMD              0x33 // 音乐状态控制
#define CUSTOM_BLE_ANC_MODE_CONTROL_CMD                 0x34 // ANC 模式控制
#define CUSTOM_BLE_EQ_MODE_CONTROL_CMD                  0x35 // EQ 模式控制
#define CUSTOM_BLE_PLAY_MODE_CONTROL_CMD                0x36 // 设置播放模式
#define CUSTOM_BLE_ALARM_CLOCK_CONTROL_CMD              0x37 // 播放闹钟
#define CUSTOM_BLE_FINE_EARPHONE_CMD                    0x38 // 查找手机
#define CUSTOM_BLE_FLASHLIGHT_CONTROL_CMD               0x39 // 手电筒
#define CUSTOM_BLE_SWITCH_LANGUAGE                      0x40 //切换语言 1中文，2英文
#define CUSTOM_BLE_CONTRAL_CALL                         0x41 //控制接听挂断  1接听 2挂断
#define CUSTOM_BLE_USER_ADD_CMD                         0X42 //用户自定义命令
#define CUSTOM_BLE_CONTRAL_DOUYIN                       0X43  //控制抖音操作  
#define CUSTOM_BLE_CONTRAL_PHOTO                        0X44  //控制拍照操作

#define CUSTOM_EDR_CONTRAL_CONN                         0X45  //控制edr连接
#define CUSTOM_EDR_SYNC_INFO                            0X46  //同步经典蓝牙信息




/*-------------------CMD end----------------------*/



void custom_client_send_volume_up(void);
void custom_client_send_volume_down(void);

void custom_client_send_music_play(void);
void custom_client_send_music_pause(void);
void custom_client_send_music_prev(void);
void custom_client_send_music_next(void);
void custom_client_send_find_earphone(u8 cmd);
void custom_client_send_anc_off(void);
void custom_client_send_anc_on(void);
void custom_client_send_transparency(void);

void custom_client_send_eq_off(void);
void custom_client_send_eq_mode(u8 val);
void custom_client_send_poweroff_earphone(void);

void custom_client_send_call(u8 data);

void custom_client_send_alarm_earphone(u8 cmd);

void custom_client_send_ble_setting(u8 data);
void custom_client_send_box_all_info(void);
void custom_client_send_ctrl_douyin(u8 cmd);
void custom_client_send_ctrl_photo(u8 cmd);



u8 sbox_bt_connect_flag_get(void);
u8 sbox_ble_connect_flag_get(void);
u8 sbox_battery_left_get(void);
u8 sbox_battery_right_get(void);
u8 sbox_battery_box_get(void);
u8 sbox_music_ui_state_get(void);
u8 sbox_volume_get(void);
u8 sbox_anc_mode_get(void);
u8 sbox_equalizer_mode_get(void);
u8 sbox_backlight_level_get(void);
u8 sbox_left_charging_get(void);
u8 sbox_right_charging_get(void);
u8 sbox_box_charging_get(void);
u8 sbox_left_finding_get(void);
u8 sbox_right_finding_get(void);
u8 sbox_box_clid_status_get(void);
u8 sbox_language_ui_get(void);
u8 sbox_low_power_get(void);
u8 sbox_phone_call_state_get(void);
u8 sbox_phone_call_mute_get(void);
u8 sbox_box_hour_get(void);
u8 sbox_box_minute_get(void);
u8 sbox_box_second_get(void);
u8 sbox_box_time_get(struct sys_time *time);
u8 sbox_local_page_get(void);
u8 sbox_emitter_state_get(void);
u8 sbox_r_inbox_get(void);
u8 sbox_l_inbox_get(void);

void sbox_bt_connect_flag_set(u8 data);
void sbox_ble_connect_flag_set(u8 data);
void sbox_battery_left_set(u8 data);
void sbox_battery_right_set(u8 data);
void sbox_battery_box_set(u8 data);
void sbox_music_ui_state_set(u8 data);
void sbox_volume_set(u8 data);
void sbox_anc_mode_set(u8 data);
void sbox_equalizer_mode_set(u8 data);
void sbox_backlight_level_set(u8 data);
void sbox_left_charging_set(u8 data);
void sbox_right_charging_set(u8 data);
void sbox_box_charging_set(u8 data);
void sbox_left_finding_set(u8 data);
void sbox_right_finding_set(u8 data);
void sbox_box_clid_status_set(u8 data);
void sbox_language_ui_set(u8 data);
void sbox_low_power_set(u8 data);
void sbox_phone_call_state_set(u8 data);
void sbox_phone_call_mute_set(u8 data);
void sbox_box_year_set(u8 data);
void sbox_box_month_set(u8 data);
void sbox_box_day_set(u8 data);
void sbox_box_hour_set(u8 data);
void sbox_box_minute_set(u8 data);
void sbox_box_second_set(u8 data);
void sbox_local_page_set(u8 data);
void sbox_emitter_state_set(u8 state);
void sbox_r_inbox_set(u8 state);
void sbox_l_inbox_set(u8 state);

void custom_client_send_ctrl_edr_info(void);
void set_emitter_info(void);
void custom_client_send_ctrl_edr_conn(u8 cmd);

int ble_notify_recv_data_handler(uint8_t *buffer, uint16_t buffer_size);
int ble_recv_musicdata_handler(uint8_t *buffer, uint16_t buffer_size);
#endif
