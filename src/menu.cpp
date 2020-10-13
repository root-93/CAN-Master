#include "../include/menu.hpp"
#include "../include/menucontent.hpp"
#include "../include/menucell.hpp"

Menu::Menu(MenuContent &&mC) : BaseMenu(mC.mainMenuName, mC.mainMenuList){  
    pSelectedCell = menuCells.data();

    pCanUtilsMenu = new BaseMenu(mC.canUtilsMenuName, mC.canUtilsMenuList, this);
    
    pSomethingElseMenu = new BaseMenu(mC.somethingElseMenuName, mC.somethingElseMenuList, this);
    
}

Menu::~Menu(){
       pCanUtilsMenu = nullptr;
       pSomethingElseMenu = nullptr;
       pActualMenu = nullptr;
}