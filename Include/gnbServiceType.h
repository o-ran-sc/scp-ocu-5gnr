/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/

#ifndef __GNB_COMM_TYPE_H__
#define __GNB_COMM_TYPE_H__

/** @brief max cell num */
#define MAX_CELL_NUM                   4

/** @brief max cell id */
#define MAX_CELL_ID                    (MAX_CELL_NUM - 1)

/** @brief max ue num */
#define MAX_UE_NUM                     42
#define MAX_UE_NUM_PER_CELL            21

/** @brief max ue id */
#define MAX_UE_ID                      (MAX_UE_NUM - 1)

/** @brief max drb num */
#define MAX_DRB_NUM                    33

/** @brief max drb id */
#define MAX_DRB_ID                     (MAX_DRB_NUM - 1)

/** @brief max srb num */
#define MAX_SRB_NUM                    4

/** @brief max srb id */
#define MAX_SRB_ID                     (MAX_SRB_NUM - 1)

/** @brief max logical channel num */
#define MAX_LCH_NUM                    33

#define MAX_PLMN_ID_NUM              8

/** @brief tunnel port */
#define TUNNEL_PORT                   2152

#define MAX_PDU_SESSION_NUM			 (10)

#define MAC_CU_DU_TNL_ASSOC_NUM (32)
/** @brief Cell ID */
typedef UINT16   CmNrCellId;

/** @brief RNTI */
typedef UINT16   CmNrRnti;

/** @brief I-RNTI */
typedef UINT64  CmNrIRnti;

/** @brief Ue Id */
typedef UINT16   CmNrUeId;

/** @brief Radio Bearer ID */
typedef UINT8    CmNrRbId;

/** @brief Logical Channel Type */
typedef UINT8    CmNrLcType;

/** @brief Radio Bearer ID */
typedef UINT8    CmNrRbId;

/** @brief Mode Type TM/UM/AM */
typedef UINT8    CmNrRlcMode;

/** @brief Logical Channel ID */
typedef UINT8    CmNrLcId;

/** @brief Logical Channel Type */
typedef UINT8    CmNrLcType;

/** @brief Sn bits*/
typedef UINT8    CmRlcSnLen;

/*见协议38401 8.5 F1 Startup and cells activation*/
typedef enum
{
    CELL_ACTIVE_STATE,
    CELL_INACTIVE_STATE,
    
}CellState_e;


typedef struct  PlmnId
{
    UINT8                  mcc2:4;
    UINT8                  mcc1:4;
    UINT8                  mnc3:4;
    UINT8                  mcc3:4;
    UINT8                  mnc2:4;
    UINT8                  mnc1:4;
} PlmnId_t;

/* NR CELL Identity */
typedef struct  NrCellId
{
    UINT64                  cellId:36;
}NrCellId_t;

#define      TRACKING_AREA_CODE     (1<<0)
#define      RANRC                  (1<<1)
typedef struct  plmnInformation
{
    UINT16                  bitMask;
    UINT8                   plmnIdNum;  
    PlmnId_t                plmnId[MAX_PLMN_ID_NUM];
    UINT32                  trackingAreaCode;  /*option*/
    UINT8                   ranac;             /*option*/
    UINT64                  cellIdentity;
    BOOL                    cellReservedForOperatorUse;
} PlmnInformation_t;


typedef struct
{
    PlmnId_t               plmn;
    UINT64                 cellId;
} GnbNrCgi_t;

typedef struct
{
    PlmnId_t               plmn;
}GnbServedPlmn_t;


/** @brief SRBID */
typedef LONG	 GnbSrbId_t;//9.3.1.7

/** @brief DRB ID */
typedef LONG	 GnbDrbId_t;

/** @brief Transaction ID */
typedef LONG     GnbTransId;

/** @brief gND DU ID */
typedef LONG     GnbDuId;

/** @brief gND CU ID */
typedef LONG     GnbCuId;



#endif

