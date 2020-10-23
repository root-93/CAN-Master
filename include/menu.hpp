#pragma once
#include "basemenu.hpp"
#include "menucontent.hpp"
#include "controler.hpp"

class Menu : public BaseMenu{
    public:
                            Menu(MenuContent&& mC, Controler* controler);
                            ~Menu();
        void                showMenu(){_pActualMenu->showMenu();}
        void                action(char key){_pActualMenu->BaseMenu::action(key);}
        BaseMenu**          getActualMenuPointer() {return &_pActualMenu;}
        Controler*          getControlerP() {return _pControler;}
    private:
        BaseMenu*           _pActualMenu = this;
        Controler* const    _pControler = nullptr;
};