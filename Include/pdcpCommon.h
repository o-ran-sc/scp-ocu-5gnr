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


#ifndef NR_PDCP_COMMON_H
#define NR_PDCP_COMMON_H

#include "vos_types.h"
#include "vos_linklist.h"
#include "vos_lib.h"
#include "gnbCommon.h"


#define FALSE 							0
#define TRUE 							1
#define PDCP_INFINITY 					1
#define PDCP_DISCARD_TIMER_INFINITY 	2
#define ROHC_BUFFER_SIZE 			 8096//1024
#define PDCP_MAC_I_LEN 					4
#define PDCP_SN_12_HEAD_LEN 			2
#define PDCP_SN_18_HEAD_LEN 			3
#define MAX_PDCP_SN_12 			   0x1000
#define MAX_PDCP_SN_18 			  0x40000
#define SN_12_WINDOW_SIZE			 2048
#define SN_18_WINDOW_SIZE		   131072
#define REORDER_TIMER_NUM			   36
#define DISCARD_TIMER_NUM			   15


// TODO: the number of node is not sure yet
#define PDCP_MAX_NODE_NUM 	10
#define PDCP_SPARED		-1

/* for ciphering */
#define INACTIVE_ENC_STATE		0
#define ACTIVE_ENC_STATE		1
#define MIDDLE_ENC_STATE 		3	/* for srb */

/* for ciphering */
#define INACTIVE_INT_STATE		0
#define ACTIVE_INT_STATE		1


typedef plist pdcpcList;

#if 0
typedef UINT8  PdcpSrbId;
typedef UINT16 PdcpUeIdx;
typedef UINT8  PdcpCellId;
#endif

typedef UINT8 PdcpBool_t;

/* the type of RB */
typedef enum
{
	SRB = 0,
	DRB = 1
}RbType;


/* the direction of data transmission */
typedef enum
{
	UPLINK		= 0,
	DOWNLINK	= 1
}PdcpDirection_e;


/* pdcp pdu type */
typedef enum
{
	PDCP_CTRL_PDU = 0,			/* control pdu */
	PDCP_DATA_PDU = 1			/* data pdu */
}PdcpPduType_e;


/* pdcp control pdu type */
typedef enum
{
	PDCP_CTRL_PDU_SR = 0, 		/*status report*/
	PDCP_CTRL_PDU_RF = 1,		/*rohc feedback*/
	PDCP_CTRL_PDU_RESERVED1 = 2,
	PDCP_CTRL_PDU_RESERVED2 = 3,
	PDCP_CTRL_PDU_RESERVED3 = 4,
	PDCP_CTRL_PDU_RESERVED4 = 5,
	PDCP_CTRL_PDU_RESERVED5 = 6,
	PDCP_CTRL_PDU_RESERVED6 = 7
}PdcpCtrlPduType_e;


/* integrity algorithm */
typedef enum
{
    NIA0 = 0,
    NIA1 = 1,
    NIA2 = 2,
    NIA3 = 3,
    INT_SPARE4 = 4,
    INT_SPARE3 = 5,
    INT_SPARE2 = 6,
    INT_SPARE1 = 7
}IntAlgorithm;


/* ciphering algorithm */
typedef enum
{
	NEA0 = 0,
	NEA1 = 1,
	NEA2 = 2,
	NEA3 = 3,
	CIP_SPARE4 = 4,
	CIP_SPARE3 = 5,
	CIP_SPARE2 = 6,
	CIP_SPARE1 = 7
}CipAlgorithm;


#if 0
/* For all srbs and drbs per ue */
typedef struct{
	UINT32	k_gnb[8];			/* 256 bit */
	UINT32 	k_up_enc[4];		/* 128 bit */
	UINT32	k_cp_enc[4];		/* 128 bit */
	UINT32 	k_up_int[4];		/* 128 bit */
	UINT32	k_cp_int[4];		/* 128 bit */
	UINT32	nh[8]; 				/* Next Hop parameter 256 bit */
	UINT8 	ncc; 				/* maximum: 3bit */
	UINT8 	enc_algorithm;  	/* Encryption Algorithm */
	UINT8	int_algorithm;  	/* Integrity Algorithm */
	UINT8	enc_active_flag;  	/* define whether the encryption function has been activated */
	UINT8	int_active_flag;   	/* define whether the integrity protection function has been activated */
	UINT8	nh_ind;				/* 1: nh existed 0: not existed */
} UeSecurityParams;
#endif

