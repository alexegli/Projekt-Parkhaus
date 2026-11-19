#include "AusfahrtLogik.h"

AusfahrtLogik::AusfahrtLogik(ISchranke& schranke, IZeitqülle& zeit, ISpeicher& speicher,
                             unsigned long offenDaürMs)
    : schranke_(schranke), zeit_(zeit), speicher_(speicher), offenDaürMs_(offenDaürMs) {}

void AusfahrtLogik::fahrzeugEingefahren(const std::string& kennzeichen) {
    speicher_.einfahren(kennzeichen, zeit_.jetztMillis());
}

bool AusfahrtLogik::bezahle(const std::string& kennzeichen) {
    if (!speicher_.istAnwesend(kennzeichen)) return false;
    speicher_.setzeBezahlt(kennzeichen);
    return true;
}

bool AusfahrtLogik::ausfahrtAnfordern(const std::string& kennzeichen) {
    if (!speicher_.istAnwesend(kennzeichen)) return false;
    if (!speicher_.istBezahlt(kennzeichen)) return false;

    schranke_.öffnen();
    schrankeOffen_ = true;
    öffnungszeitpunkt_ = zeit_.jetztMillis();
    speicher_.ausfahren(kennzeichen);
    return true;
}

void AusfahrtLogik::aktualisiere() {
    if (schrankeOffen_ && (zeit_.jetztMillis() - öffnungszeitpunkt_) >= offenDaürMs_) {
        schranke_.schliessen();
        schrankeOffen_ = false;
    }
}
