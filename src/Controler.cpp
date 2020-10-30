#include <ncurses.h>
#include <iostream>
#include <thread>
#include "../include/Controler.hpp"
#include "../include/CanUtils.hpp"
#include "../include/ViewActionData.hpp"

using namespace std;


void Controler::execAction(ViewActionData VAD)const {

    if( VAD.cellName == "Candump"){
        endwin();
        char *param0 = const_cast<char *>("canDump");
        char *param1 = const_cast<char *>("vcan0");
        char *pCanDumpArg[] {param0,
                             param1};

        char **ppCanDumpArg = pCanDumpArg;

        [[maybe_unused]] int returnValue = canutils::canDump(2, ppCanDumpArg);
        initscr();
        keypad(stdscr, true);
    }
    else if (VAD.cellName == "Cangen"){

    }
    else if (VAD.cellName == "Canpalyer"){

    }
    else if (VAD.cellName == "Cansend"){

    }
    else if (VAD.cellName == "Cansniffer"){
        thread tCanSniffer(canSniffer);
        char a;
        cin >> a;
    }
}

void Controler::canSniffer(){
    endwin();
        char *param0 = const_cast<char *>("canSniffer");
        char *param1 = const_cast<char *>("vcan0");
        char *pCanDumpArg[] {param0,
                             param1};

        char **ppCanDumpArg = pCanDumpArg;
        [[maybe_unused]] int returnValue = canutils::canSniffer(2, ppCanDumpArg);
        initscr();
        keypad(stdscr, true);
}
// char** Controler::createArgumentTable(vector<string> argV){
//     //char *param0 = const_cast<char *>(func);
//     //char *param1 = const_cast<char *>(socket);
//     char *pArgT[] {argV};
//     return &pArgT;
// }