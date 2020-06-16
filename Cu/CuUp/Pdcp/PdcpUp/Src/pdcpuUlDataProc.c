/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/
#include "vos_types.h"
#include "vos_linklist.h"
#include "vos_module.h"
#include "vos_sem.h"
#include "cuupCommon.h"
#include "msgb.h"
#include "bitsPack.h"
#include "pdcpu.h"
#include "gnbCommon.h"
#include "pdcpCommon.h"
#include "pdcpuCore.h"
#include "cuupUeIdTransf.h"

#include "cuupTest.h"

extern PdcpuUeInfo_t *gPdcpuUeInfo[MAX_UE_NUM];
extern CuupUeIdxTable_t gPdcpuUeIdxTable;
extern ULONG gPdcpuModuleId;
ULONG gPdcpuUlModuleId;

extern INT32 sdapUlDataProc(UINT64 upE1apId, UINT64 sessId, UINT64 drbId, MsgbBuff_t *pMsgBuff);
INT32 pdcpuUlInit(ULONG userModuleId)
{
	gPdcpuUlModuleId = userModuleId;
	
	return VOS_OK;
}

INT32 pdcpuUnpackPduHead(MsgbBuff_t *pMsgBuff, PdcpSnSize_e snSize, 
							UINT8 *pPdutype, UINT32 *pSn)
{	
	BitOpt_t bit;
	UINT8 *pMsgHead = msgbData(pMsgBuff);
	UINT16 pduLen = msgbDataUsedLen(pMsgBuff);

	initBits(&bit, pMsgHead, pduLen, 0);
	*pPdutype = unpackBits(&bit, 1);
	if(PDCP_CTRL_PDU == *pPdutype)
	{		
		//*pCtrlPduType = unpackBits(&bit, 3);

		return 0;
		
	}else if(PDCP_DATA_PDU == *pPdutype)
	{		
		if(LEN12BITS == snSize)
		{
			/*************D/C + 3R + PDCP SN = 16bits*************/
			skipBits(&bit, 3, BIT_UNPACKED);
			*pSn = unpackBits(&bit, LEN12BITS);
			
			return PDCP_SN_12_HEAD_LEN;
			
		}else if(LEN18BITS == snSize)
		{
			/*************D/C + 5R + PDCP SN =24bits*************/
			skipBits(&bit, 5, BIT_UNPACKED);
			*pSn = unpackBits(&bit, LEN18BITS);
			
			return PDCP_SN_18_HEAD_LEN;
			
		}else
		{
			pdcpuLog(LOG_ERR,"[PDCPU] sn size is wrong!\n");
			return VOS_ERROR;
		}
	}

	return VOS_OK;
}


INT32 pdcpuDecideCountAndHFN(PdcpStateVar_t *pStateVar, INT32 rcvdSn, PdcpSnSize_e snSize)
{
	UINT32 rcvdHFN = 0;
	UINT32 rxDeliv = pStateVar->rxDelivery;
	INT32  tmp = 0;
	
	if(LEN12BITS == snSize)
	{
		tmp = GET_SN_12_SN(rxDeliv) - SN_12_WINDOW_SIZE;
		if(rcvdSn < tmp)
		{
			rcvdHFN = GET_HFN_12_SN(rxDeliv) + 1;
		}else if(rcvdSn >= GET_SN_12_SN(rxDeliv) + SN_12_WINDOW_SIZE)
		{
			rcvdHFN = GET_HFN_12_SN(rxDeliv) - 1;
		}else
		{
			rcvdHFN = GET_HFN_12_SN(rxDeliv);
		}
		pStateVar->rxCount = GET_COUNT_12_SN(rcvdHFN, rcvdSn);
				
	}else if(LEN18BITS == snSize)
	{
		tmp = GET_SN_18_SN(rxDeliv) - SN_18_WINDOW_SIZE;
		if(rcvdSn < tmp)
		{
			rcvdHFN = GET_HFN_18_SN(rxDeliv) + 1;
			
		}else if(rcvdSn >= GET_SN_18_SN(rxDeliv) + SN_18_WINDOW_SIZE)
		{
			rcvdHFN = GET_HFN_18_SN(rxDeliv) - 1;			
		}else
		{
			rcvdHFN = GET_HFN_18_SN(rxDeliv);
		}
		pStateVar->rxCount = GET_COUNT_18_SN(rcvdHFN, rcvdSn);	
	}else
	{
		pdcpuLog(LOG_ERR,"[PDCPU] sn size is wrong!\n");
		return VOS_ERROR;
	}
		
	return VOS_OK;
}


