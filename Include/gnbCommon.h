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

#ifndef _GNB_COMMON_H_
#define _GNB_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "vos_common.h"
#include "vos_sockMgr.h"
#include <netinet/in.h>
#include "gnbServiceType.h"
#include "vos_lib.h"


extern struct timeval procStart, procEnd;

#define MARK_START_TIME()  do{\
    gettimeofday(&procStart,0);\
}while(0)

#define CU_CALC_ELAPSED_TIME(S)  do{\
        INT32 diff;   \
        gettimeofday(&procEnd,0);\
        diff = ( procEnd.tv_sec*1000000L + procEnd.tv_usec ) 		\
        - ( procStart.tv_sec*1000000L + procStart.tv_usec );	\
        vos_info_print("Msg %s spend time = %ld us\n",S ,diff);\
}while(0)


#define	GNB_OK		0
#define GNB_ERROR	1

#define TRUE		1
#define FALSE 		0

/***********************************************************************************************************
************************************************define type in DU ****************************************
************************************************************************************************************/


/***********************************************************************************************************
************************************************** macro define ******************************************
************************************************************************************************************/


/** @brief max logical channel id */
#define MAX_LCH_ID                     (MAX_LCH_NUM - 1)

#define MAX_LEN_AMF_NAME                       150
#define MAX_GNB_DU_NAME                        150
#define MAX_GNB_CU_NAME                        150
#define MAX_GNB_DU_NUM                         2


#define MAX_TASK_NUM                 60
#define MAX_TASK_NAME_LEN            256
#define MAX_QUEUE_NUM                20
#define MAX_QUEUE_MSG_NUM            256
#define MAX_IP_ADDR_STRING_LEN       256
#define MAX_IP_ADDR_NUM              COMM_SCTP_ADDR_MAX

#define MAX_LOCK_NUM                 20
#define MAX_SEMA_NUM                 20
#define MAX_TIMER_NUM                100

#define MAX_SI_NUM                   32
#define MAX_SI_MESSAGE               32
#define MAX_SIB                      32
#define MAX_SIB_LEN                  300

#define RRC_SI_DATA             4
#define MAX_TX_PDU_NUM          256//1024
#define MAX_MULTI_BANDS         8
#define MAX_NR_NS_PMAX          8
#define MAX_ACCESS_CAT          64
#define MAX_BARRING_SET         8
#define MAX_PLMN                12
#define MAXCELLINTRA            16      //Maximum number of intra-Freq cells listed in SIB3
#define MAXCELLBLACK            16      //Maximum number of NR blacklisted cell ranges in SIB3, SIB4
/** @brief max cell bands num */
#define MAX_NR_CELL_BANDS              16//32
/** @brief F1 max cell num */
#define F1_MAX_CELL_NUM                MAX_CELL_NUM


#define COMMON_LOG_LEVEL (0)
#define MAJOR_LOG_LEVEL (1)

/*module msg marco define*/
#define MSG_HEAD_LEN (20)
#define MSG_TOTAL_LEN (8096)
#define MSG_MAX_BUFFER_LEN (MSG_TOTAL_LEN-MSG_HEAD_LEN)

#define MAX_MODULE_NAME_LEN (256)

/*MAX IPV6 ADDR LEN*/
#define MAX_IPV6ADDR_LEN (16)

#define MAX_ENTITY_MANAGE_MSG_NUM 100
#define CHECK_FUNCTION_RET(ret) \
        do { \
            if (VOS_OK != (ret)) { \
                return VOS_ERROR; \
            } \
        } while(0)

extern UINT32 f1apGetModuleId();

#define DUCP_MODULE_ID  ducpGetModuleId()
#define F1AP_MODULE_ID  f1apGetModuleId()



#define	MAX_SCS			5
#define MAX_LENGTH_NGAP_RAN_NAME	150



/***********************************************************************************************************
********************************************* enum define*************************************************
************************************************************************************************************/

/* IP Type */
typedef enum ipAddrType
{
    IPv4,
    IPv6,
    IPTypeMax,
}IpAddrType_e;

typedef enum
{
    SOCKET_SCTP,
    SOCKET_UDP,
    SOCKET_TCP,
    SOCKET_UNIX_UDP,
    SOCKET_UNIX_TCP,
}SOCKET_TYPE;

/** log level */
typedef enum gnbLogLevel
{
	LOG_CRIT = 1,        ///<  critical conditions
	LOG_ERR,             ///<  error conditions
	LOG_WARNING,         ///<  warning conditions
	LOG_INFO,            ///<  informational
	LOG_DEBUG,           ///<  debug info
} gnbLogLevel_e;


/***********************************************************************************************************
****************************************************define typ *********************************************
************************************************************************************************************/
typedef VOID (*FUNCPTR)(void *args);
typedef INT32 (*VOS_TASK_INIT_FUNCPTR)();
typedef VOID (*VOS_TASK_FUNCPTR)(ULONG ulArg1, ULONG ulArg2,ULONG ulArg3, ULONG ulArg4,ULONG ulArg5, ULONG ulArg6,ULONG ulArg7, ULONG ulArg8,ULONG ulArg9, ULONG ulArg10);

typedef INT32 (*USER_TASK_INIT_FUNCPTR)();
typedef LONG  (*USER_TASK_FUNCPTR)(ULONG aulMsg[VOS_QUEUE_MSG_SIZE]);


typedef INT32 (*HOST_TASK_FUNCPTR)(ULONG aulMsg[VOS_QUEUE_MSG_SIZE]);
typedef INT32 (*HOST_TASK_INIT_FUNCPTR)(void);


/***********************************************************************************************************
************************************************task info strcut *******************************************
************************************************************************************************************/

/* IPV4 Address */
typedef struct
{
   UINT16  port;
   UINT32  address;
} Ipv4Addr_t;

/* IPV6 Address */
typedef struct cmInetIpv6Addr
{
   UINT16  port;
   UINT8   IpAddr6[MAX_IPV6ADDR_LEN];
} Ipv6Addr_t;


/* IP Address */
typedef struct ipAddress
{
    IpAddrType_e       ipType; /* type of transport address */
    union
    {
       Ipv4Addr_t  ipv4Addr; /* IPv4 transport address */
       Ipv6Addr_t  ipv6Addr; /* IPv6 transport address */
    }u;
} IpAddress_t;

/* Ran name, a string */
typedef struct  ngapRanName
{
    char                    ranName[MAX_LENGTH_NGAP_RAN_NAME];
}NgapRanName_t;

/* user task info */
typedef struct
{
    UINT32  userTaskId;
    UINT32  hostTaskId;
    UINT8   userTaskName[MAX_TASK_NAME_LEN];
    UINT32  userTaskPriority;
    FUNCPTR userTaskEntry;
} UserTaskInfo_t;

/* Host task info */
typedef struct
{
    UINT32  hostTaskId;
    UINT32  procId;
    UINT8   hostTaskName[MAX_TASK_NAME_LEN];
    UINT32  hostTaskpriority;
    FUNCPTR hostTaskEntry;
} HostTaskInfo_t;

/* user task table info */
typedef struct
{
    UINT32                  userTaskId;
    UINT32                  hostTaskId;
    CHAR                    userTaskName[MAX_TASK_NAME_LEN];/*线程名称*/
    ULONG                   userModuleID;
    UINT32                  userTaskPriority;/*优先级*/
    USER_TASK_INIT_FUNCPTR  userTaskInitPtr;
    USER_TASK_FUNCPTR       userTaskEntry;/*线程执行函数*/
} UserTaskTable_t;

/* Host task table info */

typedef struct
{
    UINT32   hostTaskId;
    CHAR     hostTaskName[MAX_TASK_NAME_LEN];/*线程名称*/
    UINT32   priority;/*优先级*/
    LONG     cpuSize;
    LONG     cpus[8];
} HostTaskTable_t;

/* vos task info */
typedef struct
{
    UINT8                   vosTaskId;
    CHAR                    vosTaskName[MAX_TASK_NAME_LEN];/*线程名称*/
    CHAR                    vosMoudleName[MAX_MODULE_NAME_LEN];
    UINT8                   vosTaskpriority;/*优先级*/
    VOS_TASK_INIT_FUNCPTR   vosTaskInitPtr;
    VOS_TASK_FUNCPTR        vosTaskEntry;/*线程执行函数*/
} VosTaskTable_t;

typedef struct
{
    UINT8         vosTaskId;
    vos_module_t  vosModule;
    VOS_HANDLE    taskHandle;
}MoudleInfo_t;

typedef struct
{
    UCHAR                  ipAddrStr[MAX_IP_ADDR_STRING_LEN];
    UINT32                 port;
}IpAddrStr_t;

typedef struct
{
    LONG                   Count;//最大个数为COMM_SCTP_ADDR_MAX
    IpAddrStr_t            ipList[MAX_IP_ADDR_NUM];
}SockAddrStr_t;

typedef struct
{
    UINT32             vosTaskId;
    SockAddrStr_t      ipAddrStr;

    SockAddrStr_t      clientAddrInfo;
}TaskSockAddrInfo_t;

typedef struct
{
    UINT32             vosTaskId;
    CHAR               vosTaskName[MAX_TASK_NAME_LEN];
    SockAddrStr_t      sockAddrInfo;
    SockAddrStr_t      clientSockAddrInfo;
    UINT32             sockType;
    vos_sock_para_t    comPara;
    vos_sock_info_t    comOpInfo;
}CommPara_t;

typedef struct
{
    UINT8              isUsed;
    vos_sock_info_t    opInfo;
}E1UpClientSockInfo_t;




typedef struct
{

}UdpSocketMsg_t;
typedef struct
{

}TcpSocketMsg_t;

typedef struct
{
    UINT32          connectId;/*SOCKET INDEX*/
    UINT32          fd;/*用于收消息的fd*/
    vos_sockaddr_t  fromAddr;/*用于消息来源地址*/
    struct sctp_sndrcvinfo sri;/*收到的SCTP消息信息*/
    LONG            msg_flags;/*链路信息*/
    UINT32          assocState;/*链路状态*/

}SctpSocketMsg_t;

typedef struct
{

}UnixUdpSocketMsg_t;

typedef struct
{

}UnixTcpSocketMsg_t;

/*
SOCKET msg
*/
typedef struct
{
    UINT32 socketMsgType;
    union
    {
        UdpSocketMsg_t      udpMsg;
        TcpSocketMsg_t      tcpMsg;
        SctpSocketMsg_t     sctpMsg;
        UnixUdpSocketMsg_t  unixUdpSocketMsg;
        UnixTcpSocketMsg_t  unixTcpSocketMsg;
    }u;
}SocketMsg_t;

