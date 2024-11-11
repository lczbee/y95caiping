#include "encode_write.h"
#include "file_operate/file_bs_deal.h"
#include "audio_enc.h"
#include "media/audio_base.h"
#include "dev_manager.h"
#include "app_config.h"
#include "res/resfile.h"
#include "lvgl.h"
#include "music/music_player.h"
#include "music/music.h"
#include "app_task.h"
#include "key_event_deal.h"
#include "sd_music_api.h"

/*****************debug********************/
// log debug宏
#define SD_MUSIC_DEBUG_EN               0

#if SD_MUSIC_DEBUG_EN
#define SD_MUSIC_DEBUG          printf
#define SD_MUSIC_MALLOC_DEBUG   n_printf
#define SD_MUSIC_FREE_DEBUG     p_printf
#else
#define SD_MUSIC_DEBUG(...)
#define SD_MUSIC_MALLOC_DEBUG(...)
#define SD_MUSIC_FREE_DEBUG(...)
#endif
/*****************debug********************/

// 扫盘参数，按文件顺序扫描所有MP3、WAV、WMA文件，包括文件夹
static const u8 FILE_SCAN_PARAM[] = "-t"
                                    "MP1MP2MP3 WAV WMA"
                                    "-d"
                                    "-sn"
                                    ;

// sd卡根目录
static char *ROOT_PATH = "storage/sd0/C/";

/*************************************工具函数**********************************************/
// 路径合并
void path_merge(char *dst_path, const char* sub_path) 
{
    if (dst_path == NULL || sub_path == NULL || sub_path == '\0') {
        SD_MUSIC_DEBUG("[SD MUSIC] input path is null, func: %s, line: %d", __func__, __LINE__);
        return;
    }

    if (strlen(dst_path) + strlen(sub_path) > MAX_NAME_LEN * 2) {
        SD_MUSIC_DEBUG("[SD MUSIC] len err! func: %s, line: %d", __func__, __LINE__);
        return;
    }
    // 将子路径sub_path拼接到dst_path后
    strcat(dst_path, sub_path);
    // dst_path后必须加"/"，不然使用文件系统的接口会直接死机
    strcat(dst_path, "/");
}

// 路径拆分
void path_split(char *dst_path, const char* sub_path) 
{
    if (dst_path == NULL || sub_path == NULL || sub_path == '\0') {
        SD_MUSIC_DEBUG("[SD MUSIC] input path is null, func: %s, line: %d", __func__, __LINE__);
        return;
    }

    if (strlen(dst_path) > MAX_NAME_LEN * 2) {
        SD_MUSIC_DEBUG("[SD MUSIC] len err! func: %s, line: %d", __func__, __LINE__);
        return;
    }
    char* sub = strstr(dst_path, sub_path); // 查找子路径的位置
    if (sub != NULL) {
        u8 len = strlen(dst_path);
        memmove(sub, sub + len, strlen(sub + len) + 1); // 移除子路径
    }
}

// 路径退级
void path_exit(char *dst_path)
{
    if (strlen(dst_path) > MAX_NAME_LEN * 2) {
        SD_MUSIC_DEBUG("[SD MUSIC] len err! func: %s, line: %d", __func__, __LINE__);
        return;
    }

    char *last_slash = NULL;
    char *second_last_slash = NULL;

    // 查找最后一个"/"
    last_slash = strrchr(dst_path, '/');
    /* SD_MUSIC_DEBUG("last_slash: %s, %x, %d", last_slash, last_slash, last_slash - dst_path); */
    if (last_slash == NULL)
    {
        SD_MUSIC_DEBUG("[SD MUSIC] last_slash is null");
        return;
    }

    // 去掉第一个"/"以后的内容
    *(last_slash) = '\0';

    /* SD_MUSIC_DEBUG("last_slash: %s", last_slash); */

    second_last_slash = strrchr(dst_path, '/');

    if (second_last_slash == NULL)
    {
        SD_MUSIC_DEBUG("[SD MUSIC] second_last_slash is null");
        return;
    }

    // 去掉倒数第二个"/"以后的内容
    *(second_last_slash + 1) = '\0';
    /* SD_MUSIC_DEBUG("dst_path: %s", dst_path); */
}
/*************************************工具函数**********************************************/


// 音乐文件数组，存储文件的id，名字和路径
static struct music_file music_files[MAX_FILE_NUM] = {0};


/*******************************音乐文件信息获取接口*****************************************/
// 根据id获取音乐文件名
char *get_music_file_title_by_id(int id)
{
    if (id >= sizeof(music_files) / sizeof(music_files[0])) {
        SD_MUSIC_DEBUG("[SD MUSIC] id err, func: %s, line: %d", __func__, __LINE__);
        return NULL;
    }
        return music_files[id].name;
}

