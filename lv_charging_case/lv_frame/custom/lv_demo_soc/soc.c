#include "soc.h"
#include "system/includes.h"
#include "app_power_manage.h"
#include "app_main.h"
#include "app_config.h"
#include "app_action.h"
#include "asm/charge.h"
#include "ui_manage.h"
#include "tone_player.h"
#include "asm/adc_api.h"
#include "btstack/avctp_user.h"
#include "user_cfg.h"
#include "bt.h"
#include "asm/charge.h"
#include "ui/ui_api.h"
#include "../../include/key_event_deal.h"
#include "smartbox_user_app.h"
#include "lvgl.h"

#define LOW_POWER_READREAD          0//比记忆低重新校准
#define DISP_TEST_SOC_UI_FIRST      0//校准显示UI

#define SOC_SIMULATE    0//仿真测试
#if LV_SOC_CHECK


//  低电参数
#define LOW_POW_STORAGE_MODE    0//1   //  低电是否直接进仓储模式
#define LOWPOWER_V              3.550           //低电提示电压
#define POWEROFF_V              3.500           //低电关机电压
#define POWEROFF_V_OFFSET       0.1             //开机滞回电压差，避免低电反复开机
// #define POWEROFF_SOC            0.01            //低电百分比关机
#define POWERSHUTDOWN_V         3.400           //严重低电关机电压
#define LOWPOWER_CNT            3               //关机计数3*8S关机


//  充电曲线
#define CHARGE_PA_END_V         4.1//0.1//4.300           //恒流结束电压（估计）
#define CHARGE_PA_START_V       (LOWPOWER_V+0.1)//3.5//0.0//3.500           //恒流开始电压（估计）
#define CHARGE_PA_END_SOC       0.8//0.0//0.8             //恒流结束百分比（估计）
#define CHARGE_PA_START_SOC     0.0//0.0             //恒流开始百分比（估计）
#define CHARGE_PV_TIME          0//(1*25*60*1000)//(1.0*60*60*1000)    //恒压充电时间（估计）

#if (CHARGE_PV_TIME  == 0)
#define CHARGE_PA_START_A       250 //  恒压充电开始电流
#define CHARGE_PA_END_A         20  //50  //  恒压充电满电电流
#endif

//  滤波参数
#define CHR_SPEED               0.003             //充电电量追赶速度
#define DIS_SPEED               0.001             //放电电量追赶速度
#define DIS_K                   0.2             //放电滤波系数，越大越快
#define CHANGE_FIL_TIME         10000           //切换过滤不靠谱时间
#define SOC_CICLE_TIME          8000            //电量循环读取时间


// #define ERROR_SOC               1.0//0.3             //放电差异太大需要重新读
// #define ZERO_RE_READ            0//1            //放电状态下 电量0 % 是否重新读，关闭比较保险
// #define CHARG_ZERO_RE_READ      0//1//0//             //第一次充电是否重读电量,982给过来的信息概率不准不建议开启
// 

// 校准
// #define charge_first_work_charge_out_trim_vbat   1//0//1
// #define NO_CHARGE_CNT       2//5//5次采样后才认为稳定
// #define     FIRST_START_INFO            /看VM序号实际配置
// #define     ALL_USR_CFG            34//看VM序号实际配置

// 放电曲线
// #define NEW_NUM_POINTS          3//11                   // 实际应用的电池曲线（放电）
static float cap_ocv[][2] = {
    {1.00, 4.1},//100%  //建议满电稍低一点，避免出现满电拔掉充电立即掉电的情况
    {0.10, LOWPOWER_V},//10%
    {0.00, POWEROFF_V},//0%
};

#define NEW_NUM_POINTS (ARRAY_SIZE(cap_ocv))


static void trig_vcb(void (*func)(void)){
    printf("os:%s func:%x", os_current_task(), func);
    func();
}

int send_to_trig_vcb(void (*func)(void), char*taskname)
{
    if(0)return 0;
    printf("send_to_trig_ui_vcb:%x",func);
    int argv[3];

    argv[0] = (int)trig_vcb;
    argv[1] = 1;
    argv[2] = func; 

    int ret = os_taskq_post_type(taskname, Q_CALLBACK, 3, argv);
	if (ret) {
		printf("post ret:%d \n", ret);
	}   
	return 0;
}
int now_soc_trim_info;

