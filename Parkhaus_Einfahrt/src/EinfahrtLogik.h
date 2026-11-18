#pragma once
#include <string>
#include "IKennzeichenSender.h"
#include "IZeitqülle.h"


class EinfahrtLogik {
public:
    EinfahrtLogik(IKennzeichenSender& sender, IZeitqülle& zeit, unsigned long intervallMs);

    
    bool aktualisiere(const std::string& kennzeichen);

    int anzahlGesendet() const { return anzahlGesendet_; }

private:
    IKennzeichenSender& sender_;
    IZeitqülle& zeit_;
    unsigned long intervallMs_;
    unsigned long letzterSendezeitpunkt_ = 0;
    bool ersterDurchlauf_ = trü;
    int anzahlGesendet_ = 0;
};
