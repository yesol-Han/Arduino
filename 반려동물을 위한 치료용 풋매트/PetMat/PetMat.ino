bool spread = false; //약을 분사하는 상황, true=분사
bool medi = true; //약이 있는지 체크
bool btn = false;
bool before_spread = false;
long time_basic, time_spread_check, time_medicine_check, time_eat_check, time_button, time_try_hum;
int change_time = 1000;

void setup() {
  Serial.begin(115200); // Serial monitor 구동 전원입력

  //센서 초기화
  sensor_setup();

  //서버 초기화
  server_setup();

  Serial.println("start");
}

void loop() {
  time_basic = millis();

  if (time_basic - time_medicine_check >= 5000) {  // 5초마다 약 잔존데이터 불러옴
    //medi = get_cin("medi1"); //약이 남아 있으면,
    medi = water();
    time_medicine_check = time_basic;

    Serial.println("here 1 ");
  }

  if (time_basic - time_spread_check >= 5000) { //5초에 한번 spread 신호 확인하기
    spread = get_cin("spread");
    Serial.println((String)"Spread: " + spread);

    if (spread != before_spread) { //밥먹은 시간
      time_eat_check = time_basic;
    }
    time_spread_check = millis(); //받고나서 5초 time_spread_check = time_basic;

    Serial.println("here 2 ");
  }

  if (time_basic - time_button >= change_time) { //버튼 체크 1초마다
    btn = button();
    time_button = time_basic;
    if (btn) {
      Serial.println("Button is pushed");
      change_time = 30000;  //먹기 시작하면 30초 무시하기
    } else {
      change_time = 1000;
    }

    Serial.println("here 3 ");
  }

  if (time_basic - time_try_hum >= 1000) {

    if (spread || btn) { //밥 먹을 시간이 되었을 때 + 밥을 먹으면

      if (medi) { //약이 남아 있다는 전제 하에
        if (water() <= 800) { //약 잔량 확인
          medi = false;
          post_cin("medi1", 0);  //강제 종료
        } else {
          humid();  // 가습기 틀기
        }
      } else { //약 충전되는지 체크
        if (water() >= 800) { //약 잔량 확인
          LED(LOW, LOW);
          medi = true;
          post_cin("medi1", 1);  //밥 먹고있음
        }
      }

      if (btn) { //버튼 -> 반려동물이 왔었으면,
        post_cin("spread", 0);
        before_spread = false;
      }

    }
    time_try_hum = time_basic;
    Serial.println("here 4 eat check");
  }

  if (time_basic - time_eat_check >= 60000) { //밥 안먹고 1시간 지나면,
    post_cin("spread", 2);

    Serial.println("here 5 eat delay check");
  }

  delay(100);
}

/*
  /spread
  1. get에 신호 있으면, 강아지 오면(button), 또는 신호 있었는데 10분이 지나도 강아지 안오면 가습기 발사(post)

  /medicine
  2. 약 없으면 post

*/
