/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/

#ifndef __SDAPCORE_H__
#define __SDAPCORE_H__

#include "vos_types.h"
#include "cuModuleInterface.h"
#include "upcContext.h"
#include "upcCommon.h"

#define UE_ACTIVITY_NOTIFY_LEVEL 		1
#define PDU_SESS_ACTIVITY_NOTIFY_LEVEL 	2
#define DRB_ACTIVITY_NOTIFY_LEVEL 		3

typedef struct
{
	UINT64 ueDataCount;
}UeActivityNotify_t;

typedef struct
{
	UINT64 pduDataCount[256];
}PduSessActivityNotify_t;

typedef struct
{
	UINT64 drbDataCount[33];
}DrbActivityNotify_t;

typedef struct
{
	UINT64  ueE1apId;
	UINT8   notifyLevel;	/*UE, PDU SESSION, DRB*/
    union {
        UeActivityNotify_t 			ueNotify;
        PduSessActivityNotify_t 	pduSessNotify;
		DrbActivityNotify_t 		drbNotify;
    }u;
}SdapActivityNotify_t;


/* 1、每个实体内的Session  ID、drbID、QosFlowId，都是连续的 
   2、Session和Qos相关的信息都是以ID作为下标保存的
   3、DRB是以DRB ID - 1 保存的*/

/* 实体的配置结果和实体的保存原则是一致的 */

typedef struct
{
	UINT64				drbId;
	UINT16				QosNum;
	UINT64				Qfi[UPC_MAX_QOS_PARA_NUM];
	UINT64				failQosNum;
	UINT64				failQfi[UPC_MAX_QOS_PARA_NUM];
	E1apCause_e			cause[UPC_MAX_QOS_PARA_NUM];
}SdapDrbCfgRet_t;

typedef struct
{
	UINT64				sessId;
	E1apCause_e			sessFailCause;

	/* Setup */
	UINT16				actDrbNum;
	UINT8				actDrbId[UPC_MAX_DRB_NUM];
	SdapDrbCfgRet_t		actDrbCfg[UPC_MAX_DRB_NUM];
	UINT16				failDrbNum;
	UINT64				failDrbId[UPC_MAX_DRB_NUM];
	E1apCause_e			cause[UPC_MAX_DRB_NUM];

	/* Modify */
	UINT16				modDrbNum;
	UINT8				modDrbId[UPC_MAX_DRB_NUM];
	SdapDrbCfgRet_t		modDrbCfg[UPC_MAX_DRB_NUM];
	UINT16				failModDrbNum;
	UINT64				failModDrbId[UPC_MAX_DRB_NUM];
	E1apCause_e			modCause[UPC_MAX_DRB_NUM];
}sdapSessCfgRet_t;

typedef struct
{
	UINT64				drbId;
	SdapCfg_t			sdapCfg;
	UINT8				qfiNum;
	INT64				qfi[UPC_MAX_QOS_PARA_NUM];
	QoSFlowQosItem_t	qosFlowInfo[UPC_MAX_QOS_PARA_NUM];
}SdapDrbCfg_t;

typedef struct
{
	UINT64				sessId;
	UINT8				drbNum;
	UINT64				drbId[UPC_MAX_DRB_NUM];
	SdapDrbCfg_t		drbCfg[UPC_MAX_DRB_NUM];
}SdapInstance_t;

typedef struct
{
	UINT64				upE1apId;
	UINT16				sessNum;
	UINT16				sessId[UPC_MAX_SESSION_NUM];
	SdapInstance_t		sdapInstance[UPC_MAX_SESSION_NUM];
}SdapGlobalDtat_t;

typedef struct
{
	UINT8   QFI :6;
	UINT8   RQI :1;
	UINT8	RDI :1;
}sdapDlHeader_t;

typedef struct
{
	UINT8   QFI  :6;
	UINT8   R    :1;
	UINT8	TYPE :1;
}sdapUlHeader_t;


#define SDAP_HEADER_LEN			1

SdapGlobalDtat_t* sdapGetUeGlobalData(UINT64	upE1apId, UINT8 *flag);
INT32 sdapCreateInstance(UINT64	upE1apId, upcTempSessInfo_t *pSessTempInfo, sdapSessCfgRet_t *pCfgRet);
INT32 sdapModSetupInstance(UINT64	upE1apId, upcTempSessInfo_t *pSessTempInfo, sdapSessCfgRet_t *pCfgRet);
INT32 sdapModInstance(UINT64	upE1apId, upcTempSessInfo_t *pSessTempInfo, sdapSessCfgRet_t *pCfgRet);
INT32 sdapDeleteDrbInfo(SdapInstance_t *pSdapInstance, UINT8 drbId);
INT32 sdapDeleteDrbInfoOfInstance(UINT64 upE1apId, UINT8 sessId, UINT8 drbId);
INT32 sdapDeleteInstance(UINT64	upE1apId, UINT16 sessId);

#endif
