#include <stdlib.h>
#include <ncurses.h>

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

int positions[5][2] = {
    {NAME_Y_POS, NAME_X_POS},
    {PRIO_Y_POS, PRIO_X_POS},
    {MACA_Y_POS, MACA_X_POS},
    {NODE_Y_POS, NODE_X_POS},
    {SPED_Y_POS, SPED_X_POS}
};

void safe_quit(void);
void general_movement(char);

int main(void){


    // Initilazes screen
    initscr();
    cbreak();
    noecho();


    printw("\n"
           "Switch 1:\n"
           "  Name = \n"
           "  Priority = \n"
           "  MAC Address = \n"
           "\n"
           "  Links:\n"
           "    Opposite Node = \n"
           "    Link Speed = \n"
           "\n\n"
           " ? for help\n");

    // Move to the first position 
    move(positions[0][0], positions[0][1]);


    // Refresh screen to match memory
    refresh();
    // Anytime you print something to the window you need to refresh to ensure
    // it gets updated to the user

    // Waits for user input
    char input;
    int Z_depressed = 0;


    while(1){

        input = getch();

        // This switch statement will only run for normal mode
        // insert mode will be handled in c, i, I, a, and A
        switch (input){
            case 'h': case 'j': case 'k': case 'l':
                general_movement(input);
                break;
            case 'c':
                // replace_input();
                break;
            case 'i': case 'I': case 'a': case 'A':
                // edit_current_display(input);
                // This input for insert mode will be handled in these functions
                // editting and changing should have the same functionality the
                // change just erases before, so they can end up going to the same
                // function
                break;
            case '\033':
                printw("Escape\n");
                // Maybe just move this to the editting functions
                break;
            case '\n':
                printw("Enter\n");
                // move to next item to input
                break;
            case '?':
                printw("Help\n");
                break;
            case 'Z':
                // Wont work until the switch is looped
                Z_depressed ? safe_quit() : (Z_depressed = 1);
                break;
            case 'q':
                safe_quit();
                break;
            default:
                // Do nothing
                break;
        }
        if(input != 'Z'){
            Z_depressed = 0;
        }
    }


    // Resets terminal
    endwin();

    return 0;
}

void safe_quit(void){
    endwin();
    exit(0);
}

void general_movement(char input){
    static int current_line = 0;

    switch (input) {
        case 'j':
            if(current_line >= 4){
                // Out of bounds
            } else if(current_line <= 0){
                // Out of bounds
            } else {
                // In bounds
                current_line++;
            }
            break;

        case 'k':
            if(current_line >= 4){
                // Out of bounds
            } else if(current_line <= 0){
                // Out of bounds
            } else {
                // In bounds
                current_line--;
            }
            break;

        case 'h':
            break;
        case 'l':
            break;
        default:
            break;
    }
    move(positions[current_line][0], positions[current_line][1]);
}
