#include "dma/dma_wrapper.h"
#include "dma_ota_wrapper.h"
#include "system/includes.h"
#include "os/os_api.h"
#include "dma_setting.h"
#include "btstack/app_protocol_event.h"
#include "btstack/avctp_user.h"
#include "system/timer.h"


#ifdef DMA_LIB_CODE_SIZE_CHECK
#pragma bss_seg(	".bt_dma_port_bss")
#pragma data_seg(	".bt_dma_port_data")
#pragma const_seg(	".bt_dma_port_const")
#pragma code_seg(	".bt_dma_port_code")
#endif

#define    IAP_CH       0x1000
#define __this_cfg  (&dueros_global_cfg)
DUER_DMA_OPER g_dma_operation;
DMA_OTA_OPER  g_dma_ota_operation;

//#define DMA_HEAP_POOL_SIZE (4096)
//char dma_heap_pool[DMA_HEAP_POOL_SIZE];

__attribute__((weak)) u8 dma_use_lib_only_ble = 0;

u8 dma_role_switch_ble_disconnect_flag = 0;
#define DMA_QUEUE_BUFFER_SIZE (4096)
//uint8_t dma_queue_buffer_pool[DMA_QUEUE_BUFFER_SIZE];
uint8_t *dma_queue_buffer_pool = NULL;
/* osMutexId dma_mutex[DMA_MUTEX_NUM]; */

/* osSemaphoreId dma_sem_id = NULL; */
OS_MUTEX dma_mutex[DMA_MUTEX_NUM];
OS_SEM dma_sem_id;
int platform_system_init(void)
{
    dma_log("%s\n", __func__);

    // ��ʼ�� dma_mutex[DMA_CMD_INPUT_MUTEX_ID];
    // ��ʼ�� dma_mutex[DMA_CMD_OUTPUT_MUTEX_ID];
    // ��ʼ�� dma_mutex[DMA_DATA_MUTEX_ID];
    // ��ʼ�� dma_mutex[DMA_SYNC_DATA_MUTEX_ID];

    // ��ʼ�� dma_heap_pool��Ӧ��heap
    // ��ʼ�� dma_sem_id
    dma_queue_buffer_pool = malloc(DMA_QUEUE_BUFFER_SIZE);
    if (dma_queue_buffer_pool == NULL) {
        dma_log("=====why dma queue not enought buf\n");
        return -1;
    }
    os_sem_create(&dma_sem_id, 0);
    for (int i = 0; i < DMA_MUTEX_NUM; i++) {
        os_mutex_create(&dma_mutex[i]);
    }
    return 0;
}
__attribute__((weak)) u8 speak_type = 0;
__attribute__((weak)) u8 use_triad_info = 0;


__attribute__((weak))
void get_user_device_capability(DUER_DMA_CAPABILITY *device_capability)
{

}
bool platform_get_device_capability(DUER_DMA_CAPABILITY *device_capability)
{
    if (NULL == device_capability) {
        return false;
    }
    dma_log("%s\n", __func__);

    dma_role_switch_ble_disconnect_flag = 0x0;
    // ���ݲ�Ʒ�������
    if (speak_type) {
        device_capability->device_type  = "SPEAKER";
        device_capability->is_earphone = false;
        device_capability->support_box_battery = false;
    } else {
        device_capability->device_type  = "HEADPHONE";
        device_capability->is_earphone = true;
        device_capability->support_box_battery = false;
    }
    set_dueros_pair_state(0, 0);
    device_capability->manufacturer = "JL";
    device_capability->support_spp  = true;
    device_capability->support_ble  = true;
    device_capability->support_a2dp = true;
    device_capability->support_at_command = true;
    device_capability->support_media = true;
    device_capability->support_sota = false;
    device_capability->support_dual_record = false;
    device_capability->support_local_voice_wake = false;
    device_capability->support_model_beamforming_asr = false;
    device_capability->support_log = false;
    device_capability->ble_role_switch_by_mobile = true;
    device_capability->support_tap_wakeup = true;
    device_capability->support_sign_method = DMA_SIGN_METHOD__SHA256;
    // device_capability->support_local_wakeup_prompt_tone = true;
    // device_capability->support_battery = true;

    get_user_device_capability(device_capability);
    return true;
}

extern u32 dma_software_version;
bool platform_get_firmeware_version(uint8_t *fw_rev_0, uint8_t *fw_rev_1, uint8_t *fw_rev_2, uint8_t *fw_rev_3)
{
    dma_log("%s-%d\n", __func__, dma_software_version);
    *fw_rev_3 = dma_software_version         & 0x000000ff;
    *fw_rev_2 = (dma_software_version >> 8)  & 0x000000ff;
    *fw_rev_1 = (dma_software_version >> 16) & 0x000000ff;
    *fw_rev_0 = (dma_software_version >> 24) & 0x000000ff;
    return true;
}

void platform_heap_free(void *ptr)
{
    dma_log("platform_heap_free\n");
    free(ptr);
}

void *platform_heap_malloc(size_t size)
{
    dma_log("platform_heap_malloc size:%d\n",size);
    return malloc(size);
}

bool platform_sem_wait(uint32_t timeout_ms)
{
    dma_log("%s timeout_ms:%x\n", __func__, timeout_ms);
    if (timeout_ms == 0xFFFFFFFF){
        os_sem_pend(&dma_sem_id, 0);
    }else{
        os_sem_pend(&dma_sem_id, timeout_ms);
    }
    return true;
}

bool platform_sem_signal()
{
    dma_log("%s\n", __func__);
    os_sem_post(&dma_sem_id);
    return true;
}

bool platform_mutex_lock(DMA_MUTEX_ID mutex_id)
{
    // dma_log("%s\n", __func__);
    os_mutex_pend(&dma_mutex[mutex_id], 0);
    return true;
}

bool platform_mutex_unlock(DMA_MUTEX_ID mutex_id)
{
    // dma_log("%s\n", __func__);
    os_mutex_post(&dma_mutex[mutex_id]);
    return true;
}

