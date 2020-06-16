/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef __CUMODULEINTERFACEH__
#define __CUMODULEINTERFACEH__

#ifdef __cplusplus
extern "C" {
#endif

#include "cuCommon.h"
#include "cuModuleCommon.h"
#include "ngasn_constant.h"
/**********************************************************************************
***********************************************************************************
**************** CUC <--> NGAP               ACCORDING TO STRUCTURE ***************
***********************************************************************************
***********************************************************************************/
typedef UINT16      Instance_t;

#define NGAP_MAX_AMF_NUM			2
#define NGAP_MAX_UE_NUM				MAX_UE_NUM

#define NG_MAX_TAC_NUM      		10
#define NG_MAX_PLMN_NUM     		2

#define NG_MAX_GUAMI_NUM			2
#define NG_MAX_SESSION_NUM  		10

#define RrcVersionLatestVerEnhancedChosen            0x1

#define e1ap_maxnoofErrors								256
#define e1ap_maxnoofSPLMNs								12
#define e1ap_maxnoofSliceItems							1024
#define e1ap_maxnoofIndividualE1ConnectionsToReset		65536
#define e1ap_maxnoofNGRANQOSParameters					256
#define e1ap_maxnoofDRBs								32
#define e1ap_maxnoofNRCGI								512
#define e1ap_maxnoofPDUSessionResource					256
#define e1ap_maxnoofQoSFlows							64
#define e1ap_maxnoofUPParameters						8
#define e1ap_maxnoofCellGroups							4


typedef struct rrcVersion
{
    UINT16                 bitmask;
    UINT8                  latestRrcVer;//f30版本中 asn的语法描述中是个错误,不应该是bitstring,在f70版本中已经修复
    UINT8                  latestRrcVerEn[3]; /* OPTIONAL */
} RrcVersion_t;

/* AMF Name */
typedef RanName_t   AmfName_t;

typedef struct
{
    UINT16                  plmnNum;
    PlmnId_t                plmnId[NG_MAX_PLMN_NUM];
    SliceList_t             taiSlice[NG_MAX_PLMN_NUM];
}BroadPlmns_t;

typedef struct
{
	UINT16                  taNum;
    CuTac_t                 tac[NG_MAX_TAC_NUM];
    BroadPlmns_t            bPlmn[NG_MAX_TAC_NUM];
}SupportTas_t;

typedef UINT8   AmfRegionId_t;

typedef struct AmfSetId
{
    UINT16                  amfSetId:10;
}AmfSetId_t;

typedef struct AmfPointer
{
    UINT8                   amfPointer:6;
}AmfPointer_t;

#define GUAMI_PLMNID_PRESENCE              (1<<0)
typedef struct guami
{
    UINT8                   bitMask;
    PlmnId_t                plmnId;
    AmfRegionId_t           amfRegionId;
    AmfSetId_t              amfSetId;
    AmfPointer_t            amfPointer;
}Guami_t;

typedef struct guamiList
{
	UINT8					guamiNum;
	Guami_t					guAmi[NG_MAX_GUAMI_NUM];
	AmfName_t				backupAmfName[NG_MAX_GUAMI_NUM]; /* xycTBD */
}GuamiList_t;

#define MAX_SIZE_OF_OCTET_STRING    255
typedef struct NasPdu
{
    UINT32                  size;
    UINT8                   buffer[MAX_SIZE_OF_OCTET_STRING];
}NasPdu_t;

typedef struct  FiveGTmsi
{
    UINT8                   fivegTmsi[4];
}FiveGTmsi_t;

typedef struct FiveGSTmsi
{
    AmfSetId_t              amfSetId;
    AmfPointer_t            amfPointer;
    FiveGTmsi_t             fiveGTmsi;
}FiveGSTmsi_t;

typedef UINT64				AmfUeNgapId_t;

#define EMERGENCY_SERVICE_TARGET_CN_PRESENT         (1 << 0)
typedef struct emergFbInd
{
    UINT16                  				bitMask;
    EmergencyFallbackRequestIndicator_e     emergencyFallbackRequestIndicator;
    EmergencyServiceTargetCN_e     			emergencyServiceTargetCn;           /* OPTIONAL */
} EmergFbInd_t;

typedef struct ueRadioCapaForPagOfNr
{
    UINT32                  size;
    UINT8                   buffer[MAX_SIZE_OF_OCTET_STRING];
}UeRadioCapaForPagOfNr_t;

#define UE_RADIO_CAPABILITY_PAGING_NR_PRESENT       (1 << 0)
#define UE_RADIO_CAPABILITY_PAGING_EUTRA_PRESENT    (1 << 1)
typedef struct UeRadioCapaForPag 
{
    UINT16                                  bitMask;
    UeRadioCapaForPagOfNr_t                 ueRadioCapabilityForPagingOfNr;     /* OPTIONAL */
    UeRadioCapaForPagOfNr_t                 ueRadioCapabilityForPagingOfEutra;  /* OPTIONAL */
} UeRadioCapaForPag_t;

typedef struct UeRadioCapability
{
    UINT32                  size;
    UINT8                   buffer[MAX_SIZE_OF_OCTET_STRING];
}UeRadioCapability_t;

typedef struct ngRanTraceId 
{
    UINT32                  size;
    UINT8                   buffer[MAX_SIZE_OF_OCTET_STRING];
}NgRanTraceId_t;

typedef UINT8 InterToTrace_t;

typedef struct traceActiv 
{
    NgRanTraceId_t          ngRanTraceId;
    InterToTrace_t          interfacesToTrace;
    INT64		            traceDepth;
    TransLayerAddr_t        traceCollectionEntityIpAddress;
} TraceActiv_t;

typedef struct  secuKey
{
    UINT8                   securityKey[32];
}SecuKey_t;

typedef struct
{
	UINT8					nextHopChainingCount;
	SecuKey_t				nextHopNH;
}SecurityCtx_t;
typedef UINT8       RatRestrInfo_t;

typedef struct ratRestrItem
{
    PlmnId_t                plmnId;
    RatRestrInfo_t          ratRestrInfo;
} RatRestrItem_t;

typedef struct mobiRestrInfo
{
    PlmnId_t                                    plmnId;
    UINT8                                       equalPlmnNum;
    PlmnId_t                                    ePlmnId[ngap_maxnoofEPLMNs];
    UINT8                                       ratRestrictNum;
    RatRestrItem_t                              ratRestrictItem[ngap_maxnoofEPLMNsPlusOne];
    UINT8                                       forbiddenAreaNum;
    PlmnId_t                                    forbPlmnId[ngap_maxnoofEPLMNsPlusOne];
    UINT16                                      forbTacNum[ngap_maxnoofEPLMNsPlusOne];
    CuTac_t                                     forbTac[ngap_maxnoofEPLMNsPlusOne][ngap_maxnoofForbTACs];
    UINT8                                       servAreaNum;
    PlmnId_t                                    servPlmnId[ngap_maxnoofEPLMNsPlusOne];
    UINT8                                       allowTacNum[ngap_maxnoofEPLMNsPlusOne];
    CuTac_t                                     allowedTac[ngap_maxnoofEPLMNsPlusOne][ngap_maxnoofAllowedAreas];
    UINT8                                       notAllowTacNum[ngap_maxnoofEPLMNsPlusOne];
    CuTac_t                                     notAllowedTac[ngap_maxnoofEPLMNsPlusOne][ngap_maxnoofAllowedAreas];
}MobiRestrInfo_t;

typedef struct ueSecurCapa 
{
    UINT16                                  nrEncryptionAlgorithms;
    UINT16                                  nrIntegrityProtectionAlgorithms;
    UINT16                                  eutraEncryptionAlgorithms;
    UINT16                                  eutraIntegrityProtectionAlgorithms;
} UeSecurCapa_t;

#define EXPECTED_ACTIVITY_PERIOD_PRESENT                        (1 << 0)
#define EXPECTED_IDLE_PERIOD_PRESENT                            (1 << 1)
#define SOURCEOF_UE_ACTIVITY_BEHAVIOUR_INFORMATION_PRESENT      (1 << 2)
typedef struct expectedUeActivityBehaviour 
{
    UINT16                                  	bitMask;
    INT64					                	expectedActivityPeriod;                 /* OPTIONAL */
    INT64				                    	expectedIdlePeriod;                     /* OPTIONAL */
    SourceOfUEActivityBehaviourInformation_e 	sourceOfUeActivityBehaviourInformation; /* OPTIONAL */
} ExpectedUeActivityBehaviour_t;

#define EXPECTEDUEMOVINGTRAJECTORYITEM_TIME_STAYED_IN_CELL_PRESENT              (1 << 0)
typedef struct expectedUeMovingTrajectoryItem 
{
    UINT16                                      bitMask;
    CuNrCgi_t                                   nrCgi;
    INT64                                       timeStayedInCell;       /* OPTIONAL */
} ExpectedUeMovingTrajectoryItem_t;

#define	EXPECTED_UE_ACTIVITY_BEHAVIOR_PRESENT		(1 << 0)
#define	EXPECTED_HO_INTERVAL_PRESENT				(1 << 1)
#define	EXPECTED_UE_MOBILITY_PRESENT				(1 << 2)
typedef struct
{
	UINT16										bitMask;
	ExpectedUeActivityBehaviour_t               expectedUeActivityBehaviour;
    INT64				                        expectedHoInterval;
    INT64				                        expectedUeMobility;
    UINT8                                       expectUeMovTrajectoryNum;
    ExpectedUeMovingTrajectoryItem_t            expectedUeMovingTrajectory[ngap_maxnoofCellsUEMovingTrajectory];
}ExpectUeBeHaviour_t;

#define	CORE_ASSISTANCE_INFO_UE_SPECIFIC_DRX_PRESENT			(1 << 0)
#define	CORE_ASSISTANCE_INFO_MICO_MODE_INDICATION_PRESENT		(1 << 1)
#define CORE_ASSISTANCE_INFO_EXPECT_UE_BEHAVIOUR_PRESENT		(1 << 2)
typedef struct coreAssitInfo
{
	UINT16										bitMask;
	UeIdIdxValue_t                              ueIdIdxValue;
    INT64		                                ueSpecificDrx;
    UINT8                                       periodicRegistrationUpdateTimer;
    INT64				                        micoModeIndication;
    UINT8                                       inactiveTaiNum;
    Tai_t                                       inactiveTai[ngap_maxnoofTAIforInactive];
	ExpectUeBeHaviour_t   						exceptUeBehaviour;
}CoreAssitInfo_t;

#define NOTIFICATION_CONTROL_PRESENT                (1 << 0)
#define MAX_PACKET_LOSSRATE_DL_PRESENT              (1 << 1)
#define MAX_PACKET_LOSSRATE_UL_PRESENT              (1 << 2)    
typedef struct gbrQosInfo
{
    UINT16                                  bitMask;
	UINT64									maxFlowBitRateDL;
	UINT64									maxFlowBitRateUL;
	UINT64									guaranteedFlowBitRateDL;
	UINT64									guaranteedFlowBitRateUL;
    NotificationControl_e                   notificationControl;            /* OPTIONAL */
    INT64			                        maxPacketLossRateDL;            /* OPTIONAL */
    INT64			                        maxPacketLossRateUL;            /* OPTIONAL */
} GbrQosInfo_t;

#define GBR_QOS_INFORMATION_PRESENT                 (1 << 0)
#define REFLECTIVE_QOS_ATTRIBUTE_PRESENT            (1 << 1)
#define ADDITIONAL_QOS_FLOW_INFORMATION_PRESENT     (1 << 2)
typedef struct qosFlowLevelQosParam
{
    UINT16                                  bitMask;
    QosCharact_t                            qosCharacteristics;
    AllocAndRetenPriority_t        			allocationAndRetentionPriority;
    GbrQosInfo_t                            gbrQosInformation;                  /* OPTIONAL */
    ReflectiveQosAttribute_e                reflectiveQosAttribute;             /* OPTIONAL */
    AddQosFlowInfo_e				        additionalQosFlowInformation;       /* OPTIONAL */
} QosFlowLevelQosParam_t;

#define QOS_FLOW_SETUP_REQ_E_RAB_ID_PRESENT                    (1 << 0)
typedef struct qosFlowSetupReqItem
{
    UINT16                                  bitMask;
    INT64			 	                    qosFlowId;
    QosFlowLevelQosParam_t                  qosFlowLevelQosParameters;
    INT64	                                eRabId;                         /* OPTIONAL */
} QosFlowSetupReqItem_t;

#define MAX_INTERITY_PROTECTED_DATARATE_PRESENT     (1 << 0)
typedef struct securIndic 
{
    UINT16                                  bitMask;
    INT64							        integrityProtectionIndication;
    INT64								    confidentialityProtectionIndication;
    INT64								    maxIntegrityProtectedDataRate;  /* OPTIONAL */
} SecurIndic_t;

typedef struct
{
	UINT64									DlSessAMBR;
	UINT64									UlSessAmbr;
}NgapPduSessAmber_t;

#define PDU_SESSION_SETUP_REQ_TRANSFER_SESSION_AMBR_PRESENT					(1 << 0)
#define PDU_SESSION_SETUP_REQ_TRANSFER_DATA_FORWARD_NOT_POSSIBLE_PRESENT	(1 << 1)
#define PDU_SESSION_SETUP_REQ_TRANSFER_SECURITY_INDICATION_PRESENT			(1 << 2)
#define PDU_SESSION_SETUP_REQ_TRANSFER_NET_WORK_INSTANCE_PRESENT			(1 << 3)

typedef struct
{
	UINT16									bitMask;
	NgapPduSessAmber_t					    sessAMBR;//Optional
    UpTransLayerInfo_t                      ulNguUpTnlInfor;
	UINT8									additionalUpTnlNum;
    UpTransLayerInfo_t                      additionalUlNguUpTnlInfor[ngap_maxnoofMultiConnectivityMinusOne];
    INT64						            dataForwardingNotPossible;//Optional
    INT64			                        pduSessionType;
    SecurIndic_t                            securityIndication;//Optional
	INT64									networkInstance;//Optional
    UINT8                                   qosFlowSetupReqNum;//   >= 1
    QosFlowSetupReqItem_t                   qosFlowSetupRequestItems[ngap_maxnoofQosFlows];
}PduSessSetupReqTransfer_t;

#define	PDU_SESSION_RESOURCE_SETUP_REQUEST_NAS_PDU_PRESENT		(1 << 0)
typedef struct pduSessionSetupReq
{
	UINT16									bitMask;
	UINT16		                            pduSessID;
    NasPdu_t                                nasPdu;//Optional
    SNssai_t                                sNSSAI;
	PduSessSetupReqTransfer_t				pduSetupReqTransfer;
}PduSessionSetupReq_t;

typedef struct recommRanforPag
{
    UINT8                           ranNum;
	/* AMFPagingTarget_PR */
    AmfPgType_e				        amfPgType[ngap_maxnoofRecommendedRANNodes];
    RecomRanGnbId_t          		gNBId[ngap_maxnoofRecommendedRANNodes];
    Tai_t                           Tai[ngap_maxnoofRecommendedRANNodes];
}RecommRanforPag_t;

#define RECOMMCELLITEM_TIME_STAYED_INCELL_PRESENT   (1 << 0)
typedef struct recommCellItem
{
    UINT16                                  bitMask;
    CuNrCgi_t                               nrCgi;
    UINT64                                  timeStayedInCell;                   /* OPTIONAL */
} RecommCellItem_t;

typedef struct recommCellforPag
{
    UINT8                                   cellNum;
    RecommCellItem_t                        cellItem[ngap_maxnoofRecommendedCells];
}RecommCellforPag_t;


#define PAGING_ATTEMPT_INFO_NEXT_PAGING_AREA_SCOPE_PRESENT	(1 << 0)
typedef struct pagingAttemptInfo
{
	UINT8									pagingAttemptCount;
	UINT8									intendNoOfPagingAttempt;
	NextPagingAreaScope_e					nextPagingAreaScope;//Optional
}PagingAttemptInfo_t;

#define ASSIST_DATA_FOR_PAGING_RECOMMAND_CELL_PRESENT		(1 << 0)
#define ASSIST_DATA_FOR_PAGING_PAGING_ATTEMPT_INFO_PRESENT	(1 << 1)
typedef struct assistDataForPaging
{
	RecommCellforPag_t						recommandCell;//Optinal
	PagingAttemptInfo_t						pagingAttemptInfo;//Optional
}AssistDataForPaging_t;
#define QOSFLOW_MAPPING_INDICATION_PRESENT  (1 << 0)
typedef struct AssocQosFlowItem 
{
    UINT16                                  bitMask;
    INT64			                        qosFlowId;
    QosFlowMapInd_e                         qosFlowMappingIndication;   /* OPTIONAL */
} AssocQosFlowItem_t;

typedef struct qosFlowPerTnlInfo
{
    UpTransLayerInfo_t                      upTransLayerInfo;
    UINT8                                   assocQosFlowNum;
    AssocQosFlowItem_t                      assocQosItem[ngap_maxnoofQosFlows];          
}QosFlowPerTnlInfo_t;

typedef struct qosFlowIte 
{
    INT64					                    qosFlowId;
    NgapCause_e                                 cause;
} QosFlowIte_t;

#define PDU_SESSION_SETUP_RSP_SECURITY_RESULT_PRESENT	(1 << 0)
typedef struct pduSessSetupResp
{
	UINT16									bitMask;
    UINT16		                            pduSessId;
    QosFlowPerTnlInfo_t                     dlQosFlowTnlInfo;
	UINT8									addDlQosFlowNum;
    QosFlowPerTnlInfo_t                     addDlQosFlowTnlInfo[ngap_maxnoofMultiConnectivityMinusOne];
    SecuResult_t                            securityResult;
    UINT8                                   qosFlowFailNum;
    QosFlowIte_t                            qosFlowFailtoSetup[ngap_maxnoofQosFlows];
}PduSessSetupResp_t;

typedef struct pduSessSetupFail
{
    UINT16		                            pduSessId;
    NgapCause_e								cause;
}PduSessSetupFail_t;

typedef struct
{
	UINT64									DlUeAMBR;
	UINT64									UlUeAmbr;
}NgapUeAmber_t;

typedef struct
{
	UINT8									timePeriodsNum;
	Timestamp_t								startTimeStamp[ngap_maxnoofTimePeriods];
	Timestamp_t								endTimeStamp[ngap_maxnoofTimePeriods];
	UINT64									usageCountUl[ngap_maxnoofTimePeriods];
	UINT64									usageConutDl[ngap_maxnoofTimePeriods];
}VolumeTimedRpt_t;

typedef struct
{
	INT64									ratType;
	VolumeTimedRpt_t						sessTimedRpt;
}PduSessUsageRpt_t;

typedef struct
{
	INT64									qfi;
	INT64									ratType;
	VolumeTimedRpt_t						flowTimedRpt;
}QosFlowUsageRptItem_t;

typedef struct
{
	PduSessUsageRpt_t						sessUsageRpt;
	UINT8									qosFlowUsageRptNum;
	QosFlowUsageRptItem_t					qosFlowUsageRptItem;
}SecondRATUsageInfo_t;

#define PDU_SESSION_RESOURCE_ITEM_SECOND_RAT_USAGE_INFO_PRESENT	(1 << 0)
typedef struct
{
	UINT16     								sessId;
	SecondRATUsageInfo_t					secondRatUsageInfo;
}PduSessResourceItem_t;

#define HO_REQUIRED_TRANSFER_DIRECT_FORWARD_PATH_AVAILABILITY_PRESENT (1 << 0)
typedef struct
{
	UINT16									bitMask;
	DirectForwardPathAvailability_e			directForwardPathAvailability;//Optional
}HoRequiredTransfer_t;

typedef struct
{
	UINT16     								sessId;
	HoRequiredTransfer_t					HoRequiredTransfer;
}HoRequiredPduSessResourcItem_t;

typedef struct
{
	INT8									qosFlowId;
	DataForwardAccepted_e					dataForwardAccepted;
}QosFlowSetupRspItem_t;

typedef struct
{
	UINT8                                   qosFlowFailNum;
    QosFlowIte_t                            qosFlowFailtoSetup[ngap_maxnoofQosFlows];
}QosFlowSetupFailItem_t;

typedef struct
{
	UpTransLayerInfo_t						additionDlUpTnlInfo;
	QosFlowSetupRspItem_t					additionQosFlowSetupRsp;
	UpTransLayerInfo_t						additionDlForwardUpTnlInfo;
}HoAdditionDlUpTnlInfoItem_t;

#define DATA_FORWARD_RSP_DRB_DL_NGU_UP_TNL_INFO_PRESENT		(1 << 0)
#define DATA_FORWARD_RSP_DRB_UL_NGU_UP_TNL_INFO_PRESENT		(1 << 1)
typedef struct
{
	UINT8									bitMask;
	UINT8									drbId;
	UpTransLayerInfo_t						dlNguUpTnlInfo;//Optional
	UpTransLayerInfo_t						ulNguUpTnlInfo;//Optional
}DataForwardRspDrb_t;

#define HO_REQUEST_ACK_TRANSFER_DL_FORWARD_UP_TNL_INFO_PRESENT		(1 << 0)
#define HO_REQUEST_ACK_TRANSFER_SECURITY_RESULT_PRESENT				(1 << 1)
typedef struct
{
	UpTransLayerInfo_t						dlNguUpTnlInfo;
	UpTransLayerInfo_t						dlForwardUpTnlInfo;//Optinal
	SecuResult_t							securityResult;//Optional
	UINT8									qosFlowRspNum;
	QosFlowSetupRspItem_t					qosFlowSetupRspItem[ngap_maxnoofQosFlows];
	UINT8									qosFlowFailNum;
	QosFlowSetupFailItem_t					qosFlowSetupFailItem[ngap_maxnoofQosFlows];
	UINT8									drbNum;
	DataForwardRspDrb_t						dataForwardRspDrbItem[ngap_maxnoofDRBs];
	UINT8									HoAddDlUpTnlInfoNum;
	HoAdditionDlUpTnlInfoItem_t				HoAddDlUpTnlInfoItem[ngap_maxnoofMultiConnectivityMinusOne];
}HoRequestAckTransfer_t;

typedef struct
{
	UINT16     								sessId;
	HoRequestAckTransfer_t					HoRequestAckTransfer;
}HoRequestAckPduSessItem_t;

typedef struct
{
	NgapCause_e								cause;
}HoRequestUnsuccTransfer_t;

typedef struct
{
	UINT16     								sessId;
	HoRequestUnsuccTransfer_t				HoRequestUnsuccTransfer;
}HoRequestFailPduSessItem_t;

#define	HO_CMD_SUCC_TRANSFER_DATA_FORWARD_RSP_DRB_PRESENT	(1 << 0)
typedef struct
{
	UpTransLayerInfo_t						dlNguUpTnlInfo;//Optional
	UINT8									qosFlowNum;
	UINT64									qosFlowIdItem[ngap_maxnoofQosFlows];
	UINT8									drbNum;
	DataForwardRspDrb_t						dataForwardRspDrbItem[ngap_maxnoofDRBs];
	UINT8									addDlQosFlowNum;
    QosFlowPerTnlInfo_t                     addDlQosFlowTnlInfo[ngap_maxnoofMultiConnectivityMinusOne];
}HoCmdSuccTransfer_t;

typedef struct
{
	UINT16     								sessId;
	HoCmdSuccTransfer_t						HoCmdSuccTransfer;
}HoCmdSuccPduSessResourceItem_t;

typedef struct
{
	NgapCause_e								cause;
}HoCmdFailTransfer_t;

typedef struct
{
	UINT16     								sessId;
	HoCmdFailTransfer_t						HoCmdFailTranser;
}HoCmdFailPduSessResourcItem_t;

typedef struct
{
	UINT16     								sessId;
	SNssai_t								sNssai;
	PduSessSetupReqTransfer_t				HoRequestTransfer;
}HoRequestPduSessResourceItem_t;
#define PATH_SWITCH_REQ_TRANSFER_DL_NGU_TNL_INFO_REUSED_PRESENT		(1 << 0)
#define PATH_SWITCH_REQ_TRANSFER_USER_PLANE_SECUR_INFO_PRESENT		(1 << 1)
typedef struct
{
	UpTransLayerInfo_t						dlNguUpTnlInfo;
	DlNguTnlInfoReused_e					dlNguUpTnlInfoReused;//Optional
	UserPlaneSecurInfo_t					userPlaneSecurInfo;//Optional
	UINT8									qosFlowNum;
	UINT64									qosFlowIdItem[ngap_maxnoofQosFlows];
	UINT8									addDlQosFlowNum;
    QosFlowPerTnlInfo_t                     addDlQosFlowTnlInfo[ngap_maxnoofMultiConnectivityMinusOne];
}PathSwitchReqTransfer_t;

typedef struct
{
	UINT16     								sessId;
	PathSwitchReqTransfer_t					pathSwitchReqTransfer;
}PathSwitchReqPduSessItem_t;

typedef struct
{
	NgapCause_e								cause;
}PathSwitchReqFailTransfer_t;

typedef struct
{
	UINT16     								sessId;
	PathSwitchReqFailTransfer_t				pathSwitchReqFailTransfer;
}PathSwitchReqFailPduSessItem_t;

#define PATH_SWITCH_REQ_ACK_TRANSFER_UL_NGU_UP_TNL_INFO_PRESENT		(1 << 0)
#define PATH_SWITCH_REQ_ACK_TRANSFER_SECURITY_IND_PRESENT			(1 << 1)
typedef struct
{
	UpTransLayerInfo_t						ulNguUpTnlInfo;//Optional
	SecurIndic_t							securityIndication;//Optional
	UINT8									upTransLayerInfoPairItemNum;
	UpTransLayerInfo_t						ulNguUpTnlInfoItem[ngap_maxnoofMultiConnectivityMinusOne];
	UpTransLayerInfo_t						dlNguUpTnlInfoItem[ngap_maxnoofMultiConnectivityMinusOne];
}PathSwitchReqAckTransfer_t;

typedef struct
{
	UINT16     								sessId;
	PathSwitchReqAckTransfer_t				pathSwitchReqAckTransfer;
}PathSwitchReqAckPduSessItem_t;

typedef struct
{
	NgapCause_e								cause;	
}PathSwitchReqUnsuccTransfer_t;


typedef struct
{
	UINT16     								sessId;
	PathSwitchReqUnsuccTransfer_t			pathSwitchReqUnsuccTransfer;
}PathSwitchRlsPduSessItem_t;

typedef struct
{
	UINT8                                   numAmf;
	IpAddress_t                             amfAddr[NGAP_MAX_AMF_NUM];
	BroadPlmns_t                            broadPlmn[NGAP_MAX_AMF_NUM];
}RegisterAmf_t;

typedef struct
{
	IpAddress_t				ipAddr;
	UINT8					state;
	NgapCause_e				cause;
	BroadPlmns_t			bPlmn;
}AmfRegistResult_t;
typedef struct
{
	UINT8					areaIntTaiNUm;
	Tai_t					areaIntTaiItem[ngap_maxnoofTAIinAoI];
	UINT8					areaIntCellNum;
	CuNrCgi_t				areaIntCgiItem[ngap_maxnoofCellinAoI];
	UINT8					areaIntRanNodeIdNum;
	GlobalRanNodeId_t		areaIntRanNodeIdItem[ngap_maxnoofRANNodeinAoI];
}AreaInterestItem_t;

typedef struct
{
	UINT8					areaIntItemNum;
	AreaInterestItem_t		areaIntItem[ngap_maxnoofAoI];
	UINT8					locaReportReferenceId;	
}AreaInterestListItem_t;

typedef struct
{
	EventType_e				eventType;
	ReportArea_e			reportArea;
	UINT8					areaIntListItemNum;
	AreaInterestListItem_t	areaIntListItem[ngap_maxnoofAoI];
	UINT8					locaReportReferenceIdTobeCancel;//Condition 
}LocationReportRequestType_t;

/**********************************************************************************
***********************************************************************************
*********** CUC --> NGAP                MESSAGE STRUCTURE *************************
***********************************************************************************
***********************************************************************************/

/* Register Request ( NG Setup Request )*/
typedef struct ngapRegistergNBReq
{
    Instance_t                              instance;
	PlmnId_t								plmnId;
	gNBId_t									gnbId;
	RanName_t								ranName;
	SupportTas_t							supportTa;
	PagingDRX_e								ranDefaPagDrx;
	UINT8									ueRetInfoFlag;
	UERetentionInformation_e				ueRetenInfo;
	RegisterAmf_t							registerAmfInfo;               
}NgapRegistergNBReq_t;

/* First NAS Request (Initial Ue Message)*/
#define FIRST_UL_NAS_AMF_REGISTER_PRESENT				(1 << 0)
#define FIRST_UL_NAS_FIVEG_STMSI_PRESENT        		(1 << 1)
#define FIRST_UL_NAS_LOCATION_INFO_TIMESTAMP_PRESENT	(1 << 2)
#define FIRST_UL_NAS_UE_CONTEXT_REQ_PRESENT     		(1 << 3)
typedef struct ngapFirstNasReq 
{
	UINT16									bitMask;
	NrCellId_t								nrCellId;
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    PlmnId_t                                plmnId;
	guamiType_e								guamiType;
    Guami_t                                 guami;
	/* e_RRCEstablishmentCause */
    RrcEstablishmentCause_e                 establishmentCause;
    NasPdu_t                                nasPdu;
	CuTac_t                   				tac;
	Timestamp_t								timeStamp;
    FiveGSTmsi_t                            fiveGSTmsi;
    ueContextRequest_e                      ueReq;
    SliceList_t                             ranAllowNssai;
} NgapFirstNasReq_t;

/* Ue Radio Capability Check Response */
typedef struct ngapUeRadioCapaCheckRsp
{
	Instance_t								instance;
	UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
	IMSVoiceSupportInd_e					IMSVoiceSupportInd;
}NgapUeRadioCapaCheckRsp_t;

/* UL NAS Transfer */
#define UL_NAS_LOCATION_INFO_TIMESTAMP_PRESENT	(1 << 0)
typedef struct ngapULNas 
{
	UINT16									bitMask;
	Instance_t								instance;
	NrCellId_t								nrCellId;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
    NasPdu_t                                nasPdu;
	PlmnId_t                				plmnId;
    CuTac_t                   				tac;
	Timestamp_t								timeStamp;
} NgapULNas_t;

/*Ue Radio Capability Information Indication*/
#define UE_RADIO_CAPABILITY_PAGING_PRESENT		(1 << 0)
typedef struct ngapUeRadioCapaInfoIndication
{
	UINT16									bitMask;
	Instance_t								instance;
	UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
    UeRadioCapability_t                     ueRadioCapability;
    UeRadioCapaForPag_t                     ueRadioCapabilityForPag;/* optional */
}NgapUeRadioCapaInfoIndication_t;

/* Initial Context Setup Response */
typedef struct ngapInitialContextSetupResp 
{
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64                        			ranUeNgapId;
    UINT8                                   rspFailFlag;
    NgapCause_e                             failCause;
    UINT16                                  pduSessSetRspNum;
    PduSessSetupResp_t                      pduSessSetRspItem[NG_MAX_SESSION_NUM];
    UINT16                                  pduSessSetFailNum;
    PduSessSetupFail_t                      pduSessSetFailItem[NG_MAX_SESSION_NUM];
} NgapInitialContextSetupResp_t;

/* PDU Session Resource Setup Response */
typedef struct ngapPduSessSetupRsp
{
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64                        			ranUeNgapId;
    UINT16                                  pduSessSetRspNum;
    PduSessSetupResp_t                      pduSessSetRspItem[NG_MAX_SESSION_NUM];
    UINT16                                  pduSessSetFailNum;
    PduSessSetupFail_t                      pduSessSetFailItem[NG_MAX_SESSION_NUM];
}NgapPduSessSetupRsp_t;

/* Ue Context Release Request */
typedef struct ngapUeCxtReleaseReq 
{
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
    UINT16                                  sessRlsNum;
    UINT16		                            rlsSessId[NG_MAX_SESSION_NUM];
    NgapCause_e                             cause;
} NgapUeCxtReleaseReq_t;

/* Ue Context Release Complete */
#define UE_CONTEXT_RELEASE_COMPLETE_USERLOCATION_TIMESTAMP_PRESENT	(1 << 0)
typedef struct ngapUeReleaseComplete 
{
	UINT16									bitMask;
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
	UINT8									locationFlag;
	PlmnId_t								plmnId;
	NrCellId_t								cellId;
	CuTac_t									tac;
	Timestamp_t								timeStamp;
    RecommCellforPag_t                      recomCellInfo;
    RecommRanforPag_t                       recomRanInfo;
    UINT8                                   rlsSessNum;
	PduSessResourceItem_t					sessResourceItem[NG_MAX_SESSION_NUM];	
    UINT8                                   allSessRlsFlag;
} NgapUeReleaseComplete_t;

#define HANDOVER_REQUIRED_DIRECT_FORWARDING_PATH_AVAILABILITY_PRESENT	(1 << 0)
typedef struct ngapHandoverRequired
{
	UINT16									bitMask;
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
	HandoverType_e							handoverType;
	NgapCause_e								cause;
	PlmnId_t								plmnId;
	gNBId_t									gnbId;
	Tai_t									tai;
	DirectForwardPathAvailability_e			directForwardPathAvailability;//Optional
	UINT8                                   sessNum;
	HoRequiredPduSessResourcItem_t			sessResourceItem[NG_MAX_SESSION_NUM];
}NgapHandoverRequired_t;

typedef struct ngapHandoverRequestAcknowledge
{
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
	UINT8									ackSessNum;
	HoRequestAckPduSessItem_t				HoRequestAckSessItem[NG_MAX_SESSION_NUM];
	UINT8									failSessNum;
	HoRequestFailPduSessItem_t				HoRequestFailSessItem[NG_MAX_SESSION_NUM];
}NgapHandoverRequestAcknowledge_t;
typedef struct ngapHandoverFailure
{
	Instance_t								instance;
    AmfUeNgapId_t                           amfUeNgapId;
	NgapCause_e								cause;
}NgapHandoverFailure_t;
#define HANDOVER_NOTIFY_USERLOCATION_TIMESTAMP_PRESENT			(1 << 0)
typedef struct ngapHandoverNotify
{
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
	PlmnId_t								plmnId;
	NrCellId_t								cellId;
	CuTac_t									tac;
	Timestamp_t								timeStamp;
}NgapHandoverNotify_t;
/* Handover Cancel */
typedef struct ngapHandoverCancel
{
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
	NgapCause_e								cause;
}NgapHandoverCancel_t;

/* Path Switch Request */
#define PATH_SWITCH_REQUEST_USERLOCATION_TIMESTAMP_PRESENT		(1 << 0)
typedef struct ngapPathSwitchRequest
{
	UINT16									bitMask;
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           sourceAmfUeNgapId;
	PlmnId_t								plmnId;
	NrCellId_t								cellId;
	CuTac_t									tac;
	Timestamp_t								timeStamp;
	UeSecurCapa_t							ueSecurityCapability;
	UINT8									switchSessNum;
	PathSwitchReqPduSessItem_t				switchPduSessItem[NG_MAX_SESSION_NUM];
	UINT8									setupFailSessNum;
	PathSwitchReqFailPduSessItem_t			setupFailPduSessItem[NG_MAX_SESSION_NUM];
}NgapPathSwitchRequest_t;

/* RRC Inactive Transition Report */
#define RRC_INACTIVE_TRANSITION_REPORT_USERLOCATION_TIMESTAMP_PRESENT	(1 << 0)
typedef struct ngapRrcInactiveTransitionReport
{
	Instance_t								instance;
    UINT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
	RrcState_e								rrcState;
	PlmnId_t								plmnId;
	NrCellId_t								cellId;
	CuTac_t									tac;
	Timestamp_t								timeStamp;
}NgapRrcInactiveTransitionReport_t;
/**********************************************************************************
***********************************************************************************
*************** NGAP --> CUC                 MESSAGE STRUCTURE ********************
***********************************************************************************
***********************************************************************************/
/* Register Confirm (NG Setup Response)*/
typedef struct ngapRegistergNBCnf 
{
	Instance_t								instance;
    UINT8                                   numAmf;             /* Number of AMF connected */
	AmfRegistResult_t						registRet[NGAP_MAX_AMF_NUM];
} NgapRegistergNBCnf_t;

/* Deregister Indication */
typedef struct ngapDeregisteredgNBInd_t
{
    UINT8                                   numAmf;            /* Number of AMF connected */
} NgapDeregisteredgNBInd_t;

#define UE_RADIO_CAPA_CHECK_REQ_UE_RADIO_CAPA_PRESENT		(1 << 0)
/* Ue Radio Capability Check Request */
typedef struct ngapUeRadioCapaCheckReq
{
	UINT16									bitMask;
	Instance_t								instance;
    AmfUeNgapId_t                           amfUeNgapId; 
    UINT64			                        ranUeNgapId;
    UeRadioCapability_t                     ueRadioCapability;//Optional
}NgapUeRadioCapaCheckReq_t;

/* DL NAS Transfer */
#define DL_NAS_TRANSFER_OLD_AMF_NAME_PRESENT                 (1 << 0)
#define DL_NAS_TRANSFER_RAN_PAGING_PRIORITY_PRESENT          (1 << 1)
#define DL_NAS_TRANSFER_MOBILITY_RESTRICTION_PRESENT         (1 << 2)
#define DL_NAS_TRANSFER_INDEX_TO_RFSP_PRESENT                (1 << 3)
#define DL_NAS_TRANSFER_UE_AMBR_PRESENT                      (1 << 4)
#define DL_NAS_TRANSFER_SNSSAI_PRESENT                       (1 << 5)
typedef struct ngapDLNas
{
	UINT16									bitMask;
	Instance_t								instance;
    AmfUeNgapId_t                           amfUeNgapId; 
    UINT64			                        ranUeNgapId;
    AmfName_t                               oldAmfName;
    INT64				                    ranPagPriority;
    NasPdu_t                                nasPdu;
    MobiRestrInfo_t                         mobiRestrictInfo;
    INT64		                            indexToRfsp;
    UINT64									ueAMBRDl;
	UINT64									ueAMBRUl;
    SliceList_t                             amfSlice;
}ngapDLNas_t;

/* Initial Context Setup Request */
#define INITIAL_CXT_SETUP_REQ_OLD_AMFNAME_PRESENT           				(1 << 0)
#define INITIAL_CXT_SETUP_REQ_UE_AGGREGATE_MAX_BITRATE_PRESENT				(1 << 1)
#define INITIAL_CXT_SETUP_REQ_CORE_INFO_PRESENT             				(1 << 2)
#define INITIAL_CXT_SETUP_REQ_PDU_SESSION_RESOURCE_SETUPLIST_CXTREQ_PRESENT	(1 << 3)
#define INITIAL_CXT_SETUP_REQ_TRACE_ACTIVATION_PRESENT      				(1 << 4)
#define INITIAL_CXT_SETUP_REQ_MOBI_RESTRICT_PRESENT         				(1 << 5)
#define INITIAL_CXT_SETUP_REQ_UE_RADIO_CAPA_PRESENT         				(1 << 6)
#define INITIAL_CXT_SETUP_REQ_IDX_RFSP_PRESENT              				(1 << 7)
#define INITIAL_CXT_SETUP_REQ_MASK_IMEISV_PRESENT           				(1 << 8)
#define INITIAL_CXT_SETUP_REQ_NASPDU_PRESENT                				(1 << 9)
#define INITIAL_CXT_SETUP_REQ_EMERGENCY_FB_PRESENT          				(1 << 10)
#define INITIAL_CXT_SETUP_REQ_INACT_TRANS_RPT_REQ_PRESENT   				(1 << 11)
#define INITIAL_CXT_SETUP_REQ_RADIO_CAPA_FOR_PAG_PRESENT    				(1 << 12)
#define INITIAL_CXT_SETUP_REQ_REDIRECTION_FOR_VOICE_EPS_FB_PRESENT    		(1 << 13)
typedef struct ngapInitialContextSetupReq
{
	UINT16									bitMask;
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64			                        ranUeNgapId;
    AmfName_t                               oldAmfName;//Optional
    NgapUeAmber_t				            ueAMBR;//Optional
    CoreAssitInfo_t                         coreNetAssistInfo;//Optional
    Guami_t                                 guami;
    UINT16                                  pduSessSetupNum;
    PduSessionSetupReq_t                    pduSessSetReqItem[NG_MAX_SESSION_NUM];
    SliceList_t                             amfSlice;
    UeSecurCapa_t                           ueSecurityCapa;
    SecuKey_t                               securityKey;
    TraceActiv_t                            traceActivation;//Optional
    MobiRestrInfo_t                         mobiRestrictInfo;//Optional
    UeRadioCapability_t                     ueRadioCapability;//Optional
    INT64		                            indexToRfsp;//Optional
    MaskedImeiSv_t                          maskedImeisv;//Optional
    NasPdu_t                                nasPdu;//Optional
    EmergFbInd_t                            emergencyFallbackIndicator;//Optional
    INT64								    rrcInactiveTransitionReportRequest;//Optional
    UeRadioCapaForPag_t                     ueRadioCapabilityForPag;//Optional
	INT64									redirectVoiceFb;//Optional
}NgapInitialContextSetupReq_t;

/* PDU Session Resource Setup Request */
#define PDU_SESS_SETUP_REQ_RAN_PAGING_PRIORITY_PRESENT			(1 << 0)
#define PDU_SESS_SETUP_REQ_NAS_PDU_PRESENT						(1 << 1)
#define PDU_SESS_SETUP_REQ_UE_AMBR_PRESENT						(1 << 2)

typedef struct ngapPduSessSetupReq
{
	UINT16 									bitMask;
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64			                        ranUeNgapId;
    INT64				                    ranPagPriority;//Optional
	NasPdu_t								nasPdu;//Optional
	UINT16                                  pduSessSetupNum;
    PduSessionSetupReq_t                    pduSessSetReqItem[NG_MAX_SESSION_NUM];
	UINT64									ueAMBRDl;//Optional
	UINT64									ueAMBRUl;//Optional
}NgapPduSessSetupReq_t;

/* Ue Context Release Command */
typedef struct ngapUeReleaseCommand
{
	/* UE_NGAP_IDs_PR */
	Instance_t								instance;
	NgapIdType_e							ngapIdType;						
    INT64			                        ranUeNgapId;
    AmfUeNgapId_t                           amfUeNgapId;
    NgapCause_e                             cause;
}NgapUeReleaseCommand_t; 

/* Handover Command */
#define HANDOVER_COMMAND_NAS_SECURITY_PARAM_FROM_NGRAN_PRESENT	(1 << 0)
typedef struct ngapHandoverCommand
{
	UINT16 									bitMask;
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64			                        ranUeNgapId;
	HandoverType_e							handoverType;
	UINT8                                   HoSessNum;
	HoCmdSuccPduSessResourceItem_t			HoSessResourceItem[NG_MAX_SESSION_NUM];
	UINT8                                   rlsSessNum;
	HoCmdFailPduSessResourcItem_t			rlsSessResourceItem[NG_MAX_SESSION_NUM];
}NgapHandoverCommand_t;

/* Handover Preparation Failure*/
typedef struct ngapHandoverPreparationFailure
{
	UINT16 									bitMask;
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64			                        ranUeNgapId;
	NgapCause_e								cause;
}NgapHandoverPreparationFailure_t;

/* Handover Request */
#define HANDOVER_REQUEST_CORE_ASSIST_INFO_PRESENT					(1 << 0)
#define HANDOVER_REQUEST_NEW_SECURITY_CTX_IND_PRESENT				(1 << 1)
#define HANDOVER_REQUEST_TRACE_ACTIVATION_PRESENT					(1 << 2)
#define HANDOVER_REQUEST_MASKED_IMEISV_PRESENT						(1 << 3)
#define HANDOVER_REQUEST_MOBILITY_RESTRICTION_INFO_PRESENT			(1 << 4)
#define	HANDOVER_REQUEST_LOCATION_REPORT_REQUEST_TYPE_PRESENT		(1 << 5)
#define HANDOVER_REQUEST_RRC_INACTIVE_TRANS_REPORT_REQUEST_PRESNET 	(1 << 6)
#define HANDOVER_REQUEST_REDIRECT_VOICE_FB_PRESNET					(1 << 7)	
typedef struct ngapHandoverRequest
{
	UINT16 									bitMask;
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
	HandoverType_e							handoverType;
	NgapCause_e								cause;
    NgapUeAmber_t				            ueAMBR;
    CoreAssitInfo_t                         coreNetAssistInfo;//Optional
    UeSecurCapa_t							ueSecurityCapability;
	SecurityCtx_t							securityContext;
	NewSecurityCtxInd_e						newSecurityContextInd;//Optional
	NasPdu_t								NASC;
	UINT8									sessNum;
	HoRequestPduSessResourceItem_t			HoRequestSessResourceItem[NG_MAX_SESSION_NUM];
    SliceList_t                             amfSlice;
    TraceActiv_t                            traceActivation;//Optional
    MaskedImeiSv_t                          maskedImeisv;//Optional
    MobiRestrInfo_t                         mobiRestrictInfo;//Optional
    LocationReportRequestType_t				locaReportReqType;//Optional
    INT64								    rrcInactiveTransitionReportRequest;//Optional
    Guami_t									guami;
	INT64									redirectVoiceFb;//Optional
}NgapHandoverRequest_t;

/* Handover Cancel Acknowledge */
typedef struct ngapHandoverCancelAcknowledge
{
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64			                        ranUeNgapId;
}NgapHandoverCancelAcknowledge_t;

/* Paging */
#define PAGING_PAGING_DRX_PRESENT 						(1 << 0)
#define PAGING_PAGING_PRIORITY_PRESENT 					(1 << 1)
#define PAGING_UE_RADIO_CAPABILITY_FOR_PAGING_PRESENT 	(1 << 2)
#define PAGING_PAGING_ORIGIN_PRESENT 					(1 << 3)
#define PAGING_ASSIST_DATA_FOR_PAGING 					(1 << 4)
typedef struct ngapPaging
{
	FiveGSTmsi_t							fiveGSTmsi;
	PagingDRX_e								pagingDrx;//Optional
	UINT8									taiForPagingNum;
	Tai_t									taiForPagingItem[ngap_maxnoofTAIforPaging];
	PagingPriority_e						pagingPriority;//Optional
	UeRadioCapaForPag_t						ueRadioCapabilityForPaging;//Optional
	PagingOrigin_e							pagingOrigin;//Optional
	AssistDataForPaging_t					assistDataForPaging;//Optional
}NgapPaging_t;

/* Path Switch Request Acknowledge */
#define PATH_SWITCH_REQUEST_ACK_UE_SECURITY_CAPABILITY_PRESENT					(1 << 0)
#define PATH_SWITCH_REQUEST_ACK_NEW_SECURITY_CTX_IND_PRESENT					(1 << 1)
#define	PATH_SWITCH_REQUEST_ACK_CORE_NETWORK_ASSIST_INFO_PRESENT				(1 << 2)
#define PATH_SWITCH_REQUEST_ACK_RRC_INACTIVE_TRANSITION_REPORT_REQUEST_PRESENT	(1 << 3)
#define	PATH_SWITCH_REQUEST_ACK_REDIRECT_VOICE_FB_PRESENT						(1 << 4)
typedef struct ngapPathSwitchRequestAcknowledge
{
	UINT16 									bitMask;
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64			                        ranUeNgapId;
	UeSecurCapa_t							ueSecurityCapability;//optional
	SecurityCtx_t							securityContext;
	NewSecurityCtxInd_e						newSecurCtxInd;//optional
	UINT8									switchSessNum;
	PathSwitchReqAckPduSessItem_t			switchPduSessItem[NG_MAX_SESSION_NUM];
	UINT8									rlsSessNum;
	PathSwitchRlsPduSessItem_t				rlsPduSessItem[NG_MAX_SESSION_NUM];
	UINT8									SNssaiNum;
	SNssai_t								SNssaiItem[ngap_maxnoofAllowedS_NSSAIs];
	CoreAssitInfo_t							coreNetworkAssitInfo;//optional
    INT64								    rrcInactiveTransitionReportRequest;//Optional
	INT64									redirectVoiceFb;//Optional
}NgapPathSwitchRequestAcknowledge_t;

/* Path Switch Request Failure */
typedef struct ngapPathSwitchRequestFailure
{
	Instance_t								instance;
	AmfUeNgapId_t                           amfUeNgapId;
    UINT64			                        ranUeNgapId;
	UINT8									rlsSessNum;
	PathSwitchRlsPduSessItem_t				rlsPduSessItem[NG_MAX_SESSION_NUM];				
}NgapPathSwitchRequestFailure_t;
/**********************************************************************************
***********************************************************************************
***************** CUC <--> E1AP               ACCORDING TO STRUCTURE **************
***********************************************************************************
***********************************************************************************/
#define MAX_LENGTH_GNBCUCP_NAME         150

typedef struct  gnbCucpName
{
    char                                    gnbCucpName[MAX_LENGTH_GNBCUCP_NAME];
}GnbCucpName_t;

#define SECURITY_ALGORITHM_INTERGRITY_PROTECTION_ALGORITHM	    (1 << 0)
typedef struct
{
	UINT16								    bitMask;
	CipAlgorithm_e	                		cipheringAlgorithm;
	IpAlgorithm_e		    				integrityProtectionAlgorithm	;/* OPTIONAL */
}SecuAlgorithm_t;

typedef struct
{
	UINT32					                size;
	UINT8					                buffer[MAX_SIZE_OF_OCTET_STRING];
}EncrypTionKey_t;

typedef struct
{
	UINT32					                size;
	UINT8					                buffer[MAX_SIZE_OF_OCTET_STRING];
}IntegrityProtectKey_t;

#define USER_PLANE_SECURITY_KEY_INTERGRITYPROTECTIONKEY_PRESENT	    (1 << 0)
typedef struct
{
	UINT16								    bitMask;
	EncrypTionKey_t		                    encryptionKey;
	IntegrityProtectKey_t	        		integrityProtectionKey;/* OPTIONAL */
}UpSecuritykey_t;

typedef struct
{
    SecuAlgorithm_t			  	            secuAlgorithm;
	UpSecuritykey_t  				    	upSecukey;
}SecuInfo_t;

#define GBR_QOS_FLOW_INFO_MAX_PACKET_LOSSRATE_DOWNLINK_PRESENT			(1 << 0)
#define GBR_QOS_FLOW_INFO_MAX_PACKET_LOSSRATE_UPLINK_PRESENT		    (1 << 1)
typedef struct gbrQoSFlowInformation 
{
    UINT16								    bitMask;
    UINT64	                            	maxFlowBitRateDownlink;
	UINT64	                            	maxFlowBitRateUplink;
	UINT64	                            	guaranteedFlowBitRateDownlink;
	UINT64	                            	guaranteedFlowBitRateUplink;
	UINT64	                                maxPacketLossRateDownlink;/* OPTIONAL */
	UINT64	                                maxPacketLossRateUplink;/* OPTIONAL */
} GBRQoSFlowInformation_t;

#define QOS_FLOW_LEVEL_PARA_GBR_QOS_FLOW_INFO_PRESENT           (1 << 0)
#define QOS_FLOW_LEVEL_PARA_REFLECTIVE_QOS_ATTRIBUTE_PRESENT    (1 << 1)
#define QOS_FLOW_LEVEL_PARA_ADDITIONAL_QOS_FLOW_INFO_PRESENT    (1 << 2)
#define QOS_FLOW_LEVEL_PARA_PAGING_POLICY_INDICATOR_PRESENT     (1 << 3)
#define QOS_FLOW_LEVEL_PARA_RDI_PRESENT		                    (1 << 4)
typedef struct
{
    UINT16								    bitMask;
	/* QoS_Characteristics_PR */
	QosCharact_t							qosCharacter;
    AllocAndRetenPriority_t		            ngRanAllAndRetentionPriority;
    GBRQoSFlowInformation_t                 gbrQoSFlowInformation;/* OPTIONAL */ 
	/* e_ReflectiveQosAttribute */
    ReflectiveQosAttribute_e	            reflectiveQosAttribute;/* OPTIONAL */ 
	/* e_AdditionalQosFlowInformation */
    AddQosFlowInfo_e          				addiQosFlowInfo;/* OPTIONAL */
	INT64									pagingPolicyInd;/* OPTIONAL */
	RDI_e									rDI;/* OPTIONAL */
}QosFlowLevelQosPar_t;

#define QOS_FLOW_QOS_ITEM_QOS_FLOW_MAP_INDICATION_PRESENT	(1 << 0)
typedef struct
{
    UINT16								    bitMask;
    INT64	                   				qosFlowIdentifier;
    QosFlowLevelQosPar_t                    qosFlowLevelQosPar;
	/* e_QoS_Flow_Mapping_Indication */
	QosFlowMapInd_e						qosFlowMapInd;/* OPTIONAL */
}QoSFlowQosItem_t;

#define QOS_FLOW_ITEM_QOS_FLOW_MAP_INDICATION_PRESENT	(1 << 0)
typedef struct qoSFlowItem
{
	long                   				    qosFlowIdentifier;
}QoSFlowItem_t;

typedef struct qosFlowList
{
    UINT8                                   qosFlowItemNum;
    QoSFlowItem_t 	                        qosFlowItem[e1ap_maxnoofQoSFlows];
}QoSFlowList_t;

typedef struct qosFlowMap
{
	UINT8									qosFlowNum;
    INT64									qfi;
	UINT8									qosFlowMapFlag;
	/* e_QoS_Flow_Mapping_Indication */
	QosFlowMapInd_e							qosFlowMapInd;
}QosFlowMap_t;

#define QOS_FLOW_MAP_IND_PRESENT	(1 << 0)
typedef struct qosFlowMapItem
{
    UINT16								    bitMask;
    UINT8									qosFlowIdentifier;
	QosFlowMapInd_e							qosFlowMappingInd;/* OPTIONAL */
}QosFlowMapItem_t;

typedef struct qosFlowMapList
{
	UINT8                                   qosFlowMapItemNum;
    QosFlowMapItem_t         				qosFlowMapItem[e1ap_maxnoofQoSFlows];
}QosFlowMapList_t;

#define DATA_FORWARDIGN_INFO_REQ_QOS_FLOWS_FORWARD_TUNNELS_PRESENT	(1 << 0)
typedef struct
{
	UINT16								    bitMask;
	/* e_Data_Forwarding_Request */
    DataForwardReq_e						dataForwardingRequest;
	QosFlowMapList_t						qosFlowForwardTunnelList;/* OPTIONAL */
}DFIRequest_t;

#define CELL_GROUP_ITEM_UL_CONFIGURATION_PRESENT		(1 << 0)
#define CELL_GROUP_ITEM_DL_TX_STOP_PRESENT				(1 << 1)
#define CELL_GROUP_ITEM_RAT_TYPE_PRESENT				(1 << 2)
typedef struct cellGroupItem
{
    UINT16								    bitMask;
    INT64	                        		cellGroupID;
	/* e_UL_Configuration */
    UlConfig_e				            	ulConfig;/* OPTIONAL */
	/* e_DL_TX_Stop */
    DlTXStop_e								dlTxStop;/* OPTIONAL */
	/* e_RAT_Type */
    RatType_e	 							ratType;/* OPTIONAL */
}CellGroupItem_t;

typedef struct cellGroupInformation
{
    UINT8                                   cellGroupNum;
    CellGroupItem_t                         cellGroupItem[e1ap_maxnoofCellGroups];
}CellGroupInformation_t;

typedef struct flowMappingInformation
{
	QoSFlowList_t							qosFlowList;
}FlowMappingInformation_t;

#define ROHC_CONTINUE_ROHC_PRESENT				(1 << 0)
typedef struct
{
	UINT16									bitMask;
	INT64									maxCid;
	INT64									rohcProfiles;
	/* e_ROHC__continueROHC */
	RohcContinueRohc_e					continueRohc;/* OPTIONAL */
}Rohc_t;

typedef struct
{
	/* ROHC_Parameters_PR */
	RohcParaPR_e							rohcType;
	Rohc_t									rohc;
	Rohc_t									ulOnlyRohc;
}RohcPara_t;

#define PDCP_CONFIGURATION_ROHC_PARA_PRESENT				(1 << 0)
#define PDCP_CONFIGURATION_REORDERING_TIMER_PRESENT     	(1 << 1)
#define PDCP_CONFIGURATION_DISCARD_TIMER_PRESENT			(1 << 2)
#define PDCP_CONFIGURATION_UL_DATA_SPLIT_THRESHOLD_PRESENT	(1 << 3)
#define PDCP_CONFIGURATION_PDCP_DUPLICATION_PRESENT     	(1 << 4)
#define PDCP_CONFIGURATION_PDCP_REESTABLISHMENT_PRESENT		(1 << 5)
#define PDCP_CONFIGURATION_PDCP_DATA_RECOVERY_PRESENT		(1 << 6)
#define PDCP_CONFIGURATION_DUPLICATION_ACTIVATION_PRESENT   (1 << 7)
#define PDCP_CONFIGURATION_OUT_OF_ORDER_DELIVERY_PRESENT	(1 << 8)
typedef struct pdcpConfiguration
{
	UINT16									bitMask;
	/* e_PDCP_SN_Size */
	PdcpSNSize_e							pdcpSNSizeUl;
	PdcpSNSize_e							pdcpSNSizeDl;
	/* e_RLC_Mode */
	CuRlcMode_e								rlcMode;
	RohcPara_t								rohcPara;/* OPTIONAL */
	/* e_T_Reordering */
	TReordering_e							reorderTimer;/* OPTIONAL */
	/* e_DiscardTimer */
	DiscardTimer_e							discadTimer;/* OPTIONAL */
	/* e_ULDataSplitThreshold */
	UlDataSplitThreshold_e					ulDataSplitThreshold;/* OPTIONAL */
    /* e_PDCP_Duplication */
	PdcpDuplication_e						pdcpDuplication;/* OPTIONAL */
	/* e_PDCP_Reestablishment */
    PdcpReestablishment_e				    pdcpReestablishment;/* OPTIONAL */
    /* e_PDCP_DataRecovery */
	PdcpDataRecovery_e						pdcpDataRecovery;/* OPTIONAL */
	/* e_Duplication_Activation */
	DuplicationActivation_e					duplicationAct;/* OPTIONAL */
	/* e_OutOfOrderDelivery */
	OutOfOrderDelivery_e					outofOrderDelivery;/* OPTIONAL */
}PDCPConfiguration_t;

typedef struct
{
	/* e_DefaultDRB */
	DefaultDRB_e							defaultDrbInd;
	/* e_SDAP_Header_UL */
	SdapHeader_e							sdapUlHeaderInd;
	/* e_SDAP_Header_DL */
	SdapHeader_e							sdapDlHeaderInd;
}SdapCfg_t;

typedef struct
{
	UINT8									qosFlowNum;
	QoSFlowQosItem_t						qosFlowInfo[e1ap_maxnoofQoSFlows];
}QosFlowQosPara_t;

typedef struct
{
	INT64									pdcpSN;
	UINT64									hFN;
}PdcpCount_t;

#define PDCP_SN_STATUS_INFORMATION_RECEIVE_PDCP_SDU_STATUSPRESENT		(1 << 0)	
typedef struct
{    
	UINT16									bitMask;
    UINT64									receivePdcpSDUBitNum;/* OPTIONAL */
	UINT64									receiveStatusofPdcpSDU[2048]; /*Length: 1 - 131072 */
	PdcpCount_t								ulCountValue;
}PdcpUlStatusInfo_t;

typedef struct
{
	PdcpCount_t								dlCountValue;
}PdcpDlStatusInfo_t;

typedef struct
{
    PdcpUlStatusInfo_t                      pdcpUlStatusInfo;
	PdcpDlStatusInfo_t		                pdcpDlStatusInfo;
}PdcpSNStatusInfo_t;

#define DRB_TO_SETUP_ITEM_DRB_DFI_REQUEST_PRESENT			(1 << 0)
#define DRB_TO_SETUP_ITEM_DRB_INACTIVITY_TIMER_PRESENT		(1 << 1)
#define DRB_TO_SETUP_ITEM_PDCP_SN_STATUS_INFO_PRESENT		(1 << 2)
typedef struct drbToSetupItem
{
	UINT16								    bitMask;
	UINT8	                            	drbID;
	SdapCfg_t								sdapConfig;
	PDCPConfiguration_t	                    pdcpConfig;
	CellGroupInformation_t                  cellGroupInfo;
	QosFlowQosPara_t						qosFlowSetup;
	DFIRequest_t							drbDataForwardInfoReq;/* OPTIONAL */
	INT64			     					inactivityTimer;/* OPTIONAL */
	PdcpSNStatusInfo_t						pdcpSNStatusInfo;/* OPTIONAL */
}DRBToSetupItem_t;

typedef struct drbToSetupList
{
	UINT8                                   drbToSetupListNum;
    DRBToSetupItem_t 	                    drbToSetupItem[e1ap_maxnoofDRBs];
}DRBToSetupList_t;

#define PDU_SESSION_RESOURCE_SETUP_DL_AMBR_PRESENT           			(1 << 0)
#define PDU_SESSION_RESOURCE_SETUP_DATA_FORWARD_INFORMATION_REQ_PRESENT	(1 << 1)
#define PDU_SESSION_RESOURCE_SETUP_INACTIVITY_TIMER_PRESENT				(1 << 2)
#define PDU_SESSION_RESOURCE_SETUP_DL_UP_TRANSPORT_LAYER_INFO_PRESENT	(1 << 3)
#define PDU_SESSION_RESOURCE_SETUP_NETWORK_INSTANCE_PRESENT				(1 << 4)
typedef struct pduSessionResourceToSetupItem
{
	UINT16								    bitMask;
	UINT16	 								pduSessionId;
	PduSessType_e	 			        	pduSessionType;
	SNssai_t	 							snssai;
	SecuInd_t				                securityIndication;
	UINT64	 								pduSessionResourceDlAMBR;/* OPTIONAL */
    UpTransLayerInfo_t                      ulUpTNLInformation;
    DFIRequest_t			                dataForwardInfoReq;/* OPTIONAL */
	INT64			     					inactTimer;/* OPTIONAL */
	UpTransLayerInfo_t						existAllocateNgDlUpTnlInfo;/* OPTIONAL */
	INT64									networkInstance;/* OPTIONAL */
    DRBToSetupList_t						drbToSetupList;
}PduSessionResourceToSetupItem_t;

typedef struct pduSessionResourceToSetupList
{
    UINT8                                   sessNum;
    PduSessionResourceToSetupItem_t         pduSessionResourceToSetupItem[e1ap_maxnoofPDUSessionResource];
}PduSessionResourceToSetupList_t;

typedef struct upParametersItem
{
    UpTransLayerInfo_t                       upTransLayerInfo;
    INT64			                         cellGroupID;
} UPParametersItem_t;

typedef struct upParametersList
{
    UINT8                                    upParaNum;
    UPParametersItem_t                       upParametersItem[e1ap_maxnoofUPParameters];
} UPParametersList_t;

#define DATA_FORWARDIGN_INFO_RSP_UL_DATA_FORWARD_PRESENT	(1 << 0)
#define DATA_FORWARDIGN_INFO_RSP_DL_DATA_FORWARD_PRESENT	(1 << 1)
typedef struct dFIResponse
{
	UINT16									 bitMask;
	UpTransLayerInfo_t                       ulDataForwarding;/*optional*/
	UpTransLayerInfo_t                       dlDataForwarding;/*optional*/
} DFIResponse_t; 

#define DRB_TO_MODIFY_ITEM_SDAP_CONFIG_PRESENT						(1 << 0)
#define DRB_TO_MODIFY_ITEM_PDCP_CONFIG_PRESENT						(1 << 1)
#define DRB_TO_MODIFY_ITEM_DRB_DATA_FORWARD_INFO_RSP_PRESENT		(1 << 2)
#define DRB_TO_MODIFY_ITEM_PDCP_SN_STATUS_REQ_PRESENT				(1 << 3)
#define DRB_TO_MODIFY_ITEM_PDCP_SN_STATUS_INFO_PRESENT				(1 << 4)
#define DRB_TO_MODIFY_ITEM_DL_UP_PARA_PRESENT						(1 << 5)
#define DRB_TO_MODIFY_ITEM_CELL_GROUP_TO_ADD_PRESENT				(1 << 6)
#define DRB_TO_MODIFY_ITEM_CELL_GROUP_TO_MODIFY_PRESENT				(1 << 7)
#define DRB_TO_MODIFY_ITEM_CELL_GROUP_TO_REMOVE_PRESENT				(1 << 8)
#define DRB_TO_MODIFY_ITEM_FLOW_MAPPING_INFO_PRESENT				(1 << 9)
#define DRB_TO_MODIFY_ITEM_DRB_INACTIVITY_TIMER_PRESENT				(1 << 10)
typedef struct drbToModifyItem
{
	UINT16								    bitMask;
	UINT8	                            	drb_ID;
	SdapCfg_t								sdapConfig;/* OPTIONAL */
	PDCPConfiguration_t	                    pdcpConfig;/* OPTIONAL */
	DFIResponse_t							drbDataForwardInfoRsp;/* OPTIONAL */
	PdcpSNStatusRequest_e					pdcpSNStatusReq;/* OPTIONAL */
	PdcpSNStatusInfo_t						pdcpSNStatusInfo;/* OPTIONAL */
	UPParametersList_t                      dlUPParameters;/* OPTIONAL */
	CellGroupInformation_t                  cellGroupToAdd;/* OPTIONAL */
    CellGroupInformation_t                  cellGroupToModify;/* OPTIONAL */
    CellGroupInformation_t                  cellGroupToRemove;/* OPTIONAL */
	QosFlowQosPara_t						flowMappingInfo;/* OPTIONAL */
	INT64                      				drbInactTimer;/* OPTIONAL */
}DRBToModifyItem_t;

typedef struct drbToModifyList
{
	UINT8                                   drbToModifyItemNum;
    DRBToModifyItem_t						drbToModifyItem[e1ap_maxnoofDRBs];
}DRBToModifyList_t;

typedef struct drbToRemoveItem
{
    UINT8			                    	drb_ID;
}DRBToRemoveItem_t;

typedef struct drbToRemoveList
{
	UINT8                                   drbToRemovetemNum;
    DRBToRemoveItem_t						drbToRemoveItem[e1ap_maxnoofDRBs];
}DRBToRemoveList_t;

#define PDU_SESSION_RESOURCE_TO_MODIFY_SECURITY_INDICATION_PRESENT          		(1 << 0)
#define PDU_SESSION_RESOURCE_TO_MODIFY_DL_AMBR_PRESENT           					(1 << 1)
#define PDU_SESSION_RESOURCE_TO_MODIFY_UL_UP_TNL_INFO_PRESENT           			(1 << 2)
#define PDU_SESSION_RESOURCE_TO_MODIFY_DATA_FORWARD_INFORMATION_REQ_PRESENT			(1 << 3)
#define PDU_SESSION_RESOURCE_TO_MODIFY_DATA_FORWARD_INFORMATION_RSP_PRESENT			(1 << 4)
#define PDU_SESSION_RESOURCE_TO_MODIFY_INACTIVITY_TIMER_PRESENT						(1 << 5)
#define PDU_SESSION_RESOURCE_TO_MODIFY_NETWORK_INSTANCE_PRESENT						(1 << 6)
#define PDU_SESSION_RESOURCE_TO_MODIFY_DRB_TO_SETUP_LIST_PRESENT					(1 << 7)
#define PDU_SESSION_RESOURCE_TO_MODIFY_DRB_TO_MODIFY_LIST_PRESENT					(1 << 8)
#define PDU_SESSION_RESOURCE_TO_MODIFY_DRB_TO_REMOVE_LIST_PRESENT					(1 << 9)
typedef struct pduSessionResourceToModifyItem
{
	UINT16									bitmask;
	UINT8									pduSessionId;
	SecuInd_t								secuIndi;/* OPTIONAL */
	UINT64									pduSessionResourceDlAMBR;/* OPTIONAL */
	UpTransLayerInfo_t                      ngUlUpTnlInfo;/* OPTIONAL */
	DFIRequest_t			                pduSessionDataForwardInfoReq;/* OPTIONAL */
	DFIResponse_t			                pduSessionDataForwardInfoRsp;/* OPTIONAL */
	INT64									pduSessionInactTimer;/* OPTIONAL */
	INT64									networkInstance;/* OPTIONAL */
	DRBToSetupList_t						drbToSetupList;/* OPTIONAL */
	DRBToModifyList_t						drbToModifyList;/* OPTIONAL */
	DRBToRemoveList_t						drbToRemoveList;/* OPTIONAL */
}PduSessionResourceToModifyItem_t;

typedef struct pduSessionResourceToModifylist
{
    UINT8                                   pduSessionResourceToModifyItemNum;
    PduSessionResourceToModifyItem_t 	    pduSessionResourceToModifyItem[e1ap_maxnoofPDUSessionResource];
}PduSessionResourceToModifyList_t;

typedef struct cellGroupList
{
    UINT8                                   numCellGroupItem;
    CellGroupItem_t						    cellGroupItem[e1ap_maxnoofCellGroups];
}CellGroupList_t;

typedef struct pduSessionResourceToRemoveItem
{
	UINT16				        pduSessionID;
}PduSessionResourceToRemoveItem_t;

typedef struct pduSessionResourceToRemoveList
{
    UINT8                                   pduSessionResourceToRemoveItemNum;
    PduSessionResourceToRemoveItem_t 	    pduSessionResourceToRemoveItem[e1ap_maxnoofPDUSessionResource];
}PduSessionResourceToRemoveList_t;

typedef struct ieCriticalityDiagnostics
{
	Criticality_e			 				 ieCriticality;
	E1apProtocolIeId_e                     	 protocolIEId; 
	ErrorType_e						         typeOfError;
}E1IECriticalityDiagnostics_t;

#define    PROCEDURE_CODE_PRESENT          		(1 << 0) 
#define    TRIGGER_MESSAGE_TYPE_PRESENT         (1 << 1) 
#define    PROCDURE_CRITICALITY_PRESENT         (1 << 2) 
#define    TRANSACTION_ID_PRESENT               (1 << 3) 
#define    IE_CRITICALITY_DIAGNOSTICS_PRESENT   (1 << 4) 
typedef struct criticalitydiagnostics
{
    UINT16                                   bitMask;
    E1apProcCode_e	 			             procedureCode;/* OPTIONAL */
	TriggerMsg_e	  				    	 typeOfMessage;/* OPTIONAL */
	Criticality_e							 criticality;/* OPTIONAL */
	INT64								     transactionID;/* OPTIONAL */
    UINT8                                    IECriticalityDiagnosticsNum;/* OPTIONAL */
	E1IECriticalityDiagnostics_t		     ieCriticalityDiagnostics[e1ap_maxnoofErrors];/* OPTIONAL */
}E1Criticalitydiagnostics_t;

typedef struct e1apCause
{
	E1apCausePr_e	present;
	union E1apCause_u 
	{
		E1apCauseRadioNetwork_e	 	e1apRadioNetwork;
		E1apCauseTransport_e	 	e1apTransport;
		E1apCauseProtocol_e	 	 	e1apProtocol;
		E1apCauseMisc_e	 		 	e1apMisc;
	} choice;
} E1apCause_t;

#define    PART_E1_INTERFACE_GNBCUCPUEID_PRESENT         (1 << 0) 
#define    PART_E1_INTERFACE_GNBCUUPUEID_PRESENT         (1 << 1) 

typedef struct partE1InterfaceItem
{
    UINT16                                   bitMask;
    UINT32                   				 gnbCucpUeE1apId;/*optional*/
    UINT32                   				 gnbCuupUeE1apId;/*optional*/
}PartE1InterfaceItem_t;

typedef struct partE1InterfaceList
{
    UINT8                                    PartE1InterfaceListNum;
	PartE1InterfaceItem_t		             partE1InterfaceItem[e1ap_maxnoofIndividualE1ConnectionsToReset];
}PartE1InterfaceList_t;

typedef struct e1apResetType
{
	E1apResetPr_e	present;
	union E1apReset_u 
	{
		INT64                       resetAll;
        PartE1InterfaceList_t       PartE1InterfaceList;
	} choice;
} E1apResetType_t;

/**********************************************************************************
***********************************************************************************
***************** CUC <--> E1AP                MESSAGE STRUCTURE ******************
***********************************************************************************
***********************************************************************************/
typedef struct ifmCucpE1apReset
{
    UINT64                                  transactionId;
    E1apCause_t                             cause;
    E1apResetType_t                         e1apResetType;
} IfmCucpE1apReset_t;

#define CUUPE1APRESETACKPARTE1INTERFACE                     (1 << 0)
#define CUUPE1APRESETACKCRITICALDIAGNOSTICS                 (1 << 1)

typedef struct ifmE1apResetAck
{
    UINT16                                  bitMask;
    UINT64                                  transactionId;
    PartE1InterfaceList_t                   PartE1InterfaceList;/*optional*/   
    E1Criticalitydiagnostics_t              criticalDiagnostics;/*optional*/
} IfmE1apResetAck_t;

#define CUCP_E1AP_SETUP_REQ_GNB_CUCP_NAME_CHOSEN_PRESENT        (1 << 0)
typedef struct ifmCucpE1apSetupReq
{
    UINT16                                  bitMask;
    UINT64                                  transactionId;
    GnbCucpName_t                           gnbCucpName;/*optional*/
} IfmCucpE1apSetupReq_t;

#define CUUPE1APSETUPRSPGNBCUCPNAMECHOSEN                       (1 << 0)
typedef struct ifmCuupE1apSetupRsp
{
    UINT16                                  bitMask;
    UINT64                                  transactionId;
    GnbCucpName_t                           gnbCucpName;/*optional*/
} IfmCuupE1apSetupRsp_t;

#define CUUPE1APSETUPFAILURETIMETOWAIT                          (1 << 0)
#define CUUPE1APSETUPFAILURECRITICALDIAGNOSTICS                 (1 << 1)
typedef struct ifmCuupE1apSetupFailure
{
    UINT16                                  bitMask;
    long                                    transactionId;
    E1apCause_t                             cause;
    TimeToWait_e                            timeToWait;/*optional*/
    E1Criticalitydiagnostics_t              criticalDiagnostics;/*optional*/
} IfmCuupE1apSetupFailure_t;

typedef struct e1apReleaseReq
{
    INT64			                         transactionId;
    E1apCause_t                              cause;
} E1apReleaseReq_t;

#define BEARER_CONTEXT_SETUP_UE_DL_MAX_IPDR_PRESENT					(1 << 0)
#define BEARER_CONTEXT_SETUP_UE_INACTIVITY_TIMER_PRESENT    		(1 << 1)
#define BEARER_CONTEXT_SETUP_BEARER_CONTEXT_STATUS_CHANGE_PRESENT   (1 << 2)
typedef struct e1apBearerContextSetupReq
{
    UINT16									bitMask;
	NrCellId_t								cellId;
	UINT32									cucpUeE1apId;
    SecuInfo_t               				secuInfo;
	UINT64									ueDlAMBR;
	UINT64									ueDlMaxIPDR;/*optional*/
    PlmnId_t                                servPlmnId;
	/* e_ActivityNotificationLevel */
    ActNotiLevel_e							actNotiLevel;	
	/* Inactivity_Timer_t */
    INT64                      				inactTimer;/*optional*/
	/* e_BearerContextStatusChange */
    BearCxtStatusChange_e					bearerCxtStatusChg;/*optional*/
    PduSessionResourceToSetupList_t         pduSessionResourceToSetupList;
} E1apBearerContextSetupReq_t;

#define DRB_TO_SETUP_MOD_ITEM_DRB_DATA_FORWARD_INFO_REQ_PRESENT			(1 << 0)
#define DRB_TO_SETUP_MOD_ITEM_DRB_INACTIVITY_TIMER_PRESENT				(1 << 1)
#define DRB_TO_SETUP_MOD_ITEM_PDCP_UL_COUNT_PRESENT						(1 << 2)
#define DRB_TO_SETUP_MOD_ITEM_PDCP_DL_COUNT_PRESENT						(1 << 3)
typedef struct drbToSetupModItem
{
	UINT16								    bitMask;
	UINT8	                            	drbID;
	SdapCfg_t								sdapConfig;
	PDCPConfiguration_t	                    pdcpConfig;
	CellGroupInformation_t                  cellGroupInfo;
	QosFlowQosPara_t						flowMappingInfo;
	DFIRequest_t							drbDataForwardInfoReq;/* OPTIONAL */
	INT64     								drbInactTimer;/* OPTIONAL */
	PdcpCount_t								pdcpUlCnt;/* OPTIONAL */
	PdcpCount_t								pdcpDlCnt;/* OPTIONAL */
}DrbToSetupModItem_t;

typedef struct drbToSetupModList
{
	UINT8                                   drbToSetupModListNum;
    DrbToSetupModItem_t 	                drbToSetupModItem[e1ap_maxnoofDRBs];
}DrbToSetupModList_t;

#define PDU_SESSION_RESOURCE_TO_SETUP_MOD_AMBR_PRESENT           					(1 << 0)
#define PDU_SESSION_RESOURCE_TO_SETUP_MOD_DATA_FORWARD_INFORMATION_REQ_PRESENT		(1 << 1)
#define PDU_SESSION_RESOURCE_TO_SETUP_MOD_INACTIVITY_TIMER_PRESENT					(1 << 2)
typedef struct pduSessionResourceToSetupModItem
{
	UINT16								    bitMask;
	UINT8 									pduSessionId;
	PduSessType_e 			        		pduSessionType;
	SNssai_t	 							snssai;
	SecuInd_t				                secuIndi;
	UINT64	 								pduSessionResourceAMBR;/* OPTIONAL */
    UpTransLayerInfo_t                      ngUlUpTnlInfo;
    DFIRequest_t			                pduSessionDataForwardInfoReq;/* OPTIONAL */
	INT64     								pduSessionInactTimer;/* OPTIONAL */
	DrbToSetupModList_t						drbToSetupModList;
}PduSessionResourceToSetupModItem_t;

typedef struct pduSessionResourceToSetupModList
{
    UINT8                                   pduSessionResourceToSetupModItemNum;
    PduSessionResourceToSetupModItem_t      pduSessionResourceToSetupModItem[e1ap_maxnoofPDUSessionResource];
}PduSessionResourceToSetupModList_t;

#define BEARER_CONTEXT_MODIFY_REQ_PDU_SESSION_RESOURCE_TO_SETUP_MOD_LIST_PRESENT			(1 << 0)
#define BEARER_CONTEXT_MODIFY_REQ_PDU_SESSION_RESOURCE_TO_MODIFY_LIST_PRESENT				(1 << 1)
#define BEARER_CONTEXT_MODIFY_REQ_PDU_SESSION_RESOURCE_TO_REMOVE_LIST_PRESENT				(1 << 2)
typedef struct e1apPduSessionResourceToList
{
    UINT16                                   bitMask;
    PduSessionResourceToSetupModList_t       pduSessionResourceToSetupModList; ///< Optional field
	PduSessionResourceToModifyList_t         pduSessionResourceToModfiyList; ///< Optional field
	PduSessionResourceToRemoveList_t         pduSessionResourceToRemoveList; ///< Optional field
} PduSessionResourceList_t;

#define BEARER_CONTEXT_MODIFY_REQ_SECURITY_INFORMATION_PRESENT          					(1 << 0)
#define BEARER_CONTEXT_MODIFY_REQ_UE_DL_AMBR_PRESENT 		            					(1 << 1)
#define BEARER_CONTEXT_MODIFY_REQ_UE_DL_MAX_IPDR_PRESENT		        					(1 << 2)
#define BEARER_CONTEXT_MODIFY_REQ_BEARER_CTX_SATAUS_CHANGE_PRESENT							(1 << 3)
#define BEARER_CONTEXT_MODIFY_REQ_NEW_UL_TNL_INFO_REQ_PRESENT								(1 << 4)
#define BEARER_CONTEXT_MODIFY_REQ_UE_INACTIBITY_TIMER_PRESENT								(1 << 5)
#define BEARER_CONTEXT_MODIFY_REQ_DATA_DISCARD_REQUIRED_PRESENT								(1 << 6)
#define BEARER_CONTEXT_MODIFY_REQ_PDU_SESSION_RESOURCE			                            (1 << 7)
typedef struct e1apBearerContextModReq
{
    UINT16                                   bitMask;
	NrCellId_t								 cellId;							 
    UINT32                   				 gnbCucpUeE1apId;
    UINT32                   				 gnbCuupUeE1apId;
	SecuInfo_t                     			 secuInfo; ///< Optional field
    UINT64                                   ueDlAMBR; ///< Optional field
    UINT64                                   ueDlMaxIPDR; ///< Optional field
    BearCxtStatusChange_e                  bearerCtxStatusChg; ///< Optional field
    NewUlTnlInfoRequire_e         			 newUlTnlInfoRequire; ///< Optional field
    INT64                        			 ueInactTimer; ///< Optional field
    DataDisRequire_e                    	 dataDisRequire; ///< Optional field
    PduSessionResourceList_t                 pduSessionResourceList;///< Optional field
} E1apBearerContextModReq_t;

typedef struct e1apBearerContextRelCmd
{
    NrCellId_t             				    cellId;//added artifficially
	UINT64									gnbCucpUeE1apId;
    UINT64				                    gnbCuupUeE1apId;
    E1apCause_t                             cause;
} E1apBearerContextRelCmd_t;

/**********************************************************************************
 ** UPC <--> E1AP               ACCORDING TO STRUCTURE
***********************************************************************************/
#define MAX_LENGTH_GNBCUUP_NAME         150
typedef struct  gnbCuupName
{
    char                                     gnbCuupName[MAX_LENGTH_GNBCUUP_NAME];
        
}GnbCuupName_t;

#define DATA_FORWARDING_INFO_UL_DATA_FORWARD_PRESENT	(1 << 0)
#define DATA_FORWARDING_INFO_DL_DATA_FORWARD_PRESENT	(1 << 1)  
typedef struct qosFlowItemIEs
{
    UINT8                                    qosFlowIndicator;
    E1apCause_t                              cause;
} QoSFlowItemIEs_t;
typedef struct flowFailedlist
{
    UINT8                                    qosFlowNum;
    QoSFlowItemIEs_t                         qosFlowItemIEs[e1ap_maxnoofQoSFlows];
} FlowFailedlist_t;

#define DRB_SETUP_ITEM_DATA_FORWARD_INFO_RES_PRESENT	(1 << 0)
#define DRB_SETUP_ITEM_FLOW_FAILED_LIST_PRESENT	        (1 << 1)
typedef struct drbSetupItem
{
	UINT16									 bitMask;
    UINT8                                 	 drId;
    DFIResponse_t      						 dataForwardInfoRsp;/*optional*/
    UPParametersList_t                       upPara;
    QoSFlowList_t                            flowSetupList; 
    FlowFailedlist_t                         flowFailedlist;/*optional*/
} DRBSetupItem_t;
typedef struct drbSetupList
{
    UINT8                                    drbSetupNum;
    DRBSetupItem_t                           drbSetupItem[e1ap_maxnoofDRBs]; 
} DRBSetupList_t;

typedef struct
{
	UINT8								 	 drbID;
	E1apCause_t								 cause;
}DRBFailItem_t;

typedef struct drbFailedList
{   
	UINT8									 drbFailNum;
	DRBFailItem_t							 drbFailItem[e1ap_maxnoofDRBs];
} DRBFailedList_t;

#define PDU_SESSION_RESOURCE_SETUP_SECURITY_RESULT_PRESENT			(1 << 0)
#define PDU_SESSION_RESOURCE_SETUP_DATA_FORWARD_INFO_RES_PRESENT	(1 << 1)
#define PDU_SESSION_RESOURCE_SETUP_NG_DL_UP_UNCHANGED_PRESENT		(1 << 2)
#define PDU_SESSION_RESOURCE_SETUP_DRB_FAILED_LIST_PRESENT		    (1 << 3)

typedef struct pduSessionResourceSetupItem
{
    UINT16								     bitMask;
    INT64                         			 pduSessionId;
    SecuResult_t	                         securityResult;/* OPTIONAL */
    UpTransLayerInfo_t                       ngDlUpTransLayerInfo;
    DFIResponse_t						     dataForwardingInformationResponse;/* OPTIONAL */
	/* e_PDU_Session_Resource_Setup_Item__nG_DL_UP_Unchanged */
	NgDlUpUnchange_e						 ngDlUpUchange;/* OPTIONAL */
    DRBSetupList_t                           drbSetupList;
    DRBFailedList_t                          drbFailedList;
}PduSessionResourceSetupItem_t;

typedef struct pduSessionResourceSetupList
{
    UINT8                                    sessionResourceSetupNum;
    PduSessionResourceSetupItem_t            pduSessionResourceSetupItem[e1ap_maxnoofPDUSessionResource];
}PduSessionResourceSetupList_t;

typedef struct pduSessionResourceFailedItem
{
    INT64                         			 sessId;
	E1apCause_t								 cause;
}PduSessionResourceFailedItem_t;

typedef struct pduSessionResourceFailedlist
{
    UINT8                                    sessFailNum;
    PduSessionResourceFailedItem_t           sessFailItem[e1ap_maxnoofPDUSessionResource];
}PduSessionResourceFailedList_t;

#define DRB_MODIFY_ITEM_UL_UP_TRANSPORT_PARA_PRESENT	(1 << 0)
#define DRB_MODIFY_ITEM_PDCP_SN_STATUS_INFO_PRESENT		(1 << 1)
#define DRB_MODIFY_ITEM_FLOW_SETUP_LIST_PRESENT			(1 << 2)
#define DRB_MODIFY_ITEM_FLOW_FAILED_LIST_PRESENT		(1 << 3)
typedef struct dRBModifyItem
{
	UINT16                    				 bitMask;
	UINT8									 drbId;
	UPParametersList_t                       ulUpTransPara;/* OPTIONAL */
	PdcpSNStatusInfo_t						 pdcpSNStatusInfo;/* OPTIONAL */
	QoSFlowList_t                            flowSetupList;/* OPTIONAL */
	FlowFailedlist_t                         flowFailedlist;/* OPTIONAL */
} DRBModifyItem_t;

typedef struct dRBModifyList
{
    UINT8                                    drbModifyItemNum;
    DRBModifyItem_t                        	 drbModifyItem[e1ap_maxnoofDRBs]; 
} DRBModifyList_t;

#define PDU_SESSION_RESOURCE_MODIFY_DL_UP_TNL_INFO_PRESENT          	(1 << 0)
#define PDU_SESSION_RESOURCE_MODIFY_SECURITY_RESULT_PRESENT          	(1 << 1)
#define PDU_SESSION_RESOURCE_MODIFY_DATA_FORWARD_INFO_RSP_PRESENT		(1 << 2)
#define PDU_SESSION_RESOURCE_MODIFY_DRB_SETUP_LIST_PRESENT				(1 << 3)
#define PDU_SESSION_RESOURCE_MODIFY_DRB_FAILED_LIST_PRESENT				(1 << 4)
#define PDU_SESSION_RESOURCE_MODIFY_DRB_MODIFY_LIST_PRESENT				(1 << 5)
#define PDU_SESSION_RESOURCE_MODIFY_DRB_FAILED_TO_MOD_LIST_PRESENT		(1 << 6)
typedef struct pduSessionResourceModifyItem
{
	UINT16									 bitmask;
	UINT8						 			 pduSessionId;
	UpTransLayerInfo_t						 ngDlUpTnlInfo;/* OPTIONAL */
	SecuResult_t	                         securityResult;/* OPTIONAL */
	DFIResponse_t							 pduSessionDataForwardInfoRsp;/* OPTIONAL */
	DRBSetupList_t							 drbSetupList;/* OPTIONAL */
	DRBFailedList_t							 drbFailedList;/* OPTIONAL */
	DRBModifyList_t							 drbModifyList;/* OPTIONAL */
	DRBFailedList_t						 	 drbFailedToModList;/* OPTIONAL */
}PduSessionResourceModifyItem_t;

typedef struct pduSessionResourceModifyList
{
    UINT8                                    pduSessionResourceModifyItemNum;
    PduSessionResourceModifyItem_t		     pduSessionResourceModifyItem[e1ap_maxnoofPDUSessionResource];
}PduSessionResourceModifyList_t;

typedef struct	e1apSliceSupportItem
{
	SNssai_t  	                             snssai;
}E1apsliceSupportItem_t;

typedef struct	e1apSliceSupportList
{
    UINT8                                    SliceSupportItemNum;
    E1apsliceSupportItem_t                   sliceSupportItem[e1ap_maxnoofSliceItems];
}E1apsliceSupportList_t;

typedef struct	nrCgiSupportItem
{
	CuNrCgi_t  	                             NrCgi;
}NrCgiSupportItem_t;

typedef struct	nrCgiSupportList
{
    UINT8                                    NrCgiSupportItemNum;
    NrCgiSupportItem_t                       NrCgiSupportItem[e1ap_maxnoofNRCGI];
}NrCgiSupportList_t;

typedef struct	NGRANQoSSupportItem
{
	NonDynamic5QIDescr_t				     NonDynamic5QIDescr;
}NGRANQoSSupportItem_t;

typedef struct	nGRANQoSSupportList
{
    UINT8                                    NGRANQoSSupportItemNum;
    NGRANQoSSupportItem_t				     NGRANQoSSupportItem[e1ap_maxnoofNGRANQOSParameters];
}NGRANQoSSupportList_t;

typedef struct	qosParamtersSupportList
{
	UINT16								     bitMask;
	NGRANQoSSupportList_t					 NGRANQoSSupportList;
}QosParamtersSupportList_t;

typedef struct supportedPLMNsItem_s
{
	PlmnId_t					             plmnId;
    E1apsliceSupportList_t  	             sliceSupportList;/*optional*/
	NrCgiSupportList_t					     nrCgiSupportList;/*optional*/
	QosParamtersSupportList_t                qosParamtersSupportList;/*optional*/
}SupportedPLMNsItem_t;

typedef struct supportedPLMNsList_s
{
	UINT8                                    supportPlmns;
    SupportedPLMNsItem_t				     SupportedPLMNsItem[e1ap_maxnoofSPLMNs];
}SupportedPLMNsList_t;

typedef struct pduSessionToNotifyItem_s
{
	UINT8									 pduSessionId;
	QoSFlowList_t                            flowSetupList;
}PduSessionToNotifyItem_t;

typedef struct pduSessionToNotifyList_s
{
	UINT8                                    pduSessionToNotifynum;
    PduSessionToNotifyItem_t				 pduSessionToNotifyItem[e1ap_maxnoofPDUSessionResource];
}PduSessionToNotifyList_t;

typedef struct e1apUpbPlmnCfgInfo_s
{
    PlmnId_t								plmnId;
	UINT16									cgiNum;
	CuNrCgi_t						        cgi[e1ap_maxnoofNRCGI];/*optional*/
	E1apsliceSupportList_t  	            sliceSupportList;/*optional*/
	UINT32									qosNum;
	NonDynamic5QIDescr_t					qosPara[e1ap_maxnoofNGRANQOSParameters];/*optional*/
}E1apUpbPlmnCfgInfo_t;

/**********************************************************************************
 ** UPC <--> E1AP                MESSAGE STRUCTURE
***********************************************************************************/

typedef struct e1apRegistergNBReq
{
    Instance_t                              instance;
    UINT8                                   state;
    GnbCuupName_t                           gnbCuupName;              
}E1apRegistergNBReq_t;

/* ����Ϣ�ṹӦ��Ų�� CUUP/INC Ŀ¼��  TBD  */
typedef struct e1apRegistergNBCnf 
{
    Instance_t                              instance;
    UINT8                                   state;
    GnbCucpName_t                           gnbCucpName;
	int										successCellNum;
	CellIdList_t							successCellList;
	int										failCellNum;
	CellIdList_t							failCellList;
} E1apRegistergNBCnf_t;

/* Deregister Indication */
typedef struct e1apDeregisteredgNBInd
{
    Instance_t                              instance;                            
} E1apDeregisteredgNBInd_t;

typedef struct UpbPlmnCfgInfolist
{
    UINT32									 bPlmnNum;
	E1apUpbPlmnCfgInfo_t					 bPlmnCfgInfo[e1ap_maxnoofSPLMNs];                         
} E1apUpbPlmnCfgInfoList_t;

#define E1AP_REGISTER_REQ_UPNAME_PRESENT		(1 << 0)
#define E1AP_REGISTER_REQ_UP_CAPACITY_PRESENT	(1 << 1)
typedef struct e1apRegisterCpReq
{
    UINT16                                   bitMask;
	Instance_t                               instance;
    UINT64                                   transactionId;
    UINT64                                   gnbCuupId;
    GnbCuupName_t                            gnbCuupName;/*optional*/
    CNSupport_e                              cnSupport;
    E1apUpbPlmnCfgInfoList_t                 e1apUpbPlmnCfgInfoList;
	INT64									 upCapacity;/*optional*/
} E1apRegisterCpReq_t;
#define E1AP_SETUP_RSP_UPNAME_PRESENT		(1 << 0)
#define E1AP_SETUP_RSP_UP_CAPACITY_PRESENT	(1 << 1)
typedef struct e1apSetupRsp
{
    UINT16                                   bitMask;
	Instance_t                               instance;
    UINT64                                   transactionId;
    UINT64                                   gnbCuupId;
    GnbCuupName_t                            gnbCuupName;/*optional*/
    CNSupport_e                              cnSupport;
    E1apUpbPlmnCfgInfoList_t                 e1apUpbPlmnCfgInfoList;
	INT64									 upCapacity;/*optional*/
} E1apSetupRsp_t;
typedef struct e1apSetupFail
{
    UINT16                                  bitMask;
    long                                    transactionId;
    E1apCause_t                             cause;
    TimeToWait_e                            timeToWait;/*optional*/
    E1Criticalitydiagnostics_t              criticalDiagnostics;/*optional*/
} E1apSetupFail_t;

typedef struct e1apReleaseRsp
{
    INT64			                          transactionId;
} E1apReleaseRsp_t;

#define E1AP_PDU_SESSION_RESOURCE_FAILED_LIST_PRESENT		(1 << 0)
typedef struct e1apPduSessionResourceSetuplist
{
    UINT16                                   bitMask;
    PduSessionResourceSetupList_t            pduSessionResourceSetuplist;
    PduSessionResourceFailedList_t           pduSessionResourceFailedList; //OPTION
} E1apPduSessionResourceSetupList_t;

typedef struct e1apBearerContextSetupRsp
{
    UINT64				                     gnbCucpUeE1apId;
    UINT64				                     gnbCuupUeE1apId;
    E1apPduSessionResourceSetupList_t        e1apPduSessionResourceSetuplist;
} E1apBearerContextSetupRsp_t;

#define BEARER_CONTEXT_MOD_FAIL_CRITICAL_DIAGNOSE_PRESENT		(1 << 0)
typedef struct e1apBearerContextModFail
{
    UINT16                    	bitMask;
    UINT32                    	gnbCucpUeE1apId;
    UINT32                    	gnbCuupUeE1apId;
	E1apCause_t				  	cause;
	E1Criticalitydiagnostics_t	e1apCriticalDiagnose;
} E1apBearerContextModFail_t;

#define BEARER_CONTEXT_SETUP_FAILURE_CRITICAL_DIAGNOSE_PRESENT	(1 << 0)
typedef struct e1apBearerContextSetupFailure
{
	UINT16                    				 bitMask;
    UINT64				                     gnbCucpUeE1apId;
    UINT64				                     gnbCuupUeE1apId;
 	E1apCause_t								 cause;
	E1Criticalitydiagnostics_t 	  			 criticalDiagnose; /* Optional field*/
} E1apBearerContextSetupFailure_t;

#define DRB_SETUP_MOD_ITEM_DATA_FORWARD_INFO_RSP_PRESENT	(1 << 0)
#define DRB_SETUP_MOD_ITEM_FLOW_FAILED_LIST_PRESENT			(1 << 1)
typedef struct dRBSetupModItem
{
	UINT16                    				 bitMask;
	UINT8									 drbId;
	DFIResponse_t							 drbDataForwardInfoRsp;/* OPTIONAL */
	UPParametersList_t                       ulUpTransPara;
    QoSFlowList_t                            flowSetupList;
	FlowFailedlist_t                         flowFailedlist;/* OPTIONAL */
} DRBSetupModItem_t;

typedef struct dRBSetupModList
{
    UINT8                                    drbSetupModItemNum;
    DRBSetupModItem_t                        drbSetupModItem[e1ap_maxnoofDRBs]; 
} DRBSetupModList_t;

#define PDU_SESSION_RESOURCE_SETUP_MOD_SECURITY_RESULT_PRESENT          (1 << 0)
#define PDU_SESSION_RESOURCE_SETUP_MOD_DATA_FORWARD_INFO_RSP_PRESENT	(1 << 1)
#define PDU_SESSION_RESOURCE_SETUP_MOD_DRB_FAILED_LIST_PRESENT			(1 << 2)
typedef struct pduSessionResourceSetupModItem
{
	UINT16									 bitmask;
	UINT8									 pduSessionId;
    SecuResult_t	                         securityResult;/* OPTIONAL */
	UpTransLayerInfo_t						 ngDlUpTnlInfo;
	DFIResponse_t							 pduSessionDataForwardInfoRsp;/* OPTIONAL */
	DRBSetupModList_t                        drbSetupModList;
	DRBFailedList_t                          drbFailedList;/* OPTIONAL */
}PduSessionResourceSetupModItem_t;

typedef struct pduSessionResourceSetupModList
{
    UINT8                                    	pduSessionResourceSetupModItemNum;
    PduSessionResourceSetupModItem_t            pduSessionResourceSetupModItem[e1ap_maxnoofPDUSessionResource];
}PduSessionResourceSetupModList_t;

#define BEARER_CONTEXT_MODIFY_RSP_PDU_SESSION_RESOURCE_SETUP_MOD_LIST_PRESENT			(1 << 0)
#define BEARER_CONTEXT_MODIFY_RSP_PDU_SESSION_RESOURCE_FAILED_MOD_LIST_PRESENT			(1 << 1)
#define BEARER_CONTEXT_MODIFY_RSP_PDU_SESSION_RESOURCE_MODIFY_LIST_PRESENT				(1 << 2)
#define BEARER_CONTEXT_MODIFY_RSP_PDU_SESSION_RESOURCE_FAILED_TO_MOD_LIST_PRESENT		(1 << 3)
typedef struct e1apBearModPduSessionResource
{
	UINT16									 bitmask;
	PduSessionResourceSetupModList_t		 pduSessionResourceSetupModList;///< Optional field
	PduSessionResourceFailedList_t           pduSessionResourceFailedModList;///< Optional field
	PduSessionResourceModifyList_t           pduSessionResourceModfiyList;///< Optional field
	PduSessionResourceFailedList_t           pduSessionResourceFailedToModList;///< Optional field
} E1apBearModPduSessionResource_t;

#define BEARER_CONTEXT_MODIFY_RSP_PDU_SESSION_RESOURCE_LIST		                        (1 << 0)
typedef struct e1apBearerContextModRsp
{
	UINT16									 bitmask;
    UINT64                   				 gnbCucpUeE1apId;
    UINT64                   				 gnbCuupUeE1apId;
    E1apBearModPduSessionResource_t          e1apBearModPduSessionResource;/*optional*/
} E1apBearerContextModRsp_t;

#define BREARE_CONTEXT_RELEASE_COMPLETE_CRITICALITY_DIAGNOSTICS_PRESENT	                (1 << 0)
typedef struct e1apBearerContextRlsCmp
{
	UINT16									 bitmask;
	UINT64					                 gnbCucpUeE1apId;
    UINT64				                     gnbCuupUeE1apId;
    E1Criticalitydiagnostics_t               criticalDiagnostics;/*optional*/
}E1apBearerContextRlsCmp_t;

#define E1AP_DL_DATA_NOTIFY_PPI_PRESENCE	                (1 << 0)
typedef struct e1apDlDataNote
{
    UINT16                                   bitmask;
    UINT64                                   gnbCucpUeE1apId;
    UINT64                                   gnbCuupUeE1apId;
    INT64                                    ppi; /*optional*/
}IfmE1apDlDataNotify_t;

typedef struct e1apUlDataNote
{
    UINT64                                   gnbCucpUeE1apId;
    UINT64                                   gnbCuupUeE1apId;
	PduSessionToNotifyList_t		         pduSessionToNotifyList;
}E1apUlDataNote_t;

/* Error Indication */
#define ERROR_INDICATION_CU_CP_UE_E1AP_ID_PRESENT   		(1 << 0)
#define ERROR_INDICATION_CU_UP_UE_E1AP_ID_PRESENT   		(1 << 1)
#define ERROR_INDICATION_CAUSE_PRESENT                  	(1 << 2)
#define ERROR_INDICATION_CRITICALITYDIAGNOSTICS_PRESENT 	(1 << 3)
typedef struct E1apErrInd
{
	UINT8							bitMask;
	UINT64		 					transId;
	UINT64							gnbCucpUeE1apId; /* OPTIONAL */
	UINT64							gnbCuupUeE1apId; /* OPTIONAL */
	E1apCause_t 					cause; /* OPTIONAL */
	E1Criticalitydiagnostics_t		critiDiag; /* OPTIONAL */
} IfmE1apErrInd_t;

//RRC_INACTIVE Begin
typedef struct e1apDrbActivityItem_s
{
    UINT32 drbId;
    BOOL   active;
}E1apDrbActivityItem_t;

typedef struct e1apDrbActivityList_s
{
    UINT8 numDrbActivityItem;//1~e1ap_maxnoofDRBs
    E1apDrbActivityItem_t drbActivityItem[e1ap_maxnoofDRBs];
}E1apDrbActivityList_t;


typedef struct e1apPduSessionActivityItem_s
{
    UINT8 pduSessionId;
    BOOL  active;
}E1apPduSessionActivityItem_t;
typedef struct e1apPduSessionActivityList_s
{
    UINT16 numPduSessionActivityItem;//1~e1ap_maxnoofPDUSessionResource
    E1apPduSessionActivityItem_t pduSessionActivityItem[e1ap_maxnoofPDUSessionResource];
}E1apPduSessionActivityList_t;
typedef struct e1apUeActivity_s
{
    BOOL active;
}E1apUeActivity_t;

//UPC_E1AP_BEAR_CTX_INACTIVE_NOTIFY
//E1AP_CUC_BEAR_CTX_INACTIVE_NOTIFY
#define TAG_E1AP_BEAR_INAC_DRB_ACTIVITY_LIST            1
#define TAG_E1AP_BEAR_INAC_PDU_SESSION_ACTIVITY_LIST    2
#define TAG_E1AP_BEAR_INAC_UE_ACTIVITY                  3
typedef struct ifmE1apBearCtxInactiveNotify
{
    UINT64                          transId;
    UINT64                          gnbCucpUeE1apId;
    UINT64                          gnbCuupUeE1apId;
    UINT8                           tag;
    union {
        E1apDrbActivityList_t drbActivityList;
        E1apPduSessionActivityList_t pduSessionActivityList;
        E1apUeActivity_t ueActivity;
    }u;
} IfmE1apBearCtxInactiveNotify_t;
#ifdef __cplusplus
}
#endif


#endif  /* __CUMODULEINTERFACEH__*/


