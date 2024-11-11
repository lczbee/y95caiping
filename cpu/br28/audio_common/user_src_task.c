/**
 * @file user_src_task.c
 * @author FSW
 * @brief 软件变采样，带task和不带task两种（升采样建议用task，降采样不用task）
 * @version 0.1
 * @date 2021-02-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "asm/includes.h"
#include "media/includes.h"
#include "system/includes.h"
#include "app_config.h"
#include "app_task.h"
#include "application/audio_energy_detect.h"
#include "user_src_task.h"

#define SRC_TYPE_SW   (0)
#define SRC_TYPE_HW   (1)//暂时不能用
#define SRC_TYPE      SRC_TYPE_SW
#define BUF_SYNC      (1)//采样同步，避免因时钟差异导致丢数据卡顿

struct USER_SYNC {
    int total_len;		// buf总长度
    int begin_per;		// 起始百分比
    int top_per;		// 最大百分比
    int bottom_per;		// 最小百分比
    int total_per;		// 总百分比
    u16 in_sr;
    u16 out_sr;			// 输出采样率
    u16 nor_sr;			// 中心采样率
    u8 inc_step;		// 每次调整增加步伐
    u8 dec_step;		// 每次调整减少步伐
    u8 max_step;		// 最大调整步伐
};

#if (SRC_TYPE == SRC_TYPE_SW)
#include "Resample_api.h"
#endif
struct TASK_PRIV {
    struct USER_SRC_PRIV src_priv;
    struct USER_SYNC sync;
    struct audio_src_handle *hw_src;
#if (SRC_TYPE == SRC_TYPE_SW)
    RS_STUCT_API *sw_src_api;
    u8 *sw_src_buf;
    s16 sw_src_output[320 * 3 + 16];
#endif
    OS_SEM sem;
    OS_MUTEX mutex;
    int data_buf_len;
    s16 *data_buf;
    u8 without_task : 1;//不带task为1，带task为0
    volatile u8 busy : 1;
    volatile u8	release : 1;
};

static struct TASK_PRIV *__this = NULL;


static u8 cnt0 = 0;
static u8 cnt1 = 0;
static u8 cnt2 = 0;
static void *mix_out_automute_hdl = NULL;
extern u8 get_usb_state(void);
extern u32 usb_audio_ext_mic_get_size(void);
extern u32 usb_audio_ext_mic_get_total(void);
int test_buf_len = 2500;
/**
 * @brief 硬件变采样处理，暂不可用
 *
 * @param task
 * @return int
 */
