#ifndef SCREEN_H
#define SCREEN_H
#include "types.h"
#include "system.h"
#include "string.h"
int cursorX = 0, cursorY = 0;
const uint8 screen_w=80, screen_h=25, screen_d = 2;
void clear_line(uint8 from, uint8 to)
{
    uint16 i = screen_w * from * screen_d;
    string vidmem=(string)0xb8000;
    for(i;i<(screen_w*(to+1)*screen_d);i++)
    {
        vidmem[i] = 0x0;
    }
}

void update_cursor()
{
    unsigned temp;
    temp = cursorY * screen_w + cursorX;  //Position = (y + width) + x

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void clear_screen()
{
    clear_line(0, screen_h - 1);
    cursorX = cursorY = 0;
    update_cursor();
}

void scroll_up(uint8 line_number)
{
    string vidmem = (string)0xb8000;
    uint16 i = 0;
    for(i;i<screen_w*(screen_h-1)*screen_d;i++)
    {
        vidmem[i] = vidmem[i+screen_w*screen_d*line_number];
    }
    clear_line(screen_h-1-line_number, screen_h-1);
    if((cursorY - line_number) < 0)
    {
        cursorX = cursorY = 0;
    }
    else
    {
        cursorY -= line_number;
    }
    update_cursor();
}
void new_line_check()
{
    if(cursorY >= screen_h-1)
    {
        scroll_up(1);
    }
}
void printch(char c)
{
    string vidmem = (string)0xb8000;
    switch (c) {
        case (0x08):  //backspace
            if(cursorX > 0)
            {
                cursorX--;
                vidmem[(cursorY * screen_h + cursorX) * screen_d] = 0x00;
            }
            break;
        case (0x09): //tab
            cursorX = (cursorX + 8) & ~(8 - 1);
            break;
        case ('\r'):
            cursorX = 0;
            break;
        case ('\n'):
            cursorX = 0;
            cursorY++;
        default:
            vidmem[(cursorY * screen_w + cursorX)*screen_d] = c;
            vidmem[(cursorY * screen_w + cursorX)*screen_d+1] = 0x0F;
            cursorX++;
            break;
    }
    if(cursorX >=  screen_w)
    {
        cursorX = 0;
        cursorY++;
    }
    new_line_check();
    update_cursor();
}

void print(string str)
{
    uint16 i =0;
    uint16 length = strlen(str);
    for(i;i<length-1;i++)
    {
        printch(str[i]);
    }
}
#endif
