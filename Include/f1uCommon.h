/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/

#ifndef F1U_COMMON_H
#define F1U_COMMON_H

#include "gnbCommon.h"

#define DL_USER_DATA				0
#define DL_DATA_DELIVERY_STATUS		1
#define CUF1U_PDU_SESSION_MAX_NUM 256

typedef enum{
	LEN_12_BITS = 0,
	LEN_18_BITS = 1
}PDCPSnSize_e;
	
/* CU-F1-U instance */
typedef struct {
	UINT64 				ueE1apId;
	UINT16  			ueIdx;
	UINT8		  		drbId;
	UINT16				pduSessionId;
	UINT32  	  		nextSubmitSn;
	PDCPSnSize_e 	 	pdcpSnSize;
	UINT32  	  		ownTeid;         /* Local teid */
}Cuf1uInstance_t;


#endif /* F1U_COMMON_H */
