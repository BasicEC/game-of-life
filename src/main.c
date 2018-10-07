#include "field.h"
#include <stdio.h>
#include <malloc.h>
#include <unistd.h> /* sleep() */
#include <curses.h>
#include "greeting.h"
#include "colors.h"
#include "settings.h"

int main()
{
	int x = 1, y = 1, isNotEnter = 1;
	int key;
	char hello00[] = "Welcome to Game of Life. >:]";
	char hello01[] = "Now you will see a clear plane.";
	char hello02[] = "You can mark some cells as living.";
	char hello03[] = "(for navigation use arrow keys, for marking use SPACE, ENTER for start).";
	char hello04[] = "Press ENTER to choose option";
	char **hello_text = malloc(sizeof(char *) * 5);
	hello_text[0] = hello00;
	hello_text[1] = hello01;
	hello_text[2] = hello02;
	hello_text[3] = hello03;
	hello_text[4] = hello04; /*it looks bad, but i don't understand how to make it better*/
	if (!initscr())
	{
		printf("Error of init ncurses :(\n");
		return 1;
	}
	start_color();

	init_pairs(); /*this from colors.h */
	noecho();
	settings_win *settings = settings_constructor();

	greeting_win *greeting = greeting_constructor(hello_text, 5, settings);
	if (greeting == NULL)
	{
		printf("Your terminal is too small for my greeting >:[\n");
		endwin();
		return 0;
	}

	show_greeting(greeting);
	free_greeting(greeting);
	curs_set(1);
	field_t *field = field_def(LINES - 2, COLS - 2);

	wattron(stdscr, COLOR_PAIR(settings->color));

	clear();
	box(stdscr, 0, 0);

	wmove(stdscr, y, x);
	refresh();
	keypad(stdscr, TRUE);

	while (isNotEnter)
	{
		key = getch();
		switch (key)
		{
		case KEY_UP:
			if (y <= 1)
				break;
			--y;
			break;
		case KEY_DOWN:
			if (y >= LINES - 2)
				break;
			++y;
			break;
		case KEY_LEFT:
			if (x <= 1)
				break;
			--x;
			break;
		case KEY_RIGHT:
			if (x >= COLS - 2)
				break;
			++x;
			break;
		case ' ':
			switch (field->plane[y - 1][x - 1])
			{
			case D_CELL:
				field->plane[y-1][x-1] = L_CELL;
				break;
			case L_CELL:
				field->plane[y-1][x-1] = D_CELL;
				break;
			}
			field->buff[y - 1][x - 1] = field->plane[y - 1][x - 1];
			waddch(stdscr, field->buff[y - 1][x - 1]);
			break;
		case 10: /*KEY_ENTER*/
			isNotEnter = 0;
		}
		wmove(stdscr, y, x);
	}
	isNotEnter = 1;
	while (isNotEnter) {
		calc_step(field);
		print_field(field, stdscr);
		wrefresh(stdscr);
//		sleep(1);
		if (wgetch(stdscr) == 10) isNotEnter = 0;
	}

	endwin();
	return 0;
}