#include "encode_write.h"
#include "file_operate/file_bs_deal.h"
#include "audio_enc.h"
#include "media/audio_base.h"
#include "dev_manager.h"
#include "app_config.h"
#include "spi/nor_fs.h"
#include "rec_nor/nor_interface.h"
#include "res/resfile.h"
#include "lvgl.h"
struct animing_head {
    char fname[8];  //  动画前缀名
    u32 num;        //  动画总数
    u32 duration;   //  间隔周期
};

struct animing_table{
    struct animing_head head;   //  动画信息头
    void * file;                //  动画文件句柄
    struct flash_file_info table;               //  动画文件table
    void * animing_src_ptr;     //  动画索引数组的二级指针
    void * animing_src_str;     //  动画索引字符串缓存区指针
};

#define MAX_ANIMING_NUM 36
struct animing_table usr_animing_table[MAX_ANIMING_NUM];
int all_usr_animing_table = 0;

static int get_photo_num()
{
    int i;
    for(i=0;i<MAX_ANIMING_NUM;i++){
        memset(&usr_animing_table[i].head, 0, sizeof(struct animing_head));

        if(usr_animing_table[i].file){
            res_fclose(usr_animing_table[i].file);
            usr_animing_table[i].file = NULL;
            ui_res_flash_info_free(&usr_animing_table[i].table, "res");
        }

        if(usr_animing_table[i].animing_src_ptr){
            free(usr_animing_table[i].animing_src_ptr);
            usr_animing_table[i].animing_src_ptr = NULL;
        }
        if(usr_animing_table[i].animing_src_str){
            free(usr_animing_table[i].animing_src_str);
            usr_animing_table[i].animing_src_str = NULL;
        }
    }

    struct vfscan *fs = NULL;
    char  name[128];
    struct vfs_attr attr = {0};
    FILE * fp = NULL;
    char * root_path = "storage/virfat_flash/C/";
    
    fs = fscan(root_path, "-tALL -sn", 2);
    if(fs == NULL)
    {
        printf("fscan end");
        return -1 ;
    }
    printf("fscan: file_number = %d\n", fs->file_number);
    if (fs->file_number == 0) { //判断是否有被扫描格式文件存在
        printf("Please create some test files!");
        return 0 ;
    }
    //遍历整个文件夹
    for(int i=1;i <= fs->file_number;i++)
    {
        //通过文件号选择文件
        fp = fselect(fs,FSEL_BY_NUMBER,i);
        if(fp)
        {
            fget_name(fp,name,sizeof(name));
            fget_attrs(fp, &attr);
            printf("fscan: attr.sclust = %d, file_name = %s\n", attr.sclust, name);
            
            u8 buf[16] ={0};
            fread(fp, buf , 16);
            put_buf(buf, 16);

        }
        
        fclose(fp);
        fp = NULL; 
                   
        char str[64] = {0};
        sprintf(str, "%s%s/%s.bin",root_path,name,name);
        // printf(">>>>>>>>>>>>>>.%s",str);
        fp = fopen(str, "r");
        if(fp){
            struct animing_head head ={0};
            fread(fp, &head , sizeof(head));
            put_buf(&head, sizeof(head));
            fclose(fp);
            memcpy(
                &usr_animing_table[all_usr_animing_table].head.fname[0],
                &head,
                sizeof(head)
            );
            printf("加载%s",&usr_animing_table[all_usr_animing_table].head.fname[0]);
            

            memset(str, 0, sizeof(str));
            sprintf(str, "%s%s/%s.res",root_path,name,name);
            usr_animing_table[all_usr_animing_table].file = res_fopen(str, "r");
            ui_res_flash_info_get(&usr_animing_table[all_usr_animing_table].table, str, "res");
            
            usr_animing_table[all_usr_animing_table].animing_src_ptr = zalloc(4*head.num);
            
        
            memset(str, 0, sizeof(str));
            sprintf(str, "B:%s/000",name);
            usr_animing_table[all_usr_animing_table].animing_src_str = zalloc(head.num*(strlen(str)+1));
            int *ptr = usr_animing_table[all_usr_animing_table].animing_src_ptr;
            u8 *sstr = usr_animing_table[all_usr_animing_table].animing_src_str;
            u8 len = strlen(str)+1;
            printf("LLLL %d", len);

            for(u8 k = 0;k<head.num;k++){
                memset(&sstr[k*len], 0, len);
                sprintf(&sstr[k*len], "B:%s/%03d",name, k+1);
                ptr[k] = &sstr[k*len];
            }

            printf("name:%s",name);
            put_buf(usr_animing_table[all_usr_animing_table].animing_src_ptr, 
            usr_animing_table[all_usr_animing_table].head.num*4);   

            for(u8 j=0;j<usr_animing_table[all_usr_animing_table].head.num;j++){
                printf("-----%s", ((int*)(usr_animing_table[all_usr_animing_table].animing_src_ptr))[j]);
            }
            
            //  释放
            if(usr_animing_table[all_usr_animing_table].file){
                res_fclose(usr_animing_table[all_usr_animing_table].file);
                usr_animing_table[all_usr_animing_table].file = NULL;
                ui_res_flash_info_free(&usr_animing_table[all_usr_animing_table].table, "res");
            }
            if(usr_animing_table[all_usr_animing_table].animing_src_ptr){
                free(usr_animing_table[all_usr_animing_table].animing_src_ptr);
                usr_animing_table[all_usr_animing_table].animing_src_ptr = NULL;
            }
            if(usr_animing_table[all_usr_animing_table].animing_src_str){
                free(usr_animing_table[all_usr_animing_table].animing_src_str);
                usr_animing_table[all_usr_animing_table].animing_src_str = NULL;
            }

            // put_buf(usr_animing_table[all_usr_animing_table].animing_src_src, ) 

            all_usr_animing_table++;
            if(all_usr_animing_table >= MAX_ANIMING_NUM) {
				printf("动画文件数 越界。。。。。。");
				ASSERT(0);
                break;
            }
        }
    }
    fscan_release(fs);
    fs = NULL;
    return fs->file_number;
}

