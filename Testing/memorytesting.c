#ifdef TESTING
#include "memorytesting.h"
#include <stdio.h>
#include <string.h>

static uint8_t memloc1[MEM_MOVE_SIZE * 2];
static uint8_t memloc2[MEM_MOVE_SIZE];
static uint8_t headerBuffer[HEADER_LENGTH];
static uint8_t testPrintBuffer[HEADER_LENGTH];

///*************************************************************************
/// Function:  MemoryTesting                                               *
///                                                                        *
/// Description: Main function that calls all individual unit test.        *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MemoryTesting()
{
    MyMemMoveUnitTest();
    MyMemSetUnitTest();
    MyReverseUnitTest();
    MyStrLenUnitTest();
}

///*************************************************************************
/// Function:  MyMemMoveUnitTest                                           *
///                                                                        *
/// Description: Allocates to memory locations and defines a string. The   *
///              string is copied to the first location using a library    *
///              function. Then the sting is copied to another location    *
///              using MyMemMove. Then the second location is compared     *
///              to the original string in three different cases. First is *
///              a direct copy with no overlap. Second is the case that    *
///              the second location overlaps the first location. The final*
///              case is when the fist location overlaps the second.       *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MyMemMoveUnitTest()
{
    sprintf(headerBuffer, "MyMemmove Unit Test");
    uint8_t testString[MEM_MOVE_SIZE] = TESTSTRING;
    uint8_t fail = 0;

    strcpy(memloc1, testString);

    PrintHeader(headerBuffer, main_e);

    MyMemMove(memloc1, memloc2, MEM_MOVE_SIZE, TESTING_DMA_CH);

    if (strcmp(memloc2, testString) != PASS)
    {
        sprintf(testPrintBuffer, "Direct copy failed! Expected %s, Copied Loc: %s\n", testString, memloc2);
        LOG0(testPrintBuffer);
        fail = 1;
    }

    // memloc2 overlaps memloc1
    uint8_t* pMemLoc2 = memloc2;
    pMemLoc2 = memloc1 + 10;

    MyMemMove(memloc1, pMemLoc2, MEM_MOVE_SIZE, TESTING_DMA_CH);

    if (strcmp(pMemLoc2, testString) != PASS)
    {
        sprintf(testPrintBuffer, "Overlap copy failed! Expected %s, Copied Loc: %s\n", testString, memloc2);
        LOG0(testPrintBuffer);
        fail = 1;
    }

    // memloc1 overlaps memloc2
    uint8_t* pMemLoc1;
    pMemLoc2 = memloc1;
    pMemLoc1 = memloc1 + 10;

    strcpy(pMemLoc1, testString);
    MyMemMove(pMemLoc1, pMemLoc2, MEM_MOVE_SIZE, TESTING_DMA_CH);

    if (strcmp(pMemLoc2, testString) != PASS)
    {
        sprintf(testPrintBuffer, "Overlap copy failed! Expected %s, Copied Loc: %s\n", testString, memloc2);
        LOG0(testPrintBuffer);
        fail = 1;
    }

    PrintHeader(headerBuffer, fail);
}

///*************************************************************************
/// Function:  MyMemSetUnitTest                                            *
///                                                                        *
/// Description: An array of data is allocated and then initialized to a   *
///              a nonzero value. Then the array is passed to MyMemSet     *
///              and verified to be zero.                                  *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MyMemSetUnitTest(void)
{
    sprintf(headerBuffer, "MyMemSet Unit Test");
    PrintHeader(headerBuffer, main_e);

    uint8_t fail = 0;

    for (uint32_t i = 0; i < MY_MEM_ZERO_SIZE; i++)
    {
        memloc2[i] = 0xA5;
    }

    MyMemSet(memloc1, 0, MY_MEM_ZERO_SIZE, TESTING_DMA_CH);

    for (uint32_t i = 0; i < MY_MEM_ZERO_SIZE; i++)
    {
        if (memloc1[i] != 0)
        {
            fail = 1;
            break;
        }
    }

    PrintHeader(headerBuffer, fail);
}

///*************************************************************************
/// Function:  MyReverseUnitTest                                           *
///                                                                        *
/// Description: Strings are defined with a length and then a defined      *
///              expected out of the revesed strings are also declared.    *
///              Each string is passed to MyReverse, and then compared     *
///              with expected output.                                     *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MyReverseUnitTest( void )
{
    uint8_t fail = 0;
    sprintf(headerBuffer, "MyReverse Unit Test");
    PrintHeader(headerBuffer, main_e);

    uint8_t myReverseUnitTestInputs[MY_REVERSE_INPUTS][35] = { "This is a string",
                                                               "some NUMbers12345",
                                                               "Does it reverse \n\0\t correctly?"
                                                             };

    uint8_t myReverseUnitTestExpectedOutputs[MY_REVERSE_INPUTS][35] = { "gnirts a si sihT",
                                                                        "54321srebMUN emos",
                                                                        "?yltcerroc \t\0\n esrever ti seoD"
                                                                      };

    uint8_t myReverseUnitTestInputsLengths[MY_REVERSE_INPUTS] = {16, 17, 30};

    for (uint32_t i = 0; i < MY_REVERSE_INPUTS; i++)
    {
        MyReverse(myReverseUnitTestInputs[i], myReverseUnitTestInputsLengths[i]);

        if (strcmp(myReverseUnitTestInputs[i], myReverseUnitTestExpectedOutputs[i]) != PASS)
        {
            sprintf(testPrintBuffer, "Test Case Failed! Expected: %s, Observed: %s\n",
            myReverseUnitTestExpectedOutputs[i], myReverseUnitTestInputs[i]);

            LOG0(testPrintBuffer);

            fail = 1;
        }
    }

    PrintHeader(headerBuffer, fail);
}

///*************************************************************************
/// Function:  MyStrLenUnitTest                                            *
///                                                                        *
/// Description: Passes in a string with a known length and then sent to   *
///              MyStrLen. The output is compared with the expected known  *
///              string length.                                            *
///                                                                        *
/// Parameters: NONE                                                       *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void MyStrLenUnitTest( void )
{
    uint8_t  fail           = 0;
    uint32_t returnedLength = 0;

    uint8_t  mystrLenUnitTestInputs[MY_STR_LEN_INPUTS][25] = {"This is a string",
                                                 "some NUMbers12345"};

    uint8_t mystrLenUnitTestInputsLengths[MY_STR_LEN_INPUTS] = {16, 17};

    sprintf(headerBuffer, "MyStrLen Unit Test");
    PrintHeader(headerBuffer, main_e);

    for (uint32_t i = 0; i < MY_STR_LEN_INPUTS; i++)
    {
        returnedLength = MyStrLen(mystrLenUnitTestInputs[i]);

        if (returnedLength != mystrLenUnitTestInputsLengths[i])
        {
            sprintf(testPrintBuffer, "Test Case Failed! Input: %s, Expected Length: %d, Observed: %d ",
             mystrLenUnitTestInputs[ i ], mystrLenUnitTestInputsLengths[ i ], returnedLength );

            LOG0(testPrintBuffer);

            fail = 1;
        }
    }

    PrintHeader(headerBuffer, fail);
}

#endif // TESTING
