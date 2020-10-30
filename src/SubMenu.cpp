#include "../include/SubMenu.hpp"
#include "../include/MenuCell.hpp"

class BaseMenu;
using CM = CompositeMenu;

using namespace std;



void SubMenu::createMenu(MenuCells* pMenuList){
    unsigned int ID = 1;
    for (auto &&s : *pMenuList){
        if(s.second){
            add(new SubMenu(ID++, s.first, this, _ppActualMenu));
            
            if(dynamic_cast<MenuCells*>(pMenuList + 1))
                (*this->GetLastPP())->createMenu(++pMenuList); //recurrence
            else
                throw "Submenu is not defined";
        }
        else{
            add(new MenuCell(ID++, s.first, this));
            dynamic_cast<MenuCell*>(*GetLastPP())->setFunction([](){});//default function
        }
    }
    
    if(MenuCell *cell = dynamic_cast<MenuCell*>(*GetLastPP())){
        if(*getParentPP() == nullptr)
            cell->setFunction([](){std::exit(EXIT_SUCCESS);});
        else
            cell->setFunction([=](){this->execAction(kbEscape);});
    }
    else 
        throw "Last cell has to be MenuCell class boject";
    
    _ppSelectedCell = this->GetFirstPP();
}



void SubMenu::execAction(char key){
    switch (key){
        case kbDown:
            if(_ppSelectedCell != GetLastPP())
                _ppSelectedCell++;
            break;
        case kbUp:
            if(_ppSelectedCell != GetFirstPP())
                _ppSelectedCell--;
            break;
        case kbEscape:
        case kbBackspace:
        case kbLeft:
            if(*getParentPP() != nullptr){
                *_ppActualMenu = *getParentPP();         
            }
            break;
        case kbEnter:
        case kbRight:
            if(dynamic_cast<CM*>(*_ppSelectedCell))
                *_ppActualMenu = *_ppSelectedCell;
            else
                (*_ppSelectedCell)->execAction(key);
            break;
        default:
            break;
    }
}