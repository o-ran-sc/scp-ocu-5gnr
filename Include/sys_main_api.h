/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef __SYS_MAIN_API_H__
#define __SYS_MAIN_API_H__


#ifdef __cplusplus
extern "C"
{
#endif

/******************************   Begin of File Body  **********************/
#include "vos_common.h"
#ifdef PLAT_MODULE_DEVSM

extern LONG sys_slot_is_master_slot( ULONG slotno );
extern LONG devsm_module_workmode_is_master(ULONG slotno);
extern LONG devsm_module_workmode_is_slave(ULONG slotno);
extern LONG devsm_module_workmode_is_master_active(ULONG slotno);
extern LONG devsm_module_workmode_is_master_standby(ULONG slotno);
extern LONG sys_product_name_get(CHAR *str, ULONG max_len);
extern USHORT sys_chassis_max_slotnum_get();
extern USHORT sys_chassis_master_slotnum_get();
extern ULONG sys_master_active_slotno_get();
extern ULONG sys_local_module_slotno_get();
extern ULONG sys_module_running_state_get(ULONG slotno);
extern ULONG sys_module_is_have_cpu(ULONG slotno);
extern ULONG sys_module_is_running(ULONG slotno);
extern ULONG sys_module_is_ready(ULONG slotno);
extern ULONG sys_module_is_inserted(ULONG slotno);
extern LONG devsm_hot_get_module_type( LONG slotno );
extern ULONG sys_module_type_get(ULONG slotno);
extern LONG sys_module_have_pp(ULONG module_type);
extern LONG sys_module_have_fpgapp(ULONG module_type);
extern LONG sys_module_port_type_num(ULONG slotno, ULONG port_type);

extern ULONG g_ulProductDevIndex;

/** JT_SRAN设备索引 */
#define JT_SRAN_DEV_ID  (g_ulProductDevIndex)

/** TRAP 类型，Dev 必须为1 */
#define TRAP_TYPE_DEV	  1

/** TRAP 类型，board 必须为2 */
#define TRAP_TYPE_BOARD	  2

/** TRAP 程序启动成功，AlarmID 为1*/
#define ProgramStartSuccessAlarmID 1

/** TRAP 板卡热插入事件，AlarmID 为11*/
#define BoardHotInsertAlarmID 11

/** TRAP 板卡热拔出事件，AlarmID 为12*/
#define BoardHotPullAlarmID 12

/** TRAP 板卡重启事件，AlarmID 为13*/
#define BoardHotRebootAlarmID 13

/** 设备管理模块名*/
#define MOD_DEVSM_NAME  "DEVSM_MODULE"

/** 设备机框最大槽位个数 */
#define PRODUCT_MAX_TOTAL_SLOTNUM 21

/** 设备管理使用通知链发送的信息 */
typedef struct _devsm_notify_info_s
{
	ULONG slotno;			///< 槽位号
	ULONG module_type;		///< 板卡类型
}devsm_notify_info_t;

/** 设备管理通知链板卡RUNNING事件 */
#define DEVSN_NOTIFY_MOD_RUNNING_EVENT	0X01

#define CPI_HOOK_CALL(hookfunc) (NULL == (hookfunc))?(VOS_ERROR):(*hookfunc)

/**************************        产品相关           ***************************/
#define SYS_PRODUCT_NAME_GET(str, maxlen) 	(sys_product_name_get(str, maxlen))		/*产品名称*/

/**************************       全局机框槽位相关           **************************/
#define SYS_MASTER_ACTIVE_SLOTNO_UNKNOW 		(0x00)											/*主用主控槽位号未知*/
#define SYS_CHASSIS_SLOTNUM_GET					(sys_chassis_max_slotnum_get()) 				/*产品机框的最大槽位个数*/
#define SYS_CHASSIS_MASTER_SLOTNUM_GET 			(sys_chassis_master_slotnum_get())				/*产品的主控槽位个数*/
#define SYS_MASTER_ACTIVE_SLOTNO_GET 			(sys_master_active_slotno_get())				/*主用主控槽位号*/
#define SYS_CHASSIS_SLAVE_SLOTNUM 				(SYS_CHASSIS_SLOTNUM_GET-SYS_CHASSIS_MASTER_SLOTNUM_GET)/*产品机框的从板槽位个数*/
#define SYS_CHASSIS_SLOTNO_ISMASTERSLOTNO(slotno) (VOS_YES == sys_slot_is_master_slot(slotno))	/*判断槽位是否为主控*/
#define SYS_CHASSIS_SLOTNO_ISSLAVESLOTNO(slotno) (VOS_NO == sys_slot_is_master_slot(slotno))	/*判断槽位是否为从板*/


/**************************       槽位号判断相关            **************************/
#define SYS_SLOTNO_IS_ILLEGAL(slotno) (((slotno) > (SYS_CHASSIS_SLOTNUM_GET))||((slotno) < 1))		/*槽位不合法*/
#define SYS_SLOT_IS_LEGAL(slot) ((slot>0) && (slot<=SYS_CHASSIS_SLOTNUM_GET))						/*槽位合法*/

#define SYS_SLOT_LOOP_BEGIN(slot)      for (slot = 1; slot <= SYS_CHASSIS_SLOTNUM_GET; ++slot) {
#define SYS_SLOT_LOOP_END(slot)        }

#ifdef PLAT_MODULE_IFM
#define SYS_MODULE_PORT_NUM(slotno, port_type)	 (sys_module_port_type_num(slotno, port_type))
#define SYS_SLOT_PORT_IS_LEGAL(slot, port_type, port) (SYS_SLOT_IS_LEGAL(slot) && ((port>0) && (port<=SYS_MODULE_PORT_NUM(slot, port_type))))
#endif

/**************************  板卡工作模式、主备状态相关                     *****************/
#define SYS_MODULE_WORKMODE_ISMASTER(slotno) 	(devsm_module_workmode_is_master(slotno))			/*板卡工作模式是否为master*/
#define SYS_MODULE_WORKMODE_ISSLAVE(slotno) 	(devsm_module_workmode_is_slave(slotno))			/*板卡工作模式是否为slave*/
#define SYS_MODULE_ISMASTERACTIVE(slotno) 		(devsm_module_workmode_is_master_active(slotno))	/*板卡是否是主用主控*/
#define SYS_MODULE_ISMASTERSTANDBY(slotno) 		(devsm_module_workmode_is_master_standby(slotno))	/*板卡是否是备用主控*/


/*********************  local板卡工作模式、主备状态相关 ******             *****************/
#define SYS_LOCAL_MODULE_SLOTNO_GET				(sys_local_module_slotno_get())								/*本板槽位号*/
#define SYS_LOCAL_MODULE_WORKMODE_ISMASTER		SYS_MODULE_WORKMODE_ISMASTER(SYS_LOCAL_MODULE_SLOTNO_GET) 	/*本板是否工作在master*/	
#define SYS_LOCAL_MODULE_WORKMODE_ISSLAVE		SYS_MODULE_WORKMODE_ISSLAVE(SYS_LOCAL_MODULE_SLOTNO_GET) 	/*本板是否工作在slave*/
#define SYS_LOCAL_MODULE_ISMASTERACTIVE			SYS_MODULE_ISMASTERACTIVE(SYS_LOCAL_MODULE_SLOTNO_GET) 		/*本板是否是主用主控*/
#define SYS_LOCAL_MODULE_ISMASTERSTANDBY		SYS_MODULE_ISMASTERSTANDBY(SYS_LOCAL_MODULE_SLOTNO_GET) 	/*本板是否是备用主控*/


/**************************     板卡公共信息相关          	***************************/
#if 0	/*暂不对外开放，要用到再放开*/
#define SYS_MODULE_SW_VERSION(slotno)		_SYS_MODULE_SW_VERSION_(slotno) 			/*软件版本信息*/
#define SYS_MODULE_NAME(slotno) 			_SYS_MODULE_NAME_(slotno)					/*板卡名称*/
#define SYS_MODULE_HARDWARE_VERSION(slotno) _SYS_MODULE_HARDWARE_VERSION_(slotno)		/*硬件版本信息*/
#define SYS_MODULE_MANUFACTURE_DATE(slotno) _SYS_MODULE_MANUFACTURE_DATE_(slotno)		/*生产日期*/
#define SYS_MODULE_SERIALNO(slotno) 		_SYS_MODULE_SERIALNO_(slotno)				/*序列号*/
#endif

#define SYS_MODULE_TYPE(slotno) 			(devsm_hot_get_module_type(slotno))	/*include pulled module lastly*/

#define __SYS_MODULE_TYPE__GET(slotno)		(sys_module_type_get(slotno))	/*insert type*/

#define SYS_MODULE_SLOT_ISHAVECPU(slotno) (VOS_YES == sys_module_is_have_cpu(slotno))		/*板卡是否有CPU*/

#define SYS_MODULE_ISHAVEPP(type) (VOS_YES == sys_module_have_pp(type))
#define SYS_MODULE_SLOT_ISHAVEPP(slotno) (SYS_MODULE_ISHAVEPP(__SYS_MODULE_TYPE__GET(slotno)))
#define SYS_LOCAL_MODULE_ISHAVEPP()  SYS_MODULE_SLOT_ISHAVEPP(SYS_LOCAL_MODULE_SLOTNO)

#define SYS_MODULE_ISHAVEFPGAPP(type) (VOS_YES == sys_module_have_fpgapp(type))
#define SYS_MODULE_SLOT_ISHAVEFPGAPP(slotno) (SYS_MODULE_ISHAVEFPGAPP(SYS_MODULE_TYPE(slotno)))


/**************************     槽位运行状态相关          	***************************/
#define SYS_MODULE_RUNNINGSTATE_GET(slotno)		(sys_module_running_state_get(slotno))		/*槽位的运行状态*/
#define SYS_LOCAL_MODULE_RUNNINGSTATE 		(SYS_MODULE_RUNNINGSTATE_GET(SYS_LOCAL_MODULE_SLOTNO_GET))	/*本板的运行状态*/
#define SYS_MODULE_IS_RUNNING(slotno)		(VOS_YES == sys_module_is_running(slotno))			/*槽位是否是RUNNING状态*/
#define SYS_MODULE_IS_READY(slotno) 		(VOS_YES == sys_module_is_ready(slotno))			/*槽位是否是READY状态*/
#define SYS_MODULE_IS_INSERTED(slotno)  (VOS_YES == sys_module_is_inserted(slotno))	/*槽位是否在位*/

extern ULONG g_SysInstallMode;
#define SYS_MODULE_IS_INSTALL_MODE (g_SysInstallMode)			/*板卡的安装模式，默认自动安装*/
/*******************************  End of File Body ***********************/
#endif

#ifdef __cplusplus
}
#endif

#endif
