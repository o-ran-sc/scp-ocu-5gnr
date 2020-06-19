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



#ifndef PLATFORM_INCLUDE_PLAT_SYSLOG_H_
#define PLATFORM_INCLUDE_PLAT_SYSLOG_H_

#include "vos_common.h"

/** 日志等级  */
typedef enum _tag_SYSLOG_LEVEL
{
	SYSLOG_CRIT = 1,        ///<  critical conditions
	SYSLOG_ERR,             ///<  error conditions
	SYSLOG_WARNING,         ///<  warning conditions
	SYSLOG_INFO,            ///<  informational
	SYSLOG_DEBUG,           ///<  debug info
	VOS_SYSLOGLEVELS_NUM    ///<  max
}SYSLOG_LEVEL;


/**
 * 日志记录
 * @param[in]   module_id   模块ID
 * @param[in]   iLog_Level  Log等级
 * @param[in]   content     Log内容，fmt字符串
 * @param[in]   arg...      fmt中要输出的变量
 * @return      无
 */
#define VOS_log(module_id, iLog_Level, content,...)\
	    VOS_SysLog(module_id, iLog_Level, __FILE__, __LINE__, __func__, content,##__VA_ARGS__);


/**
 * 指定参数日志记录,只支持打印 %d 类型,传参必须为INT
 * @param[in]   module_id   模块ID
 * @param[in]   iLog_Level  Log等级
 * @param[in]   para_no     参数的数量，最多为5
 * @param[in]   content     Log内容，fmt字符串
 * @param[in]   arg...      fmt中要输出的变量
 * @return      无
 */
#define VOS_Nlog(module_id, iLog_Level, para_no, content,...) \
				VOS_NsysLog(module_id, iLog_Level, __FILE__, __LINE__, __func__, para_no, content,##__VA_ARGS__);


/**
 * 指定参数日志记录,只支持打印 %ld %lu %lx 类型,传参必须为LONG ULONG
 * @param[in]   module_id   模块ID
 * @param[in]   iLog_Level  Log等级
 * @param[in]   para_no     参数的数量，最多为5
 * @param[in]   content     Log内容，fmt字符串
 * @param[in]   arg...      fmt中要输出的变量
 * @return      无
 */
#define VOS_Nlog2(module_id, iLog_Level, para_no, content,...) \
                VOS_NsysLog_2(module_id, iLog_Level, __FILE__, __LINE__, __func__, para_no, content,##__VA_ARGS__);


/**
 * 指定参数日志记录，只支持打印 %ld %lu %lx %d %u %x %s 类型
 * @param[in]   module_id   模块ID
 * @param[in]   iLog_Level  Log等级
 * @param[in]   content     Log内容，fmt字符串
 * @param[in]   arg...      fmt中要输出的变量
 * @return      无
 */
#define VOS_Nlog2ex(module_id, iLog_Level,content,...) \
                VOS_NsysLog_2ex(module_id, iLog_Level, __FILE__, __LINE__, __func__,content,##__VA_ARGS__);

extern VOID VOS_SysLog(ULONG module_id, ULONG iLog_Level,CONST CHAR *file, LONG lineno,CONST CHAR *func, CONST CHAR *content, ... );
extern VOID VOS_NsysLog(ULONG module_id, ULONG iLog_Level, CONST CHAR *file, LONG lineno,CONST CHAR *func, UINT para_no, CONST CHAR * content, ... );
extern VOID VOS_NsysLog_2(ULONG module_id, ULONG iLog_Level,CONST CHAR *file, LONG lineno,CONST CHAR *func,UINT para_no,CONST CHAR *content, ... );
extern VOID VOS_NsysLog_2ex(ULONG module_id, ULONG iLog_Level,CONST CHAR *file, LONG lineno,CONST CHAR *func,CONST CHAR *content, ... );


#endif /* PLATFORM_INCLUDE_PLAT_SYSLOG_H_ */
