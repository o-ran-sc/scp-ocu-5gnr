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



#ifndef __VOS_TASK_H__
#define __VOS_TASK_H__

#include "vos_types.h"
#include "vos_module.h"

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** VOS任务的参数个数. */
#define VOS_MAX_TASK_ARGS                     10

/** 任务的缺省栈大小. */
#define VOS_DEFAULT_STACKSIZE                 __VOS_DEFAULT_STACKSIZE

/** 任务入口定义宏. */
#define DECLARE_VOS_TASK(VOS_TASK_ENTRY)\
    VOID VOS_TASK_ENTRY(\
        ULONG ulArg1, ULONG ulArg2,\
        ULONG ulArg3, ULONG ulArg4,\
        ULONG ulArg5, ULONG ulArg6,\
        ULONG ulArg7, ULONG ulArg8,\
        ULONG ulArg9, ULONG ulArg10\
        )

/** 任务优先级枚举值，创建任务时请使用下面的枚举值，不要用立即数. */
typedef enum VOS_task_pri_s
{
    TASK_PRIORITY_TIME_CRITICAL   =  __TASK_PRIORITY_TIME_CRITICAL,
    TASK_PRIORITY_HIGHEST         =  __TASK_PRIORITY_HIGHEST,
    TASK_PRIORITY_HIGHER          =  __TASK_PRIORITY_HIGHER,
    TASK_PRIORITY_HIGH            =  __TASK_PRIORITY_HIGH,
    TASK_PRIORITY_ABOVE_NORMAL    =  __TASK_PRIORITY_ABOVE_NORMAL,
    TASK_PRIORITY_NORMAL          =  __TASK_PRIORITY_NORMAL,
    TASK_PRIORITY_BELOW_NORMAL    =  __TASK_PRIORITY_BELOW_NORMAL,
    TASK_PRIORITY_LOWEST          =  __TASK_PRIORITY_LOWEST,
    TASK_PRIORITY_IDLE            =  __TASK_PRIORITY_IDLE,
}VOS_task_pri_t;

typedef VOS_msg_code_handler_ptr VOS_user_task_entry;


/** 用户任务结构体 */
typedef struct VOS_user_task_s
{
    CHAR                     userTaskName[VOS_NAME_MAX_LENGTH];     ///< 用户任务名
    VOS_user_task_entry      userTaskEntry;                         ///< 用户任务入口
    ULONG                    moduleID;                              ///< 用于 VOS_Malloc 的第二个参数
}VOS_user_task_t;


/** 任务入口函数类型. */
typedef VOID (*VOS_TASK_ENTRY)( ULONG pArg1, ULONG pArg2, ULONG pArg3,
           ULONG pArg4, ULONG pArg5, ULONG pArg6,
           ULONG pArg7, ULONG pArg8, ULONG pArg9,
           ULONG pArg10 );

/**
 * 任务创建 宏,
 * 该宏 会创建一个线程，栈大小为 VOS_DEFAULT_STACKSIZE 。
 * @param[in]   taskName       任务名，长度为 VOS_NAME_MAX_LENGTH
 * @param[in]   lPriority      优先级，使用 VOS_task_pri_t 枚举值
 * @param[in]   pfEntry        任务入口函数， 原型为VOS_TASK_ENTRY，10个ULONG 参数，无返回值
                               定义时使用宏DECLARE_VOS_TASK定义，eg：DECLARE_VOS_TASK(task1){ .... }
 * @param[in]   lTaskArg       传给任务入口函数的参数，类型为ULONG pArgs[10]
 * @return      成功返回VOS_HANDLE 类型的任务句柄，失败返回NULL
 */
