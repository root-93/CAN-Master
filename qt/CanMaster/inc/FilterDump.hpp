#pragma once
#include "Filter.hpp"

class FilterDump : Filter{
    void checkFrame(const QCanBusFrame &frame) noexcept override {
        _pStack->addFrame(frame);
    }
};
