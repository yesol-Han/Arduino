#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5);
unsigned char c1, c2;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (mySerial.available()) { 
    c1 = mySerial.read();
    Serial.write(c1);
  }
  else if (Serial.available()) {
    c2 = Serial.read();
    mySerial.write(c2);
    Serial.write(c2);
  }
}
