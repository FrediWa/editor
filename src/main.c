#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>

#include "includes/editor.h"
#include "includes/control.h"

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
    
    int next_commmand = 0;
    while (next_command != EXIT)
    {
        request_input(0);
    } 
    // printf("Hello World  %d\n", input);
    printf(ASB_EXIT);
    return(0);
}