#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "app_protocol_api.h"
#include "system/includes.h"
#include "vm.h"
#include "audio_config.h"
#include "app_power_manage.h"
#include "user_cfg.h"
#if APP_PROTOCOL_DMA_CODE

#if 1
#define APP_DMA_LOG       printf
#define APP_DMA_DUMP      put_buf
#else
#define APP_DMA_LOG(...)
#define APP_DMA_DUMP(...)
#endif

//*********************************************************************************//
//                                 DMA认证信息                                     //
//*********************************************************************************//
#define DMA_PRODUCT_INFO_EN         1 //三元组使能
#define DMA_PRODUCT_INFO_TEST       1

#if DMA_PRODUCT_INFO_EN
u8 use_triad_info = 1;
#endif

//#if DMA_PRODUCT_INFO_TEST
//static const char *dma_product_id  = "5cP1rq6H4C4XiaUU8shGvH0fayKmaWCo";//asoYwYghv0fy6HFexl6bTIZUHjyZGnEH";
//static const char *dma_triad_id    = "001AFFjP0000001100009231";//0004BcJb0000000200000002";
//static const char *dma_secret      = "13d50217906a564f";//c26f08b216068119";
//#endif
//static const char *dma_product_key = "e67b5339a3e1d07135fa955e38b6c300";//Yg5Xb2NOK01bgB9csSUHAAgG4lUjMXXZ";
//
//#define DMA_PRODUCT_ID_LEN      65
//#define DMA_PRODUCT_KEY_LEN     65
//#define DMA_TRIAD_ID_LEN        32
//#define DMA_SECRET_LEN          32
 
#if 0
#if DMA_PRODUCT_INFO_TEST
static const char *dma_product_id  = "5cP1rq6H4C4XiaUU8shGvH0fayKmaWCo";
// static const char *dma_product_id  = "zca5ARwRpYvlSn1RciOX5WYfsxzDCVfh";
static const char *dma_triad_id    = "001AFFjP0000001100009239";
static const char *dma_secret      = "8cd6d1e50d13fbae";
#endif
static const char *dma_product_key = "3H7o4ifRBF2cA8R2xmBlIHmwYkAR77FD";
// static const char *dma_product_key = "3faU2WzsYXuCUGoI9im87UfO3mSWfEWC";
#else
// 百度提供的小度2.0的三元组
static const char *dma_product_id  = "zca5ARwRpYvlSn1RciOX5WYfsxzDCVfh";
 static const char *dma_product_key = "3faU2WzsYXuCUGoI9im87UfO3mSWfEWC";//"389b0d78282cf26c6a5c16e22717d64d";

// static const char *dma_triad_id    = "002AKDNK0000002400000010";
// static const char *dma_secret      = "3bea20cb915a1444";


//  static const char* dma_triad_id =    "002a1Cjn0000002400000001";
//  static const char* dma_secret =      "9000ba1c0d89df35";

 static const char* dma_triad_id =    "002a1eeV0000002400000001";  
 static const char* dma_secret =      "a893b67950c2a035";
//  static const char* dma_triad_id =    "002a1eeV0000002400000002";
//  static const char* dma_secret =      "63582a5642a7c3e3";





#endif


// static const char* dma_product_id =  "EHD3c3QDHMzy8qcSUTOgFoHYWcYsvko0";//C7 F4 27 E6 2F DA
// static const char* dma_triad_id =	 "00266D2G0000002300000032";
// static const char* dma_secret =		 "315b8298870376df";
// static const char* dma_product_key = "UI19a6CiDAllDLN8m4k9UrH5iuFtTrlI";

#define DMA_PRODUCT_ID_LEN      65
#define DMA_PRODUCT_KEY_LEN     65
#define DMA_TRIAD_ID_LEN        32
#define DMA_SECRET_LEN          32

#define DMA_LEGAL_CHAR(c)       ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

static u16 dma_get_one_info(const u8 *in, u8 *out)
{
    int read_len = 0;
    const u8 *p = in;

    while (DMA_LEGAL_CHAR(*p) && *p != ',') { //read Product ID
        *out++ = *p++;
        read_len++;
    }
    return read_len;
}

