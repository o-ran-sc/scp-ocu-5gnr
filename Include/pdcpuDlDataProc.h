/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/

#ifndef PDCPU_DL_DATA_PROC_H
#define PDCPU_DL_DATA_PROC_H

#include "vos_types.h"
#include "cuupCommon.h"
#include "msgb.h"

extern INT32 pdcpuDlDataProc(UINT64 ueE1apId, UINT8 drbId, MsgbBuff_t *pMsgBuff, UINT8 sdapPduType);

#endif /* PDCPU_DL_DATA_PROC_H */
