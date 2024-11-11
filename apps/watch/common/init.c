
#include "app_config.h"
#include "system/includes.h"
#include "asm/charge.h"
#include "app_power_manage.h"
#include "update.h"
#include "app_main.h"
#include "app_charge.h"
#include "update_loader_download.h"
#include "audio_config.h"
#include "uart_test.h"

extern void setup_arch();
extern int audio_dec_init();
extern int audio_enc_init();
extern void clr_wdt(void);

static void do_initcall()
{
    __do_initcall(initcall);
}

static void do_early_initcall()
{
    __do_initcall(early_initcall);
}

static void do_late_initcall()
{
    __do_initcall(late_initcall);
}

static void do_platform_initcall()
{
    __do_initcall(platform_initcall);
}

static void do_module_initcall()
{
    __do_initcall(module_initcall);
}

void __attribute__((weak)) board_init()
{

}
void __attribute__((weak)) board_early_init()
{

}

int eSystemConfirmStopStatus(void)
{
    /* 系统进入在未来时间里，无任务超时唤醒，可根据用户选择系统停止，或者系统定时唤醒(100ms) */
    //1:Endless Sleep
    //0:100 ms wakeup
    if (IS_CHARGE_EN()) {
        return 1;
    }
    if (get_charge_full_flag()) {
        log_i("Endless Sleep");
        power_set_soft_poweroff();
        return 1;
    } else {
        log_i("100 ms wakeup");
        return 0;
    }

}

static void check_power_on_key(void)
{
    u32 delay_10ms_cnt = 0;
#if PRODUCT_TEST_ENABLE
    u8 pt_result;
    int r = syscfg_read(PT_TEST_RESULT, (u8 *)&pt_result, sizeof(pt_result));
    if (r <= 0) {
        return;
        // log_info("vm read pt_test_result faild\n");
    }
#endif
    while (1) {
        clr_wdt();
        os_time_dly(1);

        extern u8 get_power_on_status(void);
        if (get_power_on_status()) {
            putchar('+');
            delay_10ms_cnt++;
            if (delay_10ms_cnt > 70) {
                return;
            }
        } else {
            putchar('-');
            delay_10ms_cnt = 0;
            puts("enter softpoweroff\n");
            power_set_soft_poweroff();
        }
    }
}

void check_power_on_charge(void)
{
    //充电激活
    extern u8 storage_mode_off;
    int r = syscfg_read(VM_STORAGE_MODE_FLAG, (u8 *)&storage_mode_off, sizeof(storage_mode_off));
    if (r <= 0) {
        printf("vm read storage_mode_off faild\n");
        storage_mode_off = true;//false
        syscfg_write(VM_STORAGE_MODE_FLAG, (u8 *)&storage_mode_off, sizeof(storage_mode_off));
    }

    printf("storage_mode_off = %d", storage_mode_off);
    printf("sbox_box_charging_get = %d", sbox_box_charging_get());

    if(storage_mode_off == false){

        //船运模式下，需要充电激活
        static int wait_count = 0;
        while (!sbox_box_charging_get()) {
            clr_wdt();
            os_time_dly(10);    //10ms*10 = 100ms 检测一遍

            if(wait_count > 100){   //10s内插电激活，否则关机
                printf("wait active timeout!");
                break;
            }else{
                wait_count++;
                printf("wait charge to active!");
            }
        }

        if(sbox_box_charging_get()){
            //激活
            puts("exit storage_mode!!!!!\n");
            storage_mode_off = true;
            syscfg_write(VM_STORAGE_MODE_FLAG, (u8 *)&storage_mode_off, sizeof(storage_mode_off));
        }else{
            //不激活
            puts("enter storage_mode!!!!\n");
            storage_mode_off = false;
            syscfg_write(VM_STORAGE_MODE_FLAG, (u8 *)&storage_mode_off, sizeof(storage_mode_off));

            //通知982同步进入仓储模式，避免701软关机后串口唤醒
            int msg[2];
            int err = 0;
            msg[0] = UT_TX;
            msg[1] = CMD_PRODUCT_MODE;
            err = os_taskq_post_type("sbox_uart_tx", Q_MSG, 2, msg);
            if (err) {
                printf("sbox tx post fail\n");
            }

            //延时1s,确保出串口数据发出
            mdelay(100);

            //关机
            power_set_soft_poweroff();
        }
    }
}

static void app_init()
{
    int update;

    do_early_initcall();
    do_platform_initcall();

    board_init();

    do_initcall();

    do_module_initcall();
    do_late_initcall();

    audio_enc_init();
    audio_dec_init();
    // for (cahr i = 0; i < count; i++)
    // {
    //     /* code */
    // }
    
    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        update = update_result_deal();
    }

