#include "../lv_examples.h"
#if LV_BUILD_EXAMPLES && LV_USE_BTN && LV_USE_LABEL



/**
 * Opacity and Transformations
 */
void lv_example_style_15(void)
{
    lv_obj_t * btn;
    lv_obj_t * label;

    /*Normal button*/
    btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, 100, 40);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, -70);

    label = lv_label_create(btn);
    lv_label_set_text(label, "Normal");
    lv_obj_center(label);

    /*Set opacity
     *The button and the label is rendered to a layer first and that layer is blended*/
    btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, 100, 40);
    lv_obj_set_style_opa(btn, LV_OPA_50, 0);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

    label = lv_label_create(btn);
    lv_label_set_text(label, "Opa:50%");
    lv_obj_center(label);

    /*Set transformations
     *The button and the label is rendered to a layer first and that layer is transformed*/
    btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, 100, 100);
    // lv_obj_set_style_transform_angle(btn, 150, 0);        /*15 deg*/
    lv_obj_set_style_transform_zoom(btn, 128, 0);   /*1.25x*/
    lv_obj_set_style_transform_pivot_x(btn, 50, 0);
    lv_obj_set_style_transform_pivot_y(btn, 20, 0);
    // lv_obj_set_style_opa(btn, LV_OPA_50, 0);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 70);

    label = lv_label_create(btn);
    lv_label_set_text(label, "Transf.");
    lv_obj_center(label);

    lv_obj_t * cursor_obj = lv_img_create(btn); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, "81");   
    lv_obj_set_size(cursor_obj,20,20);
     lv_obj_align(cursor_obj, LV_ALIGN_CENTER, 0, 0);  
    
}

#endif
