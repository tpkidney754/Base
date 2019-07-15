#ifndef __DATA__
#define __DATA__ 

#include "includeall.h"

#define BYTE0_MASK  0x000000FF
#define BYTE1_MASK  0x0000FF00
#define BYTE2_MASK  0X00FF0000
#define BYTE3_MASK  0XFF000000
#define BYTE3_SHIFT 24
#define BYTE2_SHIFT 16
#define BYTE1_SHIFT  8
#define BYTE0_SHIFT  0

#define ASCIINUMBASE    0x30
#define ASCIILETTERBASE 0X37

int8_t MyItoa( uint8_t * str, int32_t data, int32_t base );
int32_t MyAtoi( uint8_t * str );
int32_t MyFtoa( uint8_t * str, double data, int32_t decimalPlaces );
void DumpMemory( uint8_t * start, uint32_t length );
int32_t BigToLittle( int32_t data );
int32_t LittleToBig( int32_t data );

#endif