#include <malloc.h>
#include "greeting.h"
#include "settings.h"

greeting_win *greeting_constructor(char **text, int n_lines, settings_win *settings)
{
	int width, height, offsetx, offsety;
	greeting_win *greeting = (greeting_win *)malloc(sizeof(greeting_win));
	greeting->settings = settings;
	greeting->text = text;
	greeting->n_lines = n_lines;
	height = n_lines + 2; /*2 lines for bounds*/
	greeting->height = height;

	/* calculation of width(max length of line)*/
	width = -1;
	for (int i = 0; i < n_lines; ++i)
	{
		offsetx = 0; /*now just a buff*/
		while (text[i][offsetx++] != 0)
			;
		if (offsetx > width)
			width = offsetx;
	}
	width += 2; /*2 cols for bounds*/
	greeting->width = width;
	offsetx = (COLS - width) / 2;
	offsety = (LINES - height) / 2;
	if (offsetx <= 0 || offsety <= 0)
		return NULL; /*you must be ready to catch this null*/

	greeting->win = newwin(height, width, offsety, offsetx);
	return greeting;
}

static void print_btn(greeting_win *greeting, Color_pair color, int isPlay)
{
	wattron(greeting->win, COLOR_PAIR(color));
	if (isPlay)
	{
		wmove(greeting->win, greeting->height - 1, 10);
		waddstr(greeting->win, "< Play >");
	}
	else
	{
		wmove(greeting->win, greeting->height - 1, greeting->width - 22);
		waddstr(greeting->win, "< Settings >");
	}
	wattroff(greeting->win, COLOR_PAIR(color));
}

void show_greeting(greeting_win *greeting)
{
	if (greeting->settings == NULL)
	{
		wattron(greeting->win, COLOR_PAIR(CYAN));
	}
	else
	{
		wattron(greeting->win, COLOR_PAIR(greeting->settings->color));
	}
	box(greeting->win, 0, 0);
	int isPlay = 0;
	for (int i = 0; i < greeting->n_lines; ++i)
	{
		wmove(greeting->win, i + 1, 1);
		wrefresh(greeting->win);
		waddstr(greeting->win, greeting->text[i]);
	}
	
	print_btn(greeting, greeting->settings->color, isPlay);
	isPlay = (isPlay + 1) % 2;
	print_btn(greeting, greeting->settings->selected, isPlay);
	curs_set(0);
	keypad(greeting->win, TRUE);
	while (true)
	{
		switch (wgetch(greeting->win))
		{
		case 10: /* KEY_ENTER doesn't work >:[ */
			if (isPlay) {
				return;
			} else {
				clear();
				refresh();
				show_settings(greeting->settings);
				return;
			}

		case KEY_RIGHT:
		case KEY_LEFT:
			print_btn(greeting, greeting->settings->color, isPlay);
			isPlay = (isPlay + 1) % 2;
			print_btn(greeting, greeting->settings->selected, isPlay);
		}
	}
}

void free_greeting(greeting_win *greeting)
{
	free(greeting->text);
	free(greeting);
}
