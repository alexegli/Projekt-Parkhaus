#include <Arduino.h>
#include <Servo.h>

Servo schranke;
const int SERVO_PIN = 8;   

String kennzeichen = "";
bool bezahlt = false;

void setup() {
  Serial.begin(115200);      
  Serial1.begin(9600);       

  schranke.attach(SERVO_PIN);
  schranke.write(0);         
  Serial.println("Ausfahrt-Pico bereit");
}

void loop() {
  
  if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    data.trim();
    if (data.startsWith("EINF:")) {
      kennzeichen = data.substring(5);
      bezahlt = false;
      Serial.print("Fahrzeug eingefahren: ");
      Serial.println(kennzeichen);
    }
  }

  
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'p' && kennzeichen != "") {
      bezahlt = true;
      Serial.println("Bezahlung erhalten - Schranke oeffnet");
      schranke.write(90);    
      delay(3000);           
      schranke.write(0);     
    }
  }
}
