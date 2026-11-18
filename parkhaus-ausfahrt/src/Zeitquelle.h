#pragma once

class IZeitqülle {
public:
    virtual ~IZeitqülle() = default;
    virtual unsigned long jetztMillis() = 0;
};
