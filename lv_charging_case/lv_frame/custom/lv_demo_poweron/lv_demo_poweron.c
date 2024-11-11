#include "custom.h"

static lv_timer_t * poweron_timer = NULL;

static void screen_poweron_init()
{
	printf("%s\n", __FUNCTION__);

	setup_scr_screen_poweron(&guider_ui, NULL);

}

static void screen_poweron_deinit()
{
	printf("%s\n", __FUNCTION__);

	// usr_free_state_img("PWO");
	if(guider_ui.screen_poweron) {
		usr_free_animing(guider_ui.screen_poweron_animimg_poweron, (const void **) screen_poweron_animimg_poweron_imgs, 1, 100, LV_ANIM_REPEAT_INFINITE);
	}
	// lv_status_bar_top_show();
	lv_obj_del(guider_ui.screen_poweron);
	guider_ui.screen_poweron = NULL;
}

static void screen_poweron_load()
{
	lv_scr_load(guider_ui.screen_poweron);
}

static void poweron_timer_cb(lv_timer_t *timer)
{
	screen_list_del(SCREEN_PRIO_POWERON);

	if(poweron_timer){
		lv_timer_del(poweron_timer);
		poweron_timer = NULL;
	}
}


void screen_poweron_enter()
{
	lv_status_bar_top_hide();
	screen_list_add(screen_poweron_init, screen_poweron_deinit, screen_poweron_load, NULL, SCREEN_PRIO_POWERON);

	if(!poweron_timer){
		poweron_timer = lv_timer_create(poweron_timer_cb, POWERON_PLAYTIME, NULL);
	}
}