#include "timers.h"

#ifdef FRDM
static uint32_t timerCount = 0;
///*************************************************************************
/// Function:  SetupPWM                                                    *
///                                                                        *
/// Description: Sets up a PWM timers                                      *
///                                                                        *
/// Parameters: uint8_t tpm: desired timer module                          *
///             uint8_t ch: desire tpm modules channel                     *
///             uint16_t modulus: desired modulus, or how man clk cycle    *
///                               before the counter increments            *
///             uint8_t prescaler: desired prescaler, divides modulus.     *
///             uint16_t pulseWidth: desired pulseWidth percentage, or     *
///                                  what percentage of the period is the  *
///                                  the signal is high.                   *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void SetupPWM( uint8_t tpm, uint8_t ch, uint16_t modulus, uint8_t prescaler, uint16_t pulseWidth )
{
   switch( tpm )
   {
      case 0:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM0_MASK );
         SET_BIT_IN_REG( TPM0_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM0_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM0_SC, TPM_SC_CMOD( 1 ) | TPM_SC_PS( prescaler ) );
         TPM0_CNT = TPM_CNT_COUNT_MASK;
         TPM0_MOD = modulus;
         SET_BIT_IN_REG( TPM0_CnSC( ch ), TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK );
         TPM0_CnV( ch ) = (uint16_t) modulus * ( pulseWidth / 100.0 );
         break;
      case 1:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM1_MASK );
         SET_BIT_IN_REG( TPM1_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM1_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM1_SC, TPM_SC_CMOD( 1 ) | TPM_SC_PS( prescaler ) );
         TPM1_CNT = TPM_CNT_COUNT_MASK;
         TPM1_MOD = modulus;
         SET_BIT_IN_REG( TPM1_CnSC( ch ), TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK );
         TPM1_CnV( ch ) = (uint16_t) modulus * ( pulseWidth / 100.0 );
         break;
      case 2:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM2_MASK );
         SET_BIT_IN_REG( TPM2_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM2_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM2_SC, TPM_SC_CMOD( 1 ) | TPM_SC_PS( prescaler ) );
         TPM2_CNT = TPM_CNT_COUNT_MASK;
         TPM2_MOD = modulus;
         SET_BIT_IN_REG( TPM2_CnSC( ch ), TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK );
         TPM2_CnV( ch ) = (uint16_t) modulus * ( pulseWidth / 100.0 );
         break;
   }
}

///*************************************************************************
/// Function:  ChangeLEDPW                                                 *
///                                                                        *
/// Description: Targets the TPM and CHs that drive the three LEDs to      *
///              change the PW of the signal that will in turn modify the  *
///              intensity of the light.                                   *
///                                                                        *
/// Parameters: uint16_t pulseWidth: The new desired PW percentage.        *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void ChangeLEDPW( uint8_t pulseWidth )
{
   uint16_t valueToTPM0CnV = (uint16_t) TPM0_MOD * ( pulseWidth / 100.0 );
   uint16_t valueToTPM2CnV = (uint16_t) TPM2_MOD * ( pulseWidth / 100.0 );
   TPM2_C0V = valueToTPM2CnV;
   TPM2_C1V = valueToTPM2CnV;
   TPM0_C1V = valueToTPM0CnV;
}