u8 read_dma_product_info_from_flash(u8 *read_buf, u16 buflen)
{
    u8 *rp = read_buf;
    const u8 *dma_ptr = (u8 *)app_protocal_get_license_ptr();

    printf("%s", __func__);
    if (dma_ptr == NULL) {
        return FALSE;
    }

    if (dma_get_one_info(dma_ptr, rp) != 32) {
        return FALSE;
    }
    dma_ptr += 33;

    rp = read_buf + DMA_PRODUCT_ID_LEN;
    memcpy(rp, dma_product_key, strlen(dma_product_key));

    rp = read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN;
    if (dma_get_one_info(dma_ptr, rp) != 24) {
        return FALSE;
    }
    dma_ptr += 25;

    rp = read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN;
    if (dma_get_one_info(dma_ptr, rp) != 16) {
        return FALSE;
    }

    return TRUE;
}
__attribute__((weak))
void bt_update_testbox_addr(u8 *addr)
{

}
void dueros_dma_manufacturer_info_init()
{
    u8 read_buf[DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN + DMA_SECRET_LEN + 1] = {0};
    bool ret = FALSE;

    APP_DMA_LOG("dueros_dma_manufacturer_info_init\n");

#if DMA_PRODUCT_INFO_TEST
    memcpy(read_buf, dma_product_id, strlen(dma_product_id));
    memcpy(read_buf + DMA_PRODUCT_ID_LEN, dma_product_key, strlen(dma_product_key));
    memcpy(read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN, dma_triad_id, strlen(dma_triad_id));
    memcpy(read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN, dma_secret, strlen(dma_secret));
    ret = TRUE;
#else
    //  ret = read_dma_product_info_from_flash(read_buf, sizeof(read_buf));
#endif

    if (ret == TRUE) {
        APP_DMA_LOG("read license success\n");
        APP_DMA_LOG("product id: %s\n", read_buf);
        APP_DMA_LOG("product key: %s\n", read_buf + DMA_PRODUCT_ID_LEN);
        APP_DMA_LOG("triad id: %s\n", read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN);
        APP_DMA_LOG("secret: %s\n", read_buf + DMA_PRODUCT_ID_LEN + DMA_PRODUCT_KEY_LEN + DMA_TRIAD_ID_LEN);
        app_protocol_set_info_group(DMA_HANDLER_ID, read_buf);
    } else {
        app_protocol_set_info_group(DMA_HANDLER_ID, NULL);
    }

#if 1
    // 同一个TID需要固定一个MAC地址
    u8 mac[] = {0xF4, 0x43, 0x8D, 0x29, 0x17, 0x01};
    u8 ble_mac[6];
    void bt_update_mac_addr(u8 * addr);
    void lmp_hci_write_local_address(const u8 * addr);
    void bt_update_testbox_addr(u8 * addr);
    extern int le_controller_set_mac(void *addr);
    //extern void lib_make_ble_address(u8 * ble_address, u8 * edr_address);
    bt_update_mac_addr(mac);
    lmp_hci_write_local_address(mac);
    bt_update_testbox_addr(mac);
    //lib_make_ble_address(ble_mac, mac);
    le_controller_set_mac(mac); //修改BLE地址
    APP_DMA_DUMP(mac, 6);
    APP_DMA_DUMP(ble_mac, 6);
#endif
}

//*********************************************************************************//
//                                 DMA提示音                                       //
//*********************************************************************************//
const char *dma_notice_tab[APP_RROTOCOL_TONE_MAX] = {
    [APP_PROTOCOL_TONE_CONNECTED_ALL_FINISH]		= TONE_RES_ROOT_PATH"tone/xd_ok.*",//所有连接完成【已连接，你可以按AI键来和我进行对话】
    [APP_PROTOCOL_TONE_PROTOCOL_CONNECTED]		= TONE_RES_ROOT_PATH"tone/xd_con.*",//小度APP已连接，经典蓝牙未连接【请在手机上完成蓝牙配对】
    [APP_PROTOCOL_TONE_CONNECTED_NEED_OPEN_APP]	= TONE_RES_ROOT_PATH"tone/xd_btcon.*",//经典蓝牙已连接，小度app未连接【已配对，请打开小度app进行连接】
    [APP_PROTOCOL_TONE_DISCONNECTED]				= TONE_RES_ROOT_PATH"tone/xd_dis.*",//经典蓝牙已断开【蓝牙已断开，请在手机上完成蓝牙配对】
    [APP_PROTOCOL_TONE_DISCONNECTED_ALL]			= TONE_RES_ROOT_PATH"tone/xd_alldis.*",//经典蓝牙和小度都断开了【蓝牙未连接，请用手机蓝牙和我连接吧】
    [APP_RROTOCOL_TONE_SPEECH_APP_START]	    	= TONE_NORMAL,
    [APP_RROTOCOL_TONE_SPEECH_KEY_START]	    	= TONE_NORMAL,
};




// 歌词
void user_define_bt_music_lyric_command(char *ext, char *str){
    r_printf("func:%s----",__func__);
    if(str != NULL){
        put_buf(str,128);
        u8 data,data0,data1;
        if(str[21] == 0x2c){
            data = str[20]-0x30;;
        }else{
            data0 = str[20]-0x30;
            data1 = str[21]-0x30;
            data = data0*10+data1;
        }

        r_printf("func:%s---index:%d-",__func__,data);
    }

}

// 导航
void user_define_bt_navigation_text_command(char *ext, char *str){
    r_printf("func:%s----",__func__);
    if(str != NULL){
        put_buf(str,128);
    }

};

#endif

