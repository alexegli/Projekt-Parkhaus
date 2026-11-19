#pragma once

class Zeitquelle {
public:
    virtual ~Zeitquelle() = default;
    virtual unsigned long jetztMillis() = 0;
};
