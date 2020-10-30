#pragma once
#include "CompositeMenu.hpp"

#define vec std::vector

class SubMenu : public CompositeMenu{
    public:
            SubMenu(uint ID, std::string name, BaseMenu* pParent = nullptr, BaseMenu** ppActualMenu = nullptr)
                : CompositeMenu(ID, name, pParent), _ppActualMenu{ppActualMenu}{}
            
            ~SubMenu() override {};

    void    createMenu(MenuCells* pMenuList);
    void    execAction(char key) override;
    private:
        BaseMenu** _ppActualMenu = nullptr;
};