#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "includes/editor.h"
#include "includes/control.h"

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

void read_file(EditorContext* ctx, FILE* fp)
{
    int loc = 0;
    ctx->lines = malloc(sizeof(line) * DEFAULT_LOC);

    while (fgets(ctx->lines[loc], LINE_MAX_LENGTH, fp) != NULL) 
    {
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

    snprintf(ctx->screen_buffer, LINE_MAX_LENGTH ,
            "\033[31m %s | %s | %dL | %d, %d \033[0m", 
            ctx->file_name, 
            (ctx->editor_mode ? "Edit Mode" : "Command Mode"),
            ctx->loc,
            ctx->current_line,
            ctx->current_char
    );
}

void draw_editor_window(EditorContext* ctx)
{
    printf("Hello World\n");
    // draw_control_bar(ctx);
    // printf("(%s)", ctx->screen_buffer);
    snprintf(ctx->screen_buffer, LINE_MAX_LENGTH ,
            "\033[31m %s | %s | %dL | %d, %d \033[0m", 
            ctx->file_name, 
            (ctx->editor_mode ? "Edit Mode" : "Command Mode"),
            ctx->loc,
            ctx->current_line,
            ctx->current_char);

    printf("%s\n", ctx->screen_buffer);
}

void enter_editor_mode(EditorContext* ctx)
{
    ctx->editor_mode = 1;
    draw_control_bar(ctx);
}

void exit_editor_mode(EditorContext* ctx)
{
    ctx->editor_mode = 0;
    draw_control_bar(ctx);
}

void insert_character(char c, line line, int position)
{
    size_t characters = strlen(line);
    if(characters + 1 == LINE_MAX_LENGTH) 
        return; // Line full.

    if(position < characters) {
        strcpy(line+position+1, line+position);
    }

    line[position] = c;
}

void handle_command(EditorContext* ctx) {

}

void init_editor(EditorContext* ctx)
{
    ctx->editor_mode = 1;
    ctx->current_line = 0;
    ctx->current_char = 0;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    ctx->window_h = w.ws_row;

    ctx->screen_buffer = malloc(sizeof(line) * ctx->window_h);
}

void poll_keypresses(EditorContext* ctx) {
    while(1) {
        char action = get_input(ctx->editor_mode); 

        if(action >= 32 && action <= 127) {
            char new_character = (char) action;
            insert_character(new_character, ctx->lines[ctx->current_line], ctx->current_char);
        }

        switch(action) {
                case NEXT_CHAR:
                    ctx->current_char++;
                    break;
                case PREV_CHAR:
                    ctx->current_char--;
                    break;
                case NEXT_LINE: 
                    ctx->current_line++;
                    break;
                case PREV_LINE: 
                    ctx->current_line--;
                    break;           
            }
               
    }
    

};