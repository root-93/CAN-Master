#include <QDateTime>
#include <algorithm>

#include "FilterSniff.hpp"


void FilterSniff::checkFrame(const QCanBusFrame &newFrame) noexcept{
    _pStack->updateFrame(newFrame);
}


void FilterSniff::checkFramesOutOfDate(){
    constexpr int ttlFrame {10}; //[sec]

    auto cond {[ttlFrame](const QCanBusFrame frame){
                        auto now {QDateTime::currentSecsSinceEpoch()};
                        auto frameTimeStamp {frame.timeStamp().seconds()};
                        
                        return now > ( frameTimeStamp + ttlFrame);
                }};
    
    _pStack->removeIf(cond);  
}