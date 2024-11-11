#include "events_adapter.h"
#include "widgets_init.h"
#include "uart_test.h"
#include "events_init.h"


struct s_box_info_base_cb box_info_base_cb = {
    .lv_phone_state_get         = sbox_bt_connect_flag_get,     
    .lv_earphone_state_get      = sbox_ble_connect_flag_get,    
    .lv_l_ear_bat_get           = sbox_battery_left_get,
    .lv_r_ear_bat_get           = sbox_battery_right_get,
    .lv_box_bat_get             = sbox_battery_box_get,
    .lv_music_state_get         = sbox_music_ui_state_get,
    .lv_earphone_vol_get        = sbox_volume_get,
    .lv_anc_mode_get            = sbox_anc_mode_get,
    .lv_eq_mode_get             = sbox_equalizer_mode_get,
    .lv_ui_bl_levl_get          = sbox_backlight_level_get,
    .lv_l_charging_get          = sbox_left_charging_get,
    .lv_r_charging_get          = sbox_right_charging_get,
    .lv_box_charging_get        = sbox_box_charging_get,
    .lv_l_finding_get           = sbox_left_finding_get,
    .lv_r_finding_get           = sbox_right_finding_get,
    .lv_box_clid_status_get     = sbox_box_clid_status_get,
    .lv_language_get            = sbox_language_ui_get,
    .lv_low_power_get           = sbox_low_power_get,
    .lv_phone_call_state_get    = sbox_phone_call_state_get,
    .lv_phone_call_mute_get     = sbox_phone_call_mute_get,
    .lv_box_hour_get            = sbox_box_hour_get,
    .lv_box_minute_get          = sbox_box_minute_get,
    .lv_box_second_get          = sbox_box_second_get,
    .lv_box_time_get            = sbox_box_time_get,
    .lv_local_page_get          = sbox_local_page_get,
    .lv_emitter_state_get       = sbox_emitter_state_get,
    .lv_r_inbox_get             = sbox_r_inbox_get,
    .lv_l_inbox_get             = sbox_l_inbox_get,

    .lv_phone_state_set         = sbox_bt_connect_flag_set,
    .lv_earphone_state_set      = sbox_ble_connect_flag_set,
    .lv_l_ear_bat_set           = sbox_battery_left_set,
    .lv_r_ear_bat_set           = sbox_battery_right_set,
    .lv_box_bat_set             = sbox_battery_box_set,
    .lv_music_state_set         = sbox_music_ui_state_set,
    .lv_earphone_vol_set        = sbox_volume_set,
    .lv_anc_mode_set            = sbox_anc_mode_set,
    .lv_eq_mode_set             = sbox_equalizer_mode_set,
    .lv_ui_bl_levl_set          = sbox_backlight_level_set,
    .lv_l_charging_set          = sbox_left_charging_set,
    .lv_r_charging_set          = sbox_right_charging_set,
    .lv_box_charging_set        = sbox_box_charging_set,
    .lv_l_finding_set           = sbox_left_finding_set,
    .lv_r_finding_set           = sbox_right_finding_set,
    .lv_box_clid_status_set     = sbox_box_clid_status_set,
    .lv_language_set            = sbox_language_ui_set,
    .lv_low_power_set           = sbox_low_power_set,
    .lv_phone_call_state_set    = sbox_phone_call_state_set,
    .lv_phone_call_mute_set     = sbox_phone_call_mute_set,
    .lv_box_hour_set            = sbox_box_hour_set,
    .lv_box_minute_set          = sbox_box_minute_set,
    .lv_local_page_set          = sbox_local_page_set,
    .lv_emitter_state_set       = sbox_emitter_state_set,
    .lv_r_inbox_set             = sbox_r_inbox_set,
    .lv_l_inbox_set             = sbox_l_inbox_set,

    .lv_storage_mode_enter      = sbox_storage_mode_enter,
};

struct s_box_info_send_cb box_info_send_cb = {
    .lv_earphone_poweroff_cmd_send = custom_client_send_poweroff_earphone,     // 播放模式用于让耳机关机
    .lv_alarm_ring_cmd_send        = custom_client_send_alarm_earphone,        // 播放闹钟
    .lv_find_my_cmd_send           = custom_client_send_find_earphone,         // 查找耳机
    .lv_volume_up_cmd_send         = custom_client_send_volume_up,             // 音量增加
    .lv_volume_down_cmd_send       = custom_client_send_volume_down,           // 音量减小
    .lv_music_play_cmd_send        = custom_client_send_music_play,            // 播放
    .lv_music_pause_cmd_send       = custom_client_send_music_pause,           // 暂停
    .lv_music_prev_cmd_send        = custom_client_send_music_prev,            // 上一首
    .lv_music_next_cmd_send        = custom_client_send_music_next,            // 下一首
    .lv_anc_on_cmd_send            = custom_client_send_anc_on,                // ANC 打开
    .lv_anc_off_cmd_send           = custom_client_send_anc_off,               // ANC 关闭
    .lv_transparency_cmd_send      = custom_client_send_transparency,          // 通透模式
    .lv_eq_mode_cmd_send           = custom_client_send_eq_mode,               // EQ 模式控制
    .lv_call_status_cmd_send       = custom_client_send_call,                  // 设置接听挂断
    .lv_ble_setting_cmd_send       = custom_client_send_ble_setting,           // 设置耳机BLE进入no lantacy发送  
    .lv_box_all_info_cmd_send      = custom_client_send_box_all_info,          // 信息同步
    .lv_tiktok_pre_cmd_send        = custom_client_send_tiktok_pre,            // 抖音上一个
    .lv_tiktok_next_cmd_send       = custom_client_send_tiktok_next,           // 抖音下一个
    .lv_tiktok_like_cmd_send       = custom_client_send_tiktok_like,           // 抖音点赞
    .lv_snap_cmd_send              = custom_client_send_snap,                  // 拍照
    .lv_language_switch_cmd_send   = NULL,                                     // 切换语言
    .lv_user_add_cmd_send          = NULL,                                     // 用户自定义命令
};




