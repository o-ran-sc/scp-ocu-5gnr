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
