#pragma once

#include "Filter.hpp"


class FilterSniff : public Filter{
    public:
        static FilterSniff* instance(Stack *stack);
        bool                checkFrame(const QCanBusFrame &newFrame) noexcept override;
        void                saveFrame(const QCanBusFrame &newFrame) noexcept override;

    protected:
                            FilterSniff(Stack* stack) : Filter(stack) {}

    private:
        void                checkFramesOutOfDate() noexcept;
        static FilterSniff* _pInstance;
};
