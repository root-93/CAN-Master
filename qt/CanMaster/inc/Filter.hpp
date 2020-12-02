#pragma once
#include <QCanBusFrame>
#include <QVector>
#include "Stack.hpp"


class Filter{
    public:
        virtual bool    checkFrame(const QCanBusFrame &frame) noexcept = 0;
        virtual void    saveFrame(const QCanBusFrame &frame) noexcept = 0;
        virtual         ~Filter() = default;

    protected:
                        Filter(Stack *stack) : _pStack{stack} {}
        
        Stack           *_pStack;
};