//  获取上电信息
u8 get_first_start_info(){
    int reset_sour=0;
    int vmret = syscfg_read(FIRST_START_INFO, &reset_sour, sizeof(reset_sour));
    if(vmret == sizeof(reset_sour)){
        g_printf("write_first_start_info 读VM成功: %d", reset_sour);
    }
    now_soc_trim_info = reset_sour;
    return reset_sour;
}
#if (CHARGE_PV_TIME)
int get_vbat_a_from_f98;
#else
extern int get_vbat_a_from_f98;
#endif
static u8 get_chr_cap(float ocv, float *soc){
    if(ocv<CHARGE_PA_START_V) {
        printf("%s %d",__func__,__LINE__);
        *soc = CHARGE_PA_START_SOC;         
    } else if(ocv>=CHARGE_PA_END_V){
        #if(CHARGE_PV_TIME)
            *soc += (float)SOC_CICLE_TIME/(float)CHARGE_PV_TIME*(1.0-CHARGE_PA_END_SOC);
            if(*soc > 1.0) *soc = 1.0;     
            printf("%s %d",__func__,__LINE__); 
            return 1;      
        #else
            *soc = CHARGE_PA_END_SOC + (CHARGE_PA_START_A - get_vbat_a_from_f98)*(1.0-CHARGE_PA_END_SOC)/(CHARGE_PA_START_A-CHARGE_PA_END_A);
            printf("%s %d",__func__,__LINE__);
            return 0;
        #endif
    } else { 
        printf("%s %d",__func__,__LINE__);   
        *soc = CHARGE_PA_START_SOC + (CHARGE_PA_END_SOC-CHARGE_PA_START_SOC)*(ocv-CHARGE_PA_START_V)/(CHARGE_PA_END_V-CHARGE_PA_START_V);
    }
printf("%s %d",__func__,__LINE__);
    return 0 ;
}

static float get_ocv(float cap) {
    if (cap >= cap_ocv[0][0]) {
        return cap_ocv[0][1];
    } else if (cap <= cap_ocv[NEW_NUM_POINTS-1][0]) {
        return cap_ocv[NEW_NUM_POINTS-1][1];
    } else {
        for (int i = 0; i < NEW_NUM_POINTS-1; i++) {
            if (cap <= cap_ocv[i][0] && cap >= cap_ocv[i + 1][0]) {
                float ocv = cap_ocv[i][1] + (cap - cap_ocv[i][0]) * (cap_ocv[i + 1][1] - cap_ocv[i][1]) / (cap_ocv[i + 1][0] - cap_ocv[i][0]);
                return ocv;
            }
        }
    }
}

static float get_cap(float ocv) {
    
    printf("%f %f %f %f", cap_ocv[0][1],cap_ocv[0][0],cap_ocv[NEW_NUM_POINTS-1][1],cap_ocv[NEW_NUM_POINTS-1][0]);
    if (ocv >= cap_ocv[0][1]) {
        return cap_ocv[0][0];
    } else if (ocv <= cap_ocv[NEW_NUM_POINTS-1][1]) {
        return cap_ocv[NEW_NUM_POINTS-1][0];
    } else {
        for (int i = 0; i < NEW_NUM_POINTS-1; i++) {
            if (ocv <= cap_ocv[i][1] && ocv >= cap_ocv[i + 1][1]) {
                float cap = cap_ocv[i][0] + (ocv - cap_ocv[i][1]) * (cap_ocv[i + 1][0] - cap_ocv[i][0]) / (cap_ocv[i + 1][1] - cap_ocv[i][1]);
                return cap;
            }
        }
    }
}




static int vm_vbat_value=0;
static void write_vm_vbat_value(int vm_value){
    if(vm_value<-1){
            vm_value=-1;
    }
    else if(vm_value>100){
        vm_value=-1;
    }
    printf("%s %d", __func__, vm_value);
    syscfg_write(VM_BAT_PRESENT, &vm_value, sizeof(vm_value));
}

static int read_vm_vbat_value()
{
    int vm_value=-1;
    int ret = syscfg_read(VM_BAT_PRESENT, &vm_value, sizeof(vm_value));
    if(ret > 0) {
        if(vm_value<0){
            vm_value=-1;
        }
        else if(vm_value>100){
            vm_value=-1;
        }
        
        printf(">>>>>>>>> VM init val is %d", vm_vbat_value);
    } else {
        vm_value = -1;
    }

    // vm_vbat_value = vm_value;
    return vm_value;
}

u8 check_bat_vm_is_vaild(){
    if(-1 == read_vm_vbat_value()){
        return 0;
    } else {
        return 1;
    }
}


