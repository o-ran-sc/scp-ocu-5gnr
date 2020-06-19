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




#ifndef _VOS_BYTEORDER_H_
#define _VOS_BYTEORDER_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*
 * 下面两个宏为RPU软件定义另外字节顺序，也是
 * 两个互斥的宏。各个产品应该根据所采用CPU的类别恰当地设置
 *  default endian is little??
 *  #include <arpa/inet.h> for ntohl, ntohs, htons, htonl
 */
#include <arpa/inet.h>

#define	VOS_LITTLE_ENDIAN       (1)
#define	VOS_BIG_ENDIAN          (0)
#include <arpa/inet.h>


#if VOS_LITTLE_ENDIAN

#ifndef VOS_NTOHL /* 4字节 */
#if 0
#define VOS_NTOHL(x) ((((x) & 0xFF000000)>>24) |  (((x) & 0x00FF0000)>>8) | \
                       (((x) & 0x0000FF00)<<8 ) |  (((x) & 0x000000FF)<<24))
#endif
#define VOS_NTOHL(x) ntohl(x)
#endif

#ifndef VOS_NTOHS
#define VOS_NTOHS(x) ntohs(x)
#endif

#ifndef VOS_HTONL /* 4字节 */
#define VOS_HTONL(x) htonl(x)
#endif

#ifndef VOS_HTONS
#define VOS_HTONS(x) htons(x)
#endif

#elif VOS_BIG_ENDIAN

#ifndef VOS_NTOHL
#define VOS_NTOHL(x) (x)
#endif

#ifndef VOS_NTOHS
#define VOS_NTOHS(x) (x)
#endif

#ifndef VOS_HTONL
#define VOS_HTONL(x) (x)
#endif

#ifndef VOS_HTONS
#define VOS_HTONS(x) (x)
#endif
#else
"BYTEORDER not defined"
#endif /* VOS_LITTLE_ENDIAN */


#ifndef HAVE_MAKEWORD
#define HAVE_MAKEWORD
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#endif

#ifndef HAVE_MAKELONG
#define HAVE_MAKELONG
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#endif

#ifndef HAVE_LOWORD
#define HAVE_LOWORD
#define LOWORD(l)           ((WORD)(l))
#endif

#ifndef HAVE_HIWORD
#define HAVE_HIWORD
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#endif

#ifndef HAVE_LOBYTE
#define HAVE_LOBYTE
#define LOBYTE(w)           ((BYTE)(w))
#endif

#ifndef HAVE_HIBYTE
#define HAVE_HIBYTE
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _VOS_BYTEORDER_H_ */
