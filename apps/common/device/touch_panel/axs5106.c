
#include "app_config.h"
#include "system/includes.h"
#include "asm/iic_hw.h"
#include "asm/iic_soft.h"
#include "asm/gpio.h"
#include "asm/mcpwm.h"
#include "ui/ui.h"
#include "ui/ui_api.h"
#include "timer.h"
#include "system/device_sleep_control.h"

#include "axs5106.h"

#if TCFG_TOUCH_PANEL_ENABLE

#if TCFG_TP_AXS5106_ENABLE


#if TCFG_TOUCH_USER_IIC_TYPE
#define iic_init(iic)                       hw_iic_init(iic)
#define iic_uninit(iic)                     hw_iic_uninit(iic)
#define iic_start(iic)                      hw_iic_start(iic)
#define iic_stop(iic)                       hw_iic_stop(iic)
#define iic_tx_byte(iic, byte)              hw_iic_tx_byte(iic, byte)
#define iic_rx_byte(iic, ack)               hw_iic_rx_byte(iic, ack)
#define iic_read_buf(iic, buf, len)         hw_iic_read_buf(iic, buf, len)
#define iic_write_buf(iic, buf, len)        hw_iic_write_buf(iic, buf, len)
#define iic_suspend(iic)                    hw_iic_suspend(iic)
#define iic_resume(iic)                     hw_iic_resume(iic)
#else
#define iic_init(iic)                       soft_iic_init(iic)
#define iic_uninit(iic)                     soft_iic_uninit(iic)
#define iic_start(iic)                      soft_iic_start(iic)
#define iic_stop(iic)                       soft_iic_stop(iic)
#define iic_tx_byte(iic, byte)              soft_iic_tx_byte(iic, byte)
#define iic_rx_byte(iic, ack)               soft_iic_rx_byte(iic, ack)
#define iic_read_buf(iic, buf, len)         soft_iic_read_buf(iic, buf, len)
#define iic_write_buf(iic, buf, len)        soft_iic_write_buf(iic, buf, len)
#define iic_suspend(iic)                    soft_iic_suspend(iic)
#define iic_resume(iic)                     soft_iic_resume(iic)
#endif

typedef struct {
    u8 init;
    soft_iic_dev iic_hdl;
} ft_param;

static ft_param module_param = {0};
#define __this   (&module_param)

#define AXS5106_IIC_DELAY   1
#define AXS5106_IIC_ADDR  0xC6 /* 7-bit i2c addr */ //

#define AXS5106_RST_IO    (IO_PORTG_06)

#define AXS_UPGRADE_CHECK_VERSION    1
#define AXS_UPGRADE_ENABLE           1
#define AXS_UPGRADE_FAILED_RETRY_TIMES   1



#if TCFG_LCD_RM69330_QSPI_ENABLE
#define AXS5106_RESET_H() gpio_direction_output(AXS5106_RST_IO,1)
#define AXS5106_RESET_L() gpio_direction_output(AXS5106_RST_IO,0)
#else
#define AXS5106_RESET_H() gpio_direction_output(AXS5106_RST_IO,1)
#define AXS5106_RESET_L() gpio_direction_output(AXS5106_RST_IO,0)
#endif
#define AXS5106_INT_IO    (IO_PORTG_05)
#define AXS5106_INT_IN()  gpio_direction_input(AXS5106_INT_IO);gpio_set_pull_down(AXS5106_INT_IO,0);gpio_set_pull_up(AXS5106_INT_IO,1);
#define AXS5106_INT_R()   gpio_read(AXS5106_INT_IO)


#define I2C_MASTER_CI2C0 0
#define i2c_t uint8_t


u16 CTP_FLASH_I2C_WRITE(u8 slave_addr, u8 *buf, u16 len)
{
    u16 i = 0;
    iic_start(__this->iic_hdl);
    if (0 == iic_tx_byte(__this->iic_hdl, slave_addr)) {
        iic_stop(__this->iic_hdl);
        return 0;
    }

    for (i = 0; i < len; i++) {
        delay(AXS5106_IIC_DELAY);
        if (0 == iic_tx_byte(__this->iic_hdl, buf[i])) {
            iic_stop(__this->iic_hdl);
            return i;
        }
    }
    iic_stop(__this->iic_hdl);
    return i;
}

