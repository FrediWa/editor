#define INSERT_MODE 1
#define BITWISE_SET(byte, mask) byte |= mask
#define BITWISE_UNSET(byte, mask) byte &= ~mask

#define CLEAR_SCREEN "\033[2J"
#define ASB_ENTER "\e[?1049h"
#define ASB_EXIT "\e[?1049l"

void restoreTerminalSettings(struct termios old_termios);
struct termios saveTerminalSettings(void);
void enableRawMode(void);
void disableRawMode(void);
char readKey(void);
void drawCharacters(FILE* fp);
void drawControlBar(void);
void drawEditorWindow(void);