bool platform_get_userdata_config(DMA_USER_DATA_CONFIG *dma_userdata_config)
{
//* @brief DMAЭ��ջʹ�õ�������Ϣ��������Flash
    dma_log("%s\n", __func__);
#if DMA_LIB_DEBUG
    if (dma_userdata_config == NULL) {
        dma_log("%s no buffer\n", __func__);
        return false;
    }
#endif
    dma_message(APP_PROTOCOL_DMA_READ_RAND, dma_userdata_config, DMA_USER_DATA_CONFIG_LEN);
    //dma_dump(dma_userdata_config, DMA_USER_DATA_CONFIG_LEN);
    return true;
}
u16 last_pack_crc = 0;
extern u16 CRC16(const void *ptr, u32 len);
bool platform_set_userdata_config(const DMA_USER_DATA_CONFIG *dma_userdata_config)
{
    u16 current_crc = 0;
    dma_log("%s\n", __func__);
#if DMA_LIB_DEBUG
    if (dma_userdata_config == NULL) {
        dma_log("%s no buffer\n", __func__);
        return false;
    }
#endif
    //dma_dump(dma_userdata_config, DMA_USER_DATA_CONFIG_LEN);
    current_crc = CRC16(dma_userdata_config, DMA_USER_DATA_CONFIG_LEN);
    dma_log("====dma vm data crc %x---%x\n", last_pack_crc, current_crc);
    if (last_pack_crc != current_crc) {
        last_pack_crc = current_crc;
        dma_message(APP_PROTOCOL_DMA_SAVE_RAND, dma_userdata_config, DMA_USER_DATA_CONFIG_LEN);
    }
    return true;
}

void get_random_number(uint8_t *ptr, uint8_t len);
uint32_t platform_rand(void)
{
    dma_log("%s\n", __func__);
    uint8_t temp_buf[4];
    get_random_number(temp_buf, 4);
    return ((temp_buf[0]) | (temp_buf[1] << 8) | (temp_buf[1] << 16) | (temp_buf[1] << 24));
}
u8 wait_master_ota_init = 0;
u8 dma_enter_ota_flag = 0;
bool platform_get_ota_state(void)
{
    dma_log("%s\n", __func__);
    return dma_enter_ota_flag;
}
extern u8 dma_ota_result;
uint8_t platform_get_upgrade_state(void)
{
    dma_log("%s\n", __func__);
    return /*dma_ota_result*/1;
}

extern u8 *get_cur_connect_phone_mac_addr(void);
int32_t platform_get_mobile_connect_type(void)
{
    
    int dev_type;
    u8 *tmp_addr = get_cur_connect_phone_mac_addr();
    if (tmp_addr) {
        dev_type = remote_dev_company_ioctrl(tmp_addr, 0, 0);
    } else {
        return 0;
    }
    if (REMOTE_DEV_IOS == dev_type) {
        dma_log("%s REMOTE_DEV_IOS\n", __func__);
        return 1;
    }
    dma_log("%s REMOTE_DEV_ANDROID\n", __func__);
    return 2;
}

#define ADV_RSP_PACKET_MAX  31
extern u8 adv_data[ADV_RSP_PACKET_MAX];//max is 31
extern u8 adv_data_length;
// scan_rsp ����
extern u8 scan_rsp_data[ADV_RSP_PACKET_MAX];//max is 31
extern u8 scan_rsp_data_len;

extern u8 dma_ibeacon_data[ADV_RSP_PACKET_MAX];//max is 31
extern u8 dma_ibeacon_data_len ;
extern void dma_ble_ibeacon_adv(u8 sw);
bool platform_set_ble_advertise_data(const char *t_adv_data, uint8_t adv_data_len,
                                     const char *scan_response, uint8_t scan_response_len,
                                     const char *ibeacon_adv_data, uint8_t ibeacon_adv_data_len)
{
    dma_log("%s\n", __func__);
    if (adv_data_len != 0) {
        puts("----------------------------------------------------------------adv_data [from baidu]:");
        put_buf(t_adv_data, adv_data_len);
        if (adv_data_len < ADV_RSP_PACKET_MAX) {
            memcpy(adv_data, t_adv_data, adv_data_len);
            if (dma_use_lib_only_ble) {
                adv_data[2] = 0x06;
            }
            adv_data_length = adv_data_len;
        }
    }
    if (scan_response_len != 0) {
        puts("----------------------------------------------------------------scan_response [from baidu]:");
        put_buf(scan_response, scan_response_len);
        memcpy(scan_rsp_data, scan_response, scan_response_len);
        scan_rsp_data_len = scan_response_len;
    }
    if (ibeacon_adv_data_len != 0) {
        puts("----------------------------------------------------------------ibeacon_adv_data [from baidu]:");
        dma_dump(ibeacon_adv_data, ibeacon_adv_data_len);
        memcpy(dma_ibeacon_data, ibeacon_adv_data, ibeacon_adv_data_len);
        dma_ibeacon_data_len = ibeacon_adv_data_len;
        dma_ble_ibeacon_adv(1);
    } else {
        dma_ibeacon_data_len = 0;
    }
    //later
    return true;
}

extern void dma_ble_adv_enable(u8 enable);
bool platform_set_ble_advertise_enable(bool on)
{
    dma_log("%s enable:%d tws_is_master:%d\n", __func__, on, dma_check_tws_is_master());
    if (dma_check_tws_is_master() == 0 || get_esco_coder_busy_flag()
        || (dma_role_switch_ble_disconnect_flag != 0)) {
        dma_ble_adv_enable(0);
        dma_log("not allow dma lib open adv\n");
        return true;
    }
    dma_ble_adv_enable(on);
    return true;
}
 
extern const u8 *bt_get_mac_addr();
bool platform_get_bt_address(DMA_BT_ADDR_TYPE addr_type, uint8_t *bt_address)
{
#if 1
    dma_log("%s  addr_type:%d\n", __func__, addr_type);
    u8 temp_addr[6];
    if (NULL == bt_address) {
        return false;
    }
    swapX(bt_get_mac_addr(), temp_addr, 6);
    memcpy(bt_address, temp_addr, 6);
    put_buf(temp_addr,6);
    put_buf(bt_address,6);
#else
    u8 *temp_addr;
    dma_log("%s  addr_type:%d\n", __func__, addr_type);
    temp_addr = bt_get_mac_addr();
    memcpy(bt_address, temp_addr, 6);
    put_buf(temp_addr,6);
    put_buf(bt_address,6);
#endif

    return true;
}

