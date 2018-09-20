#include "ESC.h"
#include <stdio.h>

void main() {
	set_display_atrib(F_YELLOW); 
	set_display_atrib(B_BLUE); 
	clrscr();
	home();
	printf("┌────────────────────────┐\n");
	printf("|      Hello World!      |\n");
	printf("└────────────────────────┘\n");
}
