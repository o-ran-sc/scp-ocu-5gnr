/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/

#ifndef NGU_UL_DATA_PROC_H
#define NGU_UL_DATA_PROC_H

#include "cuupCommon.h"
#include "msgb.h"

extern INT32 nguUlDataProc(UINT64 ueE1apId, UINT16 pduSessionId, UINT8 qfi, MsgbBuff_t *pMsgBuff);

#endif /* NGU_UL_DATA_PROC_H */
