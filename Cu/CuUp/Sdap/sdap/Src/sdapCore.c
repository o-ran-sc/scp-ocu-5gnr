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

SdapGlobalDtat_t	s_SdapGlobalData[UPC_MAX_UE_NUM] = {{0}};

void sdapResortDrbId(SdapInstance_t *pSdapInstance, int idx)
{
	int i = 0;
	int j = 0;

	for(i = 0; i < pSdapInstance->drbNum; i++)
	{
		if(i == idx)
		{
			continue;
		}

		pSdapInstance->drbId[j] = pSdapInstance->drbId[i];
		j++;
	}
}

void sdapResortSessionId(SdapGlobalDtat_t	*pGlobalData, int idx)
{
	int i = 0;
	int j = 0;

	for(i = 0; i < pGlobalData->sessNum; i++)
	{
		if(i == idx)
		{
			continue;
		}

		pGlobalData->sessId[j] = pGlobalData->sessId[i];
		j++;
	}
}

SdapGlobalDtat_t* sdapGetUeGlobalData(UINT64	upE1apId, UINT8 *flag)
{
	int i = 0;

	for(i = 0; i < UPC_MAX_UE_NUM; i++)
	{
		if(upE1apId == s_SdapGlobalData[i].upE1apId)
		{
			*flag = 1;
			return &s_SdapGlobalData[i];
		}
	}

	for(i = 0; i < UPC_MAX_UE_NUM; i++)
	{
		if(0 == s_SdapGlobalData[i].upE1apId)
		{
			*flag = 0;
			return &s_SdapGlobalData[i];
		}
	}

	return NULL;
}
#if CONCEPT('Create Instance')
INT32 sdapCreateQosInfo(SdapDrbCfg_t *pDrbCfg, upcTempDrbInfo_t	*pTempDrb, SdapDrbCfgRet_t *pDrbCfgRet)
{
	int i = 0;
	INT64	qosFlowId = 0;
	upcTempQosInfo_t *pTempQos;

	for(i = 0; i < pTempDrb->qosSetupNum; i++)
	{
		pTempQos = &pTempDrb->pQosSetupList[i];

		if((NULL == pTempQos) || (TRUE != pTempQos->qosSetupAllowed))
		{
			continue;
		}

		qosFlowId = pTempQos->qosFlowId;
		pDrbCfg->qfi[pDrbCfg->qfiNum] = qosFlowId;
		pDrbCfg->qosFlowInfo[qosFlowId].qosFlowLevelQosPar = pTempQos->qosPara;
		if(pTempQos->qosMapFlag)
		{
			pDrbCfg->qosFlowInfo[qosFlowId].qosFlowMapInd = pTempQos->qosFlowMapInd;
		}
		pDrbCfg->qfiNum++;

		pDrbCfgRet->Qfi[pDrbCfgRet->QosNum] = qosFlowId;
		pDrbCfgRet->QosNum++;
	}

	if(0 == pDrbCfg->qfiNum)
	{
		return VOS_ERROR;
	}

	return VOS_OK;
}

INT32 sdapCreateDrbInfo(SdapInstance_t *pInstance, upcTempSessInfo_t *pSessTempInfo, sdapSessCfgRet_t *pCfgRet)
{
	int i = 0;
	UINT64	drbId = 0;

	upcTempDrbInfo_t	*pTempDrb = NULL;

	pInstance->sessId = pSessTempInfo->pduSessId;
	pCfgRet->sessId = pInstance->sessId;

	for(i = 0; i < pSessTempInfo->drbSetupNum; i++)
	{
		pTempDrb = &pSessTempInfo->pTempDrbSetupList[i];

		if((NULL == pTempDrb) || (TRUE != pTempDrb->drbSetupAllowed))
		{
			continue;
		}

		drbId = pTempDrb->drbId;

		if(VOS_OK != sdapCreateQosInfo(&pInstance->drbCfg[drbId - 1], pTempDrb, &pCfgRet->actDrbCfg[drbId - 1]))
		{
			pCfgRet->failDrbId[pCfgRet->failDrbNum] = drbId;
			pCfgRet->failDrbNum++;
			pCfgRet->cause[drbId - 1] = RNL_UNSPECIFIED;
			continue;
		}
		pCfgRet->actDrbId[pCfgRet->actDrbNum] = drbId;
		pCfgRet->actDrbCfg[drbId - 1].drbId = drbId;
		pCfgRet->actDrbNum++;

		VOS_MemCpy(&pInstance->drbCfg[drbId - 1].sdapCfg, &pTempDrb->sdapConfig, sizeof(SdapCfg_t));

		pInstance->drbCfg[drbId - 1].drbId = drbId;
		pInstance->drbId[pInstance->drbNum] = drbId;
		pInstance->drbNum++;
	}

	if(0 == pCfgRet->actDrbNum)
	{
		pCfgRet->sessFailCause = RNL_UNSPECIFIED;
		return VOS_ERROR;
	}

	return VOS_OK;
}


