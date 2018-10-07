#include "field.h"
#include <stdio.h>
#include <malloc.h>
#include <curses.h>

static void init_plane(field_t* field) {
	for (int i = 0; i < field->n; ++i) {
		field->plane[i] = (char*) malloc(sizeof(char)*field->m);
		field->buff[i] = (char*) malloc(sizeof(char)*field->m);
		for (int j = 0; j < field->m; ++j) {
			field->plane[i][j] = D_CELL;
			field->buff[i][j] = D_CELL;
		}
	}
}

static void swap_planes(field_t* field) {
	char** buff = field->plane;
	field->plane = field->buff;
	field->buff = buff;
}

static field_t* init(int n, int m) {
	field_t* field = (field_t*) malloc(sizeof(field_t));
	field->plane = (char**) malloc(sizeof(char*)*n);
	field->buff = (char**) malloc(sizeof(char*)*n);
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
	free(field->buff);
	free(field);
}

void print_field(field_t* field, WINDOW* win) {
	for (int i = 0; i < field->n; ++i) {
		wmove(win, i + 1,1);
		waddstr(win, *(field->plane + i));
	}	
}
void calc_step(field_t* field) {
    int neighbor_count;
    int three_neighbor = L_CELL*3 + D_CELL*5;
    int two_neighbor = L_CELL*2 + D_CELL*6;
	for (int i = field->n; i < field->n*2; ++i) {
		for (int j = field->m; j < field->m*2; ++j) {
			neighbor_count = field->plane[(i - 1) % field->n][(j - 1) % field->m] +
			+ field->plane[i % field->n][(j - 1) % field->m] +
			+ field->plane[(i + 1) % field->n][(j - 1) % field->m] +
			+ field->plane[(i - 1) % field->n][j % field->m] +
			+ field->plane[(i + 1) % field->n][j % field->m] +
			+ field->plane[(i - 1) % field->n][(j + 1) % field->m] +
			+ field->plane[i % field->n][(j + 1) % field->m] +
			+ field->plane[(i + 1) % field->n][(j + 1) % field->m];

			switch (field->plane[i % field->n][j % field->m]) {
				case D_CELL:
				    field->buff[i % field->n][j % field->m] = D_CELL;
					if (neighbor_count == three_neighbor) field->buff[i % field->n][j % field->m] = L_CELL;
					break;
				case L_CELL:
					field->buff[i % field->n][j % field->m] = L_CELL;
					if (neighbor_count > three_neighbor) field->buff[i % field->n][j % field->m] = D_CELL;
					if (neighbor_count < two_neighbor) field->buff[i % field->n][j % field->m] = D_CELL;
					break;
			}
		}
	}
	swap_planes(field);
}

