#include <Wire.h>
#include <LiquidCrystal_I2C.h> //LCD
#include <dht11.h>    //온습도

//MQ135
const int gasPin = A0;
int gasval = 0;

//DHT11
const int pinDHT11 = 2;
dht11 DHT11;
int ret;

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
//LCD 기호
byte degree[8] = {B00110, B01001, B01001, B00110, B00000, B00000, B00000, B00000,};
byte degree2[8] = {B00000, B00000, B00000, B00000, B01100, B10010, B10010, B01100,};
byte fan_on[8] = {B00100, B10101, B01110, B11111, B01110, B10101, B00100, B00000,};
byte fan_off[8] = {B00100, B00100, B00100, B11111, B00100, B00100, B00100, B00000,};

void setup() {
  Serial.begin(9600);
  lcdinit();  // LCD setting
}

//온,습도 -> LCD / CO2 -> LCD 끝에 환풍 권장 표시
void loop() {
  ret = DHT11.read(pinDHT11);
  switch (ret) {
    case DHTLIB_OK: Serial.println("OK");
      break;
    case DHTLIB_ERROR_CHECKSUM: Serial.println("Checksum error");
      break;
    case DHTLIB_ERROR_TIMEOUT: Serial.println("Time out error");
      break;
    default: Serial.println("Unknown error");
      break;
  }// Dht11가 빠른 속도로 많은 데이터를 전송하기 때문에 디지털 입력 핀에서 값을 잘 수신했는지 점검하는 작업
  
  Serial.println(gasval);
  gasval = analogRead(gasPin);
  Serial.print("Temperature (oC): "); Serial.println((float)DHT11.temperature, 1);
  Serial.print("Humidity (%): "); Serial.println((float)DHT11.humidity, 1);
  Serial.println();
  
  lcd.setCursor(6, 0); lcd.print((float)DHT11.temperature, 1);
  lcd.setCursor(6, 1); lcd.print((float)DHT11.humidity, 1);

  if (30 >= gasval) {
    lcd.setCursor(15, 1); lcd.write((byte)2);
  } else {
    lcd.setCursor(15, 1); lcd.write((byte)3);
  }

  delay(2000);  //Dht11의 데이터 측정 주기가 2초임을 고려하여 대기
}

void lcdinit() {
  lcd.init();  lcd.backlight();  lcd.begin(16, 2);
  lcd.createChar(0, degree);  lcd.createChar(1, degree2);  lcd.createChar(2, fan_off);  lcd.createChar(3, fan_on);
  lcd.setCursor(0, 0); lcd.print("TEMP:");
  lcd.setCursor(10, 0); lcd.write((byte)0);
  lcd.setCursor(11, 0); lcd.print("C");
  lcd.setCursor(0, 1); lcd.print("HUMI:");
  lcd.setCursor(10, 1); lcd.write((byte)0);
  lcd.setCursor(11, 1); lcd.print("/");
  lcd.setCursor(12, 1); lcd.write((byte)1);
}