void usr_get_animing_info(char * src, void ** p, void ** table, int *id);


void open_animing_res(){
    get_photo_num();

    void * p = NULL;
    void *table = NULL;
    int id = 0;
    usr_get_animing_info("PO/123", &p, &table, &id);
    // printf("table:%x id:%d", p, id);
}


void usr_update_animing(lv_obj_t * obj, char *res_name)
{
    lv_animimg_t * animimg = (lv_animimg_t *)obj; 
    if(strcmp("RES", lv_fs_get_ext(res_name))==0){
        lv_anim_del(obj, NULL);
        lv_animimg_set_src(obj, NULL, 0);
        lv_animimg_set_duration(obj, 0);
        // lv_animimg_set_repeat_count(obj, 0);

        // animimg->img.src = res_name;

        lv_img_set_src(obj, res_name);
        return;  
    }

    if(animimg->img.src) {
        lv_mem_free((void *)animimg->img.src);
        animimg->img.src = NULL;
    }
    
    printf("func: %s, line: %d, res_name: %s, animimg: 0x%x", __func__, __LINE__, res_name, animimg);
	if(res_name == NULL) return;
    int i;
    for(i =0; i<all_usr_animing_table; i++ ){
        if(strcmp(res_name, usr_animing_table[i].head.fname)==0){

            if(!usr_animing_table[i].file){
                printf("加载%s", &usr_animing_table[i].head.fname[0]);
                char str[64] = {0};
                char * root_path = "storage/virfat_flash/C/";
                memset(str, 0, sizeof(str));
                sprintf(str, "%s%s/%s.res",root_path,res_name,res_name);

                char str2[64] = {0};
                memset(str2, 0, sizeof(str2));
                sprintf(str2, "%s%s", root_path, "BGP_1");

                void * newf = res_fopen(str2, "r");
                if(strcmp(res_name, "BG1")==0 && newf){
                    usr_animing_table[i].file = newf;
                    ui_res_flash_info_get(&usr_animing_table[i].table, str2, "res");
                }
                else{
                    usr_animing_table[i].file = res_fopen(str, "r");
                    ui_res_flash_info_get(&usr_animing_table[i].table, str, "res");
                }
                
                usr_animing_table[i].animing_src_ptr = zalloc(4*usr_animing_table[i].head.num);
                // printf("ptr[%d] zalloc: addr is 0x%x, size is %d", i, usr_animing_table[i].animing_src_ptr, 4*usr_animing_table[i].head.num);
                memset(str, 0, sizeof(str));
                sprintf(str, "B:%s/000",res_name);
                usr_animing_table[i].animing_src_str = zalloc(usr_animing_table[i].head.num*(strlen(str)+1));
                // printf("str[%d] zalloc: addr is 0x%x, size is %d", i, usr_animing_table[i].animing_src_str, usr_animing_table[i].head.num*(strlen(str)+1));
                int *ptr = usr_animing_table[i].animing_src_ptr;
                u8 *sstr = usr_animing_table[i].animing_src_str;
                u8 len = strlen(str)+1;
                printf("LLLL %d", len);

                if(!(strcmp(res_name, "BG1")==0 && newf)){
                    for(u8 k = 0;k<usr_animing_table[i].head.num;k++){
                        memset(&sstr[k*len], 0, len);
                        sprintf(&sstr[k*len], "B:%s/%03d",res_name, k+1);
                        ptr[k] = &sstr[k*len];
                    }
                } else {
                    u8 k = 0;
                    memset(&sstr[k*len], 0, len);
                        sprintf(&sstr[k*len], "B:%s/%03d",res_name, 1);
                        ptr[k] = &sstr[k*len];
                }


                printf("name:%s",res_name);
                put_buf(usr_animing_table[i].animing_src_ptr, 
                usr_animing_table[i].head.num*4);   

                for(u8 j=0;j<usr_animing_table[i].head.num;j++){
                    printf("-----%s", ((int*)(usr_animing_table[i].animing_src_ptr))[j]);
                }
            }
            
            lv_animimg_set_src(animimg, 
                usr_animing_table[i].animing_src_ptr, 
                usr_animing_table[i].head.num);
            lv_animimg_set_duration(animimg, 
            usr_animing_table[i].head.num*usr_animing_table[i].head.duration);
            printf("num %d dur %d",usr_animing_table[i].head.num,
            usr_animing_table[i].head.duration?usr_animing_table[i].head.duration:100);
            if(usr_animing_table[i].head.num == 1){
                lv_animimg_set_repeat_count(animimg, 1);
            }
            // if(animimg->dsc) {
            //     lv_img_set_src(obj, animimg->dsc[0]);
            // }
            b_printf("anim num: %d, repeat num: %d", animimg->pic_count, animimg->anim.repeat_cnt);
            break;
        }
    }
}

