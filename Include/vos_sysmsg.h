/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/





#ifndef __VOS_SYSMSG_H__
#define __VOS_SYSMSG_H__

#ifdef __cplusplus
extern "C"{
#endif

typedef struct 
{
     USHORT  usMessageType;     /*用于指示发送或接收*/
     USHORT  usPririty;         /*优先级（用户自己定义）,支持4个优先级 */  
     ULONG   ulSrcModuleID;     /*源模块号*/
     ULONG   ulDstModuleID;     /*目标模块号*/
     ULONG   ulSequence;        /*发送序号,RPC专用*/ 

     ULONG   ulSrcSlotID;	    /*源槽位号*/
     ULONG   ulDstSlotID;       /*目的槽位号*/
     UCHAR   ucMsgType;         /*消息类型，如PDU, TIMER, REQUEST, NOTIFY... */
     UCHAR   ucMsgBodyStyle;    /*用于指明消息头和消息体是否是一体的*/
     USHORT  usMsgCode;	        /*消息码，具体消息类型的细分*/
     LONG    ulUserCode;        /* usertask user code */
     
     USHORT  usResponseType;    /*是否要求接收方用户应答：ACK/ NOACK/NEGACK*/
     USHORT  usFrameLen;        /*frame content 的长度 ，用户数据区长度*/
     VOID *  ptrMsgBody;        /*消息体指针*/
     USHORT  usAppSeqNum;       /*应用层系列号，用于发送方和接收方请求应答之间建立关联*/
     USHORT  usReserved;        /*保留 ，以后扩充使用*/
} SYS_MSG_S;


#ifdef __cplusplus
}
#endif

#endif /*__SYSDEF_H__*/


