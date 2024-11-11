/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include "lvgl.h"
#include "ui/ui_api.h"
#include "asm/imd.h"
#include "asm/debug.h"

#include "app_config.h"

#if LVGL_TEST_ENABLE

/*********************
 *      DEFINES
 *********************/
// #define MY_DISP_HOR_RES 		320//240
// #define MY_DISP_VER_RES			172//240
// #define MY_DISP_VLOCK_H			60

#define JL_SW_ROATE     1       //JL软件旋转，比LV省2/3BUF，效率更高
static u8  RBUF_WAIT =  1;      //不等待可以提速
const  u8  RBUF_270  =  1;      //0：90度 1：270度

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void *lcd);

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//        const lv_area_t * fill_area, lv_color_t color);

/**********************
 *  STATIC VARIABLES
 **********************/
extern void lvgl_disp_init(void *arg, void **buf1, void **buf2, int *lcd_w,int *lcd_h, int *colums, int *lines);
static void *buf_2_1;
static void *buf_2_2;
static int lcd_w;
static int lcd_h;
static int colums;
static int lines;
/**********************
 *      MACROS
 **********************/
static void rounder_cb(lv_disp_drv_t *disp_drv, lv_area_t *area) {
#if !JL_SW_ROATE
    area->x1 = (area->x1 / 2) * 2; // Round down x1 to the nearest multiple of 2
    area->x2 = (area->x2 / 2) * 2 + 1; // Round down x2 to the nearest multiple of 2
#else
    area->x1 = (area->x1 / 2) * 2; 
    area->x2 = (area->x2 / 2) * 2 + 1; 
    area->y1 = (area->y1 / 2) * 2; 
    area->y2 = (area->y2 / 2) * 2 + 1; 
#endif
}
static void render_start_cb(struct _lv_disp_drv_t * disp_drv){
    // extern void lcd_wait_te();
    // lcd_wait_te();
}
/**********************
 *   GLOBAL FUNCTIONS
 **********************/
extern int lcd_draw_area(u8 index, u8 *lcd_buf, int left, int top, int width, int height, int wait);

void lv_port_disp_init(void *lcd)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
#if USR_LVGL_IMB2D_EN
    //  LCD句柄     BUF1    BUF2    内存行  内存列
    lvgl_disp_init(lcd, &buf_2_1, &buf_2_2, &lcd_w, &lcd_h, &colums, &lines);
    r_printf(">>>>>>>>>>>>>>LCD>>>>>>> 2buf %x %x  LCD:%d %d  BLOCK:%d %d",buf_2_1, buf_2_2, lcd_w, lcd_h,  colums, lines);
#else
    disp_init(lcd);
#endif

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    /**
     * LVGL requires a buffer where it internally draws the widgets.
     * Later this buffer will passed to your display driver's `flush_cb` to copy its content to your display.
     * The buffer has to be greater than 1 display row
     *
     * There are 3 buffering configurations:
     * 1. Create ONE buffer:
     *      LVGL will draw the display's content here and writes it to your display
     *
     * 2. Create TWO buffer:
     *      LVGL will draw the display's content to a buffer and writes it your display.
     *      You should use DMA to write the buffer's content to the display.
     *      It will enable LVGL to draw the next part of the screen to the other buffer while
     *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
     *
     * 3. Double buffering
     *      Set 2 screens sized buffers and set disp_drv.full_refresh = 1.
     *      This way LVGL will always provide the whole rendered screen in `flush_cb`
     *      and you only need to change the frame buffer's address.
     */

    /* Example for 1) */
    /* static lv_disp_draw_buf_t draw_buf_dsc_1; */
    /* static lv_color_t buf_1[MY_DISP_HOR_RES * 10];                          [>A buffer for 10 rows<] */
    /* lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 10);   [>Initialize the display buffer<] */

    /* Example for 2) */
#if USR_LVGL_IMB2D_EN
    static lv_disp_draw_buf_t draw_buf_dsc_2;
    if(buf_2_2 == NULL){    //单BUFF整屏
        lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, NULL, lcd_w * lcd_h);   /*Initialize the display buffer*/
    } else {    //双BUFF分块
        lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, colums * lines);   /*Initialize the display buffer*/
    }
#else 
    static lv_disp_draw_buf_t draw_buf_dsc_2;
    static lv_color_t buf_2_1[MY_DISP_HOR_RES * MY_DISP_VLOCK_H];
    static lv_color_t buf_2_2[MY_DISP_HOR_RES * MY_DISP_VLOCK_H];
    /* y_printf("buf_2_1:0x%x, 0x%x \n", buf_2_1, buf_2_2); */
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * MY_DISP_VLOCK_H);   /*Initialize the display buffer*/
#endif
    /* Example for 3) also set disp_drv.full_refresh = 1 below*/
    /* static lv_disp_draw_buf_t draw_buf_dsc_3; */
    /* static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];            [>A screen sized buffer<] */
    /* static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];            [>An other screen sized buffer<] */
    /* lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2, MY_DISP_VER_RES * LV_VER_RES_MAX);   [>Initialize the display buffer<] */

    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
#if USR_LVGL_IMB2D_EN
    disp_drv.hor_res = lcd_w;
    disp_drv.ver_res = lcd_h;
#else 
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;
#endif

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_2;
    // disp_drv.sw_rotate = 1;
    // disp_drv.rotated = LV_DISP_ROT_90;

    /*Required for Example 3)*/
    // disp_drv.full_refresh = 1;

    /* Fill a memory array with a color if you have GPU.
     * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
     * But if you have a different GPU you can use with this callback.*/
    //disp_drv.gpu_fill_cb = gpu_fill;

    disp_drv.render_start_cb = render_start_cb;
    disp_drv.rounder_cb = rounder_cb;


    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

