#include "sevensegment.h"

///*************************************************************************
/// Function:  InitDisplay                                                 *
///                                                                        *
/// Description: Initializes one of the seven segment displays. Sets up    *
///              necessaries registers as GPIO creates a value that will   *
///              translate a number into ligting up the correct lights to  *
///              show that number.                                         *
///                                                                        *
/// Parameters: Display_place displayNum: Which display is being           *
///             initialized                                                *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void InitDisplay( Display_place place )
{
   // 0: A, B, C, D, E, F
   // 1: B, C
   // 2: A, B, G, E, D
   // 3: A, B, G, C, D
   // 4: F, B, G, C
   // 5: A, F, G, C, D
   // 6: F, G, C, D, E
   // 7: A, B, C
   // 8: A, B, C, D, E, F, G
   // 9: A, B, C, F, G

   switch( place )
   {
      case Display_Tens:
              SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTE_MASK );
              SET_BIT_IN_REG( DISPLAY_PORTE_A, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_B, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_C, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_D, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_E, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_F, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_G, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_H, PORT_PCR_MUX( PIN_GPIO ) );
              Display_Value[ Display_Tens ][ 0 ] =
                                        ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_E_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN );

              Display_Value[ Display_Tens ][ 1 ] =
                                        ( DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN );

              Display_Value[ Display_Tens ][ 2 ] =
                                        ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_E_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ Display_Tens ][ 3 ] =
                                        ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ Display_Tens ][ 4 ] =
                                        ( DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ Display_Tens ][ 5 ] =
                                        ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ Display_Tens ][ 6 ] =
                                        ( DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_E_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ Display_Tens ][ 7 ] =
                                        ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN );

              Display_Value[ Display_Tens ][ 8 ] =
                                        ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_E_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ Display_Tens ][ 9 ] =
                                        ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );
              Display_Port[ Display_Tens ] = GPIOE;
              // The Display_value of 8 contains all 7 pins.
              SET_BIT_IN_REG( GPIO_PDDR_REG( Display_Port[ Display_Tens ] ), Display_Value[ Display_Tens ][ 8 ] );
              break;
      case Display_Ones:
              SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTB_MASK );
              SET_BIT_IN_REG( DISPLAY_PORTB_A, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_B, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_C, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_D, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_E, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_F, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_G, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_H, PORT_PCR_MUX( PIN_GPIO ) );
              Display_Value[ Display_Ones ][ 0 ] =
                                        ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_E_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN );

              Display_Value[ Display_Ones ][ 1 ] =
                                        ( DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN );

              Display_Value[ Display_Ones ][ 2 ] =
                                        ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_E_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ Display_Ones ][ 3 ] =
                                        ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ Display_Ones ][ 4 ] =
                                        ( DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ Display_Ones ][ 5 ] =
                                        ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ Display_Ones ][ 6 ] =
                                        ( DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_E_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ Display_Ones ][ 7 ] =
                                        ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN );

              Display_Value[ Display_Ones ][ 8 ] =
                                        ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_E_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ Display_Ones ][ 9 ] =
                                        ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );
              Display_Port[ Display_Ones ] = GPIOB;
              SET_BIT_IN_REG( GPIO_PDDR_REG( Display_Port[ Display_Ones ] ), Display_Value[ Display_Ones ][ 8 ] );
              break;
   }
}

///*************************************************************************
/// Function:  UpdateDisplay                                               *
///                                                                        *
/// Description: Takes an input of which display is being updated and what *
///              the numbers that needs to be displayed.                   *
///                                                                        *
/// Parameters: Display_place displayNum: Which display is being updated   *
///             uint8_t value: number to be shown on the display.          *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void UpdateDisplay( Display_place displayNum, uint8_t value )
{
   Display_ClearAll( displayNum );
   SET_BIT_IN_REG( GPIO_PSOR_REG( Display_Port[ displayNum ] ), Display_Value[ displayNum ][ value ] );
}

///*************************************************************************
/// Function:  ClearDisplay                                                *
///                                                                        *
/// Description: Turns off all leds of the display indicated by the input  *
///                                                                        *
/// Parameters: uint8_t displayNum: Which display is being initialized     *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void Display_ClearAll( Display_place displayNum )
{
   SET_BIT_IN_REG( GPIO_PCOR_REG( Display_Port[ displayNum ] ), Display_Value[ displayNum ][ 8 ] );
}
