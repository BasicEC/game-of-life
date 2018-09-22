#include "field.h"
#include <stdio.h>
#include <malloc.h>
#include <curses.h>

static void init_plane(field_t* field) {
	for (int i = 0; i < field->n; ++i) {
		field->plane[i] = (char*) malloc(sizeof(char)*field->m);
		for (int j = 0; j < field->m; ++j) {
			field->plane[i][j] = D_CELL;
		}
	}
}

static field_t* init(int n, int m) {
	field_t* field = (field_t*) malloc(sizeof(field_t));
	field->plane = (char**) malloc(sizeof(char*)*n);
	field->n = n;
	field->m = m;
	return field;
}


static void free_plane(field_t* field) {
	for (int i = 0; i < field->n; ++i) {
		free(field->plane[i]);
	}
}

field_t* field_def(int n, int m) {
	field_t* field = init(n, m);
	init_plane(field);	
	return field;
}

void field_free(field_t* field) {
	free_plane(field);
	free(field->plane);
	free(field);
}

/*rewrite for ncurses*/
void print_field(field_t* field) {
	int i;
	for (i = 0; i < field->n; ++i) {
		printf("%s\n", *(field->plane + i));	
	}	
}

