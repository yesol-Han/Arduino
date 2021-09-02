const int led_RED = 11, led_GREEN = 10, led_YELLOW =9;
int led[4] = { led_RED, led_GREEN, led_YELLOW, led_GREEN };
unsigned long l1, l2;
unsigned long interval = 40;
int fDir1 = 0;
int fDir2 = 0;
int fade = 0;
int i;

void setup() {
  l1 = 0;
}

void loop() {
  l2 = millis();
  
  if (l2 - l1 >= interval) {
    l1 = l2;
    if (!fDir1) {
      fade += 5; 
      if (fade >= 255) {
        fade = 255; fDir1 = 1;
        }
    } else {
      fade -= 5;
      if (fade <= 0){ 
        fade = 0; fDir1 = 0; fDir2 =1;
        }
    }
    analogWrite(led[i], fade); 
    }

    if(fDir2 == 1){
      if(i != 3){
        i++;
      } else {
        i = 0; 
      }
      fDir2 = 0;
    }
    
}
