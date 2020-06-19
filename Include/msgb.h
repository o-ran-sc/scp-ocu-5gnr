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


#ifndef	MSGB_H
#define	MSGB_H

#include "vos_lib.h"
#include "vos_types.h"
#include "vos_string.h"

extern ULONG gMsgbFreeCount;

typedef struct
{
	UINT16	maxHeadLen;			/* Head域预留的长度 */
	UINT16  maxDataLen;			/* Data域预留的长度 */
	UINT16 	headSpareLen;		/* Head域空闲的长度 */
	UINT16 	tailOffset;			/* 数据尾端到dataBuff[]起始位置的距离，包括1.整个Head域 2.Data域的使用部分 */
}MsgbInfo_t;

typedef struct
{
	MsgbInfo_t 	msgbInfo;
	UINT8 		dataBuff[0];	/* DataBuff域的起始地址,指向msgbInfo变量后面的地址,该成员不占用内存 */
}MsgbBuff_t;


INT32 msgbCheck(MsgbBuff_t *pMsgBuff);
MsgbBuff_t *msgbAllocWithDebug(UINT16 dataLen, UINT16 maxHeadLen, ULONG moduleId,unsigned char *file, unsigned long line);
UINT8 *msgbDataWithDebug(MsgbBuff_t *pMsgBuff,unsigned char *fun, unsigned long line);
UINT8 *msgbTailWithDebug(MsgbBuff_t *pMsgBuff,unsigned char *fun, unsigned long line);
UINT16 msgbDataUsedLenWithDebug(MsgbBuff_t *pMsgBuff,unsigned char *fun, unsigned long line);
UINT16 msgbDataAllocLenWithDebug(MsgbBuff_t *pMsgBuff,unsigned char *fun, unsigned long line);
UINT8 *msgbHeadPushWithDebug(MsgbBuff_t *pMsgBuff, UINT32 len,unsigned char *fun, unsigned long line);
UINT8 *msgbHeadPullWithDebug(MsgbBuff_t *pMsgBuff, UINT32 len,unsigned char *fun, unsigned long line);
UINT8 *msgbTailPushWithDebug(MsgbBuff_t *pMsgBuff, UINT32 len,unsigned char *fun, unsigned long line);
UINT8 *msgbTailPullWithDebug(MsgbBuff_t *pMsgBuff, UINT32 len,unsigned char *fun, unsigned long line);


#define msgbAlloc( dataLen,  maxHeadLen,  moduleId) msgbAllocWithDebug( dataLen,  maxHeadLen,  moduleId,(UCHAR *)__func__,__LINE__)



#define msgbData(pMsgBuff) msgbDataWithDebug(pMsgBuff,(UCHAR *)__func__,__LINE__)

#define msgbTail(pMsgBuff) msgbTailWithDebug(pMsgBuff,(UCHAR *)__func__,__LINE__)

#define msgbDataUsedLen(pMsgBuff) msgbDataUsedLenWithDebug(pMsgBuff,(UCHAR *)__func__,__LINE__)

#define msgbDataAllocLen(pMsgBuff) msgbDataAllocLenWithDebug(pMsgBuff,(UCHAR *)__func__,__LINE__)

extern UINT16 msgbHeadLeftRoom(MsgbBuff_t *pMsgBuff);

extern UINT16 msgbTailLeftRoom(MsgbBuff_t *pMsgBuff);


#define msgbFree(pMsgBuff)\
({\
	if(NULL == pMsgBuff)\
	{\
	vos_err_print("input is NULL!\n");\
	}\
	VOS_Free(pMsgBuff);\
	gMsgbFreeCount++;\
})


#define msgbHeadPush(pMsgBuff,  len) msgbHeadPushWithDebug(pMsgBuff,  len,(UCHAR *)__func__,__LINE__)

#define msgbHeadPull(pMsgBuff,  len) msgbHeadPullWithDebug(pMsgBuff,  len,(UCHAR *)__func__,__LINE__)

#define msgbTailPush(pMsgBuff,  len) msgbTailPushWithDebug(pMsgBuff,  len,(UCHAR *)__func__,__LINE__)

#define msgbTailPull(pMsgBuff,  len) msgbTailPullWithDebug(pMsgBuff,  len,(UCHAR *)__func__,__LINE__)

#endif	/* MSGB_H */
