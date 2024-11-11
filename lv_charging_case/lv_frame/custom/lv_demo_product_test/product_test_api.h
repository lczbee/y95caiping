#ifndef __PRODUCT_TEST_API_H_
#define __PRODUCT_TEST_API_H_

#include "events_adapter.h"
#include "syscfg_id.h"

void sbox_storage_mode_enter();

void sbox_poweroff_enter(u8 mode);

void sbox_connect_test();

enum {
    POWEROFF_MODE_NORMAL = 0,   // 普通关机
    POWEROFF_MODE_STORAGE,      // 进入仓储模式
};

#endif /* __TIKTOK_API_H_ */