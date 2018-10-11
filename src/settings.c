#include "colors.h"
#include "settings.h"
#include <malloc.h>
#include <curses.h>
#include <math.h>

#define S_HEIGHT 8
#define S_WIDTH 50

static void printSpeed(WINDOW *win, int speed)
{
	switch (speed)
	{
	case 0:
		waddstr(win, "< 5 >");
		break;
	case 1:
		waddstr(win, "< 4 >");
		break;
	case 2:
		waddstr(win, "< 3 >");
		break;
	case 3:
		waddstr(win, "< 2 >");
		break;
	case 4:
		waddstr(win, "< 1 >");
		break;
	}
}

static void printColor(WINDOW *win, Color_pair text)
{
	switch (text)
	{
	case CYAN:
		waddstr(win, "<  CYAN  >");
		break;
	case YELLOW:
		waddstr(win, "< YELLOW >");
		break;
	case GREEN:
		waddstr(win, "< GREEN  >");
		break;
	case BLACK:
		break;
	}
}

static void print_btn(settings_win *settings, Color_pair color, int isColor)
{

	wattron(settings->win, COLOR_PAIR(color));
	if (isColor)
	{
		wmove(settings->win, 2, 18);
		printColor(settings->win, settings->color);
	}
	else
	{
		wmove(settings->win, 5, 18);
		printSpeed(settings->win, settings->speed);
	}
	wattroff(settings->win, COLOR_PAIR(color));
}

static void draw_win(settings_win *settings)
{
	wattron(settings->win, COLOR_PAIR(settings->color));
	box(settings->win, 0, 0);
	wmove(settings->win, 0, (S_WIDTH - 10) / 2);
	waddstr(settings->win, " Settings ");
	wmove(settings->win, S_HEIGHT - 1, (S_WIDTH - 34) / 2);
	waddstr(settings->win, " Press Enter when you'll be ready ");

	wmove(settings->win, 2, 1);
	waddstr(settings->win, "     Color:      ");

	wmove(settings->win, 5, 1);
	waddstr(settings->win, "     Speed:      ");
}

void show_settings(settings_win *settings)
{
	int is_color_btn = 1;
	draw_win(settings);
	print_btn(settings, settings->selected, 1);
	print_btn(settings, settings->color, 0);

	noecho();
	curs_set(0);
	keypad(settings->win, TRUE);
	while (true)
	{
		switch (wgetch(settings->win))
		{
		case 10: /*KEY_ENTER*/
			return;

		case KEY_DOWN: /*case KEY_DOWN is empty because it's like key_up*/
		case KEY_UP:
			print_btn(settings, settings->color, is_color_btn);		
			is_color_btn = (is_color_btn + 1) % 2;
			print_btn(settings, settings->selected, is_color_btn);
			break;

		case KEY_LEFT:
			if (is_color_btn)
			{
				settings->color = ((settings->color % 3) + 1) % 3 + 1;
				print_btn(settings, settings->selected, 1);
				draw_win(settings);
				print_btn(settings, settings->color, 0);
			}
			else
			{
				settings->speed = (settings->speed + 1) % 5;
				print_btn(settings, settings->selected, 0);
			}
			break;

		case KEY_RIGHT:
			if (is_color_btn)
			{
				settings->color = settings->color % 3 + 1;
				print_btn(settings, settings->selected, 1);
				draw_win(settings);
				print_btn(settings, settings->color, 0);
			}
			else
			{
				settings->speed = (settings->speed + 4) % 5;
				print_btn(settings, settings->selected, 0);
			}
			break;
		}
		wrefresh(settings->win);
	}
}

settings_win *settings_constructor()
{
	int offsetx, offsety;
	offsetx = (COLS - S_WIDTH) / 2;
	offsety = (LINES - S_HEIGHT) / 2;
	if (offsetx <= 0 || offsety <= 0)
		return NULL; /*you must be ready to catch this null*/

	settings_win *settings = (settings_win *)malloc(sizeof(settings_win *));
	settings->win = newwin(S_HEIGHT, S_WIDTH, offsety, offsety);
	settings->color = CYAN; /*default*/
	settings->selected = BLACK;
	settings->speed = 4;
	wattron(settings->win, COLOR_PAIR(settings->color));
	return settings;
}