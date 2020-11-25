#include <QDateTime>

#include "FilterSniff.hpp"


void FilterSniff::checkFrame(const QCanBusFrame &newFrame) noexcept{
        auto list = _pStack->getFrameList();

        auto itr = std::find_if(list.begin(),
                                list.end(), 
                                [&newFrame](const QCanBusFrame frame){
                                    return frame.frameId() == newFrame.frameId();
                                });

        if(itr == list.end())
            _pStack->addFrame(newFrame);
        else{
            auto index = std::distance(list.begin(), itr);
            _pStack->updateFrame(index, newFrame);
        }
    }

void FilterSniff::checkFramesOutOfDate(){
    auto list = _pStack->getFrameList();
    std::remove_if( list.begin(), 
                    list.end(), 
                    [](const QCanBusFrame frame){
                        constexpr int ttlFrame {10}; //[sec]
                        auto now {QDateTime::currentSecsSinceEpoch()};
                        auto frameTimeStamp {frame.timeStamp().seconds()};
                        return now > ( frameTimeStamp + ttlFrame);
                    });
    
}