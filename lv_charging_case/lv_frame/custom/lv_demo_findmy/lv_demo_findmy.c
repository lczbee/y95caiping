#include "custom.h"

static int find_my_flag = 0;
static const char *find_earphone_title[] = {"找到我的耳机", "Find My Earphone"};
static const char *take_off_earphone_title[] = {"摘下耳机", "Take Off Earphone"};

/*************************抢断页面****************************/
static void screen_findmy_load()
{
	lv_scr_load(guider_ui.screen_findmy);
}

void screen_findmy_enter()
{
	screen_list_add(init_screen_findmy, deinit_screen_findmy, screen_findmy_load, screen_findmy_refresh, SCREEN_PRIO_FINDMY);
}

void screen_findmy_exist()
{
	screen_list_del(SCREEN_PRIO_FINDMY);
}
/*************************抢断页面****************************/

static void screen_findmy_cont_findmy_event_handler (lv_event_t *e)
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
			screen_list_del(SCREEN_PRIO_FINDMY);
            break;
        }
		break;
	}
	default:
		break;
	}
}

// 查找L耳机
static void screen_findmy_imgbtn_findmy_left_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		int l_finding = box_info_base_cb.lv_l_finding_get();
		int r_finding = box_info_base_cb.lv_r_finding_get();
		int language = box_info_base_cb.lv_language_get();
		if (l_finding)
		{
			if(r_finding){
				box_info_send_cb.lv_find_my_cmd_send(CMD_FIND_MY_R);
				box_info_base_cb.lv_l_finding_set(FALSE);
				box_info_base_cb.lv_r_finding_set(TRUE);
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_zuoer_lianjie.bin", NULL);
				if(language == CHINESE) {
					lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);
				} else if(language == ENGLISH) {
					lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji_eng.bin", NULL);
				}
				
				// lv_obj_clear_state(guider_ui.screen_findmy_imgbtn_findmy_right, LV_STATE_CHECKED);
				// lv_obj_add_state(guider_ui.screen_findmy_imgbtn_findmy_left, LV_STATE_CHECKED);
			}else{
				box_info_send_cb.lv_find_my_cmd_send(CMD_FIND_CLOSE);
				box_info_base_cb.lv_l_finding_set(FALSE);
				box_info_base_cb.lv_r_finding_set(FALSE);

				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_zuoer_lianjie.bin", NULL);
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_youer_lianjie.bin", NULL);
				// lv_obj_clear_state(guider_ui.screen_findmy_imgbtn_findmy_left, LV_STATE_CHECKED);
				// lv_obj_clear_state(guider_ui.screen_findmy_imgbtn_findmy_right, LV_STATE_CHECKED);
			}
		}else{
			find_my_flag = FIND_MY_L;

			lv_obj_add_flag(guider_ui.screen_findmy_cont_findmy, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_findmy_cont_findmy_confirm, LV_OBJ_FLAG_HIDDEN);
		}
		break;
	}
	default:
		break;
	}
}

// 查找R耳机
static void screen_findmy_imgbtn_findmy_right_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};
		
		int l_finding = box_info_base_cb.lv_l_finding_get();
		int r_finding = box_info_base_cb.lv_r_finding_get();
		int language = box_info_base_cb.lv_language_get();
		if (r_finding)
		{
			if(l_finding){
				box_info_send_cb.lv_find_my_cmd_send(CMD_FIND_MY_L);
				box_info_base_cb.lv_r_finding_set(FALSE);
				box_info_base_cb.lv_l_finding_set(TRUE);

				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_youer_lianjie.bin", NULL);
				if(language == CHINESE) {
					lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);
				} else if(language == ENGLISH) {
					lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji_eng.bin", NULL);
				}

				// lv_obj_clear_state(guider_ui.screen_findmy_imgbtn_findmy_right, LV_STATE_CHECKED);
				// lv_obj_add_state(guider_ui.screen_findmy_imgbtn_findmy_left, LV_STATE_CHECKED);
			}else{
				box_info_send_cb.lv_find_my_cmd_send(CMD_FIND_CLOSE);
				box_info_base_cb.lv_l_finding_set(FALSE);
				box_info_base_cb.lv_r_finding_set(FALSE);

				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_zuoer_lianjie.bin", NULL);
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_youer_lianjie.bin", NULL);

				// lv_obj_clear_state(guider_ui.screen_findmy_imgbtn_findmy_left, LV_STATE_CHECKED);
				// lv_obj_clear_state(guider_ui.screen_findmy_imgbtn_findmy_right, LV_STATE_CHECKED);
			}
		}else{
			find_my_flag = FIND_MY_R;

			lv_obj_add_flag(guider_ui.screen_findmy_cont_findmy, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.screen_findmy_cont_findmy_confirm, LV_OBJ_FLAG_HIDDEN);
		}
		break;
	}
	default:
		break;
	}
}

// 取消查找耳机
static void screen_findmy_imgbtn_findmy_cancel_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		lv_obj_add_flag(guider_ui.screen_findmy_cont_findmy_confirm, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_findmy_cont_findmy, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}

