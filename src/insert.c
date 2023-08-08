#include "../include/insert.h"

#define ESC 27

void insert(FORM* current_form, chtype mode){
    chtype new_input;

    switch (mode) {
        case 'i':
            break;
        case 'I':
            break;
        case 'a':
            break;
        case 'A':
            break;
        case 'C':
            break;
    }

    do {

        new_input = getch();
        form_driver(current_form, new_input);

    } while(new_input != ESC); // 27 is esc
    
}