typedef struct
{
    UINT32 associationId;
    vos_sock_info_t op;/*发送时索引到该字段*/
    ULONG  usedFlag;
}SockInfoMng_t;



/*
1.非SOCKET msg 格式化为接口数据
2.SOCKET msg格式化为：SocketMsg_t数据+接口数据
*/
typedef struct
{
    UINT32   srcModuleId;
    UINT32   dstModuleId;
    UINT32   msgSap;
    UINT32   msgCode;
    UINT32   msgLen;
    UINT8    msgBuf[MSG_MAX_BUFFER_LEN];
} ModuleMsg_t;



/** 采用非VOS通信方式的模块需要提供的额外参数 */
typedef struct
{
    module_comm_type_t type;                ///< 通信方式
    union{
        vos_sockaddr_t addr;                ///< socket 通信
        sctp_para_t    sctp;                ///< sctp   通信
    }u;
    receive_handler  recv_handle;           ///< 接收函数
    LONG             maxClient;             ///< tcp server 允许的连接数
    BOOL             soloMode;              ///< 如果为真，则单独创建接收线程；如果为假，则由 VOS socket代理任务负责接收
    LONG             fdIdx;                 ///< 无需关心
}CommunicatePara_t;


/***********************************************************************************************************
*********************************************protocol info strcut ******************************************
************************************************************************************************************/

/*********************************** Mib_t ***************************************/
typedef enum mibSubCarrierSpacingCommon
{
    MIB_subCarrierSpacingCommon_scs15or60   = 0,
    MIB_subCarrierSpacingCommon_scs30or120  = 1
} MibSubCarrierSpacingCommon_e;

typedef enum mibDmrsTypeaPosition
{
    MIB_dmrs_TypeA_Position_pos2    = 0,
    MIB_dmrs_TypeA_Position_pos3    = 1
} MibDmrsTypeaPosition_e;

typedef enum mibCellBarred
{
    MIB_cellBarred_barred   = 0,
    MIB_cellBarred_notBarred    = 1
} MibCellBarred_e;

typedef enum mibIntraFreqReselection
{
    MIB_intraFreqReselection_allowed    = 0,
    MIB_intraFreqReselection_notAllowed = 1
} MibIntraFreqReselection_e;

typedef enum
{
    mibCellBarredBarred = 0,
    mibCellBarredNotBarred = 1
} CellBarred_e;

typedef enum
{
    mibIntraFreqReselectionAllowed = 0,
    mibIntraFreqReselectionNotAllowed = 1
} IntraFreqReselection_e;

typedef struct PDCCHConfigSIB1
{
    UINT8          controlResourceSetZero;
    UINT8          searchSpaceZero;

}PDCCHConfigSIB1_t;

typedef struct mib
{
    UINT8                               systemFrameNumber;
    MibSubCarrierSpacingCommon_e        subCarrierSpacingCommon;
    UINT8                               ssbSubcarrierOffset;
    MibDmrsTypeaPosition_e              dmrsTypeaPosition;
    UINT8                               searchSpaceZero;
    UINT8                               controlResourceSetZero;
    CellBarred_e                        cellBarred;
    IntraFreqReselection_e              intraFreqReselection;

}Mib_t;

typedef struct macCellCfgPara_s
{
	UINT32	nSSBAbsFre;//
	UINT16	PCI;//
}macCellCfgPara_t;

/*********************************** SIB1_t ***************************************/
typedef enum connEstFailureControlCount
{
    NR_ConnEstFailureControl__connEstFailCount_n1  = 0,
    NR_ConnEstFailureControl__connEstFailCount_n2  = 1,
    NR_ConnEstFailureControl__connEstFailCount_n3  = 2,
    NR_ConnEstFailureControl__connEstFailCount_n4  = 3
} ConnEstFailureControlCount_e;

typedef enum connEstFailureControlOffsetValidity
{
    NR_ConnEstFailureControl__connEstFailOffsetValidity_s30    = 0,
    NR_ConnEstFailureControl__connEstFailOffsetValidity_s60    = 1,
    NR_ConnEstFailureControl__connEstFailOffsetValidity_s120   = 2,
    NR_ConnEstFailureControl__connEstFailOffsetValidity_s240   = 3,
    NR_ConnEstFailureControl__connEstFailOffsetValidity_s300   = 4,
    NR_ConnEstFailureControl__connEstFailOffsetValidity_s420   = 5,
    NR_ConnEstFailureControl__connEstFailOffsetValidity_s600   = 6,
    NR_ConnEstFailureControl__connEstFailOffsetValidity_s900   = 7
} ConnEstFailureControlOffsetValidity_e;

#define     CONN_EST_FAILOFFSET               (1<<0)
typedef struct connEstFailCtrl
{
    UINT16                                   bitMask;
	ConnEstFailureControlCount_e	 		 connEstFailCount;
	ConnEstFailureControlOffsetValidity_e	 connEstFailOffsetValidity;
	UINT8	 								 connEstFailOffset;         /*option*/
} ConnEstFailCtrl_t;

typedef enum timerT300
{
    NR_UE_TimersAndConstants__t300_ms100   = 0,
    NR_UE_TimersAndConstants__t300_ms200   = 1,
    NR_UE_TimersAndConstants__t300_ms300   = 2,
    NR_UE_TimersAndConstants__t300_ms400   = 3,
    NR_UE_TimersAndConstants__t300_ms600   = 4,
    NR_UE_TimersAndConstants__t300_ms1000  = 5,
    NR_UE_TimersAndConstants__t300_ms1500  = 6,
    NR_UE_TimersAndConstants__t300_ms2000  = 7
} TimerT300_e;

typedef enum timerT301
{
    NR_UE_TimersAndConstants__t301_ms100   = 0,
    NR_UE_TimersAndConstants__t301_ms200   = 1,
    NR_UE_TimersAndConstants__t301_ms300   = 2,
    NR_UE_TimersAndConstants__t301_ms400   = 3,
    NR_UE_TimersAndConstants__t301_ms600   = 4,
    NR_UE_TimersAndConstants__t301_ms1000  = 5,
    NR_UE_TimersAndConstants__t301_ms1500  = 6,
    NR_UE_TimersAndConstants__t301_ms2000  = 7
} TimerT301_e;

typedef enum timerT310
{
    NR_UE_TimersAndConstants__t310_ms0     = 0,
    NR_UE_TimersAndConstants__t310_ms50    = 1,
    NR_UE_TimersAndConstants__t310_ms100   = 2,
    NR_UE_TimersAndConstants__t310_ms200   = 3,
    NR_UE_TimersAndConstants__t310_ms500   = 4,
    NR_UE_TimersAndConstants__t310_ms1000  = 5,
    NR_UE_TimersAndConstants__t310_ms2000  = 6
} TimerT310_e;

typedef enum timerN310
{
    NR_UE_TimersAndConstants__n310_n1  = 0,
    NR_UE_TimersAndConstants__n310_n2  = 1,
    NR_UE_TimersAndConstants__n310_n3  = 2,
    NR_UE_TimersAndConstants__n310_n4  = 3,
    NR_UE_TimersAndConstants__n310_n6  = 4,
    NR_UE_TimersAndConstants__n310_n8  = 5,
    NR_UE_TimersAndConstants__n310_n10 = 6,
    NR_UE_TimersAndConstants__n310_n20 = 7
} TimerN310_e;

typedef enum timerT311
{
    NR_UE_TimersAndConstants__t311_ms1000  = 0,
    NR_UE_TimersAndConstants__t311_ms3000  = 1,
    NR_UE_TimersAndConstants__t311_ms5000  = 2,
    NR_UE_TimersAndConstants__t311_ms10000 = 3,
    NR_UE_TimersAndConstants__t311_ms15000 = 4,
    NR_UE_TimersAndConstants__t311_ms20000 = 5,
    NR_UE_TimersAndConstants__t311_ms30000 = 6
} TimerT311_e;

typedef enum timerN311
{
    NR_UE_TimersAndConstants__n311_n1  = 0,
    NR_UE_TimersAndConstants__n311_n2  = 1,
    NR_UE_TimersAndConstants__n311_n3  = 2,
    NR_UE_TimersAndConstants__n311_n4  = 3,
    NR_UE_TimersAndConstants__n311_n5  = 4,
    NR_UE_TimersAndConstants__n311_n6  = 5,
    NR_UE_TimersAndConstants__n311_n8  = 6,
    NR_UE_TimersAndConstants__n311_n10 = 7
} TimerN311_e;

typedef enum timerT319
{
    NR_UE_TimersAndConstants__t319_ms100   = 0,
    NR_UE_TimersAndConstants__t319_ms200   = 1,
    NR_UE_TimersAndConstants__t319_ms300   = 2,
    NR_UE_TimersAndConstants__t319_ms400   = 3,
    NR_UE_TimersAndConstants__t319_ms600   = 4,
    NR_UE_TimersAndConstants__t319_ms1000  = 5,
    NR_UE_TimersAndConstants__t319_ms1500  = 6,
    NR_UE_TimersAndConstants__t319_ms2000  = 7
} TimerT319_e;

typedef struct ueTimersAndConstants {
    TimerT300_e  t300;
    TimerT301_e  t301;
    TimerT310_e  t310;
    TimerN310_e  n310;
    TimerT311_e  t311;
    TimerN311_e  n311;
    TimerT319_e  t319;
} UETimersAndConstants_t;





#define      CELL_RESERVED_FOR_OTHERUSE     (1<<0)
typedef struct  cellAccessInfo
{
    UINT16                  bitMask;
    UINT16                  plmnInfoNum;
    PlmnInformation_t       plmnInfo[MAX_PLMN];
    BOOL                    cellReservedForOtherUse;    /*option*/

} CellAccessInfo_t;

#define    RA_ASSOCIATION_PERIOD_INDEX         (1<<0)
#define    RA_SSB_OCCASION_MASK_INDEX          (1<<1)
typedef struct  siReqRes
{
    UINT16                  bitMask;
    UINT8                   raPreambleStartIndex;
    UINT8                   raAssociationPeriodIndex;   /*option*/
    UINT8                   raSsbOccasionMaskIndex;     /*option*/

} SiReqRes_t;

#define    PRACH_CONFIGURATION_INDEX         (1<<0)
#define    MSG1_FDM                          (1<<1)
#define    MSG1_FREQUENCYSTART               (1<<2)
#define    ZERO_COR_RELATION_ZONECONFIG      (1<<3)
#define    PREAMBLE_RECEIVED_TARGETPOWER     (1<<4)
#define    PREAMBLE_TRANS_MAX                (1<<5)
#define    POWER_RAMPING_STEP                (1<<6)
#define    RA_RESPONSE_WINDOW                (1<<7)

