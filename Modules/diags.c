#include "diags.h"
#include <string.h>

///*************************************************************************
/// Function:  ParseDiag                                                   *
///                                                                        *
/// Description: Receives a string signifying a diag command from          *
///              the serial port.                                          *
///                                                                        *
/// Parameters: uint8_t * buffer: pointer to a string buffer.              *
///                                                                        *
/// Return Value:  NONE                                                    *
///*************************************************************************
void ParseDiag(uint8_t * buffer)
{
    // Support up to four commands with 10 characters each.
    uint8_t commands[4][10];
    size_t length;
    size_t commandIndex = 0;
    uint8_t* currentCommand;

    currentCommand = strtok(buffer, "\n ");

    while (currentCommand != NULL)
    {
        strcpy(commands[commandIndex++], currentCommand);
        currentCommand = strtok(NULL, "\n ");

        length = MyStrLen(commands[commandIndex - 1]);
        commands[commandIndex - 1][length] = '\0';

        commandIndex = 0;

        if (strstr(commands[commandIndex], "set"))
        {
            commandIndex++;
            if (strstr( commands[commandIndex], "color"))
            {
                commandIndex++;
                Color_t color = NONE;

                if (strstr(commands[commandIndex], "red"))
                {
                    color = RED;
                }
                else if (strstr(commands[commandIndex], "green"))
                {
                    color = GREEN;
                }
                else if (strstr(commands[commandIndex], "blue"))
                {
                    color = BLUE;
                }
                else if (strstr(commands[commandIndex], "purple"))
                {
                    color = PURPLE;
                }
                else if (strstr(commands[commandIndex], "yellow"))
                {
                    color = YELLOW;
                }
                else if (strstr(commands[commandIndex], "cyan"))
                {
                    color = CYAN;
                }
                else if (strstr(commands[commandIndex], "white"))
                {
                    color = WHITE;
                }
                else if (strstr(commands[commandIndex], "off"))
                {
                    color = OFF;
                }
                else
                {
                    LOG0("Invalid color given\n");
                }

                SwitchLEDs((uint8_t)color);
            }
            else if (strstr(commands[commandIndex], "power"))
            {
                commandIndex++;
                uint32_t pulseWidth;
                pulseWidth = MyAtoi(commands[commandIndex]);
                ChangeLEDPW((uint8_t)pulseWidth);
            }
        }
    }
}
