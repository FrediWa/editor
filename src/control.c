#include <stdio.h>

#include "includes/control.h"
#include "includes/io.h"

int _request_command_input(char current_char)
{
	switch(current_char)
	{
		case('i'):
			return ENTER_EDIT_MODE;
			break;	
		case('h'):
			return PREV_CHAR;
			break;
		case('l'):
			return NEXT_CHAR;
			break;
		case('j'):
			return NEXT_LINE;
			break;
		case('k'):
			return PREV_LINE;
			break;
		case('q'):
			//prompt_quit
			break;
		default:
			// printf("%c", current_char);
			return NOOP;
	}
}

int _request_normal_input(char current_char)
{
	if (current_char == ANSI_ESCAPE_SEQUENCE)
	{ 
		char ch = read_key();
		if (ch == ANSI_CONTROL_SEQUENCE_INTRODUCER)
		{
			ch = read_key();
			switch (ch) {
				case 'A':
					return PREV_LINE; break;
				case 'B':
				 	return NEXT_LINE; break;
				case 'C':
					return NEXT_CHAR; break;
				case 'D': return PREV_CHAR;
					break;
				case '2':
					if (read_key() == '~')
					{
						return ENTER_EDIT_MODE;
					}
					return NOOP;
					break;
			}
		}
		else
		{
			return 'c';
		}   
	}
}

int get_input(int mode)
{
	char current_char;
	current_char = read_key();
	switch(mode) 
	{
		case(INSERT_MODE):
			return _request_normal_input(current_char);
			break;
		case(COMMAND_MODE):
			return _request_command_input(current_char);
			break;
	}
}
