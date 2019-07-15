#ifndef __DMA__
#define __DMA__

#include "includeall.h"

typedef enum DMAErrors
{
   DMANoError = 0,
   DMANot16bitTransferSize,
   DMANot32bitTransferSize,
} DMAErrors_e;

typedef enum TransferSize
{
   _32bit = 0,
   _8bit,
   _16bit,
   Reserved
} TransferSize_e;

typedef enum BufferSize
{
   BufferDisabled = 0,
   _16Bytes,
   _32Bytes,
   _64Bytes,
   _128Bytes,
   _256Bytes,
   _512Bytes,
   _1kBytes,
   _2kBytes,
   _4kBytes,
   _8kBytes,
   _16kBytes,
   _32kBytes,
   _64kBytes,
   _128kBytes,
   _256kBytes
} BufferSize_e;

void InitDMA( uint8_t ch );
DMAErrors_e StartTransfer32bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes );
DMAErrors_e StartTransfer16bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes );
DMAErrors_e StartTransfer8bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes );
DMAErrors_e MemSet32bit( uint8_t ch, uint32_t data, uint8_t * dst, uint32_t numBytes );
DMAErrors_e MemSet8bit( uint8_t ch, uint8_t data, uint8_t * dst, uint32_t numBytes );

#define MASK_32BIT         0xFFFFFFFF
#define DMA_BCR_SIZE_MASK  0x0FFFFF

#define NO_DMA             0xFF

#endif