extern const char *bt_get_local_name(void);

bool platform_get_bt_local_name(char *bt_local_name)
{
    u8 *device_name = NULL;
    int device_name_len = 0;
    if (NULL == bt_local_name) {
        return false;
    }
    device_name = bt_get_local_name();
    device_name_len = strlen(device_name);
    memcpy(bt_local_name, device_name, device_name_len);
    dma_log("%s %s\n", __func__, bt_local_name);
    return true;
}

bool platform_get_ble_local_name(char *ble_local_name)
{
    dma_log("%s\n", __func__);
    if (NULL == ble_local_name) {
        return false;
    }
    return platform_get_bt_local_name(ble_local_name);
}

bool platform_get_mobile_bt_address(uint8_t *bt_address)
{
    dma_log("%s\n", __func__);
    if (NULL == bt_address) {
        dma_log("%s no buf\n", __func__);
        return false;
    }
    if (get_cur_connect_phone_mac_addr()) {
        u8 temp_addr[6];

        //swapX(get_cur_connect_phone_mac_addr(), temp_addr, 6);
        //memcpy(bt_address, temp_addr, 6);
        memcpy(bt_address, get_cur_connect_phone_mac_addr(), 6);
        dma_dump(bt_address, 6);
        return true;
    } else {
        dma_log("%s no connect address\n", __func__);
        return false;
    }
}

extern int get_link_key(u8 *bd_addr, u8 *link_key, u8 id);
bool platform_get_linkkey_exist_state(const uint8_t *bt_address)
{
    dma_log("%s\n", __func__);
    u8 link_key[16] = {0};
    dma_dump(bt_address, 6);
    if (get_link_key(bt_address, &link_key,  0)) {
        dma_log("dma have link key\n");
        return true;
    } else {
        dma_log("dma no link key\n");
        return false;
    }
}
extern u32 dma_serial_number_int;
extern char dma_serial_number[];
__attribute__((weak))
int get_vender_special_SN(char *addr)
{
    return 0;
}
bool platform_get_serial_number(DMA_SN_TYPE sn_type, uint8_t *serial_number)
{
    dma_log("%s\n", __func__);
    //1723846
    //Ҫ����Ҫ��Ҫ����ָ��
    u8 temp_addr[6];
    u8 value_1 = 0, value_2 = 0;
    u8 serial_number_int[33];
    int SN_len = 0;
    SN_len = get_vender_special_SN(serial_number_int);
    if (SN_len > 0) {
        memcpy(serial_number, serial_number_int, SN_len);
        dma_log("%s++++%d==%s-%s\n", __func__, sn_type, serial_number, serial_number_int);
        return true;
    }
    memcpy(serial_number_int, 0, 33);
    dma_log("dma_serial_number_int %d\n", dma_serial_number_int);
    sprintf(serial_number_int, "%d", dma_serial_number_int);
    dma_log("%s---%d==%s-%s\n", __func__, sn_type, dma_serial_number, serial_number_int);
    memcpy(serial_number, serial_number_int, strlen(serial_number_int));
    return true;
}

bool platform_get_sco_state(void)
{
    dma_log("%s\n", __func__);
    return get_esco_coder_busy_flag();
}

bool platform_get_reconnect_state(void)
{
    dma_log("%s\n", __func__);
    bool flag = 0;
    flag = (bool)get_auto_connect_state(get_cur_connect_phone_mac_addr());
    return flag;
}

bool platform_set_voice_mic_stream_state(DMA_VOICE_STREAM_CTRL_TYPE cmd, DMA_VOICE_STREAM_CODEC_TYPE codec_type)
{
    dma_log("%s cmd:%d codec_type:%d\n", __func__, cmd, codec_type);
    if (DMA_VOICE_STREAM_START == cmd) {
        dma_message(APP_PROTOCOL_SPEECH_START, NULL, 0);
    } else {
        dma_message(APP_PROTOCOL_SPEECH_STOP, NULL, 0);
    }
    return true;
}

extern u8 dma_stream_upload_enable;
bool platform_set_stream_upload_enable(bool on)
{
    dma_log("%s on:\n", __func__, on);
    dma_stream_upload_enable = on;
    return true;
}

bool platform_get_stream_upload_state(void)
{
    dma_log("%s\n", __func__);
    return dma_stream_upload_enable;
}

extern u16 global_local_ble_mtu;
bool platform_get_mobile_mtu(uint32_t *mtu)
{
    if (mtu == NULL) {
        return false;
    }
    if (get_curr_channel_state() & SPP_CH) {
        *mtu = 500;
    } else {
        *mtu = global_local_ble_mtu;
    }
    dma_log("%s mtu:%d\n", __func__, *mtu);
    return true;
}

bool platform_get_peer_mtu(uint32_t *mtu)
{
    if (mtu == NULL) {
        return false;
    }
    *mtu = 320;
    dma_log("%s mtu:%d", __func__, *mtu);
    return true;
}

bool platform_set_wakeup_enable(bool on)
{
    dma_log("%s on:%d", __func__, on);
    return true;
}

bool platform_get_check_summary(const void *input_data, uint32_t len, uint8_t *output_string)
{
    dma_log("%s\n", __func__);
    sha256Compute(input_data, len, (u8 *)output_string);
    set_dueros_pair_state(1, 0);
    return true;
}

bool platform_get_prepare_state(void)
{
    // ��ȡ��ǰ�Ƿ��ڿɷ���DMA����״̬
    dma_log("%s check_can_send_data_or_not:%d\n", __func__, check_can_send_data_or_not());
    return check_can_send_data_or_not();
}