static float disp_soc;
static void soc_calculate_loop(void *p);
static void low_enter_poweroff();
static void force_poweroff(void *p);
// #include "lvgl.h"

int get_curr_soc(){
    return box_info.box_bat;
}


static u8 reread = 0;


static int soc_trim_id = 0;

extern void auto_sleep_init();
void soc_check_init(){
    r_printf("soc_check_init reset ok");
    get_first_start_info();
    // auto_sleep_init();
    //  读取各个电量信息
    float current_701_vbat = (float)(adc_get_voltage(AD_CH_VBAT) * 4)/1000.0;
    float current_982_vbat = (float)(adc_get_value_f98())/1000.0;
    u8 charging = (box_info.box_charging /*|| (nocharge_cnt<NO_CHARGE_CNT)*/);

    //  读取VM的电量
    vm_vbat_value = read_vm_vbat_value();
    r_printf("init vm_vbat_value %d", vm_vbat_value);

    //  无效电量，看时机校准
    if(vm_vbat_value == -1) {
        r_printf("init vm_vbat_value invail");
    } else {
        //  初始电量
        disp_soc = (float)vm_vbat_value/100.0; 
        r_printf("init disp_soc:%f", disp_soc);

		r_printf("arry : %d", NEW_NUM_POINTS);
#if LOW_POWER_READREAD
        

        //  非充电状态，比记忆低，重新读取
        if(!charging && (get_cap(current_701_vbat) < disp_soc-0.1)){
            g_printf(">>>>no charge vbat low low :%f, %f", disp_soc, get_cap(current_701_vbat));
            disp_soc = get_cap(current_701_vbat);
        }        
#endif
        //  范围控制
        disp_soc = LV_CLAMP(-1.0, disp_soc, 101.0);
        vm_vbat_value = (int)(disp_soc*100.0);
        if(vm_vbat_value < 1) vm_vbat_value += 1;
        vm_vbat_value = LV_CLAMP(0, vm_vbat_value, 100);
        box_info.box_bat = vm_vbat_value;
        write_vm_vbat_value(box_info.box_bat);
    }

    g_printf(">>>>set_soc_first_work c %d init %d mapsoc:%f 701:%f 982:%f", charging, box_info.box_bat, disp_soc, current_701_vbat, current_982_vbat);

#if SOC_SIMULATE
    if(!soc_trim_id) soc_trim_id = sys_timer_add(NULL, soc_calculate_loop, 10);
#else
    if(!soc_trim_id) soc_trim_id = sys_timer_add(NULL, soc_calculate_loop, (vm_vbat_value == -1)?500:SOC_CICLE_TIME);
#endif

}

static lv_obj_t * soc_remind_obj;
float current_701_vbat;
float current_982_vbat;
float map_soc;
static int last_change_time = 0;
extern void lv_exit_sleep();
static lv_timer_t * dissoctimer;
static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_LONG_PRESSED) {
        //  设置成无效状态
        box_info.box_bat = vm_vbat_value = -1;
        write_vm_vbat_value(box_info.box_bat);  
        sys_timer_modify(soc_trim_id, 100);   
        last_change_time = jiffies_msec(); 
    }

    if(code == LV_EVENT_SHORT_CLICKED) {
        lv_obj_del(soc_remind_obj);
        soc_remind_obj = NULL;
        if(dissoctimer){
            lv_timer_del(dissoctimer);
            dissoctimer = 0;
        }
    }
}



