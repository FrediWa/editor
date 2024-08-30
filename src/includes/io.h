#include "editor.h"

char read_key(void);
int open_file(char* filename, EditorContext* ctx);
int write_file(EditorContext* ctx);