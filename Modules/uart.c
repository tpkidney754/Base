#include "uart.h"

/* GLOBAL Variable */
static uint8_t parseDiag = 0;
static CircularBuffer_t UART0_RXBuffer;
static CircularBuffer_t UART0_TXBuffer;
static CircularBuffer_t UART1_RXBuffer;
static CircularBuffer_t UART1_TXBuffer;

static uint8_t uart0_RxBufferData[RXBUFFER_SIZE];
static uint8_t uart0_TxBufferData[TXBUFFER_SIZE];
static uint8_t uart1_RxBufferData[RXBUFFER_SIZE];
static uint8_t uart1_TxBufferData[TXBUFFER_SIZE];

///*************************************************************************
/// Function:  UartSetup                                                   *
///                                                                        *
/// Description: Sets up UART.                                             *
///                                                                        *
/// Parameters: uint8_t channel: UART channel to initialize.               *
///             uint32_t requestedBaudRate: Desired baud rate              *
///             uint8_t parity: Used as boolean if parity is desired.      *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void UartSetup(uint8_t channel, uint32_t requestedBuadRate, uint8_t parity)
{
    uint32_t uart0Clk     = 0;
    uint32_t calcBaudRate = 0;
    uint32_t mcgClk       = 0;
    uint32_t prdiv        = 0;
    uint32_t vdiv         = 0;

    // Determining msgCLK
    prdiv  = (MCG_C5 & MCG_C5_PRDIV0_MASK) + 1;
    vdiv   = (MCG_C6 & MCG_C6_VDIV0_MASK) + 24;
    mcgClk = (CPU_XTAL_CLK_HZ / prdiv) * vdiv;

    switch (channel)
    {
        case 0:
        {
            CBufferInit(&UART0_RXBuffer, &uart0_RxBufferData, sizeof(uint8_t), RXBUFFER_SIZE);
            CBufferInit(&UART0_TXBuffer, &uart0_TxBufferData, sizeof(uint8_t), TXBUFFER_SIZE);

            // Enable Port A
            SET_BIT_IN_REG(SIM_SCGC5, SIM_SCGC5_PORTA_MASK);
            // Enables PortA PCR1 for UART0_TXD functionality.
            SET_BIT_IN_REG(PORTA_PCR1, PORT_PCR_MUX(ALTERNATIVE_2));
            // Enables PortA PCR2 for UART0_TXD functionality.
            SET_BIT_IN_REG(PORTA_PCR2, PORT_PCR_MUX(ALTERNATIVE_2));
            // Selects the PLLFLLClk as the source for UART0
            SET_BIT_IN_REG(SIM_SOPT2, SIM_SOPT2_UART0SRC(1));
            SET_BIT_IN_REG(SIM_SOPT2, SIM_SOPT2_PLLFLLSEL(1));
            //Calculates the clk value for UART0.
            uart0Clk = (mcgClk / 2);
            // Enables the clock gate for UART0
            SET_BIT_IN_REG(SIM_SCGC4, SIM_SCGC4_UART0_MASK);
            // Disables the UART0 TX/RX before setting other registers.
            CLEAR_BITS_IN_REG(UART0_C2, (UART0_C2_TE_MASK | UART0_C2_RE_MASK));
            // Needs to calculate the baud rate mod that is placed into registers.
            calcBaudRate = uart0Clk / ((OSR) * requestedBuadRate);

            #if (OSR >= 4 && OSR <= 8)
            // If the over sampling rate is between 4 and 8, then both edge sampling needs to
            // be enabled.
            SET_BIT_IN_REG(UART0_C5, UART0_C5_BOTHEDGE_MASK);
            #endif
            // Setting the OSR value in registers.
            SET_BIT_IN_REG(UART0_C4, UART0_C4_OSR((OSR - 1)));
            // Inputting the calculated baud rate mod into registers
            SET_BIT_IN_REG(UART0_BDH, UART0_BDH_SBR((calcBaudRate & 0x1F00 ) >> 8));
            SET_BIT_IN_REG(UART0_BDL, UART0_BDL_SBR((uint8_t)(calcBaudRate & 0xFF)));

            // Enable RX Interrupt
            SET_BIT_IN_REG(UART0_C2, UART0_C2_RIE_MASK);
            //SET_BIT_IN_REG( UART0_C2, UART0_C2_TIE_MASK);
            NVIC_EnableIRQ(UART0_IRQn);
            NVIC_ClearPendingIRQ(UART0_IRQn);
            NVIC_SetPriority(UART0_IRQn, 2);

            // Enables the TX/RX pins.
            SET_BIT_IN_REG(UART0_C2, (UART0_C2_TE_MASK | UART0_C2_RE_MASK));

            break;
        }

        case 1:
        {
            CBufferInit(&UART1_RXBuffer, &uart1_RxBufferData, sizeof(uint8_t), RXBUFFER_SIZE);
            CBufferInit(&UART1_TXBuffer, &uart1_TxBufferData, sizeof(uint8_t), TXBUFFER_SIZE);
            // Enables the clock gate for UART1
            SET_BIT_IN_REG(SIM_SCGC4, SIM_SCGC4_UART1_MASK);
            // Enable Port E
            SET_BIT_IN_REG(SIM_SCGC5, SIM_SCGC5_PORTE_MASK);
            // Enables PortE PCR0 for UART1_TXD functionality.
            SET_BIT_IN_REG(PORTE_PCR0, PORT_PCR_MUX(ALTERNATIVE_3));
            // Enables PortE PCR1 for UART1_RXD functionality.
            SET_BIT_IN_REG(PORTE_PCR1, PORT_PCR_MUX(ALTERNATIVE_3));

            // Disables the UART0 TX/RX before setting other registers.
            CLEAR_BITS_IN_REG(UART1_C2, (UART_C2_TE_MASK | UART_C2_RE_MASK));

            uint16_t br = 24000000/(16 * requestedBuadRate);
            SET_BIT_IN_REG(UART1_BDH, UART_BDH_SBR((br & 0x1F00) >> 8));
            SET_BIT_IN_REG(UART1_BDL, UART_BDL_SBR(br & 0x00FF));

            // Enable RX Interrupt
            SET_BIT_IN_REG(UART1_C2, UART_C2_RIE_MASK);

            NVIC_EnableIRQ(UART1_IRQn);
            NVIC_ClearPendingIRQ(UART1_IRQn);
            NVIC_SetPriority(UART1_IRQn, 2);

            // Enables the TX/RX pins.
            SET_BIT_IN_REG(UART1_C2, (UART_C2_TE_MASK | UART_C2_RE_MASK));
            break;
        }
    }
}

