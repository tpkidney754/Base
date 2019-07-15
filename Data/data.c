#include "data.h"

///*************************************************************************
/// Function:  MyItoa                                                      *
///                                                                        *
/// Description: Inputs a integer value and coverts into a stirng.         *
///                                                                        *
/// Parameters: uint8_t * str: pointer to a string                         *
///             int32_t data: interger to be converted into a string.      *
///             int32_t base: What base the integer is going to be         *
///                           converted to                                 *
/// Return Value:  int8_t: pass/fail value. A return of 0 is a successfull *
///                        conversion. Anything else is a failure.         *
///*************************************************************************
int8_t MyItoa( uint8_t * str, int32_t data, int32_t base )
{
   uint8_t negative = 0;
   uint32_t i = 0;
   if( data < 0 )
   {
      data *= -1;
      negative = 1;
   }
   uint8_t r = 0;
   do
   {
      //retrieves the value of the least signficant digit
      r = data % base;
      //adds the ascii base for a number, '0' = 0x30, or adds on
      //the value for the letrer if the number is larger than 9.
      r += ( r > 9 ) ? ASCIILETTERBASE : ASCIINUMBASE;
      *( str + i++ ) = r;
      //Divides by base to retrieve the next value during the following
      //loop iteration.
      data /= base;
   }while( data > 0 );

   if( negative )
   {
      *( str + i++ ) = '-';
   }
   //The string is currently in reverse format.
   MyReverse( str, i );
   //Cap it with a NULL value.
   *(str + i ) = '\0';
   //If the str pointer is valid return success else failure.
   return str ? 0 : -1;
}

///*************************************************************************
/// Function:  MyAtoi                                                      *
///                                                                        *
/// Description: Inputs a string and coverts into a signed interger.       *
///                                                                        *
/// Parameters: uint8_t * str: pointer to a string to be converted.        *
///                                                                        *
/// Return Value:  int32_t: integer value converted from the string input  *
///*************************************************************************
int32_t MyAtoi( uint8_t * str )
{
   int32_t num = 0;
   uint8_t negative = 0;
   uint8_t * start = NULL;
   uint32_t length = 0;
   uint32_t i = 0;
   uint32_t temp = 0;

   if( *str == '-' )
   {
      negative = 1;
      str++;
   }

   start = str;

   while( *str++ )
   {
      length++;
   }

   i = length-1;
   str = start;
   while( (temp = *str++) != '\0' )
   {
      temp -= ASCIINUMBASE;
      for( int j = 0; j < i; j++ )
      {
         temp *= 10;
      }
      i--;
      num += temp;
   }


   return negative ? -num : num;
}

///*************************************************************************
/// Function:  MyFtoi                                                      *
///                                                                        *
/// Description: Inputs floating point number and converts it to a string. *
///                                                                        *
/// Parameters: uint8_t * str: pointer to a string buffer that is filled.  *
///             float data: floating point number to be converted          *
///             int32_t decimalPlaces: How many decimal places to be       *
///                                    to be converted to a string.        *
///                                                                        *
/// Return Value:  int32_t: integer value converted from the string input  *
///*************************************************************************
int32_t MyFtoa( uint8_t * str, double data, int32_t decimalPlaces )
{
   if( str == NULL )
   {
      return -1;
   }

   uint32_t integral = 0;
   double fractal = 0.0;

   if( data < 0 )
   {
      data *= -1.0;
      *str++ = '-';
   }

   integral = ( uint32_t ) data;
   fractal = data - integral;

   MyItoa( str, integral, 10 );

   while( *str++ != '\0' );
   *( str - 1 ) = '.';

   uint8_t temp = 0;
   for( uint32_t i = 0; i < decimalPlaces; i++ )
   {
      fractal *= 10;
      temp = ( uint8_t ) fractal;
      fractal -= temp;
      *str++ = temp + ASCIINUMBASE;
   }

   *str = '\0';

   return str ? 0 : -1;
}

///*************************************************************************
/// Function:  DumpMemory                                                  *
///                                                                        *
/// Description: Prints whats stored in memory starting at pointed         *
///              passed in for the length passed in.                       *
///                                                                        *
/// Parameters: uint8_t * start: pointer to the start of memory desired to *
///                              be printed.                               *
///             uint32_t length: Number of bytes to be printed             *
/// Return Value:  void                                                    *
///*************************************************************************
void DumpMemory( uint8_t * start, uint32_t length )
{
   uint8_t buffer[ 4 ];
   for(uint32_t i = 0; i < length; i ++ )
   {
      // sprintf( buffer, "%02X ", *( start + i ) );
      LOG0( buffer );
   }
}

///*************************************************************************
/// Function:  BigtToLittle                                                *
///                                                                        *
/// Description: Converts a memory locaiton from big endian to             *
///              little endian. it is left to the user to know theat the   *
///              data being passed in is in big endian                     *
///                                                                        *
/// Parameters: uint8_t32: Value that is in big endian to be converted     *
///                        to little endian.                               *
///                                                                        *
/// Return Value:  int32_t: Return value of the resulting conversion       *
///*************************************************************************
int32_t BigToLittle( int32_t data )
{
   uint8_t byte0 = ( uint8_t ) ( ( data & BYTE3_MASK ) >> BYTE3_SHIFT );
   uint8_t byte1 = ( uint8_t ) ( ( data & BYTE2_MASK ) >> BYTE2_SHIFT );
   uint8_t byte2 = ( uint8_t ) ( ( data & BYTE1_MASK ) >> BYTE1_SHIFT );
   uint8_t byte3 = ( uint8_t ) ( ( data & BYTE0_MASK ) >> BYTE0_SHIFT );

   uint32_t returnData = byte0 << BYTE0_SHIFT | byte1 << BYTE1_SHIFT |
                    byte2 << BYTE2_SHIFT | byte3 << BYTE3_SHIFT;

   return returnData;


}

///*************************************************************************
/// Function:  littleToBig                                                 *
///                                                                        *
/// Description: Converts a memory locaiton from little endian to          *
///              little endian. it is left to the user to know theat the   *
///              data being passed in is in little endian                  *
///                                                                        *
/// Parameters: uint8_t32: Value that is in little endian to be converted  *
///                        to big endian.                                  *
///                                                                        *
/// Return Value:  int32_t: Return value of the resulting conversion       *
///*************************************************************************
int32_t LittleToBig( int32_t data )
{
   uint8_t byte3 = ( uint8_t ) ( ( data & BYTE3_MASK ) >> BYTE3_SHIFT );
   uint8_t  byte2 = ( uint8_t ) ( ( data & BYTE2_MASK ) >> BYTE2_SHIFT );
   uint8_t byte1 = ( uint8_t ) ( ( data & BYTE1_MASK ) >> BYTE1_SHIFT );
   uint8_t byte0 = ( uint8_t ) ( ( data & BYTE0_MASK ) >> BYTE0_SHIFT );

   uint32_t returnData = byte0 << BYTE3_SHIFT | byte1 << BYTE2_SHIFT |
                    byte2 << BYTE1_SHIFT | byte3 << BYTE0_SHIFT;

   return returnData;
}
