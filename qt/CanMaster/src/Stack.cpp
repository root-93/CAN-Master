#include "../inc/Stack.hpp"

using namespace std;

void Stack::updateFrame(const QCanBusFrame &frame){
    auto itr {find(frame)};
    
    if(itr == _frameList.end())
        addFrame(frame);
    else{
        auto index = std::distance(_frameList.cbegin(), itr);
        updateFrame(index, frame);
    }
}





