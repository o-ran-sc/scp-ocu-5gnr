/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/
#include "cuupTest.h"

INT32 printfPduSessionCfgType(UpcCfgType_e type)
{
	VOS_Printf("cfg type : ");
	switch(type)
	{
		case PDU_SESSION_ADD:
			VOS_Printf("PDU_SESSION_ADD\n");
			break;
				
		case PDU_SESSION_MOD:
			VOS_Printf("PDU_SESSION_MOD\n");
			break;
		
		case PDU_SESSION_DEL:
			VOS_Printf("PDU_SESSION_DEL\n");
			break;
			
		case DRB_DEL:
			VOS_Printf("DRB_DEL\n");
			break;

		default:
			break;
	}

	return VOS_OK;
}

INT32 printfTransLayerAddr(TransLayerAddr_t *pAddr)
{
	NULL_CHECK(pAddr);

	VOS_Printf("addr size: %d bytes  ",pAddr->bitStringSize);

	UINT8 i = 0;
	for(i=0; i<pAddr->bitStringSize; i++)
	{
		VOS_Printf("%d ",pAddr->transLayerAddress[i]);
	}
	VOS_Printf("\n");

	return VOS_OK;
}

INT32 printfNguInstance(NguInstance_t *pNguInstance)
{
	NULL_CHECK(pNguInstance);
	VOS_Printf("\n");
	VOS_Printf("#################################\n");
	VOS_Printf("     ngu instance parameters     \n");
	VOS_Printf("#################################\n");
	VOS_Printf("ueE1apId:     %d\n",pNguInstance->ueE1apId);	
	VOS_Printf("ueIdx:        %d\n",pNguInstance->ueIdx);	
	VOS_Printf("pduSessionId: %d\n",pNguInstance->pduSessionId);	
	VOS_Printf("ownTeid:      0x%08x\n",pNguInstance->ownTeid);

	return VOS_OK;
}

INT32 printfNguCfgResult(NguCfgResult_t *pCfg)
{
	NULL_CHECK(pCfg);
	VOS_Printf("\n");
	VOS_Printf("##########################\n");
	VOS_Printf("     ngu config result    \n");
	VOS_Printf("##########################\n");
	printfPduSessionCfgType(pCfg->cfgType);
	VOS_Printf("pduSessionId: %d\n",pCfg->pduSessionId);
	VOS_Printf("nggtpuTeid:   0x%08x\n",pCfg->nggtpuTeid);
	printfTransLayerAddr(&pCfg->nggtpuAddr);
	VOS_Printf("failureCause: %d\n",pCfg->failureCause);

	return VOS_OK;
}


INT32 printfSecuResult(SecuResult_t *pResult)
{
	NULL_CHECK(pResult);
	
	if(CP_RESULT_PERFORMED == pResult->confidentialityProtectionResult)
	{
		VOS_Printf("cipher is performed\n");
		
	}else if(CP_RESULT_NOT_PERFORMED == pResult->confidentialityProtectionResult)
	{
		VOS_Printf("cipher is not performed\n");
		
	}else
	{
		VOS_Printf("ciper result is wrong!\n");
	}
	
	if(IP_RESULT_PERFORMED == pResult->integrityProtectionResult)
	{
		VOS_Printf("integrity is performed\n");
		
	}else if(IP_RESULT_NOT_PERFORMED == pResult->integrityProtectionResult)
	{
		VOS_Printf("integrity is not performed\n");
		
	}else
	{
		VOS_Printf("integrity result is wrong!\n");
	}

	return VOS_OK;
}

INT32 printfPdcpRlcMode(PdcpRlcMode_e mode)
{
	if(TM_MODE == mode)
	{
		VOS_Printf("rlc mode: TM_MODE\n");
		
	}else if(UM_MODE == mode)
	{
		VOS_Printf("rlc mode: UM_MODE\n");
		
	}else if(AM_MODE == mode)
	{
		VOS_Printf("rlc mode: AM_MODE\n");

	}else
	{
		VOS_Printf("rlc mode: wrong\n");
	}

	return VOS_OK;
}


