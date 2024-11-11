#include "smartbox/config.h"
#include "smartbox/smartbox.h"
#include "smartbox/function.h"
#include "smartbox/feature.h"
#include "smartbox/switch_device.h"
#include "smartbox/smartbox_device_config.h"
#include "smartbox/mass_data/mass_data.h"
#include "file_transfer.h"
#include "file_delete.h"
#include "file_env_prepare.h"
#include "file_trans_back.h"
#include "dev_format.h"
#include "smartbox/event.h"
#include "btstack/avctp_user.h"
#include "app_action.h"
#include "smartbox_adv_bluetooth.h"
#include "smartbox_extra_flash_cmd.h"
#include "smartbox_update.h"
#include "fs.h"
#include "file_bluk_trans_prepare.h"
#include "sensors_data_opt.h"
#include "file_simple_transfer.h"
#include "custom_cfg.h"
#include "JL_rcsp_api.h"
#include "comm_setting/comm_setting.h"

#undef _DEBUG_H_
#define LOG_TAG_CONST       COMM_SETTING          //修改成文件名
#define LOG_TAG             "[COMM_SETTING]"
#include "debug.h"
#define LOG_v(t)  log_tag_const_v_ ## t
#define LOG_i(t)  log_tag_const_i_ ## t
#define LOG_d(t)  log_tag_const_d_ ## t
#define LOG_w(t)  log_tag_const_w_ ## t
#define LOG_e(t)  log_tag_const_e_ ## t
#define LOG_c(t)  log_tag_const_c_ ## t
#define LOG_tag(tag, n) n(tag)
const char LOG_tag(LOG_TAG_CONST,LOG_v) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_i) AT(.LOG_TAG_CONST) = 1; //log_info
const char LOG_tag(LOG_TAG_CONST,LOG_d) AT(.LOG_TAG_CONST) = 1; //log_debug
const char LOG_tag(LOG_TAG_CONST,LOG_w) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_e) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_c) AT(.LOG_TAG_CONST) = 1;


#if (SMART_BOX_EN)


static struct __COMM_SETTING_INFO info = {
    .screen_brightness = 80,
    .screen_ext_info.screen_shape = SCREEN_RECTANGLE,
    .screen_ext_info.screen_radius = 0x00,
    .screen_ext_info.screen_color_Alpha = 0XFF,
    .screen_ext_info.screen_color_Red = 0XFF,
    .screen_ext_info.screen_color_Green = 0XFF,
    .screen_ext_info.screen_color_Blue = 0XFF,
    .screen_ext_info.screen_Width = 320,
    .screen_ext_info.screen_Height = 172,
};

#define __this  (&info)



/**
 * @description: 屏幕亮度回复数据
 * @return {*}
 * @param {void} *priv
 * @param {u8} *buf
 * @param {u16} buf_size
 * @param {_COMM_SETTING_PARAM} *param
 */
static u32 screen_brightness_parse_packet(void *priv, u8 *buf, u16 buf_size, struct _COMM_SETTING_PARAM *param)
{
    u32 offset = 0;
    struct _COMM_SETTING_COMM_RESP comm_resp;

    comm_resp.result = COMM_SETTING_OP_SUCCESS;
    comm_resp.payload_version = COMM_SETTING_VERSION;
    comm_resp.payload_func = SET_SCREEN_BRIGHTNESS;
    comm_resp.func_version = 0x00;
    comm_resp.func_op = param->func_op;
    memcpy(&buf[offset], &comm_resp, sizeof(struct _COMM_SETTING_COMM_RESP));
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_COMM_RESP, payload_func) + offset] , comm_resp.payload_func);
    offset += sizeof(struct _COMM_SETTING_COMM_RESP);
    
    buf[offset++] = __this->screen_brightness;

    log_debug("%s[line:%d]\n",__func__,__LINE__);
    log_debug_hexdump(buf, offset);
    return offset;
    

}
/**
 * @description: 设置屏幕亮度
 * @return {*}
 * @param {u8} value
 */
static void set_screen_brightness(u8 value)
{
    log_info("%s[line:%d ,value:%d]\n",__func__,__LINE__, value);
    __this->screen_brightness = value;
    
}

/**
 * @description: 屏幕信息回应
 * @return {*}
 * @param {void} *priv
 * @param {u8} *buf
 * @param {u16} buf_size
 * @param {_COMM_SETTING_PARAM} *param
 */
