#ifndef __Multilingual__
#define __Multilingual__

#include "lvgl.h"

enum{
	M_CHINESE_SIMPLIFIED,   // 简体中文
	M_CHINESE_TRANSDITION,  // 繁体中文
	M_ENGLISH,              // 英语
	M_JAPANESE,             // 日语
	M_KOREAN,               // 韩语
	M_FRENCH,               // 法语
	M_GERMEN,               // 德语
	M_RUSSIAN,              // 俄语
	M_SPANISH,              // 西班牙语
	M_PORTUGUESE,           // 葡萄牙语
	M_GREEK,                // 希腊语
	M_DUTCH,                // 荷兰语
	M_POLISH,               // 波兰语
	M_DANISH,               // 丹麦语
	M_ARABIC,               // 阿拉伯语
    MULT_MAX
};

//  多国语言文字重映射
void multilingual_text_remap(char ** strptr);

//  多国语言图片重映射
void multilingual_pic_remap(void ** picptr);

//  多国语言设置
int lv_set_language(int in);

//  多国语言获取
int lv_get_language();

//  多国语言重映射使能
void multilingual_remap_enable(unsigned char on);

#endif