INT32 printfDrbEntity(PdcpDrbEntity_t *pEntity)
{	
	NULL_CHECK(pEntity);	
	VOS_Printf("\n");
	VOS_Printf("#####################\n");
	VOS_Printf("    pdcpu entity     \n");	
	VOS_Printf("#####################\n");
	VOS_Printf("ueE1apId:      %d\n", pEntity->ueE1apId);
	VOS_Printf("ueIdx:         %d\n", pEntity->ueIdx);
	VOS_Printf("pduSessionId:  %d\n", pEntity->pduSessionId);
	VOS_Printf("drbId:         %d\n", pEntity->drbId);
	printfPdcpRlcMode(pEntity->rlcMode);
	VOS_Printf("sdapUlHeadLen: %d\n", pEntity->sdapUlHeadLen);
	VOS_Printf("sdapDlHeadLen: %d\n", pEntity->sdapDlHeadLen);
	VOS_Printf("pdcpSnSizeUl:  %d bits\n", pEntity->pdcpSnSizeUl);
	VOS_Printf("pdcpSnSizeDl:  %d bits\n", pEntity->pdcpSnSizeDl);

	if(pEntity->tDiscardActive)
	{
		VOS_Printf("discard timer is active, ");
	}else
	{
		VOS_Printf("discard timer is not active, ");
	}
	
	if(pEntity->tDiscardRun)
	{
		VOS_Printf("running, ");
	}else
	{
		VOS_Printf("not running, ");
	}
	
	VOS_Printf("period:%d ms\n", pEntity->tDiscard);
	
	if(pEntity->tReorderActive)
	{
		VOS_Printf("reorder timer is active, ");
	}else
	{
		VOS_Printf("reorder timer is not active, ");
	}
	
	if(pEntity->tReorderRun)
	{
		VOS_Printf("running, ");
	}else
	{
		VOS_Printf("not running, ");
	}
	
	VOS_Printf("period:%d ms\n", pEntity->tReorder);

	if(TRUE == pEntity->integrityProtection)
	{
		VOS_Printf("integrityProtection: enabled\n");
		
	}else if(FALSE == pEntity->integrityProtection)
	{
		VOS_Printf("integrityProtection: disabled\n");
	}else
	{
		vos_err_print("integrityProtection: enable flag is wrong\n");
	}

	if(TRUE == pEntity->ciperingEnabled)
	{
		VOS_Printf("cipher: enabled\n");
		
	}else if(FALSE == pEntity->ciperingEnabled)
	{
		VOS_Printf("cipher: disabled\n");
	}else
	{
		vos_err_print("cipher: enable flag is wrong\n");
	}

	if(TRUE == pEntity->outOfOrderDelivery)
	{
		VOS_Printf("outOfOrderDelivery: enabled\n");
		
	}else
	{
		VOS_Printf("outOfOrderDelivery: disabled\n");
	}

	if(TRUE == pEntity->headerCompress.notUsed)
	{
		VOS_Printf("headerCompress: not used\n");
		
	}else
	{
		VOS_Printf("headerCompress: used\n");
	}
	
	VOS_Printf("stateVar.rxCount:    %d\n", pEntity->stateVar.rxCount);
	VOS_Printf("stateVar.txNext:     %d\n", pEntity->stateVar.txNext);
	VOS_Printf("stateVar.rxDelivery: %d\n", pEntity->stateVar.rxDelivery);
	VOS_Printf("stateVar.rxNext:     %d\n", pEntity->stateVar.rxNext);
	VOS_Printf("stateVar.rxReorder:  %d\n", pEntity->stateVar.rxReorder);

	return VOS_OK;
}

INT32 printfDrbFailedCause(DrbFailedCause_t *p)
{
	VOS_Printf("drb id: %d, failed cause: %d\n", p->drbId, p->cause);

	return VOS_OK;
}

