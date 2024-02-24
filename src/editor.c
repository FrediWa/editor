#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "includes/editor.h"

void enableRawMode() 
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() 
{
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

void read_file(EditorContext* ctx, FILE* fp)
{
    int loc = 0;
    ctx->lines = malloc(sizeof(line) * DEFAULT_LOC);

    while (fgets(ctx->lines[loc], LINE_MAX_LENGTH, fp) != NULL) {
        printf(ctx->lines[0]);
        loc++;
    }
    ctx->loc = loc;
}

void drawEditorContents(EditorContext* ctx)
{
    int visible_lines = ctx->window_h -1;
    printf(ANSI_ESCAPE_CURSOR_POSITION, 2, 0);
    // printf("\033[31mNumber of lines: %d Mode: %s\n\033[0m", ctx->window_h, (ctx->edit_mode ? "Edit Mode" : "Command Mode"));
    for (int i = 0; i < visible_lines; i++)
    {
        printf("%4d %s", i, ctx->lines[i]);
    }
    
}
void drawControlBar(EditorContext* ctx)
{   
    printf(ANSI_ESCAPE_CURSOR_POSITION, 0, 0);
    printf("\033[31m");
    printf("%s | %s | %dL  \n", ctx->file_name, (ctx->edit_mode ? "Edit Mode" : "Command Mode"), ctx->loc);
    printf("\033[0m");
}

void drawEditorWindow(EditorContext* ctx)
{
    // printf(CLEAR_SCREEN);
    drawControlBar(ctx);
    drawEditorContents(ctx);
}

void enter_edit_mode(EditorContext* ctx)
{
    ctx->edit_mode = 1;
    drawControlBar(ctx);
}

void exit_edit_mode(EditorContext* ctx)
{
    ctx->edit_mode = 0;
    drawControlBar(ctx);
}

void init_editor(EditorContext* ctx)
{
    ctx->edit_mode = 0;
    ctx->current_line = 0;
    ctx->current_char = 0;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    ctx->window_h = w.ws_row;
}