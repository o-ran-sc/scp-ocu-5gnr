/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/

#ifndef GTPU_COMMON_H
#define GTPU_COMMON_H

#include <sys/socket.h>
#include <netinet/in.h>
#include "vos_lib.h"
#include "vos_linklist.h"
#include "vos_types.h"
#include "plat_syslog.h"
#include "vos_sockMgr.h"
#include "vos_module.h"
#include "gnbCommon.h"
#include "msgb.h"


#define GTP_MAX_TUN_NUM					 100	
#define GTPU_MODULE 					   1	/* just for compile */
#define GTP_MAX_DATA_LEN				8000
#define GTP_HEADER_SIZE_SHORT  			   8
#define GTP_HEADER_SIZE_LONG  			  12

/* GTP version 1 extension header type definitions. */
#define GTP_EXT_PDCP_PDU    			0xC0	/* PDCP PDU Number */
#define GTP_EXT_RAN_CONTAINER 			0X81	/* RAN Container */
#define GTP_EXT_NRRAN_CONTAINER 		0X84	/* NR RAN Container */
#define GTP_EXT_PDUSESSION_CONTAINER 	0X85	/* PDU Session Container */


#define GTP_ECHO_REQ          			   1 	/* Echo Request */
#define GTP_ECHO_RSP          			   2 	/* Echo Response */
#define GTP_NOT_SUPPORTED     			   3 	/* Version Not Supported */

#define GTP_ERROR            			  26 	/* Error Indication */
#define GTP_SUPP_EXT_HEADER  			  31 	/* Supported Extension Headers Notification */
#define GTP_GPDU            			 255 	/* G-PDU */
#define GTP_END_MARKER      			 254 

/* for f1u pdu */
#define GTP_DLUSERDATA_EX_LEN			   2
#define GTP_DLUSERDATA_BYTES_LEN		   8
#define GTP_DDDS_EX_LEN					   6
#define GTP_DDDS_BYTES_LEN				  24

/* for ngu pdu */
#define GTP_DLPDUSESSION_EX_LEN			   2
#define GTP_DLPDUSESSION_BYTES_LEN		   8
#define GTP_ULPDUSESSION_EX_LEN			   1
#define GTP_ULPDUSESSION_BYTES_LEN		   4

#define GTP_EXHEAD_LEN					 256


#define PATH_DETECT_TIMER 				  60      /* detect path every 60 seconds */
#define T3RESPONSE_TIMER 				   3      /* T3-RESPONSE timer defaults to 1 second */
#define N3REQUESTS       				   5      /* max times of retransmssion of echo quest */

#define GTPU_ENTITY_NUM					   2	  /* CUGTPU+DUGTPU */

#define gtpLog(iLog_Level, gtp, content, arg...) \
{\
	if(NULL != gtp)\
	{\
		VOS_SysLog(gtp->userModuleID, iLog_Level, __FILE__, __LINE__, __func__, content, ##arg);\
	}else\
	{\
		vos_err_print("gtp entity is NULL!\n");\
	}\
}

#if 0
#define gtpNullCheck(p,gtp) \
{\
   if(NULL == p)\
   {\
	   gtpLog(LOG_ERR,gtp,"[GTPU] NULL pointer\n");\
       return VOS_ERROR;\
   }\
}
#endif

typedef enum
{
	CU_GTPU,
	DU_GTPU
}GtpType_e;

typedef enum
{
	CU_NG_TUNNEL,
	CU_F1_TUNNEL,
	DU_TUNNEL
}TunnelType_e;

typedef enum
{
	TUNNEL_INACTIVE = 0,
	TUNNEL_ACTIVE
}TunnelStatus_e;



/* GTP-U header definitions */

typedef struct
{ /*    Descriptions from 3GPP 29060 */
    UINT8 pn :1;		/*    .......0 PN: N-PDU Number flag */
    UINT8 s :1;			/*    ......0. Sequence number flag: 0 */
    UINT8 e :1;			/*    .....0.. Extension header flag: 0 */
    UINT8 spare :1;		/*    ....0... Spare = 0 */
    UINT8 pt :1;		/*    ...1.... Protocol Type: GTP=1, GTP'=0 */
    UINT8 ver :3;		/*    001..... Version: 1 */
    UINT8 type; 		/* 02 Message type. T-PDU = 0xff */
    UINT16 length; 		/* 03 Length (of IP packet or signalling) */
    UINT32 tei; 		/* 05 - 08 Tunnel Endpoint ID */
} GtpHeadShort_t;

typedef struct 
{ /*    Descriptions from 3GPP 29060 */
    UINT8 pn :1;		/*    .......0 PN: N-PDU Number flag */
    UINT8 s :1;			/*    ......0. Sequence number flag: 0 */
    UINT8 e :1;			/*    .....0.. Extension header flag: 0 */
    UINT8 spare :1;		/*    ....0... Spare = 0 */
    UINT8 pt :1;		/*    ...1.... Protocol Type: GTP=1, GTP'=0 */
    UINT8 ver :3;		/*    001..... Version: 1 */
    UINT8 type; 		/* 02 Message type. T-PDU = 0xff */
    UINT16 length; 		/* 03 Length (of IP packet or signalling) */
    UINT32 tei; 		/* 05 - 08 Tunnel Endpoint ID */
    UINT16 seq; 		/* 09 - 10 Sequence Number */
    UINT8 npdu; 		/* 11 N-PDU Number */
    UINT8 next; 		/* 12 Next extension header type. Empty = 0 */
}GtpHeadLong_t;


struct gtpExtHead{
	uint8_t type;
	uint8_t len;
	uint8_t data[];
} __attribute__((packed));
#define GTP_EXTHDR(buf) ((struct gtpExtHead *)buf)
#define GTP_LHDR(buf) ((GtpHeadLong_t *)buf)
#define GTP_FIRSTHDR(buf) ((GTP_LHDR(buf)->length >= 5 &&		\
		GTP_LHDR(buf)->next) ?					\
		(struct gtpExtHead *)&GTP_LHDR(buf)->next : NULL)
