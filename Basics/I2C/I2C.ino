#include <Wire.h>
#define sv2 9
const int led = 9;

byte i = 0;
int x =0;
void setup() {
  Wire.begin(sv2);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  if (x > 28) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }
  delay(1000);
}

void receiveEvent(int howMany) {
  x = Wire.read();
  Serial.print(x);
}
