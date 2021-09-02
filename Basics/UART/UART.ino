unsigned char c;
const int led[3] = {8,9,10};
int ledmode[3] = {0, 0, 0};

void setup() {
  Serial.begin(9600);
  for(int i=0;i<3;i++){
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
}

void loop() {
  if(Serial.available()){
    c = Serial.read();
    Serial.write(c);//시리얼모니터
    
  if(c == 'r'){
    ledmode[0] = !ledmode[0];
    digitalWrite(led[0], ledmode[0]);
  } else if(c == 'b'){
    ledmode[1] = !ledmode[1];
    digitalWrite(led[1], ledmode[1]);
  } else if(c == 'g'){
    ledmode[2] = !ledmode[2];
    digitalWrite(led[2], ledmode[2]);
  }
  
  }
}
