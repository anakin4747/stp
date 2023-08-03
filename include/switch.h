#ifndef SWITCH_H
#define SWITCH_H

// Forward declaration
struct switch_t;

// Memory allocator
struct switch_t* switch_malloc(void);

// Constructor
void switch_constructor(struct switch_t*, int);

// Destructor
void switch_destructor(struct switch_t*);

// Behaviour function
void switch_print(struct switch_t*);
void switch_add_link(struct switch_t*);

#endif // SWITCH_H