typedef enum {
    DISCARD_MS10 = 10,
    DISCARD_MS20 = 20,
    DISCARD_MS30 = 30,
    DISCARD_MS40 = 40,
    DISCARD_MS50 = 50,
    DISCARD_MS60 = 60,
    DISCARD_MS75 = 75,
    DISCARD_MS100 = 100,
    DISCARD_MS150 = 150,
    DISCARD_MS200 = 200,
    DISCARD_MS250 = 250,
    DISCARD_MS300 = 300,
    DISCARD_MS500 = 500,
    DISCARD_MS750 = 750,
    DISCARD_MS1500 = 1500,
    DISCARD_INFINITY = PDCP_DISCARD_TIMER_INFINITY
}DISCARD_TIMER;


typedef enum{
    LEN12BITS = 12,
    LEN18BITS = 18
}PdcpSnSize_e;


typedef enum pdcpRlcMode
{
	TM_MODE = 1,		/*!< RLC TM Mode */
	UM_MODE,			/*!< RLC UM Mode */
	AM_MODE,			/*!< RLC AM Mode */
}PdcpRlcMode_e;


typedef struct{
    PdcpBool_t profile0x0001;
    PdcpBool_t profile0x0002;
    PdcpBool_t profile0x0003;
    PdcpBool_t profile0x0004;
    PdcpBool_t profile0x0005;
    PdcpBool_t profile0x0006;
    PdcpBool_t profile0x0101;
    PdcpBool_t profile0x0102;
    PdcpBool_t profile0x0103;
    PdcpBool_t profile0x0104;
}ROHCProfiles_t;

typedef struct{
    UINT16 maxCID;
    ROHCProfiles_t rohcProfiles;
}ROHCConfig_t;

typedef struct{
    UINT16 maxCID;
    PdcpBool_t profile0x0006;
}UplinkOnlyRohc_t;


typedef struct{
    UINT16 cellGroupID;
    UINT8  lcID;
}PrimaryPath;

typedef enum{
    B0 = 0,
    B100 = 100,
    B200 = 200,
    B400 = 400,
    B800 = 800,
    B1600 = 1600,
    B3200 = 3200,
    B6400 = 6400,
    B12800 = 12800,
    B51200 = 51200,
    B102400 = 102400,
    B204800 = 204800,
    B409600 = 409600,
    B819200 = 819200,
    B1228800 = 1228800,
    B1638400 = 1638400,
    B2457600 = 2457600,
    B3276800 = 3276800,
    B4096000 = 4096000,
    B4915200 = 4915200,
    B5734400 = 5734400,
    B6553600 = 6553600,
    INFINITY = PDCP_INFINITY,
    SPARE8 = PDCP_SPARED,
    SPARE7 = PDCP_SPARED,
    SPARE6 = PDCP_SPARED,
    SPARE5 = PDCP_SPARED,
    SPARE4 = PDCP_SPARED,
    SPARE3 = PDCP_SPARED,
    SPARE2 = PDCP_SPARED,
    SPARE1 = PDCP_SPARED
}ULSPILT_THRESHOLD;

typedef struct{
    UINT16 release;
    ULSPILT_THRESHOLD ulspiltThreshold;
}UlDataSplitThreshold;

typedef struct{
    PrimaryPath primaryPath;
    UlDataSplitThreshold ulDataSplitThreshold;
    PdcpBool_t duplication;
}MoreThanOneRLCContext;

