#ifdef TESTING
#include "performancetesting.h"

uint8_t dmaComplete[ 4 ];
///*************************************************************************
/// Function:  PerformanceTesting                                          *
///                                                                        *
/// Description: Main function that calls all individual performance test. *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void PerformanceTesting( )
{
#ifdef FRDM
   InitProfilerTimer( PROFILER_TPM, PROFILER_CH, PROFILER_PERIOD_IN_NS );
#endif
   MemoryPerformanceTesting( );
   DataPerformanceTesting( );
   PrintingPerformanceTesting( );
}

///*************************************************************************
/// Function:  MemoryPerformanceTest                                       *
///                                                                        *
/// Description: Records a timer value before and after each memory        *
///              function and then reports the difference signifying the   *
///              amount of time each function takes to complete.           *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MemoryPerformanceTesting( )
{
   uint32_t memoryTestCaseSizes[ MEMORY_TEST_CASES ] = { 10, 100, 500, 1000, 5000 };

   uint32_t start = 0;
   uint32_t end = 0;
   uint32_t diff = 0;

   for( uint32_t i = 0; i < MEMORY_TEST_CASES; i++ )
   {
//-------------------------------------------------------------------------------------------------------
      start = GetTime( );
      uint8_t * src = malloc( sizeof( uint8_t ) * memoryTestCaseSizes[ i ] );
      end = GetTime( );
      printf( "\n\nStart: %d, End: %d\n\n", start, end );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "Allocating %d bytes with empty heap took, %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------
      start = GetTime( );
      uint8_t * dst = malloc( sizeof( uint8_t ) * memoryTestCaseSizes[ i ] );
      end = GetTime( );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "Allocating %d bytes with non-empty heap took, %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------
      start = GetTime( );
      MyMemMove( src, dst, memoryTestCaseSizes[ i ], TESTING_DMA_CH );
   #ifdef FRDM
      while( dmaComplete[ TESTING_DMA_CH ] == 0 );
   #endif
      end = GetTime( );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "MyMemMove with %d bytes took, %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------
      start = GetTime( );
      memmove( dst, src, memoryTestCaseSizes[ i ] );
      end = GetTime( );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "Library function memmove with %d bytes took, %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------
      start = GetTime( );
      MyMemSet( src, 0, memoryTestCaseSizes[ i ], TESTING_DMA_CH );
   #ifdef FRDM
      while( dmaComplete[ TESTING_DMA_CH ] == 0 );
   #endif
      end = GetTime( );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "MyMemSet with %d bytes took, %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------
      start = GetTime( );
      memset( src, '0', memoryTestCaseSizes[ i ] );
      end = GetTime( );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "Library function memset with %d bytes took, %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------

      start = GetTime( );
      MyReverse( src, memoryTestCaseSizes[ i ] );
      end = GetTime( );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "MyReverse with %d bytes took, %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------
      /*start = GetTime( );
      strrev( src )
      end = GetTime( );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "MyReverse with %d bytes took %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );*/
//-------------------------------------------------------------------------------------------------------
      start = GetTime( );
      free( src );
      end = GetTime( );
      diff = GetElapsedTime( start, end );

      sprintf( testPrintBuffer, "Freeing %d bytes from the heap took, %u\n", memoryTestCaseSizes[ i ], diff );
      LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------
      free( dst );
   }

}

///*************************************************************************
/// Function:  DataPerformanceTest                                         *
///                                                                        *
/// Description: Records a timer value before and after each data          *
///              function and then reports the difference signifying the   *
///              amount of time each function takes to complete.           *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void DataPerformanceTesting( )
{
   int32_t intInput = 0xDEADBEEF;
   uint8_t buffer[ 25 ];
   int32_t intOutput = 0;
   double fInput = 123456789.987654321;

   uint32_t start = 0;
   uint32_t end = 0;
   uint32_t diff = 0;

   start = GetTime( );
   MyItoa( buffer, intInput, 10 );
   end = GetTime( );
   diff = GetElapsedTime( start, end );

   sprintf( testPrintBuffer, "MyItoa with %d took, %u\n", intInput, diff );
   LOG0( testPrintBuffer );

#if 0
   start = GetTime( );
   itoa( intInput, buffer, 10 );
   end = GetTime( );
   diff = GetElapsedTime( start, end );

   sprintf( testPrintBuffer, "Library function itoa with %d took %u\n", intInput, diff );
   LOG0( testPrintBuffer );
#endif

   start = GetTime( );
   intOutput = MyAtoi( buffer );
   end = GetTime( );
   diff = GetElapsedTime( start, end );

   sprintf( testPrintBuffer, "MyAtoi with %s took, %u\n", buffer, diff );
   LOG0( testPrintBuffer );

#if 0
   start = GetTime( );
   intOutput = atoi( buffer );
   end = GetTime( );
   diff = GetElapsedTime( start, end );

   sprintf( testPrintBuffer, "Library function atoi with %s took %u\n", buffer, diff );
   LOG0( testPrintBuffer );
#endif

   start = GetTime( );
   MyFtoa( buffer, fInput, 10 );
   end = GetTime( );
   diff = GetElapsedTime( start, end );

   sprintf( testPrintBuffer, "MyFtoa with %lf took, %u\n", fInput, diff );
   LOG0( testPrintBuffer );

#if 0
   start = GetTime( );
   ftoa( fInput, buffer, 10 );
   end = GetTime( );
   diff = GetElapsedTime( start, end );

   sprintf( testPrintBuffer, "Library function ftoa with %lf took %u\n", fInput, diff );
   LOG0( testPrintBuffer );
#endif
}

