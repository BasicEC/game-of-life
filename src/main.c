#include "field.h"
#include <stdio.h>
#include <malloc.h>
#include <unistd.h> /* sleep() */
#include <curses.h>
#include "greeting.h"
#include "colors.h"
#include "settings.h"
#include <pthread.h>
#include <stdlib.h>

field_t *field;
settings_win *settings;
greeting_win *greeting;
pthread_mutex_t mp = PTHREAD_MUTEX_INITIALIZER;

void *draw_plane(void *vptr_args)
{
	while (true)
	{
		pthread_mutex_lock(&mp);
		calc_step(field);
		print_field(field, stdscr);
		wrefresh(stdscr);
		usleep(100000 * settings->speed);
		pthread_mutex_unlock(&mp);
		usleep(1000);
	}
}

int mark_field() {

	int key;
	int x = 1, y = 1, isNotEnter = 1;

	wmove(stdscr, y, x);
	curs_set(1);

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
				field->plane[y - 1][x - 1] = L_CELL;
				break;
			case L_CELL:
				field->plane[y - 1][x - 1] = D_CELL;
				break;
			}
			field->buff[y - 1][x - 1] = field->plane[y - 1][x - 1];
			waddch(stdscr, field->buff[y - 1][x - 1]);
			break;
		case 10: /*KEY_ENTER*/
			isNotEnter = 0;
			break;
		case 27:
			endwin();
			printf("goodbye >:|\n");
			return 1;
		}
		wmove(stdscr, y, x);
	}
	curs_set(0);
	return 0;
}

void *listen_key(void *vptr_args)
{
	int isNotExit = 1;
	keypad(stdscr, TRUE);
	while (isNotExit)
	{
		switch (getch())
		{
		case 27: /* esc*/
			isNotExit = 0;
			break;
		case 'H':
		case 'h':
			pthread_mutex_lock(&mp);
			show_greeting(greeting);
			wattron(stdscr, COLOR_PAIR(settings->color));
			clear();
			box(stdscr, 0, 0);
			print_field(field, stdscr);
			wrefresh(stdscr);
			pthread_mutex_unlock(&mp);
			break;
		case 'M':
		case 'm':
			pthread_mutex_lock(&mp);
			if (mark_field()) isNotExit = 0;
			pthread_mutex_unlock(&mp);
		}
	}
	pthread_exit(NULL);
}


int main()
{
	pthread_t drawer;
	pthread_t keyListener;
	int status;
	char hello00[] = "Welcome to Game of Life. >:]";
	char hello01[] = "h - Help";
	char hello02[] = "Esc - exit";
	char hello03[] = "m - mark field"; 
	char hello04[] = "For navigation use arrow keys, for marking use SPACE.";
	char hello05[] = "Press ENTER when you finish marking.";
	char **hello_text = malloc(sizeof(char *) * 6);
	hello_text[0] = hello00;
	hello_text[1] = hello01;
	hello_text[2] = hello02;
	hello_text[3] = hello03;
	hello_text[4] = hello04; /*it looks bad, but i don't understand how to make it better*/
	hello_text[5] = hello05;
	if (!initscr())
	{
		printf("Error of init ncurses :(\n");
		return 1;
	}

	start_color();
	init_pairs(); /*this from colors.h */
	noecho();
	settings = settings_constructor();

	greeting = greeting_constructor(hello_text, 5, settings);
	if (greeting == NULL)
	{
		printf("Your terminal is too small for my greeting >:[\n");
		endwin();
		return 0;
	}

	show_greeting(greeting);
	field = field_def(LINES - 2, COLS - 2);

	wattron(stdscr, COLOR_PAIR(settings->color));

	clear();
	box(stdscr, 0, 0);

	refresh();
	keypad(stdscr, TRUE);

	if (mark_field()) return 0;

	status = pthread_create(&keyListener, NULL, listen_key, NULL);
	if (status != 0)
	{
		printf("main error: can't create thread listen_key, status = %d\n", status);
		endwin();
		exit(status);
	}
	
	status = pthread_create(&drawer, NULL, draw_plane, NULL);
	if (status != 0)
	{
		printf("main error: can't create thread draw_plane, status = %d\n", status);
		endwin();
		exit(status);
	}

	pthread_join(keyListener, NULL);
	endwin();
	printf("goodbye >:]\n");
	return 0;
}
