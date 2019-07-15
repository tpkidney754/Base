#ifndef __MEMORYUNITTEST__
#define __MEMORYUNITTEST__

#include "includeall.h"

#define MEM_MOVE_SIZE      23
#define TESTSTRING         "This is my test string"
#define MY_MEM_ZERO_SIZE   50
#define MY_REVERSE_INPUTS  3
#define MY_STR_LEN_INPUTS  2
#define MAIN_HEADER        2

#ifdef FRDM
#define TESTING_DMA_CH     3
#else
#define TESTING_DMA_CH     NO_DMA
#endif


void MemoryTesting( void );
void MyMemMoveUnitTest( void );
void MyMemSetUnitTest( void );
void MyReverseUnitTest( void );
void MyStrLenUnitTest( void );

#endif //__MEMORYUNITTEST__
