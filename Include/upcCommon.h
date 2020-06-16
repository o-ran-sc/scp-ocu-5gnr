/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef __UPCCOMMON_H__
#define __UPCCOMMON_H__

#include "plat_syslog.h"
#include "cuCommon.h"
#include "upcContext.h"

#define CONCEPT(x)		1

extern UpInstance_t	s_UpcGlobalData;

#define UPC_MODULE_ID		s_UpcGlobalData.moduleId

#define upclog(level, content, arg...)	VOS_SysLog(UPC_MODULE_ID, level, __FILE__, __LINE__, "", content, ##arg);

#define UPC_MIN(x, y)  ((x) <= (y)? (x) : (y))

#define UPC_PRESENCE(bitmask,bit)     ((bit) == ((bit) & (bitmask)))

#define UPC_CHECK_NULL(prama) \
{\
   if (NULL == prama)\
   {\
	   upclog(LOG_ERR, "UPC NULL pointer\n");\
	   VOS_ASSERT(0);	\
       return VOS_ERROR;\
   }\
}

INT32 upcSendE1apMsg(void *pMsg, UINT64	msgLen);

extern INT32 vosAdpSendAsynMsg2ModuleEx(          CHAR src_moduleName[MODULE_NAME_LEN],
                                           CHAR dst_moduleName[MODULE_NAME_LEN],                                      
                                           VOID *msgData,
                                           LONG msgDataLen);
INT32 upcConstructAndSendOamUpActRsp(int actNum, int failNum, CellIdList_t	failCellList);
void upcResortDrbId(UpSessCb_t *pSessCb, UINT8 drbId);
INT32 upcCheckSessId(UpUeCb_t *pUeCb, UINT8	sessId);
UINT32 upcCheckDrbId(UpUeCb_t *pUeCb, UINT8	drbId);
void upcFreeTempInfo(upcTempInfo_t *pTempInfo);
void upcCauseConvertToInterfaceType(E1apCause_e srcCause, E1apCause_t *dstCause);
extern UINT32 cuAppGetCucommonParaNum();
INT32 upcSendUpOamMsg(void *pMsg, UINT64	msgLen);
INT32 upcGetBearerModFailureFlag(UINT16 bitMask, UINT8 setupFailFlag, UINT8 ModFailFlag);

#ifdef NR_CUUP
INT32 upcNotifyOmaUpConnectState(INT32 state);
#endif

#endif
