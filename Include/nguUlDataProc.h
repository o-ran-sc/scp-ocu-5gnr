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


#ifndef NGU_UL_DATA_PROC_H
#define NGU_UL_DATA_PROC_H

#include "cuupCommon.h"
#include "msgb.h"

extern INT32 nguUlDataProc(UINT64 ueE1apId, UINT16 pduSessionId, UINT8 qfi, MsgbBuff_t *pMsgBuff);

#endif /* NGU_UL_DATA_PROC_H */
