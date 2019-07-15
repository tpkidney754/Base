#include "memory.h"

uint8_t dmaComplete[ 4 ];
///*************************************************************************
/// Function:  MyMemMove                                                   *
///                                                                        *
/// Description: Moves a portion of memory to another location in memory.  *
///                                                                        *
/// Parameters: uint8_t * src: Start of memory to be moved.                *
///             uint8_t * dst: Start of memory to be copied to.            *
///             int32_t length: Number of bytes to be moved.               *
///                                                                        *
/// Return Value:  int8_t: pass/fail value. Success is a 0 value, all      *
///                        values are a failure.                           *
///*************************************************************************
int8_t MyMemMove( uint8_t * src, uint8_t * dst, uint32_t numBytes, uint8_t DMAch )
{
   if( src == NULL || dst == NULL )
   {
      return -1;
   }
   // Can use DMA for overlapping regions like this. So using slow method.
   if( ( dst > src ) && ( dst <= ( src + numBytes ) ) )
   {
      dst += numBytes;
      src += numBytes;
      for( int32_t i = numBytes; i >= 0; i-- )
      {
         *dst-- = *src--;
      }

      return dst ? 0 : -1;
   }

   // Option to use DMA for memmove
#ifdef FRDM
   if( DMAch == NO_DMA )
   {
#endif
      for( size_t i = 0; i < numBytes; i++ )
      {
         *dst++ = *src++;
      }

      return 0;
#ifdef FRDM
   }

   // Need more than 3 bytes to initiate 32bit transfers.
   if( numBytes > 3 )
   {
      uint8_t remainder = numBytes % 4;
      if( remainder )
      {
         // first transfer the number of bytes that can't
         // be moved with 32bit moves. 32bit moves require the
         // total number of bytes to be divisible by 4.
         StartTransfer8bitMoves( DMAch, src, dst, remainder );
         src += remainder;
         dst += remainder;
         numBytes -= remainder;
         // wait until the 8bit move is done before moving the rest
         // becuase the channel is tied up.
         while( dmaComplete[ DMAch ] == 0 );
      }
      // Transfer remaining bytes, numBytes will be divisible by four now.
      StartTransfer32bitMoves( DMAch, src, dst, numBytes );

      return 0;
   }
   //not enough bytes for 32bit transfers.
   StartTransfer8bitMoves( DMAch, src, dst, numBytes );

   return 0;
#endif
}

///*************************************************************************
/// Function:  MyMemSet                                                    *
///                                                                        *
/// Description: Moves a value to a number of bytes in memory using DMA.   *
///                                                                        *
/// Parameters: uint8_t * src: Start of memory to be set                   *
///             uin32_t value: value to set in memory
///             int32_t length: Number of bytes to be set                  *
///                                                                        *
/// Return Value:  int8_t: pass/fail value. Success is a 0 value, all      *
///                        values are a failure.                           *
///*************************************************************************
int8_t MyMemSet( uint8_t * dst, uint32_t value, size_t numBytes, uint8_t DMAch )
{
   if( dst == NULL )
   {
      return -1;
   }

#ifdef FRDM
   if( numBytes > 3 )
   {
      uint8_t remainder = numBytes % 4;
      if( remainder )
      {
         MemSet8bit( DMAch, ( uint8_t ) value, dst, remainder );
         dst += remainder;
         numBytes -= remainder;
         while( dmaComplete[ DMAch ] == 0 );
      }

      MemSet32bit( DMAch, value, dst, numBytes );

      return 0;
   }
   // Not enough bytes to do 32bit transfers.
   MemSet8bit( DMAch, ( uint8_t ) value, dst, numBytes );
#else
   for( size_t i = 0; i < numBytes; i++ )
   {
      *dst++ = ( uint8_t ) value;
   }
#endif
   return dst ? 0 : -1;
}

///*************************************************************************
/// Function:  MyReverse                                                   *
///                                                                        *
/// Description: Reverses the bytes starting at a location given           *
///                                                                        *
/// Parameters: uint8_t * src: Start of memory to be reversed              *
///             int32_t length: Number of bytes to be revversed            *
///                                                                        *
/// Return Value:  int8_t: pass/fail value. Success is a 0 value, all      *
///                        values are a failure.                           *
///*************************************************************************
int8_t MyReverse( uint8_t * src, uint32_t length )
{
   if( src == NULL )
   {
      return -1;
   }

   int32_t loopLength = length--/2;

   for( int32_t i = 0; i < loopLength; i++ )
   {
      // A XOR B XOR A = B
      // A = *( src + i )
      // B = *( src + length - i )

      // A = A ^ B;
      *( src + i ) ^= *( src + length - i );
      // B = B ^ A = B ^ A ^ B = A
      *( src + length - i ) ^= *( src + i );
      // A = A ^ B = A ^ B ^ A = B
      *( src + i ) ^= *( src + length - i );
   }

   return src ? 0 : -1;
}

///*************************************************************************
/// Function:  MyStringLength                                              *
///                                                                        *
/// Description: Reverses the bytes starting at a location given           *
///                                                                        *
/// Parameters: uint8_t * src: Start of memory to be reversed              *
///             int32_t length: Number of bytes to be revversed            *
///                                                                        *
/// Return Value:  int8_t: pass/fail value. Success is a 0 value, all      *
///                        values are a failure.                           *
///*************************************************************************
int32_t MyStrLen( uint8_t * str )
{
   if( str == NULL )
   {
      return -1;
   }

   int32_t length = 0;

   while( *str++ != '\0' )
   {
      length++;
   }

   return length;
}
