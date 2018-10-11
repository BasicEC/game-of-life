#ifndef __FIELD__
#define __FIELD__

#include <curses.h>
/*
 * L_CELL must be greater than D_CELL
 * else you must rewrite calc_step() in field.c
 */
#define D_CELL 32 /*dead cell (space)*/
#define L_CELL 35 /*living cell*/ 

typedef struct {
	char** plane;
	char** buff;
	int n;
	int m;
} field_t;

/* "constructors" */
field_t* field_def(int n, int m);

void field_free(field_t* field);

/* funcs */
void print_field(field_t* field, WINDOW* win);
void calc_step(field_t* field);

#endif
