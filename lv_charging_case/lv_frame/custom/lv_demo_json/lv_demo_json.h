#ifndef __lvdemo_json__
#define __lvdemo_json__

#include "cJSON.h"
#include "cpu.h"
#include "res/resfile.h"

// 读取JSON配置文件
cJSON* read_config(const char* filename) ;
   

// 保存JSON配置文件
void save_config(const char* filename, cJSON* root);





#endif