void usr_free_animing(lv_obj_t * obj, void * orisrc, u8 num, int duration, u16 repeat_count){
    
    lv_animimg_t * animimg2 = (lv_animimg_t *)obj;
    if(animimg2->img.src){
        if(strcmp("RES", lv_fs_get_ext(animimg2->img.src))==0){
            lv_img_cache_invalidate_src(animimg2->img.src);
        }         
        return;
    }
   
    
    printf("func: %s, line: %d, animimg: 0x%x", __func__, __LINE__, obj);
    lv_animimg_t * animimg = (lv_animimg_t *)obj;  
    int i;
    for(i =0; i<all_usr_animing_table; i++ ){
        if(animimg->dsc == usr_animing_table[i].animing_src_ptr){
            lv_animimg_set_src(obj, orisrc, num);
            lv_animimg_set_duration(obj, duration);
            lv_animimg_set_repeat_count(obj, repeat_count);
            lv_animimg_start(obj); // 重载动画控件
            
            //  释放
            if(usr_animing_table[i].file){
                res_fclose(usr_animing_table[i].file);
                usr_animing_table[i].file = NULL;
                ui_res_flash_info_free(&usr_animing_table[i].table, "res");
            }
            if(usr_animing_table[i].animing_src_ptr){
                // printf("ptr[%d] free: addr is 0x%x", i, usr_animing_table[i].animing_src_ptr);
                free(usr_animing_table[i].animing_src_ptr);
                usr_animing_table[i].animing_src_ptr = NULL;
            }
            if(usr_animing_table[i].animing_src_str){
                // printf("str[%d] free: addr is 0x%x", i, usr_animing_table[i].animing_src_str);
                free(usr_animing_table[i].animing_src_str);
                usr_animing_table[i].animing_src_str = NULL;
            }
        }
    }
}