#define    SI_REQUEST_PERIOD                 (1<<8)
typedef struct  siRequestConfig
{
    UINT16                  bitMask;
    UINT8                   prach_ConfigurationIndex;       /*option*/
    UINT8                   msg1_FDM;                       /*option*/
    UINT16                  msg1_FrequencyStart;            /*option*/
    UINT8                   zeroCorrelationZoneConfig;      /*option*/
    INT16                   preambleReceivedTargetPower;    /*option*/
    UINT8                   preambleTransMax;               /*option*/
    UINT8                   powerRampingStep;               /*option*/
    UINT8                   raResponseWindow;               /*option*/
    UINT8                   ssbPerRachOccasion;
    UINT8                   siRequestPeriod;                /*option*/
    UINT16                  siRequestResourcesNum;
    SiReqRes_t              siRequestResources[MAX_SI_MESSAGE];
} SiRequestConfig_t;

typedef enum schInfoSiPeriod
{
    NR_SchedulingInfo__si_Periodicity_rf8  = 0,
    NR_SchedulingInfo__si_Periodicity_rf16 = 1,
    NR_SchedulingInfo__si_Periodicity_rf32 = 2,
    NR_SchedulingInfo__si_Periodicity_rf64 = 3,
    NR_SchedulingInfo__si_Periodicity_rf128    = 4,
    NR_SchedulingInfo__si_Periodicity_rf256    = 5,
    NR_SchedulingInfo__si_Periodicity_rf512    = 6
} SchInfoSiPeriod_e;

typedef enum sibType
{
    NR_SIB_TypeInfo__type_sibType2 = 0,
    NR_SIB_TypeInfo__type_sibType3 = 1,
    NR_SIB_TypeInfo__type_sibType4 = 2,
    NR_SIB_TypeInfo__type_sibType5 = 3,
    NR_SIB_TypeInfo__type_sibType6 = 4,
    NR_SIB_TypeInfo__type_sibType7 = 5,
    NR_SIB_TypeInfo__type_sibType8 = 6,
    NR_SIB_TypeInfo__type_sibType9 = 7
} SibType_e;

typedef enum sibAreaScope
{
    NR_SIB_TypeInfo__areaScope_true    = 0
} SibAreaScope_e;

#define         VALUE_TAG       (1<<0)
#define         AREA_SCOPE      (1<<1)

typedef struct sibTypeInfo
{
    UINT16              bitMask;
    SibType_e           type;
    UINT8               valueTag;       /*option*/
    SibAreaScope_e      areaScope;      /*option*/
} SibTypeInfo_t;

typedef struct  siSchInfo
{

    BOOL                    siBroadcastStatus;
    SchInfoSiPeriod_e       siPeriodicity;
    UINT16                  sibMappingNum;
    SibTypeInfo_t           sibMapping[MAX_SIB];

} SiSchInfo_t;

typedef enum nrControlResourceSet_cce_REG_MappingType_PR
{
	NrControlResourceSet_cce_REG_MappingType_PR_NOTHING,	/* No components present */
	NrControlResourceSet_cce_REG_MappingType_PR_interleaved,
	NrControlResourceSet_cce_REG_MappingType_PR_nonInterleaved
} NrControlResourceSet_cce_REG_MappingType_PR;

#define MAC_TCI_STATEID      64
#define NrControlResourceSetShiftIndexChosen      0x1
#define NrControlResourceSetTciPresentInDciChosen 0x2
#define NrControlResourceSetDmrsScramblingIDChosen 0x4
typedef struct  nrControlResourceSet
{
    UINT16                 bitmask;
    long                   controlResourceSetId;
    UINT64                   frequencyDomainResources;
	long	               duration;
	NrControlResourceSet_cce_REG_MappingType_PR present;
	union ControlResourceSet_cce_REG_MappingType_u
	{
		struct ControlResourceSet_cce_REG_MappingType_interleaved
		{
			long	 reg_BundleSize;
			long	 interleaverSize;
			long	 shiftIndex;        /* OPTIONAL */
		} nrInterleaved;
		int	 nonInterleaved;
	} choice;
	long	               precoderGranularity;
	UINT8                  tciPdcchToAddListNum;
	long                   tciStateIdAddList[MAC_TCI_STATEID];
	UINT8                  tciPdcchToReleaseListNum;
	long                   tciStateIdReleaseList[MAC_TCI_STATEID];
	long	               tci_PresentInDCI;	        /* OPTIONAL */
	long	               pdcch_DMRS_ScramblingID;	        /* OPTIONAL */
} NrControlResourceSet_t;

typedef struct nrofCandidates
{
    long     aggregationLevel1;
    long     aggregationLevel2;
    long     aggregationLevel4;
    long     aggregationLevel8;
    long     aggregationLevel16;
} NrofCandidates_t;

typedef enum nrSearchSpace_searchSpaceType_PR {
	NrSearchSpace_searchSpaceType_PR_NOTHING,	/* No components present */
	NrSearchSpace_searchSpaceType_PR_common,
	NrSearchSpace_searchSpaceType_PR_ue_Specific
} NrSearchSpace_searchSpaceType_PR;

#define	NrSearchSpaceTypeCommonDciFormat0_0_AndFormat1_0_Presence	1
#define	NrSearchSpaceTypeCommonDci_Format2_0_Presence	2
#define	NrSearchSpaceTypeCommonDci_Format2_1_Presence	4
#define	NrSearchSpaceTypeCommonDci_Format2_2_Presence	8
#define	NrSearchSpaceTypeCommonDci_Format2_3_Presence	16
typedef struct nrSearchSpaceType
{
    NrSearchSpace_searchSpaceType_PR present;
    union SearchSpace_searchSpaceType_u
    {
        struct SearchSpace_searchSpaceType_common
        {
			UINT16							 bitMask;
			struct SearchSpace_searchSpaceType_common_dci_Format0_0_AndFormat1_0
			{
			} dci_Format0_0_AndFormat1_0;//option

            struct SearchSpace_searchSpaceType_common_dci_Format2_0
            {
#define NrSearchSpaceTypeAggLevel1Chosen  1
#define NrSearchSpaceTypeAggLevel2Chosen  2
#define NrSearchSpaceTypeAggLevel4Chosen  4
#define NrSearchSpaceTypeAggLevel8Chosen  8
#define NrSearchSpaceTypeAggLevel16Chosen 16

				UINT8	bitMask;
                long    aggregationLevel1;  /* OPTIONAL */
                long    aggregationLevel2;  /* OPTIONAL */
                long    aggregationLevel4;  /* OPTIONAL */
                long    aggregationLevel8;  /* OPTIONAL */
                long    aggregationLevel16; /* OPTIONAL */
            } dci_Format2_0;//optional

			struct SearchSpace_searchSpaceType_common_dci_Format2_1
			{
			} dci_Format2_1;//optional

			struct SearchSpace_searchSpaceType_common_dci_Format2_2
			{
			} dci_Format2_2;//optional

            struct NrSearchSpace_searchSpaceType_common_dci_Format2_3
            {
#define NrSearchSpaceTypeDciFormat2_3Dummy1Chosen     1
				UINT8	bitMask;
                long     dummy1; /* OPTIONAL */
                long     dummy2;
            } dci_Format2_3;//optional
        } common;
     struct SearchSpace_searchSpaceType_specific
     {
        long     dci_Formats;
     }specific;

    } choice;
}NrSearchSpaceType_t;

typedef enum nrSearchSpaceMonitoringSlotPeriodicityAndOffset_PR
{
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_NOTHING,	/* No components present */
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl1,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl2,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl4,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl5,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl8,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl10,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl16,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl20,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl40,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl80,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl160,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl320,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl640,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl1280,
	NrSearchSpace_monitoringSlotPeriodicityAndOffset_PR_sl2560
} NrSearchSpaceMonitoringSlotPeriodicityAndOffset_PR;

#define NrSearchSpaceControlResIdChosen             0x1
#define NrSearchSpaceMonSlotPeriodAndOddsetChosen   0x2
#define NrSearchSpaceDurationChosen                 0x4
#define MONITORING_SYMBOLS_WITHIN_SLOT                 0x08
typedef struct  nrSearchSpace
{
    UINT16                 bitmask;
	long      	           searchSpaceId;
	long	               controlResourceSetId;	/* OPTIONAL */

	struct SearchSpaceMonitoringSlotPeriodicityAndOffset
	{
		NrSearchSpaceMonitoringSlotPeriodicityAndOffset_PR present;
		union SearchSpaceMonitoringSlotPeriodicityAndOffset_u
		{
			int	     sl1;
			long	 sl2;
			long	 sl4;
			long	 sl5;
			long	 sl8;
			long	 sl10;
			long	 sl16;
			long	 sl20;
			long	 sl40;
			long	 sl80;
			long	 sl160;
			long	 sl320;
			long	 sl640;
			long	 sl1280;
			long	 sl2560;
		} choice;
	} monitoringSlotPeriodicityAndOffset;/* OPTIONAL */

	long	               duration;	/* OPTIONAL */
	UINT16	               monitoringSymbolsWithinSlot;	/* OPTIONAL */
	NrofCandidates_t       nrofCandidates;
	NrSearchSpaceType_t    searchSpaceType;
} NrSearchSpace_t;

#define MAX_SEARCHSPACE_NUM   4

#define PdcchCfgCommonCtrlResSetZeroChosen    1
#define PdcchCfgCommonCtrlResSetChosen        2
#define PdcchCfgCommonSearchSpaceZeroChosen   4
#define PdcchCfgCommonSearchSpaceSIB1Chosen   8
#define PdcchCfgCommonSearchSpaceOtherSysInfoChosen   16
#define PdcchCfgCommonPagingSearchSpaceChosen 32
#define PdcchCfgCommonRaSearchSpaceChosen     64

typedef struct PDCCHCfgCommon
{

    UINT16                 bitmask;
    long                   controlResourceSetZero;	            /* OPTIONAL */
    NrControlResourceSet_t commonControlResourceSet;            /* OPTIONAL */
    long                   searchSpaceZero;	                    /* OPTIONAL */
    UINT8                  searchSpaceNum;
    NrSearchSpace_t        searchSpace[MAX_SEARCHSPACE_NUM];

	long	               searchSpaceSIB1;             	    /* OPTIONAL */
	long	               searchSpaceOtherSystemInformation;	/* OPTIONAL */
	long	               pagingSearchSpace;	                /* OPTIONAL */
	long	               raSearchSpace;                       /* OPTIONAL */
}Pdcch_Cfg_Common_t;

