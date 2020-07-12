#include <stdio.h>
#include <string.h>
#include "interpreter.h"

void drawScreen(const uint8_t screen[SCR_HEIGHT][SCR_WIDTH])
{
    char top_bot_line[SCR_WIDTH + 3] = {0};
    char buf[SCR_WIDTH + 3] = {[0] = '|', [SCR_WIDTH + 1] = '|'};

    memset(top_bot_line, '-', SCR_WIDTH + 2);
    puts(top_bot_line);
    for (uint8_t y = 0; y != SCR_HEIGHT; y += 1) {
        for (uint8_t x = 0; x != SCR_WIDTH; x += 1) {
            buf[x+1] = screen[y][x] ? '*' : ' ';
        }
        puts(buf);
    }
    puts(top_bot_line);
}

void clearScreen(uint8_t screen[SCR_HEIGHT][SCR_WIDTH])
{
    bzero(screen, SCR_SIZE);
    drawScreen(screen);
}