// 根据id获取音乐文件簇号
u32 get_music_file_clust_by_id(int id)
{
    if (id >= sizeof(music_files) / sizeof(music_files[0])) {
        SD_MUSIC_DEBUG("[SD MUSIC] id err, func: %s, line: %d", __func__, __LINE__);
        return NULL;
    }
    return music_files[id].clust;
}

// 根据id获取文件类型，是文件还是目录
u8 get_music_file_dir_type_by_id(int id)
{
    if(id >= sizeof(music_files) / sizeof(music_files[0])) {
        SD_MUSIC_DEBUG("[SD MUSIC] id err, func: %s, line: %d", __func__, __LINE__);
        return NULL;
    }
    return music_files[id].dir_type;
}
/*******************************音乐文件信息获取接口*****************************************/


/**********************************文件操作接口*********************************************/
// 文件资源全部释放
static void file_free()
{
    for(int i = 0; i < MAX_FILE_NUM; i++) {
        if(music_files[i].name != NULL) {
            SD_MUSIC_FREE_DEBUG("[SD MUSIC] free id: %d, addr: 0x%x", i, music_files[i].name);
            free(music_files[i].name);
            music_files[i].name = NULL;
        }
    }
}

// 打印文件信息
static void show_file_info(const char *path, const char *arg)
{
    if(is_sd_card_online() == 0) {
        SD_MUSIC_DEBUG("[SD MUSIC] sd card is not online");
        return;
    }

    struct vfscan *fs = NULL;
    fs = fscan(path, arg, 1);
    if(fs == NULL)
    {
        SD_MUSIC_DEBUG("[SD MUSIC] fs is null");
        // fscan_release(fs);
        // fs = NULL;
        return;
    }
    int file_num = fs->file_number;

    for(int i = 0; i < file_num; i++) {
        SD_MUSIC_DEBUG("[SD MUSIC] id: %d, name: %s, clust: %d, dir_type: %d", music_files[i].index, music_files[i].name, music_files[i].clust, music_files[i].dir_type);
    }
    fscan_release(fs);
    fs = NULL;
}

// 打开文件
static int open_file_handler(const char *path, const char *arg)
{
    if(is_sd_card_online() == 0) {
        SD_MUSIC_DEBUG("[SD MUSIC] sd card is not online");
        return -1;
    }

    struct vfscan *fs = NULL;
    u16 name[MAX_NAME_LEN];
    u16 name_unicode[MAX_NAME_LEN];
    char name_utf8[MAX_NAME_LEN * 2];
    struct vfs_attr attr = {0};
    FILE * fp = NULL;
    int file_num = 0;
    
    // 扫盘
    fs = fscan(path, FILE_SCAN_PARAM, 1);

    if(fs == NULL)
    {
        SD_MUSIC_DEBUG("[SD MUSIC] fs is null, please check the path");
        return -1 ;
    }

    SD_MUSIC_DEBUG("[SD MUSIC] fscan: file_number = %d\n", fs->file_number);

    if (fs->file_number == 0) { //判断是否有被扫描格式文件存在
        SD_MUSIC_DEBUG("[SD MUSIC] there is no file in this path");
        fscan_release(fs);
        fs = NULL;
        return 0 ;
    }

    // 限制当前路径下最大文件个数
    if(fs->file_number > MAX_FILE_NUM) {
        fs->file_number = MAX_FILE_NUM;
    }

    file_num = fs->file_number;

    // 释放动态申请的文件资源
    file_free();

    // 遍历整个文件夹
    for(int i = 0; i < fs->file_number; i++)
    {
        // 通过文件号选择文件，其中文件号从1开始
        fp = fselect(fs, FSEL_BY_NUMBER, i + 1);
        if(fp)
        {
            // 获取文件名
            fget_name(fp, name, sizeof(name));
            /* put_buf(name,sizeof(name)); */
            /* r_printf("name[0] >> 8: 0x%x, name[0] & 0xff: 0x%x", name[0] >> 8, name[0] & 0xff); */
            /* put_buf(name, sizeof(name[0])); */
            music_files[i].index = i; // 记录文件id

            // 为文件名动态申请内存
            if(music_files[i].name == NULL) {
                music_files[i].name = zalloc(sizeof(char) * MAX_NAME_LEN * 2);
                SD_MUSIC_MALLOC_DEBUG("[SD MUSIC] malloc id: %d, addr: 0x%x", i, music_files[i].name);
            }

            // 申请不到内存
            if(music_files[i].name == NULL) {
                mem_stats();
                SD_MUSIC_DEBUG("[SD MUSIC] id: %d malloc fail!");
                SD_MUSIC_DEBUG("[SD MUSIC] real file num is %d", file_num);
                file_num = i + 1;
                SD_MUSIC_DEBUG("[SD MUSIC] return file num is %d", file_num);
                break;
            }

            // 获取文件信息
            fget_attrs(fp, &attr);

            // 根据文件名前两个字节判断是长文件名还是短文件名，文件系统返回长文件名使用的是utf16编码
            if((name[0] & 0xff) == 0x5C && (name[0] >> 8) == 0x55) {
                // 长文件名(以5c 55开头，也就是"/u")
                memcpy(name_unicode, name + 1, sizeof(name) - sizeof(name[0]));
                /* SD_MUSIC_DEBUG("unicode: "); */
                /* put_buf(name_unicode,sizeof(name_unicode)); */

                // 转换为utf8编码
                Unicode2UTF8(name_utf8, name_unicode, sizeof(name_unicode));
                /* SD_MUSIC_DEBUG("utf8: "); */
                /* put_buf(name_utf8,sizeof(name_utf8)); */

                SD_MUSIC_DEBUG("[SD MUSIC] fscan: attr.sclust = %d, long_file_name = %s, attr = %d, id = %d\n", attr.sclust, name_utf8, attr.attr, i);
                memcpy(music_files[i].name, name_utf8, sizeof(name_utf8));
            } else {
                // 短文件名
                SD_MUSIC_DEBUG("[SD MUSIC] fscan: attr.sclust = %d, short_file_name = %s, attr = %d, id = %d\n", attr.sclust, name, attr.attr, i);
                // 短文件名直接保存
                memcpy(music_files[i].name, name, sizeof(name));
            }

            music_files[i].clust = attr.sclust; //记录文件簇号
            music_files[i].dir_type = attr.attr;//记录目录类型
            
            u8 buf[16] ={0};
            fread(fp, buf , 16);
            // put_buf(buf, 16);

        }
        
        fclose(fp);
        fp = NULL; 
                   
    }
    fscan_release(fs);
    fs = NULL;
    return file_num;
}

