#pragma once
#include <string>

class BaseMenu;

typedef void(*pAction)();

class MenuCell{
    public:
        MenuCell(unsigned int ID, std::string description, BaseMenu *subMenu = nullptr, pAction action = nullptr, bool selected = false)
            :ID{ID}, description{description}, selected{selected}, action{action}, subMenu{subMenu}{};
        ~MenuCell(){ subMenu = nullptr;}

        BaseMenu* getSubMenu()const {return subMenu;}
        std::string getDescription()const {return description;}    
        int getID()const {return ID;}
        void execAction()const {action();}
        bool isSelected()const {return selected;}

    private:
        unsigned int ID;
        std::string description;
        bool selected;
        pAction action;
        BaseMenu *subMenu;      
};