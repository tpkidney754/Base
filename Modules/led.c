#ifdef FRDM
#include "led.h"

///*************************************************************************
/// Function:  SwitchLEDs                                                  *
///                                                                        *
/// Description: Sets up the LEDs to be used as GPIO outputs               *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void LEDSetup( void )
{
   // Enable Port B and Port D Clocks
   SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK );
   // Leave LEDs off for now;
   RED_LED_OFF;
   GREEN_LED_OFF;
   BLUE_LED_OFF;

   // Setup the PWM needed for each pin with an initial 50% duty cycle
   SetupPWM( RED_TPM, RED_CHANNEL, MAX_MODULUS, 0, 50 );
   SetupPWM( GREEN_TPM, GREEN_CHANNEL, MAX_MODULUS, 0, 50 );
   SetupPWM( BLUE_TPM, BLUE_CHANNEL, MAX_MODULUS, 0, 50 );

   // Sets the ports as GPIO output.
   SET_BIT_IN_REG( GPIOB_PDDR, RED_PIN  );
   SET_BIT_IN_REG( GPIOB_PDDR, GREEN_PIN );
   SET_BIT_IN_REG( GPIOD_PDDR, BLUE_PIN );
}

///*************************************************************************
/// Function:  SwitchLEDs                                                  *
///                                                                        *
/// Description: Changes which LEDs are on/off based on the input color.   *
///                                                                        *
/// Parameters: Color_t color: typedef enum expressing a desired color.    *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void SwitchLEDs( uint8_t color )
{
   switch( ( Color_t ) color )
   {
      case RED:
            RED_LED_ON;
            GREEN_LED_OFF;
            BLUE_LED_OFF;
            break;
      case GREEN:
            RED_LED_OFF;
            GREEN_LED_ON;
            BLUE_LED_OFF;
            break;
      case BLUE:
            RED_LED_OFF
            GREEN_LED_OFF;
            BLUE_LED_ON;
            break;
      case PURPLE:
            RED_LED_ON;
            GREEN_LED_OFF;
            BLUE_LED_ON;
            break;
      case YELLOW:
            RED_LED_ON;
            GREEN_LED_ON;
            BLUE_LED_OFF
            break;
      case CYAN:
            RED_LED_OFF;
            GREEN_LED_ON;
            BLUE_LED_ON;
            break;
      case WHITE:
            RED_LED_ON;
            GREEN_LED_ON;
            BLUE_LED_ON;
            break;
      case OFF:
            RED_LED_OFF;
            GREEN_LED_OFF;
            BLUE_LED_OFF;
            break;
      case NONE:
      default:
            break;

   }
}
#endif

void CycleLEDs( )
{
   for( Color_t color = RED; color < 7; color++ )
   {
      SwitchLEDs( color );
      ChangeLEDPW( 0 );
      for( uint8_t power = 1; power <= 100; power ++ )
      {
         ChangeLEDPW( power );
         for( uint32_t j = 0; j < 100000; j++ );
      }

      for( int8_t power = 100; power >= 0; power-- )
      {
         ChangeLEDPW( power );
         for( uint32_t j = 0; j < 100000; j++ );
      }
   }
   SwitchLEDs( OFF );
}
