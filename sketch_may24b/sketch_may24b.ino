#include <leeminkyu1212-project-1_inferencing.h>

#include <leeminkyu1212-project-1_inferencing.h>

#include <ArduinoBLE.h>
// #include <your_edge_impulse_library.h> // 다운로드한 라이브러리를 포함시킵니다.

// 웹 서버 설정
const char* serverURL = "http://your-web-server.com/path/to/upload"; // 웹 서버 주소
const int serverPort = 80; // 웹 서버 포트

BLEService gestureService("180A");
BLEByteCharacteristic gestureCharacteristic("2A56", BLERead | BLENotify);
BLEDevice central;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  if (!BLE.begin()) {
    Serial.println("BLE initialization failed!");
    while (1);
  }
  BLE.setLocalName("GestureSensor");
  BLE.setAdvertisedService(gestureService);
  gestureService.addCharacteristic(gestureCharacteristic);
  BLE.addService(gestureService);
  gestureCharacteristic.setValue(0);
  BLE.advertise();
}

void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    while (central.connected()) {
      int result = readGesture(); // 동작 감지
      if (result >= 0) {
        sendGestureResult(result); // 웹 서버로 동작 결과 전송
      }
    }
    central.disconnect();
  }
}

int readGesture() {
  // 여기에 동작 감지 코드를 작성합니다.
  // Edge Impulse 라이브러리를 사용하여 동작을 감지하고 결과를 반환합니다.
}

void sendGestureResult(int result) {
  DynamicJsonDocument jsonDocument(256);
  jsonDocument["gesture"] = result;

  String jsonStr;
  serializeJson(jsonDocument, jsonStr);

  Serial.print("Sending JSON: ");
  Serial.println(jsonStr);

  WiFiClient client;
  if (client.connect(serverURL, serverPort)) {
    client.println("POST /path/to/upload HTTP/1.1");
    client.println("Host: your-web-server.com");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(jsonStr.length());
    client.println();
    client.println(jsonStr);
  }
  client.stop();
}