#define VOS_TaskCreate( taskName, lPriority, pfEntry, lTaskArg )\
    VOS_TaskCreate_Ex_X( taskName, pfEntry, #pfEntry, (ULONG)(lPriority), VOS_DEFAULT_STACKSIZE, (ULONG *)(lTaskArg) )

/**
 * 任务创建 宏,
 * 该宏 会创建一个线程。
 * @param[in]   taskName       任务名，长度为 VOS_NAME_MAX_LENGTH
 * @param[in]   pfEntry        任务入口函数， 原型为VOS_TASK_ENTRY，10个ULONG 参数，无返回值
                               定义时使用宏DECLARE_VOS_TASK定义，eg：DECLARE_VOS_TASK(task1){ .... }
 * @param[in]   lPriority      优先级，使用 VOS_task_pri_t 枚举值
 * @param[in]   ulStackSize    栈大小
 * @param[in]   lTaskArg       传给任务入口函数的参数，类型为ULONG pArgs[10]
 * @return      成功返回VOS_HANDLE 类型的任务句柄，失败返回NULL
 */
#define VOS_TaskCreateEx( taskName, pfEntry, lPriority, ulStackSize, lTaskArg )\
    VOS_TaskCreate_Ex_X( taskName, pfEntry, #pfEntry, lPriority, ulStackSize, lTaskArg )


/**
 * 任务延时 宏,
 * 当前任务睡眠一定的时间.
 * @param[in]   lMsec    延时时间，毫秒
 * @return      VOS_OK - 成功，其他 - 失败
 */
#define VOS_TaskDelay( lMsec )\
    (LONG)VOS_TaskDelay_Ex_X( (lMsec), __FILE__, __LINE__ )


/**
 * 任务删除 API,
 * 将指定任务删除 。
 * @param[in]   hTaskHandle    任务创建时返回的任务句柄
 * @param[in]   ulExitCode     任务退出码，仅在windows系统中有效，其他传 0 即可
 * @return      VOS_OK - 成功，其他 - 失败
 */
LONG VOS_TaskTerminate( VOS_HANDLE hTaskHandle, ULONG ulExitCode );

/**
 * 将任务信息注册到vos task，在任务入口的最开始调用。main函数则在调用VOS_init()后调用
 * @return      VOS_OK - 成功，其他 - 失败
 */
LONG VOS_TaskInfoAttach(void);

/**
* 得到当前VOS任务句柄
* @return      成功返回VOS_HANDLE 类型的任务句柄，失败返回NULL
*/
VOS_HANDLE VOS_GetCurrentTask( VOID );


/**
 * 获得任务优先级
 *
 * @param[in]    hTaskHandle    任务创建时返回的任务句柄
 * @param[out]   pPrio          任务优先级
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_TaskGetPriority( VOS_HANDLE hTaskHandle, ULONG *pPrio );


/**
 * 设置任务优先级
 *
 * @param[in]    hTaskHandle    任务创建时返回的任务句柄
 * @param[in]    ulnewPrio      任务优先级
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_TaskSetPriority( VOS_HANDLE hTaskHandle, ULONG ulnewPrio );


/**
 * 获取当前任务的名字.
 *
 * @param[out]    szTaskName     任务名，长度 VOS_NAME_MAX_LENGTH
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_GetCurrentTaskName( CHAR szTaskName[VOS_NAME_MAX_LENGTH] );


/**
 * 判断任务句柄是否有效.
 *
 * @param[in]    hTaskHandle     任务句柄
 * @return       有效返回真，否则返回假
 */
BOOL VOS_TaskHandleVerify( VOS_HANDLE hTaskHandle );


/**
 * 创建宿主任务，宿主任务可以绑定多个用户任务(回调函数),栈大小为 VOS_DEFAULT_STACKSIZE。
 * @param[in]   taskName         任务名，长度为 VOS_NAME_MAX_LENGTH
 * @param[in]   lPriority        优先级，使用 VOS_task_pri_t 枚举值
 * @return      成功返回VOS_HANDLE 类型的任务句柄，失败返回NULL
 */
#define VOS_TaskHostCreate( taskName, lPriority )\
    VOS_TaskHostCreate_Ex_X( taskName, lPriority, VOS_DEFAULT_STACKSIZE)

/**
 * 创建宿主任务，宿主任务可以绑定多个用户任务(回调函数)。
 * @param[in]   taskName         任务名，长度为 VOS_NAME_MAX_LENGTH
 * @param[in]   lPriority        优先级，使用 VOS_task_pri_t 枚举值
 * @param[in]   ulStackSize      栈大小
 * @return      成功返回VOS_HANDLE 类型的任务句柄，失败返回NULL
 */
#define VOS_TaskHostCreateEx( taskName, lPriority, ulStackSize )\
    VOS_TaskHostCreate_Ex_X( taskName, lPriority, ulStackSize )



/**
 * 删除宿主任务，同时该宿主任务下的用户任务将被全部删除
 *
 * @param[in ]    szTaskName    宿主任务名
 * @param[in ]    ulExitCode    退出码(暂未使用，填0即可)
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_TaskHostTerminate(CHAR szTaskName[VOS_NAME_MAX_LENGTH], ULONG ulExitCode);


/**
 * 向宿主任务中添加用户任务(回调函数)。
 *
 * @param[in ]    hostTaskName    宿主任务名
 * @param[in ]    userTask        用户任务
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_UserTaskAttach(CHAR hostTaskName[VOS_NAME_MAX_LENGTH],VOS_user_task_t *userTask);


/**
 * 从宿主任务中删除用户任务(回调函数)。
 *
 * @param[in ]    hostTaskName    宿主任务名
 * @param[in ]    userTaskName    用户任务
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_UserTaskDetach(CHAR hostTaskName[VOS_NAME_MAX_LENGTH],CHAR userTaskName[VOS_NAME_MAX_LENGTH]);



/**
 * 设置任务的CPU亲和性
 *
 * @param[in ]    taskName    任务名(包含宿主任务，不包含用户任务)
 * @param[in ]    size        CPU个数
 * @param[in ]    cpus        CPU ID 数组
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_TaskAffinitySet(CHAR taskName[VOS_NAME_MAX_LENGTH],LONG size,LONG cpus[]);


/**
 * 获取任务的CPU亲和性,如果实际CPU个数超过cpus数组大小，则只返回size个cpu ID,返回值为 VOS_ERROR_BAD_ARGUMENTS
 *
 * @param[in ]    taskName    任务名(包含宿主任务，不包含用户任务)
 * @param[in ]    size        cpus数组大小
 * @param[out]    size        cpus数组有效值个数
 * @param[in ]    cpus        CPU ID 数组
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_TaskAffinityGet(CHAR taskName[VOS_NAME_MAX_LENGTH],LONG *size,LONG cpus[]);



/*=========================================================================================================================*/
/* ###### 下面的函数不要直接调用，使用上面提供的宏 ###### */

/**
* 任务创建 API，不要直接使用，通过 VOS_TaskCreate 宏使用
* 该API会创建一个线程，栈大小为 VOS_DEFAULT_STACKSIZE 。
* @param[in]   szTaskName       任务名，长度为 VOS_NAME_MAX_LENGTH
* @param[in]   pfnFunc          任务入口函数， 原型为VOS_TASK_ENTRY，10个ULONG 参数，无返回值
* @param[in]   szFuncName       任务入口函数名
* @param[in]   ulStartPriority  优先级，使用 VOS_task_pri_t 枚举值
* @param[in]   ulStackSize      栈大小
* @param[in]   pArgs            传给任务入口函数的参数，类型为ULONG pArgs[10]
* @return      成功返回VOS_HANDLE 类型的任务句柄，失败返回NULL
*/
VOS_HANDLE VOS_TaskCreate_Ex_X( CHAR szTaskName[VOS_NAME_MAX_LENGTH],
                           VOS_TASK_ENTRY pfnFunc,
                           CHAR *szFuncName,
                           ULONG ulStartPriority,
                           ULONG ulStackSize,
                           ULONG pArgs[VOS_MAX_TASK_ARGS]);

/**
* 任务延时 API，不要直接使用，通过 VOS_TaskDelay 宏使用
* 当前任务睡眠一定的时间.
* @param[in]   lMsec       延时时间，毫秒
* @param[in]   szFileName  调用者的文件
* @param[in]   iLine       调用者的行号
* @return      VOS_OK - 成功，其他 - 失败
*/
LONG VOS_TaskDelay_Ex_X( ULONG lMsec, CHAR *szFileName, INT iLine );


/**
 * 创建宿主任务，不要直接使用，通过 VOS_TaskHostCreate 宏使用,宿主任务可以绑定多个用户任务(回调函数)。
 *
 * @param[in]   szTaskName       任务名，长度为 VOS_NAME_MAX_LENGTH
 * @param[in]   ulStartPriority  优先级，使用 VOS_task_pri_t 枚举值
 * @param[in]   ulStackSize      栈大小
 * @return      成功返回VOS_HANDLE 类型的任务句柄，失败返回NULL
 */
VOS_HANDLE VOS_TaskHostCreate_Ex_X( CHAR szTaskName[VOS_NAME_MAX_LENGTH],
                           ULONG ulStartPriority,
                           ULONG ulStackSize);


/**
 * 获得当前任务的进程ID(PID)
 *
 * @return      返回进程ID(PID)
 */
ULONG VOS_TaskSelfGetPID(void);


/**
 * 获得当前任务的线程ID(SPID)
 *
 * @return      返回线程ID(SPID)
 */
ULONG VOS_TaskSelfGetSPID(void);


/**
 * 获得当前任务的线程ID(thread ID)
 *
 * @return      返回线程ID(thread ID)
 */
ULONG VOS_TaskSelfThreadID(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VOS_TASK_H__ */
