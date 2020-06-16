/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef	__VOS_TIME_H__
#define	__VOS_TIME_H__

#ifdef	__cplusplus
extern "C"{
#endif

#include "vos_types.h"

#define VOS_TIME_STR_LEN 20

typedef struct LOCAL_TIME {
    USHORT usYear;
    USHORT usMonth;
    USHORT usDayOfWeek;
    USHORT usDay;
    USHORT usHour;
    USHORT usMinute;
    USHORT usSecond;
    USHORT usMilliseconds;
}VOS_LOCAL_TIME;



/** 
 * 获取当前时间
 * @param[in]   vos_time     存储时间的指针
 * @return      成功返回 VOS_OK，失败则返回其他
 */ 
LONG VOS_local_time( VOS_LOCAL_TIME *vos_time );


/** 
 * 获取当前时间
 * @param[out]   sys_time     时间
 * @return      返回值同 sys_time
 */ 
LONG VOS_time( LONG *sys_time );

/** 
 * 时间转换，local time 转成秒数
 * @param[out]   sys_time     时间
 * @return      返回 sys_time 对应的秒数
 */ 
LONG VOS_mkTime(const VOS_LOCAL_TIME *sys_time );


/** 
 * 时间转换，秒数 转成local time
 * @param[out]   sys_time     时间
 * @param[in ]   time         时间秒数
 * @return      成功返回 VOS_OK，失败则返回其他
 */ 
LONG VOS_mkLocalTime( VOS_LOCAL_TIME *sys_time ,LONG time);


/** 
 * 获得时间字符串 YYYY-MM-DD hh:mm:ss
 *  如果sys_time非空则根据sys_time转换，否则根据time转换，time为0时取当前时间转换，
 *  转换完成后存入str中
 * @param[in ]   sys_time     时间
 * @param[in ]   time         时间秒数
 * @param[out]   str          时间字符串
 * @return      指向str的指针
 */
CHAR *VOS_mkLocalTimeStr( VOS_LOCAL_TIME *sys_time ,LONG time,CHAR str[VOS_TIME_STR_LEN]);


/** 
 * 将时间字符串 YYYY-MM-DD hh:mm:ss 转换，为VOS_LOCAL_TIME 和 LONG型
 *  sys_time和time不为空则填入转换后的值，某一项不需要可以使用NULL
 * @param[in ]   str          时间字符串
 * @param[out]   sys_time     时间
 * @param[out]   time         时间秒数
 * @return      成功返回 VOS_OK，失败则返回其他
 */
LONG VOS_StrmkLocalTime( CHAR str[VOS_TIME_STR_LEN],VOS_LOCAL_TIME *sys_time ,LONG *time);


/** 
 * 将时间秒数转换成 snmp 时间
 * @param[in ]   sys_time     时间秒数
 * @param[out]   snmpTime     时间
 * @return      成功返回 VOS_OK，失败则返回其他
 */
LONG vos_time2snmp(LONG sys_time,VOS_SNMP_DateAndTime_t *snmpTime);

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of __VOS_TIME_H__ */

