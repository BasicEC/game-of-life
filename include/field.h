#ifndef __FIELD__
#define __FIELD__

#define D_CELL 32 /*dead cell (space)*/
#define L_CELL 43 /*living cell*/ 

typedef struct {
	char** plane;
	int n;
	int m;
} field_t;

/* "constructors" */
field_t* field_def(int n, int m);

/* funcs */
void print_field(field_t* field);

#endif