extern int hfp_send_user_at_cmd(bd_addr_t addr, u8 *data, u8 len);
bool platform_process_cmd(DMA_OPERATION_CMD cmd, void *param_buf, uint32_t  param_size)
{
    dma_log("platform_process_cmd======%d-%d\n", cmd, param_size);
    switch (cmd) {
    case DMA_OPERATION_NO_CMD:
        break;
    case DMA_AUDIO_GET_PLAY_PAUSE:
        if (param_buf == NULL) {
            break;
        }
        if (1 == a2dp_get_status()) {
            *(u8 *)param_buf = true;
        } else {
            *(u8 *)param_buf = false;
        }
        break;
    case DMA_AUDIO_PLAY:
        user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
        break;
    case DMA_AUDIO_PAUSE:
        user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_PAUSE, 0, NULL);
        break;
    case DMA_AUDIO_PLAY_BACKWARD:
        user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_PREV, 0, NULL);
        break;
    case DMA_AUDIO_PLAY_FORWARD:
        user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_NEXT, 0, NULL);
        break;
    case DMA_SEND_CMD:
        dueros_sent_raw_cmd(param_buf, param_size);
        break;
    case DMA_SEND_DATA:
        dueros_sent_raw_audio_data(param_buf, param_size);
        break;
    case DMA_SEND_ATCMD:
        //put_buf(param_buf, param_size);
       // hfp_send_user_at_cmd(get_cur_connect_phone_mac_addr(), param_buf, param_size);
        break;
    case DMA_SEND_VOICE_COMMAND:
        user_send_cmd_prepare(USER_CTRL_HFP_GET_SIRI_OPEN, 0, NULL);
        break;
    case DMA_DISCONNECT_MOBILE:
        break;
    case DMA_CONNECT_MOBILE:
        break;
    default:
        break;
    }
    return true;
}

__attribute__((weak))
bool platform_get_peer_connect_state(void)
{
    dma_log("%s\n", __func__);
    return true;
}

__attribute__((weak))
bool platform_send_custom_info_to_peer(uint8_t *param_buf, uint16_t param_size)
{
    dma_log("%s\n", __func__);
    return true;
}

bool platform_get_tws_role(DMA_TWS_ROLE_TYPE *role_type)
{
    if (NULL == role_type) {
        return false;
    }
    if (dma_check_tws_is_master()) {
        *role_type = DMA_TWS_MASTER;
    } else {
        *role_type = DMA_TWS_SLAVE;
    }
    dma_log("%s role_type:%d dma_check_tws_is_master:%d\n", __func__, *role_type, dma_check_tws_is_master());
    return true;
}
extern u8 dma_tws_side_info;
__attribute__((weak))
bool platform_get_tws_side(DMA_TWS_SIDE_TYPE *side_type)
{
    *side_type = dma_tws_side_info;
    dma_log("%s side_type:%d\n", __func__, *side_type);
    return true;
}

bool platform_set_role_switch_enable(bool on)
{
    dma_log("%s on:\n", __func__, on);
    return true;
}

bool platform_get_box_state(DMA_BOX_STATE_TYPE *box_state)
{
    *box_state = DMA_BOX_STATE_OPEN;
    dma_log("%s box_state:%d\n", __func__, *box_state);
    return true;
}

bool platform_get_wearing_state(void)
{
    dma_log("%s\n", __func__);
    return true;
}

static bool (*dma_get_battery_value)(u8 battery_type, u8 *value) = NULL;
void dma_get_battery_callback_register(bool (*handler)(u8 battery_type, u8 *value))
{
    dma_get_battery_value = handler;
}
u8 dma_get_bat_type_value(u8 type)
{
    u8 battery_value[APP_PROTOCOL_BAT_T_MAX] = {0};
    if (dma_get_battery_value) {
        dma_get_battery_value(BIT(type), battery_value);
    }
    dma_log("%s dma battery:%d battery_value:%d\n", __func__, type, battery_value[type]);
    return battery_value[type];
}
uint8_t platform_get_battery_level(void)
{
    dma_log("%s\n", __func__);
    int flag = 0;;
    int tws_side = 0;
    platform_get_tws_side(&tws_side);
    if (tws_side == DMA_SIDE_LEFT) {
        flag = APP_PROTOCOL_BAT_T_TWS_LEFT;
    } else {
        flag = APP_PROTOCOL_BAT_T_TWS_RIGHT;
    }
    return dma_get_bat_type_value(flag);
}

uint8_t platform_get_box_battery_level(void)
{
    dma_log("%s\n", __func__);
    return dma_get_bat_type_value(APP_PROTOCOL_BAT_T_BOX);
}
bool platform_get_triad_info(char *triad_id, char *triad_secret)
{
    if (!use_triad_info) {
        return false;
    }
    u8 copy_len = 0;
    copy_len = strlen(__this_cfg->dma_cfg_file_triad_id);
    memcpy(triad_id, (uint8_t *)__this_cfg->dma_cfg_file_triad_id, copy_len);
    copy_len = strlen(__this_cfg->dma_cfg_file_secret);
    memcpy(triad_secret, (uint8_t *)__this_cfg->dma_cfg_file_secret, copy_len);
    return true;
}

bool platform_play_local_tts(DMA_TTS_ID tts_id, bool both_side)
{
    u8 temp_tts_id = (u8)tts_id;
    dma_log("%s---tts_id:%d--both-side-%d\n", __func__, temp_tts_id, both_side);

    dma_message(APP_PROTOCOL_DMA_TTS_TYPE, &temp_tts_id, 1);

    return true;
}

