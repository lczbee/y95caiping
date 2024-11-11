#include "custom.h"

/*****************************************************pc mode******************************************************/
static const char *pc_mode_title[] = {"文件传输", "File Transmission"};
static const char *usb_plug_in_title[] = {"请插入usb", "Please plug in the usb"};
/*****************************************************pc mode******************************************************/

bool pc_mode_on = false;

static void screen_pc_mode_sw_pc_mode_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *target = lv_event_get_target(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
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

static void screen_pc_mode_page_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *target = lv_event_get_target(e);

	int page_y = lv_obj_get_y(target);
	int page_height = lv_obj_get_height(target);

	switch (code) {
	case LV_EVENT_SIZE_CHANGED :
	{
		/* printf("page_y: %d", lv_obj_get_y(target)); */
		if(guider_ui.screen_pc_mode) {
			lv_obj_set_style_bg_opa(guider_ui.screen_pc_mode_cont_pc_mode, LV_OPA_COVER - LV_OPA_COVER * LV_ABS(page_y) / page_height, 0);
		}
	
		break;
	}
	default:
		break;
	}
}

void events_init_screen_pc_mode(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_pc_mode_sw_pc_mode, screen_pc_mode_sw_pc_mode_event_handler, LV_EVENT_ALL, NULL);
#if PC_MODE_OPA_ENABLE
	if(ui->screen_pc_mode->parent) {
		lv_obj_add_event_cb(ui->screen_pc_mode->parent, screen_pc_mode_page_event_handler, LV_EVENT_ALL, NULL);
	}
#endif
}

bool screen_pc_mode_loaded;
void screen_pc_mode_refresh()
{
	//判断页面存活
	if(!screen_pc_mode_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_pc_mode_label_file_transfer, pc_mode_title[0]);
		lv_label_set_text(guider_ui.screen_pc_mode_label_usb_tip, usb_plug_in_title[0]);
	}
#else
	lv_label_set_text_fmt(guider_ui.screen_pc_mode_label_file_transfer, "%s", pc_mode_title[language]);
	lv_label_set_text_fmt(guider_ui.screen_pc_mode_label_usb_tip, "%s", usb_plug_in_title[language]);
#endif
	// lv_label_set_text_fmt(guider_ui.screen_pc_mode_label_file_transfer, "%s", pc_mode_title[language]);
	// lv_label_set_text_fmt(guider_ui.screen_pc_mode_label_usb_tip, "%s", usb_plug_in_title[language]);

	u8 box_charging = box_info_base_cb.lv_box_charging_get();

	if(box_charging) {
		lv_obj_clear_flag(guider_ui.screen_pc_mode_cont_file, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_pc_mode_cont_plug_in_tip, LV_OBJ_FLAG_HIDDEN);
	} else {
		lv_obj_clear_state(guider_ui.screen_pc_mode_sw_pc_mode, LV_STATE_CHECKED); // 拔出充电器时关闭pc模式选中
		
		lv_obj_add_flag(guider_ui.screen_pc_mode_cont_file, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_pc_mode_cont_plug_in_tip, LV_OBJ_FLAG_HIDDEN);
	}
}