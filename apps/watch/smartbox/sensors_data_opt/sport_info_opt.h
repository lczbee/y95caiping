#ifndef __SMARTBOX_SPORT_INFO_OPT_H__
#define __SMARTBOX_SPORT_INFO_OPT_H__

#include "typedef.h"
#include "app_config.h"

enum {
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_RESERVE,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_SENSOR_OPT,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_SEDENTARY,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_CONTINUOUS_HEART_RATE,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_EXERCISE_HEART_RATE,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_PRESSURE_DETECTION,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_SLEEP_DETECTION,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_FALL_DETECTION,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_RAISE_WRIST,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_PERSONAL_INFO,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_BT_DISCONN,
    SPORTS_INFO_OPT_FUNC_ATTR_TYPE_MAX,
};

// 开关
enum {
    SPORT_INFO_SWTICH_TYPE_SENSOR,
    // 传感器功能
    SPORT_INFO_SWTICH_TYPE_SENSOR_PEDOMETER,
    SPORT_INFO_SWTICH_TYPE_SENSOR_PEDOMETER_RECORD,
    SPORT_INFO_SWTICH_TYPE_SENSOR_HEART_RATE,
    SPORT_INFO_SWTICH_TYPE_SENSOR_HEART_RATE_RECORD,
    SPORT_INFO_SWTICH_TYPE_SENSOR_BLOOD_OXYGEN,
    SPORT_INFO_SWTICH_TYPE_SENSOR_BLOOD_OXYGEN_RECORD,
    SPORT_INFO_SWTICH_TYPE_SENSOR_ALTITUDE,

    SPORT_INFO_SWTICH_TYPE_SENSOR_ALTITUDE_RECORD,//8
    // 久坐提醒
    SPORT_INFO_SWTICH_TYPE_SEDENTARY,
    // 连续测量心率
    SPORT_INFO_SWTICH_TYPE_CONTINUOUS_HEART_RATE,
    // 运动心率
    SPORT_INFO_SWTICH_TYPE_EXERCISE_HEART_RATE,
    // 压力自动检测
    SPORT_INFO_SWTICH_TYPE_PRESSURE_DETECTION,
    // 睡眠检测
    SPORT_INFO_SWTICH_TYPE_SLEEP_DETECTION,
    // 跌倒检测
    SPORT_INFO_SWTICH_TYPE_FALL_DETECTION,
    // 抬腕检测
    SPORT_INFO_SWTICH_TYPE_RAISE_WRIST,
    // 蓝牙断开提示
    SPORT_INFO_SWTICH_TYPE_BT_DISCONN,
    // 当前最大值
    SPORT_INFO_SWITCH_TYPE_END,
};

// 开关类型扩展
enum SPORT_INFO_SWITCH_EXPAND_TYPE {
    // 睡眠检测 - 自定义时间段
    SPORT_INFO_SWTICH_TYPE_SLEEP_DETECTION_CUSTOMIZE = SPORT_INFO_SWITCH_TYPE_END,
    // 抬腕检测 - 自定义时间段
    SPORT_INFO_SWTICH_TYPE_RAISE_WRIST_CUSTOMIZE,
    // 最大值，不超过31
    SPORT_INFO_SWTICH_TYPE_MAX,
};

// 模式
enum {
    // 久坐提醒
    SPORT_INFO_MODE_TYPE_SEDENTARY,
    // 连续心率
    SPORT_INFO_MODE_TYPE_CONTINUOUS_HEART_RATE,
    // 压力检测
    SPORT_INFO_MODE_TYPE_PRESSURE_DETECTION,
    // 跌倒检测
    SPORT_INFO_MODE_TYPE_FALL_DETECTION,
    // 抬碗检测
    SPORT_INFO_MODE_TYPE_RAISE_WRIST,
    // 蓝牙断开提示
    SPORT_INFO_MODE_TYPE_BT_DISCONN,
    // 最大值
    SPORT_INFO_MODE_TYPE_MAX,
};

int JL_smartbox_sports_info_funciton(void *priv, u8 OpCode, u8 OpCode_SN, u8 *data, u16 len);
void sport_info_opt_update(u32 mask);

int sport_info_write_vm(int vm_id, u8 *data, u16 data_len);
int sport_info_read_vm(int vm_id, u8 *data, u16 data_len);

void sport_info_switch_record_update(u8 switch_type, u8 switch_state, u8 write_vm);
u32 sport_info_swtich_record_get(u8 switch_type);
void sport_info_mode_record_update(u8 mode_type, u8 mode);
u16 sport_info_record_get(u8 mode_type, u8 *mode_data[]);


#endif
