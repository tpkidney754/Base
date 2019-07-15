#ifdef TESTING
#include "circularbuffertesting.h"
#include <stdio.h>
#include <string.h>

static CircularBuffer_t circBuffer;
static CircularBuffer_t* cb = &circBuffer;
static uint8_t circBufferData[BUFFER_SIZE];
static uint8_t itemsToAdd[BUFFER_SIZE] = {1, 2, 3, 4, 5, 6, 7 ,8, 9, 10};
static uint8_t itemsRemoved[BUFFER_SIZE];
uint8_t midpointTest = 0;

static uint8_t headerBuffer[HEADER_LENGTH];
static uint8_t testPrintBuffer[HEADER_LENGTH];

///*************************************************************************
/// Function:  CircularBufferTesting                                       *
///                                                                        *
/// Description: Main function that calls all individual unit test.        *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void CircularBufferTesting( )
{
   midpointTest = 0;
   InitBufferUnitTest();
   AddItemsUnitTestBuffEmpty();
   AddItemsUnitTestBuffHalfFull();
   AddItemsUnitTestBuffFull();
   RemoveItemUnitTestBuffFull();
   RemoveItemUnitTestBuffHalfFull();
   RemoveItemUnitTestBuffEmpty();
   midpointTest = 1;
   BufferTestFromTheMidPoint();
}

///*************************************************************************
/// Function:  AddItemsUnitTestBuffEmpty                                   *
///                                                                        *
/// Description: Basic function to verify the values that were added to    *
///              the buffer or removed from the buffer.                    *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
uint8_t VerifyValues( uint8_t * values, uint32_t length, uint32_t index )
{
   uint8_t fail = 0;

   for( uint32_t i = index; i < length + index; i++ )
   {
      if( *(uint8_t * ) (cb->bufferStart + i ) != values[ i ] )
      {
         sprintf( testPrintBuffer, "Item %d expected value %d but observed %d!\n",
                                    i, *(uint8_t * ) (cb->bufferStart + i ), values[ i ] );
         LOG0( testPrintBuffer );
         fail = 1;
      }
   }

   return fail;
}

///*************************************************************************
/// Function:  InitBufferUnitTest                                          *
///                                                                        *
/// Description: Start of cirbuffer unit testing that initializes a buffer.*
///              The test will fail if the buffer does not initialize.     *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void InitBufferUnitTest( )
{
   uint8_t fail = 0;
   sprintf( headerBuffer, "InitBuffer Unit Test");
   PrintHeader( headerBuffer, main_e );

   CBufferInit(cb, circBufferData, BUFFER_ITEM_SIZE, BUFFER_SIZE);

   sprintf( testPrintBuffer, "Initializing Circular Buffer\nSize: %d, ItemSize: %d, NumItems: %d\n",
            cb->size, cb->itemSize, cb->numItems );
   LOG0( testPrintBuffer );

   if( cb == NULL )
   {
      fail = 1;
      LOG0( "Buffer did not initialize!\n" );
   }
}

