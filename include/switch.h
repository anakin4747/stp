#ifndef SWITCH_H
#define SWITCH_H

#include "../include/common_headers.h"

// Forward declaration
struct switch_t;

// Memory allocator
struct switch_t* switch_malloc(void);

// Constructor
void switch_constructor(struct switch_t*, int number, int top_row, int left_col);

// Destructor
void switch_destructor(struct switch_t*);

// Behaviour function
void switch_print(struct switch_t*);
void switch_add_link(struct switch_t*);
FORM* switch_get_form(struct switch_t*);


#endif // SWITCH_H
