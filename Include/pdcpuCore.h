/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/

#ifndef PDCPU_CORE_H
#define PDCPU_CORE_H

#include "vos_types.h"
#include "cuModuleInterface.h"
#include "upcContext.h"

extern VOID pdcpuFreeDataBuffNode(VOID *p);

extern INT32 pdcpuCreateEntity(UINT64 ueE1apId, UINT16 ueIdx, UINT16 pduSessionId, upcTempDrbInfo_t *pDrbItem);

extern INT32 pdcpuModCreateEntity(UINT64 ueE1apId, UINT16 ueIdx, UINT16 pduSessionId, upcTempDrbInfo_t *pDrbItem);

extern INT32 pdcpuUpdateEntity(UINT16 ueIdx, UINT16 pduSessionId, upcTempDrbInfo_t *pDrbItem);

extern INT32 pdcpuDeleteEntity(UINT16 ueIdx, UINT8 drbId);

extern INT32 pdcpuDiscardByHighestDelivSn(UINT16 ueIdx, UINT8 drbId, UINT32 sn);

extern INT32 pdcpuRetransmit(UINT16 ueIdx, UINT8 drbId, UINT32 f1uSnStart, UINT32 f1uSnEnd);

#endif /* PDCPU_CORE_H */