// 释放使用到的文件资源
static void free_file_handler(const char *path, const char *arg)
{

    if(is_sd_card_online() == 0) {
        SD_MUSIC_DEBUG("[SD MUSIC] sd card is not online");
        return;
    }

    struct vfscan *fs = NULL;
    
    FILE * fp = NULL;
    int file_num = 0;
    
    fs = fscan(path, arg, 1);
    if(fs == NULL)
    {
        SD_MUSIC_DEBUG("[SD MUSIC] fs is null");
        // fscan_release(fs);
        // fs = NULL;
        return;
    }
    SD_MUSIC_DEBUG("[SD MUSIC] fscan: file_number = %d\n", fs->file_number);

    file_num = fs->file_number;
    for(int i = 0; i < file_num; i++) {
        if(music_files[i].name != NULL) {
            free(music_files[i].name);
            music_files[i].name = NULL;
        }
    }

    fscan_release(fs);
    fs = NULL;
}

/**********************************文件操作接口*********************************************/


/********************************音乐文件操作接口*******************************************/
// 判断SD卡是否在线
u8 is_sd_card_online()
{
    if (!dev_manager_get_total(1)) {
        SD_MUSIC_DEBUG("[SD MUSIC] there is on online dev");
        return 0;
    }
    return 1;
}

// 音乐数组清零
void music_data_reset()
{
    memset(music_files, 0, sizeof(music_files)); // 数组清零
}

// 音乐文件重置
void music_files_reset()
{
    file_free(); //释放资源
    music_data_reset();
}

// 打印音乐文件信息
void show_music_file_info()
{
    show_file_info(ROOT_PATH, FILE_SCAN_PARAM);
}

// 打开sd音乐根目录
int open_music_file_handler()
{
    int music_file_num = 0;
    music_file_num = open_file_handler(ROOT_PATH, FILE_SCAN_PARAM);

    return music_file_num;
}

// 根据路径打开音乐文件
int open_music_file_by_path(const char *path)
{
    int music_file_num = 0;
    music_file_num = open_file_handler(path, FILE_SCAN_PARAM);

    return music_file_num;
}

// 释放sd根目录使用到的文件资源
void free_music_file_handler()
{
    free_file_handler(ROOT_PATH, FILE_SCAN_PARAM);
}

// 释放指定路径下使用到的文件资源
void free_music_file_by_path(const char *path)
{
    free_file_handler(path, FILE_SCAN_PARAM);
}

/********************************音乐文件操作接口*******************************************/

