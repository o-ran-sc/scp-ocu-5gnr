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
