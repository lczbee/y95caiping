#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "cpu.h"
#include "res/resfile.h"

// 读取JSON配置文件
cJSON* read_config(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    // fseek(file, 0, SEEK_END);
    long length = flen(file);
    // fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(length + 1);
    if(!data){
        printf("Error malloc fail");
        fclose(file);
        return NULL;
    }


    fread(file, data, length);
    data[length] = '\0';

    printf("read_config %s", data);

    fclose(file);

    cJSON* root = cJSON_Parse(data);
    if(!root){
        printf("Error cJSON_Parse fail");
        free(data);
        return NULL;
    }

    free(data);

    return root;
}

// 保存JSON配置文件
void save_config(const char* filename, cJSON* root) {
    FILE* file = fopen(filename, "w+");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    char* data = cJSON_Print(root);
    printf("save_config %s",data);
    if(!data) {
        printf("Error cJSON_Print fail");
        fclose(file);
        return;
    }

    fwrite(file, data, strlen(data));
    fclose(file);
    free(data);
}


#define CONFIG_NAME "storage/virfat_flash/C/cpc.jsn"
#define DEF_LOCK_NAME   "ANI3.RES"

static char selectwallpername[64];

static void set_config_default(cJSON* config){
    printf("set json def");
    
    void * f = fopen("storage/virfat_flash/C/MYLOCK.RES", "r");
    if(f){
        frename(f, DEF_LOCK_NAME);
        fclose(f);
    }
    
    cJSON_AddStringToObject(config, "wallper", "d:storage/virfat_flash/C/"DEF_LOCK_NAME);
}
char * getselectwallper();

void poweron_json_init(){
    if(!getselectwallper()){
        cJSON * config = cJSON_CreateObject();
        set_config_default(config);
        save_config(CONFIG_NAME, config);
        cJSON_Delete(config);
    }

    //extern char *lock_small_tab[];
    extern char *lock_big_tab[];
    //lock_small_tab[0] = selectwallpername;
    lock_big_tab[0] = selectwallpername;
}


char * getselectwallper(){
    cJSON* selectwallper = cJSON_GetObjectItem(read_config(CONFIG_NAME), "wallper");
    if(selectwallper) {
        if(selectwallper->valuestring){
            memset(selectwallpername, 0, sizeof(selectwallpername));
            strcpy(selectwallpername, selectwallper->valuestring);
            free(selectwallper);
            return selectwallpername;
        }
        free(selectwallper);
    } else {
        return NULL;
    }
}
    
void setselectwallper(char * s){
    cJSON* config = read_config(CONFIG_NAME);
    if(cJSON_GetObjectItem(config, "wallper")){
        r_printf("%s %d %s", __func__, __LINE__, s);
        cJSON_ReplaceItemInObject(config, "wallper", cJSON_CreateString(s));
        save_config(CONFIG_NAME, config);    
        //extern char *lock_small_tab[];
        extern char *lock_big_tab[];
        memset(selectwallpername, 0, sizeof(selectwallpername));
        strcpy(selectwallpername, s);
        //lock_small_tab[0] = selectwallpername;
        lock_big_tab[0] = selectwallpername;
    } 
    r_printf("%s %d %s", __func__, __LINE__, s);

}



