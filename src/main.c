#include <stdlib.h>
#include <ncurses.h>

#include "../include/switch.h" // Includes form.h

int main(void){

    int ch;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    struct switch_t* swtch = switch_malloc();

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
