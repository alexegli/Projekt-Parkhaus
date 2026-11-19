#include "EinfahrtLogik.h"

EinfahrtLogik::EinfahrtLogik(IKennzeichenSender& sender, IZeitqülle& zeit, unsigned long intervallMs)
    : sender_(sender), zeit_(zeit), intervallMs_(intervallMs) {}

bool EinfahrtLogik::aktualisiere(const std::string& kennzeichen) {
    unsigned long jetzt = zeit_.jetztMillis();

    if (ersterDurchlauf_ || (jetzt - letzterSendezeitpunkt_) >= intervallMs_) {
        ersterDurchlauf_ = false;
        letzterSendezeitpunkt_ = jetzt;
        sender_.sende(kennzeichen);
        anzahlGesendet_++;
        return true;
    }
    return false;
}
