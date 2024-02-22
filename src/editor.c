#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "includes/editor.h"

struct termios saveTerminalSettings() {
    struct termios old_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    return old_termios;
}

void restoreTerminalSettings(struct termios old_termios) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

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