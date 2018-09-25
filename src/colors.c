#include "colors.h"
#include "curses.h"

void init_pairs() {
	init_pair(CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
	init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(BLUE_WHITE, COLOR_BLUE, COLOR_WHITE);
		
}
