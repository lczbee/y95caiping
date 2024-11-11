#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "lv_demo_product_test.h"
#include "product_test_api.h"

/**************************************************screen test****************************************************/
static int color_tab[] = {
                  (0xFF0000),
                  (0x00FF00),
                  (0x0000FF),
                  (0xFFFF00),
                  (0xFF00FF),
                  (0x00FFFF),
                  (0xFFFFFF),
            } ;
static int cur_color = 0;
/**************************************************screen test****************************************************/

void screen_product_test_init()
{
	printf("%s\n", __FUNCTION__);
	// lv_status_bar_top_hide();

	setup_scr_screen_product_test(&guider_ui, NULL);
	if(pc_mode_on) {
		lv_obj_add_state(guider_ui.screen_product_test_btn_pc, LV_STATE_CHECKED);
	} else {
		lv_obj_clear_state(guider_ui.screen_product_test_btn_pc, LV_STATE_CHECKED);
	}
	events_init_screen_product_test(&guider_ui);

}

void screen_product_test_deinit()
{
	printf("%s\n", __FUNCTION__);

	lv_obj_del(guider_ui.screen_product_test);
	// lv_status_bar_top_show();
	guider_ui.screen_product_test = NULL;
}
static void screen_product_test_load()
{
	lv_scr_load(guider_ui.screen_product_test);
}


// 产测菜单回调
static void screen_product_test_cont_product_test_menu_event_handler (lv_event_t *e)
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
			printf("product_test_menu to right\n");
			// lv_obj_add_flag(guider_ui.screen_product_test_cont_product_test, LV_OBJ_FLAG_HIDDEN);
			screen_list_del(SCREEN_PRIO_PRODUCT_TEST);
            break;
        }
		break;
	}
	default:
		break;
	}
}

// tp测试界面回调
static void screen_product_test_cont_tp_test_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

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
			printf("tp test to right\n");

			// 右滑隐藏鼠标
			if(cursor_obj) {
				lv_obj_add_flag(cursor_obj, LV_OBJ_FLAG_HIDDEN);
			}
			
			// 隐藏tp测试界面
			lv_obj_add_flag(guider_ui.screen_product_test_cont_tp_test, LV_OBJ_FLAG_HIDDEN);
            break;
        }
		break;
	}
	default:
		break;
	}
}

// 屏幕测试界面回调
static void screen_product_test_cont_screen_test_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		cur_color = ++ cur_color >= sizeof(color_tab) / sizeof(color_tab[0]) ? 0 : cur_color;
		
		lv_obj_set_style_bg_color(guider_ui.screen_product_test_cont_screen_test, lv_color_hex(color_tab[cur_color]), LV_PART_MAIN | LV_STATE_DEFAULT );
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
			printf("screen test to right\n");
			// 隐藏屏幕测试界面
			lv_obj_add_flag(guider_ui.screen_product_test_cont_screen_test, LV_OBJ_FLAG_HIDDEN);
			
            break;
        }
		break;
	}
	default:
		break;
	}
}

// 屏幕测试按钮回调
static void screen_product_test_btn_screen_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		// 显示屏幕测试界面
		lv_obj_clear_flag(guider_ui.screen_product_test_cont_screen_test, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}

// tp测试按钮回调
static void screen_product_test_btn_tp_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		// 点击一下出鼠标
		if(cursor_obj) {
			lv_obj_clear_flag(cursor_obj, LV_OBJ_FLAG_HIDDEN);
		}

		// 显示tp测试界面
		lv_obj_clear_flag(guider_ui.screen_product_test_cont_tp_test, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}

// 连接测试按钮回调
static void screen_product_test_btn_connect_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		// smbox_bt_ble_scan_enable(1);
		sbox_connect_test();
		break;
	}
	default:
		break;
	}
}

// 复位按钮回调
static void screen_product_test_btn_reset_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		cpu_reset();
		break;
	}
	default:
		break;
	}
}

// pc模式回调
static void screen_product_test_btn_pc_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *target = lv_event_get_target(e);

	u8 box_charging = box_info_base_cb.lv_box_charging_get();

	if(box_charging) {
		lv_obj_add_flag(target, LV_OBJ_FLAG_CHECKABLE);
	} else {
		lv_obj_clear_flag(target, LV_OBJ_FLAG_CHECKABLE);
	}

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		if(lv_obj_has_state(target, LV_STATE_CHECKED)) {
			printf("PC MODE!!!");
			app_task_switch_to(APP_PC_TASK);
			if (app_get_curr_task() != APP_PC_TASK) {
				printf("switch to pc mode failed");
				pc_mode_on = false;
			} else {
				pc_mode_on = true;
			}
		} else {
			printf("BT MODE!!!");
			app_task_switch_to(APP_BT_TASK);
			pc_mode_on = false;
		}
		
		break;
	}
	default:
		break;
	}
}

// 仓储模式回调
static void screen_product_test_btn_storage_mode_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		box_info_base_cb.lv_storage_mode_enter();
		break;
	}
	default:
		break;
	}
}

// 预留1回调
static void screen_product_test_btn_reserve1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		b_printf("reserve1");
		break;
	}
	default:
		break;
	}
}

// 电量测试回调
static void screen_product_test_btn_bat_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		b_printf("bat test");
		extern int now_soc_trim_info;
		if(now_soc_trim_info==200){
			write_first_start_info(0);
		} else {
			write_first_start_info(200);
		}
		break;
	}
	default:
		break;
	}
}

// 预留2回调
static void screen_product_test_btn_reserve2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SHORT_CLICKED:
	{
		b_printf("reserve2");
		break;
	}
	default:
		break;
	}
}


void events_init_screen_product_test(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_product_test_cont_screen_test, screen_product_test_cont_screen_test_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_product_test_cont_tp_test, screen_product_test_cont_tp_test_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_product_test_cont_product_test_menu, screen_product_test_cont_product_test_menu_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_product_test_btn_screen, screen_product_test_btn_screen_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_product_test_btn_tp, screen_product_test_btn_tp_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_product_test_btn_connect, screen_product_test_btn_connect_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_product_test_btn_reset, screen_product_test_btn_reset_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_product_test_btn_pc, screen_product_test_btn_pc_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_product_test_btn_storage_mode, screen_product_test_btn_storage_mode_event_handler, LV_EVENT_ALL, NULL);
	//lv_obj_add_event_cb(ui->screen_product_test_btn_reserve1, screen_product_test_btn_reserve1_event_handler, LV_EVENT_ALL, NULL);
	//lv_obj_add_event_cb(ui->screen_product_test_btn_reserve2, screen_product_test_btn_reserve2_event_handler, LV_EVENT_ALL, NULL);
	//lv_obj_add_event_cb(ui->screen_product_test_btn_bat, screen_product_test_btn_bat_event_handler, LV_EVENT_ALL, NULL);
}


void screen_product_test_enter()
{
	screen_list_add(screen_product_test_init, screen_product_test_deinit, screen_product_test_load, NULL, SCREEN_PRIO_PRODUCT_TEST);
}
