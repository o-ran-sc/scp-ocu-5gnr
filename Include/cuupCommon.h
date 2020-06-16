/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/

#ifndef CU_UP_COMMON_H
#define CU_UP_COMMON_H

#include "vos_types.h"
#include "gnbServiceType.h"
#include "cuModuleCommon.h"
#include "cuModuleInterface.h"


#define CUUP_MAX_SESSION_NUM  	256
#define CFG_OK 					0
#define CFG_FAIL 				-1
#define SECURITY_PERFORMED 		0
#define SECURITY_NOT_PERFORMED 	1
#define CUUP_DL_HEAD_LEN 		4	// SDAP MAX HEAD 1 + PDCP MAX HEAD +3
#define CUUP_UL_HEAD_LEN 		0
#define AS_KEY_LEN				4	//4 bytes

/**
 * @brief calc function run time
 */
 #define CUUP_CALC_ELAPSED_TIME(func)			\
({										\
    struct timeval start, end;			\
	INT64 diff;							\
    gettimeofday(&start,0);	\
	func;								\
    gettimeofday(&end,0);				\
    diff = ( end.tv_sec*1000000L + end.tv_usec ) 		\
        - ( start.tv_sec*1000000L + start.tv_usec );	\
    vos_info_print("func %s spend time = %ld us\n",#func ,diff);\
})

/* brief UE E1AP ID */
typedef UINT32    CuupUeE1apId;

/* brief Session ID */
typedef UINT8    CuupSessionId;    		/* INTEGER (0 ..255) 38463 */

/* brief Data Radio Bearer ID */
typedef UINT8    CuupDrbId;

/* brief QFI */
typedef UINT8    CuupQFI;

typedef enum
{
    PDU_SESSION_ADD,    	/* SESSION TO SETUP */
    PDU_SESSION_MOD,        /* SESSION TO MODIFY */
    PDU_SESSION_DEL,        /* SESSION TO DELETE */
    DRB_DEL,				/* DRB TO DELETE */
    UE_RELEASE
}UpcCfgType_e;

typedef struct
{
	UINT64 ueE1apId;
	UINT8  drbId;
}drbToDel_t;

typedef struct
{
	UpcCfgType_e	 	 cfgType;
	UINT16				 pduSessionId;
	INT8				 cfgResult;	//will be removed
	UINT32				 nggtpuTeid;
	TransLayerAddr_t	 nggtpuAddr;
	E1apCause_e			 failureCause;
}NguCfgResult_t;

typedef struct
{
	UINT8 		drbId;
	E1apCause_e cause;
}DrbFailedCause_t;

typedef struct
{
	UpcCfgType_e		cfgType;
	UINT8				secResPresent;
	SecuResult_t		secuResult;
	UINT16				pduSessionId;
	UINT8				drbSetupSuccessNum;
	UINT8				drbSetupSuccessArray[MAX_DRB_NUM];
	UINT8				drbSetupFailNum;
	DrbFailedCause_t	drbSetupFailedArray[MAX_DRB_NUM];
	UINT8				drbModifySuccessNum;
	UINT8				drbModifySuccessArray[MAX_DRB_NUM];
	UINT8				drbModifyFailNum;
	DrbFailedCause_t	drbModifyFailedArray[MAX_DRB_NUM];
	E1apCause_e			pduSessionCause;
}PdcpuCfgResult_t;

typedef struct
{
	UINT8  drbId;
	UINT32 f1gtpuTeid;
	TransLayerAddr_t gtpuAddr;
}Cuf1uSetupInfo_t;

typedef struct
{
	UpcCfgType_e		cfgType;
	UINT16				pduSessionId;
	UINT8				drbSetupSuccessNum;
	Cuf1uSetupInfo_t	drbSetupSuccessArray[MAX_DRB_NUM];
	UINT8				drbSetupFailNum;
	DrbFailedCause_t	drbSetupFailedArray[MAX_DRB_NUM];
	UINT8				drbModifySuccessNum;
	UINT8				drbModifySuccessArray[MAX_DRB_NUM];
	UINT8				drbModifyFailNum;
	DrbFailedCause_t	drbModifyFailedArray[MAX_DRB_NUM];
	E1apCause_e			pduSessionCause;
}Cuf1uCfgResult_t;

typedef enum
{
	CUUP_BEARER_NORMAL,
	CUUP_BERAER_SUSPEND,
	CUUP_DETECT_DL_DATA  /* in suspend, ngu recv dl data */
}CuupBearerStatus_e;

typedef struct bearerCxtInactive_s
{
    CuupUeE1apId ueId;
    UINT8   tag;
    union {
        E1apDrbActivityList_t drbActivityList;
        E1apPduSessionActivityList_t pduSessionActivityList;
        E1apUeActivity_t ueActivity;
    }u;
}BearerCxtInactive_t;
extern INT32 ifmUpcBearerCxtInactiveNotification(BearerCxtInactive_t *bearerCxtInactive);
extern INT32 ifmUpcDlDataNotification(UINT64 ueE1apId, UINT8 PPI);
#endif /* CU_UP_COMMON_H */

