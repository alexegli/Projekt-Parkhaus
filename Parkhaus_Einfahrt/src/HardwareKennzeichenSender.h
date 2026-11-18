#pragma once
#include <Arduino.h>
#include "IKennzeichenSender.h"


class HardwareKennzeichenSender : public IKennzeichenSender {
public:
    void sende(const std::string& kennzeichen) override {
        Serial1.println(("EINF:" + kennzeichen).c_str());
        Serial.print("Kennzeichen gesendet: ");
        Serial.println(kennzeichen.c_str());
    }
};