static u32 screen_ext_info_parse_packet(void *priv, u8 *buf, u16 buf_size, struct _COMM_SETTING_PARAM *param)
{
    u32 offset = 0;
    struct _COMM_SETTING_COMM_RESP comm_resp;

    comm_resp.result = COMM_SETTING_OP_SUCCESS;
    comm_resp.payload_version = COMM_SETTING_VERSION;
    comm_resp.payload_func = SET_FUNC_SCREEN_EXT_INFO;//SET_FUNC_USAGE_RES;
    comm_resp.func_version = 0x00;
    comm_resp.func_op = param->func_op;
    memcpy(&buf[offset], &comm_resp, sizeof(struct _COMM_SETTING_COMM_RESP));
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_COMM_RESP, payload_func) + offset] , comm_resp.payload_func);
    offset += sizeof(struct _COMM_SETTING_COMM_RESP);
    
    memcpy(&buf[offset], &__this->screen_ext_info, sizeof(struct _COMM_SETTING_SCREEN_EXT_INFO));
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_SCREEN_EXT_INFO, screen_radius)+offset] , __this->screen_ext_info.screen_radius);
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_SCREEN_EXT_INFO, screen_Width)+offset] , __this->screen_ext_info.screen_Width);
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_SCREEN_EXT_INFO, screen_Height)+offset] , __this->screen_ext_info.screen_Height);
    offset += sizeof(struct _COMM_SETTING_SCREEN_EXT_INFO);


    log_debug("%s[line:%d, len:%d]\n",__func__,__LINE__, offset);
    log_debug_hexdump(buf, offset);
    return offset;
    

}

static int calculate_file_crc(u8 *file_path, u16* file_crc)
{
    int result = 0;

    u8 *data = malloc(256);
    if(NULL == data){
        result = -1;
        goto __calculate_file_crc_err;
    }

    FILE *file = NULL;

    file = fopen(file_path, "r");
    if (NULL == file) {
        result = -2;
        
        goto __calculate_file_crc_err;
    }
    u32 file_len = flen(file);
    u16 temp_crc = 0;

    for (u32 crc_offset = 0; crc_offset < file_len;) {
        wdt_clear();
        u32 crc_len = (file_len - crc_offset) > 256 ? 256 : (file_len - crc_offset);
        fseek(file, crc_offset, SEEK_SET);
        if (crc_len != fread(file, data, crc_len)) {
            log_error("err : read fail, %s, %d\n", file_path, crc_offset);
            result = -3;
            goto __calculate_file_crc_err;
        }
        putchar('h');
        temp_crc = CRC16_with_initval(data, crc_len, temp_crc);
        crc_offset += crc_len;
    }
    *file_crc = temp_crc;
    log_debug("%s[line:%d, file_crc:%d, temp_crc:%d]\n",__func__,__LINE__, *file_crc, temp_crc);
    
__calculate_file_crc_err:
    if (file) {      
        fclose(file);
    }
    if(data){
        free(data);
        data = NULL;
    }
    if(result){
        log_error("%s[line:%d result:%d]\n",__func__,__LINE__, result);
        
    }
    return result;
}

static u32 func_usage_res_read_parse_packet(void *priv, u8 *buf, u16 buf_size, struct _COMM_SETTING_PARAM *param)
{
    u32 offset = 0;
    struct _COMM_SETTING_COMM_RESP comm_resp;
    struct _COMM_SETTING_FUNC_USAGE_PARAM func_usage_papam;

    u16 temp_file_crc = 0;
    switch (param->func_params[0])  
    {
    case COMM_SETTING_SCREEN_SAVER:
        log_info("屏保程序\n");
        func_usage_papam.func_code = COMM_SETTING_SCREEN_SAVER;
        func_usage_papam.dev_headle = BS_FLASH;

        FILE * f = fopen(SCREEN_SAVER_PATH_C, "r");
        if(f){
            g_printf("open ok");
            struct vfs_attr attr ={0};
            fget_attrs(f, &attr);
            func_usage_papam.file_cluster = attr.sclust;
            fclose(f);
        } else {
            func_usage_papam.file_cluster = 0;
        }

        g_printf("cluster = %x",func_usage_papam.file_cluster);
        
        
        g_printf("SCREEN_SAVER_PATH_C %s SCREEN_SAVER_PATH %s", SCREEN_SAVER_PATH_C,SCREEN_SAVER_PATH);
        calculate_file_crc(SCREEN_SAVER_PATH_C, &temp_file_crc);
        func_usage_papam.crc = temp_file_crc;

        g_printf("temp_file_crc = %x",temp_file_crc);

        func_usage_papam.path_len = strlen(SCREEN_SAVER_PATH);
        func_usage_papam.path_data = SCREEN_SAVER_PATH;

        g_printf("len %d data : %s",func_usage_papam.path_len, func_usage_papam.path_data);

        break;
    case COMM_SETTING_BOOT_ANIMATION:
        log_info("开机动画\n");
        goto __func_usage_res_read_end;
        break;
    
    default:
        break;
    }

    comm_resp.result = COMM_SETTING_OP_SUCCESS;
    comm_resp.payload_version = COMM_SETTING_VERSION;
    comm_resp.payload_func = SET_FUNC_USAGE_RES;
    comm_resp.func_version = 0x00;
    comm_resp.func_op = param->func_op;
    memcpy(&buf[offset], &comm_resp, sizeof(struct _COMM_SETTING_COMM_RESP));
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_COMM_RESP, payload_func) + offset] , comm_resp.payload_func);
    offset += sizeof(struct _COMM_SETTING_COMM_RESP);

    buf[offset++] = func_usage_papam.func_code;
    WRITE_BIG_U32(&buf[offsetof(struct _COMM_SETTING_FUNC_USAGE_PARAM, dev_headle) + offset - 1] , func_usage_papam.dev_headle);
    WRITE_BIG_U32(&buf[offsetof(struct _COMM_SETTING_FUNC_USAGE_PARAM, file_cluster) + offset - 1] , func_usage_papam.file_cluster);
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_FUNC_USAGE_PARAM, crc) + offset - 1] , func_usage_papam.crc);
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_FUNC_USAGE_PARAM, path_len) + offset - 1] , func_usage_papam.path_len);
    offset += 12;
    memcpy(&buf[offset], func_usage_papam.path_data, func_usage_papam.path_len);
    offset += func_usage_papam.path_len;

    g_printf("len %d data : %s",func_usage_papam.path_len, func_usage_papam.path_data);

    log_debug("%s[line:%d, len:%d]\n",__func__,__LINE__, offset);
    log_debug_hexdump(buf, offset);

