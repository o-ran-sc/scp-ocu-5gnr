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


#ifndef F1U_COMMON_H
#define F1U_COMMON_H

#include "gnbCommon.h"

#define DL_USER_DATA				0
#define DL_DATA_DELIVERY_STATUS		1
#define CUF1U_PDU_SESSION_MAX_NUM 256

typedef enum{
	LEN_12_BITS = 0,
	LEN_18_BITS = 1
}PDCPSnSize_e;

/* CU-F1-U instance */
typedef struct {
	UINT64 				ueE1apId;
	UINT16  			ueIdx;
	UINT8		  		drbId;
	UINT16				pduSessionId;
	UINT32  	  		nextSubmitSn;
	PDCPSnSize_e 	 	pdcpSnSize;
	UINT32  	  		ownTeid;         /* Local teid */
}Cuf1uInstance_t;


#endif /* F1U_COMMON_H */