INT32 printfPdcpuCfgResult(PdcpuCfgResult_t *pResult)
{
	UINT8 i = 0;
	
	NULL_CHECK(pResult);
	VOS_Printf("\n");
	VOS_Printf("##########################\n");
	VOS_Printf("     pdcpu cfg result     \n");
	VOS_Printf("##########################\n");
	VOS_Printf("pdu Session Id: %d\n", pResult->pduSessionId);
	printfPduSessionCfgType(pResult->cfgType);

	if(pResult->secResPresent)
	{
		VOS_Printf("there is security result\n");
		printfSecuResult(&pResult->secuResult);
	}else
	{
		VOS_Printf("there is no security result\n");
	}
	
	VOS_Printf("drbSetupSuccessNum: %d\ndrb id list: ", pResult->drbSetupSuccessNum);
	for(i=0; i<pResult->drbSetupSuccessNum; i++)
	{
		VOS_Printf("%d ", pResult->drbSetupSuccessArray[i]);
	}
	
	VOS_Printf("\ndrbSetupFailNum: %d\ndrb id list: ", pResult->drbSetupFailNum);
	for(i=0; i<pResult->drbSetupFailNum; i++)
	{
		printfDrbFailedCause(&pResult->drbSetupFailedArray[i]);
	}

	VOS_Printf("\ndrbModifySuccessNum: %d\ndrb id list: ", pResult->drbModifySuccessNum);
	for(i=0; i<pResult->drbModifySuccessNum; i++)
	{
		VOS_Printf("%d ", pResult->drbModifySuccessArray[i]);
	}
	
	VOS_Printf("\ndrbModifyFailNum: %d\ndrb id list: ", pResult->drbModifyFailNum);
	for(i=0; i<pResult->drbModifyFailNum; i++)
	{
		printfDrbFailedCause(&pResult->drbModifyFailedArray[i]);
	}
	VOS_Printf("\n");
	
	return VOS_OK;
}


INT32 printfCuf1uInstance(Cuf1uInstance_t *pF1u)
{
	NULL_CHECK(pF1u);
	VOS_Printf("\n");
	VOS_Printf("##########################\n");
	VOS_Printf("     cuf1u instance     \n");
	VOS_Printf("##########################\n");
	VOS_Printf("ueE1apId:     %d\n", pF1u->ueE1apId);
	VOS_Printf("ueIdx:	      %d\n", pF1u->ueIdx);
	VOS_Printf("pduSessionId: %d\n", pF1u->pduSessionId);
	VOS_Printf("drbId:        %d\n", pF1u->drbId);
	if(LEN_12_BITS == pF1u->pdcpSnSize)
	{
		VOS_Printf("pdcpSnSize:   12 bits\n", pF1u->pdcpSnSize);
		
	}else if(LEN_18_BITS == pF1u->pdcpSnSize)
	{
		VOS_Printf("pdcpSnSize:   18 bits\n", pF1u->pdcpSnSize);
		
	}else{
		VOS_Printf("pdcpSnSize: wrong!\n");
	}
		
	VOS_Printf("ownTeid:      0X%08X\n", pF1u->ownTeid);
	VOS_Printf("nextSubmitSn: %d\n", pF1u->nextSubmitSn);

	return VOS_OK;
}

INT32 printfCuf1uSetupInfo(Cuf1uSetupInfo_t *pInfo)
{
	NULL_CHECK(pInfo);

	VOS_Printf("setup info-->drbId: %02x\n", pInfo->drbId);
	VOS_Printf("setup info-->f1gtpuTeid: %08x\n", pInfo->f1gtpuTeid);
	VOS_Printf("setup info-->");
	printfTransLayerAddr(&pInfo->gtpuAddr);

	return VOS_OK;
}


