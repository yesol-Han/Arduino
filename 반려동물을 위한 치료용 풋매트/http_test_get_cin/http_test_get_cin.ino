// get cin 성공

#include <ESP8266WiFi.h>

const char* ssid     = "Yesol"; // 접속할 와이파이 이름 한글은 안돼요
const char* password = "51839428"; // 접속할 와이파이 비밀번호

const char* host = "203.253.128.161";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // 와이파이에 연결하는 함수 입니다.

  // 와이파이에 연결이 될 때 까지 대기
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());// 아이피 주소를 출력합니다.
}

void loop() {
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 7579;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/Mobius/PetMat/user1/la";   // 접속할 사이트 경로 "/"는 최상위 경로이며 "/하위/하위2/하위3/대상파일" 과 같은 구조를 가집니다.
  Serial.print("Requesting URL: ");
  Serial.println(url);

  Serial.println();
//  Serial.println(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + ":7579" + "\r\n" +
//               "Content-Type: application/json" + "\r\n" +
//               "X-M2M-RI: 12345" + "\r\n" +
//               "X-M2M-Origin: AA" + "\r\n" +
//               "Connection: close\r\n\r\n");
//  Serial.println();
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + ":" + httpPort + "\r\n" +
               "Content-Type: application/json" + "\r\n" +
               "X-M2M-RI: 12345" + "\r\n" +
               "X-M2M-Origin: AA" + "\r\n" +
               "\r\n");
  //HTTP 요청을 보냅니다.

  unsigned long timeout = millis();
  while (client.available() == 0) {//5초동안 응답이 없다면 에러처리 합니다.
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) { //서버로부터 받은 응답을 출력합니다.
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

}
