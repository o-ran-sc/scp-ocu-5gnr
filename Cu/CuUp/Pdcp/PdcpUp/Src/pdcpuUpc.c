/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/
#include "vos_types.h"
#include "vos_string.h"
#include "vos_lib.h"
#include "pdcpu.h"
#include "pdcpuCore.h"
#include "pdcpCommon.h"
#include "cuupCommon.h"
#include "cuModuleInterface.h"
#include "pdcpComprohc.h"
#include "cuupTest.h"
#include "cuupUeIdTransf.h"
#include "upcContext.h"

extern PdcpuUeInfo_t *gPdcpuUeInfo[MAX_UE_NUM];
ULONG gPdcpuModuleId;
CuupUeIdxTable_t gPdcpuUeIdxTable;


/*******************************************************************************
* To  
* INPUT:
* 	  : 
* OUTPUT:
* 	 0:success
*	-1:fail
*******************************************************************************/ 
INT32 pdcpuInit(ULONG userModuleId)
{	
	/* get pdcpu moduleId */
	gPdcpuModuleId = userModuleId;

	/* init ueIdx table */
	UINT8 i = 0;
	for(i=0; i<MAX_UE_NUM; i++)
	{
		gPdcpuUeIdxTable.ueIdxInfo[i].isUsed = FALSE;
	}

	/* init ue info */
	for(i=0; i<MAX_UE_NUM; i++)
	{
		gPdcpuUeInfo[i] = NULL;
	}
	
	return VOS_OK;
}


INT32 pdcpuFreeSecInfo(UINT16 ueIdx)
{
	PdcpuSecInfo_t *pDrbSecInfo = gPdcpuUeInfo[ueIdx]->secInfo;
	if(NULL != pDrbSecInfo)
	{
		VOS_Free(pDrbSecInfo);
		gPdcpuUeInfo[ueIdx]->secInfo = NULL;
	}
	
	return VOS_OK;
}

/*******************************************************************************
* To deal with security indication
* Security Result indicates whether the security policy indicated as "preferred" 
* in the Security Indication IE is performed or not.
* INPUT:
* 	 ueE1apId : UE E1AP ID
*	 pduSessionId : pdu session id
* 	 pSecInd : security indication
*	 pSecResult : security result
* OUTPUT:
* 	 0:success
*	-1:fail
*******************************************************************************/ 
INT32 pdcpuDealSecurityInd(PdcpuSecInfo_t *pSec, PdcpuSecEnableInfo_t *pEnableInfo, SecuInd_t *pSecInd, PdcpuCfgResult_t *pResult)
{
	/* get security enable information global variable */
	pdcpuNullCheck(pSec);
	pdcpuNullCheck(pEnableInfo);
	pdcpuNullCheck(pSecInd);
	
	/* for integrity protection */
	if(ACTIVE_INT_STATE == pSec->intActiveFlag)
	{
		/* integrity protection is active for the UE, apply the indication */
		if(IP_REQUIRED == pSecInd->IPIndication)
		{
			pEnableInfo->integrityEnableFlag = TRUE;
			pEnableInfo->maxIPDataRate 		 = pSecInd->maxIPdataRate;
			pResult->secResPresent 			 = FALSE;
			
		}else if(IP_PREFERRED == pSecInd->IPIndication)
		{			
			pEnableInfo->integrityEnableFlag = TRUE;
			pEnableInfo->maxIPDataRate 		 = pSecInd->maxIPdataRate;
			pResult->secResPresent 			 = TRUE;
			pResult->secuResult.integrityProtectionResult= IP_RESULT_PERFORMED;
			
		}else
		{
			pEnableInfo->integrityEnableFlag = FALSE;
			pResult->secResPresent 			 = FALSE;
			
		}
		
	}else
	{		
		/* integrity protection is inactive for the UE */
		pEnableInfo->integrityEnableFlag = FALSE;		
		if(IP_PREFERRED == pSecInd->IPIndication)
		{			
			pResult->secResPresent = TRUE;
			pResult->secuResult.integrityProtectionResult= IP_RESULT_NOT_PERFORMED;			
		}
	}
	
	/* for ciphering */
	if(ACTIVE_ENC_STATE == pSec->encActiveFlag)
	{
		/* ciphering is active for the UE, apply the indication */
		if(CP_REQUIRED == pSecInd->CPIndication)
		{
			pEnableInfo->cipherEnableFlag = TRUE;			
			pResult->secResPresent 		  = FALSE;
			
		}else if(CP_PREFERRED == pSecInd->CPIndication)
		{
			pEnableInfo->cipherEnableFlag = TRUE;
			pResult->secResPresent 		  = TRUE;
			pResult->secuResult.confidentialityProtectionResult = CP_RESULT_PERFORMED;
			
		}else
		{
			pEnableInfo->cipherEnableFlag = FALSE;
			pResult->secResPresent 		  = FALSE;
			
		}
		
	}else
	{		
		/* ciphering is inactive for the UE */
		pEnableInfo->cipherEnableFlag = FALSE;		
		if(CP_PREFERRED == pSecInd->CPIndication)
		{			
			pResult->secResPresent = TRUE;
			pResult->secuResult.confidentialityProtectionResult= CP_RESULT_NOT_PERFORMED;			
		}
	}
	
	return VOS_OK;
}

