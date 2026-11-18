#pragma once
#include <string>

// Abhängigkeit: Speicherung der eingefahrenen Fahrzeuge
class ISpeicher {
public:
    virtual ~ISpeicher() = default;
    virtual void einfahren(const std::string& kennzeichen, unsigned long zeitpunkt) = 0;
    virtual bool istBezahlt(const std::string& kennzeichen) = 0;
    virtual void setzeBezahlt(const std::string& kennzeichen) = 0;
    virtual void ausfahren(const std::string& kennzeichen) = 0;
    virtual bool istAnwesend(const std::string& kennzeichen) = 0;
};
