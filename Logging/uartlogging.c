#include "uartlogging.h"

CircularBuffer_t * TXBuffer;
uint8_t dmaComplete[ 4 ];
CircularBuffer_t * UART0_TXBuffer;

///*************************************************************************
/// Function:  LOG0                                                        *
///                                                                        *
/// Description: Receives a string and sends it to either UART or printf   *
///              depending on the architecture.                            *
///                                                                        *
/// Parameters: uint8_t * data: String to passed to next function.         *
///             uint32_t length: Length of data to be sent out.            *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void LOG0( uint8_t * data )
{
   uint32_t length = MyStrLen( data );
   for( uint32_t i = 0; i < length; i++ )
   {

      if( CBufferAdd( UART0_TXBuffer, ( data + i ), DMACH_UART0TX ) == BUFFER_FULL )
      {
         while( IsBufferFull( UART0_TXBuffer ) == BUFFER_FULL );
         CBufferAdd( UART0_TXBuffer, ( data + i ), DMACH_UART0TX );
      }
   }
   SET_BIT_IN_REG( UART0_C2, UART0_C2_TIE_MASK );
}

///*************************************************************************
/// Function:  LOG1                                                        *
///                                                                        *
/// Description: Receives a string and a set of parameters that are either *
///              ints or floats.                                           *
///                                                                        *
/// Parameters: uint8_t * data: String to add the parameters onto.         *
///             uint32_t length: Length of the original string.            *
///             DataType_t dataType: Is the data an int or a float?        *
///             uint32_t numParams: How many parameters are being passed?  *
///             ... : parameters to be added onto the string.              *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
// void LOG1( uint8_t * data, uint32_t length, DataType_t dataType, uint32_t numParams, ... )
// {
//    va_list valist;
//    va_start( valist, numParams );

//    uint8_t * dataHead = data;

//    // Increment data to the end of the string and replace the null character
//    // with a space.
//    data += length;
//    if( length != 0 )
//    {
//       *data++ = ' ';
//    }
//    // Then loop throug the number of parameters passed to add to the string.
//    for( uint32_t i = 0; i < numParams; i++ )
//    {
//       switch( dataType )
//       {
//          case int_e:
//             MyItoa( data, va_arg( valist, int ), 10 );
//             break;
//          case double_e:
//             MyFtoa( data, va_arg( valist, double ), 5 );
//             break;
//       }
//       // Now find the numbers of characters added onto the string.
//       length = MyStrLen( data );
//       //Increment data to the next \0 character
//       data += length;
//       //Replace \0 with a 0
//       *data++ = ' ';
//    }
//    // All parameters have been added, now cap the string with a \0
//    *( data - 1 ) = '\n';
//    *( data ) = '\0';
//    // And then pass it to LOG0 to send out.
//    LOG0( dataHead );
// }
