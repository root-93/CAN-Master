#pragma once
#include <vector>
#include "SubMenu.hpp"
#include "MenuContent.hpp"
#include "Command.hpp"


class Menu{
    public:
        static Menu*    instance(MenuContent &&mC, std::string name = "Main Menu");

        void            show()const {_actualMenu->show();}  
        void            execute(char key) {_actualMenu->pCommand->execute(key);}
    private:
                        Menu(MenuContent &&mC, std::string name = "Main Menu")
                            : _subMenu{0, name, nullptr, &_actualMenu}  {
                                _subMenu.createMenu(mC.pMenuList.front());
                        }
        
        SubMenu         _subMenu;
        BaseMenu*       _actualMenu = &_subMenu;
        static Menu*    _menu;

        void            createMenu(MenuCells* pMenuList);

};

Menu* Menu::_menu = nullptr;

inline Menu* Menu::instance(MenuContent &&mC, std::string name){
    if(_menu)
        _menu = new Menu(std::move(mC), name);
    return _menu;
}