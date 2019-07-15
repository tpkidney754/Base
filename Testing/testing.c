#include "testing.h"
#include <string.h>
#include <stdio.h>

static uint8_t fillerChar[3] = {'*', '@', '~'};
static uint8_t testPrintBuffer[256];
static uint8_t headerBuffer[HEADER_LENGTH];
static uint8_t filler[HEADER_LENGTH];
///*************************************************************************
/// Function:  Testing                                                     *
///                                                                        *
/// Description: Main function that calls all individual test suite.       *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void Testing()
{
   InitDMA(TESTING_DMA_CH);
   DataTesting();
   MemoryTesting();
   CircularBufferTesting();
}

///*************************************************************************
/// Function:  PrintHeader                                                 *
///                                                                        *
/// Description: A string is passed in and a header type. The type will    *
///              dictate the filler characters surrounding the header      *
///              sting.                                                    *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void PrintHeader(uint8_t* header, HeaderType_t headerType)
{
   if (headerType == pass_e)
   {
      strcat(header, " Passed Successfully!");
   }
   else if (headerType == fail_e)
   {
      strcat(header, " Failed!");
   }

   uint8_t fillerLength = HEADER_LENGTH - MyStrLen(header) - 2;
   fillerLength /= 2;

   MyMemSet(filler, 0, fillerLength + 1, TESTING_DMA_CH);

   for (uint32_t i = 0; i < fillerLength; i++)
   {
      filler[i] = fillerChar[headerType];
   }

   sprintf(testPrintBuffer, "\n%s %s %s\n", filler, header, filler);
   LOG0(filler);
   LOG0(header);
   LOG0(filler);
}
