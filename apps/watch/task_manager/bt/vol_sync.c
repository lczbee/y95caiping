#include "typedef.h"
#include "app_main.h"
#include "app_config.h"
#include "bt/vol_sync.h"
#include "tone_player.h"
#include "key_event_deal.h"
#include "audio_dec_pc.h"
#include "btstack/avctp_user.h"

#if TCFG_APP_BT_EN

u8 vol_sys_tab[17] =  {0, 2, 3, 4, 6, 8, 10, 11, 12, 14, 16, 18, 19, 20, 22, 23, 25};
const u8 vol_sync_tab[17] = {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 127};

extern u8 get_max_sys_vol(void);
extern bool get_esco_busy_flag(void);

void vol_sys_tab_init(void)
{
#if BT_SUPPORT_MUSIC_VOL_SYNC

#if 1
    u8 i = 0;
    u8 max_vol = get_max_sys_vol();
    for (i = 0; i < 17; i++) {
        vol_sys_tab[i] = i * max_vol / 16;
    }
#else
    u8 i = 0;
    u8 max_vol = get_max_sys_vol();
    vol_sys_tab[0] = 0;

    //最大音量<16，补最大值
    if (max_vol <= 16) {
        for (i = 1; i <= max_vol; i++) {
            vol_sys_tab[i] = i;
        }
        for (; i < 17; i++) {
            vol_sys_tab[i] = max_vol;
        }
    } else {
        u8 j = max_vol - 16;
        u8 k = 1;
        for (i = 1; i <= max_vol; i++) {
            /* g_printf("i=%d j=%d  k=%d",i,j,k); */
            if (i % 2) {
            } else {
                //忽略多余的级数
                if (j > 0) {
                    j--;
                    continue;
                }
            }

            if (k < 17) {
                vol_sys_tab[k] = i;
            }
            k++;
        }

        vol_sys_tab[16] = max_vol;
    }

#endif
#if 1
    for (i = 0; i < 17; i++) {
        g_printf("[%d]:%d ", i, vol_sys_tab[i]);
    }
#endif
#endif //BT_SUPPORT_MUSIC_VOL_SYNC
}

//注册给库的回调函数，用户手机设置设备音量
void set_music_device_volume(int volume)
{
#if BT_SUPPORT_MUSIC_VOL_SYNC
    s16 music_volume;

#if (TCFG_DEC2TWS_ENABLE)
    extern u8 get_a2dp_start_flag();
    extern u8 is_tws_all_in_bt();
    if (!is_tws_all_in_bt() && !get_a2dp_start_flag()) { //get_a2dp_start_flag为了防止后台模式时手机播放音乐回到蓝牙模式后音量同步被过滤掉
        return;
    }
#endif

    //音量同步最大是127，请计数比例
    if (volume > 127) {
        /*log_info("vol %d invalid\n",  volume);*/
#if TCFG_VOL_RESET_WHEN_NO_SUPPORT_VOL_SYNC
        music_volume = get_max_sys_vol();
        log_i("unsupport vol_sync,reset vol:%d\n", music_volume);
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, music_volume, 1);
#endif
        return;
    }
    if (tone_get_status() || get_esco_busy_flag()) {
        log_i("It's not smart to sync a2dp vol now\n");
        app_var.music_volume = vol_sys_tab[(volume + 1) / 8];
        return;
    }
    /* s16 music_volume = (volume * get_max_sys_vol() / 127); */

    music_volume = vol_sys_tab[(volume + 1) / 8];
    app_var.opid_play_vol_sync = vol_sync_tab[(volume + 1) / 8];

    app_audio_set_volume(APP_AUDIO_STATE_MUSIC, music_volume, 1);

#endif
}

//注册给库的回调函数，用于手机获取当前设备音量
int phone_get_device_vol(void)
{
    //音量同步最大是127，请计数比例
#if 0
    return (app_var.sys_vol_l * get_max_sys_vol() / 127) ;
#else
    return app_var.opid_play_vol_sync;
#endif
}


void opid_play_vol_sync_fun(u8 *vol, u8 mode)
{
#if BT_SUPPORT_MUSIC_VOL_SYNC
    u8 i = 0;
    vol_sys_tab[16] =  get_max_sys_vol();

    if (*vol == 0) {
        if (mode) {
            *vol = vol_sys_tab[1];
            app_var.opid_play_vol_sync = vol_sync_tab[1];
        } else {
            *vol = vol_sys_tab[0];
            app_var.opid_play_vol_sync = vol_sync_tab[0];
        }
    } else if (*vol >= get_max_sys_vol()) {
        if (mode) {
            *vol = vol_sys_tab[16];
            app_var.opid_play_vol_sync = vol_sync_tab[16];
        } else {
            *vol = vol_sys_tab[15];
            app_var.opid_play_vol_sync = vol_sync_tab[15];
        }
    } else {
        for (i = 0; i < sizeof(vol_sys_tab); i++) {
            if (*vol == vol_sys_tab[i]) {
                if (mode) {
                    app_var.opid_play_vol_sync = vol_sync_tab[i + 1];
                    *vol = vol_sys_tab[i + 1];
                } else {
                    app_var.opid_play_vol_sync = vol_sync_tab[i - 1];
                    *vol = vol_sys_tab[i - 1];
                }
                break;
            } else if (*vol < vol_sys_tab[i]) {
                if (mode) {
                    *vol = vol_sys_tab[i + 1];
                    app_var.opid_play_vol_sync = vol_sync_tab[i];
                } else {
                    *vol = vol_sys_tab[i - 1];
                    app_var.opid_play_vol_sync = vol_sync_tab[i - 1];
                }
                break;
            }
        }
    }
#endif
}

