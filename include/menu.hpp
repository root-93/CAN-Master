#pragma once
#include "menucell.hpp"
#include "basemenu.hpp"
#include "menucontent.hpp"
#include <initializer_list>

class Menu : BaseMenu{
    public:
        Menu(MenuContent &&mC);
        ~Menu();
        const BaseMenu *pActualMenu = this;
        const MenuCell *pSelectedCell = nullptr;
        
    private: 
        BaseMenu *pCanUtilsMenu;
        BaseMenu *pSomethingElseMenu;
};