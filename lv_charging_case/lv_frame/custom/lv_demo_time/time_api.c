#include "events_adapter.h"
#include "ioctl_cmds.h"
#include "time_api.h"

/****************************************************set time*****************************************************/
// 年列表范围默认1990~2060
const char *roller_year = "1990\n1991\n1992\n1993\n1994\n1995\n1996\n1997\n1998\n1999\n2000\n2001\n2002\n2003\n2004\n2005\n2006\n2007\n2008\n2009\n2010\n2011\n2012\n2013\n2014\n2015\n2016\n2017\n2018\n2019\n2020\n2021\n2022\n2023\n2024\n2025\n2026\n2027\n2028\n2029\n2030\n2031\n2032\n2033\n2034\n2035\n2036\n2037\n2038\n2039\n2040\n2041\n2042\n2043\n2044\n2045\n2046\n2047\n2048\n2049\n2050\n2051\n2052\n2053\n2054\n2055\n2056\n2057\n2058\n2059\n2060";
// 月列表范围
const char *roller_month = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12";
// 31天日列表
const char *roller_day_31 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31";
// 30天日列表
const char *roller_day_30 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30";
// 29天日列表
const char *roller_day_29 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29";
// 28天日列表
const char *roller_day_28 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28";
// 24小时列表
const char *roller_hour_24 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n0";
// 12小时列表
const char *roller_hour_12 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12";
// 分钟列表范围
const char *roller_min_sec = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59";

// 闰年最大天数
const u8 month_max_leap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// 平年最大天数
const u8 month_max[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static u8 is_need_time_fresh = 0;
/****************************************************set time*****************************************************/

// 发送消息给ui线程，暂未用到
void lvgl_time_update(struct sys_time *time)
{
    int msg[8];
    msg[0] = UI_MSG_UPDATE;
    msg[1] = UI_UPDATE_TIME;
    msg[2] = time->year;
    msg[3] = time->month;
    msg[4] = time->day;
    msg[5] = time->hour;
    msg[6] = time->min;
    msg[7] = time->sec;
    // b_printf("update YMS HMS: %d/%d/%d %d=%d-%d", time->year, time->month, time->day, time->hour, time->month, time->sec);
    post_ui_msg(msg, 8);    
}

// 获取rtc时间
void sbox_get_sys_time(struct sys_time *time)
{
    void *fd = dev_open("rtc", NULL);
    if (!fd) {
        printf("[ERROR] open rtc error func: %s, line: %d", __func__, __LINE__);
        memset(time, 0, sizeof(*time));
        return;
    }
    dev_ioctl(fd, IOCTL_GET_SYS_TIME, (u32)time);
    // printf("Get systime : %d-%d-%d,%d:%d:%d\n", time->year, time->month, time->day, time->hour, time->min, time->sec);
    dev_close(fd);
}

// 设置rtc时间
void sbox_set_sys_time(struct sys_time *time)
{
    void *fd = dev_open("rtc", NULL);
    if (!fd) {
        printf("[ERROR] open rtc error func: %s, line: %d", __func__, __LINE__);
        return;
    }
    dev_ioctl(fd, IOCTL_SET_SYS_TIME, (u32)time);
    dev_close(fd);
    return;
}

// 字符串转整形（带符号）
int a2i(const char* str) 
{
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    
    int result = 0;
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            break;
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return sign * result;
}

// 闰年判断
int is_leap_year(int year)
{
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
        return 1;
    }

    return 0;
}

// 获取当前年和月对应的最大天数
u8 get_day_max(int year, int month)
{
    int day_max = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? month_max_leap[month - 1] : month_max[month - 1];
    return day_max;
}


