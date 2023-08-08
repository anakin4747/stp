#include <curses.h>
#include <form.h>
#include <stdlib.h>

#define NAME_FIELD_WIDTH 10
#define PRIO_FIELD_WIDTH 10
#define MACA_FIELD_WIDTH 10
#define NODE_FIELD_WIDTH 10
#define SPED_FIELD_WIDTH 10

#define NAME_X_POS 9
#define NAME_Y_POS 2
#define PRIO_X_POS 13
#define PRIO_Y_POS 3
#define MACA_X_POS 16
#define MACA_Y_POS 4
#define NODE_X_POS 20
#define NODE_Y_POS 7
#define SPED_X_POS 17
#define SPED_Y_POS 8

#define DEFAULT_FIELDS 5

typedef enum {
    OPEN,
    CLOSED
} viewing_state;


typedef struct {
    viewing_state view;
    unsigned int number;
    unsigned int top_row;
    unsigned int bottom_row;
    FIELD* name;
    FIELD* priority;
    FIELD* mac_addr;
    FIELD* opposite_node;
    FIELD* link_speed;
    FIELD** field_array;
    FORM* form; // To encapsulate the fields in a switch
} switch_t;

// Memory allocator
switch_t* switch_malloc(void){
    return (switch_t*)malloc(sizeof(switch_t));
}

// Constructor
void switch_constructor(switch_t* this_switch, int number, int top_row, int left_col){
    this_switch->view = OPEN;
    this_switch->number = number;
    this_switch->top_row = top_row;
    this_switch->name = new_field(1, NAME_FIELD_WIDTH,
                                  top_row + NAME_Y_POS,
                                  left_col + NAME_X_POS,
                                  0, 0);
    this_switch->priority = new_field(1, PRIO_FIELD_WIDTH,
                                      top_row + PRIO_Y_POS,
                                      left_col + PRIO_X_POS,
                                      0, 0);
    this_switch->mac_addr = new_field(1, MACA_FIELD_WIDTH,
                                      top_row + MACA_Y_POS,
                                      left_col + MACA_X_POS,
                                      0, 0);
    this_switch->opposite_node = new_field(1, NODE_FIELD_WIDTH,
                                           top_row + NODE_Y_POS,
                                           left_col + NODE_X_POS,
                                           0, 0);
    this_switch->link_speed = new_field(1, SPED_FIELD_WIDTH,
                                        top_row + SPED_Y_POS,
                                        left_col + SPED_X_POS,
                                        0, 0);

    this_switch->field_array = (FIELD**)malloc(sizeof(FIELD*) * (DEFAULT_FIELDS + 1));
    this_switch->field_array[0] = this_switch->name;
    this_switch->field_array[1] = this_switch->priority;
    this_switch->field_array[2] = this_switch->mac_addr;
    this_switch->field_array[3] = this_switch->opposite_node;
    this_switch->field_array[4] = this_switch->link_speed;
    this_switch->field_array[DEFAULT_FIELDS] = NULL;


    for(int i = 0; i < DEFAULT_FIELDS; i++){
        set_field_back(this_switch->field_array[i], A_UNDERLINE);
        field_opts_off(this_switch->field_array[i], O_AUTOSKIP);
    }

    this_switch->form = new_form(this_switch->field_array);

    
    post_form(this_switch->form); // ?????
}

// Destructor
void switch_destructor(switch_t* this_switch){

    unpost_form(this_switch->form);
    free_form(this_switch->form);

    for(int i = 0; i < DEFAULT_FIELDS; i++){
        free_field(this_switch->field_array[i]);
    }
    free(this_switch->field_array);
}

void switch_print(switch_t* this_switch){
    unsigned int top_row = this_switch->top_row;

    mvprintw(top_row + 1, 0, "Switch %d:", this_switch->number);

    if(this_switch->view == OPEN){
        mvprintw(top_row + 2, 2, "Name = ");
        mvprintw(top_row + 3, 2, "Priority = ");
        mvprintw(top_row + 4, 2, "MAC Address = ");

        mvprintw(top_row + 6, 2, "Links:");
        mvprintw(top_row + 7, 4, "Opposite Node = ");
        mvprintw(top_row + 8, 4, "Link Speed = ");
    }

    refresh();
}

FORM* switch_get_form(switch_t* this_switch){
    return this_switch->form;
}

/* Testing purposes
int main(void){

    int ch;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    switch_t* swtch = switch_malloc();

    switch_constructor(swtch, 1, 0, 0);

    switch_print(swtch);

    FORM* switch_form = switch_get_form(swtch);

    while((ch = getch()) != 'q'){

        switch(ch){

            case 'j':
                form_driver(switch_form, REQ_NEXT_FIELD);
                form_driver(switch_form, REQ_END_LINE);
                break;
            case 'k':
                form_driver(switch_form, REQ_PREV_FIELD);
                form_driver(switch_form, REQ_END_LINE);
                break;
            default:
                form_driver(switch_form, ch);
                break;
        }
    }

    switch_destructor(swtch);
    free(swtch);
    endwin();

    return 0;
}
*/
