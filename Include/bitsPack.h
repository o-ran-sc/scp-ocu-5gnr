/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/


#ifndef __BITS_PACK_H__
#define __BITS_PACK_H__

#include "vos_types.h"

/* Dependencies ------------------------------------------------------------- */

/* Constants ---------------------------------------------------------------- */

/*
 * The Bits operation type.
 */
typedef enum bitOptType
{
    BIT_PACKED,     /* Packed bits. */
    BIT_UNPACKED    /* Unpacked bits. */
} BitOptType_t;

/* Types -------------------------------------------------------------------- */

/*
 * Type of Bits for pack message operation.
 */
typedef struct bitOpt
{
    UINT8 *pMsg;       /* Point to the message whitch packed or unpacked */
    UINT32 bitOffset;      /* The bit offset from the start of msg_p. */
    UINT32 msgLen;         /* The total length of the message. */
} BitOpt_t;


/* Globals ------------------------------------------------------------------ */

extern INT32 unpackBitsWithdebug(BitOpt_t *pBit, UINT32 n,unsigned char *fun, unsigned long line);
extern INT32 packBitsWithdebug(BitOpt_t *pBit, UINT32 n, UINT32 value,unsigned char *fun, unsigned long line);
/* Functions ---------------------------------------------------------------- */
/*******************************************************************************
 * Convert length of bits to length of bytes.
 *
 * Input: bitLen : The lenght of bits.
 *
 * Output: return the length of bytes.
 ******************************************************************************/
extern UINT32 convertBitlen2Bytelen(UINT32 bitLen);

/*******************************************************************************
 * Get the length of message.
 *
 * Input: pBit : The pointer to struct bit operation.
 *
 * Output: return the length of message, or -1 when filed.
 ******************************************************************************/
extern INT32 getBitsMsgLen(BitOpt_t *pBit, UINT32 optType);


/*******************************************************************************
 * Show every bits of memory.
 *
 * Input: pMsg: The start pointer of memory.
 *        msgLen: The length of memory.
 *        lable: The lable of the memory.
 *
 * Output: None.
 ******************************************************************************/
extern void showBits(UINT8 *pMsg, UINT32 msgLen, INT8 *name);

/*******************************************************************************
 * Initial the struct of BitOpt.
 *
 * Input: pBit : The pointer to struct bit operation.
 *        pMsg : Point to the message, that will be packed or unpacked.
 *        msgLen : The length of message.
 *        bitOffset : The bit offset from the start of msg_p;
 *
 * Output: return 0, or -1 when filed.
 ******************************************************************************/
extern INT32 initBits(BitOpt_t *pBit, UINT8 *pMsg, UINT32 msgLen, UINT8 bitOffset);

/*******************************************************************************
 * Skip n bits in packed or unpacked operation. Pack operation, not insure the
 * validity of the bits that ware sikped.
 *
 * Input: pBit : The pointer to struct bit operation.
 *        n : The number of bits will be skiped.
 *
 * Output: return 0, or -1 when filed.
 ******************************************************************************/
extern INT32 skipBits(BitOpt_t *pBit, UINT32 n, UINT8 optType);

/*******************************************************************************
 * Unpack n bits from message, not support 32 bits or more.
 *
 * Input: pBit : The pointer to struct bit operation.
 *        n : The number of bits will be unpacked.
 *        msgLen : The length of message.
 *
 * Output: return the unpacked value, or -1 when error occur.
 ******************************************************************************/
#define unpackBits(pBit,n)  unpackBitsWithdebug(pBit,  n,(UCHAR *)__func__,__LINE__)

/*******************************************************************************
 * Pack the value into message with n bits, not support more than 32 bits.
 *
 * Input: pBit : The pointer to struct bit operation.
 *        n : The number of bits will be packed.
 *        value : The value need pacded into message.
 *
 * Output: return the length of message after packed, or -1 when filed.
 ******************************************************************************/
#define packBits(pBit,n,value) packBitsWithdebug(pBit,  n,  value,(UCHAR *)__func__,__LINE__)

#endif




