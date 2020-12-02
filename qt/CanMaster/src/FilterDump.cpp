#include "FilterDump.hpp"

using namespace std;

FilterDump* FilterDump::_pInstance {};

void FilterDump::saveFrame(const QCanBusFrame &frame) noexcept{
     _pStack->addFrame(frame);
}


FilterDump* FilterDump::instacne(Stack *stack){
    if(!_pInstance)
        _pInstance = new FilterDump(stack);
    return _pInstance;
}
