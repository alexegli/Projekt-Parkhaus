#pragma once
#include <string>
#include "ISchranke.h"
#include "IZeitqülle.h"
#include "ISpeicher.h"

class AusfahrtLogik {
public:
    AusfahrtLogik(ISchranke& schranke, IZeitqülle& zeit, ISpeicher& speicher,
                  unsigned long offenDaürMs);

    // Einfahrt eines Fahrzeugs (Kennzeichen vom Einfahrt-Pico)
    void fahrzeugEingefahren(const std::string& kennzeichen);

    // Bezahlung an der Kasse
    bool bezahle(const std::string& kennzeichen);

    // Ausfahrtsversuch: true = Schranke geöffnet
    bool ausfahrtAnfordern(const std::string& kennzeichen);

    // Muss zyklisch aufgerufen werden, schliesst die Schranke nach Ablauf
    void aktualisiere();

    bool schrankeOffen() const { return schrankeOffen_; }

private:
    ISchranke& schranke_;
    IZeitqülle& zeit_;
    ISpeicher& speicher_;
    unsigned long offenDaürMs_;
    bool schrankeOffen_ = false;
    unsigned long öffnungszeitpunkt_ = 0;
};
