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



#ifndef __VOS_MODULE_H__
#define __VOS_MODULE_H__

#include "vos_types.h"
#include "vos_timer.h"
#include "vos_que.h"
#include "vos_socket.h"



/** 模块名大小 */
#define MODULE_NAME_LEN (48)


/** 模块类型 */
typedef enum module_type_e{
    VOS_MOD_T_NORMAL = 0,       ///< 一般模块
    VOS_MOD_T_HOST,             ///< host task
    VOS_MOD_T_USER,             ///< user task
    VOS_MOD_T_EXTERN,           ///< 外部模块 (不是 vos app 中的模块，其他的进程 )
    VOS_MOD_T_MAX,              ///<
}module_type_t;

/** 模块通信类型 */
typedef enum module_comm_type_e{
    VOS_MOD_COMM_T_VOS              = (1 << 0),     ///< vos 模块间通信
    VOS_MOD_COMM_T_UNIX_UDP_C       = (1 << 1),     ///< unix socket udp client
    VOS_MOD_COMM_T_UNIX_UDP_S       = (1 << 2),     ///< unix socket udp server
    VOS_MOD_COMM_T_UNIX_TCP_C       = (1 << 3),     ///< unix socket tcp client
    VOS_MOD_COMM_T_UNIX_TCP_S       = (1 << 4),     ///< unix socket tcp server
    VOS_MOD_COMM_T_UDP_C            = (1 << 5),     ///< udp client
    VOS_MOD_COMM_T_UDP_S            = (1 << 6),     ///< udp server
    VOS_MOD_COMM_T_TCP_C            = (1 << 7),     ///< tcp client
    VOS_MOD_COMM_T_TCP_S            = (1 << 8),     ///< tcp server
    VOS_MOD_COMM_T_SCTP_ONE2ONE_C   = (1 << 9),     ///< sctp one2one client
    VOS_MOD_COMM_T_SCTP_ONE2ONE_S   = (1 << 10),    ///< sctp one2one server
    VOS_MOD_COMM_T_SCTP_ONE2MANY_C  = (1 << 11),    ///< sctp one2many client
    VOS_MOD_COMM_T_SCTP_ONE2MANY_S  = (1 << 12),    ///< sctp one2many server
    VOS_MOD_COMM_T_SOCK_OP          = (1 << 13),    ///< socket
    VOS_MOD_COMM_T_MAX,                             ///< max
}module_comm_type_t;


/** 模块管理类型 */
typedef struct vos_module_s{
    module_type_t       modType;                      ///< 模块类型
    LONG                commType;                     ///< 当前的通信类型
    ULONG               moduleID;                     ///< 模块ID
    CHAR                name[MODULE_NAME_LEN];        ///< 模块名
    ULONG               queueID;                      ///< 模块消息队列，用于接收从其他模块发送过来的消息
    LONG                paraCount;                    ///< 无需关心，         （添加的额外参数个数）
    void                *pPara;                       ///< 无需关心，         （vos_mod_com_para_cb_t）
    LONG                paraLock;                     ///< 无需关心，
}vos_module_t;


/** 采用非VOS通信方式的模块需要提供的handle函数，用于接收数据
*   buf         用于消息接收的缓冲区
*   size        buf 大小
*   opval       额外信息，类型为 vos_mod_com_op_t
*   opvalLen    opval的大小
*
*/
typedef LONG (*receive_handler)(VOID *buf,LONG size,VOID *opval,LONG opvalLen);


/**
 * 模块注册 API
 * 向VOS 模块管理中注册模块 。
 * @param[in ]   name         模块名，大小为 MODULE_NAME_LEN
 * @param[in]    module       模块管理信息
 *                               传入值
 *                                      module.queueID  用于模块间通信
 *                                      module.mod_type 模块类型
 * @param[out]   module       模块管理信息
 *                               传出值
 *                                      module.name
 *                                      module.moduleID
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_module_register(const CHAR *name,vos_module_t *module);


/**
 * 模块注销 API
 * 向VOS 模块管理中注册模块 。
 * @param[in ]   name         模块名，大小为 MODULE_NAME_LEN
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_module_deregister(const CHAR *name);


/**
 * 根据模块ID获得模块名
 * @param[in ]   id         模块ID
 * @param[out]   name       模块名，大小为 MODULE_NAME_LEN
 * @return       VOS_OK - 成功，其他 - 失败
 */
