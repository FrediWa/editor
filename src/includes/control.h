#ifndef __CONTROL_H__
#define __CONTROL_H__

#define NOOP 0
#define EXIT 1
#define NEXT_CHAR 2
#define PREV_CHAR 3
#define NEXT_LINE 4
#define PREV_LINE 5
#define ENTER_EDIT_MODE 6
#define EXIT_EDIT_MODE 7
#define QUIT 8
#define SPACE 9
#define BACKSPACE 10
#define ENTER 11
/* 32-127 are reserved for characters the user should be able to type */

#define ANSI_ESCAPE_SEQUENCE 27
#define ANSI_CONTROL_SEQUENCE_INTRODUCER 91

#define COMMAND_MODE 0
#define INSERT_MODE 1

int get_input(int mode);
char read_key(void);

#endif