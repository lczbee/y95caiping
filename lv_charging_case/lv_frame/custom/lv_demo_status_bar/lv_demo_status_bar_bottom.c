#include "custom.h"

lv_status_bar_bottom status_bar_bottom;

bool status_bar_bottom_loaded;

void lv_status_bar_bottom_init(lv_obj_t *page)
{
    // 创建容器为父控件
	status_bar_bottom.cont = lv_img_create(page);
	lv_obj_set_pos(status_bar_bottom.cont, 113, 157);
	lv_obj_set_size(status_bar_bottom.cont, 96, 6);
	lv_obj_set_scrollbar_mode(status_bar_bottom.cont, LV_SCROLLBAR_MODE_OFF);

	lv_obj_set_style_border_width(status_bar_bottom.cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(status_bar_bottom.cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(status_bar_bottom.cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(status_bar_bottom.cont, LV_OBJ_FLAG_FLOATING);

    //Write codes screen_loop_slider_buttom
	status_bar_bottom.img_slider_bottom = lv_img_create(status_bar_bottom.cont);
	lv_obj_add_flag(status_bar_bottom.img_slider_bottom, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(status_bar_bottom.img_slider_bottom, "C:\\Users\\12568\\Desktop\\客户目录\\【格兰图】彩屏仓\\earphone_320x172\\gui_guider_ui\\earphone_flash\\earphone\\import\\image\\page_10_01.png");
#else
	lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_01.bin");
#endif
	lv_img_set_pivot(status_bar_bottom.img_slider_bottom, 50,50);
	lv_img_set_angle(status_bar_bottom.img_slider_bottom, 0);
	lv_obj_set_pos(status_bar_bottom.img_slider_bottom, 0, 0);
	lv_obj_set_size(status_bar_bottom.img_slider_bottom, 96, 6);

	//Write style for screen_loop_slider_buttom, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(status_bar_bottom.img_slider_bottom, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_add_flag(ui->screen_loop_slider_buttom, LV_OBJ_FLAG_HIDDEN);

    status_bar_bottom_loaded = true;
}

extern PageTypeHandle screen_menu;

void lv_upadate_status_bar_bottom_by_id(enum PageId id)
{
    if (status_bar_bottom.img_slider_bottom) {
        switch (id) {
            case ID_SCREEN_MUSIC:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_01.bin");
                break;

            case ID_SCREEN_VOLUME:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_02.bin");
                break;

            case ID_SCREEN_ANC:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_03.bin");
                break;

            case ID_SCREEN_EQUALIZER:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_04.bin");
                break;

            case ID_SCREEN_ALARM:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_05.bin");
                break;

            case ID_SCREEN_BRIGHTNESS:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_06.bin");
                break;

            case ID_SCREEN_LANGUAGE:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_07.bin");
                break;

            case ID_SCREEN_WALLPAPER:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_08.bin");
                break;

            case ID_SCREEN_FINDMY:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_09.bin");
                break;

            case ID_SCREEN_LIGHT:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_10.bin");
                break;

            case ID_SCREEN_TIME:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_01.bin");
                break;

            case ID_SCREEN_TIKTOK:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_01.bin");
                break;

            case ID_SCREEN_SNAP:
                lv_img_set_src(status_bar_bottom.img_slider_bottom, "F:/page_10_01.bin");
                break;
            
            default:
                break;
        }
    }
}

void lv_status_bar_bottom_show()
{
    if(status_bar_bottom.cont) {
        lv_obj_clear_flag(status_bar_bottom.cont, LV_OBJ_FLAG_HIDDEN);
    }
}

void lv_status_bar_bottom_hide()
{
    if(status_bar_bottom.cont) {
        lv_obj_add_flag(status_bar_bottom.cont, LV_OBJ_FLAG_HIDDEN);
    }
}


void status_bar_bottom_refresh()
{
	//判断页面存活
	if(!status_bar_bottom_loaded){return;}
    // printf("%s\n", __FUNCTION__);

#if PAGE_MOVE_COVER_MODE
    // 保持在最上层
    lv_obj_move_foreground(status_bar_bottom.cont);
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

	// //状态刷新
	// if(contorl_enable){
	// }
}

