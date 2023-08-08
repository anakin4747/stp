#include "../include/movement.h"

static bool __is_first_field(FORM* form){
    return field_index(current_field(form)) == 0;
}

static bool __is_last_field(FORM* form){
    return field_index(current_field(form)) == (field_count(form) - 1);
}

// Returns 1 for push past first
// Returns 2 for push past last
// Returns 0 for only moving within a field
move_res_t movement(FORM* current_switch_form, int input){
    int res1, res2;
    switch(input){
        case 'j': case KEY_DOWN:
            if(__is_last_field(current_switch_form)){
                return NEXT_SWITCH;
            }
            res1 = form_driver(current_switch_form, REQ_NEXT_FIELD);
            res2 = form_driver(current_switch_form, REQ_END_LINE);
            break;
        case 'k': case KEY_UP:
            if(__is_first_field(current_switch_form)){
                return PREV_SWITCH;
            }
            res1 = form_driver(current_switch_form, REQ_PREV_FIELD);
            res2 = form_driver(current_switch_form, REQ_END_LINE);
            break;
    }
    if(res1 != E_OK && res2 != E_OK){
        return MOVE_ERROR;
    }
    return INTRA_FORM;
}