#define GTP_NXTHDR(buf, ext)						\
	(ext == NULL ? GTP_FIRSTHDR(buf) : 				\
		((uint8_t *)&ext->len + ext->len * 4 -			\
		(uint8_t *)&GTP_LHDR(buf)->seq) > 			\
		GTP_LHDR(buf)->length ?					\
		NULL : *((uint8_t *)&ext->len + ext->len * 4 - 1) ? 	\
			(struct gtpExtHead *)((uint8_t *)&ext->len +	\
			ext->len * 4 - 1) : NULL)
#define GTP_EXTDATA(buf) (GTP_LHDR(buf)->data)



/* GTP-U packet */
typedef struct
{
    GtpHeadShort_t h;    
    UINT8 			 p[GTP_MAX_DATA_LEN];		/* store data */
}GtpPacketShort_t;

typedef struct
{
    GtpHeadLong_t h;
    UINT8 			p[GTP_MAX_DATA_LEN];		/* store data */
}GtpPacketLong_t;

union gtpPacket
{
    GtpPacketShort_t gtps;
    GtpPacketLong_t  gtpl;
};


/* GTP-U tunnels management structures */
typedef struct tun
{
	TunnelStatus_e			tunState;				/* 0 for suspend, others are active */
	UINT16 					seq; 					/* G-PUD Sequence number counter */
    UINT32 					tunId;
    UINT32 					ownTeid; 				/* own TEID */
    UINT32 					remTeid; 				/* remote TEID */
    vos_sock_info_t			tunOpval; 				/* Address packet was sent to / received from */
	TunnelType_e			tunType;
} Tun_t;


typedef struct gtpMsg
{
    UINT16 					seq; 			/* The sequence number */
    UINT8  					type; 			/* The type of packet */    
    UINT32 					l; 				/* Length of the packet */
    union gtpPacket 		p; 				/* The packet stored */
    vos_sock_info_t			*pOpval; 		/* Address packet was sent to / received from */
    time_t 					timeout; 		/* When do we retransmit this packet? */
	UINT8 					retrans; 		/* How many times did we retransmit this? */
}GtpMsgNode_t;


/* GTP-U Protocol entity */
typedef struct
{
	GtpType_e		gtpId;
	ULONG 			userModuleID;
	
	/* Parameters related to the network INT32erface */
	vos_sockaddr_t  localAddr;						/* Local IP address for signaling and G-PDU */
	
    /* Parameters related to signaling messages */
    UINT16 			seq_next; 			 			/* Next sequence number to use */
    UINT8 			restart_counter; 		 		/* Increment on restart. */
   	plist 			pReqMsgList;    				/* list header */
	Tun_t 	   	   *tuns[GTP_MAX_TUN_NUM]; 			/* store memory,use TEID_OWN assignment */
    					
    /* Counters ,some of them may not be used. */
    UINT32 err_socket; 			/* Number of socket errors */
    UINT32 err_readfrom; 		/* Number of readfrom errors */
    UINT32 err_sendto; 			/* Number of sendto errors */
    UINT32 err_memcpy; 			/* Number of memcpy */
    UINT32 err_seq; 			/* Number of seq out of range */
    UINT32 err_cause; 			/* Unexpected cause value received */

    UINT32 empty; 				/* Number of empty packets */
    UINT32 unsup; 				/* Number of unsupported version 29.60 11.1.1 */
    UINT32 tooshort; 			/* Number of too short headers 29.60 11.1.2 */
    UINT32 unknown; 			/* Number of unknown messages 29.60 11.1.3 */
    UINT32 nu_rabid; 			/* Number of unknown RAD ID message */
    UINT32 unexpect; 			/* Number of unexpected messages 29.60 11.1.4 */
    UINT32 duplicate; 			/* Number of duplicate or unsolicited replies */
    UINT32 missing; 			/* Number of missing information field messages */
    UINT32 incorrect; 			/* Number of incorrect information field messages */
    UINT32 invalid; 			/* Number of invalid message format messages */
} Gtp_t;


typedef struct 
{
	UINT8	   *pPdu;			/* length, content, next extension type */
	UINT16		len;			/* len = exHeaderLen * 4 */
	UINT16		exHdrLen;
	UINT8		exHdrType;
}ExPduInfo_t;

/* log level */
typedef enum gtpuLogLevel
{
	GTPULOG_CRIT = 1,        ///<  critical conditions 
	GTPULOG_ERR,             ///<  error conditions 
	GTPULOG_WARNING,         ///<  warning conditions 
	GTPULOG_INFO,            ///<  informational 
	GTPULOG_DEBUG,           ///<  debug info
} GtpuLogLevel_e;

/* struct for gtpu receive data */
typedef struct
{
	vos_sock_info_t op;
	MsgbBuff_t *pData;
}GtpuRecvUdpInfo_t;

typedef struct
{
    UINT32 tunId;
	MsgbBuff_t *pMsgBuff;
	ExPduInfo_t *pExPduInfo;
}GpduInfo_t;

typedef INT32 (* GtpuDataProcFn)(GpduInfo_t *pInfo);

typedef struct
{
	GtpuDataProcFn action_fn_p;
}GtpuGpduHandler_t;





//check teid
#define gtpCheckTeid(n) if(n<0 || n>GTP_MAX_TUN_NUM) {vos_err_print(#n" is wrong\r\n");return VOS_ERROR;}


#endif /* GTPU_COMMON_H */

