
#ifndef __LED__
#define __LED__

#include "includeall.h"

#define RED_PIN         1 << 18
#define GREEN_PIN       1 << 19
#define BLUE_PIN        1 << 1
#define RED_TPM         2
#define RED_CHANNEL     0
#define GREEN_TPM    2
#define GREEN_CHANNEL   1
#define BLUE_TPM     0
#define BLUE_CHANNEL 1

// Macros to turn or off and LED. The LEDs are being driven by the TPM.
// The red led is being driven by TPM2_CH0 through the ALTERNATIVE_3 pin configuration.
// The green led is being driven by TPM2_CH1 through the ALTERNATIVE_3 pin configuration.
// The blue led is being driven by TPM0_CH1 through the ALTERNATIVE_3 pin configuration.
#ifdef FRDM
#define RED_LED_ON      SET_REG_VALUE( PORTB_PCR18, PORT_PCR_MUX_MASK, PORT_PCR_MUX( ALTERNATIVE_3 ) );
#define RED_LED_OFF     SET_REG_VALUE( PORTB_PCR18, PORT_PCR_MUX_MASK, PORT_PCR_MUX( PIN_DISABLE )   );
#define GREEN_LED_ON    SET_REG_VALUE( PORTB_PCR19, PORT_PCR_MUX_MASK, PORT_PCR_MUX( ALTERNATIVE_3 ) );
#define GREEN_LED_OFF   SET_REG_VALUE( PORTB_PCR19, PORT_PCR_MUX_MASK, PORT_PCR_MUX( PIN_DISABLE )   );
#define BLUE_LED_ON     SET_REG_VALUE( PORTD_PCR1 , PORT_PCR_MUX_MASK, PORT_PCR_MUX( ALTERNATIVE_4 ) );
#define BLUE_LED_OFF    SET_REG_VALUE( PORTD_PCR1 , PORT_PCR_MUX_MASK, PORT_PCR_MUX( PIN_DISABLE )   );
#endif

typedef enum Color_t
{
   RED = 0,
   GREEN,
   BLUE,
   PURPLE,
   YELLOW,
   CYAN,
   WHITE,
   OFF,
   NONE
} Color_t;

void LEDSetup( void );
void SwitchLEDs( uint8_t color );
void CycleLEDs( );

#endif // __LED__