#if LV_LOW_POWER_EN
    uint8_t lowpower_entry_info = 0;
    syscfg_read(LOWPOWER_ENTRY_INFO, &lowpower_entry_info, sizeof(lowpower_entry_info));
    r_printf("poweron lowpower_entry_info:0x%x\n",lowpower_entry_info);
    if(lowpower_entry_info != 0x55)
    {
#if TCFG_POWER_ON_NEED_CHARGE
        check_power_on_charge();
#endif
        lowpower_entry_info = 0;
    }else{
        lowpower_entry_info = 0xAA;
    }
    syscfg_write(LOWPOWER_ENTRY_INFO, &lowpower_entry_info, sizeof(lowpower_entry_info));
#else
#if TCFG_POWER_ON_NEED_CHARGE
    check_power_on_charge();
#endif
#endif
    app_var.play_poweron_tone = 1;

    if (!get_charge_online_flag()) {
        // if (is_reset_source(P33_POWER_RETURN))
        // {
        //     g_printf("P33_POWER_RETURN ERROR !!!!");
        //     power_set_soft_poweroff();
        //     return;
        // }
        
        check_power_on_voltage();
#if LV_SOC_CHECK
        // usr_check_power_on_voltage();
#endif
#if TCFG_POWER_ON_NEED_KEY
        /*充电拔出,CPU软件复位, 不检测按键，直接开机*/
        extern u8 get_alarm_wkup_flag(void);
#if TCFG_CHARGE_OFF_POWERON_NE
        if ((!update && cpu_reset_by_soft()) || is_ldo5v_wakeup() || get_alarm_wkup_flag()) {
#else
        if ((!update && cpu_reset_by_soft()) || get_alarm_wkup_flag()) {
#endif
            app_var.play_poweron_tone = 0;
        } else {
            check_power_on_key();
        }
#endif
    }

#if (TCFG_MC_BIAS_AUTO_ADJUST == MC_BIAS_ADJUST_POWER_ON)
    u8 por_flag = 0;
    u8 cur_por_flag = 0;
#if defined(CONFIG_CPU_BR23)
    extern u8 power_reset_src;
    /*
     *1.update
     *2.power_on_reset(BIT0:上电复位)
     *3.pin reset(BIT4:长按复位)
     */
    if (update || (power_reset_src & BIT(0)) || (power_reset_src & BIT(4))) {
        //log_info("reset_flag:0x%x",power_reset_src);
        cur_por_flag = 0xA5;
    }
#else /* #if defined(CONFIG_CPU_BR23) */
    u32 reset_src = get_reset_source_value();
    if (update || (reset_src & BIT(MSYS_POWER_RETURN)) || (reset_src & BIT(P33_PPINR_RST))) {
        //log_info("reset_flag:0x%x",reset_src);
        cur_por_flag = 0xA5;
    }
#endif /* #if defined(CONFIG_CPU_BR23) */

    int ret = syscfg_read(CFG_POR_FLAG, &por_flag, 1);
    if ((cur_por_flag == 0xA5) && (por_flag != cur_por_flag)) {
        //log_info("update POR flag");
        ret = syscfg_write(CFG_POR_FLAG, &cur_por_flag, 1);
    }
#endif

#if (TCFG_CHARGE_ENABLE && TCFG_CHARGE_POWERON_ENABLE)
    if (is_ldo5v_wakeup()) { //LDO5V唤醒
        extern u8 get_charge_online_flag(void);
        if (get_charge_online_flag()) { //关机时，充电插入

        } else { //关机时，充电拔出
            power_set_soft_poweroff();
        }
    }
#endif

#if(TCFG_CHARGE_BOX_ENABLE)
    /* clock_add_set(CHARGE_BOX_CLK); */
    chgbox_init_app();
#endif

#if PRODUCT_TEST_ENABLE
    int product_test_open(void);
    product_test_open();
#endif /* #if PRODUCT_TEST_ENABLE */
}

static void app_task_handler(void *p)
{
    app_init();
    app_main();
}

__attribute__((used)) int *__errno()
{
    static int err;
    return &err;
}

int main()
{
#if defined(CONFIG_CPU_BR23)
    clock_set_sfc_max_freq(104 * 1000000, 104 * 1000000);
    clock_reset_lsb_max_freq(80 * 1000000);
#elif defined(CONFIG_CPU_BR28)
    clock_set_sfc_max_freq(104 * 1000000, 104 * 1000000);
#endif
    wdt_close();

    os_init();

    setup_arch();

    board_early_init();

    task_create(app_task_handler, NULL, "app_core");

    os_start();

    local_irq_enable();

    while (1) {
        asm("idle");
    }

    return 0;
}

