void setup() {
  pinMode(7, INPUT_PULLUP);             // 디지털 3번핀을 입력모드로 설정
  Serial.begin(9600);              // 시리얼 통신을 시작하며, 속도는 9600으로 설정
}
 
void loop() {
  int a = digitalRead(8);          // 변수 a를 선언하여 디지털 3번핀의 값을 입력
  Serial.println(a);                   // 변수 a를 시리얼 모니터에 출력
  delay(3000);                        // 1초 대기
  Serial.println(a);                   // 변수 a를 시리얼 모니터에 출력
}