// 开始查找耳机
static void screen_findmy_imgbtn_findmy_start_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	screen_scroll_check(e);		//人为判断是否滑动事件，规避循坏页面管理器之下的屏幕无法识别滑动问题

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//避免页面滑动误触
		if(screen_scrolled){screen_scrolled = false;return;};

		int l_finding = box_info_base_cb.lv_l_finding_get();
		int r_finding = box_info_base_cb.lv_r_finding_get();
		int language = box_info_base_cb.lv_language_get();
		if(l_finding || r_finding){

			if(language == CHINESE) {
				//切换查找中按钮图标
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);
			} else if(language == ENGLISH) {
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji_eng.bin", NULL);
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji_eng.bin", NULL);
			}
			

			// lv_obj_add_state(guider_ui.screen_findmy_imgbtn_findmy_left, LV_STATE_CHECKED);
			// lv_obj_add_state(guider_ui.screen_findmy_imgbtn_findmy_right, LV_STATE_CHECKED);

			box_info_send_cb.lv_find_my_cmd_send(CMD_FIND_MY_LR);
			box_info_base_cb.lv_r_finding_set(TRUE);
			box_info_base_cb.lv_l_finding_set(TRUE);
			
		}else{

			if (find_my_flag == FIND_MY_L)
			{
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_youer_lianjie.bin", NULL);
				if(language == CHINESE) {
					lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);
				} else if(language == ENGLISH) {
					lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji_eng.bin", NULL);
				}
				// lv_obj_add_state(guider_ui.screen_findmy_imgbtn_findmy_left, LV_STATE_CHECKED);
				box_info_send_cb.lv_find_my_cmd_send(CMD_FIND_MY_L);
				box_info_base_cb.lv_l_finding_set(TRUE);
				box_info_base_cb.lv_r_finding_set(FALSE);
			}
			
			if (find_my_flag == FIND_MY_R)
			{
				lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_zuoer_lianjie.bin", NULL);
				if(language == CHINESE) {
					lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);
				} else if(language == ENGLISH) {
					lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_RELEASED, NULL, "F:/ic_kaishizhaoerji_eng.bin", NULL);
				}
				// lv_obj_add_state(guider_ui.screen_findmy_imgbtn_findmy_right, LV_STATE_CHECKED);
				box_info_send_cb.lv_find_my_cmd_send(CMD_FIND_MY_R);
				box_info_base_cb.lv_r_finding_set(TRUE);
				box_info_base_cb.lv_l_finding_set(FALSE);
			}
		}

		lv_obj_add_flag(guider_ui.screen_findmy_cont_findmy_confirm, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_findmy_cont_findmy, LV_OBJ_FLAG_HIDDEN);

		break;
	}
	default:
		break;
	}
}

void events_init_screen_findmy(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_findmy_imgbtn_findmy_left, screen_findmy_imgbtn_findmy_left_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_findmy_imgbtn_findmy_right, screen_findmy_imgbtn_findmy_right_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_findmy_imgbtn_findmy_cancel, screen_findmy_imgbtn_findmy_cancel_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_findmy_imgbtn_findmy_start, screen_findmy_imgbtn_findmy_start_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_findmy_cont_findmy, screen_findmy_cont_findmy_event_handler, LV_EVENT_ALL, NULL);
}


bool screen_findmy_loaded;
void screen_findmy_refresh()
{
	//判断页面存活
	if(!screen_findmy_loaded){return;}
	// printf("%s\n", __FUNCTION__);

	//语言更新
	u8 language = box_info_base_cb.lv_language_get();

#if MULT_ENLAUGE_REMAP_ENABLE
	if(!lv_set_language(language)) {
		lv_label_set_text(guider_ui.screen_findmy_label_findmy_title, find_earphone_title[0]);
		lv_label_set_text(guider_ui.screen_findmy_label_findmy_confirm_title, take_off_earphone_title[0]);

	}
#else
	lv_label_set_text_fmt(guider_ui.screen_findmy_label_findmy_title, "%s", find_earphone_title[language]);
	lv_label_set_text_fmt(guider_ui.screen_findmy_label_findmy_confirm_title, "%s", take_off_earphone_title[language]);
#endif
	// lv_label_set_text_fmt(guider_ui.screen_findmy_label_findmy_title, "%s", find_earphone_title[language]);
	// lv_label_set_text_fmt(guider_ui.screen_findmy_label_findmy_confirm_title, "%s", take_off_earphone_title[language]);
	switch (language) {
		case CHINESE:
			lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_kaishizhaoerji.bin", NULL);
			// lv_img_set_src(guider_ui.screen_findmy_imgbtn_findmy_cancel, "F:/ic_quxiao_chazhaoerji.bin");
			// lv_img_set_src(guider_ui.screen_findmy_imgbtn_findmy_start, "F:/ic_kaishi_chazhaoerji.bin");
			break;
		case ENGLISH:
			lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_left, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_kaishizhaoerji_eng.bin", NULL);
			lv_imgbtn_set_src(guider_ui.screen_findmy_imgbtn_findmy_right, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "F:/ic_kaishizhaoerji_eng.bin", NULL);
			// lv_img_set_src(guider_ui.screen_findmy_imgbtn_findmy_cancel, "F:/ic_quxiao_chazhaoerji_eng.bin");
			// lv_img_set_src(guider_ui.screen_findmy_imgbtn_findmy_start, "F:/ic_kaishi_chazhaoerji_eng.bin");
			break;
		default:
			break;
	}


    //使能状态刷新
	u8 phone_state = box_info_base_cb.lv_phone_state_get();
	u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	if(contorl_enable){
		lv_obj_clear_state(guider_ui.screen_findmy_imgbtn_findmy_left, LV_STATE_DISABLED);
		lv_obj_clear_state(guider_ui.screen_findmy_imgbtn_findmy_right, LV_STATE_DISABLED);
	}else{
		lv_obj_add_state(guider_ui.screen_findmy_imgbtn_findmy_left, LV_STATE_DISABLED);
		lv_obj_add_state(guider_ui.screen_findmy_imgbtn_findmy_right, LV_STATE_DISABLED);
	}


	//状态刷新
	// if(contorl_enable){

	// }
}


