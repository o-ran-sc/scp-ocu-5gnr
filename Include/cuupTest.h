/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2019] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/
#ifndef CUUP_TEST_H
#define CUUP_TEST_H

#include "vos_socket.h"
#include "pdcpu.h"
#include "ngu.h"
#include "cuupCommon.h"
#include "f1uCommon.h"
#include "gtpCommon.h"
#include "cuupUeIdTransf.h"
#include "msgb.h"
#include "sdapCore.h"

extern INT32 printfTransLayerAddr(TransLayerAddr_t *pAddr);
extern INT32 printfNguInstance(NguInstance_t *pNguInstance);
extern INT32 printfNguCfgResult(NguCfgResult_t *pCfg);
extern INT32 printfDrbEntity(PdcpDrbEntity_t *pEntity);
extern INT32 printfPdcpuCfgResult(PdcpuCfgResult_t *pResult);
extern INT32 printfCuf1uInstance(Cuf1uInstance_t *pF1u);
extern INT32 printfCuf1uCfgResult(Cuf1uCfgResult_t *pResult);
extern INT32 printfPdcpuSecInfo(PdcpuSecInfo_t *pSec);
extern INT32 printfVosSockAddr(vos_sockaddr_t *pAddr);
extern INT32 printfTun(Tun_t *pTun);
extern INT32 printfPdcpuSecEnableInfo(PdcpuSecEnableInfo_t *pInfo);
extern INT32 printfCuupUeIdxTable(CuupUeIdxTable_t *pTable);
extern INT32 printfMsgbBuff(MsgbBuff_t *pMsgBuff);
extern INT32 printfExPduInfo(ExPduInfo_t *pPdu);

#endif /* CUUP_TEST_H */