INT32 pdcpuRetFailResult(UpcCfgType_e cfgType, upcTempSessInfo_t *pCfgInfo, PdcpuCfgResult_t *pResult)
{
	pdcpuLog(LOG_ERR,"[PDCPU] pdu session config failed\n");

	UINT8 i = 0;
	if(PDU_SESSION_ADD == cfgType)
	{
		/* drb to setup list */
		for(i=0; i<pCfgInfo->drbSetupNum; i++)
		{
			pResult->drbSetupFailedArray[i].drbId = pCfgInfo->pTempDrbSetupList[i].drbId;
			pResult->drbSetupFailedArray[i].cause = RNL_UNSPECIFIED;
		}
		pResult->drbSetupFailNum = pCfgInfo->drbSetupNum;
		pResult->pduSessionCause = RNL_UNSPECIFIED;
		
	}

	
	return VOS_ERROR;
}

/*******************************************************************************
* To deal with PDU session to setup config 
* INPUT:
* 	 ueE1apId : UE E1AP ID
* 	 pPduSessionCfg : PDU session to setup config
* 	 pResult : PDU session to setup result
* OUTPUT:
* 	 none
*******************************************************************************/ 
INT32 pdcpuSessionAddProc(UINT64 ueE1apId, VOID *pCfgInfo, PdcpuCfgResult_t *pResult)
{
	upcTempSessInfo_t *pSetupInfo = (upcTempSessInfo_t *)pCfgInfo;
	upcTempDrbInfo_t  *pDrbTemp   = NULL;
	PdcpuSecInfo_t 		 *pSec 		  = NULL;
	PdcpuSecEnableInfo_t *pEnableInfo = NULL;

 	UINT16 pduSessionId = pSetupInfo->pduSessId;
	pResult->pduSessionId = pduSessionId;	

	/* get ueIdx */
	UINT16 ueIdx;	
	if(VOS_ERROR == cuupAddUeE1apid(ueE1apId, &ueIdx, &gPdcpuUeIdxTable))
	{
		pdcpuLog(LOG_ERR,"[PDCPU] add ueE1apId failed\n");
		return pdcpuRetFailResult(PDU_SESSION_ADD,pCfgInfo,pResult);
	}

	/* check ue and security context block */
	if((NULL == gPdcpuUeInfo[ueIdx]) || (NULL == gPdcpuUeInfo[ueIdx]->secInfo))
	{		
		pdcpuLog(LOG_ERR,"[PDCPU] ue and security context block not exist\n");
		return pdcpuRetFailResult(PDU_SESSION_ADD,pCfgInfo,pResult);
	}
	pSec = gPdcpuUeInfo[ueIdx]->secInfo;
	
	/* alloc pdu session information */
	pEnableInfo = gPdcpuUeInfo[ueIdx]->secEnableInfo[pduSessionId];
	if(NULL == pEnableInfo)
	{
		pEnableInfo = VOS_Malloc(sizeof(PdcpuSecEnableInfo_t), gPdcpuModuleId);
		if(NULL == pEnableInfo)
		{
			pdcpuLog(LOG_ERR,"[PDCPU] vos_malloc failed\n");
			return pdcpuRetFailResult(PDU_SESSION_ADD,pCfgInfo,pResult);
		}
		VOS_MemZero(pEnableInfo, sizeof(PdcpuSecEnableInfo_t));
		gPdcpuUeInfo[ueIdx]->secEnableInfo[pduSessionId] = pEnableInfo;
	}
	pEnableInfo->pduSessionId = pduSessionId;

	/* deal with security indication */	
	if(VOS_ERROR == pdcpuDealSecurityInd(pSec, pEnableInfo, &pSetupInfo->secuIndi, pResult))
	{
		pdcpuLog(LOG_ERR,"[PDCPU] deal security indication failed\n");
		return pdcpuRetFailResult(PDU_SESSION_ADD,pCfgInfo,pResult);
	}
	
	/* create pdcp entity */
	UINT8 i = 0;	
	for(i = 0; i < pSetupInfo->drbSetupNum; i++)
	{
		pDrbTemp = &pSetupInfo->pTempDrbSetupList[i];
 		
		if((NULL == pDrbTemp) || (FALSE == pDrbTemp->drbSetupAllowed))
		{
			continue;
		}
		
		if(VOS_OK == pdcpuCreateEntity(ueE1apId, ueIdx, pduSessionId, pDrbTemp))
		{
			pResult->drbSetupSuccessArray[pResult->drbSetupSuccessNum] = pDrbTemp->drbId;
			pResult->drbSetupSuccessNum += 1;
		}else
		{			
			pResult->drbSetupFailedArray[pResult->drbSetupFailNum].drbId = pDrbTemp->drbId;
			pResult->drbSetupFailedArray[pResult->drbSetupFailNum].cause = RNL_PDCP_CONFIG_NOT_SUPPORT;
			pResult->drbSetupFailNum += 1;
			
		}
	}

	/* return */
	if(0 != pResult->drbSetupSuccessNum)
	{
		return VOS_OK;
	}else
	{
		pResult->pduSessionCause = RNL_UNSPECIFIED;
		pdcpuLog(LOG_ERR,"[PDCPU] all drbs setup failed\n");
		return VOS_ERROR;
	}
}

