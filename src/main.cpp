#include <ncurses.h>
#include <stdlib.h>
#include "../include/CanUtils.hpp"
#include "../include/Menu.hpp"
#include "../include/MenuContent.hpp"
#include "../include/Controler.hpp"

using namespace std;


int main([[maybe_unused]]int argc,[[maybe_unused]] char *argv[]) {
    
    system("/home/root93/Repo/C++/CAN\\ Master/bash/setvcan0.sh");
    
    initscr();
    keypad(stdscr, true);
    

    MenuContent mC;
    Controler controler;
    Menu menu(std::move(mC));

    char kbCode;
    while (true){
        menu.show();
        kbCode = getch();
        menu.execute(kbCode);

        if(kbCode == 'e')
            break;
    }

    printw("\nbye");
    getch();
    endwin();
}