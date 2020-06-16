/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/




#ifndef __VOS_SYS_DIFF_H__
#define __VOS_SYS_DIFF_H__

#include "vos_types.h"

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

#if OS_LINUX
#define __TASK_PRIORITY_TIME_CRITICAL           90     /* tTimer */
#define __TASK_PRIORITY_HIGHEST                 80     /* tDevice */
#define __TASK_PRIORITY_HIGHER                  70     /* consloe telnet */
#define __TASK_PRIORITY_HIGH                    60     /* cdp等  *//*hot */
#define __TASK_PRIORITY_ABOVE_NORMAL            50     /* stp *//* IP Receive *//*backup*/
#define __TASK_PRIORITY_NORMAL                  40     /* protocols *//* FDB FIB *//* radius */
#define __TASK_PRIORITY_BELOW_NORMAL            30     /* syslog */
#define __TASK_PRIORITY_LOWEST                  10
#define __TASK_PRIORITY_IDLE                     1
#define __VOS_DEFAULT_STACKSIZE                 1024*1024*8  /* 任务的缺省栈大小. */
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VOS_SYS_DIFF_H__ */