typedef enum setup_Release_PDCCH_PR
{
	Setup_Release_PDCCH_PR_NOTHING,	/* No components present */
	Setup_Release_PDCCH_PR_release,
	Setup_Release_PDCCH_PR_setup

}Setup_Release_PDCCH_PR;
typedef struct  pdcchCfgCommon
{
    Setup_Release_PDCCH_PR present;
    union Setup_Release_PDCCH_PR_u {
            UINT32 release;
            Pdcch_Cfg_Common_t setup;

    }choice;

} PdcchCfgCommon_t;

/* PUCCH-ConfigCommon */
#define PucchCfgCommonResourceCommonChosen    1
#define PucchCfgCommonHoppingIdChosen         2
#define PucchCfgCommonP0NominalChosen         4
typedef struct nrPucch_ConfigCommon
{
    UINT16                 bitmask;
    long	               pucchResourceCommon;	/* OPTIONAL */
    long	               pucchGroupHopping;
    long	               hoppingId;	/* OPTIONAL */
    long	               p0Nominal;	/* OPTIONAL */
}NrPucch_ConfigCommon_t;

typedef enum nrPucchCfgCommon_PR
{
	NrPucchCfgCommon_PR_NOTHING,	/* No components present */
	NrPucchCfgCommon_PR_release,
	NrPucchCfgCommon_PR_setup
}NrPucchCfgCommon_PR;

typedef struct nrPucchCfgCommon
{

	NrPucchCfgCommon_PR present;
	union NrPucchCfgCommon_u {
		int	 release;
		NrPucch_ConfigCommon_t	 setup;
	} choice;

} NrPucchCfgCommon_t;

#define PdschTimeDomainAllockOChosen    1
typedef struct  pdschTimeDomainAlloc
{
    UINT16                 bitmask;
	long	               k0;	/* OPTIONAL */
	long	               mappingType;
	long	               startSymbolAndLength;
} PdschTimeDomainAlloc_t;

#define PuschTimeDomainAllock2Chosen    1
typedef struct  puschTimeDomainAlloc
{
    UINT16                 bitmask;
	long	               k2;	/* OPTIONAL */
	long	               mappingType;
	long	               startSymbolAndLength;
} PuschTimeDomainAlloc_t;


#define MAX_TIME_DOMAIN_NUM    16
#define PdschTimeDomainAllocationChose   (1 << 0)
typedef struct  pdsch_Cfg_Common_t
{
      UINT16                 bitmask;
      UINT8                  timeDomainNum;
      PdschTimeDomainAlloc_t pdschTimeDomainAllocation[MAX_TIME_DOMAIN_NUM];  /* OPTIONAL */
} Pdsch_Cfg_Common_t;

typedef enum setup_Release_PDSCH_PR
{
	Setup_Release_PDSCH_PR_NOTHING,	/* No components present */
	Setup_Release_PDSCH_PR_release,
	Setup_Release_PDSCH_PR_setup
}Setup_Release_PDSCH_PR;

typedef struct  pdschCfgCommon
{
    Setup_Release_PDSCH_PR present;
    union Setup_Release_PDSCH_PR_u {
            UINT32 release;
            Pdsch_Cfg_Common_t setup;

    }choice;

} PdschCfgCommon_t;

typedef struct  nrBWP
{
    UINT16      locationAndBandwidth;
    UINT8       subcarrierSpacing;
    /*UINT8     cyclicPrefix;      extension*/
} NrBWP_t;

#define NrBwpDownLinkCommonPdcchCfgChosen  0x1
#define NrBwpDownLinkCommonPdschCfgChosen  0x2
typedef struct  nrBwpDownLinkCommon
{
    UINT16                 bitmask;
    NrBWP_t                bwp;
    PdcchCfgCommon_t       pdcchCfgCommon;	/* OPTIONAL */
    PdschCfgCommon_t       pdschCfgCommon;	/* OPTIONAL */
} NrBwpDownLinkCommon_t;

#define      ADDITIONAL_PMAX     (1<<0)
typedef struct  pmaxValue
{
    UINT16                  bitMask;
    INT8                    additionalPmax;             /*option*/
    UINT16                  additionalSpectrumEmission;
} PmaxValue_t;

#define     FREQ_BAND_INDICATOR_NR         (1<<0)
#define     PMAX_LIST                      (1<<1)
typedef struct  nrMultiBand
{
    UINT16                  bitMask;
    UINT16                  freqBandIndicatorNR;        /*option*/
    UINT16                  pmaxListNum;
    PmaxValue_t             pmaxList[MAX_NR_NS_PMAX];   /*option*/
} NrMultiBand_t;

typedef struct  specificCarrier
{
    UINT16                     offsetToCarrier;
    UINT8                      subcarrierSpacing;
    UINT16                     carrierBandwidth;
    /*UINT16                   txDirectCurrentLocation_v1530;  extension*/

} SpecificCarrier_t;

#define     ABSOLUTE_FREQUENCY_POINTA     (1<<0)
#define     PMAX                          (1<<1)

typedef struct  freqInfoUlSib
{
    UINT16                  bitMask;
    UINT16                  nrMulBandNum;
    NrMultiBand_t           nrMulBand[MAX_MULTI_BANDS];
    UINT32                  absoluteFrequencyPointA;        /*option*/
    UINT16                  speCarrierNum;
    SpecificCarrier_t		speCarrier[MAX_SCS];
	INT8					pMax;                           /*option*/
	/*UINT8					frequencyShift7p5khz;		extension*/
} FreqInfoUlSib_t;

/* RACH-ConfigGeneric */
typedef struct nrRachCfgGeneric_t
{
	long	 prach_ConfigurationIndex;
	long	 msg1_FDM;
	long	 msg1_FrequencyStart;
	long	 zeroCorrelationZoneConfig;
	long	 preambleReceivedTargetPower;
	long	 preambleTransMax;
	long	 powerRampingStep;
	long	 ra_ResponseWindow;
} NrRachCfgGeneric_t;

typedef enum nrRachCfgCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB
{
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_NOTHING,	/* No components present */
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneEighth,
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneFourth,
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_oneHalf,
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_one,
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_two,
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_four,
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_eight,
	NrRACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_PR_sixteen
} NrRachCfgCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_e;
typedef enum nrRachCfgCommonPrachRootSequenceIndex
{
	NrRACH_ConfigCommon_prach_RootSequenceIndex_PR_NOTHING,	/* No components present */
	NrRACH_ConfigCommon_prach_RootSequenceIndex_PR_l839,
	NrRACH_ConfigCommon_prach_RootSequenceIndex_PR_l139
} NrRachCfgCommonPrachRootSequenceIndex_e;

#define NrRachCfgCommonTotalNumberOfRaChosen        (1<<0)
#define NrRachCfgCommongroupBconfiguredChosen       (1<<1)
#define NrRachCfgCommonRsrpThresholdSSBChosen       (1<<2)
#define NrRachCfgCommonRsrpThresholdSSBSulChosen    (1<<3)
#define NrRachCfgCommonMsg1SubcarrierSpacingChosen  (1<<4)
#define NrRachCfgCommonMsg3TransformPrecoderChosen  (1<<5)
#define NrRachCfgCommonGroupBconfigChosen 			32
typedef struct RACH_Config_Common
{
    UINT16                 bitmask;
	NrRachCfgGeneric_t	   rachCfgGeneric;
	long	               totalNumberOfRA_Preambles;	/* OPTIONAL */
	struct RACH_ConfigCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB
	{
		NrRachCfgCommon_ssb_perRACH_OccasionAndCB_PreamblesPerSSB_e present;
		union ssbPerRachOccAndCBPreamblesPerSSB_u
		{
			long	 oneEighth;
			long	 oneFourth;
			long	 oneHalf;
			long	 one;
			long	 two;
			long	 four;
			long	 eight;
			long	 sixteen;
		} choice;
	} ssbPerRachOccAndCBPreamblesPerSSB;

	struct rachCfgCommonGroupBconfigured
	{
		long	 ra_Msg3SizeGroupA;
		long	 messagePowerOffsetGroupB;
		long	 numberOfRA_PreamblesGroupA;
	} groupBconfigured;/* OPTIONAL */

	long	        ra_ContentionResolutionTimer;
	long	        rsrp_ThresholdSSB;	/* OPTIONAL */
	long	        rsrp_ThresholdSSB_SUL;	/* OPTIONAL */
	struct rachCfgCommonPrachRootSequenceIndex
	{
		NrRachCfgCommonPrachRootSequenceIndex_e present;
		union rachCfgCommonPrachRootSequenceIndex_u
		{
			long	 l839;
			long	 l139;
		} choice;
	} prachRootSequenceIndex;
	long	 msg1_SubcarrierSpacing;/* OPTIONAL */
	long	 restrictedSetConfig;
	long	 msg3_transformPrecoder;/* OPTIONAL */

}rACH_Config_Common_t;
typedef enum setup_Release_903P7_PR
{
	NrRachCfgCommon_PR_NOTHING,	/* No components present */
	NrRachCfgCommon_PR_release,
	NrRachCfgCommon_PR_setup
}NrRachCfgCommon_PR;

typedef struct nrRachCfgCommon
{
	NrRachCfgCommon_PR present;
	union NrRachCfgCommon_PR_u {
		int	 release;
		rACH_Config_Common_t	 setup;
	} choice;
} NrRachCfgCommon_t;

/* PUSCH-ConfigCommon */
#define NrPuschCfgCommonGroupHoppingChosen    1
#define NrPuschCfgCommonMsg3DeltaChosen       2
#define NrPuschCfgCommonPoNominalChosen       4
#define NrPuschCfgCommonpuschTimeDomainAllocationChosen       8

typedef struct nrPusch_ConfigCommon
{
    UINT16                 bitmask;
	long	               groupHoppingEnabledTransformPrecoding;	/* OPTIONAL */
    long	               msg3DeltaPreamble;	/* OPTIONAL */
	long	               p0NominalWithGrant;	/* OPTIONAL */
    UINT8                  timeDomainNum;
    PuschTimeDomainAlloc_t puschTimeDomainAllocation[MAX_TIME_DOMAIN_NUM]; /* OPTIONAL */

}NrPusch_ConfigCommon_t;

typedef enum
{
	NrPuschCfgCommon_PR_NOTHING,	/* No components present */
	NrPuschCfgCommon_PR_release,
	NrPuschCfgCommon_PR_setup
}NrPuschCfgCommon_PR;
typedef struct nrPuschCfgCommon
{
	NrPuschCfgCommon_PR present;
	union NrPuschCfgCommon_u {
		int	 release;
		NrPusch_ConfigCommon_t	 setup;
	} choice;

} NrPuschCfgCommon_t;

