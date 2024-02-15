#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "includes/editor.h"

void enableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag |= ICANON;
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


char readKey() {
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

void drawCharacters(FILE* fp){
    char ch = fgetc(fp);
    while(ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fp);
    }
}