static int user_src_task_deal_hw(struct TASK_PRIV *task)
{
    if (!task) {
        return -1;
    }

    if(task->without_task){
        goto __DEAL;
    }

    int res = os_sem_pend(&task->sem, 0);
    if (res) {
        return -1;
    }

__DEAL:
    if (task->release) {
        return -1;
    }

    u8 *buf_ptr = task->data_buf;
    u32 input_len = task->data_buf_len;
    u32 remain_len = input_len;
    while(task->src_priv.output_busy && task->src_priv.output_busy());
    if(task->without_task == 0){
        os_mutex_pend(&task->mutex, 0);
    }
#if BUF_SYNC
    if(task->src_priv.data_size() > (task->src_priv.total_size() * task->sync.top_per / task->sync.total_per))
    {
        task->sync.out_sr = (task->sync.out_sr - task->sync.dec_step) > (task->sync.nor_sr - task->sync.max_step) ?
                            (task->sync.out_sr - task->sync.dec_step) : (task->sync.nor_sr - task->sync.max_step);
        audio_hw_src_set_rate(task->hw_src, task->src_priv.in_sample_rate, task->sync.out_sr);
        cnt0++;
        if(cnt0 == 50){
            cnt0 = 0;
            putchar('-');
            putchar('+');
            // printf("%d\n", task->sync.out_sr);
        }
    }
    else if(task->src_priv.data_size() < (task->src_priv.total_size() * task->sync.bottom_per / task->sync.total_per))
    {
        task->sync.out_sr = (task->sync.out_sr + task->sync.inc_step) < (task->sync.nor_sr + task->sync.max_step) ?
                            (task->sync.out_sr + task->sync.inc_step) : (task->sync.nor_sr + task->sync.max_step);
        audio_hw_src_set_rate(task->hw_src, task->src_priv.in_sample_rate, task->sync.out_sr);
        cnt1++;
        if(cnt1 == 50){
            cnt1 = 0;
            putchar('+');
            // printf("%d\n", task->sync.out_sr);
        }
    }
    else{
        if(task->sync.out_sr > task->sync.nor_sr){
            task->sync.out_sr = (task->sync.out_sr - task->sync.dec_step/2) > task->sync.nor_sr ?
                                (task->sync.out_sr - task->sync.dec_step/2) : task->sync.nor_sr;
            audio_hw_src_set_rate(task->hw_src, task->src_priv.in_sample_rate, task->sync.out_sr);
        }
        else if(task->sync.out_sr < task->sync.nor_sr){
            task->sync.out_sr = (task->sync.out_sr + task->sync.inc_step/2) < task->sync.nor_sr ?
                                (task->sync.out_sr + task->sync.inc_step/2) : task->sync.nor_sr;
            audio_hw_src_set_rate(task->hw_src, task->src_priv.in_sample_rate, task->sync.out_sr);
        }
        cnt2++;
        if(cnt2 == 50){
            cnt2 = 0;
            putchar('n');
            // printf(":%d\n", task->sync.out_sr);
        }
    }
#endif
    if(remain_len && task->data_buf_len && buf_ptr){
        remain_len = input_len - audio_src_resample_write(task->hw_src, buf_ptr, input_len);
        buf_ptr += input_len - remain_len;
        input_len = remain_len;
        // putchar('d');
    }
    task->data_buf_len = 0;
    if(task->without_task == 0){
        os_mutex_post(&task->mutex);
    }
    return 0;
}

/**
 * @brief 软件变采样处理流程
 *
 * @param task
 * @return int
 */