///*************************************************************************
/// Function:  AddItemsUnitTestBuffEmpty                                   *
///                                                                        *
/// Description: The buffer is empty and items need to be added and        *
///              verified to be there. The test will fail if the buffer is *
///              is not empty, or if the values in the buffer do not equal *
///              what was placed into the buffer.                          *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void AddItemsUnitTestBuffEmpty( )
{
   sprintf( headerBuffer, "AddItems Buff Empty Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;
   uint32_t addIndex = 0;

   if( IsBufferEmpty( cb ) != BUFFER_EMPTY )
   {
      LOG0( "Buffer Was Not Empty!\n" );
      fail = 1;
   }

   for( uint32_t i = 0; i < ADD_ITEMS_LENGTH; i++ )
   {
      addIndex = midpointTest ? i + ADD_ITEMS_LENGTH : i;
      if( CBufferAdd( cb, &itemsToAdd[ addIndex ], TESTING_DMA_CH ) == BUFFER_FULL )
      {
         LOG0( "Buffer filled up while adding items!\n");
         fail = 1;
      }
   }

   LOG0( "Items Added, now check the buffer\n" );

   if( !midpointTest )
   {
      fail = VerifyValues( itemsToAdd, ADD_ITEMS_LENGTH, 0 );
   }

   PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  AddItemsUnitTestBuffHalfFull                                *
///                                                                        *
/// Description: The buffer is half full and items need to be added and    *
///              verified to be there. The test will fail if the buffer is *
///              empty, or if the values in the buffer do not equal        *
///              what was placed into the buffer.                          *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void AddItemsUnitTestBuffHalfFull( )
{
   sprintf( headerBuffer, "AddItems Half Full Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;
   uint32_t addIndex = 0;

   if( IsBufferEmpty( cb ) == BUFFER_EMPTY )
   {
      LOG0( "Buffer Was Empty!\n" );
      fail = 1;
   }

   for( uint32_t i = 0; i < ADD_ITEMS_LENGTH; i++ )
   {
      addIndex = midpointTest ? i : ADD_ITEMS_LENGTH + i;
      if( ( CBufferAdd( cb, &itemsToAdd[ addIndex ], TESTING_DMA_CH ) == BUFFER_FULL ) && ( i != ADD_ITEMS_LENGTH - 1 ) )
      {
         LOG0( "Buffer filled up while adding items!\n");
         fail = 1;
      }
   }

   LOG0( "Buffer should be full now verify: " );
   sprintf( testPrintBuffer, "Expecting: 1, Observed: %d\n", IsBufferFull( cb ) );
   LOG0( testPrintBuffer );
   if( IsBufferFull( cb ) != BUFFER_FULL)
   {
      fail = 1;
   }

   LOG0( "Items Added, now check the buffer\n" );
   addIndex = midpointTest ?  0 : ADD_ITEMS_LENGTH;
   fail = VerifyValues( itemsToAdd, ADD_ITEMS_LENGTH, addIndex );

   PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  AddItemsUnitTestBuffFull                                    *
///                                                                        *
/// Description: The buffer is full and no items can be added and should   *
///              verified that the add command will return an error.       *
///              The test will fail if the full is empty, or if any items  *
///              were successfully added to the buffer and the add function*
///              did not return a BUFFER_FULL value.                       *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void AddItemsUnitTestBuffFull( )
{
   sprintf( headerBuffer, "AddItems Buff Full Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;

   if( IsBufferEmpty( cb ) == BUFFER_EMPTY )
   {
      LOG0( "Buffer Was Empty!\n" );
      fail = 1;
   }

   if( CBufferAdd( cb, &itemsToAdd[ 0 ], TESTING_DMA_CH ) != BUFFER_FULL )
   {
      LOG0( "Buffer should be full but CBufferAdd did not return BUFFER_FULL!\n");
      fail = 1;
   }

   PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  RemoveItemsUnitTestBuffFull                                 *
///                                                                        *
/// Description: The buffer is full, so now we test if the buffer returns  *
///              the values to a separate data buffer. The test will fail  *
///              if the buffer is not full or if the buffer does not return*
///              the expected values.                                      *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void RemoveItemUnitTestBuffFull( )
{
   sprintf( headerBuffer, "RemoveItems Buff Full Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;
   uint32_t removalIndex = 0;

   if( IsBufferFull( cb ) != BUFFER_FULL )
   {
      LOG0( "Buffer Was Not Full!\n" );
      fail = 1;
   }

   for( uint32_t i = 0; i < REMOVE_ITEMS_LENGTH; i++ )
   {
      removalIndex = midpointTest ? i + REMOVE_ITEMS_LENGTH : i;

      if( CBufferRemove( cb, &itemsRemoved[ removalIndex ], TESTING_DMA_CH ) == BUFFER_EMPTY )
      {
         LOG0( "Buffer emptied while adding items!\n");
         fail = 1;
      }
   }

   LOG0( "Items removed, now check the returned items\n" );

   removalIndex = midpointTest ? REMOVE_ITEMS_LENGTH : 0;
   fail = VerifyValues( itemsRemoved, REMOVE_ITEMS_LENGTH, removalIndex );

   PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  RemoveItemsUnitTestBuffHalfFull                             *
///                                                                        *
/// Description: The buffer is half full, so now we test if the buffer     *
///              returns the values to a separate data buffer correctly.   *
///              The test will fail if the buffer is not full or if the    *
///              buffer does not return the expected values.               *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void RemoveItemUnitTestBuffHalfFull( )
{
   sprintf( headerBuffer, "Remove Items Buff Half Full Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;
   uint32_t removalIndex = 0;

   if( IsBufferFull( cb ) == BUFFER_FULL )
   {
      LOG0( "Buffer Is Still Full!\n" );
      fail = 1;
   }

   for( uint32_t i = 0; i < REMOVE_ITEMS_LENGTH; i++ )
   {
      removalIndex = midpointTest ? i : i + REMOVE_ITEMS_LENGTH;
      if( ( CBufferRemove( cb, &itemsRemoved[ removalIndex ], TESTING_DMA_CH ) == BUFFER_EMPTY ) && ( i != REMOVE_ITEMS_LENGTH - 1 ) )
      {
         LOG0( "Buffer emptied while adding items!\n");
         fail = 1;
      }
   }

   sprintf( testPrintBuffer, "Verify the buffer is now empty: Expected 1, Observed: %d\n", IsBufferEmpty( cb ) );
   LOG0( testPrintBuffer );
   if( IsBufferEmpty( cb ) != BUFFER_EMPTY )
   {
      LOG0( "The Buffer Was Not Empty!\n" );
      fail = 1;
   }

   LOG0( "Items removed, now check the returned items\n" );

   removalIndex = midpointTest ? 0 : REMOVE_ITEMS_LENGTH ;
   fail = VerifyValues( itemsRemoved, REMOVE_ITEMS_LENGTH, removalIndex );

   PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  RemoveItemsUnitTestBuffHalfEmpty                            *
///                                                                        *
/// Description: The buffer is half full, so now we test if the buffer     *
///              returns an error that the buffer is empty when attempting *
///              to remove and item from the buffer.                       *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void RemoveItemUnitTestBuffEmpty( )
{
   sprintf( headerBuffer, "RemoveItems Buff Empty Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;

   if( IsBufferFull( cb ) == BUFFER_FULL )
   {
      LOG0( "Buffer Was Full!\n" );
      fail = 1;
   }

   if( CBufferRemove( cb, &itemsRemoved[ 0 ], TESTING_DMA_CH ) != BUFFER_EMPTY )
   {
      LOG0( "Buffer should be empty but CBufferAdd did not return BUFFER_EMPTY!\n");
      fail = 1;
   }

   PrintHeader( headerBuffer, fail );
}

///*************************************************************************
/// Function:  BufferTestFromTheMidPoint                                   *
///                                                                        *
/// Description: The buffer is working from the end points, now check that *
///              the buffer will wrap around as expected.                  *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void BufferTestFromTheMidPoint( )
{
   sprintf( headerBuffer, "Midpoint Buffer Test");
   PrintHeader( headerBuffer, main_e );
   LOG0( "Zero out buffer\n" );
   MyMemSet( cb->bufferStart, 0, cb->size, TESTING_DMA_CH );
   DumpMemory( cb->bufferStart, cb->size );
   LOG0("\n");
   cb->head = cb->bufferStart;
   cb->tail = cb->bufferStart;
   cb->numItems = 0;
   LOG0("Adding items to fill half the buffer\n" );
   AddItemsUnitTestBuffEmpty( );
   LOG0("Removing items to empty the buffer, but place now the head is pointing to the midpoint\n" );
   RemoveItemUnitTestBuffHalfFull( );
   LOG0( "Fill buffer to the end.\n" );
   AddItemsUnitTestBuffEmpty( );
   LOG0( "Now buffer will wrap\n" );
   AddItemsUnitTestBuffHalfFull( );
   AddItemsUnitTestBuffFull( );
   RemoveItemUnitTestBuffFull( );
   RemoveItemUnitTestBuffHalfFull( );
   RemoveItemUnitTestBuffEmpty( );
}

#endif //TESTING
