#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "includes/editor.h"

void enable_raw_mode() 
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() 
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag |= ICANON;
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char read_key() {
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

void draw_editor_contents(EditorContext* ctx)
{
    int visible_lines = ctx->window_h -1;
    printf(ANSI_ESCAPE_CURSOR_POSITION, 0, 0);
    for (int i = 0; i < visible_lines; i++)
    {
        printf("%4d %s", i, ctx->lines[i]);
    }
    
}
void draw_control_bar(EditorContext* ctx)
{   
    int last_line = ctx->window_h;
    printf(ANSI_ESCAPE_CURSOR_POSITION, last_line, 0);
    snprintf(ctx->screen_buffer, LINE_MAX_LENGTH ,"\033[31m %s | %s | %dL | %d, %d      \033[0m", ctx->file_name, (ctx->edit_mode ? "Edit Mode" : "Command Mode"), ctx->loc, ctx->current_line, ctx->current_char);
}

void draw_editor_window(EditorContext* ctx)
{
    draw_control_bar(ctx);
    printf(ctx->screen_buffer);
}

void enter_edit_mode(EditorContext* ctx)
{
    ctx->edit_mode = 1;
    draw_control_bar(ctx);
}

void exit_edit_mode(EditorContext* ctx)
{
    ctx->edit_mode = 0;
    draw_control_bar(ctx);
}

void init_editor(EditorContext* ctx)
{
    ctx->edit_mode = 0;
    ctx->current_line = 0;
    ctx->current_char = 0;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    ctx->window_h = w.ws_row;

    ctx->screen_buffer = malloc(sizeof(line) * ctx->window_h);
}