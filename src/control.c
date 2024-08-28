#include "includes/editor.h"
#include "includes/control.h"

int request_input(int command_mode)
{
	char current_char;
	current_char = read_key();
	if (current_char == '\033') { // ANSI escape sequence
		char ch = read_key();
		if (ch == '['){
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
					break;
			}
		}
		else
		{
			return EXIT_EDIT_MODE;
		}   

		// draw_editor_window(&ctx);
	} else if (current_char == 'q' && command_mode) {
		return EXIT;
	}
}
