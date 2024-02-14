#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define INSERT_MODE 1
#define BITWISE_SET(byte, mask) byte |= mask
#define BITWISE_UNSET(byte, mask) byte &= ~mask

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

int main(int argc, char** argv)
{
    int editorModes = 0;
    FILE* fp;
    fp = fopen(argv[1], "r");

    if ( fp == NULL)
    {
        printf("File input required\n");
        return(1);
    }

    drawCharacters(fp);
    char current_char;
    enableRawMode();
    while (1)
    {
        current_char = readKey();
        if (current_char == '\033') { // ANSI escape sequence
            char ch = readKey();
            if (ch == '['){
                ch = readKey();
                switch (ch) {
                    case 'A':
                        printf("Up arrow key pressed\n");
                        break;
                    case 'B':
                        printf("Down arrow key pressed\n");
                        break;
                    case 'C':
                        printf("Right arrow key pressed\n");
                        break;
                    case 'D':
                        printf("Left arrow key pressed\n");
                        break;
                    case '2':
                        if (readKey() == '~')
                        {
                            BITWISE_SET(editorModes, INSERT_MODE);
                            printf("2\n");
                        }
                        break;
                }
            }
            else
            {
                BITWISE_UNSET(editorModes, INSERT_MODE);
            }   
        } else if (current_char == 'q' && (editorModes & INSERT_MODE) == 0) {
            break;
        }
    }

    // printf("Hello World  %d\n", input);
    return(0);
}