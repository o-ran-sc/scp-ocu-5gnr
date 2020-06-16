/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#include "vos_sys_diff.h"

#ifndef _VOS_TYPES_H_
#define _VOS_TYPES_H_

#ifdef __cplusplus
    extern "C" {
#endif
#include <stddef.h>

#define VOS_NAME_MAX_LENGTH     128                 /* VOS有名字的对象的名字的最大长度. */


#define VOS_YES    (1)
#define VOS_NO     (0)

#define VOS_OK     (0)
#define VOS_ERROR (-1)

#define VOS_FALSE               (0)
#define VOS_TRUE                (1)

#define CONST               const
#define VOS_PACKED          __attribute__((packed))

typedef struct VOS_MAC_addr_s{
    unsigned char addr[6];
}VOS_PACKED VOS_MAC_addr_t;

typedef struct VOS_IPv4_addr_s{
    unsigned long addr;
}VOS_PACKED VOS_IPv4_addr_t;

typedef struct VOS_IPv6_addr_s{
    unsigned char addr[16];
}VOS_PACKED VOS_IPv6_addr_t;


typedef void                VOID;
typedef int                 BOOL;

typedef char                CHAR;
typedef unsigned char       UCHAR;

typedef short               SHORT;
typedef unsigned short      USHORT;


typedef int                 INT;
typedef unsigned int        UINT;

typedef long                LONG;
typedef unsigned long       ULONG;

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
typedef float               FLOAT;


typedef char                *LPSTR;
typedef const char          *LPCSTR;
typedef unsigned long       *PULONG;

typedef LONG                 LRESULT;
typedef void                *VOS_HANDLE;


typedef char                 INT8;
typedef unsigned char        UINT8;

typedef short                INT16;
typedef unsigned short       UINT16;

typedef int                  INT32;
typedef unsigned int         UINT32;

typedef long                 INT64;
typedef unsigned long        UINT64;


#if 0
#if defined __GNUG__
#define NULL (__null)
#else
#if !defined(__cplusplus) && 0
#define NULL ((void*)0)
#else
#define NULL (0)
#endif
#endif
#endif

#if defined (OS_LINUX)

#ifndef HAVE_DOUBLE
#define HAVE_DOUBLE
typedef double              DOUBLE;
#endif

#ifndef HAVE_PUSHORT
#define HAVE_PUSHORT
typedef unsigned short      *PUSHORT;
#endif

#ifndef HAVE_PUCHAR
#define HAVE_PUCHAR
typedef unsigned char       *PUCHAR;
#endif


#ifndef HAVE_PFLOAT
#define HAVE_PFLOAT
typedef FLOAT               *PFLOAT;
#endif

#ifndef HAVE_PBOOL
#define HAVE_PBOOL
typedef int                 *PBOOL;
#endif

#ifndef HAVE_LPBOOL
#define HAVE_LPBOOL
typedef int                 *LPBOOL;
#endif

#ifndef HAVE_PBYTE
#define HAVE_PBYTE
typedef BYTE                *PBYTE;
#endif

#ifndef HAVE_LPBYTE
#define HAVE_LPBYTE
typedef BYTE                *LPBYTE;
#endif

#ifndef HAVE_PINT
#define HAVE_PINT
typedef int                 *PINT;
#endif

#ifndef HAVE_LPINT
#define HAVE_LPINT
typedef int                 *LPINT;
#endif

#ifndef HAVE_PWORD
#define HAVE_PWORD
typedef WORD                *PWORD;
#endif

#ifndef HAVE_LPWORD
#define HAVE_LPWORD
typedef WORD                *LPWORD;
#endif

#ifndef HAVE_LPLONG
#define HAVE_LPLONG
typedef long                *LPLONG;
#endif

#ifndef HAVE_PDWORD
#define HAVE_PDWORD
typedef DWORD               *PDWORD;
#endif

#ifndef HAVE_LPDWORD
#define HAVE_LPDWORD
typedef DWORD               *LPDWORD;
#endif

#ifndef HAVE_LPVOID
#define HAVE_LPVOID
typedef void                *LPVOID;
#endif

#ifndef HAVE_LPCVOID
#define HAVE_LPCVOID
typedef const void          *LPCVOID;
#endif

#ifndef HAVE_PUINT
#define HAVE_PUINT
typedef unsigned int        *PUINT;
#endif

/* Types use for passing & returning polymorphic values */
#ifndef HAVE_WPARAM
#define HAVE_WPARAM
typedef unsigned int        WPARAM;
#endif

#ifndef HAVE_LPARAM
#define HAVE_LPARAM
typedef LONG                LPARAM;
#endif

#ifndef HAVE_LRESULT
#define HAVE_LRESULT
typedef LONG                LRESULT;
#endif


#ifndef HAVE_LONGLONG
#define HAVE_LONGLONG
typedef long long           LONGLONG;
#endif

#ifndef HAVE_ULONGLONG
#define HAVE_ULONGLONG
typedef unsigned long long  ULONGLONG;
#endif

#ifndef HAVE_longlong
#define HAVE_longlong
typedef long long longlong;
#endif

#ifndef HAVE_ulonglong
#define HAVE_ulonglong
typedef unsigned long long ulonglong;
#endif

#if OS_LINUX
#define inline  
#define _inline 
#define __inline__ 
#define __const__  const
#define __signed__ signed
#define __const__ const
#endif

/* base 32*/

#define VOS_ERR_OUT VOS_Printf("error! %s(%u),%s\r\n",__FILE__,__LINE__,__func__)
#define VOS_VAL_OUT(a) VOS_Printf("\r\n var(%s),value(%d),%s(%u),%s\r\n",(#a),(a),__FILE__,__LINE__,__func__)
#define VOS_VAL_OUT_U(a) VOS_Printf("\r\n var(%s),value(%u),%s(%u),%s\r\n",(#a),(a),__FILE__,__LINE__,__func__)
#define VOS_STR_OUT(a) VOS_Printf("\r\n %s,%s(%u),%s\r\n",(a),__FILE__,__LINE__,__func__)


/* 求余 */
#define __VOS_RESIDUE( _n, _2_exp )     (((_n)<<(32-(_2_exp)))>>(32-(_2_exp)))

/* 求商 */
#define __VOS_QUOTIENT( _n, _2_exp )    ((_n)>>(_2_exp))

/* 去尾取整 */
#define __VOS_INTZERO( _n, _2_exp )     (__VOS_QUOTIENT( _n, _2_exp )<<(_2_exp))

/* 进位取整 */
#define __VOS_INTINCR( _n, _2_exp )     \
        ((__VOS_QUOTIENT( _n, _2_exp ) + (0==__VOS_QUOTIENT( __VOS_RESIDUE( _n, _2_exp ), _2_exp ))?0:1)<<(_2_exp))


#endif

#define CL_LIB_AF_INET6 10
#define CL_LIB_AF_INET  2

typedef struct{
    UINT family;
    union {
        /** IPv4 addr  */
        UINT ip4;
        /** IPv6 addr structure */
        union 
        {
            UCHAR     addr8[16];
            USHORT    addr16[8];
            UINT      addr32[4];
        } ip6;
    }addr;
}VOS_IP_t;

#define VOS_SNMP_DateAndTime_SIZE 8
typedef struct VOS_SNMP_DateAndTime_s{
    CHAR DateAndTime[VOS_SNMP_DateAndTime_SIZE];
}VOS_SNMP_DateAndTime_t;


#ifdef __cplusplus
    }
#endif

#endif /*_VOS_TYPES_H_*/
