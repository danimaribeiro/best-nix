#ifndef STRING_H
#define STRING_H

#include "types.h"
uint16 strlen(string c)
{
    uint16 i = 1;
    while(c[i++]);
    return --i;
}

#endif
