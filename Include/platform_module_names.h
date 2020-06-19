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



#ifndef __PLATFORM_MODULE_NAMES_H__
#define __PLATFORM_MODULE_NAMES_H__

#include "vos_common.h"


#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */




#define MOD_NAME_VOS_MEM                ("VOS_mem")
#define MOD_NAME_VOS_LIST               ("VOS_list")
#define MOD_NAME_VOS_MODULE_MGR         ("VOS_module_mgr")
#define MOD_NAME_VOS_TASKMON            ("VOS_taskMon")
#define MOD_NAME_VOS_CLI                ("VOS_cli")
#define MOD_NAME_VOS_SOCKET             ("VOS_socket")
#define MOD_NAME_VOS_HOSTTASK           ("VOS_hostTask")


#define MOD_NAME_PLAT_ALARM             ("PLAT_alarm")
#define MOD_NAME_PLAT_ALARM_PROC        ("PLAT_alarm_proc")
#define MOD_NAME_PLAT_DB                ("PLAT_DB")

#define MOD_NAME_PLAT_SYSLOG             ("PLAT_syslog")
#define MOD_NAME_PLAT_SYSLOG_SUP             ("PLAT_syslog_sup")

#define MOD_NAME_LIB_CSTL               ("cstl")

#define MOD_NAME_PRINT_FLTER            ("print_filter")

#define MOD_NAME_US_TIMER               ("usTimer")

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PLATFORM_MODULE_NAMES_H__ */
