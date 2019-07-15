#ifndef __TESTING__
#define __TESTING__

#include "includeall.h"

#define PASS            (0U)
#define HEADER_LENGTH   (100U)

void Testing();

typedef enum HeaderType
{
    pass_e = 0,
    fail_e,
    main_e,
} HeaderType_t;

void PrintHeader(uint8_t* header, HeaderType_t headerType);

#endif // __TESTING__
