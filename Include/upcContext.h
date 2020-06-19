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


#ifndef __UPCCONTEXT_H__
#define __UPCCONTEXT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "gnbCommon.h"
#include "cuModuleInterface.h"



#define UPC_MAX_IP_NUM			5
#define UPC_MAX_UP_NUM			1
#define UPC_MAX_PLMN_NUM        2
#define UPC_MAX_SLICE_NUM       3
#define UPC_MAX_QOS_PARA_NUM    10
#define UPC_MAX_UE_NUM          MAX_UE_NUM
#define UPC_MAX_SESSION_NUM     10
#define UPC_MAX_DRB_NUM			2

typedef struct
{
	INT64				sessId;
	E1apCause_e			cause;
}SessFailitem_t;

typedef struct
{
	INT16				drbId;
	E1apCause_e			cause;
}DrbFailitem_t;

typedef struct
{
	UINT8				qosFlowId;
	E1apCause_e			cause;
}qosFailitem_t;

typedef struct
{
	UINT8						qosSetupAllowed;
	UINT8						qosModAllowed;

	UINT8						qosFlowId;

	/* QOS Info Begin */
	QosFlowLevelQosPar_t        qosPara;

	UINT8						qosMapFlag;
	QosFlowMapInd_e			qosFlowMapInd;
	/* QOS Info End */

	E1apCause_e					qosSetFailCause;
	E1apCause_e					qosModFailCause;
}upcTempQosInfo_t;

typedef struct
{
	UINT8						drbSetupAllowed;
	UINT8						drbModAllowed;

	UINT8						drbId;

	UINT16						qosSetupNum;
	UINT16						qosSetupSuccNum;/* 最终建立成功的个数 */
	UINT16						qosSetupFailNum;/* 最终建立失败的个数 */

	UINT16						qosModNum;
	UINT16						qosModSuccNum;/* 最终建立成功的个数 */
	UINT16						qosModFailNum;/* 最终建立失败的个数 */

	upcTempQosInfo_t			*pQosSetupList;
	upcTempQosInfo_t			*pQosModList;

	/* DRB Info --Begin */

	UINT8						sdapFlag;/* Only Mod Optional */
	SdapCfg_t					sdapConfig;

	UINT8						pdcpFlag;/* Only Mod Optional */
	PDCPConfiguration_t	        pdcpConfig;
	CellGroupInformation_t      cellGroupInfo;

	CellGroupInformation_t      cellGroupToAdd;/* Only Mod Optional */
	CellGroupInformation_t      cellGroupToMod;/* Only Mod Optional */
	CellGroupInformation_t      cellGroupToRemove;/* Only Mod Optional */

	UINT8						DFIReqFlag;
	DFIRequest_t				drbDFIReq;
	UINT8						DFIRspFlag;/* Only Mod Optional */
	DFIResponse_t      			drbDFIRsp;

	UINT8						inactTimeFlag;
	INT64			     		inactivityTimer;

	UINT8						pdcpSNStatuFlag;
	PdcpSNStatusInfo_t			pdcpSNStatusInfo;

	PdcpSNStatusRequest_e		pdcpSNStatusReq;

	UPParametersList_t			f1UlUpPara;
	UINT8						f1DlUpParaFlag;/* Only Mod Optional */
	UPParametersList_t			f1DlUpPara;

	UINT8						pdcpUlCntFlag;
	PdcpCount_t					pdcpUlCount;

	UINT8						pdcpDlCntFlag;
	PdcpCount_t					pdcpDlConut;

	/* DRB Info -- end */

	E1apCause_e					drbSetFailCause;
	E1apCause_e					drbModFailCause;
}upcTempDrbInfo_t;

typedef struct
{
	UINT8						sessSetupAllowed;
	UINT8						sessModAllowed;

	UINT16						pduSessId;

	UINT16						drbSetupNum;
	UINT16						drbSetupSuccNum;/* 最终建立成功的个数 */
	UINT16						drbSetupFailNum;/* 最终建立失败的个数 */

	UINT16						drbModNum; /* 最初请求修改的个数 */
	UINT16						drbModSuccNum;	/* 最终修改成功的个数 */
	UINT16						drbModFailNum; /* 最终修改失败的个数 */

	UINT8						drbRemoveNum;
	UINT8						drbRemoveId[UPC_MAX_DRB_NUM];

	upcTempDrbInfo_t			*pTempDrbSetupList;
	upcTempDrbInfo_t			*pTempDrbModList;

	/* Session Info --Begin */
	PduSessType_e	 			pduSessionType;
	SNssai_t	 				snssai;

	UINT8						secuIndiFlag;/* Only Mod Optional */
	SecuInd_t				    secuIndi;
	SecuResult_t	            securityResult;

	UINT8						ulUpChgFlag;/* Only Mod Optional */
	UpTransLayerInfo_t          ulUpTNLInfo;

	UINT8						dlAMBRFlag;
	UINT64	 					sessDlAMBR;

	UINT8						DFIReqFlag;
    DFIRequest_t			    DFIInfoReq;
	UINT8						DFIRspFlag;/* Only Mod Optional */
	DFIResponse_t				DFIInfoRsp;

	UINT8						InactTimerFlag;
	INT64			     		inactTimer;

	UINT8						dlNGupTnlFlag;
	UpTransLayerInfo_t			dlNgUpTnlInfo;
	UINT8						dlNgUpChgFlag;

	UINT8						InstanceFlag;
	INT64						networkInstance;
	/* session Info --End */

	E1apCause_e					sessSetFailCause;
	E1apCause_e					sessModFailCause;
}upcTempSessInfo_t;