INT32 printfCuf1uCfgResult(Cuf1uCfgResult_t *pResult)
{
	UINT8 i = 0;
	
	NULL_CHECK(pResult);
	VOS_Printf("\n");
	VOS_Printf("##########################\n");
	VOS_Printf("	 cuf1u cfg result	  \n");
	VOS_Printf("##########################\n");
	VOS_Printf("pdu Session Id: %d\n", pResult->pduSessionId);
	printfPduSessionCfgType(pResult->cfgType);
	
	VOS_Printf("drbSetupSuccessNum: %d\ndrb id list:", pResult->drbSetupSuccessNum);
	for(i=0; i<pResult->drbSetupSuccessNum; i++)
	{
		printfCuf1uSetupInfo(&pResult->drbSetupSuccessArray[i]);
	}
	
	VOS_Printf("\ndrbSetupFailNum: %d\n", pResult->drbSetupFailNum);
	for(i=0; i<pResult->drbSetupFailNum; i++)
	{
		printfDrbFailedCause(&pResult->drbSetupFailedArray[i]);
	}

	VOS_Printf("\ndrbModifySuccessNum: %d\n", pResult->drbModifySuccessNum);
	for(i=0; i<pResult->drbModifySuccessNum; i++)
	{
		VOS_Printf("%d ", pResult->drbModifySuccessArray[i]);
	}
	
	VOS_Printf("\ndrbModifyFailNum: %d\n", pResult->drbModifyFailNum);
	for(i=0; i<pResult->drbModifyFailNum; i++)
	{
		printfDrbFailedCause(&pResult->drbModifyFailedArray[i]);
	}

	VOS_Printf("pduSessionFailCause: %d\n",pResult->pduSessionCause);
	
	return VOS_OK;
}

INT32 printfPdcpuSecInfo(PdcpuSecInfo_t *pSec)
{
	NULL_CHECK(pSec);
	
	UINT8 i = 0;
	
	VOS_Printf("\n");
	VOS_Printf("#################################################\n");
	VOS_Printf("	 pdcpu set security info successful	  \n");
	VOS_Printf("#################################################\n");
	VOS_Printf("ueE1apId: 0X%x\n",pSec->ueE1apId);
	VOS_Printf("ueIdx: 0X%04x\n",pSec->ueIdx);

	VOS_Printf("kUpEnc:");
	for(i=0; i<4; i++)
	{
		VOS_Printf("%08x ",pSec->kUpEnc[i]);
	}
	VOS_Printf("\n");
	
	VOS_Printf("kUpInt:");
	for(i=0; i<4; i++)
	{
		VOS_Printf("%08x ",pSec->kUpInt[i]);
	}
	VOS_Printf("\n");
	
	/*VOS_Printf("nh:");
	for(i=0; i<8; i++)
	{
		VOS_Printf("%08x ",pSec->nh[i]);
	}
	VOS_Printf("\n");
	
	VOS_Printf("ncc: 0X%02x\n",pSec->ncc);*/

	//打印加密算法
	if(NEA0 == pSec->encAlgorithm)
	{
		VOS_Printf("encAlgorithm: NEA0\n");
		
	}else if(NEA1 == pSec->encAlgorithm)
	{
		VOS_Printf("encAlgorithm: NEA1\n");
		
	}else if(NEA2 == pSec->encAlgorithm)
	{
		VOS_Printf("encAlgorithm: NEA2\n");
		
	}else
	{
		VOS_Printf("encAlgorithm: %d error!\n",pSec->encAlgorithm);
	}
	
	//打印完保算法
	if(NIA0 == pSec->intAlgorithm)
	{
		VOS_Printf("intAlgorithm: NIA0\n");
		
	}else if(NIA1 == pSec->intAlgorithm)
	{
		VOS_Printf("intAlgorithm: NIA1\n");
		
	}else if(NIA2 == pSec->intAlgorithm)
	{
		VOS_Printf("intAlgorithm: NIA2\n");
		
	}else
	{
		VOS_Printf("intAlgorithm: %d error!\n",pSec->intAlgorithm);
	}
	
	//打印加密是否激活
	if(0 == pSec->encActiveFlag)
	{
		VOS_Printf("enc status: inactive\n");
	}else
	{
		VOS_Printf("enc status: active\n");
	}

	//打印完保是否激活
	if(0 == pSec->intActiveFlag)
	{
		VOS_Printf("int status: inactive\n");
	}else
	{
		VOS_Printf("int status: active\n");
	}
	
	if(0 == pSec->nhInd)
	{
		VOS_Printf("nhInd: not exist\n");
	}else
	{
		VOS_Printf("nhInd: exist\n");
	}

	return VOS_OK;
}