extern INT32 printfSdapNewInstance(SdapGlobalDtat_t *pGlobalData);
extern INT32 sdapInactiveDetectSet(UINT64 ueE1apId);

INT32 sdapCreateNewInstance
(
	SdapGlobalDtat_t	*pGlobalData,
	UINT64	upE1apId,
	upcTempSessInfo_t *pSessTempInfo,
	sdapSessCfgRet_t *pCfgRet
)
{
	int idx = 0;
	UINT64	sessId = 0;

	pGlobalData->upE1apId = upE1apId;
	sessId = pSessTempInfo->pduSessId;
	idx = pGlobalData->sessNum;

	if(VOS_OK != sdapCreateDrbInfo(&pGlobalData->sdapInstance[sessId], pSessTempInfo, pCfgRet))
	{
		pCfgRet->sessFailCause = RNL_UNSPECIFIED;
		return VOS_ERROR;
	}

	pGlobalData->sessId[idx] = sessId;
	pGlobalData->sessNum++;

	printfSdapNewInstance(pGlobalData);

	return VOS_OK;
}

INT32 sdapCreateInstance(UINT64	upE1apId, upcTempSessInfo_t *pSessTempInfo, sdapSessCfgRet_t *pCfgRet)
{
	INT32	ret = VOS_OK;
	UINT8	flag = 0;
	SdapGlobalDtat_t	*pGlobalData = NULL;

	pGlobalData = sdapGetUeGlobalData(upE1apId, &flag);

	if(NULL == pGlobalData)
	{
		pCfgRet->sessFailCause = RNL_UNSPECIFIED;
		return VOS_ERROR;
	}

	/* 1、首次创建，初始化数据
	   2、只针对E1接口BearerContextSetupReq*/
	if(0 == flag)
	{
		VOS_MemZero(pGlobalData, sizeof(SdapGlobalDtat_t));
	}

	ret = sdapCreateNewInstance(pGlobalData, upE1apId, pSessTempInfo, pCfgRet);

	return ret;
}
#endif

#if CONCEPT('Delete Instance')
INT32 sdapDeleteDrbInfo(SdapInstance_t *pSdapInstance, UINT8 drbId)
{
	int i = 0;

	for(i = 0; i < pSdapInstance->drbNum; i++)
	{
		if(drbId == pSdapInstance->drbId[i])
		{
			sdapResortDrbId(pSdapInstance, i);
			pSdapInstance->drbNum--;
			VOS_MemZero(&pSdapInstance->drbCfg[drbId - 1], sizeof(SdapDrbCfg_t));
			return VOS_OK;
		}
	}

	return VOS_OK;
}

INT32 sdapDeleteDrbInfoOfInstance(UINT64 upE1apId, UINT8 sessId, UINT8 drbId)
{
	int i = 0;
	UINT8	flag = 0;
	SdapGlobalDtat_t	*pGlobalData = NULL;

	pGlobalData = sdapGetUeGlobalData(upE1apId, &flag);

	/* 查找失败也认为是成功的 */
	if(NULL == pGlobalData || 0 == flag)
	{
		return VOS_OK;
	}

	for(i = 0; i < pGlobalData->sessNum; i++)
	{
		if(sessId == pGlobalData->sessId[i])
		{
			sdapDeleteDrbInfo(&pGlobalData->sdapInstance[sessId], drbId);

			return VOS_OK;
		}
	}

	return VOS_OK;
}

INT32 sdapDeleteInstance(UINT64	upE1apId, UINT16 sessId)
{
	int i = 0;
	UINT8	flag = 0;
	SdapGlobalDtat_t	*pGlobalData = NULL;

	pGlobalData = sdapGetUeGlobalData(upE1apId, &flag);

	/* 查找失败也认为是成功的 */
	if(NULL == pGlobalData || 0 == flag)
	{
		return VOS_OK;
	}

	for(i = 0; i < pGlobalData->sessNum; i++)
	{
		if(sessId == pGlobalData->sessId[i])
		{
			sdapResortSessionId(pGlobalData, i);
			pGlobalData->sessNum--;
			VOS_MemZero(&pGlobalData->sdapInstance[sessId], sizeof(SdapInstance_t));
			return VOS_OK;
		}
	}

	return VOS_OK;
}
#endif