typedef struct
{
	struct upUeCb				*pUeCb;

	UINT16						sessSetupNum;	/* 最初请求建立的个数 */
	UINT16						sessSetupSuccNum;/* 最终建立成功的个数 */
	UINT16						sessSetupFailNum;/* 最终建立失败的个数 */

	UINT16						sessModNum; /* 最初请求修改的个数 */
	UINT16						sessModSuccNum;	/* 最终修改成功的个数 */
	UINT16						sessModFailNum; /* 最终修改失败的个数 */

	upcTempSessInfo_t			*pTempSessSetupList;
	upcTempSessInfo_t			*pTempSessModList;


	/* Content	--Begin */
	UINT8						secuInfoFlag;/* Only Mod Optional */
	SecuInfo_t					secuInfo;

	UINT8						dlAmbrFlag;/* Only Mod Optional */
	UINT64						ueDlAMBR;

	PlmnId_t					servPlmnId;
	ActNotiLevel_e				actNotiLevel;

	UINT8						dlIPDRFlag;
	UINT64						ueDlMaxIPDR;

	UINT8						inactTimeFlag;
	INT64						inactTimer;

	UINT8						bearStaChageFlag;
	BearCxtStatusChange_e	 	bearerCxtStatusChg;

	UINT8						newTnlInfoReqFlag;/* Only Mod Optional */
	NewUlTnlInfoRequire_e		newTnlInfoReq;

	UINT8						dataDisFlag;/* Only Mod Optional */
	DataDisRequire_e            dataDisRequire;
	/* Content	--End */
}upcTempInfo_t;


struct upSessCb;
struct upUeCb;
struct upInstance;
typedef struct upDrbCb
{
	UINT8						useFlag;
    INT64	                    drbId;

    SdapCfg_t					sdapConfig;
	PDCPConfiguration_t	        pdcpConfig;
	UPParametersList_t			f1UlUpPara;
	UPParametersList_t			f1DlUpPara;
	CellGroupInformation_t      cellGroupInfo;

	/* QOS INFO */
	QosFlowQosPara_t			qosFlowPara;

	UINT8						DFIFlag;
    DFIRequest_t      			dataForInfoReq;


	PdcpSNStatusInfo_t			pdcpSNStatusInfo;
    struct upSessCb             *pSessionCb;
}UpDrbCb_t;

typedef struct upSessCb
{
	UINT8						useFlag;
    UINT16		                sessId;
    PduSessType_e	            sessType;
    SNssai_t                    sNSsai;

    SecuInd_t	                secuInd;
	SecuResult_t				securityResult;

    UINT64		                dlAMBR;

    UpTransLayerInfo_t          ngUlUpTransInfo;
	UpTransLayerInfo_t          ngDlUpTransInfo;

    DFIRequest_t      			dataForInfoReq;



	INT64						networkInstance;

	UINT8                       drbNum;
    UpDrbCb_t                   *pDrbCb[UPC_MAX_DRB_NUM];

	struct upUeCb				*pUeCb;
}UpSessCb_t;

typedef enum upUeState_e
{
    UP_UE_INIT,
    UP_UE_ACTIVE,
    UP_UE_WAITING_INACTIVE,
    UP_UE_INACTIVE
}UpUeState_e;

typedef struct upUeCb
{
	UINT8						useFlag;
    UINT64				        cpE1apId;
    UINT64				        upE1apId;

    UpUeState_e                 ueState;
    SecuInfo_t					secuInfo;
    UINT64	                    ueDlAMBR;
	UINT64						ueDlMaxIPDR;
    PlmnId_t                    plmnId;

    INT64			            inActTimer;

	UINT16						sessNum;/* current session num */
    UpSessCb_t                  *pSessCb[UPC_MAX_SESSION_NUM];
	struct upInstance           *pUpInstance;
}UpUeCb_t;

typedef struct upInstance
{
    Instance_t                  instance;
	UINT32						moduleId;
	UINT32						state;
    UINT64                      upId;
    GnbCuupName_t               upName;
    GnbCucpName_t               cpName;
	INT8						upAddrNum;
    IpAddress_t                 upAddr[UPC_MAX_IP_NUM];
	INT8						cpAddrNum;
	IpAddress_t					cpAddr[UPC_MAX_IP_NUM];

    INT64				        upCapa;
    UINT32						bPlmnNum;
	E1apUpbPlmnCfgInfo_t		bPlmnCfgInfo[e1ap_maxnoofSPLMNs];
    UINT32                      ueNum;
    UpUeCb_t                    *pUeCb[UPC_MAX_UE_NUM];
}UpInstance_t;

UpInstance_t *upcGetInstance();
UpUeCb_t* upcAllocUeCb(UpInstance_t *pInstance, UINT64	cuCpE1apId);
INT32 upcSetSessionCb(UpUeCb_t	* pUeCb, PduSessionResourceToSetupList_t *pPduSessionSetupList);
void upcSetUeCb(UpUeCb_t	* pUeCb, E1apBearerContextSetupReq_t *pBearerCxtSetupReq);
UpUeCb_t* upcGetUeCbByUpUeE1apId(UpInstance_t *pInstance, UINT64	cuUpE1apId);
void upcRemoveSessionCb(UpUeCb_t	* pUeCb, PduSessionResourceToRemoveList_t *pRemoveList);
UpSessCb_t *upcGetSessCb(UpUeCb_t *pUeCb, UINT8 pduSessId);
UpDrbCb_t *upcGetDrbCb(UpSessCb_t *pSessCb, UINT8 drbId);

#ifdef __cplusplus
}
#endif

#endif
