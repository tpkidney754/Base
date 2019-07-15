#ifndef __MEMORY__
#define __MEMORY__

#include "includeall.h"

int8_t MyMemMove( uint8_t * src, uint8_t * dst, uint32_t length, uint8_t DMAch );
int8_t MyMemSet( uint8_t * dst, uint32_t value, size_t numBytes, uint8_t DMAch );
int8_t MyReverse( uint8_t * src, uint32_t length );
int32_t MyStrLen( uint8_t * str );

#endif
