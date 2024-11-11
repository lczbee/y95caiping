#include "custom.h"

#if LV_DEMO_POP_UP_EN

/*****************************参数配置************************************/
// log debug宏
#define POP_UP_DEBUG_EN               (1)

#if POP_UP_DEBUG_EN
#define POP_UP_DEBUG   b_printf
#else
#define POP_UP_DEBUG(...)
#endif

// 动画切换间隔
#define POP_UP_ANIM_INTERVAL 	(120)

// 动画持续时间，时间到了自动关闭页面
#define POP_UP_ANIM_DURATION 	(1500)

// 动画滤波，双耳同时出入仓时，实际上会有时间差，所以需要滤波
// 减小该值可以一定程度上提高动画反应速度，但会缩短双耳同时出入仓
// 的响应时间
#define POP_UP_ANIM_FILTER	 	(250)

// 默认左耳状态在仓
#define DEFAULT_L_STATUS		(IN_BOX) 
// 默认右耳状态在仓
#define DEFAULT_R_STATUS		(IN_BOX) 
// 默认开盖
#define DEFAULT_CLID_STATUS		(LID_OPEN) 
/*****************************参数配置************************************/


/*****************************动画数组************************************/
// 左耳正在出仓
const char *left_out[] = { 
    "F:/l_in.jpg",
    "F:/l_1.jpg",
    "F:/l_2.jpg",
    "F:/l_3.jpg",
    "F:/l_4.jpg",
    "F:/l_out.jpg"
};

//右耳正在出仓
const char *right_out[] = { 
    "F:/r_in.jpg",
    "F:/r_1.jpg",
    "F:/r_2.jpg",
    "F:/r_3.jpg",
    "F:/r_4.jpg",
    "F:/r_out.jpg"
};

// 左耳正在入仓
const char *left_in[] = { 
    "F:/l_out.jpg",
    "F:/l_4.jpg",
    "F:/l_3.jpg",
    "F:/l_2.jpg",
    "F:/l_1.jpg",
    "F:/l_in.jpg"
};

// 右耳正在入仓
const char *right_in[] = { 
    "F:/r_out.jpg",
    "F:/r_4.jpg",
    "F:/r_3.jpg",
    "F:/r_2.jpg",
    "F:/r_1.jpg",
    "F:/r_in.jpg"
};

// 左耳在仓
const char *left_stay_in[] = {
	"F:/l_in.jpg",
};

// 右耳在仓
const char *right_stay_in[] = {
	"F:/r_in.jpg",
};

// 左耳不在仓
const char *left_stay_out[] = {
	"F:/l_out.jpg",
};

// 右耳不在仓
const char *right_stay_out[] = {
	"F:/r_out.jpg",
};

// 左耳在仓关仓盖
const char *lid_left_in_close[] = { 
    "F:/lid_li1.jpg",
    "F:/lid_li2.jpg",
    "F:/lid_li3.jpg",
    "F:/lid_li4.jpg",
    "F:/lid_l_close.jpg",
};

// 左耳在仓开仓盖
const char *lid_left_in_open[] = { 
    "F:/lid_l_close.jpg",
    "F:/lid_li4.jpg",
    "F:/lid_li3.jpg",
    "F:/lid_li2.jpg",
    "F:/lid_li1.jpg",
};

// 右耳在仓关仓盖
const char *lid_right_in_close[] = { 
    "F:/lid_ri1.jpg",
    "F:/lid_ri2.jpg",
    "F:/lid_ri3.jpg",
    "F:/lid_ri4.jpg",
    "F:/lid_r_close.jpg",
};

// 右耳在仓开仓盖
const char *lid_right_in_open[] = { 
    "F:/lid_r_close.jpg",
    "F:/lid_ri4.jpg",
    "F:/lid_ri3.jpg",
    "F:/lid_ri2.jpg",
    "F:/lid_ri1.jpg",
};

// 左耳不在仓关仓盖
const char *lid_left_out_close[] = { 
    "F:/lid_lo1.jpg",
    "F:/lid_lo2.jpg",
    "F:/lid_lo3.jpg",
    "F:/lid_lo4.jpg",
    "F:/lid_l_close.jpg",
};

// 左耳不在仓开仓盖
const char *lid_left_out_open[] = { 
    "F:/lid_l_close.jpg",
    "F:/lid_lo4.jpg",
    "F:/lid_lo3.jpg",
    "F:/lid_lo2.jpg",
    "F:/lid_lo1.jpg",
};

// 右耳不在仓关仓盖
const char *lid_right_out_close[] = { 
    "F:/lid_ro1.jpg",
    "F:/lid_ro2.jpg",
    "F:/lid_ro3.jpg",
    "F:/lid_ro4.jpg",
    "F:/lid_r_close.jpg",
};

