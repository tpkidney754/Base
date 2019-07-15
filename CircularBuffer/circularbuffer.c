#include "circularbuffer.h"

uint8_t dmaComplete[4];

///*************************************************************************
/// Function:  CBufferInit                                                 *
///                                                                        *
/// Description: Initializes a circular buffer.                            *
///                                                                        *
/// Parameters: uint32_t itemSize: Size of each item in the buffer in bytes*
///             uint32_t maxItems: Maximum number of items that the buffer *
///                                can hold.                               *
///                                                                        *
/// Return Value:  CircularBuffer_t *: pointer to the circular buffer data *
///                                    structure.                          *
///*************************************************************************
void CBufferInit(CircularBuffer_t* pCb, void* data, uint32_t itemSize, uint32_t maxItems)
{
   pCb->bufferStart = data;
   pCb->head = pCb->bufferStart;
   pCb->tail = pCb->bufferStart;
   pCb->bufferEnd = pCb->bufferStart + (maxItems * itemSize) - 1;
   pCb->numItems = 0;
   pCb->itemSize = itemSize;
   pCb->size = maxItems;

   pCb->head = pCb->bufferStart;
   pCb->tail = pCb->bufferStart;
   pCb->bufferEnd = pCb->bufferStart + ( maxItems * itemSize ) - 1;
   pCb->numItems = 0;
   pCb->itemSize = itemSize;
   pCb->size = maxItems;
}

///*************************************************************************
/// Function:  IsBufferFull                                                *
///                                                                        *
/// Description: Returns a status if the buffer is full or not             *
///                                                                        *
/// Parameters: CircularBuffer_t * cb: pointer to the buffer being checked.*
///                                                                        *
/// Return Value: BufferState_e: enumeration of buffer status.             *
///*************************************************************************
inline BufferState_e IsBufferFull( CircularBuffer_t * cb )
{
   // Simple check to see if the number of items placed in the buffer
   // that have not been read is the same as the size of the buffer.
   return ( cb->numItems == cb->size ) ? BUFFER_FULL : BUFFER_NOT_FULL;
}

///*************************************************************************
/// Function:  IsBufferEmpty                                               *
///                                                                        *
/// Description: Returns a status if the buffer is empty or not            *
///                                                                        *
/// Parameters: CircularBuffer_t * cb: pointer to the buffer being checked.*
///                                                                        *
/// Return Value: BufferState_e: enumeration of buffer status.             *
///*************************************************************************
inline BufferState_e IsBufferEmpty( CircularBuffer_t * cb )
{
   // Simple check to see if anything has been written to the buffer
   // that has not been read.
   return ( cb->numItems == 0 ) ? BUFFER_EMPTY : BUFFER_NOT_EMPTY;
}

///*************************************************************************
/// Function:  CBufferAdd                                                  *
///                                                                        *
/// Description: Adds a value to the buffer                                *
///                                                                        *
/// Parameters: CircularBuffer_t * cb: pointer to the buffer that the item *
///                                    is being added to.                  *
///             void * data: Pointer to the data being added to the buffer *
///             uint8_t DMAch: DMA channel being used to transfer the data.*
///                            If DMAch is 0xFF, then software is used for *
///                            the transfer.                               *
///                                                                        *
/// Return Value:  CBufferState_e: enumeration of buffer status.           *
///*************************************************************************
inline BufferState_e CBufferAdd( CircularBuffer_t * cb, void * data, uint8_t DMAch )
{
   if( IsBufferFull( cb ) )
   {
      return BUFFER_FULL;
   }

   MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, cb->itemSize, DMAch );
   cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                              ( uint8_t * ) ( cb->head + cb->itemSize );
   cb->numItems++;
}