u16 CTP_FLASH_I2C_WRITES(u8 slave_addr, u8 *buf1,u8 len1, u8 *buf, u16 len)
{
    u16 i = 0;
    iic_start(__this->iic_hdl);
    if (0 == iic_tx_byte(__this->iic_hdl, slave_addr)) {
        iic_stop(__this->iic_hdl);
        return 0;
    }
	for (i = 0; i < len1; i++) {
        delay(AXS5106_IIC_DELAY);
        if (0 == iic_tx_byte(__this->iic_hdl, buf1[i])) {
            iic_stop(__this->iic_hdl);
            return i;
        }
	}
    for (i = 0; i < len; i++) {
        delay(AXS5106_IIC_DELAY);
        if (0 == iic_tx_byte(__this->iic_hdl, buf[i])) {
            iic_stop(__this->iic_hdl);
            return i;
        }
    }
    iic_stop(__this->iic_hdl);
    return i;
}


//return =len:ok; other:fail
u16 CTP_FLASH_I2C_READ(u8 slave_addr, u8 *buf, u16 len)
{
    u16 i = 0;
    iic_start(__this->iic_hdl);
    if (0 == iic_tx_byte(__this->iic_hdl, slave_addr + 1)) {
        iic_stop(__this->iic_hdl);
        return 0;
    }
    for (i = 0; i < len - 1; i++) {
        delay(AXS5106_IIC_DELAY);
        *buf++ = iic_rx_byte(__this->iic_hdl, 1);
    }
    i++;
    *buf = iic_rx_byte(__this->iic_hdl, 0);
    iic_stop(__this->iic_hdl);
    return i;
}

void ctp_delay_us(unsigned int time)
{
    udelay(time);
}
void ctp_delay_ms(unsigned short time)
{
    mdelay(time);
}


extern void timer1_run(u32 precesion);

void axs_reset(void)
{

	u8 rst_cmd[2] = {0xff,0xff};
    // 2. reset TouchIC
	AXS5106_RESET_H();
    ctp_delay_us(50);
    AXS5106_RESET_L();
    ctp_delay_us(50);
    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, rst_cmd, 2);
    //delay time > 2ms-->delay time > 25ms
    ctp_delay_ms(25); // 2->25
	AXS5106_RESET_H();

}



static bool touch_flag = 0;
static void touch_event_handler(void *priv);

static int touch_int_handler()
{
    touch_flag = 1;

#if defined(CONFIG_CPU_BR28)
    touch_event_handler(NULL);
#endif

    return 0;
}


#define ENERGY_XDISTANCE	1
#define ENERGY_YDISTANCE	1
#define ENERGY_TIME			500 //ms
struct touch_kinetic_energy {
    int t1;
    int x1;
    int y1;

    int t2;
    int x2;
    int y2;
};
static struct touch_kinetic_energy tke = {0};
static void tke_start(int x, int y)
{
    memcpy(&tke.t2, &tke.t1, sizeof(tke) / 2);

    if ((tke.x1 == x) && (tke.y1 == y)) {
        tke.t1 = tke.t1;
    } else {
        tke.t1 = jiffies_msec();
    }
    tke.x1 = x;
    tke.y1 = y;
}

