#include <Arduino.h>

// UART auf GP0 (TX) und GP1 (RX)
HardwareSerial picoCom(0);

void setup() {
  Serial.begin(115200);        // Serial Monitor (USB)
  picoCom.begin(9600);         // Kommunikation zwischen den Picos
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Pico 1 (Einfahrt) bereit - Kennzeichen eingeben und Enter druecken");
}

void loop() {
  // Kennzeichen vom Serial Monitor lesen
  if (Serial.available()) {
    String kennzeichen = Serial.readStringUntil('\n');
    kennzeichen.trim();
    if (kennzeichen.length() > 0) {
      Serial.print("Kennzeichen erfasst: ");
      Serial.println(kennzeichen);

      // An Pico 2 senden
      picoCom.print("EIN:" + kennzeichen + "\n");
      Serial.println("An Pico 2 gesendet");

      // Kurz LED blinken als Bestätigung
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

