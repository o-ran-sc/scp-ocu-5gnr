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