bool platform_dma_configure(void)
{
    if (platform_system_init() < 0) {
        return false;
    }
    g_printf("------%s>>>>>>>>>>>>>\n",__func__);
    g_dma_operation.get_device_capability = platform_get_device_capability;
    g_dma_operation.get_firmeware_version = platform_get_firmeware_version;
    g_dma_operation.dma_heap_malloc = platform_heap_malloc;
    g_dma_operation.dma_heap_free   = platform_heap_free;
    g_dma_operation.dma_sem_wait   = platform_sem_wait;
    g_dma_operation.dma_sem_signal = platform_sem_signal;
    g_dma_operation.dma_mutex_lock = platform_mutex_lock;
    g_dma_operation.dma_mutex_unlock = platform_mutex_unlock;
    g_dma_operation.dma_get_userdata_config = platform_get_userdata_config;
    g_dma_operation.dma_set_userdata_config = platform_set_userdata_config;
    g_dma_operation.dma_rand = platform_rand;
    g_dma_operation.get_ota_state = platform_get_ota_state;
    g_dma_operation.get_upgrade_state = platform_get_upgrade_state;
    g_dma_operation.get_mobile_bt_address = platform_get_mobile_bt_address;
    g_dma_operation.get_mobile_connect_type = platform_get_mobile_connect_type;
    g_dma_operation.set_ble_advertise_data = platform_set_ble_advertise_data;
    g_dma_operation.set_ble_advertise_enable = platform_set_ble_advertise_enable;
    g_dma_operation.get_bt_address = platform_get_bt_address;
    g_dma_operation.get_bt_local_name = platform_get_bt_local_name;
    g_dma_operation.get_ble_local_name = platform_get_ble_local_name;
    g_dma_operation.get_linkkey_exist_state = platform_get_linkkey_exist_state;
    g_dma_operation.get_serial_number = platform_get_serial_number;
    g_dma_operation.get_sco_state = platform_get_sco_state;
    g_dma_operation.get_reconnect_state = platform_get_reconnect_state;
    g_dma_operation.set_voice_mic_stream_state = platform_set_voice_mic_stream_state;
    g_dma_operation.set_stream_upload_enable = platform_set_stream_upload_enable;
    g_dma_operation.get_stream_upload_state = platform_get_stream_upload_state;
    g_dma_operation.get_mobile_mtu = platform_get_mobile_mtu;
    g_dma_operation.get_peer_mtu = platform_get_peer_mtu;
    g_dma_operation.set_wakeup_enable = platform_set_wakeup_enable;
    g_dma_operation.get_check_summary = platform_get_check_summary;
    g_dma_operation.get_prepare_state = platform_get_prepare_state;
    g_dma_operation.dma_process_cmd = platform_process_cmd;
    g_dma_operation.get_peer_connect_state = platform_get_peer_connect_state;
    g_dma_operation.send_custom_info_to_peer = platform_send_custom_info_to_peer;
    g_dma_operation.get_tws_role = platform_get_tws_role;
    g_dma_operation.get_tws_side = platform_get_tws_side;
    g_dma_operation.set_role_switch_enable = platform_set_role_switch_enable;
    g_dma_operation.get_box_state = platform_get_box_state;
    g_dma_operation.get_wearing_state = platform_get_wearing_state;
    g_dma_operation.get_battery_level = platform_get_battery_level;
    g_dma_operation.get_box_battery_level = platform_get_box_battery_level;
    g_dma_operation.get_triad_info = platform_get_triad_info;
    g_dma_operation.play_local_tts = platform_play_local_tts;

    return true;
}
#if DMA_LIB_OTA_EN
/**
 * @brief DMA OTA ms����֮����ûص�����
 *
 * @param[in] cb      �ص�����
 * @param[in] data    ���ûص�����ʱ�����ص������Ĳ���
 * @param[in] ms      ���ٺ������ô˺���
 *
 * @return ����˵��
 *        -true ����timer�ɹ�
 *        -false ����timerʧ��
 * @note ms����֮�����cb�ص�������������data
 */
bool platform_ota_callback_by_timeout(dma_ota_timeout_cb cb, void *data, uint32_t ms)
{
    dma_log("%s---%x---%d\n", __func__, data, ms);
    int ota_timer = sys_timeout_add(data, cb, ms);
    return true;
}
/**
* @brief �������ݸ��ֻ�
* @param[in] size    �������ݵĴ�С
* @param[in] data    ���͵�����
* @note OTA SDK���ֻ�֮�䴫�����ݣ�ֻ������������ \n
*/
extern int dueros_ota_sent_raw_cmd(uint8_t *data,  uint32_t len);
void platform_ota_send_data_to_mobile(uint16_t size, uint8_t *data)
{
    //dma_log("%s\n", __func__);
    //dma_dump(data, size);
    dueros_ota_sent_raw_cmd(data, size);

}

/**
* @brief �洢OTA��ص����ݵ�flash������ͬ��д��
* @param[in] size    д�����ݵĴ�С
* @param[in] data    д�������
* @note OTA�����д洢OTA��ص�����
*/
void platform_ota_save_ota_info(uint16_t size, const uint8_t *data)
{
    dma_log("%s\n", __func__);
    if (dma_check_tws_is_master()) {
        dma_message(APP_PROTOCOL_DMA_SAVE_OTA_INFO, data, size);
    }
}
/**
* @brief ��flash��ȡOTA SDK�洢������
* @param[in] size    Ҫ��ȡ���ݵĴ�С������д�����ݵĴ�С
* @param[in] buffer  ������ݵ�buffer
* @note ��ȡOTA�����д洢��OTA�������
*/
void platform_ota_read_ota_info(uint16_t size, uint8_t *buffer)
{
    dma_log("%s\n", __func__);
    dma_message(APP_PROTOCOL_DMA_READ_OTA_INFO, buffer, size);
}

/**
* @brief ��ȡ����Image���ݵĵ�buffer
* @param[out] buffer      buffer�ĵ�ַ
* @param[in] buffer       ��Ҫ��buffer��С(�ᴫ����flash sector��С4096Bytes)
* @return ����˵��
*        ʵ��buffer��С(��õ���flash sector��С)
* @note ���ڻ����յ���image���ݣ�buffer�������write_image_data_to_flash�ص�һ��д�뵽flash
*/
u8 *update_data_buf = NULL;
uint32_t platform_ota_get_flash_data_buffer(uint8_t **buffer, uint32_t size)
{
    dma_log("%s\n", __func__);
    if (update_data_buf == NULL) {
        update_data_buf = malloc(size);
        *buffer = update_data_buf;
    } else {
        dma_log("%s=====why not null\n", __func__);
        while (1);
    }
    return size;
}

/**
* @brief д��OTA Image���ݵ�flash
* @param[in] size           д�����ݵĴ�С
* @param[in] data           д�������
* @param[in] image_offset   �Ӵ�image offset����ʼд��
* @param[in] sync           �����Ƿ�ͬ��д��flash
* @note OTA Image����д�뵽flash
*       get_flash_data_buffer ��buffer���˻�д��
*       image_offset��һ�����ۼӵģ����ܻ�ӽ�С��image_offset����д������
*       ��get_flash_data_buffer��flash sector 4KB��С
*           �˽ӿڵ�image_offset����4KB����
*           ÿ��д���С����4KB
*/
__attribute__((weak))
void platform_ota_write_image_data_to_flash(uint16_t size, uint8_t *data, uint32_t image_offset, bool sync)
{
    //dma_log("%s\n", __func__);
    putchar('@');
}

