#ifdef TESTING
#ifndef __DATAUNITTEST__
#define __DATAUNITTEST__

#include "includeall.h"

#define MY_ITOA_TEST_CASES          10
#define MY_ITOA_BASE_TEST_CASES     3
#define MY_ATOI_TEST_CASES          8
#define MY_FTOA_TEST_CASES          9
#define BIG_TO_LITTLE_TEST_CASES    2
#define LITTLE_TO_BIG_TEST_CASES    2

void DataTesting( void );
void MyItoaUnitTest( void );
void MyAtoiUnitTest( void );
void MyFtoaUnitTest( void );
void BigToLittleUnitTest( void );
void LittleToBigUnitTest( void );
#endif // __DATAUNITTEST__
#endif
