// 화재 - (슬레이브) SPI로 통신 / ‘A’라는 신호를 마스터에게 받으면 감지한 방에서 부저,LED 작동

#include <SPI.h>

const int ledPins[4] = {2, 3, 4, 5};   // LED 핀 배열
const int buzzerPin = 7;                // 부저 핀
const int ssPin = 10;                    // 슬레이브 선택 핀

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  pinMode(ssPin, INPUT);  // 슬레이브에서는 SS 핀을 입력으로 설정
}

void loop() {
  char receivedData;

  if (digitalRead(ssPin) == LOW) {
    receivedData = SPI.transfer(' ');  // 마스터로부터 데이터 수신
    delay(5);  // 딜레이를 추가하여 감지 간격을 조절할 수 있습니다.

    if (receivedData == 'A') {
      Serial.println("Alarm Triggered!");

      for (int i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], HIGH);  // 감지된 센서에 해당하는 LED를 켜기
      }
      tone(buzzerPin, 1000);  // 부저 울리기
      delay(5000);  // 5초 동안 유지
      for (int i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], LOW);  // 모든 LED를 끄기
      }
      noTone(buzzerPin);  // 부저 멈추기
    }
  }
}
