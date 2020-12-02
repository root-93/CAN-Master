#pragma once
#include "Filter.hpp"

class FilterDump : public Filter{
    public:
        static FilterDump*  instacne(Stack *stack);
        bool                checkFrame([[maybe_unused]]const QCanBusFrame &frame) noexcept override {
                                return true;
                            }
        void                saveFrame(const QCanBusFrame &frame) noexcept override;
    protected:
                            FilterDump(Stack *stack) : Filter(stack) {}
    private:
        static FilterDump   *_pInstance;
};