static int  user_src_task_deal_sw(struct TASK_PRIV *task)
{
    if (!task) {
        return -1;
    }

    if(task->without_task){
        goto __DEAL;
    }

    int res = os_sem_pend(&task->sem, 0);
    if (res) {
        return -1;
    }

__DEAL:
    if (task->release) {
        return -1;
    }

    u8 *buf_ptr = task->data_buf;
    u32 input_len = task->data_buf_len;
    u32 point = input_len >> 1;

    if(task->data_buf_len == 0){
        return 0;
    }

    while(task->src_priv.output_busy && task->src_priv.output_busy());

#if (SRC_TYPE == SRC_TYPE_SW)
    if(task->without_task == 0){
        os_mutex_pend(&task->mutex, 0);
    }
#if BUF_SYNC
    if (task->sw_src_api && task->sw_src_buf && task->src_priv.data_size && task->src_priv.total_size) {
       /* if(test_buf_len > 3 * 1024){
            task->sync.in_sr += 10;
            putchar('+');
            r_printf("task->sync.in_sr += %d\n",task->sync.in_sr);
        }
        else if(test_buf_len < 1 * 1024){
            task->sync.in_sr = 10000;
            putchar('-');
            r_printf("task->sync.in_sr -= %d\n",task->sync.in_sr);           
        }
        else if(test_buf_len < 2 * 1024){
            task->sync.in_sr -= 10;
            putchar('-');
            r_printf("task->sync.in_sr -= %d\n",task->sync.in_sr);
        }
        else{

        }
        task->sw_src_api->set_sr(task->sw_src_buf, task->sync.in_sr);*/
        if(task->src_priv.data_size() < (task->src_priv.total_size() * task->sync.bottom_per / task->sync.total_per))
        {
            task->sync.in_sr = (task->sync.in_sr - task->sync.dec_step) > (task->sync.nor_sr - task->sync.max_step) ?
                                (task->sync.in_sr - task->sync.dec_step) : (task->sync.nor_sr - task->sync.max_step);
            task->sw_src_api->set_sr(task->sw_src_buf, task->sync.in_sr);
            cnt0++;
            if(cnt0 == 50){
                cnt0 = 0;
                putchar('-');
                // printf("%d\n", task->sync.out_sr);
            }
        }
        else if(task->src_priv.data_size() > (task->src_priv.total_size() * task->sync.top_per / task->sync.total_per))
        {
            task->sync.in_sr = (task->sync.in_sr + task->sync.inc_step) < (task->sync.nor_sr + task->sync.max_step) ? 
                                (task->sync.in_sr + task->sync.inc_step) : (task->sync.nor_sr + task->sync.max_step);
            task->sw_src_api->set_sr(task->sw_src_buf, task->sync.in_sr);
            cnt1++;
            if(cnt1 == 50){
                cnt1 = 0;
                putchar('+');
                //y_printf("%d+++++++\n", task->sync.in_sr);
            }
        }
        else{
            if(task->sync.in_sr > task->sync.nor_sr){
                task->sync.in_sr = (task->sync.in_sr - task->sync.dec_step/2) > task->sync.nor_sr ?
                                    (task->sync.in_sr - task->sync.dec_step/2) : task->sync.nor_sr;
                task->sw_src_api->set_sr(task->sw_src_buf, task->sync.in_sr);
            }
            else if(task->sync.in_sr < task->sync.nor_sr){
                task->sync.in_sr = (task->sync.in_sr + task->sync.inc_step/2) < task->sync.nor_sr ?
                                    (task->sync.in_sr + task->sync.inc_step/2) : task->sync.nor_sr;
                task->sw_src_api->set_sr(task->sw_src_buf, task->sync.in_sr);
            }
            cnt2++;
            if(cnt2 == 50){
                cnt2 = 0;
                putchar('n');
                //y_printf(":%dnnnnnnnnnnnnnnn\n", task->sync.in_sr);
            }
        }
    }
#endif
    if (task->sw_src_api && task->sw_src_buf) {
        input_len = task->sw_src_api->run(task->sw_src_buf, buf_ptr, point, task->sw_src_output);
        ASSERT(input_len <= (sizeof(task->sw_src_output) >> 1));
        //printf("16->48k:%d,%d,%d\n",len >> 1,outlen,sizeof(sw_src_output));
        input_len = input_len << 1;
        buf_ptr = task->sw_src_output;
    }
    if(task->without_task == 0){
        os_mutex_post(&task->mutex);
    }
    if(!input_len){
        return 0;
    }
#endif

    task->src_priv.output_handler(NULL, buf_ptr, input_len);
    task->data_buf_len = 0;
    return 0;
}

/**
 * @brief 唤醒task，一般用在获取到数据之后，唤醒task做变采样
 *
 * @param priv
 */
void src_task_resume(void *priv)
{
    struct TASK_PRIV *task = (struct TASK_PRIV *)priv;
    if (task != NULL && (task->release == 0)) {
        os_sem_set(&task->sem, 0);
        os_sem_post(&task->sem);
    }
}

static u8 cnt = 0;
u32 output_to_src_task(void *priv, s16 *data, int len)
{
    struct TASK_PRIV *task = (struct TASK_PRIV *)priv;
    u32 energy = 1;
    if(mix_out_automute_hdl){
        audio_energy_detect_run(mix_out_automute_hdl, data, len);
        energy = audio_energy_detect_energy_get(mix_out_automute_hdl, BIT(0));//有需要的可以在这里获取输入音频的能量
    }

//    cnt++;
//    if(cnt == 250){
//        printf("%d\n", energy);
//        cnt = 0;
//    }

    if(task == NULL || task->release || energy == 0){
        return 0;
    }

    if (task->without_task == 0) { //目前是带task 的变采样，到task中处理
        task->data_buf = data;
        task->data_buf_len = len;
        os_sem_set(&task->sem, 0);
        os_sem_post(&task->sem);
        //putchar('n');
    }
    else{ //目前是不带task 的变采样，直接处理
        //putchar('m');
        user_resample_without_task_deal(task, data, len);
    }
    return len;
}

/**
 * @brief 收到外部的音频数据之后，调用这个函数，把数据丢给变采样处理
 *
 * @param data
 * @param len
 * @return int
 */
