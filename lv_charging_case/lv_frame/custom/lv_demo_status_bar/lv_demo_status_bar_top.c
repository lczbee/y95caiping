#include "custom.h"

lv_status_bar_top status_bar_top;

bool status_bar_top_loaded;

void lv_status_bar_top_init(lv_obj_t *page)
{
	// 创建容器为父控件
	status_bar_top.cont = lv_img_create(page);
	lv_obj_set_pos(status_bar_top.cont, 0, 0);
	lv_obj_set_size(status_bar_top.cont, 320, 24);
	lv_obj_set_scrollbar_mode(status_bar_top.cont, LV_SCROLLBAR_MODE_OFF);

	lv_obj_set_style_border_width(status_bar_top.cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(status_bar_top.cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(status_bar_top.cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(status_bar_top.cont, LV_OBJ_FLAG_FLOATING);

    //Write codes label_battery_boximg_bt_state
	status_bar_top.img_bt_state = lv_img_create(status_bar_top.cont);
	lv_obj_add_flag(status_bar_top.img_bt_state, LV_OBJ_FLAG_FLOATING);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(img_bt_state, "C:\\Users\\12568\\Desktop\\客户目录\\【格兰图】彩屏仓\\earphone_320x172\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\ic_yilianjie.png");
#else
	lv_img_set_src(status_bar_top.img_bt_state, "F:/ic_yilianjie.bin");
#endif
	lv_img_set_pivot(status_bar_top.img_bt_state, 50,50);
	lv_img_set_angle(status_bar_top.img_bt_state, 0);
	lv_obj_set_pos(status_bar_top.img_bt_state, 29, 0);
	lv_obj_set_size(status_bar_top.img_bt_state, 14, 18);

	//Write style for label_battery_boximg_bt_state, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(status_bar_top.img_bt_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes label_battery_boxlabel_battery_left
	status_bar_top.label_battery_left = lv_label_create(status_bar_top.cont);
	lv_label_set_text(status_bar_top.label_battery_left, "--%%");
	lv_label_set_long_mode(status_bar_top.label_battery_left, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(status_bar_top.label_battery_left, 66, 8);
	lv_obj_set_size(status_bar_top.label_battery_left, 100, 20);
    lv_obj_add_flag(status_bar_top.label_battery_left, LV_OBJ_FLAG_FLOATING);

	//Write style for label_battery_boxlabel_battery_left, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(status_bar_top.label_battery_left, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(status_bar_top.label_battery_left, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(status_bar_top.label_battery_left, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(status_bar_top.label_battery_left, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(status_bar_top.label_battery_left, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes label_battery_boxlabel_battery_right
	status_bar_top.label_battery_right = lv_label_create(status_bar_top.cont);
	lv_label_set_text(status_bar_top.label_battery_right, "--%%");
	lv_label_set_long_mode(status_bar_top.label_battery_right, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(status_bar_top.label_battery_right, 122, 8);
	lv_obj_set_size(status_bar_top.label_battery_right, 100, 20);
    lv_obj_add_flag(status_bar_top.label_battery_right, LV_OBJ_FLAG_FLOATING);

	//Write style for label_battery_boxlabel_battery_right, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(status_bar_top.label_battery_right, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(status_bar_top.label_battery_right, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(status_bar_top.label_battery_right, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(status_bar_top.label_battery_right, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(status_bar_top.label_battery_right, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes label_battery_boxlabel_battery_box
	status_bar_top.label_battery_box = lv_label_create(status_bar_top.cont);
	lv_label_set_text(status_bar_top.label_battery_box, "--%%");
	lv_label_set_long_mode(status_bar_top.label_battery_box, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(status_bar_top.label_battery_box, 178, 8);
	lv_obj_set_size(status_bar_top.label_battery_box, 100, 20);
    lv_obj_add_flag(status_bar_top.label_battery_box, LV_OBJ_FLAG_FLOATING);

	//Write style for label_battery_boxlabel_battery_box, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(status_bar_top.label_battery_box, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(status_bar_top.label_battery_box, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(status_bar_top.label_battery_box, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(status_bar_top.label_battery_box, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(status_bar_top.label_battery_box, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes label_battery_boxlabel_time
	status_bar_top.label_time = lv_label_create(status_bar_top.cont);
	lv_label_set_text(status_bar_top.label_time, "10:54");
	lv_label_set_long_mode(status_bar_top.label_time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(status_bar_top.label_time, 243, 8);
	lv_obj_set_size(status_bar_top.label_time, 100, 20);
    lv_obj_add_flag(status_bar_top.label_time, LV_OBJ_FLAG_FLOATING);

	//Write style for label_battery_boxlabel_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(status_bar_top.label_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(status_bar_top.label_time, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(status_bar_top.label_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(status_bar_top.label_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(status_bar_top.label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_add_flag(label_time, LV_OBJ_FLAG_HIDDEN);

	//Write codes label_battery_boximg_right_bat
	status_bar_top.img_right_bat = lv_img_create(status_bar_top.cont);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(img_right_bat, "C:\\Users\\12568\\Desktop\\客户目录\\【格兰图】彩屏仓\\earphone_320x172\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\icon_right.png");
#else
	lv_img_set_src(status_bar_top.img_right_bat, "F:/icon_right.bin");
#endif
	lv_img_set_pivot(status_bar_top.img_right_bat, 50,50);
	lv_img_set_angle(status_bar_top.img_right_bat, 0);
	lv_obj_set_pos(status_bar_top.img_right_bat, 136, 6);
	lv_obj_set_size(status_bar_top.img_right_bat, 16, 16);
    lv_obj_add_flag(status_bar_top.img_right_bat, LV_OBJ_FLAG_FLOATING);

	//Write style for label_battery_boximg_right_bat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(status_bar_top.img_right_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes label_battery_boximg_left_bat
	status_bar_top.img_left_bat = lv_img_create(status_bar_top.cont);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(img_left_bat, "C:\\Users\\12568\\Desktop\\客户目录\\【格兰图】彩屏仓\\earphone_320x172\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\icon_left.png");
#else
	lv_img_set_src(status_bar_top.img_left_bat, "F:/icon_left.bin");
#endif
	lv_img_set_pivot(status_bar_top.img_left_bat, 50,50);
	lv_img_set_angle(status_bar_top.img_left_bat, 0);
	lv_obj_set_pos(status_bar_top.img_left_bat, 80, 6);
	lv_obj_set_size(status_bar_top.img_left_bat, 16, 16);
    lv_obj_add_flag(status_bar_top.img_left_bat, LV_OBJ_FLAG_FLOATING);

	//Write style for label_battery_boximg_left_bat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(status_bar_top.img_left_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes label_battery_boximg_box_bat
	status_bar_top.img_box_bat = lv_img_create(status_bar_top.cont);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(img_box_bat, "C:\\Users\\12568\\Desktop\\客户目录\\【格兰图】彩屏仓\\earphone_320x172\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\icon_chargingbay.png");
#else
	lv_img_set_src(status_bar_top.img_box_bat, "F:/icon_chargingbay.bin");
#endif
	lv_img_set_pivot(status_bar_top.img_box_bat, 50,50);
	lv_img_set_angle(status_bar_top.img_box_bat, 0);
	lv_obj_set_pos(status_bar_top.img_box_bat, 192, 6);
	lv_obj_set_size(status_bar_top.img_box_bat, 16, 16);
    lv_obj_add_flag(status_bar_top.img_box_bat, LV_OBJ_FLAG_FLOATING);

	//Write style for label_battery_boximg_box_bat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(status_bar_top.img_box_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	status_bar_top_loaded = true;
}

void lv_status_bar_top_show()
{
	if(status_bar_top.cont) {
		b_printf("[bar top] show");
		lv_obj_clear_flag(status_bar_top.cont, LV_OBJ_FLAG_HIDDEN);
	}
}

void lv_status_bar_top_hide()
{
	if(status_bar_top.cont) {
		b_printf("[bar top] hide");
		lv_obj_add_flag(status_bar_top.cont, LV_OBJ_FLAG_HIDDEN);
	}
}

void status_bar_top_refresh()
{
	//判断页面存活
	if(!status_bar_top_loaded){return;}
	// printf("%s\n", __FUNCTION__);

#if PAGE_MOVE_COVER_MODE
    // 保持在最上层
	lv_obj_move_foreground(status_bar_top.cont);
#endif

	// //语言更新
	// u8 language = box_info_base_cb.lv_language_get();
	// switch (language) {
	// 	case CHINESE:
	// 		break;
	// 	case ENGLISH:
	// 		break;
	// 	default:
	// 		break;
	// }
	
    // //使能状态刷新
	// u8 phone_state = box_info_base_cb.lv_phone_state_get();
	// u8 earphone_state = box_info_base_cb.lv_earphone_state_get();
	// u8 contorl_enable = (phone_state | earphone_state) ? true : false;
	// if(contorl_enable){
	// }else{
	// }

	//状态刷新

    //更新时间
	struct sys_time time = {0};
	sbox_get_sys_time(&time);
	// printf("%s %d box_hour:%d\n", __FUNCTION__, __LINE__, box_hour);
	// printf("%s %d box_minute:%d\n", __FUNCTION__, __LINE__, box_minute);
    lv_label_set_text_fmt(status_bar_top.label_time, "%02d:%02d", time.hour, time.min);

	//更新蓝牙图标
	int phone_state = box_info_base_cb.lv_phone_state_get();
	int earphone_state = box_info_base_cb.lv_earphone_state_get();
	// printf("%s %d phone_state:%d\n", __FUNCTION__, __LINE__, phone_state);
	// printf("%s %d earphone_state:%d\n", __FUNCTION__, __LINE__, earphone_state);

    switch (earphone_state) {
        case BLE_CONNECTED:
			if(phone_state){
				lv_img_set_src(status_bar_top.img_bt_state, "F:/ic_yilianjie.bin");
			}else{
				lv_img_set_src(status_bar_top.img_bt_state, "F:/ic_boxcon_phonediscon.bin");
			}
			break;
		case BLE_DISCONNET:
            lv_img_set_src(status_bar_top.img_bt_state, "F:/ic_lanyaweilianjie.bin");
            break;
        default:
            break;
    }

	//更新充电图标
	int box_charging = box_info_base_cb.lv_box_charging_get();
	int left_charging = box_info_base_cb.lv_l_charging_get();
	int right_charging = box_info_base_cb.lv_r_charging_get();
	int l_ear_bat = box_info_base_cb.lv_l_ear_bat_get();
	int r_ear_bat = box_info_base_cb.lv_r_ear_bat_get();
	int box_bat = box_info_base_cb.lv_box_bat_get();
	// printf("%s %d box_charging:%d\n", __FUNCTION__, __LINE__, box_charging);
	// printf("%s %d left_charging:%d\n", __FUNCTION__, __LINE__, left_charging);
	// printf("%s %d right_charging:%d\n", __FUNCTION__, __LINE__, right_charging);
	// printf("%s %d l_ear_bat:%d\n", __FUNCTION__, __LINE__, l_ear_bat);
	// printf("%s %d r_ear_bat:%d\n", __FUNCTION__, __LINE__, r_ear_bat);
	// printf("%s %d box_bat:%d\n", __FUNCTION__, __LINE__, box_bat);


	if(left_charging){
		lv_img_set_src(status_bar_top.img_left_bat, "F:/L_chongdian.bin");
	}else{
		lv_img_set_src(status_bar_top.img_left_bat, "F:/icon_left.bin");
	}

	if(right_charging){
		lv_img_set_src(status_bar_top.img_right_bat, "F:/R_chongdian.bin");
	}else{
		lv_img_set_src(status_bar_top.img_right_bat, "F:/icon_right.bin");
	}

	if(box_charging){
		lv_img_set_src(status_bar_top.img_box_bat, "F:/B_chongdian.bin");
	}else{
		//仓低电图标(低于10%)
		if(box_bat <= 10){
			lv_img_set_src(status_bar_top.img_box_bat, "F:/lowpower.bin");
		}else{
			lv_img_set_src(status_bar_top.img_box_bat, "F:/icon_chargingbay.bin");
		}
	}


    //更新电量
    lv_label_set_text_fmt(status_bar_top.label_battery_left, "%d%c", l_ear_bat, '%');
    lv_label_set_text_fmt(status_bar_top.label_battery_right, "%d%c", r_ear_bat, '%');

	extern int now_soc_trim_info;
	if(box_bat == 255){
		lv_label_set_text_fmt(status_bar_top.label_battery_box, "--%%");
	} else {
		lv_label_set_text_fmt(status_bar_top.label_battery_box, "%d%c", box_bat, '%');
	}
}