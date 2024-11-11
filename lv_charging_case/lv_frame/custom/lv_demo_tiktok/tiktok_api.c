#include "tiktok_api.h"

// 抖音左按键
void custom_client_send_tiktok_pre()
{
    // 发送上划指令
    custom_client_send_ctrl_douyin(TIKTOK_UP);
}

// 抖音右按键
void custom_client_send_tiktok_next()
{
    // 发送下划指令
    custom_client_send_ctrl_douyin(TIKTOK_DOWN);
}

// 抖音点赞按键
void custom_client_send_tiktok_like()
{
    // 发送点赞指令
    custom_client_send_ctrl_douyin(TIKTOK_LIKE);
}