/*******************************************************************************
 * To manage pdcp-u entity 
 * INPUT:
 *		ueE1apId		: UE E1AP ID
 *		pPduSessionCfg	: PDU Session Resource to setup item
 *		cfgType 		: configuration type
 *		pResult			: result which will return to upc
 * OUTPUT:
 *		result: PDCP config result
 *******************************************************************************/
INT32 pdcpuConfig(UINT64 ueE1apId, VOID *pCfgInfo, UpcCfgType_e cfgType, PdcpuCfgResult_t *pResult)
{		
	switch(cfgType)
	{
		case PDU_SESSION_ADD:
		{
			pdcpuNullCheck(pCfgInfo);
			pdcpuNullCheck(pResult);
			VOS_MemZero(pResult, sizeof(PdcpuCfgResult_t));
			pResult->cfgType = cfgType;
			return pdcpuSessionAddProc(ueE1apId, pCfgInfo, pResult);
		}		
		default:
		{
			pdcpuLog(LOG_ERR,"[PDCPU] cfgType error\n");
			return VOS_ERROR;
		}
	}

}


/*******************************************************************************
 * To get ue security information pointer
 * INPUT:
 *		ueIdx: UE index
 * OUTPUT:
 *		pDrbSecInfo: ue security information pointer
 *******************************************************************************/
PdcpuSecInfo_t *pdcpuAllocUeSecInfo(UINT16 ueIdx)
{
	PdcpuSecInfo_t *pSecInfo 	= NULL;		
	PdcpuUeInfo_t  *pPdcpUeInfo = NULL;

	//check ue
	if(NULL == gPdcpuUeInfo[ueIdx])
	{		
		pPdcpUeInfo = VOS_Malloc(sizeof(PdcpuUeInfo_t), gPdcpuModuleId);
		pdcpuNullCheckRp(pPdcpUeInfo);
		VOS_MemZero(pPdcpUeInfo, sizeof(PdcpuUeInfo_t));
		gPdcpuUeInfo[ueIdx] = pPdcpUeInfo;
	}else
	{
		pPdcpUeInfo = gPdcpuUeInfo[ueIdx];
	}
	//check secInfo
	if(NULL == pPdcpUeInfo->secInfo)
	{		
		pSecInfo = VOS_Malloc(sizeof(PdcpuSecInfo_t), gPdcpuModuleId);
		pdcpuNullCheckRp(pSecInfo);
		VOS_MemZero(pSecInfo, sizeof(PdcpuSecInfo_t));
		pPdcpUeInfo->secInfo = pSecInfo;
	}else
	{
		pSecInfo = pPdcpUeInfo->secInfo;
	}

	VOS_MemZero(pSecInfo, sizeof(PdcpuSecInfo_t));
	
	return pSecInfo;
}