// 右耳不在仓开仓盖
const char *lid_right_out_open[] = { 
    "F:/lid_r_close.jpg",
    "F:/lid_ro4.jpg",
    "F:/lid_ro3.jpg",
    "F:/lid_ro2.jpg",
    "F:/lid_ro1.jpg",
};
/*****************************动画数组************************************/


/*****************************重要变量************************************/
// 界面退出定时器
static lv_timer_t *screen_pop_up_exit_timer = NULL;
// 界面进入定时器
static lv_timer_t *screen_pop_up_enter_timer = NULL;

// 左耳上一次在仓状态
static u8 l_inbox_last_status = DEFAULT_L_STATUS;
// 右耳上一次在仓状态
static u8 r_inbox_last_status = DEFAULT_R_STATUS;
// 仓盖上一次状态
static u8 box_clid_last_status = DEFAULT_CLID_STATUS;
/*****************************重要变量************************************/

// 更新左耳上一次状态
void pop_up_set_l_inbox_last_status(u8 status)
{
	l_inbox_last_status = status;
}
// 更新右耳上一次状态
void pop_up_set_r_inbox_last_status(u8 status)
{
	r_inbox_last_status = status;
}
// 更新仓盖上一次状态
void pop_up_set_box_clid_last_status(u8 status)
{
	box_clid_last_status = status;
}

static void screen_pop_up_init()
{
	printf("[pop up] %s\n", __FUNCTION__);

	setup_scr_screen_pop_up(&guider_ui, NULL);
    events_init_screen_pop_up(&guider_ui);

	screen_pop_up_trig();
}

static void screen_pop_up_deinit()
{
	printf("[pop up] %s\n", __FUNCTION__);

	lv_obj_del(guider_ui.screen_pop_up);
	guider_ui.screen_pop_up = NULL;

	if(screen_pop_up_exit_timer) {
		lv_timer_del(screen_pop_up_exit_timer);
		screen_pop_up_exit_timer = NULL;
	}
	if(screen_pop_up_enter_timer) {
		lv_timer_del(screen_pop_up_enter_timer);
		screen_pop_up_enter_timer = NULL;
	}
}
static void screen_pop_up_load()
{
    lv_scr_load(guider_ui.screen_pop_up);
}

static void screen_pop_up_cont_pop_up_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
        screen_list_del(SCREEN_PRIO_POP_UP);
	}
	default:
		break;
	}
}


void events_init_screen_pop_up(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_pop_up_cont_pop_up, screen_pop_up_cont_pop_up_event_handler, LV_EVENT_ALL, NULL);
}

// 进入弹窗动画界面（该接口只能在UI线程使用）
void screen_pop_up_enter()
{
	POP_UP_DEBUG("[pop up] func: %s, line: %d", __func__, __LINE__);
	// lv_status_bar_top_hide();
	screen_list_add(screen_pop_up_init, screen_pop_up_deinit, screen_pop_up_load, NULL, SCREEN_PRIO_POP_UP);
}

// 退出弹窗动画界面（该接口只能在UI线程使用）
void screen_pop_up_exit()
{
	POP_UP_DEBUG("[pop up] func: %s, line: %d", __func__, __LINE__);
	screen_list_del(SCREEN_PRIO_POP_UP);
	u8 l_inbox = box_info_base_cb.lv_l_inbox_get();
	u8 r_inbox = box_info_base_cb.lv_r_inbox_get();
	u8 box_clid = box_info_base_cb.lv_box_clid_status_get();
	l_inbox_last_status = l_inbox;
	r_inbox_last_status = r_inbox;
	box_clid_last_status = box_clid;
	POP_UP_DEBUG("[pop up] update status, l_inbox_last_status: %d, r_inbox_last_status: %d, box_clid_last_status: %d", l_inbox_last_status, r_inbox_last_status, box_clid_last_status);
	// lv_status_bar_top_show();
}

void screen_pop_up_refresh()
{
	//判断页面存活
	if(guider_ui.screen_pop_up){return;}
	// printf("%s\n", __FUNCTION__);
}