static void soc_remind(){
    printf("%s %d", __func__, __LINE__);
    if(lcd_sleep_status()) {
        return;
    }

    static lv_obj_t * label1 = 0;
    static lv_obj_t * btn1 = 0;

    printf("%s %d", __func__, __LINE__);

    if(!soc_remind_obj) {
        soc_remind_obj = lv_obj_create(lv_layer_sys());
        // lv_obj_remove_style_all(soc_remind_obj);
        lv_obj_set_size(soc_remind_obj, 300, 130);
        lv_obj_center(soc_remind_obj);
        label1 = lv_label_create(soc_remind_obj);
        lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
        lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
        lv_label_set_text(label1, "校准中...\n"
                                    "aaaa\n"  );
        lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
        extern lv_font_t myFont; 
        lv_obj_set_style_text_font(label1, &myFont, 0);

        btn1 = lv_btn_create(soc_remind_obj);
        lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
        lv_obj_align(btn1, LV_ALIGN_RIGHT_MID, 0, 0);
        lv_obj_set_size(btn1, 60,100);
        lv_obj_t * label = lv_label_create(btn1);
        lv_label_set_text(label, "CLOSE");
        lv_obj_center(label);
        // lv_obj_add_flag(btn1, LV_OBJ_FLAG_HIDDEN);

        printf("%s %d", __func__, __LINE__);

    }
printf("%s %d", __func__, __LINE__);
    if(soc_remind_obj){printf("%s %d", __func__, __LINE__);
        lv_label_set_text_fmt(label1,   "#FF0000 701: %d   vbg: %d\n"
                                        "#FF0000 982: %d   A: %d\n"
                                        "soc: %d   map: %d\n"
                                        "%s   pvtime: %d\n"
                                        "#FF0000 %s %d"  ,
                                         (int)(current_701_vbat*1000), adc_get_value(AD_CH_LDOREF),
                                         (int)(current_982_vbat*1000), get_vbat_a_from_f98,
                                        box_info.box_bat, (int)(map_soc*100),
                                        (!box_info.box_charging)?"放电":(CHARGE_PA_END_V>=current_982_vbat)?"恒流充":"恒压充", (CHARGE_PA_END_V<=current_982_vbat)?(int)((float)CHARGE_PV_TIME*(1.0-map_soc)/(1.0-CHARGE_PA_END_SOC)/1000):-1,
                                        (box_info.box_charging&&box_info.box_bat==-1)?"请拔掉充电自动校准":(box_info.box_bat==-1)?"校准中...":(jiffies_msec()-(last_change_time) < CHANGE_FIL_TIME)?"切换等待中":"稳定", (jiffies_msec()-(last_change_time) < CHANGE_FIL_TIME)?(CHANGE_FIL_TIME-(jiffies_msec()-(last_change_time)))/1000:0
                                    );
        if(box_info.box_bat == -1){printf("%s %d", __func__, __LINE__);
            lv_obj_add_flag(btn1, LV_OBJ_FLAG_HIDDEN);
        } else {printf("%s %d", __func__, __LINE__);
            lv_obj_clear_flag(btn1, LV_OBJ_FLAG_HIDDEN);
        }printf("%s %d", __func__, __LINE__);
    }
printf("%s %d", __func__, __LINE__);
    usr_bl_update(100);
    lv_disp_trig_activity(NULL);

printf("%s %d", __func__, __LINE__);

    // if(always_disp){
    //     lv_obj_add_flag(btn1, LV_OBJ_FLAG_HIDDEN);
    // }
}


void soc_disp(){

    extern int now_soc_trim_info;
    if(now_soc_trim_info==200){
        if(!dissoctimer){
            dissoctimer = lv_timer_create(soc_remind, 500, NULL);
        }
    }

}

