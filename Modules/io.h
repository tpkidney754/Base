#ifndef __IO__
#define __IO__

#include "includeall.h"

typedef enum
{
   PIN_DISABLE = 0,
   PIN_GPIO,
   ALTERNATIVE_2,
   ALTERNATIVE_3,
   ALTERNATIVE_4,
   ALTERNATIVE_5,
   ALTERNATIVE_6,
   ALTERNATIVE_7,
} PcrMux;

typedef enum
{
   IRQDisable = 0,
   DMARising,
   DMAFalling,
   DMAEitherEdge,
   ActiveLowIRQ = 8,
   IRQRising,
   IRQFalling,
   IRQEither,
   ActiveHighIRQ,
} IRQValues;

#define WAIT_FOR_BIT_SET( BIT ) while( ( BIT ) == 0 )
#define WAIT_FOR_BIT_CLEAR( BIT ) while( ( BIT ) )
#define CLEAR_BITS_IN_REG( REG, BITS ) ( ( REG ) &= ~( BITS ) )
#define SET_BIT_IN_REG( REG, BIT ) ( ( REG ) |= ( BIT ) )
// If a value in a reg is more than one bit, this will clear those bits and then set those
// bits without disturbing any of the other bits in the register.
#define SET_REG_VALUE( REG, MASK, VALUE )  CLEAR_BITS_IN_REG( ( REG ), ( MASK ) ); \
                                           SET_BIT_IN_REG( ( REG ), ( VALUE ) )
#define READ_BITS_FROM_REG( REG, BIT_MASK, BIT_SHIFT ) ( ( ( REG ) & ( BIT_MASK ) ) >> ( BIT_SHIFT ) )

#endif // __IO__
