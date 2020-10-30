#pragma once
#include <vector>
#include "SubMenu.hpp"
#include "MenuContent.hpp"


class Menu{
    public:
                    Menu(MenuContent &&mC, std::string name = "Main Menu")
                        : subMenu{0, name, nullptr, &_actualMenu}  {
                            subMenu.createMenu(mC.pMenuList.front());
                        }

        void        show()const {_actualMenu->show();}  
        void        execAction(char key) {_actualMenu->execAction(key);}
        BaseMenu**  getActualMenu(){return &_actualMenu;}
    private:
        SubMenu    subMenu;
        BaseMenu*   _actualMenu = &subMenu;

        void    createMenu(MenuCells* pMenuList);

};