static void soc_calculate_loop(void *p){
    //  读取各个d电量信息
    current_701_vbat = (float)(adc_get_voltage(AD_CH_VBAT) * 4)/1000.0;
    current_982_vbat = (float)(adc_get_value_f98())/1000.0;
    u8 charging = box_info.box_charging;

    if(current_701_vbat < 2.0){
        r_printf("701 VBAT ERROR");
        return;
    }

    if(charging && current_982_vbat < 2.0){
        r_printf("current_982_vbat VBAT ERROR");
        return;
    }    

    //  严重低电
    if(!charging && (current_701_vbat<POWERSHUTDOWN_V)){//严重低电直接关机
        g_printf("dis charge TOO TOO TOO TOO TOO TOO LOW %f",current_701_vbat);
        g_printf("%s %d",__func__,__LINE__);
        box_info.box_bat = vm_vbat_value = 0;
        write_vm_vbat_value(box_info.box_bat);     
        force_poweroff(NULL);
        return;
    }

    //  记录变化时间点
    static s8 state = -1;
    if(state != charging || last_change_time == 0){
        last_change_time = jiffies_msec();
        state = charging;
    }

#if DISP_TEST_SOC_UI_FIRST
    if(vm_vbat_value == -1){
        static u8 firstsoc_disp = 1;
        if(firstsoc_disp){
            firstsoc_disp = 0;
            send_to_trig_vcb(soc_disp, "ui");
        }
    }
#endif

    //  过滤不靠谱时间
    g_printf("getms %d last %d",jiffies_msec(), last_change_time);
    if(jiffies_msec()-(last_change_time) < CHANGE_FIL_TIME){
        return;
    }

    //  无效电量，需要重新校准
    if(vm_vbat_value == -1){
        //  范围控制
        if(!charging){
            sys_timer_modify(soc_trim_id, SOC_CICLE_TIME);
            disp_soc = get_cap(current_701_vbat);
            disp_soc = LV_CLAMP(-1.0, disp_soc, 101.0);
            vm_vbat_value = (int)(disp_soc*100.0);
            if(vm_vbat_value < 1) vm_vbat_value += 1;
            vm_vbat_value = LV_CLAMP(0, vm_vbat_value, 100);
            box_info.box_bat = vm_vbat_value;
            write_vm_vbat_value(box_info.box_bat);            
        }
        return;
    }

    //  低电关机
    static int low_cnt = 0;
    if(!charging && (current_701_vbat<POWEROFF_V)){
        g_printf("%s %d %f",__func__,__LINE__, current_701_vbat);
        low_cnt++;
    }
    if(charging){
        g_printf("%s %d",__func__,__LINE__);
        low_cnt = 0;
    }
    if(low_cnt>LOWPOWER_CNT){
        g_printf("%s %d",__func__,__LINE__);
        box_info.box_bat = vm_vbat_value = 0;
        write_vm_vbat_value(box_info.box_bat);     
        low_enter_poweroff();
        return;
    }
    
    //  计算电量
    if(charging){
        map_soc = disp_soc;
        u8 ret = get_chr_cap(current_982_vbat, &map_soc);
        if(ret){disp_soc = map_soc;}//恒压冲速度由get_chr_cap接管
    } else {
        map_soc = get_cap(current_701_vbat);
    }

    //  追赶
    if(map_soc > disp_soc && charging){
        if(disp_soc<0.01){
            disp_soc += 0.02;
        }
        disp_soc = disp_soc + CHR_SPEED;
    }
    if(map_soc < disp_soc && !charging){
        disp_soc -= (disp_soc - map_soc)<DIS_SPEED?DIS_SPEED:(disp_soc - map_soc)*DIS_K;
    }

    //  转化整形
    disp_soc = LV_CLAMP(-1.0, disp_soc, 101.0);
    vm_vbat_value = (int)(disp_soc*100.0);
    if(vm_vbat_value < 1) vm_vbat_value += 1;
    vm_vbat_value = LV_CLAMP(0, vm_vbat_value, 100);
    box_info.box_bat = vm_vbat_value;

    //  电量变化保存
    static u8 lastboxbat = -3;
    if(lastboxbat != box_info.box_bat){
        lastboxbat = box_info.box_bat;
        write_vm_vbat_value(lastboxbat);
    }

    
    g_printf(">>>>charge %d soc %f 701:%f map_soc: %f 982:%f a:%d", charging, disp_soc*100.0, current_701_vbat, map_soc, current_982_vbat, get_vbat_a_from_f98);

    
}



//  开机前电压判断
void usr_check_power_on_voltage(void){
    float current_vbat;
    current_vbat = (float)(adc_get_voltage(AD_CH_VBAT) * 4)/1000.0;
    g_printf("usr_check_power_on_voltage current_vbat %f ", current_vbat);
    if(current_vbat <= POWEROFF_V+POWEROFF_V_OFFSET){
        extern void sbox_storage_mode_enter();
        sbox_storage_mode_enter();
    }
}

static void force_poweroff(void *p){
    g_printf("%s %d",__func__,__LINE__);
    box_info.box_bat = 0;
    write_vm_vbat_value(box_info.box_bat);

#if LOW_POW_STORAGE_MODE
    extern void sbox_storage_mode_enter();
    sbox_storage_mode_enter();
#else
    soft_poweroff_mode(1);  ///强制关机
    sys_enter_soft_poweroff(NULL);
#endif
}

static void low_enter_poweroff(){
    g_printf("%s %d",__func__,__LINE__);
    box_info.box_bat = 0;
    write_vm_vbat_value(box_info.box_bat);
    // ui_poweroff_enter();
    sys_timer_add(NULL, force_poweroff, 5000);
}

//  升级代码、上电复位、清
void write_first_start_info(int reset_sour){

    y_printf("write_first_start_info : %d",reset_sour);

    // if(reset_sour == 200){
    //     //  设置成无效状态
    //     // box_info.box_bat = vm_vbat_value = -1;
    //     // write_vm_vbat_value(box_info.box_bat);  
    //     // sys_timer_modify(soc_trim_id, 100);        
    // }

    int ret = 0;
    int retry = 10;
    do{
        ret = syscfg_write(FIRST_START_INFO, &reset_sour, sizeof(reset_sour));
        y_printf("retry:%d", retry);
        os_time_dly(1);
    }while(ret<=0 && retry);
    now_soc_trim_info = reset_sour;
}


#endif




