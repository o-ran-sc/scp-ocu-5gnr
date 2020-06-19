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

#include "vos_types.h"
#include "vos_string.h"
#include "vos_linklist.h"
#include "vos_sem.h"
#include "pdcpu.h"
#include "cuupCommon.h"
#include "cuModuleInterface.h"
#include "gnbCommon.h"
#include "upcContext.h"
#include "cuupTest.h"

PdcpuUeInfo_t *gPdcpuUeInfo[MAX_UE_NUM];
extern ULONG gPdcpuModuleId;

/* not used at the moment */
/*void pdcpuSetLessCountFun(const void* cpv_first, const void* cpv_second, void* pv_output)
{
	assert(cpv_first != NULL && cpv_second != NULL && pv_output != NULL);

   *(bool_t*)pv_output = (((PdcpuDataBuffNode_t *)cpv_first)->count) < (((PdcpuDataBuffNode_t *)cpv_second)->count) ? true : false;
}*/


/** 释放一个 PdcpuDataBuffNode_t 数据,赋值给plist->del */
VOID pdcpuFreeDataBuffNode(VOID *p)
{
	PdcpuDataBuffNode_t *pNode = NULL;
	if(NULL == p)
	{
		return ;
	}

	pNode = (PdcpuDataBuffNode_t *)p;
	if(NULL != pNode->pData)
	{
		msgbFree(pNode->pData);
		pNode->pData = NULL;
	}
	VOS_Free(p);
	p = NULL;

	return ;
}

/*******************************************************************************
 * discard all stored PDCP PDUs in the transmitting buffer
 * INPUT:
 *		pTxPduList: transmitting buffer list
 * OUTPUT:
 *		0: success
 *		-1:failed
 *******************************************************************************/
INT32 pdcpuDiscardTransmitBuff(plist pTxPduList)
{
	return VOS_OK;
}

/*******************************************************************************
 * transmit or retransmit all stored PDCP PDUs in the transmitting buffer
 * INPUT:
 *		pTxPduList: transmitting buffer list
 * OUTPUT:
 *		0: success
 *		-1:failed
 *******************************************************************************/
INT32 pdcpuDeliverTransmitBuff(PdcpDrbEntity_t *pPdcpuEntity)
{
	return VOS_OK;
}

/*******************************************************************************
 * deliver the PDCP SDUs stored in the receiving buffer to upper layers
 * in ascending order of associated COUNT values
 * INPUT:
 *		pTxPduList: transmitting buffer list
 * OUTPUT:
 *		0: success
 *		-1:failed
 *******************************************************************************/
INT32 pdcpuDeliverRecvBuff(PdcpDrbEntity_t *pPdcpuEntity)
{
	return VOS_OK;
}


/*******************************************************************************
 * To construct and send a PDCP status report
 * INPUT:
 *		pPdcpuEntity: pdcpu entity
 * OUTPUT:
 *		0: success
 *		-1:failed
 *******************************************************************************/
INT32 pdcpuConstructStatusReport(PdcpDrbEntity_t *pPdcpuEntity)
{
	return VOS_OK;
}

/*******************************************************************************
 * To perform PDCP data recovery
 * INPUT:
 *		ueE1apId: UE E1AP ID
 *		drbId : DRB ID
 * OUTPUT:
 *		0: success
 *		-1:failed
 *******************************************************************************/
INT32 pdcpuDataRecovery(PdcpDrbEntity_t *pPdcpuEntity)
{
	return VOS_OK;
}

INT32 pdcpuRecfgRohc(PdcpDrbEntity_t *pPdcpuEntity, upcTempDrbInfo_t *pDrbItem)
{
    return VOS_OK;
}



INT32 pdcpuSetSn(PdcpSnSize_e *pSn, PdcpSNSize_e snCfg)
{
	if(PDCP_SN_SIZE_S12 == snCfg)
	{
		*pSn = LEN12BITS;

	}else if(PDCP_SN_SIZE_S18 == snCfg)
	{
		*pSn = LEN18BITS;

	}else
	{
		pdcpuLog(LOG_ERR,"[PDCPU] input sn size is wrong!\n");
		return VOS_ERROR;
	}

	return VOS_OK;
}

INT32 pdcpuSetRlcMode(PdcpRlcMode_e *pRlcMode, CuRlcMode_e rlcCfg)
{
	switch(rlcCfg)
	{
		case RLCMODE_TM:
			pdcpuLog(LOG_ERR,"[PDCPU] input-TM MODE is wrong!\n");
			return VOS_ERROR;

		case RLCMODE_AM:
			*pRlcMode = AM_MODE;
			return VOS_OK;

		case RLCMODE_UM_BIDIRECTIONAL:
		case RLCMODE_UM_UNIDIRECTIONAL_UL:
		case RLCMODE_UM_UNIDIRECTIONAL_DL:
			*pRlcMode = UM_MODE;
			return VOS_OK;

		default:
			pdcpuLog(LOG_ERR,"[PDCPU] input-rlc mode is wrong\n");
			return VOS_ERROR;
	}
}

/*******************************************************************************
 * To get SDAP DATA PDU header length configuration
 * INPUT:
 *		sdapHeadInd :
 *		sdapHeadLen :
 * OUTPUT:
 *		none
 *******************************************************************************/
