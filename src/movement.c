#include "../include/movement.h"

static bool __is_first_field(FORM* form){
    int index = field_index(current_field(form)) == 0;
    return index;
}

static bool __is_last_field(FORM* form){
    int index = field_index(current_field(form)) == (field_count(form) - 1);
    return index;
}

void movement(FORM* current_switch_form, int input){
    switch(input){
        case 'j': case KEY_DOWN:
            if(__is_last_field(current_switch_form)){
                break;
            }
            form_driver(current_switch_form, REQ_NEXT_FIELD);
            form_driver(current_switch_form, REQ_END_LINE);
            break;
        case 'k': case KEY_UP:
            if(__is_first_field(current_switch_form)){
                break;
            }
            form_driver(current_switch_form, REQ_PREV_FIELD);
            form_driver(current_switch_form, REQ_END_LINE);
            break;
    }
}
