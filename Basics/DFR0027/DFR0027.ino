const int pinVibM=3;
byte count =0;
const int led[3]={9,10,11};

void setup() {
  pinMode(pinVibM, INPUT);
  for(int i=0;i<3;i++){
  pinMode(led[i], OUTPUT);
  digitalWrite(led[i], 0);
  }
  Serial.begin(9600);
  attachInterrupt(1,countVib, FALLING);
  
}

void loop() {
  if(count !=0){
    count=0;
  for(int i=0;i<3;i++){
  digitalWrite(led[i], 1);
  }
    Serial.println(1);
    delay(100);
  } else {
    for(int i=0;i<3;i++){
  digitalWrite(led[i], 0);
  }
    Serial.println(0);
    delay(100);
  }
}

void countVib(){
  count++;
}
