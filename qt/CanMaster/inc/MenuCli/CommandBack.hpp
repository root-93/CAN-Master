#pragma once
#include "Command.hpp"
#include "MenuItem.hpp"
#include "SubMenu.hpp"
#include <ncurses.h>

class CommandBack : public Command {
    public:
                        CommandBack(SubMenu* pParent) : _pParentMenu{pParent} {}
        void            execute()const override;
        void            execute([[maybe_unused]] char key)const override {}

    private:
        SubMenu*        _pParentMenu = nullptr;
};


inline void CommandBack::execute()const {
    if(_pParentMenu->getParentP() == nullptr){
        endwin();
        std::exit(EXIT_SUCCESS);
    }
    else
        _pParentMenu->pCommand->execute(SubMenu::Key::kbEscape);
}