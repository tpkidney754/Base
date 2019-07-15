#ifdef TESTING
#ifndef __CIRCBUFFUNITTEST__
#define __CIRCBUFFUNITTEST__

#include "includeall.h"

#define BUFFER_SIZE              10
#define BUFFER_ITEM_SIZE         1
#define ADD_ITEMS_LENGTH      BUFFER_SIZE / 2
#define REMOVE_ITEMS_LENGTH   BUFFER_SIZE / 2

void CircularBufferTesting( void );
uint8_t VerifyValues( uint8_t * values, uint32_t length, uint32_t index );
void InitBufferUnitTest( void );
void AddItemsUnitTestBuffEmpty( void );
void AddItemsUnitTestBuffHalfFull( void );
void AddItemsUnitTestBuffFull( void );
void RemoveItemUnitTestBuffFull( void );
void RemoveItemUnitTestBuffHalfFull( void );
void RemoveItemUnitTestBuffEmpty( void );
void BufferTestFromTheMidPoint( void );
void DestructBufferUnitTest( void );

#endif //__CIRCBUFFUNITTEST__
#endif
