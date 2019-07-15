#ifndef __UART__
#define __UART__

#include "includeall.h"

#define OSR                (16U)
#define CR                 (13U)
#define LF                 (10U)

#define RXBUFFER_SIZE      (128U)
#define TXBUFFER_SIZE      (128U)
#define DMA_RXBUFFER_SIZE  (_128Bytes)
#define DMA_TXBUFFER_SIZE  (_1kBytes)

#define DMACH_UART0RX      (NO_DMA)
#define DMACH_UART0TX      (NO_DMA)
#define DMACH_UART1RX      (NO_DMA)
#define DMACH_UART1TX      (NO_DMA)
#define DMA_TRANSFER_SIZE  (_8bit)

void UartSetup(uint8_t channel, uint32_t buadRate, uint8_t parity);
void UartTX(uint8_t* buffer, uint32_t length);
int8_t UartRX(void);
void PutChar(uint8_t data);

#endif //__UART__
