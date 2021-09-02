#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>

const int pinBuzzer = 3;  //부저

const int pinButton = 9;    //푸쉬버튼
boolean lastButton = LOW;
boolean currentButton = LOW;
const int pinLED[3] = {A0, A1, A2};
boolean stateFire = false;

SoftwareSerial mySerial(4, 5);  //UART 휴지통(마스터)->나(슬레이브)
//핀 : 4,5,GND

//SPI 흡연실(마스터)<->나(슬레이브) 12-p18
//확인했더니 화재가 아닐경우 SPI 흡연실(마스터)<-나(슬레이브)
//핀 : 10,11,12,13,GND

#define sv1 7 //I2C 통신 12p-49
#define sv2 8
#define sv3 9
byte i = 0;

unsigned long l1[2];

void siren() {  //siren
  for (int i = 200; i < 800; i++) {
    tone(pinBuzzer, i);
    delay(4);
  }
  delay(1000);
  for (int i = 800; i >= 200; i--) {
    tone(pinBuzzer, i);
    delay(4);
  }
  noTone(pinBuzzer);
}
boolean debounce(boolean last) {  //푸쉬버튼 동작
  boolean current = digitalRead(pinButton);
  if (current != last) {
    delay(5);
    current = digitalRead(pinButton);
  } return current;
}
void I2C_Fire(int sv) {
  Wire.beginTransmission(sv);
  Wire.write('F');
  Wire.write('\n');
  Wire.endTransmission();
}
void I2C_Safe(int sv) {
  Wire.beginTransmission(sv);
  Wire.write('S');
  Wire.write('\n');
  Wire.endTransmission();
}
// 경비원이 화재실 가서 확인 후 시리얼 창에 신호로 입력하면 화재!!!
// 원래는 가스센서로 쓸 거를 없어서 직접 입력으로 대체
byte Usign;
byte mysign;

///LCD는 아날로그 핀 상관 없음
//부저는 PWM (~디지털)핀만 사용

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); //UART 휴지통->나
  Wire.begin(); //I2C 나->모두

  SPCR |= _BV(SPE);  //SPI
  SPCR |= _BV(SPIE);
  SPCR &= ~_BV(MSTR);

  noTone(pinBuzzer);

  for (int i = 0; i < 3; i++) {
    pinMode(pinLED[i], OUTPUT);
  }

  Serial.write("=== Hello, Master!! Start!! ===\n");
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinButton, INPUT);
}

void loop() {
  if (mySerial.available()) { //UART 통신 11-p43
    Usign = mySerial.read();
    Serial.write(Usign);  //FULL이면... 조건짜기
    if (Usign == 'F') { //초록색 추가
      Serial.write("\t\tProblem Occurred!! > Trash can!\n");
      Serial.write("\t\t>> Call Cleaner\n");
      digitalWrite(pinLED[1], 40);
    } else if (Usign == 'E') { //휴지통 해결
      Serial.write("\t\tProblem Solved!! > Trash can!\n");
      Serial.write("\t\tCleaned!!\n");
      digitalWrite(pinLED[1], 0);
    }
  }

  if (Serial.available()) { //아두이노 - 내컴퓨터 통신
    mysign = Serial.read(); //s = safe / f = fire / c = call cleaner
    if (mysign == 's') {  //safe
      Serial.write("\t>> Safe!!\n");
      stateFire = false;
      I2C_Safe(sv1);
      I2C_Safe(sv2);
      I2C_Safe(sv3);
    } else if (mysign == 'f') { //fire
      stateFire = true;
    } else if(mysign =='c'){ //checked safe 흡연실
      Serial.write("\t>> Checked SmokingRoom!!\n");
      I2C_Safe(sv1);
      digitalWrite(pinLED[2], 0);
    }
  }
  //SPI 12-p46 -밑에
  //I2C 통신 12p-49 -여러곳에 함수로I2C

  currentButton = debounce(lastButton);          //버튼 디바운스
  if (currentButton == HIGH && lastButton == LOW)   //버튼이 눌리면 fire!!
    stateFire = ! stateFire;
  lastButton = currentButton;

  if (stateFire == true) {
    Serial.write("\t>> Fire!!\n");
    digitalWrite(pinLED[0], 40);
    I2C_Fire(sv1);
    I2C_Fire(sv2);
    I2C_Fire(sv3);
    siren();
  } else {
    digitalWrite(pinLED[0], 0);
  }
}

ISR(SPI_STC_vect) {     //흡연실에서 신호받아옴
  byte c = SPDR;
  Serial.println(c);  //확인용
  if (c == 'C') {     //check request
    digitalWrite(pinLED[2],40);
    Serial.write("\tCheck Request!! > Smoking room!!\n");
  }
}
