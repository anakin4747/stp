#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../include/common_headers.h"

typedef enum {
    INTRA_FORM, // Moving within a switch form
    NEXT_SWITCH, // Move to next switch
    PREV_SWITCH, // Move to previous switch
    MOVE_ERROR
} move_res_t;

move_res_t movement(FORM* current_switch_form, int input);

#endif // MOVEMENT_H
