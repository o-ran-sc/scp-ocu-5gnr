/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/



#ifndef _VOS_CTYPE_H
#define _VOS_CTYPE_H

#include "vos_types.h"

/*
 * NOTE! This ctype does not handle EOF like the standard C
 * library is required to.
 */

#define _VOS_U	0x01	/* upper */
#define _VOS_L	0x02	/* lower */
#define _VOS_D	0x04	/* digit */
#define _VOS_C	0x08	/* cntrl */
#define _VOS_P	0x10	/* punct */
#define _VOS_S	0x20	/* white space (space/lf/tab) */
#define _VOS_X	0x40	/* hex digit */
#define _VOS_SP	0x80	/* hard space (0x20) */

extern unsigned char _vos_ctype[];

#define __vos_ismask(x) (_vos_ctype[(int)(unsigned char)(x)])

/** 同 isalnum */
#define vos_isalnum(c)	((__vos_ismask(c)&(_VOS_U|_VOS_L|_VOS_D)) != 0)

/** 同 isalpha */
#define vos_isalpha(c)	((__vos_ismask(c)&(_VOS_U|_VOS_L)) != 0)

/** 同 iscntrl */
#define vos_iscntrl(c)	((__vos_ismask(c)&(_VOS_C)) != 0)

/** 同 isdigit */
#define vos_isdigit(c)	((__vos_ismask(c)&(_VOS_D)) != 0)

/** 同 isgraph */
#define vos_isgraph(c)	((__vos_ismask(c)&(_VOS_P|_VOS_U|_VOS_L|_VOS_D)) != 0)

/** 同 islower */
#define vos_islower(c)	((__vos_ismask(c)&(_VOS_L)) != 0)

/** 同 isprint */
#define vos_isprint(c)	((__vos_ismask(c)&(_VOS_P|_VOS_U|_VOS_L|_VOS_D|_VOS_SP)) != 0)

/** 同 ispunct */
#define vos_ispunct(c)	((__vos_ismask(c)&(_VOS_P)) != 0)

/** 同 isspace */
#define vos_isspace(c)	((__vos_ismask(c)&(_VOS_S)) != 0)

/** 同 isupper */
#define vos_isupper(c)	((__vos_ismask(c)&(_VOS_U)) != 0)

/** 同 isxdigit */
#define vos_isxdigit(c)	((__vos_ismask(c)&(_VOS_D|_VOS_X)) != 0)

/** 同 isascii */
#define vos_isascii(c) (((unsigned char)(c))<=0x7f)

/** 同 toascii */
#define vos_toascii(c) (((unsigned char)(c))&0x7f)

/** 同 tolower */
UCHAR vos_tolower(UCHAR c);

/** 同 toupper */
UCHAR vos_toupper(UCHAR c);

#endif
