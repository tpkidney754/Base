#ifndef __SEVENSEGMENT__
#define __SEVENSEGMENT__

#include "includeall.h"

#define NUM_DISPLAYS    3
#define NUM_SEGMENTS    8
#define NUM_DIGITS      10
#define DISPLAY_CLEAR   0
#define DISPLAY_SET     1

GPIO_Type * Display_Port[ NUM_DISPLAYS ];
uint32_t Display_Value[ NUM_DISPLAYS ][ NUM_DIGITS ];

#define DISPLAY_PORTE_A             PORTE_PCR30
#define DISPLAY_PORTE_B             PORTE_PCR29
#define DISPLAY_PORTE_C             PORTE_PCR23
#define DISPLAY_PORTE_D             PORTE_PCR22
#define DISPLAY_PORTE_E             PORTE_PCR21
#define DISPLAY_PORTE_F             PORTE_PCR20
#define DISPLAY_PORTE_G             PORTE_PCR5
#define DISPLAY_PORTE_H             PORTE_PCR2

#define DISPLAY_A_PORTE_PIN         0x40000000
#define DISPLAY_B_PORTE_PIN         0x20000000
#define DISPLAY_C_PORTE_PIN         0x00800000
#define DISPLAY_D_PORTE_PIN         0x00400000
#define DISPLAY_E_PORTE_PIN         0x00200000
#define DISPLAY_F_PORTE_PIN         0x00100000
#define DISPLAY_G_PORTE_PIN         0x00000020
#define DISPLAY_H_PORTE_PIN         0x00000002

#define DISPLAY_PORTB_A             PORTB_PCR3
#define DISPLAY_PORTB_B             PORTB_PCR2
#define DISPLAY_PORTB_C             PORTB_PCR1
#define DISPLAY_PORTB_D             PORTB_PCR0
#define DISPLAY_PORTB_E             PORTB_PCR11
#define DISPLAY_PORTB_F             PORTB_PCR10
#define DISPLAY_PORTB_G             PORTB_PCR9
#define DISPLAY_PORTB_H             PORTB_PCR8

#define DISPLAY_A_PORTB_PIN         0x00000008
#define DISPLAY_B_PORTB_PIN         0x00000004
#define DISPLAY_C_PORTB_PIN         0x00000002
#define DISPLAY_D_PORTB_PIN         0x00000001
#define DISPLAY_E_PORTB_PIN         0x00000800
#define DISPLAY_F_PORTB_PIN         0x00000400
#define DISPLAY_G_PORTB_PIN         0x00000200
#define DISPLAY_H_PORTB_PIN         0x00000100

typedef enum
{
   Display_NoError = 0,
   Display_NotSingleDigit,
} Display_Errors;

typedef enum
{
   Display_Tens = 0,
   Display_Ones,
} Display_place;

void InitDisplay( Display_place place );
void UpdateDisplay( Display_place place, uint8_t value );
void Display_ClearAll( Display_place place );

#endif // __SEVENSEGMENT__