/**
* @brief ��flash�ڶ�ȡOTA Image����
* @param[in] size           Ҫ��ȡ���ݵĴ�С
* @param[in] buffer         ������ݵ�buffer
* @param[in] image_offset   �Ӵ�image offset����ʼ��ȡ
* @note ��flash�ڶ�ȡOTA Image����
*/

u8 crc_os_time_dly_flag = 0;
void platform_ota_read_image_data_from_flash(uint16_t size, uint8_t *buffer, uint32_t image_offset)
{
    static cnt = 0;
    //dma_log("%s-size-%d-img_offset-%d\n", __func__, size, image_offset);
    if (crc_os_time_dly_flag) {
        if (++cnt == 10) {
            cnt = 0;
            //Ҫ��ʱ��TWS֮��ͨ��
            os_time_dly(10);
        }
    }
}

/**
* @brief ��flash�ڲ���OTA Image����
* @param[in] size           Ҫ�������ݵĴ�С
* @param[in] image_offset   �Ӵ�image offset����ʼ����
* @note ��flash�ڲ���OTA Image����
*           ����ʱ4KB����ģ�DMA_OTA_FLASH_SECTOR_SIZE �ı���
*           size�� DMA_OTA_FLASH_SECTOR_SIZE �ı���(image�����һ���ֲ���)
*           image_offset �� DMA_OTA_FLASH_SECTOR_SIZE �ı���
*/
__attribute__((weak))
void platform_ota_erase_image_data_from_flash(uint16_t size, uint32_t image_offset)
{
    dma_log("%s-size-%d-img_offset-%d\n", __func__, size, image_offset);
}

extern u8 dma_ota_spp_connect_flag;
/**
* @brief ����OTAģʽ
* @note ��ʼOTA���ص��˺���
*/
__attribute__((weak))
void app_protocol_enter_ota_state(void)
{

}
void platform_ota_enter_ota_state(void)
{
    wait_master_ota_init = 0;
    dma_enter_ota_flag = 1;
    //dma_message(APP_PROTOCOL_OTA_BEGIN, NULL, 0);
    dma_log("%s\n", __func__);
}
__attribute__((weak))
void platform_ota_set_new_image_size(u32 total_image_size)
{
    dma_log("%s==%d\n", __func__, total_image_size);
}

/**
* @brief �˳�OTAģʽ
* @param[in] error      �Ƿ��쳣�˳�
*           -true   �쳣�˳�
*           -false  �����˳�
* @note OTA�쳣�˳����������������ص��˺���
*/
void disconnect_free_ota_buffer(u8 flag);
void platform_ota_exit_ota_state(bool error)
{
    dma_enter_ota_flag = 0;
    dma_log("%s--flag-%d\n", __func__, error);
    disconnect_free_ota_buffer(0);
}

/**
* @brief OTA���ݴ������
* @param[in] total_image_size      �̼��ܴ�С
* @return ����˵��
*           -true Image�̼�û������
*           -false Image�̼�������
* @note OTA���ݴ�����ɺ�ص��˺����������ڴ˺��������̼���У��
*/
__attribute__((weak))
bool platform_ota_data_transmit_complete_and_check(uint32_t total_image_size)
{
    dma_log("%s--size-%d\n", __func__, total_image_size);
    return true;
}
/**
* @brief OTA����check��ɺ�Ļص�
* @param[in] check_pass      �����̼�У��ɹ����
*               - true �̼�У��û���⣨��ΪTWS���������߶�û���⣩
*               - false �̼�У�������⣨��ΪTWS����������һ�������⣩
* @note OTA���ݴ�����ɺ�ص��˺����������ڴ˺��������̼���У��
*/
__attribute__((weak))
void platform_ota_image_check_complete(bool check_pass)
{
    dma_log("%s--flag-%d\n", __func__, check_pass);
}

/**
* @brief Ӧ���µĹ̼���ϵͳ������ʹ���µĹ̼�����
* @return ����˵��
*           -true   Ӧ���µĹ̼��ɹ�
*           -false  Ӧ���µĹ̼�ʧ��
* @note Ӧ���µĹ̼���ϵͳ������ʹ���µĹ̼�������ֻ�й̼�У��ͨ�����Ż��ߵ�������á�
*/
__attribute__((weak))
bool platform_ota_image_apply(void)
{
    dma_log("%s\n", __func__);
    return true;
}

__attribute__((weak))
void platform_ota_send_custom_info_to_peer(uint16_t param_size, uint8_t *param_buf)
{
    dma_log("%s\n", __func__);
}

__attribute__((weak))
void dma_ota_disconnect(void)
{
    dma_log("%s\n", __func__);
}


void disconnect_free_ota_buffer(u8 flag)
{
    r_printf("%s\n", __func__);
    if (update_data_buf == NULL) {
        return ;
    }
    dma_ota_disconnect();
    if (dma_check_tws_is_master()) {
        platform_ota_send_custom_info_to_peer(3, "JLE");
    }
    if (flag) {
        dma_ota_stop_ota();
    }
    if (update_data_buf) {
        printf("===================free+++++++++++++++++\n");
        free(update_data_buf);
        update_data_buf = NULL;
    }
}


