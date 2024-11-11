#include "custom.h"

#if LV_DEMO_WOODEN_FISH_EN 

static const char *virtue_title[] = {"今日功德", "Today's Merit"};
static const char *label_virtue[] = {"功德+1", "Merit + 1"};

static int wooden_fish_count =  0;
static int virtue_count = 0;
static int wooden_last_click = 0;

#define ANIM_INTERVAL	(40)

static lv_style_t style_text_opa_100;
static lv_style_t style_text_opa_90;
static lv_style_t style_text_opa_70;
static lv_style_t style_text_opa_50;

lv_timer_t *wooden_fish_timer;

void wooden_fish_timer_cb()
{
	static enter_time = 0;

	switch (enter_time)
	{
		case 0:
			lv_img_set_src(guider_ui.screen_wooden_fish_img_wooden_fish, "F:/wooden_fish1.bin");

			lv_obj_clear_flag(guider_ui.screen_wooden_fish_label_cumulate1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate3, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate4, LV_OBJ_FLAG_HIDDEN);
			enter_time++;
			break;
		case 1:
			lv_img_set_src(guider_ui.screen_wooden_fish_img_wooden_fish, "F:/wooden_fish2.bin");

			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_wooden_fish_label_cumulate2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate3, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate4, LV_OBJ_FLAG_HIDDEN);
			enter_time++;
			break;
		case 2:
			lv_img_set_src(guider_ui.screen_wooden_fish_img_wooden_fish, "F:/wooden_fish3.bin");

			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_wooden_fish_label_cumulate3, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate4, LV_OBJ_FLAG_HIDDEN);
			enter_time++;
			break;
		case 3:
			lv_img_set_src(guider_ui.screen_wooden_fish_img_wooden_fish, "F:/wooden_fish4.bin");

			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate3, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_wooden_fish_label_cumulate4, LV_OBJ_FLAG_HIDDEN);
			enter_time++;
			break;
	
		default:
			enter_time = 0;
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate3, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.screen_wooden_fish_label_cumulate4, LV_OBJ_FLAG_HIDDEN);
			b_printf("del fish");
			if(wooden_fish_timer) {
				lv_timer_del(wooden_fish_timer);
				wooden_fish_timer = NULL;
			}
			break;
	}
}

void screen_wooden_fish_refresh();

static void screen_wooden_fish_label_style_init()
{
	lv_style_init(&style_text_opa_50);
	lv_style_set_text_opa(&style_text_opa_50, LV_OPA_50);
	lv_obj_add_style(guider_ui.screen_wooden_fish_label_cumulate4, &style_text_opa_50, 0);

	lv_style_init(&style_text_opa_70);
	lv_style_set_text_opa(&style_text_opa_70, LV_OPA_70);
	lv_obj_add_style(guider_ui.screen_wooden_fish_label_cumulate3, &style_text_opa_70, 0);

	lv_style_init(&style_text_opa_90);
	lv_style_set_text_opa(&style_text_opa_90, LV_OPA_90);
	lv_obj_add_style(guider_ui.screen_wooden_fish_label_cumulate2, &style_text_opa_90, 0);
}

static void screen_wooden_fish_init()
{
	printf("%s\n", __FUNCTION__);

	setup_scr_screen_wooden_fish(&guider_ui, NULL);
	screen_wooden_fish_label_style_init();
	events_init_screen_wooden_fish(&guider_ui);
}
static void screen_wooden_fish_deinit()
{
	printf("%s\n", __FUNCTION__);
	// lv_status_bar_top_show();
	lv_obj_del(guider_ui.screen_wooden_fish);
	guider_ui.screen_wooden_fish = NULL;

	if(wooden_fish_timer) {
		lv_timer_del(wooden_fish_timer);
		wooden_fish_timer = NULL;
	}
}
static void screen_wooden_fish_load()
{
	lv_scr_load(guider_ui.screen_wooden_fish);
}

// static void wooden_fish_click_cb()
// {
// 	virtue_count++;
// 	int duration_time = lv_tick_elaps(wooden_last_click);
// 	if(duration_time < 300) {
// 		wooden_fish_count++;
// 	} else {
// 		wooden_fish_count = 0;
// 	}
// 	wooden_last_click = lv_tick_get();
// 	b_printf("<<<wooden_last_click: %d, wooden_fish_count: %d>>>", wooden_last_click, wooden_fish_count);
// }

static void screen_wooden_fish_img_wooden_fish_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		b_printf("func: %s, line: %d", __func__, __LINE__);
		// wooden_fish_click_cb();
		virtue_count++;
		if(!wooden_fish_timer) {
			wooden_fish_timer = lv_timer_create(wooden_fish_timer_cb, ANIM_INTERVAL, NULL);
		}
		break;
	}
	case LV_EVENT_GESTURE:
	{
		lv_indev_wait_release(lv_indev_get_act());
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir){
        case LV_DIR_LEFT:
            break;
        case LV_DIR_RIGHT:
			screen_list_del(SCREEN_PRIO_WOODEN_FISH);
            break;
        }

		break;
	}
	default:
		break;
	}
}

void events_init_screen_wooden_fish(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_wooden_fish_img_wooden_fish, screen_wooden_fish_img_wooden_fish_event_handler, LV_EVENT_ALL, NULL);
}



void screen_wooden_fish_enter()
{
	// printf("%s\n", __FUNCTION__);
	// lv_status_bar_top_hide();
	screen_list_add(screen_wooden_fish_init, screen_wooden_fish_deinit, screen_wooden_fish_load, screen_wooden_fish_refresh, SCREEN_PRIO_WOODEN_FISH);
}

void screen_wooden_fish_refresh()
{
	//判断页面存活
	if(!guider_ui.screen_wooden_fish){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text_fmt(guider_ui.screen_wooden_fish_label_virtue_num, "+%d", virtue_count);
		lv_label_set_text(guider_ui.screen_wooden_fish_label_virtue_title,  virtue_title[0]);
		lv_label_set_text(guider_ui.screen_wooden_fish_label_cumulate1, label_virtue[0]);
		lv_label_set_text(guider_ui.screen_wooden_fish_label_cumulate2, label_virtue[0]);
		lv_label_set_text(guider_ui.screen_wooden_fish_label_cumulate3, label_virtue[0]);
		lv_label_set_text(guider_ui.screen_wooden_fish_label_cumulate4, label_virtue[0]);
	}
#else
	lv_label_set_text_fmt(guider_ui.screen_wooden_fish_label_virtue_num, "+%d", virtue_count);
    lv_label_set_text_fmt(guider_ui.screen_wooden_fish_label_virtue_title, "%s", virtue_title[language]);
    lv_label_set_text_fmt(guider_ui.screen_wooden_fish_label_cumulate1, "%s", label_virtue[language]);
    lv_label_set_text_fmt(guider_ui.screen_wooden_fish_label_cumulate2, "%s", label_virtue[language]);
    lv_label_set_text_fmt(guider_ui.screen_wooden_fish_label_cumulate3, "%s", label_virtue[language]);
    lv_label_set_text_fmt(guider_ui.screen_wooden_fish_label_cumulate4, "%s", label_virtue[language]);
#endif
}

#endif

