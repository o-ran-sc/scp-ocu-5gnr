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

#include "sdapCore.h"
#include "msgb.h"
#include "bitsPack.h"
#include "pdcpuDlDataProc.h"
#include "nguUlDataProc.h"
#include "cuupTest.h"


INT8 sdapMatchQosFlowId(SdapInstance_t *pSdapInstance, INT64	qosFlowId, UINT64	*pDrbId, UINT8 *pFlag)
{
	int i = 0;
	int j = 0;
	UINT64 drbId = 0;
	SdapDrbCfg_t sdapDrbCfg = {0};

	for(i = 0; i < pSdapInstance->drbNum; i++)
	{
		drbId = pSdapInstance->drbId[i];

		VOS_MemCpy(&sdapDrbCfg, &pSdapInstance->drbCfg[drbId - 1], sizeof(SdapDrbCfg_t));

		for(j = 0; j < sdapDrbCfg.qfiNum; j++)
		{
			if(qosFlowId == sdapDrbCfg.qfi[j])
			{
				*pDrbId = drbId;
				break;
			}
		}
	}

	/* 没有查找到DRB，映射到默认的DRB */
	if(0 == *pDrbId)
	{
		for(i = 0; i < pSdapInstance->drbNum; i++)
		{
			drbId = pSdapInstance->drbId[i];

			/* 一个实例，即一个会话内，有且只有一个默认的DRB */
			if(DEFAULT_DRB_TRUE == pSdapInstance->drbCfg[drbId - 1].sdapCfg.defaultDrbInd)
			{
				*pDrbId = drbId;
				*pFlag = 1;
				break;
			}
		}
	}

	return VOS_OK;
}

INT8 sdapPackPduHead(SdapInstance_t *pSdapInstance, INT64	qosFlowId, UINT64	*pDrbId, MsgbBuff_t *pMsgBuff, UINT8 rqi)
{
	UINT8 *p= NULL;
	UINT64 qosNum = 0;
	UINT8  updateFlag = 0;
	sdapDlHeader_t sdapHeader = {0};
	INT8	pduHeadLen = 0;

	if(VOS_OK != sdapMatchQosFlowId(pSdapInstance, qosFlowId, pDrbId, &updateFlag))
	{
		return VOS_ERROR;
	}

	if(*pDrbId < 1 || *pDrbId > 32)
	{
		return VOS_ERROR;
	}

	/*表明默认DRB上，增加了一条QOS的映射*/
	if(1 == updateFlag)
	{
		qosNum = pSdapInstance->drbCfg[*pDrbId -1].qfiNum;
		pSdapInstance->drbCfg[*pDrbId -1].qfi[qosNum] = qosFlowId;
		pSdapInstance->drbCfg[*pDrbId -1].qfiNum++;
	}

	if(SDAP_HEADER_PRESENT == pSdapInstance->drbCfg[*pDrbId - 1].sdapCfg.sdapDlHeaderInd)
	{
		sdapHeader.QFI = qosFlowId;
		if(1 == updateFlag)
		{
			sdapHeader.RDI = 1;
		}

		sdapHeader.RQI = rqi;

		pduHeadLen = sizeof(sdapDlHeader_t);

		p = msgbHeadPush(pMsgBuff, pduHeadLen);
		VOS_MemCpy(p, &sdapHeader, pduHeadLen);

		return pduHeadLen;
	}

	/* 没有消息头的配置 */
	return 0;
}

