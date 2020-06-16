/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef __CUMODULECOMMONH__
#define __CUMODULECOMMONH__

#ifdef __cplusplus
extern "C" {
#endif

#include "gnbCommon.h"
#include "cuModuleEnum.h"

#define MAX_LENGTH_RAN_NAME         150

#define CU_MAX_PLMN_NUM       6
#define CU_MAX_UES_PER_CELL   32
#define CU_MAX_DU_NUM         2

#define CU_MAX_AMF_NUM         2
#define CU_MAX_UPF_NUM         2
#define CU_MAX_CUUP_NUM        4

#define CU_MAX_CUCP_NUM        2


#define CU_SEC_SNOW3G_ALGO_BITMASK 0x01
#define CU_SEC_AES_ALGO_BITMASK    0x02
#define CU_SEC_ZUC_ALGO_BITMASK    0x03

#define CU_MAX_AS_SEC_ALGOS   4

#define CU_MAX_SNSSAI_NUM   		3

typedef enum cuSecAlgo_
{
  CU_SEC_NULL_ALGO,
  CU_SEC_SNOW3G_ALGO,
  CU_SEC_AES_ALGO,
  CU_SEC_ZUC_ALGO
} CuSecAlgo_e;


#define CU_INVALID_AP_ID             0xFFFFFFFF;

#define CU_SET_CU_UE_F1AP_ID(_cuUeF1apId,_cellIdx,_ueIdx)  CU_SET_TRANS_ID(_cuUeF1apId,_cellIdx,_ueIdx,0)

/* gNB Identity */
typedef UINT32  gNBId_t;

typedef struct 
{
	PlmnId_t	plmnId;
	gNBId_t		gNBId;
}GlobalRanNodeId_t;

/* Ran name, a string */
typedef struct  RanName
{
    char                    nodeName[MAX_LENGTH_RAN_NAME];
}RanName_t;

/* Tracking Area Code */
typedef struct  cuTac
{
    UINT8                   tac[3];
}CuTac_t;

typedef struct  cuepsTac_s
{
    UINT8                   tac[2];
}CuEpsTac_t;

/* S_NSSAI */
#define S_NSSAI_SD_PRESENT      (1 << 0)
typedef struct  SNssai
{
    UINT16                  bitMask;
    UINT8                   sst;
    UINT32                  sd:24;/*optional*/
}SNssai_t;

typedef struct
{
    UINT8                   sNssaiNum;
    SNssai_t                sNssai[CU_MAX_SNSSAI_NUM];
}SliceList_t;

/* time stamp */
typedef struct  Timestamp
{
    UINT8                   timeStamp[4];
}Timestamp_t;
/* NR-CGI */
typedef struct cuNrCgi
{
    PlmnId_t                plmnId;
    NrCellId_t              nrCellId;
}CuNrCgi_t;
/* TAI */
typedef struct Tai
{
    PlmnId_t                plmnId;
    CuTac_t                   tac;
}Tai_t;

/* masked imeisv */
typedef UINT64  MaskedImeiSv_t;

/* UE Identity Index value */
typedef struct UeIdIdxValue
{
    UINT16                  ueIdIdxValue:10;
}UeIdIdxValue_t;

/* GTP Teid */
typedef UINT32  GtpTeid_t;

typedef struct recomRanGnbId
{
	PlmnId_t				plmnId;
	gNBId_t					gNBId;
}RecomRanGnbId_t;

typedef struct transLayerAddr
{
    UINT8                   transLayerAddress[20];
	UINT8					bitStringSize;			/* bit string size in bytes */
}TransLayerAddr_t;

typedef struct secuResult 
{
    IPResult_e               integrityProtectionResult;
    CPResult_e               confidentialityProtectionResult;
} SecuResult_t;

typedef struct gtpTunnel 
{
    TransLayerAddr_t                        transLayerAddr;
    GtpTeid_t                               gtpTeid;
} GtpTunnel_t;

typedef struct upTransLayerInfo 
{
    GtpTunnel_t                             gtpTunnel;
} UpTransLayerInfo_t;

typedef struct
{
	IPIndication_e							IPIndication;
	CPIndication_e							CPIndication;
	MaxIpDataRate_e							maxIPdataRate;
}SecuInd_t;

#define PRIORITY_LEVEL_QOS_PRESENT                  (1 << 0)
#define NON_DYNAMIC_AVERAGING_WINDOW_PRESENT        (1 << 1) 
#define NON_DYNAMIC_MAX_DATA_BURST_VOLUME           (1 << 2) 
typedef struct nonDynamic5QIDescr 
{
	UINT16									bitMask;
	INT64									fiveQI;
	INT64									priorityLevelQos;		/* OPTIONAL */
	INT64									averagingWindow;		/* OPTIONAL */
	INT64									maxDataBurstVolume; /* OPTIONAL */
} NonDynamic5QIDescr_t;

typedef struct
{
	INT64									perScalar;
	INT64									perExponent;
}PackErrorRate_t;
	
#define FIVEQI_PRESENT                              (1 << 0)
#define DELAY_CRITICAL_PRESENT                      (1 << 1)
#define DYNAMIC_AVERAGING_WINDOW_PRESENT            (1 << 2)
#define DYNAMIC_MAX_DATA_BURST_VOLUME               (1 << 3)
typedef struct dynamic5QIDescr 
{
	UINT16									bitMask;
	INT64									priorityLevelQos;
	INT64									packetDelayBudget;
	PackErrorRate_t 						packetErrorRate;
	INT64									fiveQI; 				/* OPTIONAL */
	Dynamic5QIDelayCritical_e				delayCritical;			/* OPTIONAL */
	INT64									averagingWindow;		/* OPTIONAL */
	INT64									maxDataBurstVolume; 	/* OPTIONAL */
} Dynamic5QIDescr_t;

typedef struct QosCharact
{
	QosCharacterPR_e	present;
	union{
		NonDynamic5QIDescr_t				nonDynamic5QI;
		Dynamic5QIDescr_t					dynamic5QI;
	}choice;
} QosCharact_t;

typedef struct
{
	PriorityLevel_e							priorityLevel;
	PreEmptionCapability_e					pre_emptionCapability;
	PreEmptionVulnerability_e				pre_emptionVulnerability;
}AllocAndRetenPriority_t;

typedef struct
{
	SecuResult_t			securityResult;
	SecuInd_t				securityIndication;
}UserPlaneSecurInfo_t;

#ifdef __cplusplus
}

#endif

#endif