int external_audio_input(void *priv, s16 *data, u16 len)
{
    int outlen = len;
    s16 *outdat = data;
    int i;
    int mono_point = len >> 2;
    struct TASK_PRIV *task = (struct TASK_PRIV *)priv;

    if(!task){
        return 0;
    }
    //立体声-->单声道
    for(i = 0; i < mono_point; i++){
        outdat[i] = outdat[2*i];
    }
    outlen = mono_point << 1;

    return output_to_src_task(task, outdat, outlen);
}

void automute_event_handler(u8 event, u8 channel)
{
    printf(">>>> ch:%d %s\n", channel, event ? ("MUTE") : ("UNMUTE"));
}

#if (SRC_TYPE == SRC_TYPE_SW)
u32 sw_src_need_buf;

/**
 * @brief 软件变采样初始化
 *
 * @param in_sr
 * @param out_sr
 * @return int
 */
static int sw_src_init(void *p, u16 in_sr, u16 out_sr)
{
    struct TASK_PRIV *task = (struct TASK_PRIV *)p;
    printf("sw_src_init %d --> %d\n", in_sr, out_sr);
    task->sw_src_api = get_rs16_context();
    // sw_src_api = get_rsfast_context();
    g_printf("sw_src_api:0x%x\n", task->sw_src_api);
    ASSERT(task->sw_src_api);
    sw_src_need_buf = task->sw_src_api->need_buf();
    printf("sw_src_buf:%d\n", sw_src_need_buf);
    task->sw_src_buf = malloc(sw_src_need_buf);
    ASSERT(task->sw_src_buf);
    RS_PARA_STRUCT rs_para_obj;
    rs_para_obj.nch = 1;

    rs_para_obj.new_insample = in_sr;
    rs_para_obj.new_outsample = out_sr;
    printf("sw src,in = %d,out = %d\n", rs_para_obj.new_insample, rs_para_obj.new_outsample);
    r_f_printf("sw_src_init 0x%x, 0x%x, 0x%x\n", task, task->sw_src_buf, task->sw_src_api);
    task->sw_src_api->open(task->sw_src_buf, &rs_para_obj);
    return 0;
}

static int sw_src_close(void *p)
{
    struct TASK_PRIV *task = (struct TASK_PRIV *)p;
    if(task && task->sw_src_buf){
        g_f_printf("sw_src_close 0x%x, 0x%x, 0x%x\n", task, task->sw_src_buf, task->sw_src_api);
        free(task->sw_src_buf);
        task->sw_src_buf = NULL;
        task->sw_src_api = NULL;
    }
    return 0;
}
#endif

/**
 * @brief 带task的变采样才会跑这个task
 *
 * @param p
 */
static void user_src_task(void *p)
{
    struct TASK_PRIV *task = (struct TASK_PRIV *)p;
    struct USER_SRC_PRIV *src_p = &task->src_priv;
    int ret = 0;
    int msg[16];

    ASSERT(task, "task err\n");

    audio_energy_detect_param e_det_param = {0};
    e_det_param.mute_energy = 5;
    e_det_param.unmute_energy = 10;
    e_det_param.mute_time_ms = 1000;
    e_det_param.unmute_time_ms = 50;
    e_det_param.count_cycle_ms = 10;
    e_det_param.sample_rate = src_p->in_sample_rate;
    e_det_param.event_handler = automute_event_handler;
    e_det_param.ch_total = src_p->channel;
    e_det_param.dcc = 1;
    // mix_out_automute_hdl = audio_energy_detect_open(&e_det_param);//可以检测能量

#if (SRC_TYPE == SRC_TYPE_SW)
    sw_src_init(task, src_p->in_sample_rate, src_p->out_sample_rate);
#else
    struct audio_src_handle *hw_src;
    hw_src = zalloc(sizeof(struct audio_src_handle));
    ASSERT(hw_src, "user_src_task hw_src zalloc err\n");

    audio_hw_src_open(hw_src, src_p->channel, SRC_TYPE_RESAMPLE);
    audio_hw_src_set_rate(hw_src, src_p->in_sample_rate, src_p->out_sample_rate);
    printf("user_src_task:%d -> %d\n", src_p->in_sample_rate, src_p->out_sample_rate);
    audio_src_set_output_handler(hw_src, NULL, src_p->output_handler);
    task->hw_src = hw_src;
#endif
    task->busy = 1;
    while(1)
    {
#if (SRC_TYPE == SRC_TYPE_SW)
        ret = user_src_task_deal_sw(task);
#else
        ret = user_src_task_deal_hw(task);
#endif
        if (ret) {
            ///等待删除线程
            if (mix_out_automute_hdl) {
                audio_energy_detect_close(mix_out_automute_hdl);
                mix_out_automute_hdl = NULL;
            }
#if (SRC_TYPE == SRC_TYPE_SW)
            sw_src_close(task);
#else
            if (task->hw_src) {
                audio_hw_src_stop(task->hw_src);
                audio_hw_src_close(task->hw_src);
                free(task->hw_src);
                task->hw_src = NULL;
            }
#endif
            task->busy = 0;
            while (1) {
                os_time_dly(10000);
            }
        }
    }
}

