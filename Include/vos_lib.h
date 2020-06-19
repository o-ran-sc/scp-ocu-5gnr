/******************************************************************************
*
*   Copyright (c) 2020 ICT/CAS.
*
*   Licensed under the O-RAN Software License, Version 1.0 (the "Software License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       https://www.o-ran.org/software
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
*******************************************************************************/


#ifndef _VOS_LIB_H_
#define _VOS_LIB_H_

#ifdef __cplusplus
    extern "C" {
#endif

#include "vos_types.h"
#include "vos_module.h"
#include <stdarg.h>
#include "plat_syslog.h"
#include <stdio.h>



#define FILE_PATH_MAX 4096


/**
 * VOS 平台初始化
 * @param[in]   appPath      APP文件路径
 * @param[in]   cfgPath      vos config 文件路径
 * @param[in]   mods         定义已存在模块的数组
 * @param[in]   num          mods数组大小
 * @return      成功时返回申请内存的地址，失败则返回NULL。
 */
LONG VOS_Init(const CHAR *appPath,const CHAR *cfgPath,vos_module_t * mods,INT num);


/**
 * 分配内存
 * @param[in]   ulSize      申请内存的大小
 * @param[in]   ulModuleId  申请模块的模块ID
 * @return      成功时返回申请内存的地址，失败则返回NULL。
 */
#define VOS_Malloc(ulSize,ulModuleId) VOS_MallocWithDebug(ulSize,ulModuleId,(UCHAR *)__FILE__,__LINE__)


/**
 * 释放内存
 * @param[in]   ptr      释放内存的指针
 */
#define VOS_Free(ptr) VOS_Free_Debug(ptr,(UCHAR *)__FILE__,__LINE__)


/**
 * 根据bExp判断是否打印调用栈
 * @param[in]   exp        当bExp为假时打印调用栈
 */
#define VOS_ASSERT(exp)   VOS_ASSERT_X( (LONG)(exp), __FILE__, __LINE__ , 0)


/**
 * 格式化输出到默认输出
 * 注意 LONG 输出时，要用%ld,或%lx
 * @param[in]   format    格式字符串
 * @param[in]   ...       要输出的变量
 * @return      返回输出的字节数
 */
ULONG VOS_Printf(const CHAR *format ,...);


/**
 * 格式化输出到指定字符串中
 * @param[in]   buf       输出位置
 * @param[in]   fmt       格式字符串
 * @param[in]   ...       要输出的变量
 * @return      返回输出的字节数
 */
ULONG VOS_Sprintf(CHAR *buf ,CHAR *fmt, ...);


/**
 * 格式化输出到指定字符串中
 * @param[in]   buf       输出位置
 * @param[in]   size      buf的大小
 * @param[in]   fmt       格式字符串
 * @param[in]   ...       要输出的变量
 * @return      返回输出的字节数
 */
ULONG VOS_Snprintf(CHAR *buf, ULONG size, CHAR *fmt, ...);


/**
 * 读取格式化的字符串中的数据
 * @param[in]   buf       要读取的字符串
 * @param[in]   fmt       读取格式
 * @param[in]   ...       存储数据的指针
 * @return      返回成功读取的字段个数
 */
ULONG VOS_Sscanf(const CHAR * buf, const CHAR * fmt,...);


/** 同qsort */
VOID VOS_qsort(VOID *base, INT nmemb, INT size,
                  INT (*compar)(const VOID *, const VOID *));

/** 同 vsnprintf */
ULONG VOS_Vsnprintf(CHAR * buf, ULONG size, const CHAR * fmt, va_list args);

/** 同 vsprintf */
ULONG VOS_Vsprintf(CHAR * buf, const CHAR * fmt, va_list args);

/**
 * 判断文件是否存在
 * @param[in]   path      文件路径
 * @return      path存在返回TURE，不存在则返回FALSE
 */
BOOL VOS_file_exist(const CHAR *path);

#define NUM_LIST_MAX 4096

/**
 * 将数值list字符串(1-6,8,13)转换为，数组
 * @param[in ]   list      数值字符串
 * @param[out]   numList   解析后的数值数组
 * @return      成功解析的个数
 */
LONG parseNumList(const CHAR * list,ULONG numList[NUM_LIST_MAX]);


/**
 * 将数值list字符串(1-6,8,13)转换为一个ULONG bitmap
 * @param[in ]   list      数值字符串
 * @param[out]   map       解析后的bitmap
 * @return      成功返回VOS_OK，失败返回其他
 */
LONG parseNumList2BitMap(const CHAR * list,ULONG *map);

/**
 * 延时
 * @param[in ]   seconds      延时的秒数
 */
VOID VOS_Sleep(LONG seconds);

typedef VOID( *VOS_SIGNAL_FUNC ) ( int signal);

/**
 * vos信号处理回调函数注册
 * @param[in ]   sig      			信号
 * @param[in ]   sig_handler      	回调函数
 * @return      成功返回VOS_OK，失败返回VOS_ERROR
 */
LONG Vos_Signal(int sig, VOS_SIGNAL_FUNC sig_handler);

/**
 * product信号处理回调函数注册
 * @param[in ]   sig      			信号
 * @param[in ]   status      		是否退出
 * @param[in ]   sig_handler      	回调函数
 * @return      成功返回VOS_OK，失败返回VOS_ERROR
 */
LONG Product_Signal(int sig,	 ULONG status, VOS_SIGNAL_FUNC sig_handler);

/**
 * product最后处理的信号回调函数注册
 * @param[in ]   sig      			信号
 * @param[in ]   status      		是否退出
 * @param[in ]   sig_handler      	回调函数
 * @return      成功返回VOS_OK，失败返回VOS_ERROR
 */
LONG Product_Signal_Last(int sig,	 ULONG status, VOS_SIGNAL_FUNC sig_handler);

/**
 * 信号处理模块初始化
 * @param[in ]   signal      		信号
 * @return      成功返回VOS_OK，失败返回VOS_ERROR
 */
LONG Vos_SignalInit();

//信号最小值
#define SIGNAL_MIN 				0

//信号最大值
#define SIGNAL_MAX 				65

/** VOS 消息类型 */
typedef enum VOS_MOD_EVENT_TYPE_S
{
    VOS_MOD_EVENT_TYPE_ASYN   = 1,           ///< 异步消息
    VOS_MOD_EVENT_TYPE_SYN    = 2,           ///< 同步消息
    VOS_MOD_EVENT_TYPE_TIMER  = 3,           ///< 定时器消息
    VOS_MOD_EVENT_TYPE_MAX    = 0x100,       ///< VOS 占用最大消息类型ID
}VOS_MOD_EVENT_TYPE_T;

#define VOS_MOD_EVENT_TYPE_MAC_UL   (VOS_MOD_EVENT_TYPE_MAX+1)


/*=========================================================================================================================*/
/* ###### 下面的函数不要直接调用，使用上面提供的宏 ###### */
/**
 * 分配内存,不要直接调用该API，通过宏 VOS_Malloc 调用
 * @param[in]   size      申请内存的大小
 * @param[in]   moduleId  申请内存的模块ID
 * @param[in]   file      申请内存处的文件名
 * @param[in]   line      申请内存处的行号
 * @return      成功时返回申请内存的地址，失败则返回NULL。
 */
void* VOS_MallocWithDebug(unsigned long size, unsigned long moduleId, unsigned char *file, unsigned long line);

/**
 * 释放内存,不要直接调用该API，通过宏 VOS_Free 调用
 * @param[in]   ptr       释放内存的地址
 * @param[in]   file      释放内存处的文件名
 * @param[in]   line      释放内存处的行号
 * @return
 */
void VOS_Free_Debug(const void *ptr,  UCHAR *file, ULONG line);

/**
 * 打印断言，根据bExp判断是否打印调用栈，不要直接调用该API，通过宏 VOS_ASSERT 调用
 * @param[in]   bExp        当bExp为假时打印调用栈
 * @param[in]   szFileName  打印处的文件名
 * @param[in]   iLine       打印处的行号
 * @param[in]   bOutConsole 输出fd
 */
VOID VOS_ASSERT_X( BOOL bExp, CHAR *szFileName, INT iLine , INT bOutConsole);

/******计算某个函数运行时间******/
extern ULONG gTimerTickPerNsec;
uint64_t timer_get_ticks_diff(uint64_t CurrTick, uint64_t LastTick);
uint64_t timer_get_ticks(void);



#define VOS_CALC_ELAPSED_TIME_NS(func)			\
({										\
	uint64_t start, end;			\
	uint64_t diff;							\
	start = timer_get_ticks();	\
	func;								\
	end = timer_get_ticks();	 \
	diff = timer_get_ticks_diff(end,start);\
	vos_info_print("func %s spend diff %ld,gTimerTickPerNsec %ld, time = %ld ns,\n",#func ,diff,gTimerTickPerNsec,diff/gTimerTickPerNsec);\
})

#define __vos_start_tick()  uint64_t start_tick = timer_get_ticks(),cur_tick = 0;
#define __vos_diff_tick()   cur_tick = timer_get_ticks();printf("%s.%d  diff ticks %ld \r\n",__func__,__LINE__,timer_get_ticks_diff(cur_tick,start_tick));start_tick = timer_get_ticks();

typedef LONG (*vos_print_wrapper_func_t)(void *dst,const char * format,...);
LONG vos_vty_out_wrapper(void *vty,const char * format, ... );
LONG vos_printf_wrapper(void *vty,const char * format, ... );

//#####################################################################################
// 未包含设备管理模块时需要添加的宏
#ifndef PLAT_MODULE_DEVSM
#define SYS_LOCAL_MODULE_SLOTNO_GET (1)
#define SYS_MODULE_IS_RUNNING(slotno) (VOS_TRUE)

#endif

//#####################################################################################
typedef enum {
    _vos_print_lv_info = 0,
    _vos_print_lv_warning,
    _vos_print_lv_err,
    _vos_print_lv_max
}_vos_print_lv;


// 带颜色的打印，开发调试时使用
#define VOS_COLOR_NONE "\033[m"
#define VOS_COLOR_RED "\033[1;31m"
#define VOS_COLOR_BLUE "\033[1;34m"
#define VOS_COLOR_PURPLE "\033[1;35m"
#define VOS_COLOR_GREEN "\033[1;32m"


extern BOOL vos_info_print_filter_is_filtered(LONG lv,const char *val);
#define __is_p_(lv,val) vos_info_print_filter_is_filtered(lv,val)
#define __print_check(lv,func,line)  char tmp1[200];snprintf(tmp1,sizeof(tmp1),"%s.%d",func,line);if( !( __is_p_(lv,tmp1)||__is_p_(lv,func)))
extern int sprintf(char *str, const char *format, ...);
#define vos_raw_print(_format, ...)  printf(_format, ##__VA_ARGS__)
#define vos_info_print(_format, ...)  {__print_check(_vos_print_lv_info,__func__,__LINE__){vos_raw_print(VOS_COLOR_BLUE"%s.%d:" _format VOS_COLOR_NONE"",__func__,__LINE__,##__VA_ARGS__);}}
#ifdef VOS_log
extern vos_module_t module_print_filter;
#define __log_mid module_print_filter.moduleID
#define vos_warning_print(_format, ...)  {__print_check(_vos_print_lv_warning,__func__,__LINE__){vos_raw_print(VOS_COLOR_PURPLE"%s.%d:"_format VOS_COLOR_NONE"",__func__,__LINE__,##__VA_ARGS__);VOS_log(__log_mid,SYSLOG_WARNING,_format, ##__VA_ARGS__);}}
#define vos_err_print(_format, ...)  {__print_check(_vos_print_lv_err,__func__,__LINE__){vos_raw_print(VOS_COLOR_RED"%s.%d:"_format VOS_COLOR_NONE"",__func__,__LINE__,##__VA_ARGS__);VOS_log(__log_mid,SYSLOG_ERR,_format, ##__VA_ARGS__);}}
#define vos_perror(_format, ...)  {__print_check(_vos_print_lv_err,__func__,__LINE__){char tmp[200];vos_raw_print(VOS_COLOR_RED"%s.%d:",__func__,__LINE__);vos_raw_print(_format, ##__VA_ARGS__);sprintf(tmp,"%m");vos_raw_print(": %s",tmp);vos_raw_print(VOS_COLOR_NONE"");VOS_log(__log_mid,SYSLOG_ERR,_format, ##__VA_ARGS__);}}
#else
#define vos_warning_print(_format, ...)  {__print_check(_vos_print_lv_warning,__func__,__LINE__){vos_raw_print(VOS_COLOR_PURPLE"%s.%d:"_format VOS_COLOR_NONE"",__func__,__LINE__,##__VA_ARGS__);}}
#define vos_err_print(_format, ...)  {__print_check(_vos_print_lv_err,__func__,__LINE__){vos_raw_print(VOS_COLOR_RED"%s.%d:"_format VOS_COLOR_NONE"",__func__,__LINE__,##__VA_ARGS__);}}
#define vos_perror(_format, ...)  {__print_check(_vos_print_lv_err,__func__,__LINE__){char tmp[200];vos_raw_print(VOS_COLOR_RED"%s.%d:",__func__,__LINE__);vos_raw_print(_format, ##__VA_ARGS__);sprintf(tmp,"%m");vos_raw_print(": %s",tmp);vos_raw_print(VOS_COLOR_NONE"");}}
#endif

#define NULL_CHECK(p) if(NULL == p) {vos_err_print(#p" is null\r\n");return VOS_ERROR;}

#define NULL_CHECK_RP(p) if(NULL == p) {vos_err_print(#p" is null\r\n");return NULL;}


#define RET_CHECK(bool,p) if(bool) {vos_err_print(#p" error\r\n");return VOS_ERROR;}

LONG VOS_mini_Init(VOID);// 调试时使用
LONG VOS_mini_Init_task(VOID);
LONG VOS_mini_Init_cli(VOID);
LONG VOS_mini_Init_cli_db(const CHAR *appPath,const CHAR *cfgPath,vos_module_t * mods,INT num);
LONG VOS_mini_Init_cli_alarm(const CHAR *appPath,const CHAR *cfgPath,vos_module_t * mods,INT num);


#ifdef __cplusplus
    }
#endif

#endif /*_VOS_LIB_H_*/
