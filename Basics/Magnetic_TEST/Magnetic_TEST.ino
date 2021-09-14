const int MaganetPin=4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MaganetPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(MaganetPin);
  Serial.println(a);
  delay(100);
}
