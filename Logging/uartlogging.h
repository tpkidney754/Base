#ifndef __UARTLOGGING__
#define __UARTLOGGING__

#include "includeall.h"

typedef enum DataType_t
{
	int_e = 0,
	double_e,
} DataType_t;

void LOG0( uint8_t * data );
void LOG1( uint8_t * data, uint32_t length, DataType_t dataType, uint32_t numParms, ... );

#endif // __UARTLOGGING__
