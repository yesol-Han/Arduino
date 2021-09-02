const int led[3]={9,10,11};
const int pinTrig = 2;
const int pinEcho = 4;
int rangeMax = 30;
int rangeMin=0;
long T, L;

void setup() {
  Serial.begin(9600);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  for(int i=0;i<3;i++){
    pinMode(led[i],OUTPUT);
    digitalWrite(led[i],0);
  }
}

void loop() {
  digitalWrite(pinTrig, LOW); delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH); delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  T = pulseIn(pinEcho, HIGH);
  L = T/58.82;
  if(L>=rangeMin && L<=10){
    digitalWrite(led[0],0);
    digitalWrite(led[1],0);
    digitalWrite(led[2],1);
  } else if(L>10 && L<=15){
    digitalWrite(led[0],0);
    digitalWrite(led[1],1);
    digitalWrite(led[2],0);
  } else if(L>15 && L<=rangeMax){
    digitalWrite(led[0],1);
    digitalWrite(led[1],0);
    digitalWrite(led[2],0);
  } else {
    digitalWrite(led[0],0);
    digitalWrite(led[1],0);
    digitalWrite(led[2],0);
  }
  delay(100);
}