void screen_pop_up_trig()
{
	u8 l_inbox = box_info_base_cb.lv_l_inbox_get();
	u8 r_inbox = box_info_base_cb.lv_r_inbox_get();
	u8 box_clid = box_info_base_cb.lv_box_clid_status_get();

	POP_UP_DEBUG("[pop up] l_inbox: %d, r_inbox: %d, box_clid: %d, \n\t\t\tlast_l_inbox: %d, last_r_inbox: %d, box_clid_last_status: %d", l_inbox, r_inbox, box_clid, l_inbox_last_status, r_inbox_last_status, box_clid_last_status);

	// 仓盖发生变化
	if(box_clid != box_clid_last_status) {
		// 开仓盖
		if(box_clid == LID_OPEN) {
			if(l_inbox == IN_BOX) {
				u8 anim_num = sizeof(lid_left_in_open) / sizeof(lid_left_in_open[0]);
				POP_UP_DEBUG("[pop up] anim num: %d, lid_left_in_open", anim_num);
				lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_l, (const void **)lid_left_in_open, anim_num);
				lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_l, anim_num * POP_UP_ANIM_INTERVAL);
			} else {
				u8 anim_num = sizeof(lid_left_out_open) / sizeof(lid_left_out_open[0]);
				POP_UP_DEBUG("[pop up] anim num: %d, lid_left_out_open", anim_num);
				lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_l, (const void **)lid_left_out_open, anim_num);
				lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_l, anim_num * POP_UP_ANIM_INTERVAL);
			}
			if(r_inbox == IN_BOX) {
				u8 anim_num = sizeof(lid_right_in_open) / sizeof(lid_right_in_open[0]);
				POP_UP_DEBUG("[pop up] anim num: %d, lid_right_in_open", anim_num);
				lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_r, (const void **)lid_right_in_open, anim_num);
				lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_r, anim_num * POP_UP_ANIM_INTERVAL);
			} else {
				u8 anim_num = sizeof(lid_right_out_open) / sizeof(lid_right_out_open[0]);
				POP_UP_DEBUG("[pop up] anim num: %d, lid_right_out_open", anim_num);
				lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_r, (const void **)lid_right_out_open, anim_num);
				lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_r, anim_num * POP_UP_ANIM_INTERVAL);
			}

			// 关仓盖
		} else {
#if 0
			// 暂时不需要关盖动画
			if(l_inbox == 1) {
				u8 anim_num = sizeof(lid_left_in_close) / sizeof(lid_left_in_close[0]);
				POP_UP_DEBUG("anim num: %d, lid_left_in_close", anim_num);
				lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_l, (const void **)lid_left_in_close, anim_num);
				lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_l, anim_num * POP_UP_ANIM_INTERVAL);
			} else {
				u8 anim_num = sizeof(lid_left_out_close) / sizeof(lid_left_out_close[0]);
				POP_UP_DEBUG("anim num: %d, lid_left_out_close", anim_num);
				lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_l, (const void **)lid_left_out_close, anim_num);
				lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_l, anim_num * POP_UP_ANIM_INTERVAL);
			}
			if(r_inbox == 1) {
				u8 anim_num = sizeof(lid_right_in_close) / sizeof(lid_right_in_close[0]);
				POP_UP_DEBUG("anim num: %d, lid_right_in_close", anim_num);
				lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_r, (const void **)lid_right_in_close, anim_num);
				lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_r, anim_num * POP_UP_ANIM_INTERVAL);
			} else {
				u8 anim_num = sizeof(lid_right_out_close) / sizeof(lid_right_out_close[0]);
				POP_UP_DEBUG("anim num: %d, lid_right_out_close", anim_num);
				lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_r, (const void **)lid_right_out_close, anim_num);
				lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_r, anim_num * POP_UP_ANIM_INTERVAL);
			}
