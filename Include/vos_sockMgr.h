/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/



#ifndef __VOS_SOCKMGR_H__ 
#define __VOS_SOCKMGR_H__

#include "vos_types.h"
#include "vos_timer.h"
#include "vos_que.h"
#include "vos_socket.h"
#include "vos_module.h"

#define COMM_SCTP_ADDR_MAX 5


#define VOS_SOCKET_MSG_MAX 9000 


/** 采用socket mgr 需要提供的handle函数，用于接收数据
 * @param[in ]   buf         用于消息接收的缓冲区
 * @param[in ]   size        buf 大小
 * @param[in ]   opval       额外信息，类型为 vos_mod_com_op_t 
 * @param[in ]   opvalLen    opval的大小
 *
*/
typedef LONG (*receive_handler)(VOID *buf,LONG size,VOID *opval,LONG opvalLen);


/** tcp/sctp one-to-one 用于接收客户端accept 事件的函数
* @param[in ]   info           客户端信息，实际为vos_sock_info_t
* @param[in ]   infoLen        信息长度
*
*/
typedef LONG (*accept_handler)(VOID *info,LONG infoLen);


typedef struct sctp_para_s {
    vos_sockaddr_t                  addrs[COMM_SCTP_ADDR_MAX];  ///< ip 地址
    LONG                            addrsCnt;                   ///< ip 个数
    struct sctp_sndrcvinfo          sinfo;                      ///< sctp_sndrcvinfo
    struct sctp_initmsg             initmsg;                    ///< sctp_initmsg
    struct sctp_event_subscribe     events;                     ///< sctp_event_subscribe
}sctp_para_t;

typedef union {
        vos_sockaddr_t   addr;
        sctp_para_t      sctp;
}___addr_u;

/** 创建socket需要提供的参数 */
typedef struct vos_sock_para_s
{
    module_comm_type_t type;                ///< 通信方式 
    union{
        vos_sockaddr_t addr;                ///< socket 通信
        sctp_para_t    sctp;                ///< sctp   通信
    }u;
    ___addr_u          client_bind_addr;    ///< 创建客户端时如果也需要绑定地址，填写该变量
    receive_handler  recv_handle;           ///< 接收函数 
    accept_handler   accept_handle;         ///< 接收accept 事件 
    LONG             maxClient;             ///< tcp server 允许的连接数
    BOOL             soloMode;              ///< 如果为真，则单独创建接收线程；如果为假，则由 VOS socket代理任务负责接收
    LONG             fdIdx;                 ///< 无需关心
}vos_sock_para_t;

typedef struct vos_sock_info_s{
    module_comm_type_t type;     ///< 通信方式 
    LONG fd;                     ///< socket
    LONG fdIdx;                  ///< 无需关心
    LONG c_flag;                 ///< 无需关心
    struct sctp_sndrcvinfo sri;  ///< sctp_recvmsg()/sctp_send() 中的 sinfo,sctp_sendmsg() 中ppid,flags,stream_no,timetolive,context也从该结构中获得
    LONG msg_flags;              ///< sctp_recvmsg() 中的 msg_flags
    vos_sockaddr_t addr;         ///< udp/sctp one-to-many 接收到的对端地址，同时也是udp/sctp one-to-many 发送的目的地址
}vos_sock_info_t;


/** 
 * 创建socket通信
 * @param[in ]   name         模块名，大小为 MODULE_NAME_LEN
 * @param[in ]   pPara        额外参数数组
 * @param[in ]   size         数组大小
 * @param[out]   info           socket 相关信息，用于发送消息和删除该socket
 * @return       VOS_OK - 成功，其他 - 失败
 */ 
LONG VOS_SOCKET_create(const CHAR *name,vos_sock_para_t *pPara,LONG size,vos_sock_info_t *info);


/** 
 * 删除 socket
 * @param[in ]   info           创建时获得的socket 相关信息
 * @return       VOS_OK - 成功，其他 - 失败
 */ 
LONG VOS_SOCKET_delete(vos_sock_info_t *info);


/** 
 * 判断是否连接成功(只判断tcp 和sctp one-to-one 是否connect成功)
 * @param[in ]   info           创建时获得的socket 相关信息
 * @return       连接正常返回 VOS_TRUE,否则返回 VOS_FALSE
 */ 
BOOL VOS_SOCKET_isLink(vos_sock_info_t *info);


/** 
 * socket 发送数据
 * @param[in ]   info           socket 相关信息
 * @param[in ]   msgData        数据
 * @param[in ]   msgDataLen     数据长度
 * @return       成功返回 发送的字节数 ，失败则返回 VOS_ERROR
 */ 
LONG VOS_SOCKET_send(vos_sock_info_t *info,VOID *msgData,LONG msgDataLen);



#endif /* __VOS_SOCKMGR_H__ */