#define SIZEOF_ALIN(var,al)     ((((var)+(al)-1)/(al))*(al))
/**
 * @brief 带task 的变采样的初始化
 *
 * @param priv struct USER_SRC_PRIV 类型的参数
 * @return void*
 */
void *user_resample_task_create(void *priv)
{
    if(!priv){
        return NULL;
    }
    if(__this){
        return NULL;
    }
    int err;
    u32 buf_size = SIZEOF_ALIN(sizeof(struct TASK_PRIV), 4);
    u8 *buf = zalloc(buf_size);
    struct TASK_PRIV *src_task = (struct TASK_PRIV *)buf;
    ASSERT(src_task, "user_resample_task_create src_task zalloc err\n");
    os_mutex_create(&src_task->mutex);
    os_sem_create(&src_task->sem, 0);
    os_mutex_post(&src_task->mutex);
    memcpy(&src_task->src_priv, priv, sizeof(src_task->src_priv));
#if BUF_SYNC
    src_task->sync.begin_per = 5;
    src_task->sync.bottom_per = 5;
    src_task->sync.top_per = 8;
    src_task->sync.total_per = 10;
    src_task->sync.inc_step = 5;
    src_task->sync.dec_step = 5;
    src_task->sync.max_step = 100;//跟要调节的采样率成正比
#if (SRC_TYPE == SRC_TYPE_SW)
    src_task->sync.in_sr = src_task->src_priv.in_sample_rate;
    src_task->sync.nor_sr = src_task->src_priv.in_sample_rate;
#else
    src_task->sync.nor_sr = src_task->src_priv.out_sample_rate;
#endif
    src_task->sync.out_sr = src_task->src_priv.out_sample_rate;
#endif
    err = task_create(user_src_task, src_task, "src_task");
    if (err != OS_NO_ERR) {
        printf("%s creat fail %x\n", __FUNCTION__,  err);
        free(src_task);
        return NULL;
    }
    // mem_stats();
    src_task->without_task = 0;
    printf("%s creat succ\n", __FUNCTION__);
    __this = src_task;
    return src_task;
}

void user_resample_task_kill(void **priv)
{
    if(priv == NULL){
        priv = &__this;
    }
    if(!priv || !(*priv)){
        return;
    }
    struct TASK_PRIV *task = *(struct TASK_PRIV **)priv;
    if(task->without_task){
        return;
    }
    task->release = 1;
    os_sem_set(&task->sem, 0);
    os_sem_post(&task->sem);
    os_mutex_post(&task->mutex);
    while (task->busy) {
        os_time_dly(5);
    }
    int err = task_kill("src_task");
    if (!err) {
        printf("user_resample_task_kill succ!!\n");
    } else {
        printf("user_resample_task_kill fail!!\n");
    }
    os_sem_del(&task->sem, 0);
    os_mutex_del(&task->mutex, 0);
    local_irq_disable();
    free(*priv);
    *priv = NULL;
    __this = NULL;
    local_irq_enable();
}

