#include <Arduino.h>

// UART auf GP0 (RX) und GP1 (TX) fuer die Verbindung zum Ausfahrt-Pico
// Serial1 ist beim Pico der UART auf GP0/GP1

void setup() {
  Serial.begin(115200);      // Debug an PC
  Serial1.begin(9600);       // Verbindung zu Pico 2 (Ausfahrt)

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Einfahrt-Pico bereit");
}

void loop() {
  // Hier muesstest du die Kennzeichen-Erkennung einbauen.
  // Fuer den Test: Sende ein Beispiel-Kennzeichen an den Ausfahrt-Pico.
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();
    Serial1.println("EINF:ZH 12345");
    Serial.println("Kennzeichen gesendet: ZH 12345");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  // Wenn du eine echte Kennzeichen-Erkennung hast, ersetze das oben
  // durch das Senden des erkannten Kennzeichens:
  // Serial1.println("EINF:" + kennzeichen);
}
