#ifdef FRDM
#include "dma.h"

extern uint8_t dmaComplete[ 4 ];
///*************************************************************************
/// Function:  InitDMA                                                     *
///                                                                        *
/// Description: Starts the clock for the DMA module and initializes the   *
///              global boolean used to indicate when a DMA transfer is    *
///              complete.                                                 *
///                                                                        *
/// Parameters: uint8_t ch: DMA ch being initialized                       *
///                                                                        *
/// Return Value:  None                                                    *
///*************************************************************************
void InitDMA( uint8_t ch )
{
   SET_BIT_IN_REG( SIM_SCGC7, SIM_SCGC7_DMA_MASK );
   dmaComplete[ ch ] = 1;
}

///*************************************************************************
/// Function:  StartTransfer32bitMoves                                     *
///                                                                        *
/// Description: Transfers memory 32bits at a time.                        *
///                                                                        *
/// Parameters: uint8_t ch: DMA ch being used                              *
///             uint8_t * src: Source memory location of data to be moved. *
///             uint8_t * dst: Destination location to move data           *
///             uint32_t numBytes: Number of bytes to be moved             *
///                                                                        *
/// Return Value: DMAErors_e: Enumerated DMA errors.                       *
///*************************************************************************
DMAErrors_e StartTransfer32bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes )
{
   if( numBytes % 4 != 0 )
   {
      return DMANot32bitTransferSize;
   }

   DMA_SAR( ch ) = ( uint32_t ) src;
   DMA_DAR( ch ) = ( uint32_t ) dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // Clears out the entire register
                  MASK_32BIT,
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _32bit ) |
                    DMA_DCR_DSIZE( _32bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   // Set the byte count register. it must be less than or equal to 0x0FFFFF or DMA_BCR_SIZE_MASK
   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes & DMA_BCR_SIZE_MASK );
   // Sets global boolean to false
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   // Clears and enables the interrupt for the DMA channel
   // The interrupt will occur when the DMA is complete.
   NVIC_ClearPendingIRQ( ch );
   NVIC_EnableIRQ( ch );
   NVIC_SetPriority( ch, 2 );

   return DMANoError;
}

///*************************************************************************
/// Function:  StartTransfer16bitMoves                                     *
///                                                                        *
/// Description: Transfers memory 16bits at a time.                        *
///                                                                        *
/// Parameters: uint8_t ch: DMA ch being used                              *
///             uint8_t * src: Source memory location of data to be moved. *
///             uint8_t * dst: Destination location to move data           *
///             uint32_t numBytes: Number of bytes to be moved             *
///                                                                        *
/// Return Value: DMAErors_e: Enumerated DMA errors.                       *
///*************************************************************************
DMAErrors_e StartTransfer16bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes )
{
   if( numBytes % 2 != 0 )
   {
      return DMANot16bitTransferSize;
   }

   DMA_SAR( ch ) = ( uint32_t ) src;
   DMA_DAR( ch ) = ( uint32_t ) dst;
   SET_REG_VALUE( DMA_DCR( ch ),
                  // Clears out the entire register
                  MASK_32BIT,
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _16bit ) |
                    DMA_DCR_DSIZE( _16bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes & DMA_BCR_SIZE_MASK );
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   NVIC_ClearPendingIRQ( ch );
   NVIC_EnableIRQ( ch );
   NVIC_SetPriority( ch, 2 );


   return DMANoError;
   return DMANoError;
}

///*************************************************************************
/// Function:  StartTransfer8bitMoves                                      *
///                                                                        *
/// Description: Transfers memory 8bits at a time.                         *
///                                                                        *
/// Parameters: uint8_t ch: DMA ch being used                              *
///             uint8_t * src: Source memory location of data to be moved. *
///             uint8_t * dst: Destination location to move data           *
///             uint32_t numBytes: Number of bytes to be moved             *
///                                                                        *
/// Return Value: DMAErors_e: Enumerated DMA errors.                       *
///*************************************************************************
DMAErrors_e StartTransfer8bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes )
{
   DMA_SAR( ch ) = ( uint32_t ) src;
   DMA_DAR( ch ) = ( uint32_t ) dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // Clears out the entire register
                  MASK_32BIT,
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _8bit ) |
                    DMA_DCR_DSIZE( _8bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes & DMA_BCR_SIZE_MASK );
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   NVIC_ClearPendingIRQ( ch );
   NVIC_EnableIRQ( ch );
   NVIC_SetPriority( ch, 2 );

   return DMANoError;
}

