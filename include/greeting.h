#ifndef __GREETING__
#define __GREETING__ 

#include <curses.h>

typedef struct {
	WINDOW* win;
	WINDOW* settings; /*win with settings. There you can change */
	char** text;
	int n_lines; /*number of lines*/
} greeting_win;

greeting_win* greeting_constructor(char** text, int n_lines, WINDOW* settings); 
void show_greeting(greeting_win* greeting);

#endif
