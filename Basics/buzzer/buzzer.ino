const int pinButton[8] = {6,7,8,9,10,11,12,13};

const int pinBuzzer = 2;

void setup() {
  pinMode(pinBuzzer, OUTPUT);
//  digitalWrite(pinBuzzer, 0);
  for(int i=0;i<8;i++){
    pinMode(pinButton[i], INPUT);
  }
}

void loop() {  
  if (digitalRead(pinButton[0]) == HIGH) {
      tone(pinBuzzer, 262);
    } else if (digitalRead(pinButton[1]) == HIGH) {
      tone(pinBuzzer, 294);
    } else if (digitalRead(pinButton[2]) == HIGH) { 
      tone(pinBuzzer, 330);
    } else if (digitalRead(pinButton[3]) == HIGH) {
      tone(pinBuzzer, 349);
    } else if (digitalRead(pinButton[4]) == HIGH) {
      tone(pinBuzzer, 392);
    } else if (digitalRead(pinButton[5]) == HIGH) {
      tone(pinBuzzer, 440);
    } else if (digitalRead(pinButton[6]) == HIGH) {
      tone(pinBuzzer, 494);
    } else if (digitalRead(pinButton[7]) == HIGH) {
      tone(pinBuzzer, 523);
    } else 
      noTone(pinBuzzer);
}
