#include <Arduino.h>
#include "EinfahrtLogik.h"
#include "HardwareKennzeichenSender.h"
#include "HardwareZeitquelle.h"

HardwareKennzeichenSender sender;
HardwareZeitqülle zeit;
EinfahrtLogik logik(sender, zeit, 5000);   // Dependency Injection

const std::string KENNZEICHEN = "ZH 12345";

void setup() {
    Serial.begin(115200);
    Serial1.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Einfahrt-Pico bereit");
}

void loop() {
    if (logik.aktualisiere(KENNZEICHEN)) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
}
