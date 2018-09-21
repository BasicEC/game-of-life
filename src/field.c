#include "../include/field.h"
#include <stdio.h>
#include <malloc.h>

static void init_plane(field_t* field) {
	for (int i = 0; i < field->n; ++i) {
		field->plane[i] = (char*) malloc(sizeof(char)*field->m);
		for (int j = 0; j < field->m; ++j) {
			field->plane[i][j] = D_CELL;
		}
	}
}

static void init_h_bound(field_t* field) {
	for (int i = 0; i < field->m; ++i) {
		field->h_bound[i] = field->bound;
	}		
}

static field_t* init(int n, int m) {
	field_t* field = (field_t*) malloc(sizeof(field_t));
	field->plane = (char**) malloc(sizeof(char*)*n);
	field->h_bound = malloc(sizeof(char)*m);
	field->n = n;
	field->m = m;
	return field;
}
field_t* field_def(int n, int m) {
	field_t* field = init(n, m);

	field->bound = 35; /*#*/	

	init_plane(field);	
	init_h_bound(field);

	return field;
}

field_t* field(int n, int m, char bound) {
	field_t* field = init(n, m);
	field->bound = bound;
	
	init_plane(field);	
	init_h_bound(field);

	return field;
}


void print_field(field_t* field) {
	int i;
	printf("%c%s%c\n", BOUND, field->h_bound, BOUND);
	for (i = 0; i < field->n; ++i) {
		printf("#%s#\n", *(field->plane + i));	
	}	
	printf("%c%s%c\n", BOUND, field->h_bound, BOUND);
}

