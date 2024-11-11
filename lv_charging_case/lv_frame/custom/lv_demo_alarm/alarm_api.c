#include "custom.h"


//	需要精确计时用jiffies_msec
static uint32_t my_lv_tick_elaps(uint32_t prev_tick)
{
    uint32_t act_time = jiffies_msec();

    /*If there is no overflow in sys_time simple subtract*/
    if(act_time >= prev_tick) {
        prev_tick = act_time - prev_tick;
    }
    else {
        prev_tick = UINT32_MAX - prev_tick + 1;
        prev_tick += act_time;
    }

    return prev_tick;
}
#define lv_tick_get			jiffies_msec
#define lv_tick_elaps		my_lv_tick_elaps

static int alarm_wakeup_timer = 0;
static u8 alarm_status = ALARM_OFF; // 闹钟开关
static int alarm_countdown = 0; 	// 闹钟倒计时时长
static int start_tick = 0; 			// 闹钟设置开始时间，用时间戳来更新

static void  __sec2day(int sec, struct sys_time *time)
{
    time->day = sec / (60 * 60 * 24);
    time->hour = sec % (60 * 60 * 24) / (60 * 60);
    time->min = sec % (60 * 60 * 24) % (60 * 60) / 60;
    time->sec = sec % (60 * 60 * 24) % (60 * 60) % 60;
}

static void lv_alarm_wakeup_timer_cb()
{
	u32 tick_pass = lv_tick_elaps(start_tick);
    if(alarm_countdown * 1000  <= tick_pass) {

		// 主线程计时结束后，回到UI程运行唤醒逻辑
		int err;
		int msg[4];
		msg[0] = (int)alarm_ring_on;
		msg[1] = 0;
		err = os_taskq_post_type("ui", Q_CALLBACK, 2, msg);
		if (err) {
			printf("lv_alarm_wakeup_timer_add post fail\n");
		}

		if(alarm_wakeup_timer){
			sys_timer_del(alarm_wakeup_timer);
			alarm_wakeup_timer = 0;
		}
	}
}

static void lv_alarm_wakeup_timer_add()
{
	if(!alarm_wakeup_timer) {
		alarm_wakeup_timer = sys_timer_add(NULL, lv_alarm_wakeup_timer_cb, 1000);
	}
}

static void lv_alarm_wakeup_timer_del()
{
	if(alarm_wakeup_timer) {
		sys_timer_del(alarm_wakeup_timer);
		alarm_wakeup_timer = 0;
	}
}
extern bool screen_alarm_loaded;
void alarm_start(int countdown_sec)
{
	alarm_status = ALARM_ON;

	// 获取点击设置时的时间戳
	start_tick = lv_tick_get(); 
	
	// 显示倒计时初始值
	alarm_countdown = countdown_sec;
	int hour = alarm_countdown / 3600;
	int min = (alarm_countdown % 3600) / 60;
	int sec = alarm_countdown % 60;

	if(screen_alarm_loaded) {
		lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_count, "%02d:%02d:%02d", hour, min, sec);
	}

	// 在主线程运行定时器，避免低功耗时LVGL线程定时器停摆
	int err;
	int msg[4];
	msg[0] = (int)lv_alarm_wakeup_timer_add;
	msg[1] = 0;
	err = os_taskq_post_type("app_core", Q_CALLBACK, 2, msg);
	if (err) {
		printf("lv_alarm_wakeup_timer_add post fail\n");
	}
}

void alarm_cancel()
{
	alarm_status = ALARM_OFF;

	// 关闭在主线程运行的定时器
	int err;
	int msg[4];
	msg[0] = (int)lv_alarm_wakeup_timer_del;
	msg[1] = 0;
	err = os_taskq_post_type("app_core", Q_CALLBACK, 2, msg);
	if (err) {
		printf("lv_alarm_wakeup_timer_del post fail\n");
	}
}

void alarm_ring_on()
{
	alarm_status = ALARM_RING;

	// 退出休眠
	extern void lv_exit_sleep();
	lv_exit_sleep();

	screen_alarm_ring_enter();

	//发送闹钟指令
	box_info_send_cb.lv_alarm_ring_cmd_send(CMD_ALARM_RING);
}

void alarm_ring_off()
{
	alarm_status = ALARM_OFF;

	box_info_send_cb.lv_alarm_ring_cmd_send(CMD_FIND_CLOSE);
}

void alarm_refresh()
{
	if(alarm_status != ALARM_ON) {
		return;
	}

	if(!guider_ui.screen_alarm) {
		printf("[alarm] guider_ui.screen_alarm is NULL");
		return;
	}

	u32 tick_pass = lv_tick_elaps(start_tick);
    struct sys_time time;
    if(alarm_countdown * 1000 > tick_pass) {    //  倒计时过程
        __sec2day((alarm_countdown - tick_pass / 1000), &time);
		lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_count, "%02d:%02d:%02d", time.hour, time.min, time.sec);
		printf("hour: %d, min: %d, sec: %d", time.hour, time.min, time.sec);
	} else if(alarm_countdown * 1000  <= tick_pass) {
		lv_label_set_text_fmt(guider_ui.screen_alarm_label_alarm_count, "%02d:%02d:%02d", 0, 0, 0);
		printf("hour: %d, min: %d, sec: %d", time.hour, time.min, time.sec);
	}
}

u8 alarm_status_get()
{
	return alarm_status;
}