#endif
		}
	} else {
		// 开盖
		if(box_clid == LID_OPEN) {
			if(l_inbox != l_inbox_last_status) {
				if(l_inbox == IN_BOX) {
					u8 anim_num = sizeof(left_in) / sizeof(left_in[0]);
					POP_UP_DEBUG("[pop up] anim num: %d, l_in", anim_num);
					lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_l, (const void **)left_in, anim_num);
					lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_l, anim_num * POP_UP_ANIM_INTERVAL);
				} else {
					u8 anim_num = sizeof(left_out) / sizeof(left_out[0]);
					POP_UP_DEBUG("[pop up] anim num: %d, l_out", anim_num);
					lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_l, (const void **)left_out, anim_num);
					lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_l, anim_num * POP_UP_ANIM_INTERVAL);
				}
			} else {
				if(l_inbox == IN_BOX) {
					u8 anim_num = sizeof(left_stay_in) / sizeof(left_stay_in[0]);
					POP_UP_DEBUG("[pop up] anim num: %d, l_stay_in", anim_num);
					lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_l, (const void **)left_stay_in, anim_num);
					lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_l, anim_num * POP_UP_ANIM_INTERVAL);
				} else {
					u8 anim_num = sizeof(left_stay_out) / sizeof(left_stay_out[0]);
					POP_UP_DEBUG("[pop up] anim num: %d, l_stay_out", anim_num);
					lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_l, (const void **)left_stay_out, anim_num);
					lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_l, anim_num * POP_UP_ANIM_INTERVAL);
				}
			}

			if(r_inbox != r_inbox_last_status) {
				if(r_inbox == IN_BOX) {
					u8 anim_num = sizeof(right_in) / sizeof(right_in[0]);
					POP_UP_DEBUG("[pop up] anim num: %d, r_in", anim_num);
					lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_r, (const void **)right_in, anim_num);
					lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_r, anim_num * POP_UP_ANIM_INTERVAL);
				} else {
					u8 anim_num = sizeof(right_out) / sizeof(right_out[0]);
					POP_UP_DEBUG("[pop up] anim num: %d, r_out", anim_num);
					lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_r, (const void **)right_out, anim_num);
					lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_r, anim_num * POP_UP_ANIM_INTERVAL);
				}
			} else {
				if(r_inbox == IN_BOX) {
					u8 anim_num = sizeof(right_stay_in) / sizeof(right_stay_in[0]);
					POP_UP_DEBUG("[pop up] anim num: %d, r_stay_in", anim_num);
					lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_r, (const void **)right_stay_in, anim_num);
					lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_r, anim_num * POP_UP_ANIM_INTERVAL);
				} else {
					u8 anim_num = sizeof(right_stay_out) / sizeof(right_stay_out[0]);
					POP_UP_DEBUG("[pop up] anim num: %d, r_stay_out", anim_num);
					lv_animimg_set_src(guider_ui.screen_pop_up_animimg_pop_r, (const void **)right_stay_out, anim_num);
					lv_animimg_set_duration(guider_ui.screen_pop_up_animimg_pop_r, anim_num * POP_UP_ANIM_INTERVAL);
				}
			}
		} else {
			POP_UP_DEBUG("[pop up] keep lid close");
		}
	}

	
	lv_animimg_start(guider_ui.screen_pop_up_animimg_pop_l);
	lv_animimg_start(guider_ui.screen_pop_up_animimg_pop_r);

	l_inbox_last_status = l_inbox;
	r_inbox_last_status = r_inbox;
	box_clid_last_status = box_clid;
	POP_UP_DEBUG("[pop up] update status, l_inbox_last_status: %d, r_inbox_last_status: %d, box_clid_last_status: %d", l_inbox_last_status, r_inbox_last_status, box_clid_last_status);

	if(!screen_pop_up_exit_timer){
		screen_pop_up_exit_timer = lv_timer_create(screen_pop_up_exit, POP_UP_ANIM_DURATION, NULL);
	}
}

// 进入弹窗动画界面（该接口可以在其他线程使用）
void screen_pop_up_callback_enter()
{
	POP_UP_DEBUG("[pop up] func: %s, line: %d", __func__, __LINE__);

	if(guider_ui.screen_pop_up) {
		if(screen_pop_up_exit_timer) {
			lv_timer_del(screen_pop_up_exit_timer);
			screen_pop_up_exit_timer = NULL;
		}
		screen_pop_up_trig();
		
		POP_UP_DEBUG("[pop up] pop_up has been existed, animimg restarts");
	} else {
		send_to_trig_ui_vcb(screen_pop_up_enter);
		POP_UP_DEBUG("[pop up] pop_up starts");
	}

	if(screen_pop_up_enter_timer) {
		lv_timer_del(screen_pop_up_enter_timer);
		screen_pop_up_enter_timer = NULL;
	}
}

// 进入弹窗动画界面过滤，防止一定时间内弹出多次弹窗界面（该接口可以在其他线程使用）
void screen_pop_up_callback_enter_filter()
{
	u32 rets;
    __asm__ volatile("%0 = rets":"=r"(rets));
	POP_UP_DEBUG("[pop up] func: %s, line: %d, rets: %x", __func__, __LINE__, rets);
	static uint32_t last_tick = 0;

	if(lv_tick_elaps(last_tick) < POP_UP_ANIM_FILTER) {
		// 时间戳小于滤波间隔，直接返回
		POP_UP_DEBUG("[pop up] lv_tick_elaps(last_tick): %d < %d, return!", lv_tick_elaps(last_tick),  POP_UP_ANIM_FILTER);
		return;
	} else {
		lv_exit_sleep();
		if(!screen_pop_up_enter_timer) {
			screen_pop_up_enter_timer = lv_timer_create(screen_pop_up_callback_enter, POP_UP_ANIM_FILTER, NULL);
		}
		if(screen_pop_up_exit_timer) {
			lv_timer_del(screen_pop_up_exit_timer);
			screen_pop_up_exit_timer = NULL;
		}
		last_tick = lv_tick_get();
	}
}

#endif