///*************************************************************************
/// Function:  CBufferAdd                                                  *
///                                                                        *
/// Description: Adds multiple values to the buffer with the use of DMA.   *
///              The function currently does not work and is very          *
///              complicated. This would help improve performance of the   *
///              DMA transfers if needed.                                  *
///                                                                        *
/// Parameters: CircularBuffer_t * cb: pointer to the buffer that the item *
///                                    is being added to.                  *
///             void * data: Pointer to the data being added to the buffer *
///             uint32_t numToAdd: Number of items to be added.            *
///             uint8_t DMAch: DMA channel being used to transfer the data.*
///                            If DMAch is 0xFF, then software is used for *
///                            the transfer.                               *
///                                                                        *
/// Return Value:  CBufferState_e: enumeration of buffer status.           *
///*************************************************************************
BufferState_e CBufferAddItems( CircularBuffer_t * cb, void * data,
                               uint32_t numToAdd, uint8_t DMAch )
{
   if( IsBufferFull( cb ) )
   {
      return BUFFER_FULL;
   }

   // If the total items is going to wrap the buffer, first add items to the end of the buffer.
   if( (cb->head + ( cb->itemSize * numToAdd ) ) >= cb->bufferEnd )
   {
      // if the first move is going to fill up the buffer, add items that fill up the buffer.
      // otherwise, fill up the buffer to the end point before wrapping.
      uint32_t firstMove = ( cb->numItems + numToAdd ) >= cb->size ?
                                                          cb->size - cb->numItems :
                                                        ( cb->bufferEnd - cb->head ) / cb->itemSize;
      // Start first transfer
      MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, firstMove * cb->itemSize, DMAch );

      // Set the head to current value of the DMA destination pointer.
      cb->head += firstMove * cb->itemSize;
      // Wrap if needed.
      cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                                 ( uint8_t * ) ( cb->head + cb->itemSize );
      // Increment numItems as needed.
      cb->numItems += firstMove;
      // If the first move filled up the buffer then return.
      if( IsBufferFull( cb ) )
      {
         return BUFFER_FULL;
      }
      // Wait until first transfer is complete.
      while( dmaComplete[ DMAch ] == 0 );

      numToAdd -= firstMove;
      uint32_t secondMove = ( cb->numItems + numToAdd ) >= cb->size ?
                                                           cb->size - cb->numItems :
                                                           numToAdd;
      // StartSecondTransfer
      MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, secondMove * cb->itemSize, DMAch );
      // Increment head to the end of the second transfer.
      cb->head += secondMove * cb->itemSize;
      // Increment head as needed.
      cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                                 ( uint8_t * ) ( cb->head + cb->itemSize );
      cb->numItems += secondMove;

      return IsBufferFull( cb );
   }
   // No buffer wrap will take place
   // Now there is a need to make sure that the numItems wont overfill buffer
   if( numToAdd + cb->numItems >= cb->size )
   {
      numToAdd = cb->size - cb->numItems;

      MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, numToAdd * cb->itemSize, DMAch );
      // Increment head to the end of the second transfer.
      cb->head += numToAdd * cb->itemSize;
      // Increment head as needed.
      cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                                 ( uint8_t * ) ( cb->head + cb->itemSize );
      cb->numItems += numToAdd;

      return IsBufferFull( cb );
   }

   MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, numToAdd * cb->itemSize, DMAch );
   cb->head += numToAdd * cb->itemSize;
   cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                              ( uint8_t * ) ( cb->head + cb->itemSize );
   cb->numItems += numToAdd;

   return IsBufferFull( cb );
}

///*************************************************************************
/// Function:  CBufferRemove                                               *
///                                                                        *
/// Description: Removes a value from the buffer                           *
///                                                                        *
/// Parameters: CircularBuffer_t * cb: pointer to the buffer that the item *
///                                    is being removed from.              *
///             void * data: Pointer to memory that the item will be placed*
///             uint8_t DMAch: DMA channel being used to transfer the data.*
///                            If DMAch is 0xFF, then software is used for *
///                            the transfer.                               *
///                                                                        *
/// Return Value:  CBufferState_e: enumeration of buffer status.           *
///*************************************************************************
inline BufferState_e CBufferRemove( CircularBuffer_t * cb, void * data, uint8_t DMAch )
{
   if( IsBufferEmpty( cb ) )
   {
      return BUFFER_EMPTY;
   }

   MyMemMove( ( uint8_t *) cb->tail, ( uint8_t *) data, cb->itemSize, DMAch );
   cb->tail = ( cb->tail == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                              ( uint8_t * ) ( cb->tail + cb->itemSize );
   cb->numItems--;
}
