#include "custom.h"

/*************************************参数配置**********************************************/
#if LV_DEMO_WEATHER_EN

#define WEATHER_DEBUG_EN	1
#if WEATHER_DEBUG_EN
#define WEATHER_DEBUG   b_printf
#else
#define WEATHER_DEBUG(...)
#endif
/*************************************参数配置**********************************************/


/************************************天气信息***********************************************/
#include "weather/weather.h"

static u8 *weather_type[] = {
    "晴",
    "少云",
    "晴间多云",
    "多云",
    "阴",
    "有风",
    "平静",
    "大风",
    "飓风",
    "风暴",
    "霾",
    "阵雨",
    "雷阵雨",
    "雷阵雨并伴有冰雹",
    "小雨",
    "中雨",
    "大雨",
    "暴雨",
    "大暴雨",
    "特大暴雨",
    "强阵雨",
    "强雷阵雨",
    "极端阵雨",
    "雨夹雪",
    "雪",
    "阵雪",
    "小雪",
    "中雪",
    "大雪",
    "暴雪",
    "浮尘",
    "扬沙",
    "沙尘暴",
    "强沙尘暴",
    "龙卷风",
    "雾",
    "热",
    "冷",
    "未知",
};

static u8 weather_type_num = sizeof(weather_type) / sizeof(weather_type[0]);

static struct __WEATHER_INFO weather_info;

void func_attr_weather_info_set(void *priv, u8 attr, u8 *data, u16 len)
{
    printf("->%s\n", __FUNCTION__);
    /* g_log_info("============="); */
    /* put_buf(data, len); */
    /* g_log_info("============="); */
    u8 province_name_len;
    u8 city_name_len;
    u8 offset = 0;
    u32 timestamp;

    province_name_len = data[offset];
    /* log_info("province_name_len:%d", province_name_len); */
    offset++;
    if (weather_info.province) {
        free(weather_info.province);
        weather_info.province = 0;
    }
    weather_info.province_name_len = province_name_len + 1;
    weather_info.province = zalloc(province_name_len + 1);
    if (!weather_info.province) {
        WEATHER_DEBUG("[weather] weather_info.province malloc fail");
        return;
    }
    memcpy(weather_info.province, data + offset, province_name_len);
    WEATHER_DEBUG("[weather] province_name_len : %d", weather_info.province_name_len);
    WEATHER_DEBUG("[weather] province:%s\n", weather_info.province);
    put_buf(weather_info.province, weather_info.province_name_len);

    offset += province_name_len;
    city_name_len = data[offset];
    /* WEATHER_DEBUG("city_name_len:%d", city_name_len); */
    offset++;
    if (weather_info.city) {
        free(weather_info.city);
        weather_info.city = 0;
    }

    weather_info.city_name_len = city_name_len + 1;
    weather_info.city = zalloc(city_name_len + 1);
    if (!weather_info.city) {
        WEATHER_DEBUG("[weather] weather_info.city malloc fail");
        return;
    }
    memcpy(weather_info.city, data + offset, city_name_len);
    WEATHER_DEBUG("[weather] city:%s", weather_info.city);

    offset += city_name_len;
    weather_info.weather = data[offset];
    WEATHER_DEBUG("[weather] weather_info.weather:%d", weather_info.weather);

    offset++;
    weather_info.temperature = data[offset];
    WEATHER_DEBUG("[weather] weather_info.temperature:%d", weather_info.temperature); 

    offset++;
    weather_info.humidity = data[offset];
    WEATHER_DEBUG("[weather] weather_info.humidity:%d", weather_info.humidity); 

    offset++;
    weather_info.wind_direction = data[offset];
    WEATHER_DEBUG("[weather] weather_info.wind_direction:%d", weather_info.wind_direction); 

    offset++;
    weather_info.wind_power = data[offset];
    WEATHER_DEBUG("[weather] weather_info.wind_power:%d", weather_info.wind_power);

    offset++;
    weather_info.update_time = (*(data + offset) << 24) | (*(data + offset + 1) << 16) | (*(data + offset + 2) << 8) | (*(data + offset + 3) << 0);
    timestamp = weather_info.update_time;
    /* log_info("%d年%d月%d日%d时%d分%d秒", ((timestamp >> 26) & 0x3f) + 2010, (timestamp >> 22) & 0xf, (timestamp >> 17) & 0x1f, (timestamp >> 12) & 0x1f, (timestamp >> 6) & 0x3f, timestamp & 0x3f); */

    // UI_MSG_POST("weather_info:event=%4", 0);
}
/************************************天气信息***********************************************/

static void screen_weather_init()
{
	printf("%s\n", __FUNCTION__);
    // lv_status_bar_top_hide();
	setup_scr_screen_weather(&guider_ui, NULL);
	events_init_screen_weather(&guider_ui);
	
}

static void screen_weather_deinit()
{
	printf("%s\n", __FUNCTION__);
    // lv_status_bar_top_show();
	lv_obj_del(guider_ui.screen_weather);
	guider_ui.screen_weather = NULL;
}
static void screen_weather_load()
{
	lv_scr_load(guider_ui.screen_weather);
}


static void screen_weather_cont_weather_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_GESTURE:
	{
        lv_indev_wait_release(lv_indev_get_act());
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir){
        case LV_DIR_LEFT:
            break;
        case LV_DIR_RIGHT:
			// 右滑退出天气页面
			screen_weather_exit();
			break;
        }
		break;
	}
	default:
		break;
	}
}


void events_init_screen_weather(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_weather_cont_weather, screen_weather_cont_weather_event_handler, LV_EVENT_ALL, NULL);
}


void screen_weather_enter()
{
	screen_list_add(screen_weather_init, screen_weather_deinit, screen_weather_load, screen_weather_refresh, SCREEN_PRIO_WEATHER);
}

void screen_weather_exit()
{
	screen_list_del(SCREEN_PRIO_WEATHER);
}

void screen_weather_refresh()
{
	char buf[64] = {0};
	char no_data[] = "---";

	lv_label_set_text_fmt(guider_ui.screen_weather_label_temperature, "%d°", weather_info.temperature);

	if(weather_info.weather < weather_type_num) {
		lv_label_set_text_fmt(guider_ui.screen_weather_label_weather, "%s", weather_type[weather_info.weather]);
	}

	if(weather_info.province && weather_info.city) {
		sprintf(buf, "%s市/%s", weather_info.province, weather_info.city);
	} else if(weather_info.province && weather_info.city == 0) {
		sprintf(buf, "%s/%s", weather_info.province, no_data);
	} else if(weather_info.province == 0 && weather_info.city) {
		sprintf(buf, "%s/%s", no_data, weather_info.city);
	} else {
		sprintf(buf, "%s/%s", no_data, no_data);
	}

	lv_label_set_text(guider_ui.screen_weather_label_location, buf);
	
	lv_label_set_text_fmt(guider_ui.screen_weather_label_humidness, "%d%%", weather_info.humidity);
	lv_label_set_text_fmt(guider_ui.screen_weather_label_wind, "%d级", weather_info.wind_power);
    
}

#endif