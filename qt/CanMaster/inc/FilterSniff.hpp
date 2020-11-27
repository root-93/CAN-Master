#pragma once

#include "Filter.hpp"


class FilterSniff : public Filter{
    public:
        void checkFrame(const QCanBusFrame &newFrame) noexcept override;
    private:
        void checkFramesOutOfDate() noexcept;
};