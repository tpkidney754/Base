#ifdef TESTING
#include "datatesting.h"
#include <string.h>
#include <stdio.h>

static uint8_t headerBuffer[HEADER_LENGTH];
static uint8_t testPrintBuffer[HEADER_LENGTH];

///*************************************************************************
/// Function:  DataTesting                                                 *
///                                                                        *
/// Description: Main function that calls all individual unit tests.        *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void DataTesting( )
{
   MyItoaUnitTest( );
   MyAtoiUnitTest( );
   MyFtoaUnitTest( );
   BigToLittleUnitTest( );
   LittleToBigUnitTest( );
}

///*************************************************************************
/// Function:  MyItoaUnitTest                                              *
///                                                                        *
/// Description: Sends a known input to MyItoa and then compares it's      *
///              output with a known output. The test will fail if the     *
///              output of the function does not match a predefined        *
///              expected output.                                          *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MyItoaUnitTest( )
{
   sprintf( headerBuffer, "MyItoa Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;
   uint8_t dataTestStringBuffer[100];

   int32_t myItoaInputTestCases[ MY_ITOA_TEST_CASES ] = { 1234567890,
                                                          3483279,
                                                          0,
                                                          1,
                                                          0x7FFFFFFF,
                                                          -1234567890,
                                                          -3482379,
                                                          -1,
                                                          0xFFFFFFFF,
                                                          0xDEADBEEF };
   uint8_t myItoaInputBases[ MY_ITOA_BASE_TEST_CASES ] = { 10, 8, 16 };
   uint8_t myItoaOutputTestCases[ MY_ITOA_BASE_TEST_CASES ][ MY_ITOA_TEST_CASES ][25] =
            {  { "1234567890",
                 "3483279",
                 "0",
                 "1",
                 "2147483647",
                 "-1234567890",
                 "-3482379",
                 "-1",
                 "-1",
                 "-559038737"},
               { "11145401322",
                 "15223217",
                 "0",
                 "1",
                 "17777777777",
                 "-11145401322",
                 "-15221413",
                 "-1",
                 "-1",
                 "-4124440421"},
               { "499602D2",
                 "35268F",
                 "0",
                 "1",
                 "7FFFFFFF",
                 "-499602D2",
                 "-35230B",
                 "-1",
                 "-1",
                 "-21524111" } };

   for( uint8_t i = 0; i < MY_ITOA_BASE_TEST_CASES; i++ )
   {
      for( uint8_t j = 0; j < MY_ITOA_TEST_CASES; j++ )
      {
         if( MyItoa( dataTestStringBuffer, myItoaInputTestCases[ j ], myItoaInputBases[ i ] ) )
         {
            sprintf( dataTestStringBuffer, "Conversion Failed, Test Case: %d, Base: %d\n", myItoaInputTestCases[ j ], myItoaInputBases[ i ] );
            LOG0( dataTestStringBuffer );
            continue;
         }

         if( strcmp( dataTestStringBuffer, myItoaOutputTestCases[ i ][ j ] ) != PASS )
         {
            sprintf( testPrintBuffer, "Test Case Failed! Input: %d, Base: %d, Conversion: %s, Expected Output: %s\n",
                     myItoaInputTestCases[ j ],
                     myItoaInputBases[ i ],
                     dataTestStringBuffer,
                     myItoaOutputTestCases[ i ][ j ] );
            LOG0( testPrintBuffer );
            fail = 1;
         }
      }
   }

  PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  MyAtoiUnitTest                                              *
///                                                                        *
/// Description: Sends a known input to MyAtoi and then compares it's      *
///              output with a known output. The test will fail if the     *
///              output of the function does not match a predefined        *
///              expected output.                                          *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MyAtoiUnitTest( )
{
   sprintf( headerBuffer, "MyAtoi Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;
   uint8_t myAtoiUnitTestInputs[ MY_ATOI_TEST_CASES ][25] = { "123456789",
                                                         "987654321",
                                                         "-987654321",
                                                         "-123456789",
                                                         "-1",
                                                         "0",
                                                         "2147483647",
                                                         "-2147483648" };
   int32_t myAtoiUnitTestExpectedOutputs[ MY_ATOI_TEST_CASES ] = { 123456789,
                                                                  987654321,
                                                                  -987654321,
                                                                  -123456789,
                                                                  -1,
                                                                  0,
                                                                  2147483647,
                                                                  -2147483648 };
   int32_t convertedData = 0;
   for( uint32_t i = 0; i < MY_ATOI_TEST_CASES; i++ )
   {
      convertedData = MyAtoi( myAtoiUnitTestInputs[ i ] );
      if( convertedData != myAtoiUnitTestExpectedOutputs[ i ] )
      {
         sprintf( testPrintBuffer, "Test Case Failed! Input: %s, convertedData: %d, Expected Output: %d\n",
                  myAtoiUnitTestInputs[ i ], convertedData, myAtoiUnitTestExpectedOutputs[ i ] );
         LOG0( testPrintBuffer );
         fail = 1;
      }
   }

   PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  MyFtoaUnitTest                                              *
///                                                                        *
/// Description: Sends a known input to MyFtoa and then compares it's      *
///              output with a known output. The test will fail if the     *
///              output of the function does not match a predefined        *
///              expected output.                                          *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MyFtoaUnitTest( )
{
   uint8_t fail = 0;
   sprintf( headerBuffer, "MyFtoa Unit Test" );
   PrintHeader( headerBuffer, main_e );
   double myFtoaTestCasesInput[ MY_FTOA_TEST_CASES ] = { 1.0,
                                                         0.14252,
                                                         0,
                                                         123456789,
                                                         145643.0123456789876543210,
                                                         -145643.0123456789876543210,
                                                         -123456789,
                                                         -0.14252,
                                                         -1.0 };

   uint8_t myFtoaTestCasesExpectedOutput[ MY_FTOA_TEST_CASES ][25] = { "1.00000",
                                                                       "0.14252",
                                                                       "0.00000",
                                                                       "123456789.00000",
                                                                       "145643.01234",
                                                                       "-145643.01234",
                                                                       "-123456789.00000",
                                                                       "-0.14252",
                                                                       "-1.00000" };
   uint8_t dataTestStringBuffer[100];
   for( uint32_t i = 0; i < MY_FTOA_TEST_CASES; i++ )
   {
      MyFtoa( dataTestStringBuffer, myFtoaTestCasesInput[ i ], 5 );
      if( strcmp( dataTestStringBuffer, myFtoaTestCasesExpectedOutput[ i ] ) != PASS )
      {
         sprintf( testPrintBuffer, "Test Case Failed! Input: %lf, Conversion: %s, Expected Output: %s\n",
                  myFtoaTestCasesInput[ i ], dataTestStringBuffer, myFtoaTestCasesExpectedOutput[ i ] );
         LOG0( testPrintBuffer );
         fail = 1;
      }

   }

   PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  BigToLittleUnitTest                                         *
///                                                                        *
/// Description: Defines a 32 bit value and the sends to BigToLittle       *
///              A predefined value that is opposite endianess is checked  *
///              against the ouput. The test will fail if the output does  *
///              not equal the predefined expected output.                 *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void BigToLittleUnitTest( )
{
   sprintf( headerBuffer, "MyBigToLittle Unit Test" );
   PrintHeader( headerBuffer, main_e );

   uint32_t data = 0xDEADBEEF;
   uint32_t reverse = 0xEFBEADDE;
   uint32_t result = 0;
   uint8_t * pData = ( uint8_t * ) &data;

   result = BigToLittle( data );
   PrintHeader( headerBuffer, result == reverse ? 0 : 1 );
}

///*************************************************************************
/// Function:  LittleToBigUnitTest                                         *
///                                                                        *
/// Description: Defines a 32 bit value and the sends to LittleToBig       *
///              A predefined value that is opposite endianess is checked  *
///              against the ouput. The test will fail if the output does  *
///              not equal the predefined expected output.                 *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void LittleToBigUnitTest( )
{
   sprintf( headerBuffer, "MyLittleToBig Unit Test" );
   PrintHeader( headerBuffer, main_e );

   uint32_t data = 0xDEADBEEF;
   uint32_t reverse = 0xEFBEADDE;
   uint32_t result = 0;

   result = LittleToBig( data );
   PrintHeader( headerBuffer, result == reverse ? 0 : 1 );
}

#endif