INT32 sdapDlDataProc(UINT64 upE1apId, UINT64 sessId, INT64	qosFlowId, MsgbBuff_t *pMsgBuff, UINT8 rqi)
{
	int i = 0;
	UINT8	flag = 0;
	UINT16  sduLen = 0;
	INT8	pduHeadLen = 0;
	UINT64	drbId = 0;

	SdapGlobalDtat_t	*pGlobalData = NULL;
	SdapInstance_t		*pSdapInstance = NULL;
	UINT8 *pMsgHead   = NULL;

	if(NULL == pMsgBuff)
	{
		return VOS_ERROR;
	}

	/* Get Instance */
	pGlobalData = sdapGetUeGlobalData(upE1apId, &flag);

	if(NULL == pGlobalData || 0 == flag)
	{
		return VOS_ERROR;
	}

	for(i = 0; i < pGlobalData->sessNum; i++)
	{
		if(sessId == pGlobalData->sessId[i])
		{
			pSdapInstance = &pGlobalData->sdapInstance[sessId];
			break;
		}
	}

	if(NULL == pSdapInstance)
	{
		return VOS_ERROR;
	}

	sduLen = msgbDataUsedLen(pMsgBuff);	//length of sdap sdu, not include sdap pdu head
	pMsgHead = msgbData(pMsgBuff);//start of sdap sdu, not include sdap pdu head

	if(0 > sduLen || NULL == pMsgHead)
	{
		return VOS_ERROR;
	}

	pduHeadLen = sdapPackPduHead(pSdapInstance, qosFlowId, &drbId, pMsgBuff, rqi);

	if(VOS_ERROR == pduHeadLen)
	{
		return VOS_ERROR;
	}

	/*传递到PDCP-U*/
	pdcpuDlDataProc(upE1apId, drbId, pMsgBuff, 1);

	return VOS_OK;
}

INT8 sdapUnPackPduHead(MsgbBuff_t *pMsgBuff)
{
	BitOpt_t bit;
	UINT32	bitSize = 0;

	UINT8 *pMsgHead = msgbData(pMsgBuff);
	UINT16 pduLen = msgbDataUsedLen(pMsgBuff);

	initBits(&bit, pMsgHead, pduLen, 0);

	/* SDAP头固定长度 1 */
	bitSize = SDAP_HEADER_LEN*8;

	if(-1 == unpackBits(&bit, bitSize))
	{
		return VOS_ERROR;
	}

	return SDAP_HEADER_LEN;
}

INT32 sdapUlDataProc(UINT64 upE1apId, UINT64 sessId, UINT64 drbId, MsgbBuff_t *pMsgBuff)
{
	int i = 0;
	UINT8	flag = 0;
	INT8	pduHeadLen = 0;

	sdapUlHeader_t *pHead = NULL;
	UINT8 qosFlowId = 0xff;
	UINT8 pduType   = 0;

	SdapGlobalDtat_t	*pGlobalData = NULL;
	SdapInstance_t		*pSdapInstance = NULL;
	SdapDrbCfg_t		*pDrbCfgInfo = NULL;

	if(NULL == pMsgBuff)
	{
		return VOS_ERROR;
	}

	/* Get Instance */
	pGlobalData = sdapGetUeGlobalData(upE1apId, &flag);

	if(NULL == pGlobalData || 0 == flag)
	{
		return VOS_ERROR;
	}

	/* get instance */
	for(i = 0; i < pGlobalData->sessNum; i++)
	{
		if(sessId == pGlobalData->sessId[i])
		{
			pSdapInstance = &pGlobalData->sdapInstance[sessId];
			break;
		}
	}

	if(NULL == pSdapInstance)
	{
		return VOS_ERROR;
	}

	/* get Drb Cfg */
	for(i = 0; i < pSdapInstance->drbNum; i++)
	{
		if(drbId == pSdapInstance->drbId[i])
		{
			pDrbCfgInfo = &pSdapInstance->drbCfg[drbId - 1];
			break;
		}
	}

	if(NULL == pDrbCfgInfo)
	{
		return VOS_ERROR;
	}

	/* 有消息头的情况，去头 */
	if(SDAP_HEADER_PRESENT == pDrbCfgInfo->sdapCfg.sdapUlHeaderInd)
	{
		pduHeadLen = sdapUnPackPduHead(pMsgBuff);

		pHead	  = (sdapUlHeader_t *)msgbData(pMsgBuff);
		qosFlowId = pHead->QFI;
		pduType   = pHead->TYPE;

		if(!pduType)
		{
			/* receive control pdu */
			return VOS_OK;
		}

		/* check qosFlowId */
		for(i = 0; i < pDrbCfgInfo->qfiNum; i++)
		{
			if(pDrbCfgInfo->qfi[i] == qosFlowId)
			{
				break;
			}
		}

		if(i < pDrbCfgInfo->qfiNum)
		{
			/* qfi found */
			msgbHeadPull(pMsgBuff, pduHeadLen);
		}else
		{
			/* qfi not found */
			return VOS_ERROR;
		}

	}


	/* 调用NG-U的上行数据处理接口 */
	return nguUlDataProc(upE1apId, sessId, qosFlowId, pMsgBuff);
}