__func_usage_res_read_end:
    return offset;

}


static u32 func_usage_res_write_parse_packet(void *priv, u8 *buf, u16 buf_size, struct _COMM_SETTING_PARAM *param)
{
    u32 offset = 0;
    u16 temp_file_crc = 0;
    struct _COMM_SETTING_COMM_RESP comm_resp;
    struct _COMM_SETTING_FUNC_USAGE_PARAM func_usage_papam;
    log_info("%s[line:%d]\n",__func__,__LINE__);
    switch (param->func_params[0])  
    {
    case COMM_SETTING_SCREEN_SAVER:
        func_usage_papam.func_code = COMM_SETTING_SCREEN_SAVER;
        func_usage_papam.dev_headle = BS_FLASH;
        func_usage_papam.file_cluster = 0x00;
        func_usage_papam.crc = 0x00;
        calculate_file_crc(SCREEN_SAVER_PATH_C, &temp_file_crc);
        func_usage_papam.crc = temp_file_crc;
        func_usage_papam.path_len = READ_BIG_U16(&param->func_params[11]);
        func_usage_papam.path_data = &(param->func_params[13]);

        g_printf("len %d data : %s",func_usage_papam.path_len, func_usage_papam.path_data);
        put_buf(func_usage_papam.path_data, func_usage_papam.path_len);
        break;
    case COMM_SETTING_BOOT_ANIMATION:
        goto __func_usage_res_write_end;
        break;
    
    default:
        break;
    }

    comm_resp.result = COMM_SETTING_OP_SUCCESS;
    comm_resp.payload_version = COMM_SETTING_VERSION;
    comm_resp.payload_func = SET_FUNC_USAGE_RES;
    comm_resp.func_version = 0x00;
    comm_resp.func_op = param->func_op;
    memcpy(&buf[offset], &comm_resp, sizeof(struct _COMM_SETTING_COMM_RESP));
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_COMM_RESP, payload_func) + offset] , comm_resp.payload_func);
    offset += sizeof(struct _COMM_SETTING_COMM_RESP);

    buf[offset++] = func_usage_papam.func_code;
    WRITE_BIG_U32(&buf[offsetof(struct _COMM_SETTING_FUNC_USAGE_PARAM, dev_headle) + offset -1] , func_usage_papam.dev_headle);
    WRITE_BIG_U32(&buf[offsetof(struct _COMM_SETTING_FUNC_USAGE_PARAM, file_cluster) + offset -1] , func_usage_papam.file_cluster);
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_FUNC_USAGE_PARAM, crc) + offset-1] , func_usage_papam.crc);
    WRITE_BIG_U16(&buf[offsetof(struct _COMM_SETTING_FUNC_USAGE_PARAM, path_len) + offset-1] , func_usage_papam.path_len);
    offset += 12;
    memcpy(&buf[offset], func_usage_papam.path_data, func_usage_papam.path_len);
    offset += func_usage_papam.path_len;

    g_printf("len %d data : %s",func_usage_papam.path_len, func_usage_papam.path_data);

    log_debug("%s[line:%d, len:%d]\n",__func__,__LINE__, offset);
    log_debug_hexdump(buf, offset);
__func_usage_res_write_end:

    return offset;

}



