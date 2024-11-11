#ifndef UART_TEST_H
#define UART_TEST_H

#include "app_config.h"
#include "includes.h"
#include "ui/ui_api.h"
#include "ui/ui.h"
#include "res/mem_var.h"
#include "typedef.h"
#include "clock_cfg.h"
#include "app_task.h"
#include "btstack/avctp_user.h"
#include "key_event_deal.h"

#include "uart.h"
#include "uart_types.h"

typedef struct {
    u8 magic_1;
    u8 magic_2;
    u8 type;
    u8 direct;
    u8 length;
    u8 payload[0];
} uart_packet_t;

typedef enum {
    BYTE_MAGIC_1,
    BYTE_MAGIC_2,
    BYTE_TYPE,
    BYTE_DIRECT,
    BYTE_LENGTH,
    BYTE_PAYLOAD_0,
    BYTE_PAYLOAD_1,
    BYTE_PAYLOAD_2,
    BYTE_PAYLOAD_3,
    BYTE_PAYLOAD_4,
    BYTE_PAYLOAD_5,
    BYTE_PAYLOAD_6,
} UART_FRAME_BYTE;


typedef enum {
    UART_CMD_BATTERY,
    UART_CMD_CHARGING,
    UART_CMD_HALL,
    UART_CMD_MAC,
    CMD_BATTERY_F98,
    UART_CMD_BUTTON,
    UART_USER_ADD,
    CMD_PRODUCT_MODE,

    UART_CMD_EAR_HW_ST = 0x09,

    UART_CMD_NULL = 0xFF,
} UART_CMD_TYPE;
typedef enum {
    TO_7012,
    TO_982,
} UART_DIRECTION;
#define UART_MAGIC_NUM_1      0X55
#define UART_MAGIC_NUM_2      0XAA
#define JBL_UART_FRAME_LEN      15
#endif //UART_TEST_H