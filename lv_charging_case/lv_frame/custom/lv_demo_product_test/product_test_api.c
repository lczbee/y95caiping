#include "product_test_api.h"
#include "uart/uart_test.h"

u8 storage_mode_off;
void sbox_storage_mode_enter()
{
    //通知982同步进入仓储模式，避免701软关机后串口唤醒
    int msg[2];
    int err = 0;
    msg[0] = UT_TX;
    msg[1] = CMD_PRODUCT_MODE;
    err = os_taskq_post_type("sbox_uart_tx", Q_MSG, 2, msg);
    if (err) {
        printf("sbox tx post fail\n");
        return;
    }

    //立即灭屏
    usr_screen_on(0);

    //延时1s,确保出串口数据发出
    mdelay(100);

    //设置关机时，关闭RTC
    printf("storage_mode_off set before = %d", storage_mode_off);
    storage_mode_off = false;  
    syscfg_write(VM_STORAGE_MODE_FLAG, (u8 *)&storage_mode_off, sizeof(storage_mode_off));
    printf("storage_mode_off set after = %d", storage_mode_off);

    extern void key_wakeup_disable();
    key_wakeup_disable();

    //701软关机
    soft_poweroff_mode(1);  //设置强制关机
    sys_enter_soft_poweroff(NULL);
}

void sbox_poweroff_enter(u8 mode)
{
    //通知982同步进入仓储模式，避免701软关机后串口唤醒
    int msg[2];
    int err = 0;
    msg[0] = UT_TX;
    msg[1] = CMD_PRODUCT_MODE;
    err = os_taskq_post_type("sbox_uart_tx", Q_MSG, 2, msg);
    if (err) {
        printf("sbox tx post fail\n");
        return;
    }

    //立即灭屏
    usr_screen_on(0);

    //延时1s,确保出串口数据发出
    mdelay(100);

    if(mode == POWEROFF_MODE_STORAGE) {
        //设置关机时，关闭RTC
        printf("storage_mode_off set before = %d", storage_mode_off);
        storage_mode_off = false;
        syscfg_write(VM_STORAGE_MODE_FLAG, (u8 *)&storage_mode_off, sizeof(storage_mode_off));
        printf("storage_mode_off set after = %d", storage_mode_off);
    }

    extern void key_wakeup_disable();
    key_wakeup_disable();

    //701软关机
    soft_poweroff_mode(1);  //设置强制关机
    sys_enter_soft_poweroff(NULL);
}

void sbox_connect_test()
{
    int msg[2];
    int err = 0;
    msg[0] = UT_TX;
    msg[1] = UART_CMD_MAC;
    printf("sbox_connect_test UART_CMD_MAC");
    err = os_taskq_post_type("sbox_uart_tx", Q_MSG, 2, msg);
    if (err) {
        printf("sbox tx post fail\n");
        return;
    }
}