///*************************************************************************
/// Function:  PrintingPerformanceTest                                     *
///                                                                        *
/// Description: Records a timer value before and after each printing      *
///              function and then reports the difference signifying the   *
///              amount of time each function takes to complete.           *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void PrintingPerformanceTesting( )
{
   uint32_t start = 0;
   uint32_t end = 0;
   uint32_t diff = 0;
   uint32_t intData = 123456789;
   double fData = 123456789.987654321;
   uint8_t log1buffer[25] = "";

   start = GetTime( );
#ifdef FRDM
   LOG0( "20 character string!" );
#else
   printf( "20 character string!" );
#endif
   end = GetTime( );
   diff = GetElapsedTime( start, end );
#ifdef FRDM
   sprintf( testPrintBuffer, "\nLOG0 with %d characters took, %u\n", 20, diff );
#else
   sprintf( testPrintBuffer, "\nPrintf with %d characters took, %u\n", 20, diff );
#endif
   LOG0( testPrintBuffer );

//-------------------------------------------------------------------------------------------------------
   start = GetTime( );
#ifdef FRDM
   LOG1( log1buffer, 0, int_e, 1, intData);
#else
   printf( "%d", intData );
#endif
   end = GetTime( );
   diff = GetElapsedTime( start, end );
#ifdef FRDM
   sprintf( testPrintBuffer, "LOG1 with 1 int input took, %u\n", diff );
#else
   sprintf( testPrintBuffer, "\nPrintf with 1 int input took, %u\n", diff );
#endif
   LOG0( testPrintBuffer );
//-------------------------------------------------------------------------------------------------------
   start = GetTime( );
#ifdef FRDM
   LOG1( log1buffer, 0, int_e, 2, intData, intData );
#else
   printf( "%d %d", intData, intData );
#endif
   end = GetTime( );
   diff = GetElapsedTime( start, end );
#ifdef FRDM
   sprintf( testPrintBuffer, "LOG1 with 2 int inputs took, %u\n", diff );
#else
   sprintf( testPrintBuffer, "\nPrintf with 2 int inputs took, %u\n", diff );
#endif
   LOG0( testPrintBuffer );

//-------------------------------------------------------------------------------------------------------
   start = GetTime( );
#ifdef FRDM
   LOG1( log1buffer, 0, int_e, 3, intData, intData, intData );
#else
   printf( "%d %d %d", intData, intData, intData );
#endif
   end = GetTime( );
   diff = GetElapsedTime( start, end );
#ifdef FRDM
   sprintf( testPrintBuffer, "LOG1 with 3 int inputs took, %u\n", diff );
#else
   sprintf( testPrintBuffer, "\nPrintf with 3 int inputs took, %u\n", diff );
#endif
   LOG0( testPrintBuffer );

//-------------------------------------------------------------------------------------------------------
   start = GetTime( );
#ifdef FRDM
   LOG1( log1buffer, 0, double_e, 1, fData);
#else
   printf( "%lf", fData );
#endif
   end = GetTime( );
   diff = GetElapsedTime( start, end );
#ifdef FRDM
   sprintf( testPrintBuffer, "LOG1 with 1 flaot input took, %u\n", diff );
#else
   sprintf( testPrintBuffer, "\nPrintf with 1 float input took, %u\n", diff );
#endif
   LOG0( testPrintBuffer );

//-------------------------------------------------------------------------------------------------------
   start = GetTime( );
#ifdef FRDM
   LOG1( log1buffer, 0, double_e, 2, fData, fData );
#else
   printf( "%lf %lf", fData, fData );
#endif
   end = GetTime( );
   diff = GetElapsedTime( start, end );
#ifdef FRDM
   sprintf( testPrintBuffer, "LOG1 with 2 float inputs took, %u\n", diff );
#else
   sprintf( testPrintBuffer, "\nPrintf with 2 float inputs took, %u\n", diff );
#endif
   LOG0( testPrintBuffer );

//-------------------------------------------------------------------------------------------------------
   start = GetTime( );
#ifdef FRDM
   LOG1( log1buffer, 0, double_e, 3, fData, fData, fData );
#else
   printf( "%lf %lf %lf", fData, fData, fData );
#endif
   end = GetTime( );
   diff = GetElapsedTime( start, end );
#ifdef FRDM
   sprintf( testPrintBuffer, "LOG1 with 3 float inputs took, %u\n", diff );
#else
   sprintf( testPrintBuffer, "\nPrintf with 3 float inputs took, %u\n", diff );
#endif
   LOG0( testPrintBuffer );

//-------------------------------------------------------------------------------------------------------
}

#endif // TESTING
