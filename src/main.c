#include "../include/field.h"
#include <stdio.h>
#include <malloc.h>
#include <unistd.h> /* sleep() */
#include <curses.h> 

static int greeting() {
	int width = 83;/*hard code*/
	int height = 7;
	int offsetx = (COLS - width) / 2;
	int offsety = (LINES - height) / 2;
	if (offsetx <=0 || offsety <=0 ) return 1;

	WINDOW *win = newwin(height, width, offsety, offsetx);	
	wattron(win, COLOR_PAIR(1));

	box(win, 0, 0);
	wmove(win , 1,1);
	waddstr(win ,"Welcome to Game of Life. >:]");/*todo: animation of typing for all phrases*/
	
	wmove(win , 2,1);
	waddstr(win ,"Now you will see a clear plane.");

	wmove(win , 3,1);
	waddstr(win ,"You can mark some cells as living.");

	wmove(win , 4,1);
	waddstr(win ,"(for navigation use arrow keys, and for marking use SPACE).");
	
	wmove(win , 5,1);
	waddstr(win ,"Press ENTER when you will be ready to start marking and in the end of marking...");
	wrefresh(win);
	keypad(stdscr, TRUE);
	while(wgetch(win) != 10);/* KEY_ENTER doesn't work >:[ */
	return 0;

}

int main() {	
	int x,y;
	x = 1;
	y = 1;
	int key;

	if(!initscr()) {
		printf("Error of init ncurses :(\n");
		return 1;
	}
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);/*Well, maybe there will be not one color*/
	/*
	todo: some flags that will change colors
	*/
	
	noecho();
	greeting();
	clear();
	box(stdscr, 0, 0);
	
	wmove(stdscr, y, x);
	refresh();
	keypad(stdscr, TRUE);
	
	while (TRUE) {
		key = getch();
		switch (key) {
		case KEY_UP:
			if (y <= 1) break;
			--y;
			wmove(stdscr, y, x);
			break;
		case KEY_DOWN:
			if (y >= LINES - 2) break;
			++y;
			wmove(stdscr, y, x);
			break;
		case KEY_LEFT:		
			if (x <= 1) break;
			--x;
			wmove(stdscr, y, x);
			break;
		case KEY_RIGHT:		
			if (x >= COLS - 2) break;
			++x;
			wmove(stdscr, y, x);
			break;
		}
		if (key == 10) break;
	}
	endwin();
	return 0;
}

