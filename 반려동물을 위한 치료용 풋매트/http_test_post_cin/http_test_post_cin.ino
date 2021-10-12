// post cin 성공

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

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
  HTTPClient http;

  const int httpPort = 7579;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/Mobius/PetMat/user1";   // 접속할 사이트 경로 "/"는 최상위 경로이며 "/하위/하위2/하위3/대상파일" 과 같은 구조를 가집니다.
  Serial.print("Requesting URL: ");
  Serial.println(url);

  Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, (String)"http://" + host + ":" + httpPort + url); //HTTP
    http.addHeader("Accept", "application/json");
    http.addHeader("X-M2M-RI", "12345");
    http.addHeader("X-M2M-Origin", "AA");
    http.addHeader("Content-Type", "application/vnd.onem2m-res+json; ty=4");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = http.POST((String)"{\n    \"m2m:cin\": {\n        \"con\": \"" + "test3" + "\"\n    }\n}");


    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
//
//  // This will send the request to the server
//  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + ":" + httpPort + "\r\n" +
//
//               "Accept: application/json" + "\r\n" +  //
//               "X-M2M-RI: 12345" + "\r\n" +
//               "X-M2M-Origin: AA" + "\r\n" +
//               "Content-Type: application/vnd.onem2m-res+json; ty=4" + "\r\n\r\n");
//               client.add((String)"{\n    \"m2m:cin\": {\n        \"con\": \"" + "test2" + "\"\n    }\n}" + "\r\n" +
//
//               "\r\n");
  //HTTP 요청을 보냅니다.
//
//  unsigned long timeout = millis();
//  while (client.available() == 0) {//5초동안 응답이 없다면 에러처리 합니다.
//    if (millis() - timeout > 5000) {
//      Serial.println(">>> Client Timeout !");
//      client.stop();
//      return;
//    }
//  }
//
//  // Read all the lines of the reply from server and print them to Serial
//  while (client.available()) { //서버로부터 받은 응답을 출력합니다.
//    String line = client.readStringUntil('\r');
//    Serial.print(line);
//  }

  Serial.println();
  Serial.println("closing connection");
delay(10000);
}
