#include <WebSocketsServer.h>

// Определение пинов подключения L9110S к ESP32
const int motorPin1 = 12; // Пин для подключения к IN1 L9110S
const int motorPin2 = 13; // Пин для подключения к IN2 L9110S

// Определение пинов подключения L9110S к ESP32
const int motorPin3 = 14; // Пин для подключения к IN1 L9110S
const int motorPin4 = 15; // Пин для подключения к IN2 L9110S


void stopMotors() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);

  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

}

void setupPin() {
  // Установка пинов в режим вывода
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  stopMotors();
}





WebSocketsServer webSocket = WebSocketsServer(81);
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  int values[4] = {0, 0, 0, 0}; // Инициализация массива

  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      stopMotors();
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      stopMotors();
      break;
    case WStype_TEXT:
      Serial.printf("[%u] Received text: %s\n", num, payload);

      // Преобразование текста в массив четырех чисел
      {
        int count = sscanf((const char*)payload, "%d,%d,%d,%d", &values[0], &values[1], &values[2], &values[3]);

        // Проверка, что было успешно прочитано 4 значения
        if (count == 4) {
          // Обработка значений
          Serial.printf("Received values: %d, %d, %d, %d\n", values[0], values[1], values[2], values[3]);

          digitalWrite(motorPin1, values[0]);
          analogWrite(motorPin2, values[1]);

          digitalWrite(motorPin3, values[2]);
          analogWrite(motorPin4, values[3]);

        } else {
          Serial.println("Invalid format. Expected 4 comma-separated values.");
          stopMotors();
        }
      }
      break;
    default:
      break;
  }
}

