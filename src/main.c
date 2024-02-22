#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "includes/editor.h"

int main(int argc, char** argv)
{
    struct termios old_termios = saveTerminalSettings();
    printf(CLEAR_SCREEN);
    printf("\033[H"); 
    int editorModes = 0;
    FILE* fp;
    fp = fopen(argv[1], "r");

    if ( fp == NULL)
    {
        printf("File input required\n");
        return(1);
    }

    drawCharacters(fp);
    enableRawMode();
    
    char current_char;
    while (1)
    {
        current_char = readKey();
        if (current_char == '\033') { // ANSI escape sequence
            char ch = readKey();
            if (ch == '['){
                ch = readKey();
                switch (ch) {
                    case 'A':
                        // printf("Up arrow key pressed\n");
                        break;
                    case 'B':
                        // printf("Down arrow key pressed\n");
                        break;
                    case 'C':
                        // printf("Right arrow key pressed\n");
                        break;
                    case 'D':
                        // printf("Left arrow key pressed\n");
                        break;
                    case '2':
                        if (readKey() == '~')
                        {
                            BITWISE_SET(editorModes, INSERT_MODE);
                            printf("Edit mode\n");
                        }
                        break;
                }
            }
            else
            {
                BITWISE_UNSET(editorModes, INSERT_MODE);
                printf("Command mode\n");
            }   
        } else if (current_char == 'q' && (editorModes & INSERT_MODE) == 0) {
            break;
        }
    }

    restoreTerminalSettings(old_termios);
    // printf("Hello World  %d\n", input);
    return(0);
}