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

#ifndef _CU_COMMON_H_
#define _CU_COMMON_H_


#ifdef __cplusplus
extern "C" {
#endif
#include <netinet/in.h>
#include "gnbCommon.h"

#define MAX_CU_NAME_LEN   256
#define MAX_CUCP_NAME_LEN 256
#define MAX_CUUP_NAME_LEN 256

#define	MAX_OM_MSG_BUF_LEN	64

/****************************************oam active message code****************************************/
#define 	OAM_CU_ACTIVE_BASE     					0x7000
#define 	OAM_CUUP_NET_ELEMENT_ACTIVE_REQ    		OAM_CU_ACTIVE_BASE + 1
#define 	OAM_CUCP_NET_ELEMENT_ACTIVE_REQ        	OAM_CU_ACTIVE_BASE + 2
#define 	CUCP_OAM_CELL_ACTIVE_RSP        		OAM_CU_ACTIVE_BASE + 3
#define 	CUUP_OAM_CELL_ACTIVE_RSP        		OAM_CU_ACTIVE_BASE + 3

typedef enum
{
    MODULE_OM,
    MODULE_CUCP_E1,
    MODULE_CUUP_E1  ,
    MODULE_NG,
    MODULE_Xn,
    MODULE_F1_C,
    MODULE_CUC,
    MODULE_RRC,
    MODULE_PDCP_C,
    MODULE_UPC,
    MODULE_NG_U,
    MODULE_NG_GTPU,
    MODULE_SDAP,
    MODULE_F1_U,
    MODULE_F1_GTPU,

}CuModule_e;



typedef enum CuCpVosTask
{
    CUCP_OMADP_VOS_TASK,
    CUC_VOS_TASK,
    CUCP_NG_C_VOS_TASK,
    CUCP_F1_C_VOS_TASK,
    CUCP_E1_VOS_TASK,
#ifdef AMF_TEST
    AMF_VOS_TASK,
#endif
	CP_MAX_VOS_TASK
}CuCpVosTask_e;

typedef enum CuUpVosTask
{
    UP_OMADP_VOS_TASK,
	UP_DL_VOS_TASK,
	UP_UL_VOS_TASK,
	UP_GTPU_VOS_TASK,
	UP_MAX_VOS_TASK
}CuUpVosTask_e;

typedef enum
{
    CUCP_HOST_TASK,
    CUUP_HOST_TASK,
    CUUP_DATA_HOST_TASK
}CuHostTask_e;

typedef enum
{
#if 0
    CUC_USER_TASK,
    CUCP_NG_C_USER_TASK,
    CUCP_F1_C_USER_TASK,
    CUCP_E1_USER_TASK,
#endif
    /*注意：请新增任务定义在注释中间*/




    /*注意：请新增任务定义在注释中间*/
    CUCP_END_USER_TASK = 100
}CucpUserTask_e;

typedef enum
{
    CUUP_BEGIN_USER_TASK=200,
    CUUP_UPC_USER_TASK,
    CUUP_E1_USER_TASK,
    CUUP_NGGTPU_DL_TASK,
    CUUP_NGU_DL_TASK,
    CUUP_SDAP_DL_TASK,
    CUUP_PDCPU_DL_TASK,
    CUUP_F1U_DL_TASK,
    CUUP_F1GTPU_DL_TASK,

    CUUP_NGGTPU_UL_TASK,
    CUUP_NGU_UL_TASK,
    CUUP_SDAP_UL_TASK,
    CUUP_PDCPU_UL_TASK,
    CUUP_F1U_UL_TASK,
    CUUP_F1GTPU_UL_TASK,
    /*注意：请新增任务定义在注释中间*/
    CUUP_GTPU_USER_TASK,
    CUUP_PDCPU_USER_TASK,
    CUUP_SDAP_USER_TASK,


    /*注意：请新增任务定义在注释中间*/
    CUUP_END_USER_TASK=400,
}CuupUserTask_e;


typedef struct
{
    UINT8 cuName[MAX_CU_NAME_LEN];  /* CU Name */
    UINT32 nodeID;
    IpAddress_t cuIpAddr;
    IpAddress_t omIpAddr;

    IpAddress_t amfIpAddr;
    IpAddress_t umfIpAddr;

    IpAddress_t cucpF1SctpIpAddr;
    IpAddress_t cuupF1GtpuIpAddr;

    IpAddress_t duF1SctpIpAddr;
    IpAddress_t duF1GtpuIpAddr;

    IpAddress_t cucpE1SctpIpAddr;
    IpAddress_t cuupE1SctpIpAddr;

    IpAddress_t cucpNgSctpIpAddr;
    IpAddress_t cuupNgGtpuIpAddr;

    IpAddress_t cuXnSctpIpAddr;
}CuCommCfg_t;

typedef struct
{
    UINT8   NodeBName[MAX_CU_NAME_LEN];
    UINT32 procId;
    UserTaskInfo_t  userTaskInfo[MAX_TASK_NUM];
    CuCommCfg_t commCfg;
    UINT8  cuStackState;
    UINT8  omState;

    UINT8  printDebug;
    UINT8  printLevel;
    UINT8  interLogFlag;

} CuCtrlBlock_t;

typedef struct
{
	PlmnId_t	plmnId;
	NrCellId_t  CellId[MAX_CELL_NUM];
}CellIdList_t;

typedef struct oamCuUpNetElementActReq
{
	UINT8		actCellNum;
	CellIdList_t	cellIdList;
} OamCuUpNetElementActReq_t;

typedef struct oamCuUpCellActRsp
{
	UINT8		successCellNum;
	UINT8		failCellNum;
	NrCellId_t	failCellId[MAX_CELL_NUM];
} OamCuUpCellActRsp_t;

typedef struct oamCuCpNetElementActReq
{
	UINT8		cuCpNetElementAct[MAX_CELL_NUM];
} OamCuCpNetElementActReq_t;

typedef struct oamCuCpCellActRsp
{
	UINT8		cuCpCellActFlag[MAX_CELL_NUM];
} OamCuCpCellActRsp_t;

typedef enum
{
	SRB0 =0 ,
	SRB1 = 1,
	SRB2 = 2,
	SRB3 = 3,

}SRB_e;





#ifdef __cplusplus
}
#endif

#endif  /* _CU_COMMON_H_*/
