/**
 * @file audio_usb_ext_audio.c
 * @author FSW
 * @brief 与SDK\cpu\br25\audio_dec\audio_usb_mic.c文件的功能类似，提供音源(IIS)给PC mic
 * @version 0.1
 * @date 2021-02-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "asm/includes.h"
#include "media/includes.h"
#include "system/includes.h"
#include "device/uac_stream.h"
#include "app_main.h"
#include "user_cfg_id.h"
// #include "audio_common/audio_iis.h"
#include "user_src_task.h"

#define PCM_ENC2USB_OUTBUF_LEN		(5 * 1024)

/* #define USB_MIC_BUF_NUM        3 */
/* #define USB_MIC_CH_NUM         1 */
/* #define USB_MIC_IRQ_POINTS     256 */
/* #define USB_MIC_BUFS_SIZE      (USB_MIC_CH_NUM * USB_MIC_BUF_NUM * USB_MIC_IRQ_POINTS) */

#define USB_MIC_STOP  0x00
#define USB_MIC_START 0x01

extern struct audio_adc_hdl adc_hdl;
extern u16 uac_get_mic_vol(const u8 usb_id);

struct _usb_mic_hdl {
    cbuffer_t output_cbuf;
    volatile void *user_src;
    u16 src_in_sr;
    u16 src_out_sr;
    u16 src_nor_sr;
    u8 *output_buf;//[PCM_ENC2USB_OUTBUF_LEN];
    u8 rec_tx_channels;
    u8 mic_data_ok;/*mic数据等到一定长度再开始发送*/
    u8 status;
    u8 drop_data; //用来丢掉刚开mic的前几帧数据
    volatile u8 busy;
};

static struct _usb_mic_hdl *usb_mic_hdl = NULL;
static struct _usb_mic_hdl *usb_mic_hdl_1 = NULL;

static int usb_audio_mic_sync(u32 data_size)
{
#if 0
    int change_point = 0;

    if (data_size > __this->rec_top_size) {
        change_point = -1;
    } else if (data_size < __this->rec_bottom_size) {
        change_point = 1;
    }

    if (change_point) {
        struct audio_pcm_src src;
        src.resample = 0;
        src.ratio_i = (1024) * 2;
        src.ratio_o = (1024 + change_point) * 2;
        src.convert = 1;
        dev_ioctl(__this->rec_dev, AUDIOC_PCM_RATE_CTL, (u32)&src);
    }
#endif

    return 0;
}

static u8 cnt0 = 0;
static u8 cnt1 = 0;
static u8 cnt2 = 0;

u8 get_usb_state(void)
{
    return usb_mic_hdl && usb_mic_hdl->busy;
}
extern struct audio_dac_channel default_dac;
static u16 user_cnt = 0;
const s16 tsin_48k[48] = {
    0, 2139, 4240, 6270, 8192, 9974, 11585, 12998,
    14189, 15137, 15826, 16244, 16384, 16244, 15826, 15137,
    14189, 12998, 11585, 9974, 8192, 6270, 4240, 2139,
    0, -2139, -4240, -6270, -8192, -9974, -11585, -12998,
    -14189, -15137, -15826, -16244, -16384, -16244, -15826, -15137,
    -14189, -12998, -11585, -9974, -8192, -6270, -4240, -2139
};

int get_sine_data(u16 *s_cnt, s16 *data, u16 points, u8 ch)
{
    while (points--) {
        if (*s_cnt >= 48) {
            *s_cnt = 0;
        }
        *data++ = tsin_48k[*s_cnt];
        if (ch == 2) {
            *data++ = tsin_48k[*s_cnt];
        }
        (*s_cnt)++;
    }
    return 0;
}

void *data_u = NULL;
s16 data_e[720] = {};

