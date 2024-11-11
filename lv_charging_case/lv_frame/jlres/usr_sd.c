#include "usr_sd.h"

#include "board_config.h"

#if 0//TCFG_SD0_ENABLE

static u8 jpg_temp[40*1024];

void sd_test(){

    struct sd_res_h head={0};

    int fp = fopen("storage/sd0/C/snpg.bin", "r");
    printf("res:%x", fp);

    if(fp){
        u8 temp[32];
        fread(fp, &head, sizeof(struct sd_res_h));
        printf("Head:\n\
            int checksum = %d\n\
            int tablen = %d\n\
            int filesnum = %d\n\
            int fps = %d\n\
            u8 name[12] = %s\n\
            int fileslen %d\n\
        ", head.checksum, head.tablen, head.filesnum, head.fps, head.name, head.fileslen);


        struct sd_table_data table={0};
        fread(fp, &table, sizeof(struct sd_table_data));
        printf("\n\
        sd_table_data :\n\
            u8 name [12] = %s\n\
            int addr = %x\n\
        ",
        table.name,
        table.addr
        );

        int test_addr = table.addr;
#define LOG_DEBUG  0//1

        while(test_addr<head.fileslen){
            fseek(fp, test_addr, SEEK_SET);
            struct img_h img_head={0};
            fread(fp, &img_head, sizeof(struct img_h));
#if LOG_DEBUG
            printf("\n\
            img_head :\n\
                int nowaddr = %x\n\
                int nextaddr = %x\n\
                struct image_file file :\n\
                    u8 format = %d\n\
                    u8 compress = %d\n\
                    u16 data_crc = %d\n\
                    u16 width = %d\n\
                    u16 height = %d\n\
                    u32 offset = %x\n\
                    u32 len = %d\n\
                    u32 unzipOffset = %d\n\
                    u32 unzipLen = %d\n\
                u8 data[0] = %x\n\
            ",
            img_head.nowaddr,
            img_head.nextaddr,
            img_head.file.format,
            img_head.file.compress,
            img_head.file.data_crc,
            img_head.file.width,
            img_head.file.height,
            img_head.file.offset,
            img_head.file.len,
            img_head.file.unzipOffset,
            img_head.file.unzipLen,
            img_head.file.len,
            img_head.data
            );      
#endif
            int a = jiffies_half_msec();
            fread(fp, jpg_temp, img_head.file.len);
            int b = jiffies_half_msec();
            printf("l %d t %d", img_head.file.len, b-a);

            os_time_dly(1);
            test_addr = img_head.nextaddr;

        }
         
    }


__error:

    if(fp){
        fclose(fp);
        fp = NULL;
    }


}

#endif