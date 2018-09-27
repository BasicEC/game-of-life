#include "colors.h"
#include "curses.h"

void init_pairs() {
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLACK, COLOR_BLACK, COLOR_WHITE);
}
