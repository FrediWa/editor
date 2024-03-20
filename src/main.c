#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>

#include "includes/editor.h"

int main(int argc, char** argv)
{

    EditorContext ctx;
    init_editor(&ctx);
    ctx.file_name = argv[1];
    printf(ASB_ENTER, CLEAR_SCREEN, HOME_CURSOR);
    int editorModes = 0;

    FILE* fp;
    fp = fopen(argv[1], "r");
    if ( fp == NULL)
    {
        printf("File input required\n");
        return(1);
    }
    read_file(&ctx, fp);
    draw_editor_window(&ctx);

    enable_raw_mode();
    
    char current_char;
    while (1)
    {
        current_char = read_key();
        if (current_char == '\033') { // ANSI escape sequence
            char ch = read_key();
            if (ch == '['){
                ch = read_key();
                switch (ch) {
                    case 'A':
                        // printf("Up arrow key pressed\n");
                        ctx.current_line--;
                        break;
                    case 'B':
                        ctx.current_line++;
                        printf(ANSI_ESCAPE_CURSOR_POSITION, ctx.current_line, ctx.current_char);
                        // printf("Down arrow key pressed\n");
                        break;
                    case 'C':
                        // printf("Right arrow key pressed\n");
                        ctx.current_char++;
                        break;
                    case 'D':
                        // printf("Left arrow key pressed\n");
                        ctx.current_char--;
                        break;
                    case '2':
                        if (read_key() == '~')
                        {
                            enter_edit_mode(&ctx);
                        }
                        break;

                    
                }
            }
            else
            {
                exit_edit_mode(&ctx);
            }   
            
        // draw_editor_window(&ctx);
        } else if (current_char == 'q' && !ctx.edit_mode) {
            break;
        }
    }
    // printf("Hello World  %d\n", input);
    printf(ASB_EXIT);
    return(0);
}