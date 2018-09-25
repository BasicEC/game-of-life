#include "field.h"
#include <stdio.h>
#include <malloc.h>
#include <unistd.h> /* sleep() */
#include <curses.h>
#include "greeting.h"
#include "colors.h"

int main()
{
	int x, y;
	x = 1;
	y = 1;
	int key;
	char hello00[] = "Welcome to Game of Life. >:]";
	char hello01[] = "Now you will see a clear plane.";
	char hello02[] = "You can mark some cells as living.";
	char hello03[] = "(for navigation use arrow keys, and for marking use SPACE).";
	char hello04[] = "Press ENTER when you will be ready to start marking and in the end of marking...";
	char** hello_text = malloc(sizeof(char*)*5);
	hello_text[0] = hello00;
	hello_text[1] = hello01;
	hello_text[2] = hello02;
	hello_text[3] = hello03;
	hello_text[4] = hello04;/*it looks bad, but i don't understand how to make it better*/
	

	if (!initscr())
	{
		printf("Error of init ncurses :(\n");
		return 1;
	}
	start_color();
	init_pairs();/*this from colors.h */
	wattron(stdscr, COLOR_PAIR(GREEN_BLACK));
	noecho();

	greeting_win* greeting = greeting_constructor(hello_text, 5, NULL);/* todo settings*/
	if (greeting == NULL) {
		printf("Your terminal is too small for my greeting >:[\n");
		endwin();
		return 0;
	}
	show_greeting(greeting);	

	clear();
	box(stdscr, 0, 0);
	
	wmove(stdscr, y, x);
	refresh();
	keypad(stdscr, TRUE);

	while (TRUE)
	{
		key = getch();
		switch (key)
		{
		case KEY_UP:
			if (y <= 1)
				break;
			--y;
			wmove(stdscr, y, x);
			break;
		case KEY_DOWN:
			if (y >= LINES - 2)
				break;
			++y;
			wmove(stdscr, y, x);
			break;
		case KEY_LEFT:
			if (x <= 1)
				break;
			--x;
			wmove(stdscr, y, x);
			break;
		case KEY_RIGHT:
			if (x >= COLS - 2)
				break;
			++x;
			wmove(stdscr, y, x);
			break;
		}
		if (key == 10)
			break;
	}
	endwin();
	return 0;
}
