#pragma once
#include <Arduino.h>
#include <map>
#include "ISpeicher.h"

class HardwareSpeicher : public ISpeicher {
public:
    void einfahren(const std::string& k, unsigned long t) override {
        fahrzeuge_[k] = {t, false};
    }
    bool istBezahlt(const std::string& k) override {
        auto it = fahrzeuge_.find(k);
        return it != fahrzeuge_.end() && it->second.bezahlt;
    }
    void setzeBezahlt(const std::string& k) override {
        auto it = fahrzeuge_.find(k);
        if (it != fahrzeuge_.end()) it->second.bezahlt = true;
    }
    void ausfahren(const std::string& k) override { fahrzeuge_.erase(k); }
    bool istAnwesend(const std::string& k) override {
        return fahrzeuge_.find(k) != fahrzeuge_.end();
    }
private:
    struct Eintrag { unsigned long einfahrt; bool bezahlt; };
    std::map<std::string, Eintrag> fahrzeuge_;
};
