#include "../include/insert.h"

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

    } while(new_input != ESC);
    
}
