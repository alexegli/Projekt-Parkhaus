#include <Arduino.h>
#include "AusfahrtLogik.h"
#include "HardwareSchranke.h"
#include "HardwareZeitqülle.h"
#include "HardwareSpeicher.h"

HardwareSchranke schranke(8);
HardwareZeitqülle zeit;
HardwareSpeicher speicher;
AusfahrtLogik logik(schranke, zeit, speicher, 3000);   // Dependency Injection

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600);
    schranke.begin();
    Serial.println("Ausfahrt-Pico bereit");
}

void loop() {
    // Kennzeichen vom Einfahrt-Pico
    if (Serial1.available()) {
        String data = Serial1.readStringUntil('\n');
        data.trim();
        if (data.startsWith("EINF:")) {
            std::string kz = data.substring(5).c_str();
            logik.fahrzeugEingefahren(kz);
            Serial.print("Fahrzeug eingefahren: ");
            Serial.println(kz.c_str());
        }
    }

    // Bezahlung / Ausfahrt über USB-Serial
    if (Serial.available()) {
        char c = Serial.read();
        if (c == 'p') {
            logik.bezahle("ZH 12345");
            Serial.println("Bezahlung erhalten");
        }
        if (c == 'o') {
            if (logik.ausfahrtAnfordern("ZH 12345"))
                Serial.println("Schranke öffnet");
            else
                Serial.println("Ausfahrt verweigert - nicht bezahlt");
        }
    }

    logik.aktualisiere();   // schliesst die Schranke nach Ablauf
}