INT32 pdcpuGetSdapHeadLen(SdapHeader_e sdapHeadInd, UINT8 *sdapHeadLen)
{
	if(SDAP_HEADER_PRESENT == sdapHeadInd)
	{
		*sdapHeadLen = 1;	/*Data PDU with SDAP header*/

	}else if(SDAP_HEADER_ABSENT == sdapHeadInd)
	{
		*sdapHeadLen = 0;	/*Data PDU without SDAP header*/

	}else
	{
		pdcpuLog(LOG_ERR,"[PDCPU] sdap head cfg is wrong\n");
		return VOS_ERROR;
	}

	return VOS_OK;
}


/*******************************************************************************
 * To create PDCP-U entity
 * INPUT:
 *		ueE1apId: UE E1AP ID
 *		pDrbItem : DRB to setup item
 * OUTPUT:
 *		0: success
 *		-1:failed
 *******************************************************************************/
INT32 pdcpuCreateEntity(UINT64 ueE1apId, UINT16 ueIdx, UINT16 pduSessionId, upcTempDrbInfo_t *pDrbItem)
{
	UINT8 drbId = pDrbItem->drbId;
	PdcpuUeInfo_t	*pPdcpUeInfo  = NULL;
	PdcpDrbEntity_t *pPdcpuEntity = NULL;
	INT8 ret = 0;

	pdcpuCheckUeIdx(ueIdx);
	pdcpuCheckDrbId(drbId);

	/* examine ue info */
	if(NULL == gPdcpuUeInfo[ueIdx])
	{
		pPdcpUeInfo = VOS_Malloc(sizeof(PdcpuUeInfo_t), gPdcpuModuleId);
		pdcpuNullCheck(pPdcpUeInfo);
		VOS_MemZero(pPdcpUeInfo, sizeof(PdcpuUeInfo_t));
		gPdcpuUeInfo[ueIdx] = pPdcpUeInfo;
	}else
	{
		pPdcpUeInfo = gPdcpuUeInfo[ueIdx];
	}

	/* examine drb info */
	if(NULL != pPdcpUeInfo->pdcpDrbEntity[drbId])
	{
		pPdcpuEntity = pPdcpUeInfo->pdcpDrbEntity[drbId];

	}
	pPdcpuEntity = VOS_Malloc(sizeof(PdcpDrbEntity_t), gPdcpuModuleId);
	pdcpuNullCheck(pPdcpuEntity);
	VOS_MemZero(pPdcpuEntity, sizeof(PdcpDrbEntity_t));
	pPdcpUeInfo->pdcpDrbEntity[drbId] = pPdcpuEntity;

	PDCPConfiguration_t *pPdcpCfg 	= &(pDrbItem->pdcpConfig);
	pPdcpuEntity->ueE1apId			= ueE1apId;
	pPdcpuEntity->ueIdx				= ueIdx;
	pPdcpuEntity->pduSessionId		= pduSessionId;
	pPdcpuEntity->drbId				= drbId;

	if(0 != ((pPdcpCfg->bitMask)&PDCP_CONFIGURATION_OUT_OF_ORDER_DELIVERY_PRESENT))
	{
		pdcpuLog(LOG_INFO,"[PDCPU] 乱序递交已设置\n");
		pPdcpuEntity->outOfOrderDelivery= TRUE;
	}

	/* set rlc mode */
	ret += pdcpuSetRlcMode(&pPdcpuEntity->rlcMode, pPdcpCfg->rlcMode);

	/* set sn size- Cond Setup2(38.331) */
	ret += pdcpuSetSn(&pPdcpuEntity->pdcpSnSizeUl, pPdcpCfg->pdcpSNSizeUl);
	ret += pdcpuSetSn(&pPdcpuEntity->pdcpSnSizeDl, pPdcpCfg->pdcpSNSizeDl);


	/* set sdap head length */
	ret += pdcpuGetSdapHeadLen(pDrbItem->sdapConfig.sdapDlHeaderInd, &pPdcpuEntity->sdapDlHeadLen);
	ret += pdcpuGetSdapHeadLen(pDrbItem->sdapConfig.sdapUlHeaderInd, &pPdcpuEntity->sdapUlHeadLen);

	/* check the above return results */
	if(0 != ret)
	{
		pdcpuLog(LOG_ERR,"[PDCPU] input parameter is wrong\n");
		VOS_Free(pPdcpuEntity);
		pPdcpUeInfo->pdcpDrbEntity[drbId] = NULL;
		return VOS_ERROR;
	}


	/* set security enable information */
	PdcpuSecEnableInfo_t *pEnableInfo = gPdcpuUeInfo[ueIdx]->secEnableInfo[pduSessionId];
	pdcpuNullCheck(pEnableInfo);
	pPdcpuEntity->integrityProtection = pEnableInfo->integrityEnableFlag;
	pPdcpuEntity->ciperingEnabled = pEnableInfo->cipherEnableFlag;

	/* not support: ulDataSplitThreshold, pdcpDuplication */

	/* set state variable */
	VOS_MemZero(&(pPdcpuEntity->stateVar), sizeof(PdcpStateVar_t));


	/* initial transmitting buffer */
	pPdcpuEntity->txListLock = VOS_SemMCreate(VOS_SEM_Q_FIFO);
	pPdcpuEntity->pTxPduList = cl_lib_list_new("pdcpuTxPduList", gPdcpuModuleId);

	/* initial receiving buffer */
	pPdcpuEntity->rxListLock = VOS_SemMCreate(VOS_SEM_Q_FIFO);
	pPdcpuEntity->pRxSduList = cl_lib_list_new("pdcpuRxSduList", gPdcpuModuleId);

	printfDrbEntity(pPdcpuEntity);

	return VOS_OK;
}
