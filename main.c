#include "ESC.h"
#include "field.h"
#include <stdio.h>
#include <malloc.h>

void main() {
	field_t* field01;
	field_t* field02;
	int n,m;

	set_display_atrib(F_YELLOW); 
	set_display_atrib(B_BLACK); 
	clrscr();
	printf("######################################\n");
	printf("#      Welcome to Game of Life!      #\n");
	printf("######################################\n\nWrite a size of field (n, m): ");
	
	scanf("%d%d", &n, &m);

	if (n > 100 || n < 20 || m > 100 || m < 20) {
		printf("max - 100, min - 20\nTry again or just exit (ctrl + c): ");
		scanf("%d%d", &n, &m);
	}

	field01 = field_def(n,m);
	field02 = field_def(n,m);

	print_field(field01);	
	
}
