#include <Arduino.h>
#include <Servo.h>

const int servoPin = 2;        // Servo an GP2
HardwareSerial picoCom(0);     // UART auf GP0 (RX) und GP1 (TX)

Servo schranke;
String empfang = "";

void setup() {
  Serial.begin(115200);
  picoCom.begin(9600);
  schranke.attach(servoPin);
  schranke.write(0);           // Schranke zu
  Serial.println("Pico 2 (Schranke) bereit");
}

void loop() {
  // Nachricht von Pico 1 empfangen
  while (picoCom.available()) {
    char c = picoCom.read();
    if (c == '\n') {
      empfang.trim();
      if (empfang.startsWith("EIN:")) {
        String kennzeichen = empfang.substring(4);
        Serial.print("Kennzeichen empfangen: ");
        Serial.println(kennzeichen);
        schrankeOeffnen();
      }
      empfang = "";
    } else {
      empfang += c;
    }
  }
}

void schrankeOeffnen() {
  schranke.write(90);          // Schranke auf
  Serial.println("Schranke geoeffnet");
  delay(3000);                 // 3 Sekunden offen
  schranke.write(0);           // Schranke zu
  Serial.println("Schranke geschlossen");
}

