#include <dht11.h>
#include <SPI.h>
#include <Wire.h>

boolean stateFire = false;
char s; //SPI

#define sv 7 //I2C
byte i = 0;

unsigned long l1[2], l2[2]; //각각 다른 시간 측정을 위해

const int pinLED[3] = {4, 5, 7};  //위에 전등

const int pinLM35  = A0;  // LM35 -> 온도 측정
float val_temp = 0;

const int pinDHT11 = 6;    //DHT11 -> 습도측정
int ret;
dht11 DHT11;

const int pinLight1 = A1;    //DFR0026 ->주변광 측정1
int val_light1 = 0;
const int pinLight2 = A2;   //PT550 ->주변광 측정2
int val_light2 = 0;

const int MC1 = 3;    // moter
const int MC2 = 2;
const int EN = 9;

void forward() {  //모터 동작1
  digitalWrite(EN, LOW);  digitalWrite(MC1, LOW);  digitalWrite(MC2, HIGH);  analogWrite(EN, 400);
}
void reverse() {  //모터 동작2
  digitalWrite(EN, LOW);  digitalWrite(MC1, HIGH);  digitalWrite(MC2, LOW);  analogWrite(EN, 400);
}
void brake() {  //모터 동작3
  digitalWrite(EN, LOW);  digitalWrite(MC1, LOW);  digitalWrite(MC2, LOW);  analogWrite(EN, HIGH);
}

//1차: LM35 온도 떨어지고, DHT11 습도 떨어지고, DFR0026 연기로 주변이 어두워지면
//  -> 관리실로 신호 보냄
//2차: 관리실에서  1. 일반인이 신고하면 버튼 누르라고 요청 2. 관리자가 가서 확인하고 버튼을 누르면(관리실)
//  -> 모든 장소로 화재 상황 보내고, 모터를 반대로 돌림
//마지막에 체크 해야 할것!!! -> 최소대기시간이 필요한 센서가 있는지.

void setup() {
  Serial.begin(9600);
  SPI.begin(); pinMode(SS, OUTPUT); digitalWrite(SS, HIGH); SPI.setClockDivider(SPI_CLOCK_DIV16); //SPI

  Wire.begin(sv);
  Wire.onReceive(receiveEvent);

  for (int i = 0; i < 3; i++) {
    pinMode(pinLED[i], OUTPUT);
    digitalWrite(pinLED[i], HIGH);
  }

  pinMode(EN, OUTPUT);  //모터 초기화
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  forward();
}
float val_temp_re;
void loop() {
  if (stateFire == false) {

    l1[1] = millis();
    if (l1[1] - l1[0] >= 1000) {                      //온도 측정 LM35
      l1[0] = l1[1];

      val_temp = analogRead(pinLM35);
      Serial.print(" val_temp : ");
      val_temp_re = val_temp * 5 * 100 / 1024.0;
      Serial.println(val_temp * 5 * 100 / 1024.0);

      ret = DHT11.read(pinDHT11);                    //습도 측정 DHT11
      switch (ret) {
        case DHTLIB_OK: Serial.println("OK"); break;
        case DHTLIB_ERROR_CHECKSUM: Serial.println("Checksum error"); break;
        case DHTLIB_ERROR_TIMEOUT: Serial.println("Time out error"); break;
        default: Serial.println("Unknown error"); break;
      }
      Serial.print(" Humidity (%): ");
      Serial.println((float)DHT11.humidity, 1);

      val_light1 = analogRead(pinLight1);                    //주변광 측정 DFR0026
      val_light2 = analogRead(pinLight2);                    //주변광 측정 PT550

      Serial.print(" val_light1 - val_light2 : ");
      Serial.println(val_light1 - val_light2);
      Serial.println();
    }

    // 화재상황으로 추측되면 check 요청
    l2[1] = millis();
    if (val_temp_re >= 30.0 && (float)DHT11.humidity <= 22.0 && val_light1 - val_light2>= 500) {
      if (l2[1] - l2[0] >= 1000) {
        l2[0] = l2[1];
        digitalWrite(SS, LOW);
        SPI.transfer('C');
        digitalWrite(SS, HIGH);
      }
    }

  }
}

void receiveEvent(int howMany) {
  char c1 = Wire.read();
  char c2 = Wire.read();
  if (c1 == 'F') {
    Serial.write(c1);Serial.write(c2);
    stateFire = true;
    brake(); delay(100);
    reverse();
  } else {
    Serial.write(c1);Serial.write(c2);
    stateFire = false;
    brake();
    delay(100);
    forward();
  }
}