DMA_OTA_TWS_ROLE_TYPE platform_ota_get_tws_role()
{
    DMA_OTA_TWS_ROLE_TYPE role_type = DMA_OTA_TWS_UNKNOWN;
    if (dma_check_tws_is_master()) {
        role_type = DMA_OTA_TWS_MASTER;
    } else {
        role_type = DMA_OTA_TWS_SLAVE;
    }
    //dma_log("%s %d\n", __func__, role_type);
    return role_type;
}
bool platform_ota_get_mobile_mtu(uint32_t *mtu)
{
    if (mtu == NULL) {
        return false;
    }
    if (get_curr_channel_state() & IAP_CH) {
        *mtu = 500;
    } else {
        *mtu = global_local_ble_mtu - 2;
    }
    dma_log("%s-%d\n", __func__, *mtu);
    return true;
}
void platform_dma_ota_configure(void)
{
    g_dma_ota_operation.callback_by_timeout       = platform_ota_callback_by_timeout;
    g_dma_ota_operation.get_firmeware_version     = platform_get_firmeware_version;
    g_dma_ota_operation.dma_ota_heap_malloc       = platform_heap_malloc;
    g_dma_ota_operation.dma_ota_heap_free     = platform_heap_free;
    g_dma_ota_operation.get_mobile_mtu        = platform_get_mobile_mtu;
    g_dma_ota_operation.get_peer_mtu          = platform_get_peer_mtu;
    g_dma_ota_operation.get_tws_role         = platform_ota_get_tws_role;
    g_dma_ota_operation.is_tws_link_connected = platform_get_peer_connect_state;
    g_dma_ota_operation.send_data_to_mobile      = platform_ota_send_data_to_mobile;
    g_dma_ota_operation.send_data_to_tws_peer    = platform_ota_send_custom_info_to_peer;
    g_dma_ota_operation.save_ota_info            = platform_ota_save_ota_info;
    g_dma_ota_operation.read_ota_info            = platform_ota_read_ota_info;
    g_dma_ota_operation.get_flash_data_buffer         = platform_ota_get_flash_data_buffer;
    g_dma_ota_operation.write_image_data_to_flash     = platform_ota_write_image_data_to_flash;
    g_dma_ota_operation.read_image_data_from_flash    = platform_ota_read_image_data_from_flash;
    g_dma_ota_operation.erase_image_data_from_flash   = platform_ota_erase_image_data_from_flash;
    g_dma_ota_operation.enter_ota_state          =  platform_ota_enter_ota_state;
    g_dma_ota_operation.set_new_image_size       =  platform_ota_set_new_image_size;
    g_dma_ota_operation.exit_ota_state           =  platform_ota_exit_ota_state;
    g_dma_ota_operation.data_transmit_complete_and_check = platform_ota_data_transmit_complete_and_check;
    g_dma_ota_operation.image_check_complete     = platform_ota_image_check_complete;
    g_dma_ota_operation.image_apply              = platform_ota_image_apply;
}
#endif
static uint8_t vendor_id[] = {0xB0, 0x02};
static uint8_t JL_vendor_id[] = {0xD6, 0x05};

void dma_thread(void const *argument)
{
    dma_log("dma task..."); 
    while (true) {
        dma_process(0xffffffff);
    }
}

uint32_t platform_dma_init()
{
    dma_log("%s\n", __func__);
    int init_error  = 0;
    u8  device_type = 1;
    platform_dma_configure();
    dma_register_operation(&g_dma_operation);
    if (dma_use_lib_only_ble) {
        device_type = 0;
    }
    init_error = dma_protocol_init(
                     (uint8_t *)__this_cfg->dma_cfg_file_product_id,
                     (uint8_t *)__this_cfg->dma_cfg_file_product_key,
                     vendor_id,
                     device_type,
                     3,
                     dma_queue_buffer_pool
                 );

    dma_log("dma_cfg_file_product_id:%s\n", __this_cfg->dma_cfg_file_product_id);
    dma_log("dma_cfg_file_product_key:%s\n", __this_cfg->dma_cfg_file_product_key);

    dma_log(" dma_queue_buffer_pool %d----need size %d\n", init_error, sizeof(DUER_DMA_OPER) + DMA_QUEUE_BUFFER_SIZE);
//    task_create(dma_thread, NULL, "dma");
    /* dma_thread_tid = osThreadCreate(osThread(dma_thread), NULL); */
    return 0;
}

void platform_dma_ota_init()
{
    if (update_data_buf) {
        return ;
    }
    wait_master_ota_init = 1;
    if (dma_check_tws_is_master()) {
        platform_ota_send_custom_info_to_peer(3, "JLB");
    }
#if DMA_LIB_OTA_EN
    platform_dma_ota_configure();
    dma_ota_register_operation(&g_dma_ota_operation);
    dma_log("=====dma_ota_init====\n");
    dma_ota_init(560 * 1024);
#endif
    app_protocol_enter_ota_state();
}
extern int dma_disconnect(void *addr);
extern void cpu_assert_debug();
extern const int config_asser;

