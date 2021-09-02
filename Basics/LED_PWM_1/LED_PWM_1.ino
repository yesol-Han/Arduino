const int pinLED[3] = {8,9,10};
const int pinButton[3] = {2,3,4};
boolean lastButton[3] = {LOW,LOW,LOW};
boolean currentButton[3] = {LOW,LOW,LOW};
int ledMode[3] = {0,0,0};

void setup() {
  for(int i=0;i<3;i++){
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
  for(int i=0;i<3;i++){
    currentButton[i] = debounce(lastButton[i],pinButton[i]);
  }
  for(int i=0;i<3;i++){
    if(currentButton[i] == HIGH && lastButton[i] == LOW){
      if(ledMode[i]!=0){
        ledMode[i] = 0;
      } else{
      ledMode[i] = 1;
      }
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
