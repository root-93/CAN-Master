#include "CommandKey.hpp"
#include "SubMenu.hpp"

void CommandKey::execute(char key)const {
    _pParent->move(key); 
}
