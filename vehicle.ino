#include <ESPAsyncWebServer.h>

const char* ssid = "имя_сети";
const char* password = "пароль_сети";

#include "page.h"
#include "js.h"
#include "socket.h"
#include "cameraServer.h"

// Создание объекта сервера
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Подключение к Wi-Fi

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");


  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", htmlPage);
  });

  server.on("/js.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", js);
  });


  // Настройка сервера
 // server.begin();

 // webSocket.begin();
 // webSocket.onEvent(onWebSocketEvent);
  setupPin();
  cameraSetup();
}

void loop() {
 // webSocket.loop();
}
