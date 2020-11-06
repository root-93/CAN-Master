#include "canmaster.h"
#include <ncurses.h>
#include "Menu.hpp"
#include "MenuContent.hpp"
#include "Controler.hpp"
#include <QApplication>
#include <iostream>
//#include <csignal>
//#include <unistd.h>

void consoleView();
int GUI(int argc, char *argv[]);

//int wait = 1;
//void signalHandler([[maybe_unused]]int sig){
//    wait = 0;
//}


int main(int argc, char *argv[]){
    //signal(SIGUSR1, signalHandler);
    volatile int a = system("/home/root93/Repo/C++/CAN\\ Master/qt/CanMaster/bash/setvcan0.sh");
    //while(wait){sleep(1);}
    if (a != 0) {
        std::exit(EXIT_FAILURE);
    }

    int exitCode = 0;
    QString param {"-c"};
    if(param == argv[1]){
        consoleView();
    }
    else{
        exitCode = GUI(argc, argv);
    }
    return exitCode;
}



int GUI(int argc, char *argv[]){
    QApplication a(argc, argv);
    CanMaster w;
    w.show();
    return a.exec();  
}



void consoleView(){
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
