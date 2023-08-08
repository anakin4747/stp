#include "../include/common_headers.h"

#include "../include/switch.h"
#include "../include/movement.h"
#include "../include/insert.h"

void curses_init(void);
void curses_destroy(struct switch_t** switch_arr);

int main(void){

    chtype input;

    bool Z_depressed, quit_app;
    Z_depressed = quit_app = false;

    curses_init();

    struct switch_t** switch_array = (struct switch_t**)malloc(sizeof(struct switch_t*) * 2);
    // Switches will be stored in a variable array

    switch_array[0] = switch_malloc();
    switch_array[1] = NULL;
    // Since you are choosing to iterate based on NULL termination you
    // need to be vigilent with NULL termination

    switch_constructor(switch_array[0], 1, 0, 0);
    FORM* switch_form = switch_get_form(switch_array[0]);

    post_form(switch_form);

    switch_print(switch_array[0]);

    form_driver(switch_form, REQ_FIRST_FIELD);

    while(!quit_app){
        input = getch();

        switch(input){

            case 'j': case KEY_DOWN:
            case 'k': case KEY_UP:
                movement(switch_form, input);
                break;
            case 'q': case 'Q':
                quit_app = true; 
                break;
            case 'Z':
                Z_depressed ? (quit_app = true) : (Z_depressed = true);
                break;
            case 'i': case 'I':
            case 'a': case 'A':
                insert(switch_form, input);
                break;
            default:
                form_driver(switch_form, input);
                break;
        }

        // Ensure the ZZ are consecutive
        if(input != 'Z'){
            Z_depressed = false;
        }
    }

    unpost_form(switch_form);
    curses_destroy(switch_array);

    return 0;
}

void curses_init(void){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void curses_destroy(struct switch_t** switch_arr){
    while(*switch_arr){
        switch_destructor(*switch_arr);
        free(*switch_arr++);
    }
    endwin();
}
