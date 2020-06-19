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


#ifndef PDCP_U_H
#define PDCP_U_H

#include "vos_linklist.h"
#include "pdcpCommon.h"
#include "msgb.h"
#include "cuupCommon.h"
#include "cuModuleCommon.h"
#include "plat_syslog.h"

#define PROFILE0X0001_PRENSENT 0x0001
#define PROFILE0X0002_PRENSENT 0x0002
#define PROFILE0X0003_PRENSENT 0x0004
#define PROFILE0X0004_PRENSENT 0x0008
#define PROFILE0X0006_PRENSENT 0x0010
#define PROFILE0X0101_PRENSENT 0x0020
#define PROFILE0X0102_PRENSENT 0x0040
#define PROFILE0X0103_PRENSENT 0x0080
#define PROFILE0X0104_PRENSENT 0x0100

#define pdcpuLog(iLog_Level, content, arg...) \
	VOS_SysLog(gPdcpuModuleId, iLog_Level, __FILE__, __LINE__, __func__, content, ##arg);

#define pdcpuNullCheck(p) \
{\
   if(NULL == p)\
   {\
	   pdcpuLog(LOG_ERR,"[PDCPU] NULL pointer\n");\
       return VOS_ERROR;\
   }\
}

#define pdcpuNullCheckRp(p) \
{\
   if(NULL == p)\
   {\
	   pdcpuLog(LOG_ERR,"[PDCPU] NULL pointer\n");\
       return NULL;\
   }\
}


#define pdcpuCheckUeIdx(n) if(n<0 || n>MAX_UE_NUM) {pdcpuLog(LOG_ERR,#n" is wrong\r\n");return VOS_ERROR;}
#define pdcpuCheckDrbId(n) if(n<1 || n>MAX_DRB_ID) {pdcpuLog(LOG_ERR,#n":%d is wrong\r\n");return VOS_ERROR;}
#define pdcpuCheckPduSessionId(n) if(n<0 || n>255) {pdcpuLog(LOG_ERR,#n" is wrong\r\n");return VOS_ERROR;}

#define pdcpuGetEntity(ueIdx, drbId, p)\
{\
	if((NULL==gPdcpuUeInfo[ueIdx])\
		||(NULL==gPdcpuUeInfo[ueIdx]->pdcpDrbEntity[drbId]))\
	{\
		p = NULL;\
	}else\
	{\
		p = gPdcpuUeInfo[ueIdx]->pdcpDrbEntity[drbId];\
	}\
}

#define pdcpuMsgbFree(p)\
{\
	if(NULL != p)\
	{\
		msgbFree(p);\
		p = NULL;\
	}\
}

typedef struct
{
	UINT16  pduSessionId;
	UINT8  integrityEnableFlag;
	UINT8  cipherEnableFlag;
	UINT64 maxIPDataRate;	/* Maximum Integrity Protected Data Rate */
}PdcpuSecEnableInfo_t;


typedef enum
{
	NEW_PACKET = 0,
	OLD_PACKET
}PdcpTxNodeType_e;

typedef enum
{
	PDCP_DISCARD_TIMER = 1,
	PDCP_REORDER_TIMER
}PdcpTimer_e;


typedef struct
{
	UINT32 			count;
	UINT32			f1uSn;		/* Not used in receiving buffer */
	MsgbBuff_t     *pData;
	UINT8 		    flag;
    struct timeval	startTime;
}PdcpuDataBuffNode_t;


typedef struct
{
    UINT16 				notUsed;
	RohcParaPR_e		rohcType;
    union
    {
		ROHCConfig_t	 rohcConfig;
		UplinkOnlyRohc_t uplinkOnlyRohc;
    }u;
}HeaderCompression_t;

typedef struct
{
	UINT8	  				drbId;
	UINT16					pduSessionId;
	UINT64					ueE1apId;
	UINT16 					ueIdx;
	UINT32 					rlcState;
	PdcpRlcMode_e 			rlcMode;
	UINT8					sdapUlHeadLen;
	UINT8					sdapDlHeadLen;
    PdcpSnSize_e 			pdcpSnSizeUl;
    PdcpSnSize_e 			pdcpSnSizeDl;
    HeaderCompression_t		headerCompress;

	UINT8 					tDiscardActive;			/* TRUE/FALSE */
	UINT8					tDiscardRun;			/* TRUE/FALSE */
	UINT16		 			tDiscard;				/* ms */
	ModuleMsg_t 			*pDiscardMsg;

	UINT8 					tReorderActive;			/* TRUE/FALSE */
	UINT8					tReorderRun;			/* TRUE/FALSE */
	UINT16			 		tReorder;				/* ms */
	ModuleMsg_t 			*pReorderMsg;
	LONG					tReorderId;

    MoreThanOneRLCContext 	moreThanOneRLCContext;
    UINT8 					integrityProtection;	/* TRUR: used, FALSE: not used */
    UINT8 					outOfOrderDelivery;
	UINT8 					ciperingEnabled;		/* TRUR: used, FALSE: not used */
	PdcpStateVar_t 			stateVar;

	plist					pTxPduList;				/* transmitting buffer */
	ULONG 					txListLock;				/* txListLock */

	plist					pRxSduList;				/* receiving buffer	   */
	ULONG 					rxListLock;				/* rxListLock */
}PdcpDrbEntity_t;

typedef struct
{
	UINT64  ueE1apId;
	UINT16  ueIdx;
	UINT32	kUpEnc[4];			/* 128 bit */
	UINT32	kUpInt[4];			/* 128 bit */
	UINT32	nh[8];				/* Next Hop parameter 256 bit */
	UINT8	ncc;				/* maximum: 3bit */
	UINT8	encAlgorithm;		/* Encryption Algorithm */
	UINT8	intAlgorithm;		/* Integrity Algorithm */
	UINT8	encActiveFlag;		/* define whether the encryption function has been activated */
	UINT8	intActiveFlag;		/* define whether the integrity protection function has been activated */
	UINT8	nhInd; 				/* 1: nh existed 0: not existed */
}PdcpuSecInfo_t;

typedef struct
{
	UINT16 			   	  ueIdx;
	CuupBearerStatus_e 	  ueStatus;
	PdcpuSecInfo_t   	 *secInfo;
	PdcpuSecEnableInfo_t *secEnableInfo[CUUP_MAX_SESSION_NUM];
	PdcpDrbEntity_t	  	 *pdcpDrbEntity[MAX_DRB_NUM];
}PdcpuUeInfo_t;

typedef struct
{
	UINT16 		ueIdx;
	UINT8		drbId;
}PdcpuDrbIdx_t;


#endif /* PDCP_U_H */