#define InitialUlBwpRachCfgChosen     1
#define InitialUlBwpPuschCfgChosen    2
#define InitialUlBwpPucchCfgChosen    4
typedef struct  initialUlBwp
{
    UINT16                 bitmask;
    NrBWP_t                bwp;
    NrRachCfgCommon_t      rachCfgCommon;	/* OPTIONAL */
	NrPuschCfgCommon_t	   puschCfgCommon;	/* OPTIONAL */
	NrPucchCfgCommon_t	   pucchCfgCommon;	/* OPTIONAL */
} InitialUlBwp_t;

typedef struct  ulCfgCommonSIB
{
    FreqInfoUlSib_t         frequencyInfoUL;
    InitialUlBwp_t          initialUplinkBWP;
    UINT8                   timeAlignmentTimerCommon;
} UlCfgCommonSIB_t;

typedef struct  freqInfoDlSib
{
    UINT16                  frequencyBandListNum;
    NrMultiBand_t           frequencyBandList[MAX_MULTI_BANDS];
    UINT16                  offsetToPointA;
    UINT16                  speCarrierNum;
	SpecificCarrier_t		speCarrier[MAX_SCS];
} FreqInfoDlSib_t;

#define  FIRST_PDCCH_MONITORING_OCCASION_OF_PO_T  (1<<0)
typedef enum
{
	PagingFrameOffset_PR_NOTHING,	/* No components present */
	PagingFrameOffset_PR_oneT,
	PagingFrameOffset_PR_halfT,
	PagingFrameOffset_PR_quarterT,
	PagingFrameOffset_PR_oneEighthT,
	PagingFrameOffset_PR_oneSixteenthT,
} PagingFrameOffset_e;

typedef enum
{
    PDCCH_Monitoring_PR_NOTHING,   /* No components present */
    PDCCH_Monitoring_PR_sCS15KHZoneT,
    PDCCH_Monitoring_PR_sCS30KHZoneT_SCS15KHZhalfT,
    PDCCH_Monitoring_PR_sCS60KHZoneT_SCS30KHZhalfT_SCS15KHZquarterT,
    PDCCH_Monitoring_PR_sCS120KHZoneT_SCS60KHZhalfT_SCS30KHZquarterT_SCS15KHZoneEighthT,
    PDCCH_Monitoring_PR_sCS120KHZhalfT_SCS60KHZquarterT_SCS30KHZoneEighthT_SCS15KHZoneSixteenthT,
    PDCCH_Monitoring_PR_sCS120KHZquarterT_SCS60KHZoneEighthT_SCS30KHZoneSixteenthT,
    PDCCH_Monitoring_PR_sCS120KHZoneEighthT_SCS60KHZoneSixteenthT,
    PDCCH_Monitoring_PR_sCS120KHZoneSixteenthT,
} FirstPDCCH_MonitoringOccasionOfPO_e;

#define  MAX_PDCCH_MONITORING_OCCASION   4

typedef	struct  sCS15KHZoneT_s
{
	UINT16		   poNum;
	UINT16		   firstMonitorOccasionOfPO[MAX_PDCCH_MONITORING_OCCASION];
}SCS15KHZoneT_t;

typedef	struct  sCS30KHZoneT_SCS15KHZhalfT_s
{

	UINT16		   poNum;
	UINT16		   firstMonitorOccasionOfPO[MAX_PDCCH_MONITORING_OCCASION];

}sCS30KHZoneT_SCS15KHZhalfT_t;

typedef	struct  sCS60KHZoneT_SCS30KHZhalfT_SCS15KHZquarterT_s
{
	UINT16		   poNum;
	UINT16		   firstMonitorOccasionOfPO[MAX_PDCCH_MONITORING_OCCASION];

}sCS60KHZoneT_SCS30KHZhalfT_SCS15KHZquarterT_t;

typedef	struct  sCS120KHZoneT_SCS60KHZhalfT_SCS30KHZquarterT_SCS15KHZoneEighthT_s
{
	UINT16		   poNum;
	UINT16		   firstMonitorOccasionOfPO[MAX_PDCCH_MONITORING_OCCASION];

}sCS120KHZoneT_SCS60KHZhalfT_SCS30KHZquarterT_SCS15KHZoneEighthT_t;

typedef	struct  sCS120KHZhalfT_SCS60KHZquarterT_SCS30KHZoneEighthT_SCS15KHZoneSixteenthT_s
{
	UINT16		   poNum;
	UINT16		   firstMonitorOccasionOfPO[MAX_PDCCH_MONITORING_OCCASION];

}sCS120KHZhalfT_SCS60KHZquarterT_SCS30KHZoneEighthT_SCS15KHZoneSixteenthT_t;

typedef	struct  sCS120KHZquarterT_SCS60KHZoneEighthT_SCS30KHZoneSixteenthT_s
{
	UINT16		   poNum;
	UINT16		   firstMonitorOccasionOfPO[MAX_PDCCH_MONITORING_OCCASION];

}sCS120KHZquarterT_SCS60KHZoneEighthT_SCS30KHZoneSixteenthT_t;

typedef	struct  sCS120KHZoneEighthT_SCS60KHZoneSixteenthT_s
{
	UINT16		   poNum;
	UINT16		   firstMonitorOccasionOfPO[MAX_PDCCH_MONITORING_OCCASION];

}sCS120KHZoneEighthT_SCS60KHZoneSixteenthT_t;

typedef	struct  sCS120KHZoneSixteenthT_s
{
	UINT16		   poNum;
	UINT16		   firstMonitorOccasionOfPO[MAX_PDCCH_MONITORING_OCCASION];

}sCS120KHZoneSixteenthT_t;

#define FirstPDCCH_MonitoringOccasionOfpoChosen  (1 << 0)
typedef struct  pcchConfig
{
    UINT16         bitMask;
    UINT8          defaultPagingCycle;

    struct PagingFrameOffset
    {   PagingFrameOffset_e		   present;
        union PagingFrame {
        INT32          oneT;
        UINT8          halfT;
        UINT8          quarterT;
        UINT8          oneEighthT;
        UINT8          oneSixteenthT;
        }choice;
    }pagingFrameOffset_t;
    UINT8          ns;
    struct FirstPDCCH_MonitoringOccasionOfPO
    {   FirstPDCCH_MonitoringOccasionOfPO_e		   present;
        union PDCCH_MonitoringOccasion {

			SCS15KHZoneT_t	SCS15KHZoneT;
			sCS30KHZoneT_SCS15KHZhalfT_t sCS30KHZoneT_SCS15KHZhalfT;
			sCS60KHZoneT_SCS30KHZhalfT_SCS15KHZquarterT_t	sCS60KHZoneT_SCS30KHZhalfT_SCS15KHZquarterT;
			sCS120KHZoneT_SCS60KHZhalfT_SCS30KHZquarterT_SCS15KHZoneEighthT_t	sCS120KHZoneT_SCS60KHZhalfT_SCS30KHZquarterT_SCS15KHZoneEighthT;
			sCS120KHZhalfT_SCS60KHZquarterT_SCS30KHZoneEighthT_SCS15KHZoneSixteenthT_t	sCS120KHZhalfT_SCS60KHZquarterT_SCS30KHZoneEighthT_SCS15KHZoneSixteenthT;
			sCS120KHZquarterT_SCS60KHZoneEighthT_SCS30KHZoneSixteenthT_t sCS120KHZquarterT_SCS60KHZoneEighthT_SCS30KHZoneSixteenthT;
			sCS120KHZoneEighthT_SCS60KHZoneSixteenthT_t sCS120KHZoneEighthT_SCS60KHZoneSixteenthT;
			sCS120KHZoneSixteenthT_t sCS120KHZoneSixteenthT;
        }choice;
    }firstPDCCH_MonitoringOccasionOfPO_t;    /*option*/

} PcchConfig_t;

typedef struct  dlCfgCommonSIB
{
    FreqInfoDlSib_t          frequencyInfoDL;
    NrBwpDownLinkCommon_t    initialDownlinkBWP;
    UINT8                    modificationPeriodCoeff;
	PcchConfig_t	 		 pcchConfig;
} DlCfgCommonSIB_t;

typedef struct  tddUlDlPattern
{
    UINT8       dlULTransmissionPeriodicity;
    UINT16      nrofDownlinkSlots;
    UINT8       nrofDownlinkSymbols;
    UINT16      nrofUplinkSlots;
    UINT8       nrofUplinkSymbols;
    /*UINT8     dlULTransmissionPeriodicity_v1530;     extension*/
} TddUlDlPattern_t;


typedef struct  tddUlDlCfgCom
{
    UINT8                    referenceSubcarrierSpacing;
    TddUlDlPattern_t         pattern1;
	/*TddUlDlPattern_t	 	 pattern2;					extension*/
} TddUlDlCfgCom_t;


#define        UPLINK_CONFIG_COMMON         (1<<0)
#define        SUPPLEMENTARY_UPLINK         (1<<1)
#define        NTIMING_ADVANCE_OFFSET       (1<<2)
#define        GROUP_PRESENCE               (1<<3)
#define        TDD_ULDL_CFG_COMMON          (1<<4)
typedef struct  servingCellCfg
{
    UINT16                   bitMask;
    DlCfgCommonSIB_t         downlinkConfigCommon;
    UlCfgCommonSIB_t         uplinkConfigCommon;        /*option*/
    UlCfgCommonSIB_t         supplementaryUplink;       /*option*/
	UINT8					 nTimingAdvanceOffset;      /*option*/
    UINT8                    inOneGroup;
    UINT8                    groupPresence;             /*option*/
    UINT8                    ssbPeriodServingCell;
    TddUlDlCfgCom_t          tddUlDlCfgCommon;          /*option*/
    INT8                     ssPBCHBlockPower;
} ServingCellCfg_t;

typedef struct  uACBarringPerCat
{
    UINT8                       accessCategory;
    UINT8                       uacBarringInfoSetIndex;
} UACBarringPerCat_t;

#define UAC_AC_BARRING_LIST_TYPE  (1 << 0)

typedef enum UacAcBarringListType_PR {
	UacImplicitACBarringList_UacExplicitAcBarringListType_PR_NOTHING,	/* No components present */
	UacImplicitACBarringList_UacExplicitAcBarringListType_PR_UacImplicitACBarringList,
	UacImplicitACBarringList_UacExplicitAcBarringListType_PR_UacExplicitAcBarringList
} UacImplicitACBarringList_UacExplicitAcBarringList_PR;


