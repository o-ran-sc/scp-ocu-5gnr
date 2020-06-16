/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/
#ifndef CUUP_UE_INFO_H
#define CUUP_UE_INFO_H

#include "vos_types.h"
#include "vos_lib.h"

#define FALSE 							0
#define TRUE 							1
#define MAX_UE_NUM						42

typedef struct cuupUeIdxInfo
{
	UINT8  isUsed;		/* TRUE:used, FALSE: not used */
	UINT16 ueIdx;
	UINT64 ueE1apId;
}CuupUeIdxInfo_t;

typedef struct cuupUeIdxTable
{
	CuupUeIdxInfo_t ueIdxInfo[MAX_UE_NUM];
}CuupUeIdxTable_t;

extern INT32 cuupAddUeE1apid(UINT64 ueE1apId, UINT16 *ueIdx, CuupUeIdxTable_t *pTable);
extern INT32 cuupDelUeIdx(UINT16 ueIdx, CuupUeIdxTable_t *pTable);
extern INT32 cuupGetUeIdx(UINT64 ueE1apId, UINT16 *ueIdx, CuupUeIdxTable_t *pTable);


#endif /* CUUP_UE_INFO_H */
