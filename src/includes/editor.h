#define INSERT_MODE 1
#define BITWISE_SET(byte, mask) byte |= mask
#define BITWISE_UNSET(byte, mask) byte &= ~mask

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
    int edit_mode;
    int window_h;
    char* file_name;
} EditorContext;

void restoreTerminalSettings(struct termios old_termios);
struct termios saveTerminalSettings(void);
void enableRawMode(void);
void disableRawMode(void);
char readKey(void);
void drawEditorWindow(EditorContext* ctx);
void enter_edit_mode(EditorContext* ctx);
void exit_edit_mode(EditorContext* ctx);
void init_editor(EditorContext* ctx);
void read_file(EditorContext* ctx, FILE* fp);