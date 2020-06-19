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



#ifndef __CUUPPROTOCOLPARA_H__
#define __CUUPPROTOCOLPARA_H__

#include "vos_lib.h"

#pragma pack(1)

/*******************************CUUP基本信息***********************************/

#define		CUUP_NAME_MAX_LEN		32

typedef struct CuupBasicInfoCfg_s
{
	UINT64	gnbCuupId;
	UCHAR	gnbCuupName[CUUP_NAME_MAX_LEN];
	UINT8	cnSupportType;//ENUMERATED (EPC,5GC,both)
	UINT8	cuupCapacity_presence;//cuupCapacity配置标志位
	UINT8	cuupCapacity;//取值范围（0…255）
}cuupBasicInfoCfg_t;


/**********************************IP信息**************************************/

#define		MAX_CUUP_IPV6_ADDR_LEN		40
#define		MAX_CUUP_IPV4_ADDR_LEN		16

#define		MAX_NROF_CUUP_CUC_IP_ADDR		5
#define		MAX_NROF_CUUP_CUUP_IP_ADDR		5

typedef struct 	CuupIpAddrList_s
{
	UINT8	ipType;
	UINT32	port;
	char	ipv4Address[MAX_CUUP_IPV4_ADDR_LEN];
	char	ipv6Address[MAX_CUUP_IPV6_ADDR_LEN];
}cuupIpAddrList_t;

typedef struct CuupIpInfoList_s
{
	UINT8	cucIpAddrNum;
	cuupIpAddrList_t	cucIpList[MAX_NROF_CUUP_CUC_IP_ADDR];

	UINT8	cuupIpAddrNum;
	cuupIpAddrList_t	cuupIpList[MAX_NROF_CUUP_CUUP_IP_ADDR];

}cuupIpInfoList_t;

/**********************************PLMN信息表**************************************/

#define		MAX_CUUP_NROF_PLMN			5//12
#define		CU_MCC_LEN					3
#define		CU_MAX_MNC_LEN				3

typedef struct	CuupPlmnIdList_s
{
	UINT8	MCC_Presence;//MCC配置标志位
	UINT8	MCC[CU_MCC_LEN];
	UINT8	mncNum;//取值2或者3
	UINT8	MNC[CU_MAX_MNC_LEN];

}cuupPlmnIdList_t;

typedef struct CuupPlmnIdInfo_s
{
	UINT8	plmnIdNum;//取值范围1...12(协议规定)，目前暂定取值范围1...5
	cuupPlmnIdList_t	plmnIdList[MAX_CUUP_NROF_PLMN];

}cuupPlmnIdInfo_t;




/**********************************E1接口信息***********************************/

#define MAX_NROF_NG_RAN_QOS_PARAMETER	1//256协议规定
typedef struct qosSupportInfo_s
{
	UINT8	plmnIdx;
	UINT8	fiveQI;//取值范围:0~255
	UINT8	qoSPrirotyLevel_presence;//qoSPrirotyLevel配置标志位
	UINT8	qoSPrirotyLevel;//取值范围:0~127
	UINT8	averagingWindow_presence;//averagingWindow配置标志位
	UINT16	averagingWindow;//取值范围:0~4095
	UINT16	maxDataBurstVolume_presence;//maxDataBurstVolume配置标志位
	UINT16	maxDataBurstVolume;//取值范围:0~4095
}qosSupportInfo_t;


typedef struct ngranQosSupportList_s
{
	UINT8	qosSupportNum;
	qosSupportInfo_t qosSupportInfo[MAX_NROF_NG_RAN_QOS_PARAMETER];
}ngranQosSupportList_t;


/**********************************切片信息***********************************/

#define	MAX_NROF_SLICE_SUPPORTED		3



typedef struct SliceSupportInfo_s
{
	UINT8	PlmnIdx;
	UINT8	SST;	//为了支持网络切片,与SD字段可以组成S-NSSAI
	UINT8	SD_presence;//SD配置标志位
	UINT32	SD:24;
}sliceSupportInfo_t;

typedef struct SliceSupportList_s
{
	UINT8	sliceSupportNum;//取值范围1--1024(协议规定),目前取值范围1...3
	sliceSupportInfo_t	sliceSupportInfo[MAX_NROF_SLICE_SUPPORTED];
}sliceSupportList_t;

/**********************************UP支持的小区ID列表****************************/

#define	MAX_NROF_CUUP_SUPPORT_CELL		10//512

typedef struct cellIdSupportInfo_s
{
	UINT8	plmnIdx;
	UINT64	cellGlobalId;
}cellIdSupportInfo_t;



typedef struct cellIdSupportList_s
{
	UINT8	cellSupportNum;//取值范围0--512(协议规定),目前取值范围0...10
	cellIdSupportInfo_t	cellIdInfo[MAX_NROF_CUUP_SUPPORT_CELL];
}cellIdSupportList_t;


#pragma pack()

#endif
