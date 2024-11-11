
#include "usr_pic_index.h"
const struct Idex use_img_index[1] = {
    {.name="/temp1.gif", .id=1,},
};
#include "cpu.h"
AT(.lvgl_ram) int NAME2ID(char* src){
    // extern const struct Idex use_img_index[];
    int i;
    sizeof(struct Idex);
    sizeof(use_img_index[0]);
    for(i=0;i<ARRAY_SIZE(use_img_index);i++){
        if(strcmp(src, use_img_index[i].name)==0){
            return use_img_index[i].id;
        }
    }
    printf("FIND ERROR");
    return 0;
}