#if PC_AUDIO_EMITTER

//emeet音量控制
u8 now_vol_level = 20;
u8 con_vol_level = 0;
unsigned short emeet_vol[11][3] = {
    { 0,   0,   0}, //
    { 10,  3,  15}, // 
    { 20,  5,  23}, // 
    { 30,  9,  39}, // 
    { 40, 11,  47}, // 
    { 50, 15,  63}, // 
    { 60, 17,  71}, // 
    { 70, 21,  87}, // 
    { 80, 23,  95}, // 
    { 90, 27,  111}, // 
    {100, 31,  127}, // 
};

int control_pc_vol_time = 0x5A;
int get_control_pc_vol_time()
{
    return control_pc_vol_time;
}
void add_control_pc_vol_time(int vol)
{
    control_pc_vol_time += vol;
}

void set_control_pc_vol_time(int vol)
{
    control_pc_vol_time = vol;
}

int ignore_pc_cmd_status = 0;
void ignore_pc_cmd()
{
    ignore_pc_cmd_status = 0;
}

void emeet_control_from_receive(u8 vol)
{
    u16 l_volume, r_volume;
    u8 i = 0;
    uac_get_cur_vol(0, &l_volume, &r_volume);
    printf("emeet_control_from_receive == %d\n",vol);
    for(i = 10;i>=0;i--){
        if(l_volume >= emeet_vol[i][0]){
            now_vol_level = i;
            break;
        }
    }
    for(i = 10;i>=0;i--){
        if(vol >= emeet_vol[i][2]){
            con_vol_level = i;
            break;
        }
    }
    if(vol > 0 && con_vol_level == 0){         //0音量特殊处理，避免出现+不上去问题
        con_vol_level = 1;
    }
    printf("now_vol_level == %d con_vol_level == %d\n",now_vol_level,con_vol_level);
    if(now_vol_level == con_vol_level){
        printf("donot need control vol\n");
    }
    else{
        control_pc_vol_time = 0;
        int d_value = 0;
        if((emeet_vol[con_vol_level][0] - l_volume) > 0){
            d_value = ((emeet_vol[con_vol_level][0] - l_volume))/2;
            if(l_volume != emeet_vol[con_vol_level][0] && emeet_vol[con_vol_level][0] == 100){ //防止出现+不到100的情况
                d_value += 1;
            }
        }
        else{
            d_value = ((emeet_vol[con_vol_level][0] - l_volume)-1)/2;
            if(l_volume != emeet_vol[con_vol_level][0] && emeet_vol[con_vol_level][0] == 0){ //防止出现-不到0的情况
                d_value -= 1;
            }
        }
        int i = 0;
        if(d_value > 0){
            for(i = 0;i < d_value;i++){
                putchar('u');
                control_pc_vol_time++;
            }
        }
        if(d_value < 0){
            for(i = 0;i > d_value;i--){
                putchar('d');
                 control_pc_vol_time--;
            }
        }
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, emeet_vol[con_vol_level][1], 1);
        now_vol_level = con_vol_level;
        if(ignore_pc_cmd_status != 0){
            sys_timeout_del(ignore_pc_cmd_status);
            ignore_pc_cmd_status = 0;
        }
        ignore_pc_cmd_status = sys_timeout_add(NULL,ignore_pc_cmd,500);
        app_task_put_key_msg(KEY_PC_VOL_CON,0);
    }
    
}


void emeet_control_from_pc(u8 vol)
{
    printf("emeet_control_from_pc == %d\n",vol);
    u8 i = 0;
    for(i = 10;i>=0;i--){
        if(vol >= emeet_vol[i][0]){
            con_vol_level = i;
            break;
        }
    }  
    if(con_vol_level != now_vol_level && ignore_pc_cmd_status == 0){
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, emeet_vol[con_vol_level][1], 1);
        if(MIC_OPEN_FLAG == 0){
            app_var.opid_play_vol_sync = emeet_vol[con_vol_level][2];
            printf("audio_vol_set == %d\n",app_var.opid_play_vol_sync);
            user_emitter_cmd_prepare(USER_CTRL_AVCTP_OPID_SEND_VOL, 0, NULL);
            now_vol_level = con_vol_level;
        }
    }  
}


#endif  /* PC_AUDIO_EMITTER */

#endif
