#include "custom.h"

static void screen_upgrade_init()
{
	printf("%s\n", __FUNCTION__);

	setup_scr_screen_upgrade(&guider_ui, NULL);
	events_init_screen_upgrade(&guider_ui);
}

static void screen_upgrade_deinit()
{
	printf("%s\n", __FUNCTION__);

	lv_obj_del(guider_ui.screen_upgrade);
	guider_ui.screen_upgrade = NULL;
}

static void screen_upgrade_load()
{
	lv_scr_load(guider_ui.screen_upgrade);
}

void screen_upgrade_enter()
{
	// lv_status_bar_top_hide();
	screen_list_add(screen_upgrade_init, screen_upgrade_deinit, screen_upgrade_load, NULL, SCREEN_PRIO_UPGRADE);
}

void screen_upgrade_exit()
{
	screen_list_del(SCREEN_PRIO_UPGRADE);
}

void events_init_screen_upgrade(lv_ui *ui)
{
	
}

void screen_upgrade_check()
{
	if(app_get_curr_task() == 13){
        if(!guider_ui.screen_upgrade) {
			screen_upgrade_enter();
		}
    } else {
		if(guider_ui.screen_upgrade) {
			screen_upgrade_exit();
		}
	}
}