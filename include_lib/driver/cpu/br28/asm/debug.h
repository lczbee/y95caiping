#ifndef __DEBUG_H__
#define __DEBUG_H__


/* ---------------------------------------------------------------------------- */
/**
 * @brief 异常检测模块初始化
 */
/* ---------------------------------------------------------------------------- */
void debug_init();


/* ---------------------------------------------------------------------------- */
/**
 * @brief 异常分析函数
 */
/* ---------------------------------------------------------------------------- */
void exception_analyze();


/* ---------------------------------------------------------------------------- */
/**
 * @brief 根据设备名获取设备ID
 *
 * @param name: 设备名称, 如:"DBG_SPI0"
 *
 * @return: 设备ID
 */
/* ---------------------------------------------------------------------------- */
u32 get_dev_id(char *name);

/* ---------------------------------------------------------------------------- */
/**
 * @brief Memory权限保护设置
 *
 * @param idx: 保护框索引, 范围: 0 ~ 7, 目前系统默认使用0和3, 用户可用1, 2, 4, 5, 6, 7
 * @param begin: Memory开始地址
 * @param end: Memory结束地址
 * @param inv: 0: 保护框内, 1: 保护框外
 * @param format: "Cxwr0rw1rw2rw3rw", CPU:外设0:外设1:外设2:外设3,
 * @param ...: 外设ID号索引, 如: DBG_EQ, 见debug.h

 * @example1: 设置内存保护框1, 保护地址为0x200 ~ 0x400 - 1, 令该地址只可以FFT和EQ设备访问:
    mpu_set(1, 0x200, 0x400 - 1, 0, "0rw1rw", get_dev_id("DBG_FFT"), get_dev_id("DBG_EQ"));
 * @example2: 设置内存保护框2, 保护地址为0x200 ~ 0x400 - 1, 令该地址只可以cpu读写和EQ设备访问:
    mpu_set(2, 0x200, 0x400 - 1, 0, "Crw0rw", get_dev_id("DBG_EQ"));
 */
/* ---------------------------------------------------------------------------- */
void mpu_set(int idx, u32 begin, u32 end, u32 inv, const char *format, ...);


/* ---------------------------------------------------------------------------- */
/**
 * @brief 取消指定框的mpu保护
 *
 * @param idx: 保护框索引号
 */
/* ---------------------------------------------------------------------------- */
void mpu_disable_by_index(u8 idx);


/* ---------------------------------------------------------------------------- */
/**
 * @brief :取消所有保护框mpu保护
 */
/* ---------------------------------------------------------------------------- */
void mpu_diasble(void);


/* ---------------------------------------------------------------------------- */
/**
 * @brief flash PC范围设置为Flash外区域, 调用该接口后调用flash里的函数将触发异常
 */
/* ---------------------------------------------------------------------------- */
void flash_pc_limit_disable();

/* ---------------------------------------------------------------------------- */
/**
 * @brief flash PC范围限制恢复为flash代码区域, 调用该接口后可调用flash里的函数
 */
/* ---------------------------------------------------------------------------- */
void flash_pc_limit_enable();


#endif /* #ifndef __DEBUG_H__ */