typedef struct  uACBarringPerPLMN
{
    UINT16                     bitMask;
    UINT8                      plmnIdentityIndex;
    UINT16                     BarringListNum;
    UacImplicitACBarringList_UacExplicitAcBarringList_PR  present;
    union UacAcBarringListType_u {
    UINT8                      uacImplicitACBarringList[MAX_ACCESS_CAT - 1];
    UACBarringPerCat_t         uacExplicitAcBarringList[MAX_ACCESS_CAT - 1];
    }choice;                                    /*option*/
} UACBarringPerPLMN_t;

/***
typedef struct  uACBarringPerPLMN
{
    UINT8                      plmnIdentityIndex;
    UINT8                      present;
    UINT8                      uacImplicitACBarringList[MAX_ACCESS_CAT - 1];
    UACBarringPerCat_t         uacExplicitAcBarringList[MAX_ACCESS_CAT - 1];

} UACBarringPerPLMN_t;


***/


typedef struct  uACBarringInfoSet
{
    UINT8                   uacBarringFactor;
    UINT8                   uacBarringTime;
    UINT8                   uacBarringForAccessIdentity;
} UACBarringInfoSet_t;

#define UAC_BARRING_FOR_COMMON     		   (1 << 0)
#define UAC_BARRING_PER_PLMN_LIST  		   (1 << 1)
#define UAC_INDIVIDUAL_PLMN_LIST  		   (1 << 2)
#define UAC_ACT1_ESCLECT_ASSISTANCE_INFO   (1 << 3)

typedef enum uac_AccessCategory1_SelectionAssistanceInfo_PR
{
	uac_AccessCategory1_SelectionAssistanceInfo_nonthing,//guotingting
	uac_AccessCategory1_SelectionAssistanceInfo_plmnCommon,
    uac_AccessCategory1_SelectionAssistanceInfo_individualPLMNList
} Uac_AccessCategory1_SelectionAssistanceInfo_PR;


typedef struct  sib1UacBarringInfo
{
    UINT16                  bitMask;
    UINT16                  uac_BarringForCommonNUM;
    UACBarringPerCat_t      uac_BarringForCommon[MAX_ACCESS_CAT - 1]; /*option*/
    UINT16                  uacBarringPerPLMNListNUM;
    UACBarringPerPLMN_t     uacBarringPerPLMNList[MAX_PLMN];          /*option*/
    UINT16                  uacBarringInfoSetListNUM;
    UACBarringInfoSet_t     uacBarringInfoSetList[MAX_BARRING_SET];
    Uac_AccessCategory1_SelectionAssistanceInfo_PR    present;
    UINT16                  individualPLMNListNUM;
    union uac_AccessCategory1_SelectionAssistanceInfo
    {
        UINT8                   plmnCommon;
        UINT8                   individualPLMNList[MAX_PLMN];

    }choice;                                                         /*option*/

} Sib1UacBarringInfo_t;



#define Q_RXLEVMIN_OFFSETD        (1 << 0)
#define Q_RXLEVMIN_SUL            (1 << 1)
#define Q_QUAL_MIN                (1 << 2)
#define Q_QUALMIN_OFFSET          (1 << 3)
#define CONN_EST_FAILURE_CTRL     (1 << 4)
#define	SI_SCHE_LIST_PRESENCE	  (1 << 5)
#define SI_SCHEDUL_INFO           (1 << 6)
#define SI_REQ_CFG                (1 << 7)
#define SI_REQ_CFGSUL             (1 << 8)
#define SYSTEM_INFORMATION_AREAID (1 << 9)
#define SERVING_CELL_CFGCOMMON    (1 << 10)
#define IMS_EMERGENCY_SUPPORT     (1 << 11)
#define E_CALL_OVERIMS_SUPPORT    (1 << 12)
#define UE_TIMERS_ANDCONSTS       (1 << 13)
#define SIB1_UAC_BARINFO          (1 << 14)
#define USEFULL_RESUMEID          (1 << 15)


typedef struct sib1
{
    UINT16                              bitMask;
    INT8                                qRxLevMin;
    UINT8                               qRxLevMinOffsetd;               /*option*/
    INT8                                qRxLevMinSUL;                   /*option*/
    INT8                                qQualMin;                       /*option*/
    UINT8                               qQualMinOffset;                 /*option*/
	CellAccessInfo_t	 				cellAccessRelateInfo;
	ConnEstFailCtrl_t					connEstFailureCtrl;             /*option*/
    UINT8                               siWindowLen;
	UINT16								siNum;
    SiSchInfo_t                         siSchedulInfo[MAX_SI_MESSAGE];  /*option*/
    SiRequestConfig_t                   siReqCfg;                       /*option*/
    SiRequestConfig_t                   siReqCfgSul;                    /*option*/
    UINT32                              systemInformationAreaID;        /*option*/
	ServingCellCfg_t					servingCellCfgCommon;           /*option*/
    BOOL                                ims_EmergencySupport;           /*option*/
    BOOL                                eCallOverIMS_Support;           /*option*/
    UETimersAndConstants_t              ueTimersAndConsts;              /*option*/
    Sib1UacBarringInfo_t                sib1UacBarInfo;                 /*option*/
    BOOL                                useFullResumeID;                /*option*/
}Sib1_t;

/**********************        Sib2_t       ************************/
typedef enum cmSib2QHyst
{
	qHystdB0 	= 0,
	qHystdB1 	= 1,
	qHystdB2 	= 2,
	qHystdB3 	= 3,
	qHystdB4	= 4,
	qHystdB5	= 5,
	qHystdB6	= 6,
	qHystdB8	= 7,
	qHystdB10	= 8,
	qHystdB12	= 9,
	qHystdB14	= 10,
	qHystdB16	= 11,
	qHystdB18	= 12,
	qHystdB20	= 13,
	qHystdB22	= 14,
	qHystdB24	= 15
}CmSib2QHyst_e;


typedef enum cmSib2SfMedium
{
	qHystSFdBMedium0 	= 0,
	qHystSFdBMedium2	= 1,
	qHystSFdBMedium4	= 2,
	qHystSFdBMedium6 	= 3
}CmSib2SfMedium_e;

typedef enum cmSib2SfHigh
{
	qHystSFdBHigh0 		= 0,
	qHystSFdBHigh2 		= 1,
	qHystSFdBHigh4 		= 2,
	qHystSFdBHigh6 		= 3
}CmSib2SfHigh_e;

typedef struct cmSib2QHystSf
{
	CmSib2SfMedium_e 	sfMedium;
	CmSib2SfHigh_e 		sfHigh;
}CmSib2QHystSf_t;


typedef enum cmSib2TEvaluation
{
	tEvaluationS30 		= 0,
	tEvaluationS60 		= 1,
	tEvaluationS120 	= 2,
	tEvaluationS180 	= 3,
	tEvaluationS240 	= 4,
	tEvaluationSpare3	= 5,
	tEvaluationSpare2 	= 6,
	tEvaluationSpare1 	= 7
}CmSib2TEvaluation_e;

typedef enum cmSib2THystNormal
{
	tHystNormalS30 		= 0,
	tHystNormalS60 		= 1,
	tHystNormalS120 	= 2,
	tHystNormalS180 	= 3,
	tHystNormalS240 	= 4,
	tHystNormalSpare3	= 5,
	tHystNormalSpare2 	= 6,
	tHystNormalSpare1 	= 7
}CmSib2THystNormal_e;


typedef struct cmSib2MobilityStateParameters
{
	CmSib2TEvaluation_e  tEvaluation;
	CmSib2THystNormal_e  tHystNormal;
	UINT8 				 nCellChangeMedium;      /*1-16*/
	UINT8 				 nCellChangeHigh;		 /*1-16*/
}CmSib2MobilityStateParameters_t;


typedef struct cmSib2SpeedStateReselectionPars
{
	CmSib2MobilityStateParameters_t 	mobilityStateParameters;
	CmSib2QHystSf_t 					qHystSF;
}CmSib2SpeedStateReselectionPars_t;

#define THRESHOLD_RSRP_PRESENT                 (1 << 0)
#define THRESHOLD_PSRQ_PRESENT        		   (1 << 1)
#define THRESHOLD_SINR_PRESENT           	   (1 << 2)
typedef struct cmSib2ThresholdNr
{
	UINT16		bitMask;
	UINT8 		thresholdRSRP;    		/*0-127 OPTIONAL*/
	UINT8		thresholdRSRQ;			/*0-127 OPTIONAL*/
	UINT8   	thresholdSINR;			/*0-127 OPTIONAL*/
}CmSib2ThresholdNr_t;

typedef enum cmSib2QOffsetRange
{
	sib2qOffsetRangeMinus24  = 0,
	sib2qOffsetRangeMinus22  = 1,
	sib2qOffsetRangeMinus20  = 2,
	sib2qOffsetRangeMinus18  = 3,
	sib2qOffsetRangeMinus16  = 4,
	sib2qOffsetRangeMinus14  = 5,
	sib2qOffsetRangeMinus12  = 6,
	sib2qOffsetRangeMinus10  = 7,
	sib2qOffsetRangeMinus8   = 8,
	sib2qOffsetRangeMinus6   = 9,
	sib2qOffsetRangeMinus5   = 10,
	sib2qOffsetRangeMinus4   = 11,
	sib2qOffsetRangeMinus3   = 12,
	sib2qOffsetRangeMinus2   = 13,
	sib2qOffsetRangeMinus1   = 14,
	sib2qOffsetRangePlus0    = 15,
	sib2qOffsetRangePlus1	 = 16,
	sib2qOffsetRangePlus2	 = 17,
	sib2qOffsetRangePlus3	 = 18,
	sib2qOffsetRangePlus4	 = 19,
	sib2qOffsetRangePlus5	 = 20,
	sib2qOffsetRangePlus6	 = 21,
	sib2qOffsetRangePlus8	 = 22,
	sib2qOffsetRangePlus10   = 23,
	sib2qOffsetRangePlus12   = 24,
	sib2qOffsetRangePlus14   = 25,
	sib2qOffsetRangePlus16   = 26,
	sib2qOffsetRangePlus18   = 27,
	sib2qOffsetRangePlus20	 = 28,
    sib2qOffsetRangePlus22   = 29,
	sib2qOffsetRangePlus24	 = 30,

}CmSib2QOffsetRange_e;

