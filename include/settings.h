#ifndef __SETTINGS__
#define __SETTINGS__

#include <curses.h>
#include "colors.h"

typedef struct {
	WINDOW* win;
	Color_pair color;
	Color_pair selected;
	int speed;
	
} settings_win;

settings_win* settings_constructor();
void show_settings(settings_win* settings);

#endif
