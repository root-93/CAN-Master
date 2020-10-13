#include <ncurses.h>
#include "../include/basemenu.hpp"
#include "../include/menucell.hpp"
using namespace std;

void BaseMenu::showMenu()const {
    clear();
    
    if(has_colors()){
        start_color();
        init_pair(1,COLOR_BLACK, COLOR_GREEN);
        attron(COLOR_PAIR(1));
        
        printw("%s", name.c_str());
        attroff(COLOR_PAIR(1));
    }
    else{
        printw(":( Twoja konsola nie obsługuje kolorów");
    }

    printw("\n\n");
    
    for (auto &i : menuCells){
        if(isSelected(i.getID()))
            attron(A_BOLD);
        printw("%d: %s\n", i.getID(), i.getDescription().c_str());

        attroff(A_BOLD);
    }
}