void dma_assert(int cond, ...)
{
    dma_log("%s\n", __func__);
// #ifdef CONFIG_RELEASE_ENABLE
#if 0
    if (!(cond)) {
        //cpu_reset();
        log_info("func:%s---line:%d",__func__,__LINE__);
        dma_disconnect(NULL);
    }
#else
    int argv[8];
    int argv_cnt = 0;
    va_list argptr;

    va_start(argptr, cond);
    for (int i = 0; i < 5; i++) {
        argv[i] = va_arg(argptr, int);
        if (argv[i]) {
            argv_cnt++;
        } else {
            break;
        }
    }
    va_end(argptr);
    if (!(cond)) {
        dma_log("================dma assert ==%d============\n", argv_cnt);
        if (argv_cnt == 2) {
            dma_log("[%s]", argv[0]);
        }
        if (argv_cnt > 3) {
            dma_log("[%s %s %d]", argv[0], argv[1], argv[2]);
        }
        log_info("func:%s---line:%d",__func__,__LINE__);
        dma_disconnect(NULL);
        //while (1);
    }
#endif
}
u16 dma_speech_data_send(u8 *buf, u16 len)
{
//DMA_ERROR_CODE dma_feed_compressed_data(const char* input_data, uint32_t date_len);
    u16 res = 0;
    if (dma_ota_spp_connect_flag) {
        return DMA_SUCCESS;
    }
    if (dma_role_switch_ble_disconnect_flag) {
        putchar('K');
        //��Ҫ�����л������̲���Ӧmic���ݷ���
        return res;
    }
    res = dma_feed_compressed_data(buf, len);
    if (DMA_SUCCESS != res) {
        dma_log("send error %d\n", res);
    }
    return res;
}
// extern DMA_ERROR_CODE dma_notify_state(DMA_NOTIFY_STATE state, void *param_buf, uint32_t  param_size);
int dma_start_voice_recognition(u8 en)
{
    u8 flag = true;
    if (dma_ota_spp_connect_flag) {
        return -1;
    }
    if (en == 2) {
        flag = true;
    } else {
        flag = false;
    }
    //DMA_ERROR_CODE dma_notify_state(DMA_NOTIFY_STATE state);
    dma_log("dma_notify_state---%d---%d\n", DMA_NOTIFY_STATE_DOUBLE_CLICK, flag);
    if (en) {
        dma_notify_state(DMA_NOTIFY_STATE_DOUBLE_CLICK, &flag, 1);
    }
    return 0;
}
extern bool check_dma_le_handle(void);
extern void dma_ble_disconnect(void);
u8 tws_role_switch_wait_cnt = 0;
u8 tws_role_switch_check_ble_status()
{
    if (check_dma_le_handle()) {
        if ((tws_role_switch_wait_cnt == 10) && (dma_role_switch_ble_disconnect_flag == 0xAA)) {
            dma_role_switch_ble_disconnect_flag = 0xAB;
    log_info("*****func:%s******\n",__func__);
            dma_ble_disconnect();
        }
        if (tws_role_switch_wait_cnt++ > 12) {
            tws_role_switch_wait_cnt = 0;
            y_printf("tws_role_switch_wait timeout\n");
            return 0;
        }
        putchar('@');
        return 1;
    }
    return 0;
}
int dma_update_tws_state_to_lib(int state)
{
    u8 flag = true;
    log_info("*****func:%s******\n",__func__);
    // return 0;
    dma_log("dma_notify_state---%d\n", state);
    if (state == JL_NOTIFY_STATE_STOP_OTA) {
        if (dma_enter_ota_flag) {
            r_printf("user___stop ota===\n");
            dma_ota_stop_ota();
            //dma_ble_disconnect();
        }
    }
    if (state == DMA_NOTIFY_STATE_TWS_DISCONNECT) {
        if (update_data_buf) {
            r_printf("user___stop ota 2222===\n");
            disconnect_free_ota_buffer(1);
        }
    }
    if (state == DMA_NOTIFY_STATE_TWS_CONNECT) {
        //��ʼ���жϵ����Ӳ�׼���������ϣ��ӻ�Ҫ����
        if (!dma_check_tws_is_master()) {
            dma_log("ble connect slave before tws pair\n");
            dma_ble_disconnect();
        }
        dma_ble_adv_enable(0);
    }
    if (state == DMA_NOTIFY_STATE_ROLE_SWITCH_START) {
        //�����л��Ͽ�BLE������ǳ�ʱ��Ƚ���
        dma_ble_adv_enable(0);
        if (dma_check_tws_is_master()) {
            dma_role_switch_ble_disconnect_flag = 0xAA;
            tws_role_switch_wait_cnt = 0;
        }
    }
    // if (state < JL_NOTIFY_STATE_ONE_CLICK) 
    {
        dma_notify_state(state, &flag, 1);
    }
    if (state == DMA_NOTIFY_STATE_ROLE_SWITCH_FINISH) {
        if (!dma_check_tws_is_master()) {
            dma_ble_adv_enable(0);
        }
    }
    if (state == DMA_NOTIFY_STATE_DMA_DISCONNECTED) {
        dma_role_switch_ble_disconnect_flag = 0x0;
    }
    return 0;
}
void dma_ota_recieve_data(u8 *buf, u16 len)
{
#if DMA_LIB_OTA_EN
    if (len < 32) {
        printf("ota buf");
        put_buf(buf, len);
    }
    if (update_data_buf == NULL) {
        return;
    }
    //DMA_OTA_CMD_IMAGE_VERIFY �¼�Ҫ������ʱУ����ʱ
    if ((len == 1) && (buf[0] == 0x90)) {
        printf("set crc_os_time_dly_flag\n");
        crc_os_time_dly_flag = 1;
    }
    putchar('[');
    if (get_curr_channel_state() & IAP_CH) {
        dma_ota_recv_mobile_data(len, buf, false, false);
    } else {
        dma_ota_recv_mobile_data(len, buf, true, true);
    }
    putchar(']');
#endif
}
void dma_recieve_data(u8 *buf, u16 len)
{
    log_info("*****func:%s******\n",__func__);
    //DMA_ERROR_CODE dma_recv_mobile_data(const char *input_data, uint32_t date_len);
    dma_recv_mobile_data(buf, len);
    //����֪ͨapp �л�֮���յ����ݰ���Ϊ֪ͨ�ɹ����Ͽ�ble
    if (dma_role_switch_ble_disconnect_flag == 0xAA) {
        dma_role_switch_ble_disconnect_flag = 0xAB;
        dma_log("role_switch disconnect\n");
        dma_ble_disconnect();
    }
}

void dma_ota_peer_recieve_data(u8 *buf, u16 len)
{
#if DMA_LIB_OTA_EN
    if (dma_check_tws_is_master()) {
        //�������û�д�����һ�����ݾʹ���TWS�����������ݰ������ܻᵼ�¿�ʼOTA��ʧ��
        while (wait_master_ota_init) {
            putchar('@');
            os_time_dly(10);
        }
    }
    dma_log("%s -- %d\n", __func__, len);
    if (!(get_curr_channel_state() & IAP_CH)) {
        //BLE��ʱ�����а�����TWSֱ��ת�������ġ����dly��ʶҪ��������
        if ((len == 2) && (buf[0] == 0x09) && (buf[1] == 0x90)) {
            printf("set crc_os_time_dly_flag\n");
            crc_os_time_dly_flag = 1;
        }
        //BLE�ӻ�û�����ӺͶϿ���Ϣ��������Щ����Ҫ������
        if ((len == 3) && (buf[0] == 'J') && (buf[1] == 'L') && (buf[2] == 'B')) {
            platform_dma_ota_init();
            return ;
        }
        if ((len == 3) && (buf[0] == 'J') && (buf[1] == 'L') && (buf[2] == 'E')) {
            disconnect_free_ota_buffer(1);
            return ;
        }
    }
    dma_ota_recv_tws_data(len, buf);
#endif
}
void dma_peer_recieve_data(u8 *buf, u16 len)
{
    dma_log("%s -- %d\n", __func__, len);
    dma_recv_peer_data(buf, len);
}

extern bool dma_pair_state();
int update_tws_battary_to_app()
{
    u8 flag = true;
    int tws_side = 0;
    if (!dma_pair_state()) {
        return -1;
    }
    platform_get_tws_side(&tws_side);
    if (tws_side == DMA_SIDE_LEFT) {
        flag = true;
    } else {
        flag = false;
    }
    dma_log("dma_notify_bat_state--side:%d\n", flag);
    dma_notify_state(DMA_NOTIFY_STATE_BATTERY_LEVEL_UPDATE, &flag, 1);
    return 0;
}

