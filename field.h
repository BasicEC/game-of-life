#ifndef __FIELD__
#define __FIELD__

#define D_CELL 32 /*dead cell (space)*/
#define L_CELL 43 /*living cell*/ 
#define BOUND 35  /*#*/

typedef struct {
	char** plane;
	char* h_bound;
	int n;
	int m;
	char bound;	
} field_t;

/* "constructors" */
field_t* field_def(int n, int m);
field_t* field(int n, int m, char bound);

/* funcs */
void print_field(field_t* fiel);

#endif
