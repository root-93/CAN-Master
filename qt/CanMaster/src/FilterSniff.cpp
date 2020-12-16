#include <QDateTime>
#include <algorithm>

#include "FilterSniff.hpp"


FilterSniff* FilterSniff::_pInstance {};


FilterSniff* FilterSniff::instance(Stack *stack){
    if(!_pInstance)
        _pInstance = new FilterSniff(stack);
    return _pInstance;
}


bool FilterSniff::checkFrame([[maybe_unused]]const QCanBusFrame &newFrame) noexcept{
    checkFramesOutOfDate();
    return true;
}


void FilterSniff::saveFrame(const QCanBusFrame &newFrame) noexcept{
    _pStack->updateFrame(newFrame);
}


void FilterSniff::checkFramesOutOfDate() noexcept{
    constexpr int ttlFrame {5}; //[sec]

    static auto cond {[](const QCanBusFrame frame){
                    auto now {QDateTime::currentSecsSinceEpoch()};
                    auto frameTimeStamp {frame.timeStamp().seconds()};
                        
                    return now > ( frameTimeStamp + ttlFrame);
                }};
    
    _pStack->removeIf(cond);  
}

