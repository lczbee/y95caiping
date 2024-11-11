#include "uart_test.h"
#include "smartbox_user_app.h"


#define LOG_TAG     		"[UART-JL]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


// 串口框架


// 串口命令类型

// 按键事件类型



static int tx_ack_timer = 0;
static int check_uart_insleep =0;
static uart_packet_t *uart_rxbuf;
static uart_packet_t *uart_txbuf;
static uart_packet_t *uart_temp_buf;
extern u8 test_remoter_addr[6];

OS_SEM uart_sem;

struct uart_frame
{
    u16 crc;
    u16 length;
    u8 data[0];
};


#define UART_FRAME_LEM (15)

static u8 uart_cbuf[32] __attribute__((aligned(4)));

bool int_into_read_uart =1;

struct uart_frame frame;
int r=0;
static void uart_irq_func(int uart_num, enum uart_event_v1 event)
{
    if(event & UART_EVENT_TX_DONE){
        // printf("UART_EVENT_TX_DONE");
         
    }

    if(event & UART_EVENT_RX_DATA){
        // printf("UART_EVENT_RX_DATA");
      
    }

    if(event & UART_EVENT_RX_FIFO_OVF){
        // printf("UART_EVENT_RX_FIFO_OVF");
        // os_sem_post(&uart_sem);
    }
     if(event & UART_EVENT_RX_TIMEOUT){
        // printf("UART_EVENT_RX_TIMEOUT");
        // os_sem_post(&uart_sem);
    }
    if(event & UART_EVENT_TX_DONE){
        // printf("UART_EVENT_TX_DONE");
    }
}
extern u8 uart_into_new_sleep;
int uart_receive_data_timer=0;
void user_check_into_sleep(void)
{
    y_printf("user_check_into_sleep\n");
    uart_receive_data_timer=0;
    int_into_read_uart=0;
    uart_into_new_sleep=1;
}

void uart_ack_timeout_cb()
{
    static u8 ack_timeout_cnt = 0;

    log_info("uart ack timeout!!!!\n");

    ack_timeout_cnt++;
    if(ack_timeout_cnt > 3){
        log_info("ack_timeout_cnt > MAX !!!!\n");
        ack_timeout_cnt = 0;
        return;
    }

   uart_send_blocking(1,uart_temp_buf, JBL_UART_FRAME_LEN,20);
    log_info("tx_data[%d]:\n", JBL_UART_FRAME_LEN);
    put_buf(uart_temp_buf, JBL_UART_FRAME_LEN);
    // jbl_uart_sleep=1;
}

void sbox_uart_tx_task(void)
{
    log_info(">>>>>>>>jbl_uart_tx_task");
    uart_txbuf = (uart_packet_t *)malloc(JBL_UART_FRAME_LEN);
    uart_temp_buf = (uart_packet_t *)malloc(JBL_UART_FRAME_LEN);

    int msg[32];
    int ret;

    while (1){
        putchar('t');
        ret = os_taskq_pend(NULL, msg, ARRAY_SIZE(msg));
        if (ret != OS_TASKQ) {
            continue;
        }

        if (msg[0] != Q_MSG) {
            continue;
        }
        //  串口发送
        if (msg[1] == UT_TX) {  
            memset(uart_txbuf, 0, JBL_UART_FRAME_LEN);
            switch (msg[2]) {
                case UART_CMD_CHARGING:
                log_info("UART_CMD_SCREEN\n");
                    uart_txbuf->magic_1 = UART_MAGIC_NUM_1;
                    uart_txbuf->magic_2 = UART_MAGIC_NUM_2;
                    uart_txbuf->type = UART_CMD_CHARGING;
                    uart_txbuf->direct = TO_982;
                    uart_txbuf->length = 0X01;
                    uart_txbuf->payload[0] = msg[3];
                    break;
                case UART_CMD_MAC:
                    log_info("UART_CMD_MAC\n");
                    uart_txbuf->magic_1 = UART_MAGIC_NUM_1;
                    uart_txbuf->magic_2 = UART_MAGIC_NUM_2;
                    uart_txbuf->type = UART_USER_ADD;
                    uart_txbuf->direct = TO_982;
                    uart_txbuf->length = 0X01;
                    uart_txbuf->payload[0] = 0xac;//msg[3];
                    break;
                case CMD_PRODUCT_MODE:
                    log_info("CMD_PRODUCT_MODE\n");
                    uart_txbuf->magic_1 = UART_MAGIC_NUM_1;
                    uart_txbuf->magic_2 = UART_MAGIC_NUM_2;
                    uart_txbuf->type = CMD_PRODUCT_MODE;
                    uart_txbuf->direct = TO_982;
                    uart_txbuf->length = 0X01;
                    uart_txbuf->payload[0] = 0x01;//msg[3];
                    break;
                default:
                    break;
            }
            //备份
            memset(uart_temp_buf, 0, JBL_UART_FRAME_LEN);
            memcpy(uart_temp_buf, uart_txbuf, JBL_UART_FRAME_LEN);
            uart_send_blocking(1, uart_txbuf, JBL_UART_FRAME_LEN, 1);
            printf("tx_data[%d]:\n", JBL_UART_FRAME_LEN);
            put_buf(uart_txbuf, JBL_UART_FRAME_LEN);
            if(tx_ack_timer){
                sys_timeout_del(tx_ack_timer);
                tx_ack_timer=0;
            }
            tx_ack_timer = sys_timeout_add(NULL, uart_ack_timeout_cb, 200);
        }
    }
    // jbl_uart_sleep=1;
}




