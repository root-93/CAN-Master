#pragma once
#include <string>
#include <functional>

class BaseMenu;

using pCellAction = std::function<void()>;

class MenuCell{
    public:
        MenuCell(unsigned int ID, std::string description, bool subMenu = false, pCellAction pAction = nullptr)
            :pAction{pAction}, _ID{ID}, _description{description}, _isSubMenu{subMenu}, _pSubMenu{}{};
        ~MenuCell(){ _pSubMenu = nullptr;}

        pCellAction     pAction;
        
        BaseMenu*       getSubMenu() {return _pSubMenu;}
        void            setSubMenu(BaseMenu *pSubMenu) {_pSubMenu = pSubMenu;}
        std::string     getDescription()const {return _description;}    
        int             getID()const {return _ID;}
        void            setAction(pCellAction pA) {pAction = pA;}
        bool            isSubMenu()const {return _isSubMenu;}

        // trzeba to porawić, porównanie nie kompletne !!!
        bool            operator==(const MenuCell &mC)const noexcept{
                            return (_ID == mC._ID && 
                            _description == mC.getDescription());
                            //_pAction == mC._pAction &&
                        }
    private:
        unsigned int    _ID;
        std::string     _description;
        bool            _isSubMenu;
        BaseMenu*       _pSubMenu;  
};