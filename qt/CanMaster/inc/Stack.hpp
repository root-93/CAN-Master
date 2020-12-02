#pragma once
#include <vector>
#include <QCanBusFrame>
#include <algorithm>
#include <functional>
#include <exception>

struct AliasID{
    uint ID;
    QString alias;
};

#define frames QVector<QCanBusFrame>
#define IDs std::vector<AliasID>

#define frameItr frames::iterator

class Stack {
        const int       maxSize {2048};
    public:
        bool            contain(const QCanBusFrame &other)const noexcept;

        /*Update frame if exist, otherwise add new frame to list*/
        void            updateFrame(const QCanBusFrame &frame);
        void            addFrame(const QCanBusFrame &frame);
        void            removeFrame(QCanBusFrame &frame);
        void            markID(uint ID,const QString &alias);
        void            clearStack() noexcept;
        void            clearFrames() noexcept{_frameList.clear();}
        void            clearIDs() noexcept{_IDList.clear();}
        void            removeIf(std::function<bool(QCanBusFrame)> cond);
        bool            isFull()const noexcept {return _frameList.size() == maxSize;}
        frames*         getFrames() noexcept {return &_frameList;}
        auto            size()const noexcept {return _frameList.size();}
    private:
        frames          _frameList;
        IDs             _IDList;
        frameItr        find(const QCanBusFrame &other)const;
};



inline void Stack::clearStack() noexcept{
    clearFrames();
    clearIDs();
}


inline bool Stack::contain(const QCanBusFrame &other)const noexcept{
    auto itr = find(other);
    return itr == _frameList.end() ? false : true;
}


inline void Stack::addFrame(const QCanBusFrame &frame){
    if(!isFull())
        _frameList.push_back(frame);
}


inline void Stack::removeFrame(QCanBusFrame &frame){
    auto itr{find(frame)};
    if(!(itr == _frameList.end()))
        _frameList.erase(itr);
}


inline void Stack::markID(uint ID,const QString &alias){
    _IDList.push_back(AliasID{ID, alias});
}


inline void Stack::removeIf(std::function<bool(QCanBusFrame)> cond){
    std::remove_if(_frameList.begin(),
                    _frameList.end(),
                    cond);
}


inline frameItr Stack::find(const QCanBusFrame &other)const{
    auto itr = std::find_if(_frameList.begin(),
                        _frameList.end(),
                        [&other](const QCanBusFrame frame){
                            return frame.frameId() == other.frameId();
                        }
               );
    return const_cast<frameItr>(itr);
}