#define NROF_SS_BLOCKS_TO_AVERAGE_PRESENT                 (1 << 0)
#define ABS_THRESH_SS_BLOCKS_CONSOLIDATION_PRESENT        (1 << 1)
#define RANGE_TO_BEST_CELL_PRESENT           			  (1 << 2)
#define SPEED_STATE_RESELECTION_PARS_PRESENT         	  (1 << 3)
typedef struct cmSib2CellReselectionInfoCommon
{
	UINT16								bitMask;
	UINT8 								nrofSsBlocksToAverage;               /*2-16 OPTIONAL*/
	CmSib2ThresholdNr_t 				absThreshSsBlocksConsolidation;		 /*OPTIONAL*/
	CmSib2QOffsetRange_e 				rangeToBestCell;					 /*OPTIONAL*/
	CmSib2QHyst_e 						qHyst;
	CmSib2SpeedStateReselectionPars_t   speedStateReselectionPars;
} CmSib2CellReselectionInfoCommon_t;

typedef enum cmSib2CellReselectionSubPriority
{
	cellReselectionSubPriorityoDot2	= 0,
	cellReselectionSubPriorityoDot4	= 1,
	cellReselectionSubPriorityoDot6	= 2,
	cellReselectionSubPriorityoDot8	= 3
}CmSib2CellReselectionSubPriority_e;

#define CM_SIB2_RESELECT_SERV_FREQ_SNON_INTRA_SEARCH_P        (1 << 0)
#define CM_SIB2_RESELECT_SERV_FREQ_SNON_INTRA_SEARCH_Q        (1 << 1)
#define CM_SIB2_RESELECT_SERV_FREQ_THRESH_SERV_LOWQ           (1 << 2)
#define CM_SIB2_RESELECT_SERV_FREQ_SUB_PRIORITY         	  (1 << 3)
typedef struct cmSib2CellReselectionServingFreqInfo
{
	UINT16			   bitMask;
	UINT8 			   sNonIntraSearchP; 		 //0-31
	UINT8 	           sNonIntraSearchQ;		 //0-31
	UINT8 			   threshServingLowP;		 //0-31
	UINT8 			   threshServingLowQ;		 //0-31
	UINT8 		   	   cellReselectionPriority;  //0-7
	CmSib2CellReselectionSubPriority_e cellReselectionSubPriority;
} CmSib2CellReselectionServingFreqInfo_t;


typedef struct cmSib2SsRssiMeasurement
{
	UINT8 		measurementSlots[10];			//BIT STRING SIZE(1-80)
	UINT8 		endSymbol;				//0-3
} CmSib2SsRssiMeasurement_t;


typedef struct cmSib2NrNsPmaxValue
{
	INT8 		additionalPmax;  			  /*-30~30   OPTIONAL*/
	UINT8 		additionalSpectrumEmission;   /*0-7*/
} CmSib2NrNsPmaxValue_t;


typedef struct cmSib2NrNsPmaxList
{
	CmSib2NrNsPmaxValue_t nRNsPmaxList[MAX_NR_NS_PMAX];
} CmSib2NrNsPmaxList_t;


typedef struct cmSib2NrMultiBandInfo
{
	UINT16 					freqBandIndicatorNR; 		//1-1024
	CmSib2NrNsPmaxList_t 	nRNsPmaxList;
} CmSib2NrMultiBandInfo_t;


typedef struct cmSib2MultiFrequencyBandListNrSib
{
	CmSib2NrMultiBandInfo_t multiFrequencyBandListNrSib[MAX_MULTI_BANDS];

} CmSib2MultiFrequencyBandListNrSib_t;


typedef enum cmSib2Duration
{
	durationSf1 = 0,
	durationSf2 = 1,
	durationSf3 = 2,
	durationSf4 = 3,
	durationSf5 = 4,
}CmSib2Duration_e;

typedef enum cmSib2SsMtcPresent
{
	CM_SIB2_SSB_MTC_NOTHING = 0,
	CM_SIB2_SSB_MTC_SF5 	= 1,
	CM_SIB2_SSB_MTC_SF10 	= 2,
	CM_SIB2_SSB_MTC_SF20 	= 3,
	CM_SIB2_SSB_MTC_SF40 	= 4,
	CM_SIB2_SSB_MTC_SF80 	= 5,
	CM_SIB2_SSB_MTC_SF160 	= 6,
}CmSib2SsMtcPresent_e;

typedef struct cmSib2SsbMtc  //choice sf5-sf160
{
	CmSib2SsMtcPresent_e present;
	UINT8 sf5;   //0-4
	UINT8 sf10;	 //0-9
	UINT8 sf20;	 //0-19
	UINT8 sf40;	 //0-39
	UINT8 sf80;	 //0-79
	UINT8 sf160; //0-159
	CmSib2Duration_e duration;

} CmSib2SsbMtc_t;

typedef enum cmSib2SsbToMeasurePresent
{
	CM_SIB2_SSB_TO_MEASURE_NOTHING 	= 0,
	CM_SIB2_SSB_TO_MEASURE_SHORT_BITMAP 	= 1,
	CM_SIB2_SSB_TO_MEASURE_MEDIUM_BITMAP 	= 2,
	CM_SIB2_SSB_TO_MEASURE_LONG_BITMAP 	= 3,
}CmSib2SsbToMeasurePresent_e;

typedef struct cmSib2SsbToMeasure
{
	CmSib2SsbToMeasurePresent_e 	present;
	UINT8 	shortBitmap;      	//BIT STRING SIZE(4)
	UINT8 	mediumBitmap;     	//BIT STRING SIZE(8)
	UINT64 	longBitmap;			//BIT STRING SIZE(64)

} CmSib2SsbToMeasure_t;

#define CM_INTRA_FREQ_CELL_RESELECT_QRX_LEV_MIN_SUL_PRESENT               	(1 << 0)
#define CM_INTRA_FREQ_CELL_RESELECT_QUAL_MIN_PRESENT        				(1 << 1)
#define CM_INTRA_FREQ_CELL_RESELECT_SINTRA_SEARCH_Q_PRESENT           	 	(1 << 2)
#define CM_INTRA_FREQ_CELL_RESELECT_FREQUENCY_BAND_LIST_PRESENT         	(1 << 3)
#define CM_INTRA_FREQ_CELL_RESELECT_FREQUENCY_BAND_LIST_SUL_PRESENT         (1 << 4)
#define CM_INTRA_FREQ_CELL_RESELECT_PMAX_PRESENT         	  			 	(1 << 5)
#define CM_INTRA_FREQ_CELL_RESELECT_CM_SIB2_SSB_MTC_PRSENT         	  	 	(1 << 6)
#define CM_INTRA_FREQ_CELL_RESELECT_CM_SIB2_SS_RSSI_MEASUREMENT_PRSENT  	(1 << 7)
#define CM_INTRA_FREQ_CELL_RESELECT_CM_SIB2_SSB_TO_MEASURE_PRSENT  	 		(1 << 8)
typedef struct cmSib2IntraFreqCellReselectionInfo
{
	UINT16 									bitMask;
	INT8 				  					qRxLevMin; 			//-70~-22
	INT8				  					qRxLevMinSUL;		//-70~-22
	INT8				  					qQualMin;			//-34~-3
	UINT8  				  					sIntraSearchP;    	//0-31
	UINT8				  					sIntraSearchQ;		//0-31
	UINT8				  					tReselectionNR;		//0-7
	CmSib2MultiFrequencyBandListNrSib_t 	frequencyBandList;
	CmSib2MultiFrequencyBandListNrSib_t 	frequencyBandListSUL;
	INT8                      				pMax;         		//-30-33
	CmSib2SsbMtc_t            				smtc;
	CmSib2SsRssiMeasurement_t 				ssRssiMeasurement ;
	CmSib2SsbToMeasure_t      				ssbToMeasure;
	BOOL                      				deriveSSBIndexFromCell;
} CmSib2IntraFreqCellReselectionInfo_t;

typedef struct sib2
{
	CmSib2CellReselectionInfoCommon_t 		 cellReselectionCommon;
	CmSib2CellReselectionServingFreqInfo_t   cellReselectionServingFreq;
	CmSib2IntraFreqCellReselectionInfo_t  	 intraFreqCellReselection;
}Sib2_t;

/**********************        Sib3_t       ************************/
typedef enum cmSib3QOffsetRange
{
	sib3qOffsetRangeMinus24  = 0,
	sib3qOffsetRangeMinus22  = 1,
	sib3qOffsetRangeMinus20  = 2,
	sib3qOffsetRangeMinus18  = 3,
	sib3qOffsetRangeMinus16  = 4,
	sib3qOffsetRangeMinus14  = 5,
	sib3qOffsetRangeMinus12  = 6,
	sib3qOffsetRangeMinus10  = 7,
	sib3qOffsetRangeMinus8   = 8,
	sib3qOffsetRangeMinus6   = 9,
	sib3qOffsetRangeMinus5   = 10,
	sib3qOffsetRangeMinus4   = 11,
	sib3qOffsetRangeMinus3   = 12,
	sib3qOffsetRangeMinus2   = 13,
	sib3qOffsetRangeMinus1   = 14,
	sib3qOffsetRangePlus0    = 15,
	sib3qOffsetRangePlus1	 = 16,
	sib3qOffsetRangePlus2	 = 17,
	sib3qOffsetRangePlus3	 = 18,
	sib3qOffsetRangePlus4	 = 19,
	sib3qOffsetRangePlus5	 = 20,
	sib3qOffsetRangePlus6	 = 21,
	sib3qOffsetRangePlus8	 = 22,
	sib3qOffsetRangePlus10   = 23,
	sib3qOffsetRangePlus12   = 24,
	sib3qOffsetRangePlus14   = 25,
	sib3qOffsetRangePlus16   = 26,
	sib3qOffsetRangePlus18   = 27,
	sib3qOffsetRangePlus20	 = 28,
    sib3qOffsetRangePlus22   = 29,
	sib3qOffsetRangePlus24	 = 30
}CmSib3QOffsetRange_e;

#define CM_INTRA_FREQ_NEIGH_CELL_QRX_LEV_MIN_OFFSET_CELL             (1 << 0)
#define CM_INTRA_FREQ_NEIGH_CELL_QRX_LEV_MIN_OFFSET_SUL_CELL     	 (1 << 1)
#define CM_INTRA_FREQ_NEIGH_CELL_QUAL_MIN_OFFSET_CELL           	 (1 << 2)
typedef struct cmSib3IntraFreqNeighCellInfo
{
	UINT32 					bitMask;
	UINT16  				physCellId; 		    //0-1007
	CmSib3QOffsetRange_e 	qOffsetCell;
	UINT8 					qRxLevMinOffsetCell;    //1-8
	UINT8					qRxLevMinOffsetCellSUL; //1-8
	UINT8 					qQualMinOffsetCell;		//1-8

} CmSib3IntraFreqNeighCellInfo_t;


