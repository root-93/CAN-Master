#pragma once
#include <vector>
#include <QCanBusFrame>

#define frames std::vector<QCanBusFrame>
#define IDs std::vector<uint>

class Stack {
    public:
        frames          getFrameList();
        IDs             getIDList();
        void            addFrame(const QCanBusFrame &frame);
        void            updateFrame(std::ptrdiff_t index,const QCanBusFrame &frame);
        void            removeFrame(QCanBusFrame &frame);
        void            markID(uint ID, QString alias);
        void            clearStack();
        void            clearFrames();
        void            clearIDs();
    
    private:
        frames          _frameList;
        IDs             _IDList;
};