#pragma once
#include <ncurses.h>
#include <string>
#include <vector>
#include <initializer_list>
#include "menucell.hpp"

typedef std::vector<MenuCell> MenuCells;

class BaseMenu{
    public:
        BaseMenu(std::string name, 
                MenuCells cells, 
                BaseMenu *parent = nullptr)
                :name{name}, 
                menuCells{cells}, 
                pParent{parent} {};

        virtual ~BaseMenu(){}

        virtual void showMenu()const;
        virtual bool isSelected(int ID)const{
            printw("mc ID: %i, ", ID);
            printw("pSC ID: %i  |",pSelectedCell->getID());
            return ID == pSelectedCell->getID();
        }
        
    protected:
        std::string name;
        std::vector<MenuCell> menuCells;
        const BaseMenu *pParent;
        const MenuCell *pSelectedCell;                 

};