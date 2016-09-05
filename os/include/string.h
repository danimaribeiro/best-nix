#ifndef STRING_H
#define STRING_H

#include "types.h"
uint16 strlen(string c)
{
    uint16 i = 1;
    while(c[i++]);
    return --i;
}

uint8 strequal(string c1, string c2)
{
    if(strlen(c1) != strlen(c2))
        return 0;
    uint16 i=0;
    while(c1[i]){
        if(c1[i]!=c2[i])
            return 0;
        i++;
    }
    return 1;
}

#endif
