const int led_RED = 13, led_GREEN = 12, led_YELLOW =8;
unsigned long l1, l2, l3, l4, l5, l6;
unsigned long interval1 = 1000, interval2 = 2000, interval3 = 3000;
int fON1 = 0;
int fON2 = 0;
int fON3 = 0;

void setup() {
  pinMode(led_RED, OUTPUT);
  pinMode(led_GREEN, OUTPUT);
  pinMode(led_YELLOW, OUTPUT);
  l1 = 0;
  l3 = 0;
  l5 = 0;
}
  
void loop() {
  l2 = millis();
  if (l2 - l1 >= interval1) {
    l1 = l2;
    
    if (!fON1) {
      fON1 = HIGH; 
      } else {
        fON1 = LOW;
        }
        digitalWrite(led_RED, fON1);  
  }

  l4 = millis();
  if (l4 - l3 >= interval2) {
    l3 = l4;
     if (!fON2) {
      fON2 = HIGH; 
      } else {
        fON2 = LOW; 
        }
        digitalWrite(led_GREEN, fON2);
    }

  l6 = millis();
  if (l6 - l5 >= interval3) {
    l5 = l6;
     if (!fON3) {
      fON3 = HIGH; 
      } else {
        fON3 = LOW; 
        }
        digitalWrite(led_YELLOW, fON3);  
    }
}