extern int lcd_drv_init(void *p);
/*Initialize your display and the required peripherals.*/
static void disp_init(void *lcd)
{
    /*You code here*/
    lcd_drv_init(lcd);
}



static void jl_sw_rotate(lv_disp_drv_t *disp_drv, lv_color_t *color_p, int left, int top, int width, int height, u8 wait){
    if(wait)lcd_wait();  
    if(disp_drv->draw_buf->buf1 && disp_drv->draw_buf->buf2) {
        if(disp_drv->draw_buf->buf_act == disp_drv->draw_buf->buf1)
            disp_drv->draw_buf->buf_act = disp_drv->draw_buf->buf2;
        else
            disp_drv->draw_buf->buf_act = disp_drv->draw_buf->buf1;
    }
    lv_color_t * rot_buf = disp_drv->draw_buf->buf_act;

    lv_color_t * orig_color_p = color_p;
    int a = jiffies_half_msec();
    int area_w = width;
    int area_h = height;
    const u8 invert_i = RBUF_270;
    uint32_t invert = (area_w * area_h) - 1;
    uint32_t initial_i = ((area_w - 1) * area_h);
    for(lv_coord_t y = 0; y < area_h; y++) {
        uint32_t i = initial_i + y;
        if(invert_i)
            i = invert - i;
        for(lv_coord_t x = 0; x < area_w; x++) {
            rot_buf[i] = *(orig_color_p++);
            if(invert_i)
                i += area_h;
            else
                i -= area_h;
        }
    }
    // memcpy(color_p, rot_buf, width*height*2);
    int b = jiffies_half_msec();
    // printf("draw_buf_rotate_90 %d 1/2ms",b-a);
    if(invert_i){
        /* mpu_disable_by_index(4); */
        lcd_draw_area(0, rot_buf, lcd_h - (top+height), left, height, width, 0); //旋转
        /* mpu_set(4,0x118a30 ,0x118a30+3, 0, "CrPr"); */
    } else {
        /* mpu_disable_by_index(4); */
        lcd_draw_area(0, rot_buf, top, lcd_w - (left+width), height, width, 0); //旋转
        /* mpu_set(4,0x118a30,0x118a30+3, 0, "CrPr"); */
    }
}





extern void lv_lcd_data_copy(u8 *lcd_buf, int left, int top, int width, int height);
/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
LV_ATTRIBUTE_FAST_MEM static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    int left	= area->x1;
    int top		= area->y1;
    int width	= area->x2 - area->x1 + 1;
    int height	= area->y2 - area->y1 + 1;
    // y_printf("[%d,%d,%d,%d]", left, top, width, height);
    /* 异常条件 */
    if(width<=1 || lcd_sleep_status()) goto __end;

    /* 软件旋转BUF处理 */
    // if(disp_drv->draw_buf->buf_act != color_p && disp_drv->sw_rotate){
    //     memcpy(disp_drv->draw_buf->buf_act, color_p, width*height*2);
    //     color_p = disp_drv->draw_buf->buf_act;
    // }

    /* 显示buf匹配 */
    if(disp_drv->draw_buf->buf_act != color_p) goto __end;

    extern volatile u8 usr_full_screen;
    extern volatile u8 usr_wait_te;
    static int cnt = 0;
    cnt ++;

    if (PSRAM_FULL_SCREEN && usr_full_screen){  //  先缓存到PSRAM
        lv_lcd_data_copy(color_p,  left,  top,  width,  height);    //分块DMA到PSRAM
        if(disp_drv->draw_buf->buf2 == NULL) dma_memcpy_wait_idle(); 
    }else{
        if(usr_wait_te && cnt==1) lcd_wait_te();   //第一个刷新等待TE
#if JL_SW_ROATE
        jl_sw_rotate(disp_drv, color_p, left, top, width, height, RBUF_WAIT);
#else
        lcd_draw_area(0, color_p, left, top, width, height, cnt==1); //正常
#endif        
        if(disp_drv->draw_buf->buf2 == NULL) lcd_wait();  
    }

    //  最后一个BUF cnt清0
    if(lv_disp_flush_is_last(disp_drv)){
        static int last_ms = 0;
        // printf("true fps: %d", 1000/(jiffies_msec()-last_ms));
        last_ms = jiffies_msec();
        cnt = 0;
    }

    //  如果缓存到PSRAM，最后一个buf 推屏
    if(cnt == 0 && PSRAM_FULL_SCREEN && usr_full_screen){
        // dma_memcpy_wait_idle(); // 等最后一块合成buf dma完成，这里PSRAM推屏的位置追不上最后一块SRAM dma到PSRAM的位置可以不打开，进一步提高速度
        full_screen_flush();    //PSRAM推整屏 
    }

__end:
    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

/*OPTIONAL: GPU INTERFACE*/

/*If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color*/
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//                    const lv_area_t * fill_area, lv_color_t color)
//{
//    /*It's an example code which should be done by your GPU*/
//    int32_t x, y;
//    dest_buf += dest_width * fill_area->y1; /*Go to the first line*/
//
//    for(y = fill_area->y1; y <= fill_area->y2; y++) {
//        for(x = fill_area->x1; x <= fill_area->x2; x++) {
//            dest_buf[x] = color;
//        }
//        dest_buf+=dest_width;    /*Go to the next line*/
//    }
//}


#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif

#endif /* #if LVGL_TEST_ENABLE */