INT32 printfVosSockAddr(vos_sockaddr_t *pAddr)
{
	NULL_CHECK(pAddr);
	
	UINT8 *temp = NULL;
	UINT8 i = 0;

	if(AF_INET == pAddr->sa.sa_family)
	{
		VOS_Printf("IP type : IPV4\n");
		VOS_Printf("IP addr : ");
		for(i=0; i<4; i++)
		{
			temp = (UINT8 *)&pAddr->sin.sin_addr + i;
			VOS_Printf("%d ",*temp);
		}
		VOS_Printf("\n");
	}else if(AF_INET6 == pAddr->sa.sa_family)
	{
		VOS_Printf("IP type : IPV6\n");
		VOS_Printf("IP addr : ");
		for(i=0; i<16; i++)
		{
			temp = (UINT8 *)&pAddr->sin6.sin6_addr + i;
			VOS_Printf("%d ",*temp);
		}
		VOS_Printf("\n");
	}else
	{
		VOS_Printf("addr type is wrong!\n");
	}

	return VOS_OK;
}

INT32 printfTun(Tun_t *pTun)
{
	NULL_CHECK(pTun);
	
	VOS_Printf("\n");
	VOS_Printf("##############################\n");
	VOS_Printf("	       tunnel info	      \n");
	VOS_Printf("##############################\n");

	if(0 == pTun->tunState)
	{
		VOS_Printf("tun state is inactive\n");
	}else
	{
		VOS_Printf("tun state is active\n");
	}

	VOS_Printf("seq: %d\n",pTun->seq);
	VOS_Printf("tunId:   0x%08x\n",pTun->tunId);
	VOS_Printf("ownTeid: 0x%08x\n",pTun->ownTeid);
	VOS_Printf("remTeid: 0x%08x\n",pTun->remTeid);
	printfVosSockAddr(&pTun->tunOpval.addr);

	return VOS_OK;
}

INT32 printfPdcpuSecEnableInfo(PdcpuSecEnableInfo_t *pInfo)
{
	NULL_CHECK(pInfo);

	VOS_Printf("\n");
	VOS_Printf("######################################\n");
	VOS_Printf("	       security enable info	      \n");
	VOS_Printf("######################################\n");	
	VOS_Printf("pduSessionId: %d\n",pInfo->pduSessionId);

	//加密
	if(TRUE == pInfo->cipherEnableFlag)
	{
		VOS_Printf("cipher : enabled\n");
	}else
	{
		VOS_Printf("cipher : disabled\n");
	}

	//完整性保护
	if(TRUE == pInfo->integrityEnableFlag)
	{
		VOS_Printf("integrity : enabled\n");
	}else
	{
		VOS_Printf("integrity : disabled\n");
	}

	//完保速率
	VOS_Printf("maxIPDataRate: %d\n",pInfo->maxIPDataRate);

	return VOS_OK;
}

INT32 printfCuupUeIdxTable(CuupUeIdxTable_t *pTable)
{
	UINT8 i = 0;
	VOS_Printf("0 is used, 1 is not used, else is wrong\n");
	for(i=0; i<MAX_UE_NUM; i++)
	{
		VOS_Printf("i is %d  ",i);
		VOS_Printf("usedFlag: %d  ",pTable->ueIdxInfo[i].isUsed);
		VOS_Printf("ueE1apId: %d  ",pTable->ueIdxInfo[i].ueE1apId);
		VOS_Printf("ueIdx:    %04x\n",pTable->ueIdxInfo[i].ueIdx);
	}
	VOS_Printf("at end i = %d\n",i);

	return VOS_OK;
}