///*************************************************************************
/// Function:  InitProfilerTimer                                           *
///                                                                        *
/// Description: Starts a profiler timer based on the tpm, ch, and the     *
///              interval in NS.                                           *
///                                                                        *
/// Parameters: uint16_t pulseWidth: The new desired PW percentage.        *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void InitProfilerTimer( uint8_t tpm, uint8_t ch, uint32_t intervalInNs )
{
   uint32_t clockPeriodInNs = NS_PER_SEC / DEFAULT_SYSTEM_CLOCK;
   uint32_t modulus = (uint32_t ) ( ( intervalInNs ) / clockPeriodInNs ) - 1;

   switch( tpm )
   {
      case 0:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM0_MASK );
         SET_BIT_IN_REG( TPM0_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM0_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM0_SC, TPM_SC_CMOD( 1 ) );
         SET_BIT_IN_REG( TPM0_SC, TPM_SC_TOIE_MASK );
         NVIC_EnableIRQ( TPM0_IRQn );
         NVIC_SetPriority( TPM0_IRQn, 2 );
         TPM0_CNT = TPM_CNT_COUNT_MASK;
         TPM0_MOD = modulus;
         SET_BIT_IN_REG( TPM0_CnSC( ch ), TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK );
         TPM0_CnV( ch ) = (uint16_t) modulus;
         break;
      case 1:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM1_MASK );
         SET_BIT_IN_REG( TPM1_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM1_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM1_SC, TPM_SC_CMOD( 1 ) );
         SET_BIT_IN_REG( TPM1_SC, TPM_SC_TOIE_MASK );
         NVIC_EnableIRQ( TPM1_IRQn );
         NVIC_SetPriority( TPM1_IRQn, 2 );
         TPM1_CNT = TPM_CNT_COUNT_MASK;
         TPM1_MOD = modulus;
         SET_BIT_IN_REG( TPM1_CnSC( ch ), TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK );
         TPM1_CnV( ch ) = (uint16_t) modulus;
         break;
      case 2:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM2_MASK );
         SET_BIT_IN_REG( TPM2_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM2_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM2_SC, TPM_SC_CMOD( 1 ) );
         SET_BIT_IN_REG( TPM2_SC, TPM_SC_TOIE_MASK );
         NVIC_EnableIRQ( TPM2_IRQn );
         NVIC_SetPriority( TPM2_IRQn, 2 );
         TPM2_CNT = TPM_CNT_COUNT_MASK;
         TPM2_MOD = modulus;
         SET_BIT_IN_REG( TPM2_CnSC( ch ), TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK );
         TPM2_CnV( ch ) = (uint16_t) modulus;
         break;
   }
}

///*************************************************************************
/// Function:  InitWaitTimer                                               *
///                                                                        *
/// Description: Initializes the timer for pauses.                         *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value: NONE                                                     *
///                                                                        *
///*************************************************************************
void InitWaitTimer( )
{
   SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM1_MASK );
   SET_BIT_IN_REG( TPM_SC_REG( WAIT_TPM ), TPM_SC_CMOD( 1 ) );
   TPM_CNT_REG( WAIT_TPM ) = TPM_CNT_COUNT_MASK;
}

///*************************************************************************
/// Function:  WaitInUs                                                    *
///                                                                        *
/// Description: Uses the timer module to pause the program for a specified*
///              ammount of time in microseconds.                          *
///                                                                        *
/// Parameters: uint16_t waitTime: Ammount of time in microseconds to wait *
///                                                                        *
/// Return Value: NONE                                                     *
///                                                                        *
///*************************************************************************
void WaitInUs( uint16_t waitTime )
{
   // Each clock is 21ns
   // Therefore 1 us is roughly 48 counts.
   waitTime *= COUNTS_PER_US;
   uint16_t countValue;
   TPM_CNT_REG( WAIT_TPM ) = TPM_CNT_COUNT_MASK;
   countValue = TPM_CNT_REG( WAIT_TPM );
   while( countValue < waitTime )
   {
      countValue = TPM_CNT_REG( WAIT_TPM );
   }
}

void TPM0_IRQHandler()
{
   if( TPM0_SC & TPM_SC_TOF_MASK )
   {
      timerCount++;
      SET_BIT_IN_REG( TPM0_SC, TPM_SC_TOF_MASK );
   }
}

void TPM1_IRQHandler()
{
   if( TPM1_SC & TPM_SC_TOF_MASK )
   {
      timerCount++;
      SET_BIT_IN_REG( TPM1_SC, TPM_SC_TOF_MASK );
   }
}

void TPM2_IRQHandler()
{
   if( TPM2_SC & TPM_SC_TOF_MASK )
   {
      timerCount++;
      SET_BIT_IN_REG( TPM2_SC, TPM_SC_TOF_MASK );
   }
}

#endif //FRDM

inline uint32_t GetTime( )
{
#ifdef FRDM
   return timerCount;
#else
   return ( uint32_t ) clock( );
#endif
}

inline uint32_t GetElapsedTime( uint32_t start, uint32_t end )
{
#ifdef FRDM
   timerCount = 0;
   return end - start;
#else
   //printf( "CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC );
   return  ( end - start );
#endif
}