static int usb_audio_mic_tx_handler(int event, void *data, int len)
{
    if (usb_mic_hdl == NULL) {
        return 0;
    }
    if (usb_mic_hdl->status == USB_MIC_STOP) {
        return 0;
    }
    int i = 0;
    int r_len = 0;
    u8 ch = 0;
    u8 double_read = 0;
    putchar('&');
    /* int rlen = 0; */

    if (usb_mic_hdl->mic_data_ok == 0) {
        if (usb_mic_hdl->output_cbuf.data_len > (PCM_ENC2USB_OUTBUF_LEN / 4) ) {
            usb_mic_hdl->mic_data_ok = 1;
        }
        //y_printf("mic_tx NULL\n");
        memset(data, 0, len);
        return len;
    }
    if(usb_mic_hdl->output_cbuf.data_len < len){
        //printf("KKKKKKKKKKKKKKKKKKKKKKKKKKK\n");
        // get_sine_data(&user_cnt,data_e,720,1);
        // cbuf_write(&usb_mic_hdl->output_cbuf, data_e, 720);
        //return len;
    }
    usb_mic_hdl->busy = 1;
    /* usb_audio_mic_sync(size); */
    if(usb_mic_hdl->rec_tx_channels == 2) {
        len = cbuf_read(&usb_mic_hdl->output_cbuf, data, len / 2);
        s16 *tx_pcm = (s16 *)data;
        int cnt = len / 2;
        for (cnt = len / 2; cnt >= 2;) {
            tx_pcm[cnt - 1] = tx_pcm[cnt / 2 - 1];
            tx_pcm[cnt - 2] = tx_pcm[cnt / 2 - 1];
            cnt -= 2;
        }
        len *= 2;
        //cbuf_read(&usb_mic_hdl->output_cbuf, tx_pcm, len / 2);
    } else {
        putchar('$');
        //memcpy
        len = cbuf_read(&usb_mic_hdl->output_cbuf, data, len);
        //memcpy(data,data_u,len);
        //get_sine_data(&user_cnt,data,len,1);
    }
    // putchar('r');
    usb_mic_hdl->busy = 0;
    return len;
}

int usb_audio_ext_mic_write(void *data, u16 len)
{
    int wlen = len;
    if (usb_mic_hdl) {
        wlen = cbuf_write(&usb_mic_hdl->output_cbuf, data, len);
#if 1
        static u32 usb_mic_data_max = 0;
        if (usb_mic_data_max < usb_mic_hdl->output_cbuf.data_len) {
            usb_mic_data_max = usb_mic_hdl->output_cbuf.data_len;
            printf("usb_mic_max:%d", usb_mic_data_max);
        }
#endif
        if (wlen != len) {
            printf("usb_mic write full:%d-%d\n", wlen, len);
        }
    }
    return wlen;
}

u32 usb_audio_ext_mic_get_size(void)
{
    if(usb_mic_hdl){
        return cbuf_get_data_size(&usb_mic_hdl->output_cbuf);
    }

    return 0;
}

u32 usb_audio_ext_mic_get_total(void)
{
    if(usb_mic_hdl){
        return usb_mic_hdl->output_cbuf.total_len;
    }

    return 0;
}
extern struct audio_dac_channel default_dac;
void src_output_handle(void *p, void *data, u32 len)
{
    if(data && len){
        // local_irq_disable();
        usb_audio_ext_mic_write(data, len);
        //audio_dac_write(&default_dac, data, len);
        // local_irq_enable();
    }
}

void *get_usb_mic_src_hdl(void)
{
    if(!usb_mic_hdl){
        return NULL;
    }
    return usb_mic_hdl->user_src;
}

