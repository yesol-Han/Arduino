const int button_pin = D4; //버튼

const int hum_pin = D5; //가습기 모듈

const int led_G = D6; //LED
const int led_R = D7; //LED

long duration, distance;
const int water_pin = A0; //수분수위센서 A0에 연결

long hum_time1, hum_time2;
int water_val = 0;

void sensor_setup() {
  pinMode(hum_pin, OUTPUT); //수위센서 출력
  pinMode(water_pin, INPUT); // 가습기 모듈 입력으로 설정
  pinMode(button_pin, INPUT_PULLUP); // 버튼을 입력으로 설정

  pinMode(led_G, OUTPUT); //초록색
  pinMode(led_R, OUTPUT); //빨간색 출력

  digitalWrite(led_G, LOW);
  digitalWrite(led_R, LOW);
  digitalWrite(hum_pin, LOW);
}

void timer() {
  hum_time1 = millis();
}

bool button() {
  return digitalRead(button_pin);
}

void LED(bool sig1, bool sig2){
  digitalWrite(led_G, sig1);
  digitalWrite(led_R, sig2);
}

int water() {
  water_val = analogRead(water_pin);
  Serial.print("Medicine: ");
  Serial.println(water_val); //가습 센서 값
  if(water_val<=800){
    LED(LOW, HIGH);
  }
  return water_val;
}

void humid() {
  LED(HIGH, LOW);
    digitalWrite(hum_pin, true);
    delay(10000);
    digitalWrite(hum_pin, false);
    post_cin("medi1", 0);  //밥 다먹음
    LED(LOW, LOW);
}
