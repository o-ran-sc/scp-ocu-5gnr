/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include "vos_common.h"
#include "vos_time.h"
#include "vos_cli.h"
#include "plat_alarm.h"
#include "plat_db.h"
#include "gnbCommon.h"
#include "cuCommon.h"
#include "omCuupApi.h"
extern UCHAR cuupUnSocketPath[];
INT32 cuupGetSetUpPara(INT32 argc, INT8 **argv)
{
	UCHAR *pInt = NULL;
	
	struct option long_options[] =
	{
		{"startup-item",	required_argument,	0,	'i' },
		{"version", 		no_argument,		0,	'v' },
		{"help",			no_argument,		0,	'h' },
		{0, 				0,					0,	0 }
	};
	
	while (1)
	{
		int option_index = 0;
		int c = getopt_long(argc, argv, "i:vh", long_options, &option_index);
		if (c == -1)
		{
			break;
		}
		
		switch (c)
		{
			case 'i':
				pInt = (UCHAR *)cuupUnSocketPath;
				break;
			case 'v': 
				exit(0);
				break;
			case 'h':
				exit(0);
            default:
                return VOS_OK;
		}
	
		if (pInt && optarg)
		{
			sscanf(optarg, "%s", pInt);
			VOS_Printf("unSocketPath: %s\n", cuupUnSocketPath);
		}
	}
	
	return VOS_OK;
}

void cuupAppSigHandler(int sig)
{            
    VOS_Printf("\r\nReceive signal:%d\r\n",sig);
    
    if(SIGSEGV == sig)
    {
        if(shm_unlink(CUUP_SHM_FILE) < 0)
        {
            VOS_Printf("Du_shm Delete CUUP_SHM_FILE shared memory failed !\n ");
            return;
        }
       signal(sig, SIG_DFL);
       kill(getpid(), sig);
    }
    else if(SIGINT == sig)
    {
    }
    else if(SIGABRT == sig)
    {
        if(shm_unlink(CUUP_SHM_FILE) < 0)
        {
            VOS_Printf("Du_shm Delete CUUP_SHM_FILE shared memory failed !\n ");
            return;
        }    
    }
    return;
}

INT32 cuupAppregisterSignal()
{

    /*9:SIGSEGV signal*/
    if ( Product_Signal( SIGSEGV, 0,cuupAppSigHandler ) == VOS_ERROR )
    {
        /*commomctrl_om_init_fail_rsp(0);*/
        return VOS_ERROR;
    }

    if ( Product_Signal( SIGINT, 0,cuupAppSigHandler ) == VOS_ERROR )
    {

        return VOS_ERROR;
    }

    /*2:capture signal*/
    if ( Product_Signal( SIGABRT,0,cuupAppSigHandler ) == VOS_ERROR )
    {
        /*commomctrl_om_init_fail_rsp(0);*/
        return VOS_ERROR;
    }
    return VOS_OK;
}

/*
    function name: main
    function:      协议栈入口函数
    para:          无
    return value:  VOS_OK,VOS_ERROR
*/
INT32 main(int argc,INT8 **argv)
{
    /*check para*/
    
    CHECK_FUNCTION_RET(cuupGetSetUpPara(argc,argv));

    /*init cucp global var*/
    CHECK_FUNCTION_RET(cuupAppGlobalVarInit());
    
    /*platform init*/
    CHECK_FUNCTION_RET(cuupAppPlatformInit(argv));
	
    /*register signal*/
    CHECK_FUNCTION_RET(cuupAppregisterSignal());
    /*VOS_TaskInfoAttach 必须在main函数里调用*/
    
    /*omadp vos task create*/
    CHECK_FUNCTION_RET(cuupAppOmadpModuleInit());
    
    while(1)
    {
        sleep(5000);

    }   
    return 0;
}






