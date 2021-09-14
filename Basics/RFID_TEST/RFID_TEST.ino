#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9                            // reset핀은 9번으로 설정
#define SS_PIN    10                           // SS핀은 10번으로 설정
                                               // SS핀은 데이터를 주고받는 역할의 핀( SS = Slave Selector )

MFRC522 mfrc(SS_PIN, RST_PIN);                 // MFR522를 이용하기 위해 mfrc객체를 생성해 줍니다.

void setup(){
  Serial.begin(9600);                         // 시리얼 통신, 속도는 9600
  SPI.begin();                                // SPI 초기화
                                              // (SPI : 하나의 마스터와 다수의 SLAVE(종속적인 역활)간의 통신 방식)
  mfrc.PCD_Init();                               
}

void loop(){
  // 카드를 인식하기 위해 대기
    if ( ! mfrc.PICC_IsNewCardPresent()) {
      Serial.print("1");
      delay(500);
        return; // 카드가 인식되지 않으면 return.
    }
 
    // 카드 정보를 시리얼로 표시
    if ( ! mfrc.PICC_ReadCardSerial()) {
      Serial.print("2");
      delay(500);
        return;
    } 
    
  Serial.print("Card UID:");                  // 태그의 ID출력
  
  for (byte i = 0; i < 4; i++) {               // 태그의 ID출력하는 반복문.태그의 ID사이즈(4)까지
    Serial.print(mfrc.uid.uidByte[i]);        // mfrc.uid.uidByte[0] ~ mfrc.uid.uidByte[3]까지 출력
    Serial.print(" ");                        // id 사이의 간격 출력
  }
  Serial.println(); 
}
