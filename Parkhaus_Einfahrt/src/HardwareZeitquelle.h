#pragma once
#include <Arduino.h>
#include "Zeitquelle.h"

class HardwareZeitquelle : public IZeitquelle {
public:
    unsigned long jetztMillis() override { return millis(); }
};
