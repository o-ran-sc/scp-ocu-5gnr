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



#ifndef __VOS_TIMER_H__
#define __VOS_TIMER_H__
#include "vos_types.h"

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */


/** VOS Timer 类型枚举值 */
typedef enum
{
    VOS_TIMER_LOOP,             ///< 循环执行的timer
    VOS_TIMER_NO_LOOP,          ///< 执行一次的timer
}VOS_TIMER_TYPE_EN;


/**
 * 创建定时器
 * @param[in]   ulModuleId         模块ID
 * @param[in]   msgQId             如果pfTimerFunc非空则无效；如果pfTimerFunc为NULL，则向msgQId队列发送定时器超时消息
 * @param[in]   lMillSec           定时器的时间，毫秒
 * @param[in]   pfTimerFunc        超时回调函数
 * @param[in]   pArg               回调函数参数
 * @param[in]   enType             定时器类型
 * @return      返回Timer ID，失败则返回VOS_ERROR
 */
LONG VOS_TimerCreate(ULONG ulModuleId, ULONG msgQId, LONG lMillSec,
    VOID  (*pfTimerFunc)(VOID *), VOID  *pArg, VOS_TIMER_TYPE_EN enType);


/**
* 改变定时器时间,不能在超时回调函数中调用
* @param[in]   ulModuleId         模块ID
* @param[in]   ulTimerId          定时器Id
* @param[in]   lMillSec           定时器的时间，毫秒
* @return      成功返回VOS_OK，失败则返回VOS_ERROR
*/
LONG VOS_TimerChange(ULONG ulModuleId, ULONG ulTimerId, LONG lMillSec);


/**
* 删除定时器
* @param[in]   ulModuleId         模块ID
* @param[in]   ulTimerId          定时器Id
* @return      成功VOS_OK，失败则返回VOS_ERROR
*/
LONG VOS_TimerDelete(ULONG ulModuleId, ULONG ulTimerId);


/**
 * 创建微秒定时器，必须绑核
 * @param[in]   ulModuleId         模块ID
 * @param[in]   luSec              定时器的时间，微妙
 * @param[in]   pfTimerFunc        超时回调函数
 * @param[in]   pArg               回调函数参数
 * @param[in]   enType             定时器类型
 * @param[in]   cpuNum             CPU个数
 * @param[in]   cpus               CPU ID 数组
 * @return      返回Timer ID，失败则返回VOS_ERROR
 */
LONG VOS_usTimerCreate(ULONG ulModuleId,LONG luSec,VOID  (*pfTimerFunc)(VOID *), VOID  *pArg, VOS_TIMER_TYPE_EN enType,LONG cpuNum,LONG cpus[]);



/**
 * 创建微秒定时器，必须绑核
 * @param[in]   ulModuleId         模块ID
 * @param[in]   ulTimerId          Timer ID
 * @return      成功VOS_OK，失败则返回VOS_ERROR
 */
LONG VOS_usTimerDestroy(ULONG ulModuleId, ULONG ulTimerId);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __VOS_TIMER_H__ */
