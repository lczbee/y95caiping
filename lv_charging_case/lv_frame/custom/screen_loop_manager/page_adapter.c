#include "custom.h"

extern bool screen_language_loaded;
extern bool screen_findmy_loaded;
extern bool screen_charging_loaded;
extern bool screen_equalizer_loaded;
extern bool screen_brightness_loaded;
extern bool screen_light_loaded;
extern bool screen_wallpaper_loaded;
extern bool screen_music_loaded;
extern bool screen_product_test_loaded;
extern bool screen_anc_loaded;
extern bool screen_time_loaded;
extern bool screen_time_cont_set_loaded;
extern bool screen_squelch_loaded;
extern bool screen_snap_loaded;
extern bool screen_tiktok_loaded;
extern bool screen_alarm_loaded;
extern bool screen_volume_loaded;
extern bool screen_pc_mode_loaded;
extern bool screen_menu_loaded;

#if PAGE_MOVE_COVER_MODE
static void lv_page_add_bg_img(lv_obj_t *page)
{
	lv_img_t* BgImg = lv_img_create(page);
	lv_obj_set_style_radius(BgImg, 0, 0);
	lv_obj_set_style_pad_all(BgImg, 0, 0);
	lv_obj_set_style_border_width(BgImg, 0, 0);
	lv_img_set_src(BgImg, "F:/bg.bin");
	lv_obj_move_background(BgImg);
	lv_obj_set_pos(BgImg, 0, 0);
	lv_obj_set_size(BgImg, 320, 172);
}
#endif

void lv_page_manager_page_adapte(lv_obj_t *page)
{
	lv_obj_set_style_border_width(page, 0, LV_PART_MAIN|LV_STATE_DEFAULT); // 使用页面管理时，要取消页面边框，必须有
	lv_obj_set_style_pad_all(page, 0, LV_PART_MAIN|LV_STATE_DEFAULT); // 使用页面管理时，要取消页面距离边界距离，必须有
	lv_obj_add_flag(page, LV_OBJ_FLAG_EVENT_BUBBLE); // 将消息传给父控件，必须有
}

void lv_page_manager_cont_adapte(lv_obj_t *page)
{
	lv_obj_add_flag(page, LV_OBJ_FLAG_EVENT_BUBBLE); // 将消息传给父控件，必须有
}

void lv_page_manager_obj_adapte(lv_obj_t *btn)
{
	lv_obj_add_flag(btn, LV_OBJ_FLAG_EVENT_BUBBLE); // 将消息传给父控件，必须有
}

// 抢断页面背景适配
void lv_page_manager_preempt_page_bg_adapte(lv_obj_t *page)
{
	// lv_obj_set_style_bg_opa(page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	// lv_obj_set_style_bg_color(page, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(page, "F:/bg.bin", 0);
}

// 抢断页面布局适配
void lv_page_manager_preempt_page_cont_adapte(lv_obj_t *page)
{
	lv_obj_add_flag(page, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE); // 将消息传给父控件，必须有
	lv_obj_clear_flag(page, LV_OBJ_FLAG_GESTURE_BUBBLE);
}

void init_screen_language(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_language_loaded = true;
	setup_scr_screen_language(&guider_ui, page);
	// setup_scr_screen_language(&guider_ui, NULL);
	events_init_screen_language(&guider_ui);
}

void init_screen_findmy(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_findmy_loaded = true;
	setup_scr_screen_findmy(&guider_ui, page);
	// setup_scr_screen_findmy(&guider_ui, NULL);
	events_init_screen_findmy(&guider_ui);
}

void init_screen_equalizer(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_equalizer_loaded = true;
	setup_scr_screen_equalizer(&guider_ui, page);
	// setup_scr_screen_equalizer(&guider_ui, NULL);
	events_init_screen_equalizer(&guider_ui);
}

void init_screen_brightness(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_brightness_loaded = true;
	setup_scr_screen_brightness(&guider_ui, page);
	// setup_scr_screen_brightness(&guider_ui, NULL);
	events_init_screen_brightness(&guider_ui);
}

void init_screen_light(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_light_loaded = true;
	setup_scr_screen_light(&guider_ui, page);
	// setup_scr_screen_light(&guider_ui, NULL);
	events_init_screen_light(&guider_ui);
}

void init_screen_wallpaper(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_wallpaper_loaded = true;
	setup_scr_screen_wallpaper(&guider_ui, page);
	// setup_scr_screen_wallpaper(&guider_ui, NULL);
	events_init_screen_wallpaper(&guider_ui);
	//animimg_update_screen_wallpaper();
}



void init_screen_music(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_music_loaded = true;
	setup_scr_screen_music(&guider_ui, page);
	// setup_scr_screen_music(&guider_ui, NULL);
	events_init_screen_music(&guider_ui);

#if LOCAL_MUSIC_ENABLE
	setup_scr_screen_music_local_music(&guider_ui);
	events_init_screen_music_local_music(&guider_ui);
// 	lv_sd_music_list_init();

// #if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
// 	usr_update_animing(guider_ui.screen_music_animimg_wait, "WAT");
// #endif

#endif /* LOCAL_MUSIC_ENABLE */

#if BT_LYRICS_ENABLE
	setup_scr_screen_music_lyrics(&guider_ui);
	events_init_screen_music_lyrics(&guider_ui);
	lv_music_lyrics_init();
#endif /* BT_LYRICS_ENABLE */

}

void init_screen_anc(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_anc_loaded = true;
	setup_scr_screen_anc(&guider_ui, page);
	// setup_scr_screen_anc(&guider_ui, NULL);
	events_init_screen_anc(&guider_ui);
	
	int anc_mode = box_info_base_cb.lv_anc_mode_get();
	b_printf("anc_mode: %d", anc_mode);
	lv_anc_mode_update(anc_mode);
}