static void tke_stop(int x, int y)
{
    struct touch_event t;
    u8 xdir, ydir;

    if (tke.t1 == 0) {
        return;
    }
    tke.t1 = tke.t1 - tke.t2;
    tke.x1 = tke.x1 - tke.x2;
    tke.y1 = tke.y1 - tke.y2;

    /* printf("tke end %d, %d, %d\n", tke.t1, tke.x1, tke.y1); */

    if ((tke.t1 < ENERGY_TIME) &&
        ((abs(tke.x1) > ENERGY_XDISTANCE) || abs(tke.y1) > ENERGY_YDISTANCE)) {

        if (abs(tke.x1) <= ENERGY_XDISTANCE) {
            tke.x1 = 0;
        }
        if (abs(tke.y1) <= ENERGY_YDISTANCE) {
            tke.y1 = 0;
        }
        xdir = (tke.x1 < 0) ? 1 : 2;
        ydir = (tke.y1 < 0) ? 1 : 2;
        /* printf("xdir %d, ydir %d\n", xdir, ydir); */

        t.event = ELM_EVENT_TOUCH_ENERGY;
        t.x = (tke.x1 << 16) | (tke.t1 & 0xffff);
        t.y = (tke.y1 << 16) | (ydir << 8) | (xdir & 0xff);
        // ui_touch_msg_post(&t);

        /* printf("tke out %d, %d, %d, %d, %d\n", (t.x & 0xffff), (t.x >> 16), (t.y >> 16), (t.y & 0xff), (t.y >> 8) & 0xff); */

    }

    memset(&tke, 0, sizeof(tke));

}


struct point {
    int x;
    int y;
};

typedef struct {
    struct point point;
    int state;
} lv_indev_data_t;

#define LV_INDEV_STATE_PR  0
#define LV_INDEV_STATE_REL 1
#define VK_X 320
#define VK_Y 172//282

static int vk_state = LV_INDEV_STATE_REL;


#define Y_MIRROR  0
#define X_MIRROR  0

static u8 tp_last_staus = ELM_EVENT_TOUCH_UP;
static int tp_down_cnt = 0;

#define abs(x)  ((x)>0?(x):-(x) )

static void tpd_down(int raw_x, int raw_y, int x, int y, int p)
{
    struct touch_event t;
    static int first_x = 0;
    static int first_y = 0;
    static u8 move_flag = 0;

#if Y_MIRROR
    y = VK_Y - y;
#endif

#if X_MIRROR
    x = VK_X - x;
#endif

    if ((tp_last_staus == ELM_EVENT_TOUCH_DOWN) && (x == first_x) && (y == first_y)) //TP长按动作，发送长按消息
    {
        tp_down_cnt++;
        if (tp_down_cnt < 30) {
            return;
        }
        tp_last_staus = ELM_EVENT_TOUCH_HOLD;
        tp_down_cnt = 0;

        t.event = tp_last_staus;
        t.x = x;
        t.y = y;
        // ui_touch_msg_post(&t);
        return;
    }

    if (tp_last_staus != ELM_EVENT_TOUCH_UP) {
        int x_move = abs(x - first_x);
        int y_move = abs(y - first_y);

        if (!move_flag && (x_move >= 50 || y_move >= 50) && (abs(x_move - y_move) >= 25)) 
        {
            if (x_move > y_move)
            {
                if (x > first_x) {
                        //printf("----- ELM_EVENT_TOUCH_R_MOVE -------");
                    tp_last_staus = ELM_EVENT_TOUCH_R_MOVE;
                } else {
                       // printf("----- ELM_EVENT_TOUCH_L_MOVE -------");
                    tp_last_staus = ELM_EVENT_TOUCH_L_MOVE;
                }
            } 
            else 
            {
                if (y > first_y) {
                    tp_last_staus = ELM_EVENT_TOUCH_D_MOVE;
                } else {
                    tp_last_staus = ELM_EVENT_TOUCH_U_MOVE;
                }
            }
            move_flag = 1;
        } 
        else
        {
            tp_last_staus = ELM_EVENT_TOUCH_MOVE;
        }
        tke_start(x,y);
    } 
    else
    {
        tp_last_staus = ELM_EVENT_TOUCH_DOWN;
        //t.user_event=ELM_EVENT_USER_TOUCH_DOWN;
        first_x = x;
        first_y = y;
        move_flag = 0;
    }

    t.event = tp_last_staus;
    t.x = x;
    t.y = y;
    // ui_touch_msg_post(&t);
}

static void tpd_up(int raw_x, int raw_y, int x, int y, int p)
{
    struct touch_event t;
#if Y_MIRROR
    x = VK_X - x;
#endif
#if X_MIRROR
    y = VK_Y - y;
#endif

    tp_last_staus = ELM_EVENT_TOUCH_UP;
    t.event = tp_last_staus;
    t.x = x;
    t.y = y;
    // ui_touch_msg_post(&t);

    tke_stop(x, y);
}





