#pragma once
#include <string>
#include <list>
#include <vector>
#include "CanMaster.hpp"

#define itr std::vector<BaseMenu*>::iterator

class BaseMenu{
    public:
        virtual             ~BaseMenu(){}
        
        virtual void        add(BaseMenu*) = 0;
        virtual void        remove(BaseMenu*) = 0;
        virtual void        removeLast() = 0;
        BaseMenu**          getParent() {return &_pParent;}
        virtual void        show()const noexcept = 0;
        virtual void        execAction(char key) = 0;
        unsigned int        getID()const noexcept{return _ID;}    
        const std::string   getName()const noexcept{return _name;}    
        //virtual itr*        begin() {return new itr();}
        //virtual itr*        end() {return new itr();}
        virtual void        createMenu(MenuCells *pMenuList) = 0;
        virtual BaseMenu*   getSelectedCell() = 0;

    protected:
                            BaseMenu(unsigned int ID, std::string name, BaseMenu* pParent = nullptr)
                                : _ID{ID}, _name{name}, _pParent{pParent} {};

        unsigned int        _ID = 0;
        std::string         _name;
        BaseMenu*           _pParent = nullptr;     
        
        BaseMenu*           getMainMenu()const{return (_pParent == nullptr) ? const_cast<BaseMenu*>(this) : _pParent->getMainMenu();}
        
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
