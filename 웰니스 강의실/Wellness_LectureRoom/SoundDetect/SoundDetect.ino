const int sampleWindow = 30; //샘플링 시간 ms
unsigned int sample;
const int LED = 3;

void setup() {
  pinMode(A0, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long startMillis = millis(); // 생플링 시작
  unsigned int peakToPeak = 0;   // 음성신호의 진폭

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // 생플링 구간동안 최댓값과 최소값을 읽어들입니다.
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(A0);
    if (sample < 1024) { // toss out spurious readings
      if (sample > signalMax) {
        signalMax = sample;  // save just the max levels
      } else if (sample < signalMin) {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // 최대값에서 최소값을 빼서 진폭을 계산
  //double volts = (peakToPeak * 5.0) / 1024;  // 이를 전압단위로 변경합니다.
  if (peakToPeak > 30)  {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
  Serial.println(peakToPeak);
}
