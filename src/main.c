#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

#include "../include/switch.h" // Includes form.h

#define INITIAL_SWITCHES 1

void curses_init(void);
void curses_destroy(struct switch_t** switch_arr);

int main(void){

    int ch, Z_depressed = 0;
    bool quit_app = false;

    curses_init();

    struct switch_t** switch_array = (struct switch_t**)malloc(sizeof(struct switch_t*) * (INITIAL_SWITCHES + 1));

    switch_array[0] = switch_malloc();
    switch_array[1] = NULL;
    // Since you are choosing to iterate based on NULL termination you
    // need to be vigilent with NULL termination

    switch_constructor(switch_array[0], 1, 0, 0);
    switch_print(switch_array[0]);
    FORM* switch_form = switch_get_form(switch_array[0]);

    while(!quit_app){
        ch = getch();

        switch(ch){

            case 'j': case KEY_DOWN:
                form_driver(switch_form, REQ_NEXT_FIELD);
                form_driver(switch_form, REQ_END_LINE);
                break;
            case 'k': case KEY_UP:
                form_driver(switch_form, REQ_PREV_FIELD);
                form_driver(switch_form, REQ_END_LINE);
                break;
            case 'q': case 'Q':
                quit_app = true; 
                break;
            case 'Z':
                Z_depressed ? (quit_app = true) : (Z_depressed = true);
                break;
            default:
                form_driver(switch_form, ch);
                break;
        }

        if(ch != 'Z'){
            Z_depressed = false;
        }
    }

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
