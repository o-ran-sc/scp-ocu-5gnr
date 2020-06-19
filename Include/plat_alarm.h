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



#ifndef __PLAT_ALARM_H__
#define __PLAT_ALARM_H__
#include "vos_types.h"

#ifdef    __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "vos_common.h"



/** trap OID 长度 */
#define TRAP_OID_LEN   (32)

/** 告警源信息中index最大个数 */
#define ALARM_INDEX_MAX_LEN	5

/** 告警源信息中所携带数据大小 *sizeof(ULONG) */
#define MAXLEN_EVENT_DATA	16

/** 记录告警源信息 */
typedef  union alarmSrc_s{
	ULONG  alarmSrcData[MAXLEN_EVENT_DATA];  ///< 告警数据
}__attribute__((packed)) alarmSrc_t;


/**
* 告警消息
*/
typedef struct alarmMsg_s
{
	UCHAR 	alarmType;    ///< 告警类型
	UCHAR 	alarmId;      ///< 告警标识:用于映射告警描述
	alarmSrc_t alarmSrc;  ///< 告警源信息
}__attribute__((packed))alarmMsg_t;


typedef struct {
	ULONG  year		:6;
	ULONG  month	:4;
	ULONG  day		:5;
	ULONG  hour		:5;
	ULONG  minute	:6;
	ULONG  second	:6;
}__attribute__((packed)) logDateAndTime_t;

/**
* 用于当前告警和历史告警存储
*/
typedef struct {
    ULONG  sequenceID;              ///< 告警序号
	UCHAR  alarmType;               ///< 告警类型
	UCHAR  alarmId;                 ///< 告警标识:用于映射告警描述
	alarmSrc_t alarmSrc;            ///< 告警源
	logDateAndTime_t  alarmTime;    ///< 告警发生时间
	logDateAndTime_t  clearTime;    ///< 告警清除时间
	UCHAR	alarmMskFlg;            ///< 告警屏蔽标记
	UCHAR	alarmInvFlg;            ///< 告警翻转标记
	UCHAR	reserved[2];            ///< 保留字段
} __attribute__((packed)) alm_status_t;

/**
 * 通用告警上报API，使用变长参数，变长参数只支持ULONG  和char * 字符串。
 * 设备索引和上报参数依次排列，不能乱序。
 * @param[in]   alarmType    告警类型
 * @param[in]   alarmId      告警ID
 * @return        VOS_OK - 成功，VOS_ERROR－ 失败
 */
LONG alarm_commonReport( LONG alarmType, LONG alarmId, ... );


/**
 * 根据 alarmType 和 alarmId 获取告警 TrapOid。
 * @param[in ]   alarmType    告警类型
 * @param[in ]   alarmId      告警ID
 * @param[out]   pTrapOid     存放oid 的数组
 * @param[out]   pOidLen      oid长度
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_TrapOid_get( ULONG alarmType, ULONG alarmId, ULONG pTrapOid[TRAP_OID_LEN], LONG *pOidLen );


/**
 * 根据 alarmType 和 alarmId 获取告警 level。
 * @param[in]   alarmType    告警类型
 * @param[in]   alarmId      告警ID
 * @return      成功返回告警 level，失败返回 0
 */
ULONG alarm_Level_get( ULONG alarmType, ULONG alarmId );


/**
 * 根据 alarmType 和 alarmId 获取告警 trap使能。
 * @param[in]   alarmType    告警类型
 * @param[in]   alarmId      告警ID
 * @return      返回告警 trap是否使能
 */
ULONG alarm_TrapEnable_get( ULONG alarmType, ULONG alarmId );


/**
 * 根据 alarmType 和 alarmId 获取告警 index个数。
 * @param[in]   alarmType    告警类型
 * @param[in]   alarmId      告警ID
 * @return      返回告警 index个数
 */
ULONG alarm_IndexNum_get( ULONG alarmType, ULONG alarmId );


/**
 * 根据 alarmType 和 alarmId 获取告警 参数个数。
 * @param[in]   alarmType    告警类型
 * @param[in]   alarmId      告警ID
 * @return      返回告警 参数个数
 */
ULONG alarm_ParaNum_get( ULONG alarmType, ULONG alarmId );


/**
 * 根据 alarmType 和 alarmId 获取告警 index打印格式。
 * @param[in ]   alarmType    告警类型
 * @param[in ]   alarmId      告警ID
 * @param[out]   fmt          index打印格式
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_IndexFormat_get( ULONG alarmType, ULONG alarmId ,CHAR *fmt);


/**
 * 根据 alarmType 和 alarmId 获取告警 参数打印格式。
 * @param[in ]   alarmType    告警类型
 * @param[in ]   alarmId      告警ID
 * @param[out]   fmt          参数打印格式
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_ParaFormat_get( ULONG alarmType, ULONG alarmId ,CHAR *fmt);



/**
 * 根据 alarmType 和 alarmId 获取告警 priority
 * @param[in]   alarmType    告警类型
 * @param[in]   alarmId      告警ID
 * @return      成功返回告警 priority，失败返回 0
 */
ULONG alarm_Priority_get( ULONG alarmType, ULONG alarmId );

/**
 * 根据 alarmType 和 alarmId 获取告警 PartnerId
 * @param[in]   alarmType    告警类型
 * @param[in]   alarmId      告警ID
 * @return      成功返回告警 PartnerId，失败返回 0
 */
ULONG alarm_PartnerId_get( ULONG alarmType, ULONG alarmId );

/**
 * 判断该告警是否为事件
 * @param[in]   alarmType    告警类型
 * @param[in]   alarmId      告警ID
 * @return      为事件返回真，为告警返回false
 */
BOOL alarm_is_event( ULONG alarmType, ULONG alarmId );

/**
 * 将告警数据转换成字符串
 * @param[in]   pAlmMsg    告警数据
 * @param[in]   logDesc    存放转换后的结果
 * @param[in]   size       logDesc 的大小，建议大小512字节
 * @return      返回指向转换结果的指针（同logDesc）
 */
CHAR *alarmDataToStrings( alarmMsg_t *pAlmMsg, CHAR *logDesc,LONG size );

/**
 * 获取当前告警的第一条。
 * @param[out]   pItem    告警条目
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_alm_cur_list_get_first(alm_status_t *pItem);


/**
 * 获取当前告警的下一条。
 * @param[in ]   pItem    当前条目
 * @param[out]   pItem    下一条目
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_alm_cur_list_get_next(alm_status_t *pItem);


/**
 * 获取历史告警的第一条。
 * @param[out]   pItem    告警条目
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_alm_hist_list_get_first(alm_status_t *pItem);


/**
 * 获取历史告警的下一条。
 * @param[in ]   pItem    当前条目
 * @param[out]   pItem    下一条目
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_alm_hist_list_get_next(alm_status_t *pItem);

/**
 * 获取事件的第一条。
 * @param[in ]   pItem    当前条目
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_alm_event_list_get_first(alm_status_t *pItem);


/**
 * 获取事件的下一条。
 * @param[in ]   pItem    当前条目
 * @param[out]   pItem    下一条目
 * @return      成功返回 VOS_OK ，失败返回 其他
 */
LONG alarm_alm_event_list_get_next(alm_status_t *pItem);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __PLAT_ALARM_H__ */
