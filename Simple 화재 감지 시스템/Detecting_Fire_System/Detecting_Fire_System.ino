#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

const int gasPin = A0 ;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int a;

void setup()
{
  lcd.init(); 
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
}

void loop()
{
a = analogRead(gasPin);
Serial.println(a);
lcd.backlight();

 // green
 if(60 >= a){
  setColor(0, 100, 0);
  Serial.println("green");
  lcd.init();
  lcd.setCursor(6, 0);
  lcd.print("s"); lcd.print("a"); lcd.print("f"); lcd.print("e");
  lcd.blink(); 
  }
  // yellow
  else if(80 >=a && a > 60){
  setColor(100, 100, 0);
  Serial.println("yellow");
  lcd.init();
  lcd.setCursor(6, 0);
  lcd.print("w"); lcd.print("a"); lcd.print("r"); lcd.print("n");
  lcd.blink(); 
  }
  // red
  else if(a > 80){
  setColor(100, 0, 0);
  Serial.println("red");
  lcd.init(); 
  lcd.setCursor(5, 1);
  lcd.print("f"); lcd.print("i"); lcd.print("r"); lcd.print("e"); lcd.print("!"); lcd.print("!");
  lcd.blink(); 
  }
 delay(1000);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
