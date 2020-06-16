/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef __OMCUUPAPI_H__
#define __OMCUUPAPI_H__

#include	"cuupProtocolPara.h"



#define MAC_CUUP_CELL_NUM	10

#define CUUP_SHM_FILE	"cuup_shm"

/*结构体id*/
typedef enum{
    id_cuupBasicInfoCf = 1,  
    id_cuupIpInfoList,
    id_cuupPlmnInfo,
	id_qosSupportList,
	id_sliceSupportList,
	id_cellIdSupportList,
}OM_CuUp_para_struct_id;
	

/////CPUP配置信息
#pragma pack(1)


typedef struct CuUpCfg_s
{
	cuupBasicInfoCfg_t	cuupBasicInfoCfg;
	cuupIpInfoList_t	cuupIpInfoList;
	cuupPlmnIdInfo_t	plmnInfo;
	ngranQosSupportList_t	qosSupportList;
	sliceSupportList_t	sliceSupportList;
	cellIdSupportList_t	cellIdSupportList;
}cuUpCfg_t;


/////小区配置信息
/*typedef struct CuUpCellInfoCfg_s
{
	UINT32	cellId;
	e1setupRequestInfo_t	e1setupRequestInfo;
	sliceSupportList_t		sliceSupportList;

}cuUpCellInfoCfg_t;
*/


typedef struct CuUp_shm_table_s
{
	//UINT8	cell_num;
	cuUpCfg_t	shm_cuupCfg;
}CuUp_shm_table_t;

#pragma pack()


#endif

