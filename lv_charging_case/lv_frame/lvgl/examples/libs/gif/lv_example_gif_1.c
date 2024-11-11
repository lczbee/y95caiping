#include "../../lv_examples.h"
#if LV_USE_GIF && LV_BUILD_EXAMPLES


const anmi_src[] = {
    "s:storage/sd0/C/4_150.bin",
    "s:storage/sd0/C/5.bin",
    "s:storage/sd0/C/5_150.bin",
    "s:storage/sd0/C/6.bin",
    "s:storage/sd0/C/chick.bin",
    "s:storage/sd0/C/frame.jpg",
};
static void test_cb(lv_timer_t * p){

    //  在lv_conf.h配置缓存图片的个数，#define LV_IMG_CACHE_DEF_SIZE 50//0//缓存的图片数量
    //  最大占用psram内存缓存大小 = n张图片所有缓存图片加起来，其中动态图256K一个
    //  加载数量超过上限会自动释放旧图片，自行去评估LV_IMG_CACHE_DEF_SIZE大小。

    //  静态图释放不释放都可以
    //  lv_img_cache_invalidate_src(NULL);

    lv_obj_t * imgobj = p->user_data;
    static u8 i = 0;
    i = (++i)%ARRAY_SIZE(anmi_src);

    lv_img_set_src(imgobj, anmi_src[i]);
    

}

/**
 * Open a GIF image from a file and a variable
 */
void lv_example_gif_1(void)
{

#if 1//
    lv_obj_t * imgobj = lv_img_create(lv_scr_act());
    lv_img_set_src(imgobj, "s:storage/sd0/C/aq.bin");
    lv_obj_align(imgobj, LV_ALIGN_CENTER, 0, 0);

    lv_timer_create(test_cb, 1000, imgobj);

#else

    LV_IMG_DECLARE(img_bulb_gif);
    lv_obj_t * img;

    void *fp = fopen("storage/sd0/C/yhy.gif", "r");
    void * imgdata;
    if(fp) {
        printf("d0/C/qipao.gif");
        imgdata = malloc_psram(flen(fp));
        if(imgdata== NULL) printf("PSARMsq异常");
        fread(fp, imgdata, flen(fp));
        fclose(fp);
    }

    static lv_img_dsc_t test = {0};
    test.header.always_zero = 0,
    test.header.w = 0,
    test.header.h = 0,
    test.data_size = 0,
    test.header.cf = LV_IMG_CF_RAW,
    test.data = imgdata,

    img = lv_gif_create(lv_scr_act());
    lv_gif_set_src(img, &test);
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 20, 0);

    // img = lv_gif_create(lv_scr_act());
    // /* Assuming a File system is attached to letter 'A'
    //  * E.g. set LV_USE_FS_STDIO 'A' in lv_conf.h */
    // lv_gif_set_src(img, "P:storage/sd0/C/qipao.gif");
    // lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
#endif
}

#endif
