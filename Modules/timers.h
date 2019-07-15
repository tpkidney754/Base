#ifndef __TIMERS__
#define __TIMERS__

#include "includeall.h"

#define MAX_MODULUS 	   0xFFFF
#define MAX_PRESCALER 	0x7

#define NS_PER_SEC         1000000000
#define _10US_PER_SEC      10000000
#define UNITS_US           1000000
#define NS_PER_US          1000

#define PROFILER_TPM             1
#define PROFILER_CH              1
#define PROFILER_PERIOD_IN_NS    10000

#define COUNTS_PER_US            48

#define WAIT_TPM                 TPM1
#define WAIT_CH                  2

typedef enum
{
   externalTriggerPinInput = 0,
   CMP0Output,
   reserved0,
   reseved1,
   pitTrigger0,
   pitTrigger1,
   reserved2,
   reserved3,
   tpm0Overflow,
   tpm1Overflow,
   tpm2Overflow,
   reserved4,
   rtcAlarm,
   rtcSeconds,
   LPTMRtrigger,
   reserved5,
} TPM_TriggerOptions;

#ifdef FRDM
void SetupPWM( uint8_t tpm, uint8_t ch, uint16_t modulus, uint8_t prescaler, uint16_t pulseWidth );
void ChangeLEDPW( uint8_t pulseWidth );
void InitProfilerTimer( uint8_t tpm, uint8_t ch, uint32_t intervalInNs );
void InitWaitTimer( );
void WaitInUs( uint16_t waitTime );
#endif

uint32_t GetTime( );
uint32_t GetElapsedTime( uint32_t start, uint32_t end );

#endif //__TIMERS__
