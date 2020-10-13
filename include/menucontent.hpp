#pragma once
#include <vector>
#include <string>
#include "menucell.hpp"

typedef std::vector<MenuCell> MenuCells;
class BaseMenu;

struct MenuContent{
    //Menu level 2 : parent(mainMenu)
    BaseMenu *pCanUtilsMenu = nullptr;
    std::string canUtilsMenuName = "Can Utils";

    BaseMenu *pSomethingElseMenu = nullptr;
    std::string somethingElseMenuName = "Something";

    //Menu Level 1

    BaseMenu *pMainMenu = nullptr;
    std::string mainMenuName = "Menu glowne";
    
    //Cells definition
    
    MenuCells canUtilsMenuList {
        MenuCell(1, "Candump"),
        MenuCell(2, "Cangen"),
        MenuCell(3, "Canplayer"),
        MenuCell(4, "Cansend"),
        MenuCell(5, "Cansniffer"),
        MenuCell(9, "Back", pMainMenu)
    };

    MenuCells somethingElseMenuList {
        MenuCell(1, "cell 1"),
        MenuCell(2, "cell 2"),
        MenuCell(3, "cell 3"),
        MenuCell(4, "cell 4"),
        MenuCell(5, "cell 5"),
        MenuCell(9, "Back", pMainMenu)
    };

    MenuCells mainMenuList{
        MenuCell(1, "Can Utils", pCanUtilsMenu),
        MenuCell(2, "Something else", pSomethingElseMenu),
        MenuCell(9, "Exit")
    };

    void setSubmenu(){

    }

    void closeApp(){
        //printw("I don't know what I should to do :(");
    }
};