LONG VOS_module_get_name(ULONG id,CHAR name[MODULE_NAME_LEN]);

/**
 * 根据模块名获得模块ID
 * @param[in ]   name       模块名，大小为 MODULE_NAME_LEN
 * @return       成功返回模块ID，失败返回 0
 */
ULONG VOS_module_get_Id(CHAR *name);


/**
 * 向某个模块发送异步消息
 * @param[in ]   dst_slot           目的槽位号
 * @param[in ]   dst_moduleName     目的模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   src_moduleName     源模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   msgCode            消息码
 * @param[in ]   msgData            消息数据
 * @param[in ]   msgDataLen         消息数据长度
 * @return       成功返回 VOS_OK，失败返回 其他
 */
LONG VOS_SendAsynMsg2Module(LONG dst_slot,CHAR dst_moduleName[MODULE_NAME_LEN],CHAR src_moduleName[MODULE_NAME_LEN],
                                    LONG msgCode,VOID *msgData,LONG msgDataLen);

/**
 * 向某个模块发送同步消息
 * @param[in ]   dst_slot           目的槽位号
 * @param[in ]   dst_moduleName     目的模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   src_moduleName     源模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   msgCode            消息码
 * @param[in ]   msgData            消息数据，如果没有则填 NULL
 * @param[in ]   msgDataLen         消息数据长度，如果msgData 为NULL 填0
 * @param[out]   ackData            接收返回数据的buf
 * @param[in ]   ackDataLen         输入：接收返回数据buf的长度
 * @param[out]   ackDataLen         输出：buf的有效长度
 * @param[in ]   timeout            等待接收的时间，单位毫秒,调用者自行判断需要等待时间，一般等待 5秒
 * @return       成功返回 VOS_OK，失败返回 其他
 */
LONG VOS_SendSynMsg2Module(LONG dst_slot,CHAR dst_moduleName[MODULE_NAME_LEN],CHAR src_moduleName[MODULE_NAME_LEN],
                                  LONG msgCode,VOID *msgData,LONG msgDataLen,VOID *ackData,LONG *ackDataLen,LONG timeout);



/**
 * 向某个模块发送异步消息，支持非VOS通信方式
 * @param[in ]   dst_slot           目的槽位号
 * @param[in ]   dst_moduleName     目的模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   src_moduleName     源模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   msgCode            消息码
 * @param[in ]   msgData            消息数据
 * @param[in ]   msgDataLen         消息数据长度
 * @param[in ]   commType           通信方式
 * @param[in ]   optval             可选参数，不需要则填NULL
 * @param[in ]   optlen             可选参数长度
 * @return       成功返回 VOS_OK，失败返回 其他
 */
LONG VOS_SendAsynMsg2ModuleEx(LONG dst_slot,CHAR dst_moduleName[MODULE_NAME_LEN],CHAR src_moduleName[MODULE_NAME_LEN],
                                      LONG msgCode,VOID *msgData,LONG msgDataLen,
                                      module_comm_type_t commType,VOID *optval,LONG optlen);


/**
 * 向某个模块发送同步消息，仅支持VOS通信方式
 * @param[in ]   dst_slot           目的槽位号
 * @param[in ]   dst_moduleName     目的模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   src_moduleName     源模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   msgCode            消息码
 * @param[in ]   msgData            消息数据，如果没有则填 NULL
 * @param[in ]   msgDataLen         消息数据长度，如果msgData 为NULL 填0
 * @param[out]   ackData            接收返回数据的buf
 * @param[in ]   ackDataLen         输入：接收返回数据buf的长度
 * @param[out]   ackDataLen         输出：buf的有效长度
 * @param[in ]   timeout            等待接收的时间，单位毫秒,调用者自行判断需要等待时间，一般等待 5秒
 * @param[in ]   commType           通信方式
 * @param[in ]   optval             可选参数，不需要则填NULL
 * @param[in ]   optlen             可选参数长度
 * @return       成功返回 VOS_OK，失败返回 其他
 */
LONG VOS_SendSynMsg2ModuleEx(LONG dst_slot,CHAR dst_moduleName[MODULE_NAME_LEN],CHAR src_moduleName[MODULE_NAME_LEN],
                                    LONG msgCode,VOID *msgData,LONG msgDataLen,VOID *ackData,LONG *ackDataLen,LONG timeout,
                                    module_comm_type_t commType,VOID *optval,LONG optlen);