bool AXS5106_read(lv_indev_data_t *data)
{
    unsigned irq_state;
    int update = 0;
    static int x_last, y_last;
    unsigned char buf[6];
    unsigned char cmdPoint = 0x01;


    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, &cmdPoint, sizeof(cmdPoint));
    CTP_FLASH_I2C_READ(AXS5106_IIC_ADDR,  buf, sizeof(buf));
    data->point.x = buf[3] | ((buf[2] & 0xF) << 8);
    data->point.y = buf[5] | ((buf[4] & 0xF) << 8);
    x_last = data->point.x;
    y_last = data->point.y;
    data->state = ((buf[2] & 0xF0) != 0x40) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
    printf("finger:%d, %d,(%d, %d), %s\n",  buf[0],buf[1], data->point.x, data->point.y, (data->state == LV_INDEV_STATE_PR) ? "pressed" : "released");
    // printf("buf[0], buf[1], buf[2], buf[3], buf[4]: [%d %d %d %d %d]", buf[0], buf[1], buf[2], buf[3], buf[4]);
    if ((data->point.x == VK_X) && (data->point.y == VK_Y)) {
        vk_state = data->state;
        printf("vk %s\n", (vk_state == LV_INDEV_STATE_PR) ? "press" : "release");
    }

    if ((buf[2] & 0xF0) != 0x40) {
          printf("***** tpd_down *******");
        tpd_down(0, 0, data->point.x, data->point.y, 0);
    } else {
        printf("***** tpd_up *******");
        tpd_up(0, 0, data->point.x, data->point.y, 0);
    }

    return false; /* no more data to read */
}



static u16 regs_table[] = {
    0x01,//GestureID
    0x02,//FingerNum
    0x03,//XposH
    0x04,//XposL
    0x05,//YposH
    0x06,//YposL
    0xB0,//BPC0H
    0xB1,//BPC0L
    0xB2,//BPC1H
    0xB3,//BPC1L
    0xA7,//ChipID
    0xA8,//ProjID
    0xA9,//FwVersion
    0xEC,//MotionMask
    0xED,//IrqPluseWidth
    0xEE,//NorScanPer
    0xEF,//MotionS1Angle
    0xF0,//LpScanRaw1H
    0xF1,//LpScanRaw1L
    0xF2,//LpScanRaw2H
    0xF3,//LpScanRaw2L
    0xF4,//LpAutoWakeTime
    0xF5,//LpScanTH
    0xF6,//LpScanWin
    0xF7,//LpScanFreq
    0xF8,//LpScanIdac
    0xF9,//AutoSleepTime
    0xFA,//IrqCtl
    0xFB,//AutoReset
    0xFC,//LongPressTime
    0xFD,//IOCtl
    0xFE//DisAutoSleep
};


int axs_version(u16 *buf)
{
    int ret = 0x00;

    ctp_delay_ms(50);
    uint8_t sendata[] = {0x05};
    uint8_t getdata[2] = {};
    ret = CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 1);
    if (ret != 1) {
        printf("axs_get_version:i2c write flash error___\n");
        ret = -1;
    }
    ret = CTP_FLASH_I2C_READ(AXS5106_IIC_ADDR, getdata, 2);
    if (ret != 2) {
        printf("axs_get_version:i2c read flash error___\n");
        ret = -1;
    }

	*buf  = ((getdata[0]<<8)|getdata[1]);

    ctp_delay_ms(20);
    return ret;
}


int axs_project_id(u16 *buf)
{
    int ret = 0x00;

    ctp_delay_ms(50);
    uint8_t sendata[] = {0x0A};
    uint8_t getdata[2] = {};
    ret = CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 1);
    if (ret != 1) {
        printf("axs_get_version:i2c write flash error___\n");
        ret = -1;
    }
    ret = CTP_FLASH_I2C_READ(AXS5106_IIC_ADDR, getdata, 2);
    if (ret != 2) {
        printf("axs_get_version:i2c read flash error___\n");
        ret = -1;
    }

	*buf  = ((getdata[0]<<8)|getdata[1]);

    ctp_delay_ms(20);
    return ret;
}


