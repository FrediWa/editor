#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <stdio.h>

#define CLEAR_SCREEN "\033[2J"
#define ASB_ENTER    "\e[?1049h"
#define ASB_EXIT     "\e[?1049l"
#define HOME_CURSOR  "\033[H"
#define ANSI_ESCAPE_CURSOR_POSITION "\033[%d;%dH"

#define LINE_MAX_LENGTH 100
#define DEFAULT_LOC 100
#define GROWTH_FACTOR 2

typedef char line[LINE_MAX_LENGTH];
typedef struct {
    int loc;
    int current_line;
    int current_char;
    line* lines;
    int lines_size;
    int editor_mode;
    int window_h;
    char* file_name;
    char* screen_buffer;
    int file_name_given;
    char debug[20];
    // ScrollContext? {start, end}
} EditorContext;

void enable_raw_mode(void);
void disable_raw_mode(void);
void draw_editor_window(EditorContext* ctx);
void enter_editor_mode(EditorContext* ctx);
void exit_editor_mode(EditorContext* ctx);
void init_editor(EditorContext* ctx);
void read_file(EditorContext* ctx, FILE* fp);
void poll_keypresses(EditorContext* ctx);


#endif 