int lasttime = 0;//jiffies_msec();
void uart_active(){
    os_sem_post(&uart_sem);
    lasttime = jiffies_msec();
}

extern void vbat_voltage_array_f98_init(void);
extern void vbat_voltage_array_f98_uninit(void);
extern void f98_vbat_to_array(u16 vbat_f98);
// extern u32 adc_get_value_f98(void);
bool get_vbat_value_from_f98 = 0;

int get_vbat_a_from_f98 = 0;
void sbox_uart_rx_task(void *p)
{
    struct uart_config config =
        {
            .baud_rate = UART_BAUD_RATE_982,
            .tx_pin = UART_TX_982,
            .rx_pin = UART_RX_982,
            .parity = UART_PARITY_DISABLE,
        };
    // void *uart_rx_ptr = dma_malloc(768);
    void *uart_rx_ptr = dma_malloc(64);
    struct uart_dma_config dma = {
        .rx_timeout_thresh = 100,   //单位：us
        .frame_size = UART_FRAME_LEM,
        .event_mask = UART_EVENT_TX_DONE | UART_EVENT_RX_DATA | UART_EVENT_RX_FIFO_OVF | UART_EVENT_RX_TIMEOUT | UART_EVENT_TX_DONE,
        .irq_callback = uart_irq_func,
        .rx_cbuffer = uart_rx_ptr,
        .rx_cbuffer_size = 64,
    };
    int r = uart_init_new(1, &config);
    if(r < 0){
        printf("init error %d", r);
    }
    uart_dma_init(1, &dma);
    uart_dump();
    printf("uart init ok\n");
    
    extern user_check_into_scan(void);
    extern u8 custom_remote_addr[6];
    struct uart_frame *frame = (struct uart_frame *)malloc(UART_FRAME_LEM);

    os_sem_create(&uart_sem, 0);
    uart_rxbuf = (uart_packet_t *)malloc(JBL_UART_FRAME_LEN);
    uart_txbuf = (uart_packet_t *)malloc(JBL_UART_FRAME_LEN);
    u8 cnt = 0;
    s32 ret = 0;
    u8 rxbuf[64] = {0};
    int checksum;
    int msg[2]={0};
    uart_active();
    os_sem_post(&uart_sem);
    while (1){
        os_time_dly(1);
        os_sem_pend(&uart_sem, 0);

        if(jiffies_msec()- lasttime < 300){
            // g_printf("noon active %s %d", __func__, __LINE__);
            // os_sem_post(&uart_sem);

            os_sem_post(&uart_sem);
        }else{
            // g_printf("set 1 active %s %d", __func__, __LINE__);
            uart_into_new_sleep=1;
        }
        // putchar('r');
        ret = uart_recv_bytes(1,rxbuf,64);
        // r_printf("uart_recv_bytes : %d", ret);
        int index = 0;
        while(ret>0){
            u8 rx = rxbuf[index];
            index++;
            ret--;

            if (1) {
            // log_info("get_byte: %02x\n", rx);
            uart_active();
            switch (cnt) {
                case BYTE_MAGIC_1:
                    if(rx != UART_MAGIC_NUM_1){
                        cnt = 0;
                        break;
                    }
                    uart_rxbuf->magic_1 = rx;
                    cnt++;
                    break;
                case BYTE_MAGIC_2:
                    if(rx != UART_MAGIC_NUM_2){
                        cnt = 0;
                        break;
                    }
                    uart_rxbuf->magic_2 = rx;
                    cnt++;
                    break;
                case BYTE_TYPE:
                    uart_rxbuf->type = rx ;
                    cnt++;
                    break;
                case BYTE_DIRECT:
                    uart_rxbuf->direct = rx;
                    cnt++;
                    break;
                case BYTE_LENGTH:
                    uart_rxbuf->length = rx;
                    cnt++;
                    break;
                case BYTE_PAYLOAD_0:
                    uart_rxbuf->payload[0] = rx;
                    cnt++;
                    break;
                case BYTE_PAYLOAD_1:
                    uart_rxbuf->payload[1] = rx;
                    cnt++;
                    break;
                case BYTE_PAYLOAD_2:
                    uart_rxbuf->payload[2] = rx;
                    cnt++;
                    break;
                case BYTE_PAYLOAD_3:
                    uart_rxbuf->payload[3] = rx;
                    cnt++;
                    break;
                case BYTE_PAYLOAD_4:
                    uart_rxbuf->payload[4] = rx;
                    cnt++;
                    break;
                case BYTE_PAYLOAD_5:
                    uart_rxbuf->payload[5] = rx;
                    cnt = 0;
                    // printf("uart_rxbuf->magic_1:%x", uart_rxbuf->magic_1);
                    // printf("uart_rxbuf->magic_2:%x", uart_rxbuf->magic_1);
                    // printf("uart_rxbuf->type:%x", uart_rxbuf->type);
                    // printf("uart_rxbuf->direct:%x", uart_rxbuf->direct);
                    // printf("uart_rxbuf->length:%x",uart_rxbuf->length );
                    // printf("uart_rxbuf->payload[0]:%x", uart_rxbuf->payload[0]);
                    // printf("uart_rxbuf->payload[1]:%x", uart_rxbuf->payload[1]);
                    // printf("uart_rxbuf->payload[2]:%x", uart_rxbuf->payload[2]);
                    // printf("uart_rxbuf->payload[3]:%x", uart_rxbuf->payload[3]);
                    // printf("uart_rxbuf->payload[4]:%x", uart_rxbuf->payload[4]);
                    // printf("uart_rxbuf->payload[5]:%x", uart_rxbuf->payload[5]);

                    // 校验
                    if(uart_rxbuf->magic_1 != UART_MAGIC_NUM_1 || uart_rxbuf->magic_2 != UART_MAGIC_NUM_2){
                        log_info("magic incorrect :%x %x!\n", uart_rxbuf->magic_1, uart_rxbuf->magic_2);
                        continue;
                    }
                        for(int u_check=0;u_check<6;u_check++){
                            
                            checksum+=uart_rxbuf->payload[u_check];
                            // y_printf("%d\n",checksum);
                        }
                        u8 checksums = (checksum & 0xff);
                    // 过滤
                    if(uart_rxbuf->direct != TO_7012){
                        log_info("direct incorrect :%x!\n", uart_rxbuf->direct);
                        continue;
                    }
                    // 应答过滤
                    if(uart_rxbuf->length == 0x00){
                        // log_info("ack correct0!\n");
                        if(tx_ack_timer){
                            sys_timeout_del(tx_ack_timer);
                            tx_ack_timer=0;
                        }
                        continue;
                    }
                    // 传递
                    switch (uart_rxbuf->type) {
                        // 自行处理
                        case UART_CMD_HALL:     //舱门状态
                            r_printf("UART_CMD_HALL : %x\n", uart_rxbuf->payload[4]);
                            // log_info("UART_CMD_CHARGING : %x\n", uart_rxbuf->payload[0]);
                            // log_info("UART_CMD_CHARGING : %x\n", uart_rxbuf->payload[1]);
                            // log_info("UART_CMD_CHARGING : %x\n", uart_rxbuf->payload[2]);
                            // log_info("UART_CMD_CHARGING : %x\n", uart_rxbuf->payload[3]);
                            if(get_vbat_value_from_f98 != (uart_rxbuf->payload[3] & BIT(2)?1:0)){
                                if(!get_vbat_value_from_f98) {
                                    get_vbat_value_from_f98 = 1;
                                    vbat_voltage_array_f98_init();
                                } else {
                                    get_vbat_value_from_f98 = 0;
                                    vbat_voltage_array_f98_uninit();
                                }
                            }
                            if(uart_rxbuf->payload[1]<=100 && uart_rxbuf->payload[1]>=0){
                                 box_info.l_ear_bat=uart_rxbuf->payload[1];
                            }
                            if(uart_rxbuf->payload[2]<=100 && uart_rxbuf->payload[2]>=0){
                                 box_info.r_ear_bat=uart_rxbuf->payload[2];
                            }
                            if(uart_rxbuf->payload[3]<=7 && uart_rxbuf->payload[3]>=0){// 4:仓充电  2:L充电  1:R充电  7:都充电
                                 printf(" 4:仓充电  2:L充电  1:R充电  7:都充电 %d ", ((uart_rxbuf->payload[3] & 0x04)?1:0));
                                 if(box_info.box_charging != ((uart_rxbuf->payload[3] & 0x04)?1:0)){
                                    printf(">>>>>>>>>>>lv_exit_sleep");
                                    extern void lv_exit_sleep();
                                    lv_exit_sleep();
                                 }
                                 box_info.box_charging = (uart_rxbuf->payload[3] & 0x04)?1:0;
                                 box_info.l_charging = (uart_rxbuf->payload[3] & 0x02)?1:0;
                                 box_info.r_charging = (uart_rxbuf->payload[3] & 0x01)?1:0;
                            }
                            box_info.box_clid_status = uart_rxbuf->payload[4];
                            msg[0] = (int)user_check_into_scan;
                            msg[1] = 1;
                            os_taskq_post_type("app_core", Q_CALLBACK, 2, msg);
                            break;
                        case UART_CMD_MAC:      //MAC地址
                            log_info("UART_CMD_MAC : %x %x %x %x %x %x\n",    uart_rxbuf->payload[0], uart_rxbuf->payload[1], \
                                                                            uart_rxbuf->payload[2], uart_rxbuf->payload[3], \
                                                                            uart_rxbuf->payload[4], uart_rxbuf->payload[5]);
                            memcpy(custom_remote_addr, uart_rxbuf->payload,6);
                            extern void sbox_receive_earphone_mac(void);
                            int msg[2]={0};
                            msg[0] = (int)sbox_receive_earphone_mac;
                            msg[1] = 1;
                            os_taskq_post_type("app_core", Q_CALLBACK, 2, msg);
                            break;
                        // 菜单处理
                        case UART_CMD_BATTERY:  //电量交互
                            log_info("UART_CMD_BATTERY : %x\n", uart_rxbuf->payload[0]);
                            // os_taskq_post_msg(JBL_MENU_TASK_NAME, 2, JBL_CMD_BATTERY);
                            break;
                        case UART_CMD_CHARGING: //充电与电量状态交互
                            log_info("UART_CMD_CHARGING : %x\n", uart_rxbuf->payload[0]);
                            log_info("UART_CMD_CHARGING : %x\n", uart_rxbuf->payload[1]);
                            log_info("UART_CMD_CHARGING : %x\n", uart_rxbuf->payload[2]);
                            log_info("UART_CMD_CHARGING : %x\n", uart_rxbuf->payload[3]);
                            if(get_vbat_value_from_f98 != (uart_rxbuf->payload[3] & BIT(2)?1:0)){
                                if(!get_vbat_value_from_f98) {
                                    get_vbat_value_from_f98 = 1;
                                    vbat_voltage_array_f98_init();
                                                                    } else {
                                    get_vbat_value_from_f98 = 0;
                                    vbat_voltage_array_f98_uninit();
                                                                    }
                            }
                            if(uart_rxbuf->payload[1]<=100 && uart_rxbuf->payload[1]>=0){
                                 box_info.l_ear_bat=uart_rxbuf->payload[1];
                            }
                            if(uart_rxbuf->payload[2]<=100 && uart_rxbuf->payload[2]>=0){
                                 box_info.r_ear_bat=uart_rxbuf->payload[2];
                            }
                            if(uart_rxbuf->payload[3]<=7 && uart_rxbuf->payload[3]>=0){// 4:仓充电  2:L充电  1:R充电  7:都充电
                                 printf(" 4:仓充电  2:L充电  1:R充电  7:都充电 %d ", ((uart_rxbuf->payload[3] & 0x04)?1:0));
                                 if(box_info.box_charging != ((uart_rxbuf->payload[3] & 0x04)?1:0)){
                                    printf(">>>>>>>>>>>lv_exit_sleep");
                                    extern void lv_exit_sleep();
                                    lv_exit_sleep();
                                 }
                                 box_info.box_charging = (uart_rxbuf->payload[3] & 0x04)?1:0;
                                 b_printf("c仓充电： %d", box_info.box_charging);
                                 box_info.l_charging = (uart_rxbuf->payload[3] & 0x02)?1:0;
                                 box_info.r_charging = (uart_rxbuf->payload[3] & 0x01)?1:0;
                            }
                            break;
                        case UART_CMD_BUTTON:   //按键事件
                            log_info("UART_CMD_BUTTON : %x\n", uart_rxbuf->payload[0]);
                            break;
                        case UART_USER_ADD:
                            log_info("UART_USER_ADD : %x\n", uart_rxbuf->payload[0]);
                            break;
                        case UART_CMD_EAR_HW_ST:
                            log_info("UART_CMD_EAR_HW_ST : %x\n", uart_rxbuf->payload[0]);
                            extern void ear_inbox_state_deal(u8 status);
                            ear_inbox_state_deal(uart_rxbuf->payload[0]);
                            break;
                        case CMD_BATTERY_F98:
                            log_info("CMD_BATTERY_F98");
                            u16 temp_adc_value = 0;
                            temp_adc_value = (u16)((uart_rxbuf->payload[0] << 8) | uart_rxbuf->payload[1]);
                            get_vbat_value_from_f98 = uart_rxbuf->payload[2];
                            g_printf("DDD - temp_adc_value: 0x%x", temp_adc_value);

                            get_vbat_a_from_f98 = (u16)((uart_rxbuf->payload[3] << 8) | uart_rxbuf->payload[4]);
                            g_printf("DDD - a_f98: 0x%x", get_vbat_a_from_f98);
                            // g_printf("charge_en: %d", uart_rxbuf->payload[0]);
                            if (get_vbat_value_from_f98) {
                                f98_vbat_to_array(temp_adc_value);
                            }
                            break;
                        default:
                            break;
                    }
                        // /* memset(uart_txbuf, 0, JBL_UART_FRAME_LEN);
                        // uart_txbuf->magic_1 = UART_MAGIC_NUM_1;
                        // uart_txbuf->magic_2 = UART_MAGIC_NUM_2;
                        // uart_txbuf->type = uart_rxbuf->type;
                        // uart_txbuf->direct = TO_982;
                        // uart_send_blocking(1, uart_txbuf, JBL_UART_FRAME_LEN,1);
                        // // uart_send_bytes(1, uart_txbuf, JBL_UART_FRAME_LEN);
                        // log_info("tx_data[%d]:\n", JBL_UART_FRAME_LEN);
                        // put_buf(uart_txbuf, JBL_UART_FRAME_LEN); */
                    break;
                default:
                    break;
                }
            }
        }
    }
}
extern u8 uart_into_new_sleep;
static void user_uart_int_handler()
{
    // y_printf("%s %d\n",__func__,uart_into_new_sleep);
    int_into_read_uart=1;
    uart_active();
    if(uart_into_new_sleep){
        uart_into_new_sleep=0;
        power_wakeup_index_enable(6,1);
    }
    
}

void sbox_uart_init(void)
{
    power_wakeup_index_enable(6,1);
    port_edge_wkup_set_callback_by_index(6, user_uart_int_handler);
    int err = task_create(sbox_uart_rx_task, NULL, "sbox_uart_rx");
    if(err != OS_NO_ERR){
        printf("creat fail %x\n", err);
    }
    err = task_create(sbox_uart_tx_task, NULL, "sbox_uart_tx" );
    if (err) {
        printf("jbl_uart_tx_task creat fail %x\n", err);
    }
}