INT32 printfMsgbBuff(MsgbBuff_t *pMsgBuff)
{
	NULL_CHECK(pMsgBuff);
	
	UINT8 *pMsgHead = msgbData(pMsgBuff);
	UINT32 pduLen = msgbDataUsedLen(pMsgBuff);
	
	/*VOS_Printf("msgb maxDataLen:%d maxHeadLen:%d headSpareLen:%d tailOffset:%d ",
		pMsgBuff->msgbInfo.maxDataLen,
		pMsgBuff->msgbInfo.maxHeadLen,
		pMsgBuff->msgbInfo.headSpareLen,
		pMsgBuff->msgbInfo.tailOffset);*/

	VOS_Printf(VOS_COLOR_BLUE"data len:%d\n"VOS_COLOR_NONE,pduLen);

	UINT32 j = 0;
	for(j=0; j<pduLen; j++)
	{
		VOS_Printf("%02x ",*(pMsgHead+j));
	}
	VOS_Printf("\n");
	
	return VOS_OK;
}

INT32 printfExPduInfo(ExPduInfo_t *pPdu)
{	
	NULL_CHECK(pPdu);
	
	VOS_Printf("exHdrLen:%d Byteslen:%d exHdrType:0x%02x\n",
				pPdu->exHdrLen,pPdu->len,pPdu->exHdrType);
	
	UINT8 i = 0;
	for(i=0; i<pPdu->len; i++)
	{
		VOS_Printf("%02x ",*((UINT8 *)(pPdu->pPdu)+i));
	}
	VOS_Printf("\n");
	
	return VOS_OK;
}

INT32 printfSdapNewInstance(SdapGlobalDtat_t *pGlobalData)
{
	VOS_Printf("\n**sdapCreateNewInstance**\n");
	VOS_Printf("upE1apId:%d\n",pGlobalData->upE1apId);
	VOS_Printf("sessNum:%d\n",pGlobalData->sessNum);
	UINT8 i = 0;
	UINT8 m = 0;
	UINT8 n = 0;
	VOS_Printf("sessId list:");
	for(i=0; i<pGlobalData->sessNum; i++)
	{
		VOS_Printf("%d,",pGlobalData->sessId[i]);
	}
	VOS_Printf("\n");
	
	UINT8 pduId = 0;
	for(i=0; i<pGlobalData->sessNum; i++)
	{	
		pduId = pGlobalData->sessId[i];
		VOS_Printf("i:%d, sessId:%d, sessNum:%d\n",i,pduId,pGlobalData->sessNum);
		VOS_Printf("drbNum:%d\n",pGlobalData->sdapInstance[pduId].drbNum);
		VOS_Printf("drbId list:");	
		for(m=0; m<pGlobalData->sdapInstance[pduId].drbNum; m++)
		{
			VOS_Printf("%d,",pGlobalData->sdapInstance[pduId].drbId[m]);
		}
		VOS_Printf("\n");
		
		VOS_Printf("\n******drbCfg*******\n");

		UINT8 j=0;
		UINT8 drbId = 0;
		UINT8 qfiNum = 0;
		for(n=0; n<pGlobalData->sdapInstance[pduId].drbNum; n++)
		{
			drbId = pGlobalData->sdapInstance[pduId].drbId[n];
			VOS_Printf("drbId:%d \n",drbId);
			VOS_Printf("drbCfg.drbId:%d\n",pGlobalData->sdapInstance[pduId].drbCfg[drbId-1].drbId);
			VOS_Printf("drbCfg.sdapUlHead:%d\n",pGlobalData->sdapInstance[pduId].drbCfg[drbId-1].sdapCfg.sdapUlHeaderInd);
			VOS_Printf("drbCfg.sdapDlHead:%d\n",pGlobalData->sdapInstance[pduId].drbCfg[drbId-1].sdapCfg.sdapDlHeaderInd);
			VOS_Printf("drbCfg.defaultDrbInd:%d\n",pGlobalData->sdapInstance[pduId].drbCfg[drbId-1].sdapCfg.defaultDrbInd);
			qfiNum = pGlobalData->sdapInstance[pduId].drbCfg[drbId-1].qfiNum;
			VOS_Printf("drbCfg.qfiNum:%d\nqfi list:",qfiNum);
			for(j=0; j<qfiNum; j++)
			{
				VOS_Printf("%d ",pGlobalData->sdapInstance[pduId].drbCfg[drbId-1].qfi[j]);
			}
			VOS_Printf("\n");
		}
	}

	return VOS_OK;
}