INT32 pdcpuCtrlPduProc(MsgbBuff_t *pMsgBuff, PdcpCtrlPduType_e ctrlPduType, PdcpDrbEntity_t *pPdcpDrbEntity)
{
	pdcpuMsgbFree(pMsgBuff);

	return VOS_OK;	
}


INT32 pdcpuDelivUldata(PdcpDrbEntity_t *pDrbEntity)
{
	/* traverse list and send data to SDAP */	
	struct cl_lib_listnode *pNode = NULL;
	PdcpuDataBuffNode_t *pDataInBuff1 = NULL;
	PdcpuDataBuffNode_t *pDataInBuff2 = NULL;

	UINT32 count = 0;
	
	pNode = cl_lib_listhead(pDrbEntity->pRxSduList);	
	if(NULL == pNode)
	{
		/* There is no data in buffer */
		VOS_Printf("there is no data in buffer\n");
		return VOS_OK;
	}
	pDataInBuff1 = (PdcpuDataBuffNode_t *)cl_lib_getdata(pNode);		

	if(pDataInBuff1->count == pDrbEntity->stateVar.rxDelivery)
	{	
		while(pNode)
		{		
			cl_lib_nextnode (pNode);
			count = pDataInBuff1->count;
			
			/*+++++++++++++++++++++++++++test+++++++++++++++++++++++++++*/					
			//VOS_Printf("\n[pdcp ul data] pdcpuDelivUldata ueIdx:%d ueE1apId:%d drbId:%d count:%d \n",
			//			pDrbEntity->ueIdx,pDrbEntity->ueE1apId,pDrbEntity->drbId,count);
			//printfMsgbBuff(pDataInBuff1->pData);		
			/*---------------------------test----------------------------*/
			
			/* delivery to sdap,if sdapUlDataProc return VOS_OK,free the data
			   else, also free the data */
			sdapUlDataProc(pDrbEntity->ueE1apId,pDrbEntity->pduSessionId,pDrbEntity->drbId,pDataInBuff1->pData);
			
			/* update stateVar */
			pDrbEntity->stateVar.rxDelivery = count + 1;
						
			/* delete rx buffer */
			cl_lib_listnode_delete(pDrbEntity->pRxSduList, pDataInBuff1);
			pdcpuFreeDataBuffNode(pDataInBuff1);
			
			if(NULL == pNode)
			{
				/* There is no more data in buffer */
				return VOS_OK;
			}
			pDataInBuff2 = (PdcpuDataBuffNode_t *)cl_lib_getdata(pNode);				
			if(NULL == pDataInBuff2)
			{
				/* There is no more data in buffer */
				pdcpuLog(LOG_ERR,"[PDCPU] data is null\n");
				return VOS_ERROR;
			}
					
			if(pDataInBuff2->count == count + 1)
			{
				/* The data is continuously */
				pDataInBuff1 = pDataInBuff2;
				
			}else if(pDataInBuff2->count > count + 1)
			{	
				/* The data is not continuously */
				return VOS_OK;	
			}else
			{	
				pdcpuLog(LOG_ERR,"[PDCPU] out of order in receiving buffer!\n");
				return VOS_ERROR;
			}

			
		}

		return VOS_OK;
	}else if(pDataInBuff1->count > pDrbEntity->stateVar.rxDelivery)
	{
		/* the data whose count value is equal to rxDelivery,is still waited for */
		return VOS_OK;
	}else
	{
		pdcpuLog(LOG_ERR,"[PDCPU] rxbuff is wrong!\n");
		return VOS_ERROR;
	}
	
	return VOS_OK;
}


