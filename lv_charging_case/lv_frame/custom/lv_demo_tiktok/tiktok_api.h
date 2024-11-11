#ifndef __TIKTOK_API_H_
#define __TIKTOK_API_H_

#include "smartbox_user_app.h"

enum {
    TIKTOK_UP,
    TIKTOK_DOWN,
    TIKTOK_LEFT,
    TIKTOK_RIGHT,
    TIKTOK_LIKE,
};

void custom_client_send_tiktok_pre();
void custom_client_send_tiktok_next();
void custom_client_send_tiktok_like();

#endif /* __TIKTOK_API_H_ */