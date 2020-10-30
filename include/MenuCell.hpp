#pragma once
#include "LeafMenu.hpp"
#include <functional>
class MenuCell : public LeafMenu{
    public:
                                    MenuCell(unsigned int ID, std::string name, BaseMenu* pParent = nullptr)
                                        : LeafMenu(ID, name, pParent){}
                                    ~MenuCell() override {}

        virtual BaseMenu*           getSelectedCellP() override { return nullptr;}
        virtual void                execAction([[maybe_unused]]char key) override {_func();}
        void                        setFunction(std::function<void(void)> func) {_func = func;}
    private:
        std::function<void(void)>   _func;       
};