/*******************************************************************************
 * pdcp-u ul data process
 * INPUT:
 * 	 ueE1apId: E1AP ID of the UE
 * 	 drbId: ID of data radio bearer
 * 	 pMsgBuff: SDAP PDU
 * OUTPUT:
 * 	 0: success
 * 	 -1:failed
*******************************************************************************/
INT32 pdcpuUlDataProc(UINT64 ueE1apId, UINT8 drbId, MsgbBuff_t *pMsgBuff)
{	
	UINT8  pduType     = 0;
	UINT32 rcvdSn	   = 0;
	UINT32 count 	   = 0;
	INT8   pduHeadLen  = 0;
	UINT16 ueIdx       = 0xffff;
	INT32  ret         = -1;
	PdcpSnSize_e		snSize;
	PdcpDrbEntity_t 	*pPdcpDrbEntity = NULL;
	PdcpStateVar_t		*pStateVar		= NULL;
			
	pdcpuNullCheck(pMsgBuff);
	UINT8 *pMsgHead = msgbData(pMsgBuff);
	UINT16 pduLen   = msgbDataUsedLen(pMsgBuff);
	if(pduLen<1)
	{
		pdcpuMsgbFree(pMsgBuff);
		pdcpuLog(LOG_ERR,"[PDCPU] data len is too small!\n");
		return VOS_ERROR;
	}
	
	if(VOS_ERROR == cuupGetUeIdx(ueE1apId, &ueIdx, &gPdcpuUeIdxTable))
	{
		pdcpuLog(LOG_ERR,"[PDCPU] add ueE1apId failed\n");
		pdcpuMsgbFree(pMsgBuff);
		return VOS_ERROR;
	}
	pdcpuGetEntity(ueIdx, drbId, pPdcpDrbEntity);
	pdcpuNullCheck(pPdcpDrbEntity);
	snSize 	  = pPdcpDrbEntity->pdcpSnSizeUl;
	pStateVar = &pPdcpDrbEntity->stateVar;
		
	/* get pdcp pdu type */
	BitOpt_t bit;
	initBits(&bit, pMsgHead, pduLen, 0);
	pduType = unpackBits(&bit, 1);

    if(PDCP_DATA_PDU == pduType)
	{
		//1.analysis pdcp header: shall not move the data start pointer
		pduHeadLen = pdcpuUnpackPduHead(pMsgBuff, snSize, &pduType, &rcvdSn);
		if(VOS_ERROR == pduHeadLen)
		{
			pdcpuLog(LOG_ERR,"[PDCPU] unpack pdu head wrong!\n");
			pdcpuMsgbFree(pMsgBuff);
			return VOS_ERROR;
		}
		
		//make sure received HFN and received Count
		if(VOS_ERROR == pdcpuDecideCountAndHFN(pStateVar, rcvdSn, snSize))
		{
			pdcpuLog(LOG_ERR,"[PDCPU] get count wrong!\n");
			pdcpuMsgbFree(pMsgBuff);
			return VOS_ERROR;
		}
        
		count = pStateVar->rxCount;
        
		//2.deciphering : except pdcp pdu head, the SDAP header and the SDAP Control PDU
		//get sdap pdu type
		BitOpt_t SdapHeadbit;
		UINT8 *pSdapPduHead = msgbData(pMsgBuff) + pduHeadLen;
		initBits(&SdapHeadbit, pSdapPduHead, 1, 0);
		//5.remove pdcp pdu head
		msgbHeadPull(pMsgBuff, pduHeadLen);
		ret = sdapUlDataProc(ueE1apId,pPdcpDrbEntity->pduSessionId,drbId,pMsgBuff);
		pPdcpDrbEntity->stateVar.rxDelivery = count + 1;
		if(VOS_OK == ret)
		{
			pdcpuMsgbFree(pMsgBuff);
			return VOS_OK;
		}else
		{
			pdcpuMsgbFree(pMsgBuff);
			pdcpuLog(LOG_ERR,"[PDCPU] ul proc failed\n");
			return VOS_ERROR;
		}
		
				
	}

	return VOS_OK;
}

