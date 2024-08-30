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
    printf("File opened\n");

    read_file(&ctx, fp);
    draw_editor_window(&ctx);


    enable_raw_mode();
    
    poll_keypresses(&ctx);

    printf(ASB_EXIT);
    return(0);
}