typedef struct cmSib3IntraFreqNeighCellList
{
	UINT32						   neighNum;
	CmSib3IntraFreqNeighCellInfo_t intraFrequenceNeighCellList[MAXCELLINTRA];

} CmSib3IntraFreqNeighCellList_t;


typedef enum cmSib3Range
{
		rangeN4 	 = 0,
		rangeN8 	 = 1,
		rangeN12 	 = 2,
		rangeN16 	 = 3,
		rangeN24 	 = 4,
		rangeN32 	 = 5,
		rangeN48 	 = 6,
		rangeN64 	 = 7,
		rangeN84	 = 8,
		rangeN96 	 = 9,
		rangeN128 	 = 10,
		rangeN168 	 = 11,
		rangeN252 	 = 12,
		rangeN504 	 = 13,
		rangeN1008 	 = 14,
		rangeSpare1  = 15,
}CmSib3Range_e;

#define CM_SIB3_PCI_RANGE             (1 << 0)
typedef struct cmSib3PciRange
{
	UINT32		   bitMask;
	UINT16         physCellId; //0-1007
	CmSib3Range_e  range;
} CmSib3PciRange_t;


typedef struct cmSib3IntraFreqBlackCellList
{
	UINT32			 blackNum;
	CmSib3PciRange_t intraFrequenceBlackCellList[MAXCELLBLACK];

} CmSib3IntraFreqBlackCellList_t;

#define CM_SIB3_INTRA_FREQ_NEIGH_CELL_LIST               (1 << 0)
#define CM_SIB3_INTRA_FREQ_BLACK_CELL_LIST               (1 << 1)
typedef struct sib3
{
	UINT16							bitMask;
	CmSib3IntraFreqNeighCellList_t  intraFreqNeighCell;
	CmSib3IntraFreqBlackCellList_t 	intraFreqBlackCell;
}Sib3_t;

/**********************     SystemInfo_t    ************************/
typedef struct systemInfo
{
		Sib2_t	 siSib2;
		Sib3_t	 siSib3;
#if 0
		Sib4_t	 siSib4;
		Sib5_t	 siSib5;
		Sib6_t	 siSib6;
		Sib7_t	 siSib7;
		Sib8_t	 siSib8;
		Sib9_t	 siSib9;
#endif
}SystemInfo_t;

/**********************     SiConfig_t    ************************/
typedef struct siConfig
{
	Mib_t			 mibCfg;
	Sib1_t			 sib1Cfg;
	Sib2_t	 		 sib2Cfg;
	Sib3_t	 		 sib3Cfg;
	SystemInfo_t	 si1Cfg;
	SystemInfo_t	 si2Cfg;
	UINT8			 sib1Flag;
	UINT8	 		 siFlag;
	UINT8	 		 pagingFlag;
#if 0
	Sib4_t	 		 sib4Cfg;
	Sib5_t	 		 sib5Cfg;
	Sib6_t	 		 sib6Cfg;
	Sib7_t	 		 sib7Cfg;
	Sib8_t	 		 sib8Cfg;
	Sib9_t	 		 sib9Cfg;
	SystemInfo_t	 si3;
	SystemInfo_t	 si4;
	SystemInfo_t	 si5;
	SystemInfo_t	 si6;
	SystemInfo_t	 si7;
	SystemInfo_t	 si8;
#endif
} SiConfig_t;

typedef struct ngapConfig
{
	UINT32				gNBId;							/* Global Ran Node ID of one gNB */
	NgapRanName_t		ranNodeName;					/* name of one gNB */
	IpAddress_t			ranNodeIp;						/* IP Address of gNB */
} NGAPConfig_t;
/**********************     OamCuCpConfig_t    ************************/
typedef struct
{
    UINT64        gnbDuId;
    IpAddress_t   gnbDuIp;/* IP Address of DU */
    UCHAR         gnbDuName[MAX_GNB_DU_NAME];

}F1apDuInfo_t;

typedef struct f1apConfig
{
    UINT32       gNBId;

    UINT64        gnbCuId;
    IpAddress_t   gnbCuIp;/* IP Address of CU */
    UCHAR         gnbCuName[MAX_GNB_CU_NAME];
	UINT8		  gnbDuNum;
	F1apDuInfo_t  gnbDuCfg[MAX_GNB_DU_NUM];
} F1APConfig_t;

/**
 * @struct Transmission BandWidth
   This structure is the Transmission BandWidth of  Cell Configuration
*/
typedef struct transBandWidth
{
    long	          nrScs;
    long              nrb;
} TransBandWidth_t;

/**
 * @struct SULInfo
   This structure is the sul Info of  Cell Configuration
*/
typedef struct sulInfo
{
    UINT32            sulArfcn;
    TransBandWidth_t  sulTransBW;
} SulInfo_t;

/**
 * @struct FreqBand
   This structure is the freq Band of  Cell Configuration
*/
typedef struct freqBand
{
    UINT32             nrFreqBand;
    UINT8              supportedSulBandNum;
    UINT32             sulBand[MAX_NR_CELL_BANDS];
} FreqBand_t;

/**
 * @struct FreqInfo
   This structure is the freq Info of  Cell Configuration
*/
#define FreqInfoSulInfoChosen       0x01
typedef struct freqInfo
{
    UINT16             bitmask;
    UINT32             nrArfcn;
    SulInfo_t          sulInfo;
    UINT8              freqBandNum;
    FreqBand_t         freqBandItem[MAX_NR_CELL_BANDS];
} FreqInfo_t;

/**
 * @struct FDDInfo
   This structure is the FDD Mode Config Info of  Cell Configuration
*/
typedef struct fddInfo
{
    FreqInfo_t         ulFreqInfo;
    FreqInfo_t         dlFreqInfo;
    TransBandWidth_t   ulTransBW;
    TransBandWidth_t   dlTransBW;
} FddInfo_t;

/**
 * @struct TDDInfo
   This structure is the TDD Mode Config Info of  Cell Configuration
*/
typedef struct tddInfo
{
    FreqInfo_t         nrFreqInfo;
    TransBandWidth_t   transBW;
} TddInfo_t;

/**
 * @struct oamActCellInfo
   This structure is oam send this message  to Du act cell
*/
typedef struct oamActCellInfo
{
    UINT8              actCellNum;
	CmNrCellId		   actCellId[MAX_CELL_NUM];
} OamActCellInfo_t;

/**
 * @struct oamActCellRsp
   This structure is DU send reponse message  to OAM
*/
typedef struct oamActCellRsp
{
    UINT8              actResult;       //0: all failed 1: all success 2: some success and some failed
    UINT8              actCellNum;
	CmNrCellId		   actSuccessCellId[MAX_CELL_NUM];
	CmNrCellId		   actFailedCellId[MAX_CELL_NUM];
} OamActCellRsp_t;


/** 从原始消息中获取SOCKET msg */
#define GNB_GET_SOCKET_MSG(src,dst)   VOS_MemCpy((CHAR*)dst,(CHAR*)src,sizeof(vos_sock_info_t))

/** 从原始消息中拷贝消息到dst中 */
#define GNB_GET_DATA(src,dst,len)    if(len > sizeof(vos_sock_info_t)) \
                                     {  \
                                        VOS_MemCpy((CHAR*)dst,((CHAR*)src+sizeof(vos_sock_info_t)),(len-sizeof(vos_sock_info_t))); \
                                     } \
                                     else \
                                     { \
                                        printf("msg len invalid, len = %d \r\n",len);\
                                        VOS_ASSERT(0); \
                                        return VOS_ERROR;\
                                     }
/*获取msgBuf中消息地址*/
#define GNB_GET_MODULE_MSG_DATA_PTR(dataType,pData,buf)   do{ \
																ULONG ulBufAddr = 0; \
																VOS_MemCpy((CHAR*)&ulBufAddr,(CHAR*)buf,sizeof(ULONG));\
																pData =(dataType*)(ULONG*)ulBufAddr; \
															  }while(0)
/*设置msgBuf中消息地址*/
#define GNB_SET_MODULE_MSG_DATA_PTR(src,dst)   do{ \
													  ULONG ulBufAddr = 0; \
													  ulBufAddr= (ULONG)((ULONG*)src); \
													  VOS_MemCpy(dst, &ulBufAddr, sizeof(ULONG)); \
													}while(0)

/*填充数据地址到msgBuf中*/
#define GNB_SET_MODULE_MSG(msg,pModuleMsg) do{ \
												  CHAR*  bufPtr = NULL; \
												  ULONG  ulBufAddr = 0; \
												  bufPtr = (CHAR*)VOS_Malloc((pModuleMsg)->msgLen,(pModuleMsg)->srcModuleId); \
												  if(NULL == bufPtr)  \
												  { \
													 VOS_ASSERT(0); \
													 return VOS_ERROR; \
												  } \
												  VOS_MemCpy(bufPtr,&msg,sizeof(msg)); \
												  ulBufAddr= (ULONG)((ULONG*)bufPtr); \
												  VOS_MemCpy((pModuleMsg)->msgBuf, &ulBufAddr, sizeof(ULONG)); \
												}while(0)
#define BUFFER_TO_UINT32(buf, x) \
do {                            \
    x = ((uint32_t)((buf)[0]) ) |      \
        ((uint32_t)((buf)[1]) << 8) |      \
        ((uint32_t)((buf)[2]) << 16)  |      \
        ((uint32_t)((buf)[3]) << 24);             \
} while(0)

#define INT32_TO_BUFFER(x, buf) \
do {                            \
    (buf)[0] = (x) >> 24;       \
    (buf)[1] = (x) >> 16;       \
    (buf)[2] = (x) >> 8;        \
    (buf)[3] = (x);             \
} while(0)




extern void fillSocketPara(UINT32 sockType,SockAddrStr_t* pSockAddr,SockAddrStr_t* clientSockAddrInfo,vos_sock_para_t *para);
extern INT32 get_file_len(FILE *file_p);
extern INT32 tell_file(FILE *file_p);
extern INT32 getpos_file(FILE *file_p, fpos_t *pos);
extern INT32 putpos_file(FILE *file_p, fpos_t *pos);
extern INT32 seek_file(FILE *file_p, INT32 offset, INT32 whence);
extern INT32 eof_file(FILE *file_p);
extern INT32 error_file(FILE *file_p);
extern FILE *open_file(const char *path, const char *flag);
extern INT32 close_file(FILE *file_p);
extern INT32 read_file(void *buf, INT32 size, INT32 count, FILE *file_p);

extern VOID sctpMsgNotifyProc(vos_sock_info_t* opval,VOID* buffer);

void gnbPrintRrcMsg(int direction, int msgType, UINT8 *buf, INT32 size);

#ifdef __cplusplus
}
#endif

#endif  /* _CU_COMMON_H_*/
