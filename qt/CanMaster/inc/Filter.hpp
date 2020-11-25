#pragma once
#include <QCanBusFrame>
#include <QVector>
#include "Stack.hpp"


class Filter{
    public:
        virtual void    checkFrame(const QCanBusFrame &frame) noexcept = 0;

    protected:
                        Filter(Stack *stack) : _pStack{stack} {}
        virtual         ~Filter() = default;
        
        Stack           *_pStack;
};
