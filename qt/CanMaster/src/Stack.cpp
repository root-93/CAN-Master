#include "../inc/Stack.hpp"

using namespace std;

bool operator==(QCanBusFrame first, QCanBusFrame secound){
    return first.frameId() == secound.frameId();
}

void Stack::updateFrame(const QCanBusFrame &frame){
    //auto itr {find(frame)};
    
    if(!_frameList.contains(frame))
        addFrame(frame);
    else{
        auto index = _frameList.indexOf(frame);
        _frameList.replace(index, frame);
    }
}
