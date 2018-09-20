#include "ESC.h"
#include <stdio.h>
#include <malloc.h>

void main() {
	int field_size = 0;
	int s_field_size; /*sqr*/
	char** field;
	char** buff_field;
	char* top;
	char* bot;
	int i,j;
	set_display_atrib(F_YELLOW); 
	set_display_atrib(B_BLACK); 
	clrscr();
	printf("┌────────────────────────────────────┐\n");
	printf("|      Welcome to Game of Life!      |\n");
	printf("└────────────────────────────────────┘\n\nWrite a size of field: ");

	scanf("%d", &field_size);

	if (field_size > 100 || field_size < 2) {
		printf("max - 100, min - 2\nTry again or just exit (ctrl + c): ");
	}

	field =(char**) malloc(sizeof(char*)*field_size);
	buff_field =(char**) malloc(sizeof(char*)*field_size);

	for (i = 0; i < field_size; ++i) {
		field[i] =(char*) malloc(sizeof(char)*field_size);
		buff_field[i] =(char*) malloc(sizeof(char)*field_size);

		for (j = 0; j < field_size; ++j) {
			field[i][j] = 32;/*space*/
			buff_field[i][j] = 32;
		}
	}


	top = malloc(sizeof(char)*(field_size));
	bot = malloc(sizeof(char)*(field_size));
	
	for (i = 0; i < field_size; ++i) {
		*(top + i) = '#';
		*(bot + i) = '#';
	}	
	
	
	printf("#%s#\n",top);
	for (i = 0; i < field_size; ++i) {
		printf("#%s#\n", *(field + i));	
	}	
	printf("#%s#\n",bot);
}
