#ifndef __SD_MUSIC_API_H_
#define __SD_MUSIC_API_H_

#include "lvgl.h"
#include <string.h>

/**************************************模块说明***********************************************/
/**
 * 使用时需要构建一个struct music_file的示例music_files对象用于保存文件信息
 * 通过open_file_handler去加载当前目录信息并保存到music_files里，此时可以通过 音乐文件信息获取接口 去
 * 获取对应文件信息，使用结束后通过file_free或free_file_handler释放资源
*/
/**************************************模块说明***********************************************/

/**************************************注意事项***********************************************/
/**
* MAX_FILE_NUM 越大，支持同时显示的文件越多
* MAX_MUSIC_NAME_LEN 越大，支持的最大文件名越长
* 但占用内存越大，因为需要动态申请空间用来保留目录信息，用户需要自行衡量
*/
/**************************************注意事项***********************************************/

// 支持同时显示的最大音乐文件数量
#define MAX_MUSIC_FILE_NUM  100

// 音乐文件名最大字符长度
#define MAX_MUSIC_NAME_LEN  64

// 支持同时显示的最大文件数量
#define MAX_FILE_NUM    MAX_MUSIC_FILE_NUM

// 文件名最大字符长度
#define MAX_NAME_LEN    MAX_MUSIC_NAME_LEN

// 目录类型
#define DIR_TYPE_FOLDER     4
// 文件类型
#define DIR_TYPE_FILE       2

struct music_file {
    u32 clust;   // 音乐文件簇号
    char *name;  // 音乐文件名
    int index;   // 文件索引
    u8 dir_type; // 目录类型，0: folder， 2：file
};

// utf16转utf8接口
extern int Unicode2UTF8(char *utf8_buf, u16 *pUniBuf, int uni_len);

// 获取设备数
extern u32 dev_manager_get_total(u8 valid);

/*******************************音乐文件信息获取接口*****************************************/

/**
 * @brief 根据id获取音乐文件名
 * 
 * @param id 文件id
 * @return char* 文件名
 */
char *get_music_file_title_by_id(int id);

/**
 * @brief 根据id获取音乐文件簇号
 * 
 * @param id 文件id
 * @return u32 簇号
 */
u32 get_music_file_clust_by_id(int id);

/**
 * @brief 根据id获取文件类型，是文件还是目录
 * 
 * @param id 文件id
 * @return u8 0为目录，2为文件
 */
u8 get_music_file_dir_type_by_id(int id);
/*******************************音乐文件信息获取接口*****************************************/

/*************************************工具函数**********************************************/
/**
 * @brief 路径合并，将dst_path和sub_path合并，并保存到dst_path
 * 
 * @param dst_path 目标路径
 * @param sub_path 子路径
 */
void path_merge(char *dst_path, const char* sub_path);

/**
 * @brief 路径拆解，将dst_path里面的sub_path去掉，并保存到dst_path
 * 
 * @param dst_path 目标路径
 * @param sub_path 子路径
 */
void path_split(char *dst_path, const char* sub_path);

/**
 * @brief 路径退级，退到上一级路径并保存到dst_path
 * 
 * @param dst_path 目标路径
 */
void path_exit(char *dst_path);
/*************************************工具函数**********************************************/

/**********************************文件操作接口*********************************************/

/**
 * @brief 文件资源全部释放，完整遍历数组释放资源
 * 
 */
static void file_free();

/**
 * @brief 打印文件路径信息，把当前路径下的文件id，簇号和名字打印出来
 * 
 * @param path 输入路径
 * @param arg 扫盘参数
 */
static void show_file_info(const char *path, const char *arg);

/**
 * @brief 打开文件路径，并将当前路径下的文件id，簇号和名字保存到数组
 * 
 * @param path 文件路径
 * @param arg 扫盘参数
 * @return int 返回当前路径下的文件数量，大于等于0为正常，-1则表示打开路径失败
 */
static int open_file_handler(const char *path, const char *arg);

/**
 * @brief 释放当前路径使用到的资源
 * 
 * @param path 文件路径
 * @param arg 扫盘参数
 */
static void free_file_handler(const char *path, const char *arg);
/**********************************文件操作接口*********************************************/

/********************************音乐文件操作接口*******************************************/

/**
 * @brief 判断SD卡是否在线
 * 
 * @return u8 0：不在线  1：在线
 */
u8 is_sd_card_online();

/**
 * @brief 音乐数组清零（仅清空本地数组）
 * 
 */
void music_data_reset();

/**
 * @brief 音乐文件重置（包括清空本地数组和释放资源）
 * 
 */
void music_files_reset();

/**
 * @brief 打印音乐文件信息
 * 
 */
void show_music_file_info();

/**
 * @brief 打开sd音乐根目录
 * 
 * @return int 返回当前路径下的音乐文件数量，大于等于0为正常，-1则表示打开路径失败
 */
int open_music_file_handler();

/**
 * @brief 根据路径打开音乐文件
 * 
 * @param path 输入路径
 * @return int 返回输入路径下的音乐文件数量，大于等于0为正常，-1则表示打开路径失败
 */
int open_music_file_by_path(const char *path);

/**
 * @brief 释放sd根目录使用到的文件资源
 * 
 */
void free_music_file_handler();

/**
 * @brief 释放指定路径下使用到的文件资源
 * 
 * @param path 输入路径
 */
void free_music_file_by_path(const char *path);
/********************************音乐文件操作接口*******************************************/


#endif /* __SD_MUSIC_API_H_ */