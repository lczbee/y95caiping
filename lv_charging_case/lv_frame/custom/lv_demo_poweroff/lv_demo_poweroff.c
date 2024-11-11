#include "custom.h"
#include "lv_demo_product_test/product_test_api.h"

static void screen_poweroff_init()
{
	printf("%s\n", __FUNCTION__);

	setup_scr_screen_poweroff(&guider_ui, NULL);
	events_init_screen_poweroff(&guider_ui);
}

static void screen_poweroff_deinit()
{
	printf("%s\n", __FUNCTION__);

	lv_obj_del(guider_ui.screen_poweroff);
	guider_ui.screen_poweroff = NULL;
}

static void screen_poweroff_load()
{
	lv_scr_load(guider_ui.screen_poweroff);
}

void screen_poweroff_enter()
{
	// lv_status_bar_top_hide();
	screen_list_add(screen_poweroff_init, screen_poweroff_deinit, screen_poweroff_load, NULL, SCREEN_PRIO_POWEROFF);
}

void screen_poweroff_exit()
{
	screen_list_del(SCREEN_PRIO_POWEROFF);
}

static void screen_poweroff_cont_poweroff_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	extern lv_obj_t * cursor_obj;

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		break;
	}
	case LV_EVENT_GESTURE:
	{
        lv_indev_wait_release(lv_indev_get_act());
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir){
        case LV_DIR_LEFT:
			// printf("to left\n");
            break;
        case LV_DIR_RIGHT:
			// 右滑隐藏产测菜单
			printf("func: %s, line: %d, page return", __func__, __LINE__);
			screen_poweroff_exit();
            break;
        }
		break;
	}
	default:
		break;
	}
}

static void screen_poweroff_img_sys_poweroff_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	extern lv_obj_t * cursor_obj;

	switch (code) {
	case LV_EVENT_LONG_PRESSED:
	{
		sbox_poweroff_enter(POWEROFF_MODE_STORAGE);
		// sbox_storage_mode_enter();
		break;
	}

	case LV_EVENT_CLICKED:
	{
		printf("[poweroff] poweroff");
		sbox_poweroff_enter(POWEROFF_MODE_NORMAL);
		break;
	}
	default:
		break;
	}
}

static void screen_poweroff_img_sys_reset_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	extern lv_obj_t * cursor_obj;

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		printf("[poweroff] reset");
#if LV_SOC_CHECK
		r_printf("screen_product_test_btn_reset_event_handlerLV_EVENT_CLICKED");
		extern void write_first_start_info(int reset_sour);
		if(!box_info.box_charging){
			// write_first_start_info(200);
			cpu_reset();
		}
#endif
		
		break;
	}
	default:
		break;
	}
}

void events_init_screen_poweroff(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_poweroff_cont_poweroff, screen_poweroff_cont_poweroff_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_poweroff_img_sys_reset, screen_poweroff_img_sys_reset_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_poweroff_img_sys_poweroff, screen_poweroff_img_sys_poweroff_event_handler, LV_EVENT_ALL, NULL);
}