static int A2I(char* str) {
    int result = 0;
    int i = 0;

    // 逐个字符进行转换
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result;
}
void usr_get_animing_info(char * src, void ** p, void ** table, int *id){
    char extracted[9] = {0};
    
    // 查找第一个斜杠的位置
   char * slash = strchr(src, '/');
    
    // 计算提取的字符串的长度
    int length = slash - src;
    
    char * id_str = src + length + 1;
    

    // 复制提取的字符串到新的数组中
    strncpy(extracted, src, length);
    extracted[length] = '\0';
    
    // printf("pre %s id_str %s", extracted, id_str);

    int i;
    for(i =0; i<all_usr_animing_table; i++ ){
        // printf(">>%s", &usr_animing_table[i].head.fname[0]);
        if(strcmp(extracted, &usr_animing_table[i].head.fname)==0){
            
            *p = usr_animing_table[i].file;
            *table = &usr_animing_table[i].table;
            *id = A2I(id_str);
            if(*id > usr_animing_table[i].head.num){
                *id = usr_animing_table[i].head.num;
            }
            break;
        }
    }
}


void usr_update_state_img(char *res_name){
    int i;
    for(i =0; i<all_usr_animing_table; i++ ){
        if(strcmp(res_name, usr_animing_table[i].head.fname)==0){

            if(!usr_animing_table[i].file){
                printf("加载%s", &usr_animing_table[i].head.fname[0]);
                char str[64] = {0};
                char * root_path = "storage/virfat_flash/C/";
                memset(str, 0, sizeof(str));
                sprintf(str, "%s%s/%s.res",root_path,res_name,res_name);
                usr_animing_table[i].file = res_fopen(str, "r");
                ui_res_flash_info_get(&usr_animing_table[i].table, str, "res");
                usr_animing_table[i].animing_src_ptr = zalloc(4*usr_animing_table[i].head.num);
                memset(str, 0, sizeof(str));
                sprintf(str, "B:%s/000",res_name);
                usr_animing_table[i].animing_src_str = zalloc(usr_animing_table[i].head.num*(strlen(str)+1));
                int *ptr = usr_animing_table[i].animing_src_ptr;
                u8 *sstr = usr_animing_table[i].animing_src_str;
                u8 len = strlen(str)+1;
                printf("LLLL %d", len);

                for(u8 k = 0;k<usr_animing_table[i].head.num;k++){
                    memset(&sstr[k*len], 0, len);
                    sprintf(&sstr[k*len], "B:%s/%03d",res_name, k+1);
                    ptr[k] = &sstr[k*len];
                }

                printf("name:%s",res_name);
                put_buf(usr_animing_table[i].animing_src_ptr, 
                usr_animing_table[i].head.num*4);   

                for(u8 j=0;j<usr_animing_table[i].head.num;j++){
                    printf("-----%s", ((int*)(usr_animing_table[i].animing_src_ptr))[j]);
                }
            }
            return;
            break;
        }
    }
}

void * get_state_img_src(char *res_name, u8 idx){
    int i;
    for(i =0; i<all_usr_animing_table; i++ ){
        if(strcmp(res_name, usr_animing_table[i].head.fname)==0){
            if(usr_animing_table[i].animing_src_ptr == NULL){
                printf("索引缓存 无效!!!!");
                return NULL;
            }
            void ** img = usr_animing_table[i].animing_src_ptr;

            if(usr_animing_table[i].head.num <= idx){
                printf("索引值 %d 越界，设置失败!!!!", idx);
                return NULL;
            }

            printf("图像索引切换为：%s", img[idx]);
            return img[idx];
        }
    }
    return NULL;
}
            


void usr_free_state_img(char *res_name){
    int i;
    for(i =0; i<all_usr_animing_table; i++ ){
        if(strcmp(res_name, usr_animing_table[i].head.fname)==0){
            //  释放
            if(usr_animing_table[i].file){
                res_fclose(usr_animing_table[i].file);
                usr_animing_table[i].file = NULL;
                ui_res_flash_info_free(&usr_animing_table[i].table, "res");
            }
            if(usr_animing_table[i].animing_src_ptr){
                free(usr_animing_table[i].animing_src_ptr);
                usr_animing_table[i].animing_src_ptr = NULL;
            }
            if(usr_animing_table[i].animing_src_str){
                free(usr_animing_table[i].animing_src_str);
                usr_animing_table[i].animing_src_str = NULL;
            }
        }
    }
}




