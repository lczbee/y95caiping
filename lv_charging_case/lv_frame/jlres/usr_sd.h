#ifndef __USR_SD
#define __USR_SD

#include "cpu.h"
#include "res/resfile.h"

struct sd_res_h {
    int checksum;
    int tablen;
    int filesnum;
    int fps;
    u8 name[12];
    int fileslen;
};

struct sd_table_data {
    u8 name [12];
    int addr;
};

struct img_h {
    int nowaddr;
    int nextaddr;
    struct image_file file;
    u8 data[0];
};

#endif