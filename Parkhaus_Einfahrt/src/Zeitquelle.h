#pragma once


class IZeitquelle {
public:
    virtual ~IZeitquelle() = default;
    virtual unsigned long jetztMillis() = 0;
};
