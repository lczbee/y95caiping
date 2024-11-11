#ifndef EVENTS_ADAPTER_H_
#define EVENTS_ADAPTER_H_
#ifdef __cplusplus
extern "C" {
#endif



// #include "ui/ui_api.h"
// #include "ui/ui.h"
#include "events_init.h"
#include "smartbox_user_app.h"
#include "lv_demo_tiktok/tiktok_api.h"
#include "lv_demo_snap/snap_api.h"
#include "lv_demo_alarm/alarm_api.h"
#include "lv_demo_product_test/product_test_api.h"
void usr_screen_on(u8 on);




// UI >>> 蓝牙
typedef enum {
    LV_EQ_MODE_NORMAL = 0,
    LV_EQ_MODE_ROCK,
    LV_EQ_MODE_POP,
    LV_EQ_MODE_CLASSIC,
    LV_EQ_MODE_JAZZ,
} LV_EQ_MODE;

typedef enum {
    CALL_CONTROL_ANSWER = 1,
    CALL_CONTROL_HANG_UP,
} CALL_CONTROL;

typedef enum {
    LANGUAGE_CHINESE = 1,
    LANGUAGE_ENGLISH,
} LANGUAGE_LIST;

#define CMD_FIND_MY_L   (0x10)
#define CMD_FIND_MY_R   (0x01) 
#define CMD_FIND_MY_LR  (0x11)
#define CMD_FIND_CLOSE  (0x03)

#define CMD_ALARM_RING  (0x12)

#define CMD_BLE_NO_LANTACY_ON   (0xf1)
#define CMD_BLE_NO_LANTACY_OFF  (0xf0)

struct s_box_info_send_cb {
    // 播放模式用于让耳机关机
    void (*lv_earphone_poweroff_cmd_send)(void);   // 0x12 闹钟响起

    // 播放闹钟
    void (*lv_alarm_ring_cmd_send)(u8 data);        // 0x12 闹钟响起

    // 查找耳机
    void (*lv_find_my_cmd_send)(u8 data);           // 0x10查找L | 0x01查找R | 0x11查找LR | 0x03查找关闭 

    // 音量
    void (*lv_volume_up_cmd_send)(void);           // 音量增加
    void (*lv_volume_down_cmd_send)(void);         // 音量减小

    // 音乐
    void (*lv_music_play_cmd_send)(void);          // 播放
    void (*lv_music_pause_cmd_send)(void);         // 暂停
    void (*lv_music_prev_cmd_send)(void);          // 上一首
    void (*lv_music_next_cmd_send)(void);          // 下一首

    //设置ANC
    void (*lv_anc_on_cmd_send)(void);              // ANC 打开
    void (*lv_anc_off_cmd_send)(void);             // ANC 关闭
    void (*lv_transparency_cmd_send)(void);        // 通透模式

    // EQ 模式控制
    void (*lv_eq_mode_cmd_send)(LV_EQ_MODE data);

    //设置接听挂断
    void (*lv_call_status_cmd_send)(CALL_CONTROL data);    // 控制接听挂断  1接听 2挂断

    //设置耳机BLE进入 no lantacy发送  
    void (*lv_ble_setting_cmd_send)(u8 data);      // 0xf1 设置 0xf0退出
    void (*lv_box_all_info_cmd_send)(void);

    //抖音控制
    void (*lv_tiktok_pre_cmd_send)(void);          // 抖音上一个
    void (*lv_tiktok_next_cmd_send)(void);         // 抖音下一个
    void (*lv_tiktok_like_cmd_send)(void);         // 抖音点赞

    // 拍照
    void (*lv_snap_cmd_send)(void);           // 拍照
    
    // 切换语言
    void (*lv_language_switch_cmd_send)(LANGUAGE_LIST data);    // 1中文，2英文

    // 用户自定义命令
    void (*lv_user_add_cmd_send)(void);
};

extern struct s_box_info_send_cb box_info_send_cb;







// 蓝牙 >>> UI
typedef enum {
    CALL_STATUS_HANGUP = 1,
    CALL_STATUS_INCOME,
    CALL_STATUS_ACTIVE,
} CALL_STATUS;


typedef enum {
    BLE_DISCONNET = 0,
    BLE_CONNECTED,
} BLE_STATUS;

typedef enum {
    BT_DISCONNET = 0,
    BT_CONNECTED,
} BT_STATUS;


typedef enum {
    ANC_STATUS_CLOSE = 0,
    ANC_STATUS_OPEN,
    ANC_STATUS_TRANSPARENCY,
} ANC_STATUS;

typedef enum {
    MUSIC_STATE_NULL = 0,
    MUSIC_STATE_PLAY, //音乐播放
    MUSIC_STATE_PAUSE, //音乐暂停
} MUSIC_STATUS;



struct s_box_info_base_cb {
    u8 (*lv_phone_state_get)(void);
    u8 (*lv_earphone_state_get)(void);
    u8 (*lv_l_ear_bat_get)(void);
    u8 (*lv_r_ear_bat_get)(void);
    u8 (*lv_box_bat_get)(void);
    u8 (*lv_music_state_get)(void);
    u8 (*lv_earphone_vol_get)(void);
    u8 (*lv_anc_mode_get)(void);
    u8 (*lv_eq_mode_get)(void);
    u8 (*lv_ui_bl_levl_get)(void);
    u8 (*lv_l_charging_get)(void);
    u8 (*lv_r_charging_get)(void);
    u8 (*lv_box_charging_get)(void);
    u8 (*lv_l_finding_get)(void);
    u8 (*lv_r_finding_get)(void);
    u8 (*lv_box_clid_status_get)(void);
    u8 (*lv_language_get)(void);
    u8 (*lv_low_power_get)(void);
    u8 (*lv_phone_call_state_get)(void);
    u8 (*lv_phone_call_mute_get)(void);
    u8 (*lv_box_hour_get)(void);
    u8 (*lv_box_minute_get)(void);
    u8 (*lv_box_second_get)(void);
    u8 (*lv_box_time_get)(void *time);
    u8 (*lv_local_page_get)(void);
    u8 (*lv_emitter_state_get)(void);
    u8 (*lv_r_inbox_get)(void);
    u8 (*lv_l_inbox_get)(void);

    void (*lv_phone_state_set)(u8 data);
    void (*lv_earphone_state_set)(u8 data);
    void (*lv_l_ear_bat_set)(u8 data);
    void (*lv_r_ear_bat_set)(u8 data);
    void (*lv_box_bat_set)(u8 data);
    void (*lv_music_state_set)(u8 data);
    void (*lv_earphone_vol_set)(u8 data);
    void (*lv_anc_mode_set)(u8 data);
    void (*lv_eq_mode_set)(u8 data);
    void (*lv_ui_bl_levl_set)(u8 data);
    void (*lv_l_charging_set)(u8 data);
    void (*lv_r_charging_set)(u8 data);
    void (*lv_box_charging_set)(u8 data);
    void (*lv_l_finding_set)(u8 data);
    void (*lv_r_finding_set)(u8 data);
    void (*lv_box_clid_status_set)(u8 data);
    void (*lv_language_set)(u8 data);
    void (*lv_low_power_set)(u8 data);
    void (*lv_phone_call_state_set)(u8 data);
    void (*lv_phone_call_mute_set)(u8 data);
    void (*lv_box_hour_set)(u8 data);
    void (*lv_box_minute_set)(u8 data);
    void (*lv_local_page_set)(u8 data);
    void (*lv_emitter_state_set)(u8 state);
    void (*lv_r_inbox_set)(void);
    void (*lv_l_inbox_set)(void);

    void (*lv_storage_mode_enter)(void);
};
extern struct s_box_info_base_cb box_info_base_cb;

enum {
    UI_MSG_OTHER,
    UI_MSG_KEY,
    UI_MSG_TOUCH,
    UI_MSG_SHOW,
    UI_MSG_HIDE,
    UI_MSG_UPDATE,
};

enum {
    BR_INIT,
    BR_CONNECTED,
    BR_DISCONNECTED,
    BR_PAGE_TIMEROUT,
    BR_EXIT,
};

enum {
    UI_UPDATE_TIME,
    UI_UPDATE_BR_STATUS,
};

enum {
    LOCAL_PLAY_PC_MUSIC_PREV,
    LOCAL_PLAY_PC_MUSIC_NEXT,
    LOCAL_PLAY_PC_MUSIC_PP,
    LOCAL_PLAY_PC_CLOSE,
    LOCAL_PLAY_PC_START,
    LOCAL_PLAY_PC_STOP,
    LOCAL_PLAY_MUSIC_MODE,
    LOCAL_PLAY_MASK_MODE,

};

#ifdef __cplusplus
}
#endif
#endif /* EVENTS_ADAPTER_H_ */