static BOOL axs_fwupg_get_ver_in_bin(u16 *ver)
{
    u16 ver_offset = 0x400;
    if (!sizeof(fw_buf))
    {
        printf("axs_data/upgrade/func/fw/ver is NULL");
        return FALSE;
    }

    if (sizeof(fw_buf) < ver_offset)
    {
        printf("fw len(0x%0x) < fw ver offset(0x%x)",
                  sizeof(fw_buf), ver_offset);
        return FALSE;
    }
    *ver = ((fw_buf[ver_offset]<<8)|(fw_buf[ver_offset+1]));
    return TRUE;
}

static BOOL axs_fwupg_get_project_id_in_bin(u16 *project_id)
{
    u16 project_id_offset = 0x402;
    if (!sizeof(fw_buf))
    {
        printf("axs_data/upgrade/func/fw/project_id is NULL");
        return FALSE;
    }

    if (sizeof(fw_buf) < project_id_offset)
    {
        printf("fw len(0x%0x) < fw project_id offset(0x%x)",
                  sizeof(fw_buf), project_id_offset);
        return FALSE;
    }
    *project_id = ((fw_buf[project_id_offset]<<8)|(fw_buf[project_id_offset+1]));
    return TRUE;
}


/******************************************************************************
 *@Description :  get firmware version from tp
 *@Function    :  axs_fwupg_get_ver_in_tp
 *@Note        :
*******************************************************************************/
static BOOL axs_fwupg_get_project_id_in_tp(u16 *project_id)
{
    if (axs_project_id(project_id))
    {
    	return TRUE;
    }
    return FALSE;
}
/******************************************************************************
 *@Description :  get firmware version from tp
 *@Function    :  axs_fwupg_get_ver_in_tp
 *@Note        :
*******************************************************************************/
static BOOL axs_fwupg_get_ver_in_tp(u16 *ver)
{
    if (axs_version(ver))
    {
    	return TRUE;
    }
    return FALSE;
}
/******************************************************************************
 *@Description :  upgrade step 1:enter debug mode
 *@Function    :  axs_fwupg_enter_debug_mode
 *@Note        :
*******************************************************************************/
// static void axs_fwupg_enter_debug_mode(void)
// {
// 	uint8_t sendata[] = {0xaa,0x55};
//     axs_reset();
//     //make sure: 500us < delay time < 2ms
//     ctp_delay_ms(1);
// 	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 2);
//     //delay time >= 50us
//     ctp_delay_us(100);
// }

static void axs_fwupg_enter_debug_mode(void)
{
    printf("func: %s, line: %d", __func__, __LINE__);
	uint8_t sendata[] = {0xaa,0x55};
	uint8_t sendata1[] = {0x80,0x7f,0xd1};
	u8 getdata = 0;
    axs_reset();
    //make sure: 500us < delay time < 2ms
    ctp_delay_ms(1);
	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 2);
    //delay time >= 50us
    ctp_delay_us(100);
	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata1, 3);
	ctp_delay_us(50);
	CTP_FLASH_I2C_READ(AXS5106_IIC_ADDR, &getdata, 1);
	// printf("enter debug mode cmd:%x", getdata);
}

static void axs_fwupg_exit_debug_mode(void)
{
    uint8_t sendata[] = {0xa0,0x5f};
	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 2);
}
/******************************************************************************
 *@Description :  upgrade step 2:unlock mtpc wite protect
 *@Function    :  axs_fwupg_unlock_mtpc_wp
 *@Note        :
*******************************************************************************/
static BOOL axs_fwupg_unlock_mtpc_wp(void)
{
	uint8_t sendata[] = {0x90,0x6f,0xff,0xff};
	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);
    sendata[2]=0xda;
    sendata[3]=0x18;
	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);
    return TRUE;
}
/******************************************************************************
 *@Description :  upgrade step 3:erase flash
 *@Function    :  axs_fwupg_flash_erase
 *@Note        :
*******************************************************************************/
static BOOL axs_fwupg_flash_erase(void)
{
    uint8_t sendata[] = {0x90,0x6f,0xd6,0x77};
	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);
    //delay time >= 240ms
    ctp_delay_ms(260);
    sendata[3]=0x00;
	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);
    return TRUE;
}