///*************************************************************************
/// Function:  MemSet32bit                                                 *
///                                                                        *
/// Description: Writes memory 32bits at a time.                           *
///                                                                        *
/// Parameters: uint8_t ch: DMA ch being used                              *
///             uint32_t data: Value to be written to memory               *
///             uint8_t * dst: Destination location to write data          *
///             uint32_t numBytes: Number of bytes to be written, must be  *
///                                divisible by 4.                         *
///                                                                        *
/// Return Value: DMAErors_e: Enumerated DMA errors.                       *
///*************************************************************************
DMAErrors_e MemSet32bit( uint8_t ch, uint32_t data, uint8_t * dst, uint32_t numBytes )
{
   if( numBytes % 4 != 0 )
   {
      return DMANot32bitTransferSize;
   }

   DMA_SAR( ch ) = ( uint32_t ) &data;
   DMA_DAR( ch ) = ( uint32_t ) dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // Clears out the entire register
                  MASK_32BIT,
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _8bit ) |
                    DMA_DCR_DSIZE( _8bit ) |
                    DMA_DCR_DINC_MASK ) );
                  // Main difference with memmove is that the SINC mask will not be set
                  // because the source is a single 32bit value.
   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes & DMA_BCR_SIZE_MASK );
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   NVIC_ClearPendingIRQ( ch );
   NVIC_EnableIRQ( ch );
   NVIC_SetPriority( ch, 2 );

   return DMANoError;
}

///*************************************************************************
/// Function:  MemSet8bit                                                  *
///                                                                        *
/// Description: Writes memory 8bits at a time.                            *
///                                                                        *
/// Parameters: uint8_t ch: DMA ch being used                              *
///             uint32_t data: Value to be written to memory               *
///             uint8_t * dst: Destination location to write data          *
///             uint32_t numBytes: Number of bytes to be written.          *
///                                                                        *
/// Return Value: DMAErors_e: Enumerated DMA errors.                       *
///*************************************************************************
DMAErrors_e MemSet8bit( uint8_t ch, uint8_t data, uint8_t * dst, uint32_t numBytes )
{
   DMA_SAR( ch ) = ( uint32_t ) &data;
   DMA_DAR( ch ) = ( uint32_t ) dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // Clears out the entire register
                  MASK_32BIT,
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _8bit ) |
                    DMA_DCR_DSIZE( _8bit ) |
                    DMA_DCR_DINC_MASK ) );

   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes & DMA_BCR_SIZE_MASK );
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   NVIC_ClearPendingIRQ( ch );
   NVIC_EnableIRQ( ch );
   NVIC_SetPriority( ch, 2 );

   return DMANoError;
}

void DMA0_IRQHandler( )
{
   NVIC_DisableIRQ( 0 );
   uint32_t statusRegister = DMA_DSR_BCR0;
   if( DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK )
   {
      // Done bit is the reason for the interrupt. Writing
      // to that bit will clear out the status register.
      // There will be no renabling of the interrupt after the
      // done bit is set.
      SET_BIT_IN_REG( DMA_DSR_BCR( 0 ), DMA_DSR_BCR_DONE_MASK );
      dmaComplete[ 0 ] = 1;
   }
   else if( statusRegister & 0xFE000000 )
   {
      // purpose of this is that a configuration error will
      // cause an interrupt also. If any of these bits are set
      // then there was a configuration error and this will act
      // as an assert for debugging purposes.
      while( 1 );
   }
   else
   {
      NVIC_EnableIRQ( 0 );
   }
}

void DMA1_IRQHandler( )
{
   NVIC_DisableIRQ( 1 );
   uint32_t statusRegister = DMA_DSR_BCR1;
   if( DMA_DSR_BCR1 & DMA_DSR_BCR_DONE_MASK )
   {
      SET_BIT_IN_REG( DMA_DSR_BCR( 1 ), DMA_DSR_BCR_DONE_MASK );
      dmaComplete[ 1 ] = 1;
   }
   else if( statusRegister & 0xFE000000 )
   {
      while( 1 );
   }
   else
   {
      NVIC_EnableIRQ( 1 );
   }
}

void DMA2_IRQHandler( )
{
   NVIC_DisableIRQ( 2 );
   uint32_t statusRegister = DMA_DSR_BCR2;
   if( DMA_DSR_BCR2 & DMA_DSR_BCR_DONE_MASK )
   {
      SET_BIT_IN_REG( DMA_DSR_BCR( 2 ), DMA_DSR_BCR_DONE_MASK );
      dmaComplete[ 2 ] = 1;
   }
   else if( statusRegister & 0xFE000000 )
   {
      while( 1 );
   }
   else
   {
      NVIC_EnableIRQ( 2 );
   }
}

void DMA3_IRQHandler( )
{
   NVIC_DisableIRQ( 3 );
   uint32_t statusRegister = DMA_DSR_BCR3;
   if( DMA_DSR_BCR3 & DMA_DSR_BCR_DONE_MASK )
   {
      SET_BIT_IN_REG( DMA_DSR_BCR( 3 ), DMA_DSR_BCR_DONE_MASK );
      dmaComplete[ 3 ] = 1;
   }
   else if( statusRegister & 0xFE000000 )
   {
      while( 1 );
   }
   else
   {
      NVIC_EnableIRQ( 3 );
   }
}
#endif //FRDM
