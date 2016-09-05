#include "include/screen.h"
#include "include/kb.h"
#include "include/string.h"

kmain()
{
    clear_screen();
    print("Bem Vindo ao Danix OS!\nPor favor entre um comando\n");
    while(1)
    {
        print(">");
        string command = readstring();
        if(strequal(command, "clear"))
        {
            clear_screen();
        }
        print(command);
    }
}
