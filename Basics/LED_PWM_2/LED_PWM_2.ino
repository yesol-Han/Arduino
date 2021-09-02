const int pinLED[6] = {8,9,10,11,12,13};
const int pinButton[6] = {2,3,4,5,6,7};
boolean lastButton[6] = {LOW,LOW,LOW,LOW,LOW,LOW};
boolean currentButton[6] = {LOW,LOW,LOW,LOW,LOW,LOW};
int ledMode[6] = {0,0,0,0,0,0};

void setup() {
  for(int i=0;i<6;i++){
     pinMode(pinLED[i], OUTPUT);
     pinMode(pinButton[i], INPUT);
     digitalWrite(pinLED[i], 0);
  }
}

boolean debounce(boolean last, int pin) {
  boolean current = digitalRead(pin);
  if(current != last){
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}

void loop() {
  for(int i=0;i<6;i++){
    currentButton[i] = debounce(lastButton[i],pinButton[i]);
  }
  for(int i=0;i<6;i++){
    if(currentButton[i] == HIGH && lastButton[i] == LOW){
      ledMode[i];
    }
    if (i>2 && currentButton[i] == LOW && lastButton[i] == HIGH){
        ledMode[i] != ledMode[i];
    }
    lastButton[i] = currentButton[i];
    setMode(ledMode[i], i);
  }
}

void setMode(int mode, int num){
  switch(mode) {
    case 0:
    digitalWrite(pinLED[num],0);
    break;
    case 1:
    digitalWrite(pinLED[num],1);
    break;
  }
}