typedef enum{
	REORDER_MS0 = 0,
	REORDER_MS1 = 1,
	REORDER_MS2 = 2,
	REORDER_MS4 = 4,
	REORDER_MS5 = 5,
	REORDER_MS8 = 8,
	REORDER_MS10 = 10,
	REORDER_MS15 = 15,
	REORDER_MS20 = 20,
	REORDER_MS30 = 30,
	REORDER_MS40 = 40,
	REORDER_MS50 = 50,
	REORDER_MS60 = 60,
	REORDER_MS80 = 80,
	REORDER_MS100 = 100,
	REORDER_MS120 = 120,
	REORDER_MS140 = 140,
	REORDER_MS160 = 160,
	REORDER_MS180 = 180,
	REORDER_MS200 = 200,
	REORDER_MS220 = 220,
	REORDER_MS240 = 240,
	REORDER_MS260 = 260,
	REORDER_MS280 = 280,
	REORDER_MS300 = 300,
	REORDER_MS500 = 500,
	REORDER_MS750 = 750,
	REORDER_MS1000 = 1000,
	REORDER_MS1250 = 1250,
	REORDER_MS1500 = 1500,
	REORDER_MS1750 = 1750,
	REORDER_MS2000 = 2000,
	REORDER_MS2250 = 2250,
	REORDER_MS2500 = 2500,
	REORDER_MS2750 = 2750,
	REORDER_MS3000 = 3000,
	REORDER_SPARE28 = PDCP_SPARED,
	REORDER_SPARE27 = PDCP_SPARED,
	REORDER_SPARE26 = PDCP_SPARED,
	REORDER_SPARE25 = PDCP_SPARED,
	REORDER_SPARE24 = PDCP_SPARED,
	REORDER_SPARE23 = PDCP_SPARED,
	REORDER_SPARE22 = PDCP_SPARED,
	REORDER_SPARE21 = PDCP_SPARED,
	REORDER_SPARE20 = PDCP_SPARED,
	REORDER_SPARE19 = PDCP_SPARED,
	REORDER_SPARE18 = PDCP_SPARED,
	REORDER_SPARE17 = PDCP_SPARED,
	REORDER_SPARE16 = PDCP_SPARED,
	REORDER_SPARE15 = PDCP_SPARED,
	REORDER_SPARE14 = PDCP_SPARED,
	REORDER_SPARE13 = PDCP_SPARED,
	REORDER_SPARE12 = PDCP_SPARED,
	REORDER_SPARE11 = PDCP_SPARED,
	REORDER_SPARE10 = PDCP_SPARED,
	REORDER_SPARE09 = PDCP_SPARED,
	REORDER_SPARE08 = PDCP_SPARED,
	REORDER_SPARE07 = PDCP_SPARED,
	REORDER_SPARE06 = PDCP_SPARED,
	REORDER_SPARE05 = PDCP_SPARED,
	REORDER_SPARE04 = PDCP_SPARED,
	REORDER_SPARE03 = PDCP_SPARED,
	REORDER_SPARE02 = PDCP_SPARED,
	REORDER_SPARE01 = PDCP_SPARED
}PDCP_TREORDERING;

typedef struct{
	UINT32 rxCount;		/* count value calculated of per data packet */
    UINT32 txNext;
    UINT32 rxDelivery;
    UINT32 rxNext;
    UINT32 rxReorder;
}PdcpStateVar_t;


typedef struct{

}ROHCCompressor;

typedef struct{

}ROHCDecompressor;


/* get sn value when sn size is 12 bits */
#define GET_SN_12_SN(p)  ((p) & 0x00000fff)

/* get sn value when sn size is 18 bits */
#define GET_SN_18_SN(p)  ((p) & 0x0003ffff)

/* get hfn value when sn size is 12 bits */
#define GET_HFN_12_SN(p) (((p) & 0xfffff000) >> 12)

/* get hfn value when sn size is 18 bits */
#define GET_HFN_18_SN(p) (((p) & 0xfffc0000) >> 18)

/* get count value when sn size is 12 bits */
#define GET_COUNT_12_SN(a,b)  ((((a) & 0x000fffff)<<12)|((b) & 0x00000fff))

/* get count value when sn size is 18 bits */
#define GET_COUNT_18_SN(a,b)  ((((a) & 0x00003fff)<<18)|((b) & 0x00003ffff))




#endif /* NR_PDCP_COMMON_H */
