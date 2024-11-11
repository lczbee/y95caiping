#include "ui_msg_action.h"
#include "os/os_api.h"

static u8 hinder_msg = 0;

void usr_hinder_msg(u8 i){
    hinder_msg = i;
}

static void trig_ui_vcb(void (*func)(void)){
    printf("ui:%x",func);
    func();
}

int send_to_trig_ui_vcb(void (*func)(void))
{
    if(hinder_msg)return 0;
    printf("send_to_trig_ui_vcb:%x",func);
    int argv[3];

    argv[0] = (int)trig_ui_vcb;
    argv[1] = 1;
    argv[2] = func; 

    int ret = os_taskq_post_type("ui", Q_CALLBACK, 3, argv);
	if (ret) {
		printf("post ret:%d \n", ret);
	}   
	return 0;
}


static void trig_app_core_vcb(void (*func)(void)){
    printf("ui:%x",func);
    func();
}

int send_to_trig_app_core_vcb(void (*func)(void))
{
    if(hinder_msg)return 0;
    printf("send_to_trig_ui_vcb:%x",func);
    int argv[3];

    argv[0] = (int)trig_app_core_vcb;
    argv[1] = 1;
    argv[2] = func; 

    int ret = os_taskq_post_type("app_core", Q_CALLBACK, 3, argv);
	if (ret) {
		printf("post ret:%d \n", ret);
	}   
	return 0;
}