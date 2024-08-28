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

int request_input(int command_mode);

#endif