/******************************************************************************
 *@Description :  upgrade step 4:write firmware bin to flash
 *@Function    :  axs_fwupg_flash_write
 *@Note        :
*******************************************************************************/
static BOOL axs_fwupg_flash_write(const u8 *fw_buf, u16 fw_len)
{
    uint8_t sendata[] = {0x90,0x6f,0xd4,0x00};
   	uint8_t write_flash_long_reg[6] = {0x70,0x8f,0xd7,0x00,0x00,0x00};
	u16 i;

	CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);

    sendata[2]=0xd5;
    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);
    sendata[2]=0xd2;
    sendata[3]=((fw_len-1)&0xff);
    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);
    sendata[2]=0xd3;
    sendata[3]=(((fw_len-1)>>8)&0xff);
    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);
    sendata[2]=0xd6;
    sendata[3]=0xf4;
    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);

	write_flash_long_reg[4]=((fw_len-1)>>8)&0xff;
	write_flash_long_reg[5]=(fw_len-1)&0xff;
	CTP_FLASH_I2C_WRITES(AXS5106_IIC_ADDR,write_flash_long_reg,6,fw_buf,fw_len);
	
    sendata[2]=0xd6;
    sendata[3]=0x00;
    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sendata, 4);
    return TRUE;
}


static BOOL axs_fwupg_write_flash(void)
{
    axs_fwupg_enter_debug_mode();

    if (!axs_fwupg_unlock_mtpc_wp())
    {
        printf("axs_fwupg_flash_init failed");
        return FALSE;
    }
    if (!axs_fwupg_flash_erase())
    {
        printf("axs_fwupg_flash_erase failed");
        return FALSE;
    }
    // write firmware
    if (!axs_fwupg_flash_write(fw_buf, sizeof(fw_buf)))
    {
        printf("axs_fwupg_flash_write failed");
        return FALSE;
    }
	axs_fwupg_exit_debug_mode();
    ctp_delay_ms(10);
    return TRUE;
}


static BOOL axs_fwupg_need_upgrade(void)
{
    u16 fw_ver_in_bin = 0;
    u16 fw_ver_in_tp = 0;
    u16 fw_project_id_in_bin = 0;
    u16 fw_project_id_in_tp = 0;
    if (!axs_fwupg_get_ver_in_bin(&fw_ver_in_bin))
    {
        return FALSE;
    }
    if (!axs_fwupg_get_ver_in_tp(&fw_ver_in_tp))
    {
        return FALSE; /*get firmware ver failed, do not upgrade;*/
    }
	
    printf("fw version in tp:%x, host:%x", fw_ver_in_tp, fw_ver_in_bin);

	
    if (!axs_fwupg_get_project_id_in_bin(&fw_project_id_in_bin))
    {
        return FALSE;
    }
    if (!axs_fwupg_get_project_id_in_tp(&fw_project_id_in_tp))
    {
        return FALSE; /*get firmware project_id failed, do not upgrade;*/
    }

	
    printf("fw project_id in tp:%x, host:%x", fw_project_id_in_tp, fw_project_id_in_bin);
	
    if ((fw_ver_in_tp != fw_ver_in_bin)||(fw_project_id_in_tp != fw_project_id_in_bin))
    {
        return TRUE;
    }
    else
    {
        printf("fw version is latest!");
    }

    return FALSE;
}

static BOOL axs_upgrade_process(void)
{
    if (!axs_fwupg_write_flash())
    {
        printf("writing firmware Failed\r\n");
        return FALSE;
    }
    return TRUE;
}

