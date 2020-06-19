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


#ifndef NG_U_H
#define NG_U_H

#include "vos_lib.h"
#include "cuupCommon.h"
#include "plat_syslog.h"

#define DL_PDU_SESSION_INFORMATION 	0	/* NGU DL PDU type */
#define UL_PDU_SESSION_INFORMATION 	1	/* NGU UL PDU type */

#define NGU_FREE(p) if(NULL != p)\
					{\
						VOS_Free(p);\
						p = NULL;\
					}

#define nguLog(iLog_Level, content, arg...) \
	VOS_SysLog(gNguModuleId, iLog_Level, __FILE__, __LINE__, __func__, content, ##arg);

#define nguNullCheck(p) \
{\
   if(NULL == p)\
   {\
	   nguLog(LOG_ERR, "[NGU] NULL pointer\n");\
       return VOS_ERROR;\
   }\
}

#define nguGetInstance(ueIdx,pduSessId,p) \
{\
	if((NULL == gNguUeInfo[ueIdx])\
		|| (NULL == gNguUeInfo[ueIdx]->nguInstance[pduSessId]))\
	{\
		p = NULL;\
	}else\
	{\
		p = gNguUeInfo[ueIdx]->nguInstance[pduSessId];\
	}\
}

#define nguDlDataCheck(p) 	if(NULL == p)\
							{\
								nguLog(LOG_ERR,"[NGU] input is NULL!\n");\
								return VOS_ERROR;\
							}else if(NULL==p->pMsgBuff)\
							{\
								nguLog(LOG_ERR,"[NGU] p->pMsgBuff in input is NULL!\n");\
								return VOS_ERROR;\
							}\

#define nguExPduCheck(p)	if(NULL == p)\
							{\
								nguLog(LOG_ERR,"[NGU] ex pdu is null\n");\
								return VOS_ERROR;\
							}else if( (GTP_EXT_PDUSESSION_CONTAINER!=p->exHdrType) || (NULL==p->pPdu) || (p->len<=0))\
							{\
								nguLog(LOG_ERR,"[NGU] ex pdu is wrong\n");\
								return VOS_ERROR;\
							}

#define nguDlDataFree(p) \
{\
	if(NULL != p)\
	{\
		if(NULL != p->pExPduInfo)\
		{\
			if(NULL != p->pExPduInfo->pPdu)\
			{\
				NGU_FREE(p->pExPduInfo->pPdu);\
				p->pExPduInfo->pPdu = NULL;\
			}\
			NGU_FREE(p->pExPduInfo);\
			p->pExPduInfo = NULL;\
		}\
		NGU_FREE(p);\
		p = NULL;\
	}\
}



typedef struct
{
	UINT64			ueE1apId;
	UINT16			ueIdx;
	UINT16		   	pduSessionId;
	UINT32    		ownTeid;
}NguInstance_t;


typedef struct
{
	UINT16		   		ueIdx;
	UINT64				ueE1apId;
	CuupBearerStatus_e 	ueStatus;
	NguInstance_t 		*nguInstance[CUUP_MAX_SESSION_NUM];
}NguUeInfo_t;


typedef struct dlPduSessInfo
{
	UINT8 exHdrLen;		/* gtp extension head length:2 */
	UINT8 spare1 :4;	/* spare: 0 */
	UINT8 pduType :4;	/* pdu type:0 */
	UINT8 qfi :6;		/* qfi */
	UINT8 rqi :1;
	UINT8 ppp :1;
	UINT8 spare2 :5;
	UINT8 ppi :3;
	UINT8 padding[3];
	UINT8 nextExHdrType;/* next extension head type:0 */
}DlPduSessInfo_t;

typedef struct ulPduSessInfo
{
	UINT8 exHdrLen;		/* gtp extension head length:1 */
	UINT8 spare1 :4;	/* spare: 0 */
	UINT8 pduType :4;	/* pdu type:1 */
	UINT8 qfi :6;		/* qfi */
	UINT8 spare2 :2;
	UINT8 nextExHdrType;/* next extension head type:0 */
}UlPduSessInfo_t;


#endif /* NG_U_H */
