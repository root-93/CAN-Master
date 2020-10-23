#pragma once
#include <ncurses.h>
#include <string>
#include "canmaster.hpp"
#include "menucell.hpp"

class BaseMenu{
    public:
        BaseMenu            (std::string name, MenuCells& cells, BaseMenu* parent = nullptr)
                                :pParent{parent}, _name{name}, _menuCells{cells}, _pSelectedCell{getFirstCellPointer()}{};
        virtual             ~BaseMenu(){}
        
        virtual void        showMenu()const noexcept;
        virtual void        action(char key);
        BaseMenu*           pParent; 
    
    protected:
        std::string         _name;
        MenuCells           _menuCells;
        MenuCell*           _pSelectedCell = nullptr;
           
        MenuCell*           getFirstCellPointer(){return &_menuCells.front();}
        MenuCell*           getLastCellPointer(){return &_menuCells.back();}
        void                createSubMenu(MenuCells* menuList);
        void                deleteSubMenu();
        const BaseMenu*     getMainMenuPointer()const{return (pParent == nullptr) ? this : pParent->getMainMenuPointer();}
        virtual bool        isSelected(const MenuCell &cell)const;

        enum Key{
            kbDown = 2,
            kbUp,
            kbLeft,
            kbRight,
            kbBackspace = 7,
            kbEnter = 10,
            kbEscape = 27
        };
};