static BOOL axs_upgrade_enter(void)
{
	u8 i=0;
#if AXS_UPGRADE_CHECK_VERSION
	axs_reset();
	//delay > 5ms
	ctp_delay_ms(10);
    if (!axs_fwupg_need_upgrade())
    {
        return -1; /*do not need upgrade*/
    }
#endif

    for (i=0; i<(AXS_UPGRADE_FAILED_RETRY_TIMES+1); i++)
    {
        if (axs_upgrade_process())
        {
            break; // success
        }
    }

    if (i==(AXS_UPGRADE_FAILED_RETRY_TIMES+1))
    {
        return -2;/*upgrade failed*/
    }
    return 0;/*upgrade success*/
}

void AXS5106_deep_sleep(void) {
    unsigned char sleepCmd[] = {0x19, 0x03};
    ctp_delay_ms(10);
    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, sleepCmd, 2);
    printf("AXS5106_sleep %s \n",__func__);

}

void AXS5106_low_power_mode(void) {
    unsigned char lowpowerCmd[] = {0x39, 0x01};
    ctp_delay_ms(10);
    CTP_FLASH_I2C_WRITE(AXS5106_IIC_ADDR, lowpowerCmd, 2);
    printf("AXS5106_sleep %s \n",__func__);

}


void AXS5106_wakeup(void) {
    printf(" AXS5106_wakeup %s \n",__func__);
    axs_reset();

}

void ctp_enter_sleep(void)
{
    AXS5106_low_power_mode();
}

void ctp_exit_sleep(void)
{
    AXS5106_wakeup();
}


 volatile u8 touch_down;
 volatile int touch_x;
 volatile int touch_y;
volatile u32 touch_interval;

static void touch_event_handler()
{
    //u8 buf[1];
    //int i;

    touch_interval =  jiffies_msec();

    lv_indev_data_t touch_data;
    if (!touch_flag) {
        return ;
    }
    touch_flag = 0;
    //printf("touch_event_handler\n");
    AXS5106_read(&touch_data);
    touch_x = touch_data.point.x;
    touch_y = VK_Y - touch_data.point.y - 1;
    touch_down = touch_data.state == LV_INDEV_STATE_PR?1:0;
    // printf("touch_x: %d, touch_y: %d", touch_x, touch_y);
    extern void lv_exit_sleep();
    if(touch_down && lcd_sleep_status()){
        screen_on_source = SCREEN_ON_SOURCE_TOUCH;
        printf("lv_exit_sleep");
        lv_exit_sleep();
        AXS5106_wakeup(); // axs5106拉复位唤醒
    }
    lv_touch_active();
#if 0
    buf[0] = 0x3;
    i2c_write_regs(I2C_MASTER_CI2C0, HYN_I2C_ADDR, 0xf8, &buf[0], 1, 0);
    for (i = 0; i < sizeof(regs_table) / sizeof(regs_table[0]); i++) {
        i2c_read_regs(I2C_MASTER_CI2C0, HYN_I2C_ADDR, regs_table[i], &buf[0], 1, 0);
        printf("addr:0x%x , val:0x%02x\n", regs_table[i], buf[0]);
    }
#endif
    // return 1;
}


void ui_set_touch_event(void (*touch_event)(void *priv), int interval);

void AXS5106_init()
{
	u16 chip_version = 0x00;


	printf("AXS5106_init init...\n");

    iic_init(__this->iic_hdl);

    AXS5106_INT_IN();

	axs_version(&chip_version);

    printf("AXS5106_chip_version! = 0x%x\n",chip_version);

#if AXS_UPGRADE_ENABLE

    if (!axs_upgrade_enter()) {
        printf("AXS5106_upgrade fail!\n");
    }
#endif


	ctp_delay_ms(10);

    axs_reset();
	
#ifdef CONFIG_CPU_BR23
    extern void io_ext_interrupt_init(u8 port, trigger_mode_type trigger_mode, IO_ISR_FUNC cbfun);
    io_ext_interrupt_init(CST816S_INT_IO, falling_edge_trigger, touch_int_handler);

#if TCFG_UI_ENABLE
    ui_set_touch_event(touch_event_handler, 2);
#endif

#elif defined(CONFIG_CPU_BR28)
    port_edge_wkup_set_callback_by_index(1, touch_int_handler); 
#endif

#if TCFG_UI_ENABLE
    ui_set_touch_event(NULL, 0);
#endif
}


#endif

#endif


