/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef __VOS_STRING_H__
#define __VOS_STRING_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/** 同 memcpy */
VOID *VOS_MemCpy(VOID * pcDest, const VOID * pcSrc, ULONG ulLen);

/** 同 memmove */
VOID *VOS_MemMove(VOID * pcDest, const VOID * pcSrc, ULONG ulLen);

/** 同 memset */
VOID *VOS_MemSet(VOID *pcBuf, CHAR cWhat, ULONG ulHowMany);

/** 同 memset(&var,0,sizeof(var)) */
VOID *VOS_MemZero(VOID *pcBuf, ULONG ulHowMany);

/** 同 memcmp */
LONG VOS_MemCmp(const VOID *pcBuf1, const VOID *pcBuf2, ULONG ulLen);

/** 同 strchr */
CHAR *VOS_StrChr(const CHAR *pcStr, CHAR cCh);

/** 同 strrchr */
CHAR *VOS_StrRChr(const CHAR *pcStr, CHAR cCh);

/** 同 strcat */
CHAR *VOS_StrCat(CHAR *pcDest, const CHAR *pcAppend);

/** 同 strncat */
CHAR *VOS_StrnCat(CHAR *pcDest, const CHAR *pcAppend, ULONG ulLen);

/** 同 strcpy */
CHAR *VOS_StrCpy(CHAR *pcDest, const CHAR *pcSrc);

/** 同 strncpy */
CHAR *VOS_StrnCpy(CHAR * pcDest,const CHAR *pcSrc, ULONG ulCount);

/** 同 strncmp */
ULONG VOS_StrnCmp(const CHAR * cs, const CHAR * ct, ULONG count);

/** 同 strcmp */
LONG VOS_StrCmp(const CHAR *szStr1, const CHAR *szStr2);

/** 同 strlen */
ULONG VOS_StrLen(const CHAR *szStr);

/** 同 strstr */
CHAR *VOS_StrStr(const CHAR *szStr, const CHAR *szToFind);

/** 同 strncmp */
CHAR *VOS_StrpBrk(const CHAR *szStr, const CHAR *szToFind);

/** 同 atol */
LONG VOS_AtoL(const CHAR *szString);

/** 同 strtol */
LONG VOS_StrToL(const CHAR *cp,CHAR **endp,INT base);

/** 同 strtoul */
ULONG VOS_StrToUL(const CHAR *szNptr, CHAR **szEndptr, INT ulBase );

/** 同 strtoll */
LONGLONG VOS_StrToLL(const CHAR *cp,CHAR **endp,INT base);

/** 同 strtoull */
ULONGLONG VOS_StrToULL(const CHAR *cp,CHAR **endp,INT base);

/** 同 strtok */
CHAR * VOS_StrToK(CHAR* strToken, const CHAR * strDelimit);

/** 同 atoi */
INT VOS_AtoI(const CHAR* s);

/** 同 strncasecmp */
ULONG VOS_StrnCaseCmp(const CHAR*, const CHAR*, ULONG ulLen);

/** 同 strcasecmp */
LONG VOS_StrCaseCmp(const CHAR *cs, const CHAR *ct);

/** 同 strnlen */
ULONG VOS_StrnLen(const CHAR * s, ULONG count);

/** 将字符串转换为小写 */
CHAR *VOS_StrToLower(CHAR *src);

/** 将字符串转换为大写 */
CHAR *VOS_StrToUpper(CHAR *src);


/** 
 * 复制字符串，申请大小为strlen(src)+1内存，然后将字符串拷入，并返回
 * @param[in]   src       源字符串
 * @param[in]   mod_id    模块ID
 * @return      成功返回新字符串的地址，失败返回NULL
 */
CHAR *VOS_StrDup (const CHAR *src,INT mod_id);


/** 
 * 复制字符串，并转换为小写，申请大小为strlen(src)+1内存，然后将字符串拷入，并返回
 * @param[in]   src       源字符串
 * @param[in]   mod_id    模块ID
 */
CHAR *VOS_StrDupToLower (const CHAR *src,INT mod_id);


/** 
 * 计算从左侧第一个不是空白字符起到字符串结尾的长度
 * @param[in]   szStr      字符串
* @return      字符串长度
*/
ULONG VOS_StrLeftTrimLen(const CHAR *szStr);


/** 
 * 将str 中的old字符替换成new字符
 * @param[in]   src      字符串
 * @param[in]   old      要替换的字符
 * @param[in]   new      替换成的字符
 * @return      返回指向src的指针
 */
CHAR *VOS_StrCharReplace(CHAR *src,const CHAR old,const CHAR new);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__VOS_STRING_H__*/
