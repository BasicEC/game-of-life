#include <malloc.h>
#include <unistd.h> /* sleep() */
#include "greeting.h"

static void type_string(WINDOW *win, char *str) {
	int i = 0;
	while (str[i] != 0) {
		waddch(win, str[i++]);
		wrefresh(win);
		usleep(70000);
	}
}

greeting_win* greeting_constructor(char** text, int n_lines, WINDOW* settings) {
	int width, height, offsetx, offsety;
	greeting_win* greeting = (greeting_win*) malloc(sizeof(greeting_win));
	greeting->settings = settings;
	greeting->text = text;
	greeting->n_lines = n_lines;
	height = n_lines + 2; /*2 lines for bounds*/

	/* calculation of width(max length of line)*/
	width = -1;
	for (int i = 0; i < n_lines; ++i) {
		offsetx = 0;/*now just a buff*/
		while (text[i][offsetx++] != 0);
		if (offsetx > width) width = offsetx;
	}
	width += 2; /*2 cols for bounds*/
	offsetx = (COLS - width) / 2;
	offsety = (LINES - height) / 2;
	if (offsetx <= 0 || offsety <= 0)
		return NULL;/*you must be ready to catch this null*/

	greeting->win = newwin(height, width, offsety, offsetx);
/*	wattron(greeting->win, COLOR_PAIR(settings->color)); use it when settings will be write*/	
	wattron(greeting->win, COLOR_PAIR(1));
	box(greeting->win, 0, 0);
	return greeting;
}



void show_greeting(greeting_win* greeting) {
	for (int i = 0; i < greeting->n_lines; ++i) {
		wmove(greeting->win, i+1, 1);
		wrefresh(greeting->win);
		sleep(1);
		type_string(greeting->win, greeting->text[i]);
	}
	
	keypad(stdscr, TRUE);
	while (wgetch(greeting->win) != 10); /* KEY_ENTER doesn't work >:[ */
/*todo: add work with setting window*/	
}