/*******************************************************************************
 * To set ue security parameters. When receiving security information, 
 * pdcp-u shall save AS keys, AS algorithm and active integrity and ciphering. 
 * INPUT:
 *		ueE1apId: UE E1AP ID
 *		secInfo: security information
 * OUTPUT:
 *		0: success
 *		-1:failed
 *******************************************************************************/
INT32 pdcpuSetSecParam(UINT64 ueE1apId, SecuInfo_t *secInfo)
{
	pdcpuNullCheck(secInfo);
	
	UINT16 ueIdx;	
	if(VOS_ERROR == cuupAddUeE1apid(ueE1apId, &ueIdx, &gPdcpuUeIdxTable))
	{
		pdcpuLog(LOG_ERR,"[PDCPU] add ueE1apId failed\n");
		return VOS_ERROR;
	}
	
	/* find ue security struct */
	PdcpuSecInfo_t *pDrbSecInfo = pdcpuAllocUeSecInfo(ueIdx);
	pdcpuNullCheck(pDrbSecInfo);
	
	/* activate integrity */
	if(secInfo->secuAlgorithm.bitMask & SECURITY_ALGORITHM_INTERGRITY_PROTECTION_ALGORITHM)
	{	
		UINT8  intAlgorithm = secInfo->secuAlgorithm.integrityProtectionAlgorithm;
		UINT8 *pIntKey 		= secInfo->upSecukey.integrityProtectionKey.buffer;
		UINT8  intKeyLen 	= secInfo->upSecukey.integrityProtectionKey.size;	/* 128 bits */

		if(intKeyLen < AS_KEY_LEN)
		{
			pdcpuLog(LOG_ERR,"[PDCPU] integrity parameter is wrong!\n");
			pdcpuFreeSecInfo(ueIdx);
			return VOS_ERROR;
		}
		
		pDrbSecInfo->intActiveFlag = ACTIVE_INT_STATE;					/* 0-inactive, 1-active */
		if(intAlgorithm == NIA0 || intAlgorithm == NIA1 || intAlgorithm == NIA2)
		{
			pDrbSecInfo->intAlgorithm  = intAlgorithm;
			VOS_MemCpy(pDrbSecInfo->kUpInt, pIntKey, AS_KEY_LEN);		/* 128 bits */
		}else
		{
			pDrbSecInfo->intActiveFlag = INACTIVE_INT_STATE;
			pdcpuLog(LOG_ERR,"[PDCPU] integrity algorithm is %d, not supported!\n",intAlgorithm);
			pdcpuFreeSecInfo(ueIdx);
			return VOS_ERROR;
		}
	}else
	{
		pDrbSecInfo->intActiveFlag = INACTIVE_INT_STATE;
		pdcpuLog(LOG_INFO,"[PDCPU] integrity is not config\n");
	}
	
	/* activate encryption */	
	UINT8  encAlgorithm = secInfo->secuAlgorithm.cipheringAlgorithm;
	UINT8 *pEncKey		= secInfo->upSecukey.encryptionKey.buffer;
	UINT8  encKeyLen	= secInfo->upSecukey.encryptionKey.size;		/* 128 bits */

	if(encKeyLen < AS_KEY_LEN)
	{
		pdcpuLog(LOG_ERR,"[PDCPU] encryption parameter is wrong!\n");
		pdcpuFreeSecInfo(ueIdx);
		return VOS_ERROR;
	}

	pDrbSecInfo->encActiveFlag = ACTIVE_ENC_STATE;						/* 0-inactive, 1-active */
	if(encAlgorithm == NEA0 || encAlgorithm == NEA1 || encAlgorithm == NEA2)
	{			
		pDrbSecInfo->encAlgorithm  = encAlgorithm;	
		VOS_MemCpy(pDrbSecInfo->kUpEnc, pEncKey, AS_KEY_LEN);			/* 128 bits */
	}else
	{
		pDrbSecInfo->encActiveFlag = INACTIVE_ENC_STATE;		
		pdcpuLog(LOG_ERR,"[PDCPU] encryption algorithm:%d, is not supported!\n", encAlgorithm);
		pdcpuFreeSecInfo(ueIdx);
		return VOS_ERROR;
	}

	pDrbSecInfo->ueE1apId = ueE1apId;
	pDrbSecInfo->ueIdx 	  = ueIdx;
	pDrbSecInfo->nhInd 	  = FALSE;
		
	return VOS_OK;
}