LONG VOS_SendAsynMsg2Module_Raw(LONG dst_slot,CHAR dst_moduleName[MODULE_NAME_LEN],CHAR src_moduleName[MODULE_NAME_LEN],
                                    ULONG aulMsg[VOS_QUEUE_MSG_SIZE]);



/**
* 回复同步消息
* @param[in ]   aulMsg             VOS_QueReceive 收到的原始消息
* @param[in ]   ackData            返回数据的buf
* @param[in ]   ackDataLen         返回数据buf的长度
* @return       成功返回 VOS_OK，失败返回 其他
*/
LONG VOS_SendSynAckMsg(ULONG aulMsg[VOS_QUEUE_MSG_SIZE],VOID *ackData,LONG ackDataLen);


/**
* 注册timer 消息
* @param[in ]   module_ID        要注册timer msg的模块号
* @param[in ]   msg_code         消息码
* @param[in ]   interval         发送间隔,毫秒
* @param[in ]   type             类型，循环或者只执行一次
* @param[in ]   pArg             附加参数，一般为一个指针
* @return       成功返回 VOS_OK，失败返回 其他
*/
LONG VOS_RegTimerMsg(LONG module_ID,LONG msg_code,LONG interval,VOS_TIMER_TYPE_EN type,VOID  *pArg);


/**
* 注销timer 消息
* @param[in ]   module_ID        要注销timer msg的模块号
* @param[in ]   msg_code         消息码
* @return       成功返回 VOS_OK，失败返回 其他
*/
LONG VOS_DeregTimerMsg(LONG module_ID,LONG msg_code);


/** 从原始消息中获取消息类型 （同步/异步） */
#define VOS_MOD_MSG_GET_EVENT_TYPE(aulMsg)       aulMsg[0]

/** 从原始消息中获取消息类码 */
#define VOS_MOD_MSG_GET_CODE(aulMsg)         ((SYS_MSG_S *)(aulMsg[3]))->usMsgCode


/** 从原始消息中获取源模块号 */
#define VOS_MOD_MSG_GET_SRC_ID(aulMsg)       ((SYS_MSG_S *)(aulMsg[3]))->ulSrcModuleID


/** 从原始消息中获取目的模块号 */
#define VOS_MOD_MSG_GET_DST_ID(aulMsg)       ((SYS_MSG_S *)(aulMsg[3]))->ulDstModuleID


/** 从原始消息中获取源槽位号 */
#define VOS_MOD_MSG_GET_SRC_SLOT(aulMsg)     ((SYS_MSG_S *)(aulMsg[3]))->ulSrcSlotID


/** 从原始消息中获取目的槽位号 */
#define VOS_MOD_MSG_GET_DST_SLOT(aulMsg)     ((SYS_MSG_S *)(aulMsg[3]))->ulDstSlotID


/** 从原始消息中获取消息长度 */
#define VOS_MOD_MSG_GET_LEN(aulMsg)        ((SYS_MSG_S *)(aulMsg[3]))->usFrameLen

/** 从原始消息中获取消息buf 的指针 */
#define VOS_MOD_MSG_GET_DATAPTR(aulMsg)    ((SYS_MSG_S *)(aulMsg[3]))->ptrMsgBody

/** 从原始消息中拷贝消息到dst中 */
#define VOS_MOD_MSG_GET_DATA(dst,aulMsg)   if( NULL != VOS_MOD_MSG_GET_DATAPTR(aulMsg) )                                                 \
                                           {  VOS_MemCpy(dst,VOS_MOD_MSG_GET_DATAPTR(aulMsg),VOS_MOD_MSG_GET_LEN(aulMsg));  }           \
                                           else                                                                                         \
                                           {  VOS_ASSERT(0);   }

/** 释放原始消息中的sys msg */
#define VOS_MOD_MSG_FREE(aulMsg)           VOS_Free((VOID *)aulMsg[3])


/** msg handler的函数原型 */
typedef LONG(*VOS_msg_code_handler_ptr)(ULONG aulMsg[VOS_QUEUE_MSG_SIZE]);


/** 用于模块间通信的code 和 handler的map */
typedef struct msg_code_handle_map_s
{
    LONG                     msg_code;   ///< 消息码
    VOS_msg_code_handler_ptr handler;    ///< 消息码的处理函数
}VOS_msg_code_handle_map_t;



#endif /* __VOS_MODULE_H__ */
