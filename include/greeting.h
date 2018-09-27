#ifndef __GREETING__
#define __GREETING__ 

#include <curses.h>
#include "settings.h"

typedef struct {
	WINDOW* win;
	settings_win* settings; /*win with settings. There you can change */
	char** text;
	int n_lines; /*number of lines*/
	int width;
	int height;
} greeting_win;

greeting_win* greeting_constructor(char** text, int n_lines, settings_win* settings); 
void show_greeting(greeting_win* greeting);
void free_greeting(greeting_win* greeting);

#endif
