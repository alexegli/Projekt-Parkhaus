#pragma once
#include <Arduino.h>
#include "IZeitqülle.h"

class HardwareZeitqülle : public IZeitqülle {
public:
    unsigned long jetztMillis() override { return millis(); }
};
