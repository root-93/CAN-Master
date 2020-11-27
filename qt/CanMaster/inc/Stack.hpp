#pragma once
#include <vector>
#include <QCanBusFrame>
#include <algorithm>
#include <functional>

struct AliasID{
    uint ID;
    QString alias;
};

#define frames std::vector<QCanBusFrame>
#define IDs std::vector<AliasID>

#define frameItr std::vector<QCanBusFrame>::const_iterator

class Stack {
    public:
        bool            contain(const QCanBusFrame &other)const noexcept;

        /*Update frame if exist, otherwise add new frame to list*/
        void            updateFrame(const QCanBusFrame &frame);
        void            addFrame(const QCanBusFrame &frame);
        void            removeFrame(QCanBusFrame &frame);
        void            markID(uint ID, QString alias);
        void            clearStack() noexcept;
        void            clearFrames() noexcept{_frameList.clear();}
        void            clearIDs() noexcept{_IDList.clear();}
        void            removeIf(std::function<bool(QCanBusFrame)> cond);
    
    private:
        frames          _frameList;
        IDs             _IDList;
        void            updateFrame(std::ptrdiff_t index,const QCanBusFrame &frame);
        frameItr        find(const QCanBusFrame &other)const;
};



inline void Stack::clearStack(){
    clearFrames();
    clearIDs();
}


inline bool Stack::contain(const QCanBusFrame &other)const noexcept{
    auto itr  = find(other);
    return itr == _frameList.end() ? false : true;
}


inline void Stack::addFrame(const QCanBusFrame &frame){
    _frameList.push_back(frame);
}


inline void Stack::removeFrame(QCanBusFrame &frame){
    auto itr{find(frame)};
    if(!(itr == _frameList.end()))
        _frameList.erase(itr);
}


inline void Stack::markID(uint ID, QString alias){
    _IDList.push_back(AliasID{ID, alias});
}


inline void Stack::removeIf(std::function<bool(QCanBusFrame)> cond){
    std::remove_if(_frameList.begin(),
                    _frameList.end(),
                    cond);
}


inline frameItr Stack::find(const QCanBusFrame &other)const{
    return std::find_if(_frameList.begin(), 
                        _frameList.end(),
                        [&other](const QCanBusFrame frame){
                            return frame.frameId() == other.frameId();
                        }
            );
}