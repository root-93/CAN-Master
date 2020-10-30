#pragma once
#include "BaseMenu.hpp"
#include "Controler.hpp"
#include "CanMaster.hpp"
#include <vector>

#define vec std::vector

class CompositeMenu : public BaseMenu{
                        
    public:
        virtual         ~CompositeMenu() override {for (auto s : _vChilds) { delete s;}};
        
        virtual void    add(BaseMenu *child) override {_vChilds.push_back(child);}
        virtual void    remove([[maybe_unused]]BaseMenu *child) override {throw "function not defined";}
        virtual void    removeLast() override {_vChilds.pop_back();}

        virtual void    show()const noexcept override;
        BaseMenu*       getSelectedCell() override {return *_ppSelectedCell;}      
        //virtual itr*    begin() override {return &_vChilds.begin() ;}
        //virtual itr*    end() override {return &_vChilds.end() ;}
        virtual void    createMenu([[maybe_unused]]MenuCells *pMenuList) override {}

    protected:
                        CompositeMenu(uint ID, std::string name, BaseMenu* pParent = nullptr)
                            : BaseMenu(ID, name, pParent){}
        
        BaseMenu**       _ppSelectedCell = nullptr;

        BaseMenu**       ppGetFirst() {return &_vChilds.front();}
        BaseMenu**       ppGetLast() {return &_vChilds.back();}
        bool            isSelected(BaseMenu* const cell)const {
                            if(_ppSelectedCell == nullptr)
                                LOG(this->_name + ": pSelectedCell == nullptr");
                            return *_ppSelectedCell == cell;
                        }
    private:
        vec<BaseMenu*>  _vChilds; 
};