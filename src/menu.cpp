#include "../include/menu.hpp"
#include "../include/menucontent.hpp"
#include "../include/menucell.hpp"



Menu::Menu(MenuContent &&mC, Controler* controler) :
     BaseMenu(mC.mainMenuName, mC.mainMenuList), _pControler{controler}{
    auto pMenuList {mC.pMenuList.front()};
    _pActualMenu = this;
    _pSelectedCell = &_menuCells.front();
    this->createSubMenu(pMenuList);
}

Menu::~Menu(){
    deleteSubMenu();
    _pActualMenu = nullptr;
    _pSelectedCell = nullptr;
}