static int comm_settiong_deal(void *priv, u8 OpCode, u8 OpCode_SN, u8 *data, u16 len, struct _COMM_SETTING_PARAM *param)
{
    int ret = 0;
    u32 wlen = 0;
    u8 *resp = NULL;

    u8 *p_offset = param->func_params;

    switch (param->function)
    {
    case SET_FUNC_USAGE_RES:
        switch (param->func_op)
        {
        case READ_OPT:
            resp = zalloc(TARGET_FEATURE_RESP_BUF_SIZE);
            ASSERT(resp);
            wlen = func_usage_res_read_parse_packet(priv, resp, TARGET_FEATURE_RESP_BUF_SIZE, param);
            if(!wlen){
                log_error("func usage res read parse packet wlen err!!!\n");
                ret = -1;
            }else{
                JL_CMD_response_send(OpCode, JL_PRO_STATUS_SUCCESS, OpCode_SN, (u8 *)resp, wlen);
                ret = 0;
            }
            free(resp);
            break;
        case WRITE_OPT:
            resp = zalloc(TARGET_FEATURE_RESP_BUF_SIZE);
            ASSERT(resp);
            wlen = func_usage_res_write_parse_packet(priv, resp, TARGET_FEATURE_RESP_BUF_SIZE, param);
            if(!wlen){
                log_error("func usage res write parse packet wlen err!!!\n");
                ret = -1;
            }else{
                JL_CMD_response_send(OpCode, JL_PRO_STATUS_SUCCESS, OpCode_SN, (u8 *)resp, wlen);
                ret = 0;
            }
            free(resp);
            break;
        
        default:
            ret = -1;
            break;
        }
        break;

    case SET_FUNC_SCREEN_EXT_INFO:
        switch (param->func_op)
        {
        case READ_OPT:
            /* code */
            resp = zalloc(TARGET_FEATURE_RESP_BUF_SIZE);
            ASSERT(resp);
            wlen = screen_ext_info_parse_packet(priv, resp, TARGET_FEATURE_RESP_BUF_SIZE, &param);
            if(!wlen){
                log_error("screen ext info parse packet wlen err!!!\n");
                ret = -1;
            }else{
                JL_CMD_response_send(OpCode, JL_PRO_STATUS_SUCCESS, OpCode_SN, (u8 *)resp, wlen);
                ret = 0;
            }
            free(resp);
            break;
        
        default:
            ret = -1;
            break;
        }

        break;

    case SET_SCREEN_BRIGHTNESS:
        switch (param->func_op)
        {
        case WRITE_OPT:
            put_buf(param->func_params, param->func_params_len);
            set_screen_brightness(param->func_params[0]);
        case READ_OPT:
            /* code */
            resp = zalloc(TARGET_FEATURE_RESP_BUF_SIZE);
            ASSERT(resp);
            wlen = screen_brightness_parse_packet(priv, resp, TARGET_FEATURE_RESP_BUF_SIZE, param);
            JL_CMD_response_send(OpCode, JL_PRO_STATUS_SUCCESS, OpCode_SN, (u8 *)resp, wlen);
            free(resp);
            ret = 0;
            break;
        
        default:
            ret = -1;
            break;
        }

        break;
    
    
    default:
        ret = -2;
        break;
    }
__comm_settiong_deal_end:
    return ret;
}


void comm_settiong_recieve(void *priv, u8 OpCode, u8 OpCode_SN, u8 *data, u16 len)
{
    int result = 0;
    struct _COMM_SETTING_PARAM comm_setting_param;
    log_info(" %s[line:%d, len:%d]\n",__func__,__LINE__, len);
    put_buf(data, len);

    comm_setting_param.version = data[0];
    comm_setting_param.function = READ_BIG_U16(&data[1]);
    comm_setting_param.func_version = data[3];
    comm_setting_param.func_op = data[4];
    comm_setting_param.func_params = &data[5];
    comm_setting_param.func_params_len = len - FUNC_PARAMS_OFFSET;

    log_debug("version:%d, function:%x, func_version:%d, func_op:%d, func_params_len:%d\n", 
            comm_setting_param.version, comm_setting_param.function, comm_setting_param.func_version, comm_setting_param.func_op, comm_setting_param.func_params_len);
    log_debug_hexdump(comm_setting_param.func_params, comm_setting_param.func_params_len);

    result = comm_settiong_deal(priv, OpCode, OpCode_SN, data, len, &comm_setting_param);
    if(result){
        log_error("%s[line:%d result:%d]\n",__func__,__LINE__, result);
        
        JL_CMD_response_send(OpCode, JL_PRO_STATUS_UNKOWN_CMD, OpCode_SN, 0, 0);
    }
    return;
}






#endif//SMART_BOX_EN


