#include "../include/common_headers.h"

#include "../include/switch.h"
#include "../include/movement.h"
#include "../include/insert.h"

void curses_init(void);
void curses_destroy(struct switch_t** switch_arr);

int main(void){

    int result;

    chtype input;
    move_res_t move_result;

    // Used for exiting successfully
    bool Z_depressed, quit_app;
    Z_depressed = quit_app = false;

    curses_init();

    struct switch_t** switch_array = (struct switch_t**)malloc(sizeof(struct switch_t*) * 2);

    if(switch_array == NULL){
        fprintf(stderr, "Error: malloc of dynamic switch_array failed: main.c\n");
        endwin();
        exit(EXIT_FAILURE);
    }

    switch_array[0] = switch_malloc();
    if(switch_array[0] == NULL){
        fprintf(stderr, "Error: malloc of first switch failed: main.c\n");
        endwin();
        exit(EXIT_FAILURE);
    }
    switch_array[1] = NULL;
    // Since you are choosing to iterate based on NULL termination you
    // need to be vigilent with NULL termination

    switch_constructor(switch_array[0], 1, 0, 0);
    FORM* switch_form = switch_get_form(switch_array[0]);

    result = post_form(switch_form);
    if(result != E_OK){
        fprintf(stderr, "Error: posting first form failed: main.c\n");
        curses_destroy(switch_array);
        exit(EXIT_FAILURE);
    }

    switch_print(switch_array[0]);

    result = form_driver(switch_form, REQ_FIRST_FIELD);
    if(result != E_OK){
        fprintf(stderr, "Error: moving to first field in first form failed: main.c\n");
        curses_destroy(switch_array);
        exit(EXIT_FAILURE);
    }

    while(!quit_app){
        input = getch();

        switch(input){

            case 'j': case KEY_DOWN:
            case 'k': case KEY_UP:
            //case 'h': case KEY_LEFT:
            //case 'l': case KEY_RIGHT:
                move_result = movement(switch_form, input);
                if(move_result == PREV_SWITCH){
                    // Move to previous switch
                } else if(move_result == NEXT_SWITCH){
                    // Create new switch below
                } else if(move_result == MOVE_ERROR){
                    fprintf(stderr, "Error: movement failed: main.c\n");
                    curses_destroy(switch_array);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'i': case 'I':
            case 'a': case 'A':
            case 'C':
                insert(switch_form, input);
                break;
            case 'n':
                // New link on switch
                break;
            case 'q': case 'Q':
                quit_app = true; 
                break;
            case 'Z':
                Z_depressed ? (quit_app = true) : (Z_depressed = true);
                break;
            default:
                break;
        }

        // Ensure the ZZ are consecutive
        if(input != 'Z'){
            Z_depressed = false;
        }
    }

    result = unpost_form(switch_form);
    if(result != E_OK){
        fprintf(stderr, "Error: unposting form failed: main.c\n");
        curses_destroy(switch_array);
        exit(EXIT_FAILURE);
    }

    curses_destroy(switch_array);

    return EXIT_SUCCESS;
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
