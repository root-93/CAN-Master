#include <ncurses.h>
#include "../include/basemenu.hpp"
#include "../include/menucell.hpp"
#include "../include/menu.hpp"
#include "../include/viewactiondata.hpp"

using namespace std;

#define DEFAULT_ACTION [=](){pControler->execAction(ViewActionData(s.getDescription()));}
#define MAIN_MENU_POINTER reinterpret_cast<Menu*>(const_cast<BaseMenu*>(getMainMenuPointer()))


void BaseMenu::showMenu()const noexcept{
    clear();
    
    if(has_colors()){
        start_color();
        init_pair(1,COLOR_BLACK, COLOR_GREEN);
        attron(COLOR_PAIR(1));
        
        printw("%s", _name.c_str());
        attroff(COLOR_PAIR(1));
    }
    else{
        printw("Twoja konsola nie obsługuje kolorów :(");
    }

    printw("\n\n");
    
    for (auto &&i : _menuCells){
        if(isSelected(i))
            attron(A_REVERSE);
        printw("%d: %s\n", i.getID(), i.getDescription().c_str());

        attroff(A_REVERSE);
    }
}


void BaseMenu::createSubMenu(MenuCells* pMenuList){
    auto const pMainMenu {MAIN_MENU_POINTER};
    auto const pControler{pMainMenu->getControlerP()};
    auto ppActualMenu{pMainMenu->getActualMenuPointer()};
    
    for (auto &&s : _menuCells){
        if(s.pAction == nullptr){
            if(s == *getLastCellPointer())
                s.setAction([=](){*ppActualMenu = this->pParent;});
            else
                s.setAction(DEFAULT_ACTION);
        }

        if(s.isSubMenu()){
            s.setSubMenu(new BaseMenu(s.getDescription(),
                        *pMenuList,
                        this));
            s.getSubMenu()->createSubMenu(++pMenuList); //recurrency
        }
    }
}  


void BaseMenu::deleteSubMenu(){
    for (auto &&s : _menuCells){
        if(s.isSubMenu()){
            (s.getSubMenu())->deleteSubMenu(); //recurrency
            delete s.getSubMenu();
        }
    }
}


void BaseMenu::action(char key){
    static Menu* const pMainMenu {MAIN_MENU_POINTER};
    static BaseMenu** const ppActualMenu {pMainMenu->getActualMenuPointer()};
    
    switch (key){
        case kbDown:
            if(_pSelectedCell != getLastCellPointer())
                _pSelectedCell++;
            break;
        case kbUp:
            if(_pSelectedCell != getFirstCellPointer())
                _pSelectedCell--;
            break;
        case kbEscape:
        case kbBackspace:
        case kbLeft:
            if(pParent != nullptr){
                *ppActualMenu = pParent;         
            }
            break;
        case kbEnter:
        case kbRight:
            if((_pSelectedCell->getSubMenu()) != nullptr){
                *ppActualMenu = _pSelectedCell->getSubMenu();
            }
            else
                _pSelectedCell->pAction();
            break;
        default:
            break;
    }
}


bool BaseMenu::isSelected(const MenuCell &cell)const{
    if(_pSelectedCell == nullptr){
        LOG(this->_name + ": pSelectedCell == nullptr");
        return false;
    }
    return  cell == *_pSelectedCell;
}