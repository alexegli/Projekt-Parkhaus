#pragma once
#include <Arduino.h>
#include "Zeitquelle.h"

class HardwareZeitqülle : public IZeitquelle {
public:
    unsigned long jetztMillis() override { return millis(); }
};