void init_screen_time(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_time_loaded = true;
	setup_scr_screen_time(&guider_ui, page);
	// setup_scr_screen_time(&guider_ui, NULL);
	events_init_screen_time(&guider_ui);
}

// 静噪功能，暂未使用
void init_screen_squelch(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_squelch_loaded = true;
	setup_scr_screen_squelch(&guider_ui, page);
}

void init_screen_snap(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_snap_loaded = true;
	setup_scr_screen_snap(&guider_ui, page);
	// setup_scr_screen_snap(&guider_ui, NULL);
	events_init_screen_snap(&guider_ui);
}

void init_screen_tiktok(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_tiktok_loaded = true;
	setup_scr_screen_tiktok(&guider_ui, page);
	// setup_scr_screen_tiktok(&guider_ui, NULL);
	events_init_screen_tiktok(&guider_ui);
	setup_scr_screen_tiktok_rejust(&guider_ui);
	events_init_screen_tiktok_rejust(&guider_ui);
}

void init_screen_alarm(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_alarm_loaded = true;
	setup_scr_screen_alarm(&guider_ui, page);
	// setup_scr_screen_alarm(&guider_ui, NULL);
	events_init_screen_alarm(&guider_ui);
}

void init_screen_volume(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_volume_loaded = true;
	setup_scr_screen_volume(&guider_ui, page);
	// setup_scr_screen_volume(&guider_ui, NULL);
	events_init_screen_volume(&guider_ui);
}

void init_screen_pc_mode(lv_obj_t *page)
{
#if PAGE_MOVE_COVER_MODE
	lv_page_add_bg_img(page);
#endif

	printf("%s\n", __FUNCTION__);
	screen_pc_mode_loaded = true;
	setup_scr_screen_pc_mode(&guider_ui, page);
	if(pc_mode_on) {
		lv_obj_add_state(guider_ui.screen_pc_mode_sw_pc_mode, LV_STATE_CHECKED);
	} else {
		lv_obj_clear_state(guider_ui.screen_pc_mode_sw_pc_mode, LV_STATE_CHECKED);
	}
	events_init_screen_pc_mode(&guider_ui);
}

void init_screen_menu(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_menu_loaded = true;
	setup_scr_screen_menu(&guider_ui, page);
	lv_menu_init(page);
	events_init_screen_menu(&guider_ui);
}



void deinit_screen_language(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	lv_obj_del(guider_ui.screen_language);
	guider_ui.screen_language = NULL;
	screen_language_loaded = false;
}

void deinit_screen_findmy(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	lv_obj_del(guider_ui.screen_findmy);
	guider_ui.screen_findmy = NULL;
	screen_findmy_loaded = false;
}

void deinit_screen_equalizer(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_equalizer_loaded = false;
}

void deinit_screen_brightness(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	lv_obj_del(guider_ui.screen_brightness);
	guider_ui.screen_brightness = NULL;
	screen_brightness_loaded = false;
}

void deinit_screen_light(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	lv_obj_del(guider_ui.screen_light);
	guider_ui.screen_light = NULL;
	screen_light_loaded = false;
}

void deinit_screen_wallpaper(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_wallpaper_loaded = false;
	// usr_free_state_img(lock_small_tab[cur_lock_index]);
	/*
	if(guider_ui.screen_wallpaper) {
		usr_free_animing(guider_ui.screen_wallpaper_animimg_wp, (const void **) screen_wallpaper_animimg_wp_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	}	
	*/
	
	lv_obj_del(guider_ui.screen_wallpaper);
	guider_ui.screen_wallpaper = NULL;
}

void deinit_screen_music(lv_obj_t *page)
{

	guider_ui.screen_music = NULL;

	printf("%s\n", __FUNCTION__);
	screen_music_loaded = false;
#if LOCAL_MUSIC_ENABLE
	// free_music_file_handler();

	lv_sd_music_list_deinit();

#if (WAIT_ANIM_SELECT == WAIT_ANIMIMG)
	if(guider_ui.screen_music) {
		usr_free_animing(guider_ui.screen_music_animimg_wait, (const void **) screen_music_animimg_wait_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	}
#endif
	
	extern lv_timer_t *wait_timeout_timer;
	if(wait_timeout_timer){
		lv_timer_del(wait_timeout_timer);
		wait_timeout_timer = NULL;
	}
#endif
}

void deinit_screen_anc(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_anc_loaded = false;
}

void deinit_screen_time(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	lv_obj_del(guider_ui.screen_time);
	guider_ui.screen_time = NULL;
	screen_time_loaded = false;
	screen_time_cont_set_loaded = false;
}

void deinit_screen_squelch(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_squelch_loaded = false;
}

void deinit_screen_snap(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_snap_loaded = false;

	if(snap_timer) {
		lv_timer_del(snap_timer);
		snap_timer = NULL;
	}
}

void deinit_screen_tiktok(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_tiktok_loaded = false;

	if(tiktok_timer) {
		lv_timer_del(tiktok_timer);
		tiktok_timer = NULL;
	}
}

void deinit_screen_alarm(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	lv_obj_del(guider_ui.screen_alarm);
	guider_ui.screen_alarm = NULL;	
	screen_alarm_loaded = false;
}

void deinit_screen_volume(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_volume_loaded = false;
}

void deinit_screen_pc_mode(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_pc_mode_loaded = false;
}

void deinit_screen_menu(lv_obj_t *page)
{
	printf("%s\n", __FUNCTION__);
	screen_menu_loaded = false;
	lv_menu_deinit();
}



