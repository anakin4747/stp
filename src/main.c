#include <curses.h>
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

int main(int argc, char** argv){

    // Initilazes screen
    initscr();
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
           " h/j/k/l/c/a/A/i/I/<enter>\t? for help\n");

    // Refresh screen to match memory
    refresh();
    // Anytime you print something to the window you need to refresh to ensure
    // it gets updated to the user
    //
    mvprintw(NAME_Y_POS, NAME_X_POS, "NAME");
    mvprintw(PRIO_Y_POS, PRIO_X_POS, "prio");
    mvprintw(MACA_Y_POS, MACA_X_POS, "mac");
    mvprintw(NODE_Y_POS, NODE_X_POS, "node");
    mvprintw(SPED_Y_POS, SPED_X_POS, "speed");

    // Waits for user input
    char input = getch();

    switch (input){
        case 'h':
        case 'j':
        case 'k':
        case 'l':
            // general_movement_function(input);
            break;
        case 'c':
            // replace_input();
            break;
        case 'i':
        case 'I':
        case 'a':
        case 'A':
            // edit_current_display(input);
            // editting and changing should have the same functionality the
            // change just erases before, so they can end up going to the same
            // function
            break;
        case '\033':
            printw("Escape\n");
            // if in insert mode exit insert mode
            // else do nothing
            break;
        case '\n':
            printw("Enter\n");
            // move to next item to input
            // if in insert mode exit insert mode
            break;
        case '?':
            printw("Help\n");
            break;
        default:
            // Do nothing
            break;
    }

    refresh();
    getch();

    // Resets terminal
    endwin();

    return 0;
}
