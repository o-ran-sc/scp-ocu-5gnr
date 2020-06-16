/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/
#include <sys/time.h>
#include "vos_types.h"
#include "vos_linklist.h"
#include "vos_sem.h"
#include "cuupCommon.h"
#include "msgb.h"
#include "bitsPack.h"
#include "pdcpu.h"
#include "gnbCommon.h"
#include "cuupUeIdTransf.h"

#include "cuupTest.h"	//for test

extern PdcpuUeInfo_t    *gPdcpuUeInfo[MAX_UE_NUM];
extern CuupUeIdxTable_t gPdcpuUeIdxTable;
extern ULONG gPdcpuModuleId;

ULONG gPdcpuDlModuleId;

INT32 pdcpuDlInit(ULONG userModuleId)
{
	gPdcpuDlModuleId = userModuleId;

	return VOS_OK;
}

INT32 pdcpuPackPduHead(PdcpRlcMode_e rlc_mode,PdcpSnSize_e snSize, UINT32 sn, MsgbBuff_t *msgb)
{
	BitOpt_t bit;
	UINT8   *p 		  	 = NULL;
	UINT8   *pPduHead 	 = NULL;
	UINT8 	 pduHeadLen  = 0;

	if(LEN12BITS == snSize)
	{
		pduHeadLen = PDCP_SN_12_HEAD_LEN;
	}else if(LEN18BITS == snSize)
	{
		pduHeadLen = PDCP_SN_18_HEAD_LEN;
	}else
	{	
		pdcpuLog(LOG_ERR,"[PDCPU] sn size is wrong!\n");
		return VOS_ERROR;
	}
	pPduHead  =  VOS_Malloc(pduHeadLen,gPdcpuDlModuleId);
	pdcpuNullCheck(pPduHead);
	VOS_MemZero(pPduHead, pduHeadLen);

	if(snSize == LEN12BITS)
	{
		if(sn >= MAX_PDCP_SN_12)
		{
			pdcpuLog(LOG_ERR,"[PDCPU] sn too big\n");
			return VOS_ERROR;
		}
		initBits(&bit, pPduHead, 16, 0);
		packBits(&bit, 1, 1);
		skipBits(&bit, 3, BIT_PACKED);
		packBits(&bit, 4, ((sn & 0xf00)>>8));
		packBits(&bit, 8, sn & 0x0ff);		
	}else if(snSize == LEN18BITS)
	{
		if(sn >= MAX_PDCP_SN_18)
		{
			pdcpuLog(LOG_ERR,"[PDCPU] sn too big\n");
			return VOS_ERROR;
		}
		initBits(&bit, pPduHead, 24, 0);
		packBits(&bit, 1, 1);
		skipBits(&bit, 5, BIT_PACKED);
		packBits(&bit, 2, ((sn & 0x00030000)>>16));
		packBits(&bit, 8, ((sn & 0x0000ff00)>>8));
		packBits(&bit, 8, sn & 0x000000ff);
	}else
	{
		pdcpuLog(LOG_ERR,"[PDCPU] sn size error\n");
		return VOS_ERROR;
	}

	p = msgbHeadPush(msgb, pduHeadLen);
	if(NULL != p)
	{
		VOS_MemCpy(p, pPduHead, pduHeadLen);
	}else
	{
		pdcpuLog(LOG_ERR,"[PDCPU] msgbHeadPush failed!\n");
		return VOS_ERROR;
	}
	
	if(NULL != pPduHead)
	{ 
		VOS_Free(pPduHead);
		pPduHead= NULL;
	}
	
	return pduHeadLen;
}


/*******************************************************************************
 * pdcp-u dl data process
 * INPUT:
 *		ueE1apId: E1AP ID of the UE
 *		drbId: ID of data radio bearer
 *		pMsgBuff: PDCP PDU
 * OUTPUT:
 *		0: success
 *		-1:failed
 *******************************************************************************/
INT32 pdcpuDlDataProc(UINT64 ueE1apId, UINT8 drbId, MsgbBuff_t *pMsgBuff, UINT8 sdapPduType)
{	
	UINT32 sn 		  = 0;
	INT8   pduHeadLen = 0;

	PdcpSnSize_e		snSize;
	PdcpRlcMode_e 		rlcMode;
	PdcpDrbEntity_t 	*pPdcpDrbEntity = NULL;
	
	UINT16 ueIdx;	
	if(VOS_ERROR == cuupGetUeIdx(ueE1apId, &ueIdx, &gPdcpuUeIdxTable))
	{
		pdcpuLog(LOG_ERR,"[PDCPU] get ueIdx failed,ueE1apId:%d\n",ueE1apId);
		return VOS_ERROR;
	}
	pdcpuCheckUeIdx(ueIdx);
	pdcpuCheckDrbId(drbId);
	
	pdcpuGetEntity(ueIdx, drbId, pPdcpDrbEntity);
	pdcpuNullCheck(pPdcpDrbEntity);
	rlcMode = pPdcpDrbEntity->rlcMode;
	
	//1.check data
	pdcpuNullCheck(pMsgBuff);
	
	//2.assign the sn 
	UINT32 count = pPdcpDrbEntity->stateVar.txNext++;

	// check out count wrapping around whether or not
	if(0xffffffff == count)
	{
		pdcpuLog(LOG_ERR,"[PDCPU] count value is going to wrap around!\n");
		return VOS_ERROR;
	}
	
	snSize = pPdcpDrbEntity->pdcpSnSizeDl;
	if(snSize == LEN12BITS)
	{
		sn = GET_SN_12_SN(count);
	}else if(snSize == LEN18BITS)
	{
		sn = GET_SN_18_SN(count);
	}else
	{
		pdcpuLog(LOG_ERR,"[PDCPU] sn size is wrong!\n");
		return VOS_ERROR;
	}

	//4.add pdu head
	pduHeadLen = pdcpuPackPduHead(rlcMode, snSize, sn, pMsgBuff);
	if(VOS_ERROR == pduHeadLen)
	{
		pdcpuLog(LOG_ERR,"[PDCPU] pack pdcp pdu head failed!\n");
		return VOS_ERROR;
	}
	
	//8. 否则：cuf1u将数据发送成功后，释放
	if(VOS_OK == cuf1uDlDataProc(ueE1apId, drbId, pMsgBuff, NULL))
	{
		//vos_info_print("there is no buffer\n");
		msgbFree(pMsgBuff);
		pMsgBuff = NULL;
		return VOS_OK;
	}else
	{
		pdcpuLog(LOG_ERR,"[PDCPU] cuf1u send failed\n");
		return VOS_ERROR;
	}
	
}

