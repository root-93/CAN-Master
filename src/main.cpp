#define C_PLUS_PLUS

#include <ncurses.h>
#include "../include/canutils.hpp"
#include "../include/menu.hpp"
#include "../include/menucontent.hpp"
#include <unistd.h>

enum{
    kbUp = 72,
    kbDown = 80,
    kbLeft = 77,
    kbEscape = 27
};

int main() {
    initscr();
    keypad(stdscr, true);
    noecho();
    printw("Hello from Can Master!\n");

    MenuContent mC;
    Menu menu(std::move(mC));
    

    char kbCode;
    while (true){
        menu.pActualMenu->showMenu();
        kbCode = getch();
        printf("code = %i", kbCode);
        usleep(200000);
        // switch(KbCode){
        //     case(kbDown)
        // }
        if(kbCode == 'e')
            break;
    }

    printw("\nbye");
    getch();
    endwin();
}


//==========================================================
    // char *param0 = const_cast<char *>("canDump");
    // char *param1 = const_cast<char *>("vcan0");
    // char *pCanDumpArg[] {param0,
    //                      param1};

    // char **ppCanDumpArg = pCanDumpArg;
    // int returnValue = canDump(2, ppCanDumpArg);
    // cout << returnValue;
//==========================================================