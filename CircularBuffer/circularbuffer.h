#ifndef __CIRCBUFF__
#define __CIRCBUFF__

#include "includeall.h"

typedef struct CircularBuffer_t
{
   void * bufferStart;
   void * head;
   void * tail;
   void * bufferEnd;
   uint32_t size;
   uint32_t numItems;
   uint32_t itemSize;
} CircularBuffer_t;

typedef enum BufferState
{
   BUFFER_NOT_FULL = 0,
   BUFFER_FULL = 1,
   BUFFER_NOT_EMPTY = 0,
   BUFFER_EMPTY = 1
} BufferState_e;

void CBufferInit(CircularBuffer_t* pCb, void* data, uint32_t itemSize, uint32_t maxItems);
BufferState_e IsBufferFull(CircularBuffer_t* cb);
BufferState_e IsBufferEmpty(CircularBuffer_t* cb);
BufferState_e CBufferAdd(CircularBuffer_t* cb, void* data, uint8_t DMAch);
BufferState_e CBufferAddItems(CircularBuffer_t* cb, void* data, uint32_t numToAdd, uint8_t DMAch);
BufferState_e CBufferRemove(CircularBuffer_t* cb, void* data, uint8_t DMAch);

#endif //__CIRCBUFF__
