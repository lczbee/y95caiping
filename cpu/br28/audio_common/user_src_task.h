#ifndef __USER_SRC_TASK__
#define __USER_SRC_TASK__

/**
 * @brief 需要提供给变采样的参数
 * 
 */
struct USER_SRC_PRIV{
    u16 in_sample_rate;//原始数据的采样率
    u16 out_sample_rate;//需要输出的采样率
    u32 point_len;
    u8 channel;//数据的声道数
    u8 (*output_busy)(void);//输出buffer忙标志（当不能写输出buffer时返回1）
    u32 (*data_size)(void);//当前buffer的有效数据大小
    u32 (*total_size)(void);//buffer的总大小
    int (*output_handler)(void *parm, void *data, int len);//变采样之后的数据的输出回调
};

void *user_resample_task_create(void *priv);
void user_resample_task_kill(void **priv);
u32 output_to_src_task(void *priv, s16 *data, int len);
void user_resample_set_sr(void *p, u16 in, u16 out);
void *user_resample_without_task_init(void *priv);
void user_resample_without_task_uninit(void **priv);
void user_resample_without_task_deal(void *priv, void *buf, u32 len);
int external_audio_input(void *priv, s16 *data, u16 len);
extern int test_buf_len;
#endif