void user_resample_set_sr(void *priv, u16 in, u16 out)
{
    struct TASK_PRIV *task = (struct TASK_PRIV *)priv;
    if(!task){
        return;
    }
    if(task->without_task == 0){
        os_mutex_pend(&task->mutex, 0);
    }
#if (SRC_TYPE == SRC_TYPE_SW)
    if(in){
        task->src_priv.in_sample_rate = in;
        task->sync.in_sr = in;
        task->sync.nor_sr = in;
    }
    if(out){
        task->src_priv.out_sample_rate = out;
        task->sync.out_sr = out;
    }
    g_printf("user_resample_set_sr\n");
#else
    if(task->hw_src){
        task->src_priv.in_sample_rate = in;
        task->src_priv.out_sample_rate = out;
        audio_hw_src_set_rate(task->hw_src, in, out);
    }
#endif
    if(task->without_task == 0){
        os_mutex_post(&task->mutex);
    }
}

/**
 * @brief 不带task 的变采样的初始化
 *
 * @param priv struct USER_SRC_PRIV 类型的参数
 * @return void*
 */
void *user_resample_without_task_init(void *priv)
{
    if(!priv){
        return NULL;
    }
    int err;
    u32 buf_size = SIZEOF_ALIN(sizeof(struct TASK_PRIV), 4);
    u8 *buf = zalloc(buf_size);
    struct TASK_PRIV *src_task = (struct TASK_PRIV *)buf;
    ASSERT(src_task, "user_resample_task_create src_task zalloc err\n");
    memcpy(&src_task->src_priv, priv, sizeof(src_task->src_priv));
#if BUF_SYNC
    src_task->sync.begin_per = 5;
    src_task->sync.bottom_per = 5;
    src_task->sync.top_per = 8;
    src_task->sync.total_per = 10;
    src_task->sync.inc_step = 5;
    src_task->sync.dec_step = 5;
    src_task->sync.max_step = 100;//跟要调节的采样率成正比
#if (SRC_TYPE == SRC_TYPE_SW)
    src_task->sync.in_sr = src_task->src_priv.in_sample_rate;
    src_task->sync.nor_sr = src_task->src_priv.in_sample_rate;
#else
    src_task->sync.nor_sr = src_task->src_priv.out_sample_rate;
#endif
    src_task->sync.out_sr = src_task->src_priv.out_sample_rate;
#endif
    struct USER_SRC_PRIV *src_p = &src_task->src_priv;
#if (SRC_TYPE == SRC_TYPE_SW)
    //sw_src_init(src_task, 8000, src_p->out_sample_rate);
    sw_src_init(src_task, src_p->in_sample_rate, src_p->out_sample_rate);
#else
    struct audio_src_handle *hw_src;
    hw_src = zalloc(sizeof(struct audio_src_handle));
    ASSERT(hw_src, "user_src_task hw_src zalloc err\n");

    audio_hw_src_open(hw_src, src_p->channel, SRC_TYPE_RESAMPLE);
    audio_hw_src_set_rate(hw_src, src_p->in_sample_rate, src_p->out_sample_rate);
    printf("user_src_task:%d -> %d\n", src_p->in_sample_rate, src_p->out_sample_rate);
    audio_src_set_output_handler(hw_src, NULL, src_p->output_handler);
    src_task->hw_src = hw_src;
#endif
    src_task->without_task = 1;
    // mem_stats();
    printf("%s succ\n", __FUNCTION__);
    return src_task;
}

void user_resample_without_task_uninit(void **priv)
{
    struct TASK_PRIV *task = *(struct TASK_PRIV **)priv;
    if(!task || task->without_task == 0){
        return;
    }
    task->release = 1;
#if (SRC_TYPE == SRC_TYPE_SW)
    sw_src_close(task);
#else
    if (task->hw_src) {
        audio_hw_src_stop(task->hw_src);
        audio_hw_src_close(task->hw_src);
        free(task->hw_src);
        task->hw_src = NULL;
    }
#endif
    local_irq_disable();
    free(*priv);
    *priv = NULL;
    local_irq_enable();
    printf("%s succ\n", __FUNCTION__);
}

void user_resample_without_task_deal(void *priv, void *buf, u32 len)
{
    struct TASK_PRIV *task = (struct TASK_PRIV *)priv;
    if(!task || task->without_task == 0){
        return;
    }
    task->data_buf = buf;
    task->data_buf_len = len;
#if (SRC_TYPE == SRC_TYPE_SW)
    //putchar('%');
    user_src_task_deal_sw(task);
#else
    user_src_task_deal_hw(task);
#endif
}
