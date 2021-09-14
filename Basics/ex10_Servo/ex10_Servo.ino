#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성
int value = 0;    // 각도를 조절할 변수 value

void setup() {
  servo.attach(7);     //맴버함수인 attach : 핀 설정
  Serial.begin(9600); //시리얼 모니터 사용 고고
}

void loop() {
  if(Serial.available())      //시리얼 모니터에 데이터가 입력되면
  {
    char in_data;             // 입력된 데이터를 담을 변수 in_data
    in_data = Serial.read(); //시리얼모니터로 입력된 데이터 in_data로 저장
    if(in_data == '1')        //입력된 데이터가 1이라면
    {
      value += 30;            //각도를 30도 증가시킨다.
      if(value == 210)        //각도가 210도가 되면 (180도보다 커지면)
        value = 0;            //각도를 0으로 초기화
    }
    else                      //그외의 데이터가 입력되면
      value = 0;              //각도를 0으로 초기화
      
    servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
  }
}