extern u16 uac_get_mic_vol(const u8 usb_id);
extern int uac_vol_switch(int vol);
int usb_audio_mic_open_ext(void *_info)
{
    if (usb_mic_hdl) {
        return 0;
    }
    usb_mic_hdl = zalloc(sizeof(*usb_mic_hdl));
    if (!usb_mic_hdl) {
        return -EFAULT;
    }
    usb_mic_hdl->status = USB_MIC_STOP;

    usb_mic_hdl->output_buf = zalloc(PCM_ENC2USB_OUTBUF_LEN);
    if (!usb_mic_hdl->output_buf) {
        printf("usb_mic_hdl->output_buf NULL\n");

        if (usb_mic_hdl) {
            free(usb_mic_hdl);
            usb_mic_hdl = NULL;
        }
        return -EFAULT;
    }

    u32 sample_rate = (u32)_info & 0xFFFFFF;
    usb_mic_hdl->rec_tx_channels = (u32)_info >> 24;
    g_printf("usb_audio_mic_open_ext sr:%d ch:%d\n", sample_rate, usb_mic_hdl->rec_tx_channels);

    usb_mic_hdl->drop_data = 2; //用来丢掉前几帧数据
    cbuf_init(&usb_mic_hdl->output_cbuf, usb_mic_hdl->output_buf, PCM_ENC2USB_OUTBUF_LEN);
    extern u16 get_esco_audio_samplerate(void);
    struct USER_SRC_PRIV src_priv;
    src_priv.channel = usb_mic_hdl->rec_tx_channels;
    src_priv.in_sample_rate = get_esco_audio_samplerate();
    src_priv.out_sample_rate = sample_rate;
    src_priv.output_busy = get_usb_state;
    src_priv.data_size = usb_audio_ext_mic_get_size;
    src_priv.total_size = usb_audio_ext_mic_get_total;
    src_priv.output_handler = src_output_handle;
    usb_mic_hdl->user_src = user_resample_task_create(&src_priv);
    // user_resample_without_task_init(&src_priv);

    app_var.usb_mic_gain = uac_vol_switch(uac_get_mic_vol(0));

    set_uac_mic_tx_handler(NULL, usb_audio_mic_tx_handler);

    //iis_input_start(usb_mic_hdl->user_src, external_audio_input);

    usb_mic_hdl->status = USB_MIC_START;
    /* __this->rec_begin = 0; */
    return 0;
}



/*
 *************************************************************
 *
 *	usb mic gain save
 *
 *************************************************************
 */
static int usb_mic_gain_save_timer;
static u8  usb_mic_gain_save_cnt;
static void usb_audio_mic_gain_save_do(void *priv)
{
    //printf(" usb_audio_mic_gain_save_do %d\n", usb_mic_gain_save_cnt);
    local_irq_disable();
    if (++usb_mic_gain_save_cnt >= 5) {
        sys_hi_timer_del(usb_mic_gain_save_timer);
        usb_mic_gain_save_timer = 0;
        usb_mic_gain_save_cnt = 0;
        local_irq_enable();
        printf("USB_GAIN_SAVE\n");
        syscfg_write(VM_USB_MIC_GAIN, &app_var.usb_mic_gain, 1);
        return;
    }
    local_irq_enable();
}

static void usb_audio_mic_gain_change(u8 gain)
{
    local_irq_disable();
    app_var.usb_mic_gain = gain;
    usb_mic_gain_save_cnt = 0;
    if (usb_mic_gain_save_timer == 0) {
        usb_mic_gain_save_timer = sys_hi_timer_add(NULL, usb_audio_mic_gain_save_do, 1000);
    }
    local_irq_enable();
}

void usb_audio_mic_set_gain_ext(int gain)
{
    if (usb_mic_hdl == NULL) {
        r_printf("usb_mic_hdl NULL gain");
        return;
    }
    gain = uac_vol_switch(gain);
    usb_audio_mic_gain_change(gain);
}
int usb_audio_mic_close_ext(void *arg)
{
    if (usb_mic_hdl == NULL) {
        r_printf("usb_mic_hdl NULL close");
        return 0;
    }
    printf("usb_audio_mic_close_ext \nusb_mic_hdl->status %x\n", usb_mic_hdl->status);
    if (usb_mic_hdl && usb_mic_hdl->status == USB_MIC_START) {
        printf("usb_audio_mic_close in\n");
        usb_mic_hdl->status = USB_MIC_STOP;
        user_resample_task_kill(&usb_mic_hdl->user_src);
        // user_resample_without_task_uninit(&usb_mic_hdl->user_src);
        //iis_input_stop();
        printf("usb_mic_hdl->user_src 0x%x\n", usb_mic_hdl->user_src);
        cbuf_clear(&usb_mic_hdl->output_cbuf);
        if (usb_mic_hdl->output_buf) {
            free(usb_mic_hdl->output_buf);
            usb_mic_hdl->output_buf = NULL;
        }
        free(usb_mic_hdl);
        usb_mic_hdl = NULL;
    }
    printf("usb_audio_mic_close out\n");

    return 0;
}