///*************************************************************************
/// Function:  UartTX                                                      *
///                                                                        *
/// Description: Uses a blocking method to transmit on UART.               *
///                                                                        *
/// Parameters: uint8_t * buffer: pointer to an array of characters that   *
///                       are to be transmitted through the UART           *
///             uint32_t length: Num of bytes to be sent through           *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void UartTX(uint8_t* buffer, uint32_t length)
{
    for (uint8_t i = 0; i < length; i++)
    {
       WAIT_FOR_BIT_SET( UART1_S1 & UART_S1_TDRE_MASK );
       UART1_D = buffer[ i ];
    }
}

///*************************************************************************
/// Function:  UartRX                                                      *
///                                                                        *
/// Description: Uses the polling method to receive data through UART      *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  uint8_t: byte received from UART                        *
///*************************************************************************
int8_t UartRX(void)
{
    WAIT_FOR_BIT_SET(UART0_S1 & UART0_S1_RDRF_MASK);

    return UART0_D;
}

///*************************************************************************
/// Function:  PutChar                                                     *
///                                                                        *
/// Description: Transmits a single character through UART0                *
///                                                                        *
/// Parameters: uint8_t data: character to be sent.                        *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void PutChar(uint8_t data)
{
    WAIT_FOR_BIT_SET(UART0_S1 & UART0_S1_TDRE_MASK);
    UART0_D = data;
}

///*************************************************************************
/// Function:  UART0_IRQHandler                                            *
///                                                                        *
/// Description: Interrupt Handler for UART0 for RX operations.            *
///              The handler checks the RDRF flag to verify it's a RX      *
///              then adds the character to buffer, then the character     *
///              is printed out to UART0TX. Once a CR is identified, a LF  *
///              and \0 character is added to buffer to terminate the      *
///              string and a boolean is set for main to start parsing the *
///              diag command.                                             *
///                                                                        *
/// Parameters: uint8_t data: character to be sent.                        *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void UART0_IRQHandler()
{
    uint8_t data;

    if ((UART0_S1 & UART0_S1_TDRE_MASK))
    {
        if (CBufferRemove(&UART0_TXBuffer, &data, DMACH_UART0TX) == BUFFER_EMPTY)
        {
            CLEAR_BITS_IN_REG(UART0_C2, UART0_C2_TIE_MASK);
        }
        else
        {
            UART0_D = data;
        }
    }

    if (UART0_S1 & UART0_S1_RDRF_MASK)
    {
        data = UART0_D;

        CBufferAdd(&UART0_RXBuffer, &data, DMACH_UART0RX);

        PutChar(data);

        if (data == LF || data == CR)
        {
           data = '\0';

           CBufferAdd(&UART0_RXBuffer, &data, DMACH_UART0RX);

            parseDiag = 1;
        }
    }
}

void UART1_IRQHandler()
{
    uint8_t data;

    if ((UART1_S1 & UART_S1_TDRE_MASK))
    {
        if (UART1_TXBuffer.numItems == 0)
        {
           CLEAR_BITS_IN_REG(UART1_C2, UART_C2_TIE_MASK);
        }
        else
        {
            CBufferRemove(&UART1_TXBuffer, &data, DMACH_UART1TX);
            UART1_D = data;
        }
    }

    if (UART1_S1 & UART_S1_RDRF_MASK)
    {
        data = UART1_D;

        CBufferAdd(&UART1_RXBuffer, &data, DMACH_UART1RX);
    }
}
