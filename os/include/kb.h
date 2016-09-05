#ifndef KB_H
#define KB_H

#include "screen.h"
#include "system.h"
#include "types.h"

char ASCII[6] = {'0', '1', '2', '3', '4', '5'};

string readstring()
{
    char buff;
    string buffstr;
    uint8 i = 0;
    uint8  reading = 1;
    while(reading)
    {
        if(inportb(0x64) & 0x1)
        {
            uint16 read = inportb(0x60);
            if(read==0)
                continue;
            if(read<6)
                printch(ASCII[read]);
                buffstr[i] = ASCII[read];
                i++;
        }
    }
    buffstr[i] = 0;
    return buffstr;
}

#endif
