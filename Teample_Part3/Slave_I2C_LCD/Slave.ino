// 슬레이브 (LCD 제어 및 I2C 수신)
// I2C 통신을 통해 마스터 아두이노로부터 메시지를 수신하고, 수신된 메시지를 LCD에 출력

#include <Wire.h>
#include <LiquidCrystal.h>

// LCD에 대한 핀 설정
const int RS = 12;
const int EN = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

String roomNumber = ""; // 방 번호 저장 변수

void setup() {
  Wire.begin(8);                // 슬레이브 주소 설정
  Wire.onReceive(receiveEvent);  // 수신 이벤트 핸들러 등록

  lcdInitialize();
}

void loop() {
  // 기타 작업 수행 가능
}

void lcdInitialize() {
  lcdCommand(0x33);
  lcdCommand(0x32);
  lcdCommand(0x28);  // 4-bit mode, 2-line, 5x7 font
  lcdCommand(0x0C);  // Display on, cursor off, blink off
  lcdCommand(0x06);  // Increment cursor (shift cursor to right)
  lcdCommand(0x01);  // Clear display screen
  delay(2);
}

void lcdCommand(int command) {
  digitalWrite(RS, LOW);
  lcdWrite(command);
}

void lcdWrite(int data) {
  digitalWrite(EN, HIGH);
  delayMicroseconds(100);
  digitalWrite(D4, (data >> 4) & 0x01);
  digitalWrite(D5, (data >> 5) & 0x01);
  digitalWrite(D6, (data >> 6) & 0x01);
  digitalWrite(D7, (data >> 7) & 0x01);
  digitalWrite(EN, LOW);
  delayMicroseconds(100);
  digitalWrite(EN, HIGH);
  delayMicroseconds(100);
  digitalWrite(D4, data & 0x01);
  digitalWrite(D5, (data >> 1) & 0x01);
  digitalWrite(D6, (data >> 2) & 0x01);
  digitalWrite(D7, (data >> 3) & 0x01);
  digitalWrite(EN, LOW);
  delayMicroseconds(100);
}

void lcdPrint(String message, int row, int col) {
  lcdCommand(0x80 | (row * 0x40 + col));  // Set cursor position
  digitalWrite(RS, HIGH);
  for (int i = 0; i < message.length(); i++) {
    lcdWrite(message[i]);
  }
}

void receiveEvent() {
  while (Wire.available()) {
    char c = Wire.read();   // 문자 하나 읽기
    if (c == '\n') {        // 개행 문자를 만나면 방 번호를 LCD에 출력
      lcd.clear();
      lcdPrint("A person is in", 0, 0);
      lcdPrint(roomNumber, 1, 0);
      roomNumber = "";      // 방 번호 초기화
    } else {
      roomNumber += c;      // 문자를 방 번호에 추가
    }
  }
}
