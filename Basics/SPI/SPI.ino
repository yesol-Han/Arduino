char buf[100];
volatile boolean done = false;
const int led = 9;

void setup() {
  Serial.begin(9600);
  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE);
  SPCR &= ~_BV(MSTR);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
delay(100);
}

ISR(SPI_STC_vect) {
  byte c = SPDR;
  Serial.println(c);
  if(c>24){
    digitalWrite(led,HIGH);
    delay(1000);
  }else{
    digitalWrite(led,LOW);
    delay(1000);
  }
}
