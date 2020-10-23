#include <ncurses.h>
#include <stdlib.h>
#include "../include/canutils.hpp"
#include "../include/menu.hpp"
#include "../include/menucontent.hpp"
#include "../include/controler.hpp"

using namespace std;


int main([[maybe_unused]]int argc,[[maybe_unused]] char *argv[]) {
    
    system("/home/root93/Repo/C++/CAN\\ Master/python/setvcan0.sh");
    
    initscr();
    keypad(stdscr, true);
    

    MenuContent mC;
    Controler controler;
    Menu menu(std::move(mC), &controler);

    char kbCode;
    while (true){
        menu.showMenu();
        kbCode = getch();
        menu.action(kbCode);

        if(kbCode == 'e')
            break;
    }

    printw("\nbye");
    getch();
    endwin();
}