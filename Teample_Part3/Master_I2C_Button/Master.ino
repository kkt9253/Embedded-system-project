// 마스터 (버튼 입력 감지 및 I2C 전송)
// 버튼 입력을 감지하고, 해당 버튼 번호를 슬레이브 아두이노로 전송
// LCD에 버튼이 눌린 이후 출력됨은 "사람이 갇혀있음"을 소방관에게 통신했음을 의미함

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int pinButton1 = 2; // 디지털 핀
const int pinButton2 = 3;
const int pinButton3 = 4;
const int pinButton4 = 5;

boolean lastButton1 = LOW;
boolean lastButton2 = LOW;
boolean lastButton3 = LOW;
boolean lastButton4 = LOW;
boolean currentButton1 = LOW;
boolean currentButton2 = LOW;
boolean currentButton3 = LOW;
boolean currentButton4 = LOW;
const int slaveAddress = 8; // 슬레이브 장치의 I2C 주소

void setup() {
  pinMode(pinButton1, INPUT);
  pinMode(pinButton2, INPUT);
  pinMode(pinButton3, INPUT);
  pinMode(pinButton4, INPUT);
  Serial.begin(9600);

  Wire.begin(); // I2C 통신 초기화
}

boolean debounce(int pinButton, boolean last) {
  boolean current = digitalRead(pinButton);
  if (current != last) {
    delay(5);
    current = digitalRead(pinButton);
  }
  return current;
}

void sendButtonPress(String buttonNumber) {
  Wire.beginTransmission(slaveAddress);

  // 바이트 배열의 각 원소를 I2C로 전송
    Wire.write(buttonNumber[0]);
    Serial.println(buttonNumber[0]);

    Wire.requestFrom(slaveAddress, 1);
    while (Wire.available()) {
      Serial.println("data-kim :");
      byte m = Wire.read();
      Serial.println(m);
      
  // 전송 종료
  
  if (m == 8) {
  int transmissionResult = Wire.endTransmission();
  }
    }
//  Serial.println("hello2");
//  // 전송 결과 확인
//  if (transmissionResult == 0) {
//    Serial.println("Transmission successful");
//  } else if (transmissionResult == 1) {
//    Serial.println("Transmission failed-1");
//  } else if (transmissionResult == 2) {
//    Serial.println("Transmission failed-2");
//  } else if (transmissionResult == 3) {
//    Serial.println("Transmission failed-3");
//  } else if (transmissionResult == 4) {
//    Serial.println("Transmission failed-4");
//  }
}


void loop() {
  
  
  currentButton1 = debounce(pinButton1, lastButton1);
  currentButton2 = debounce(pinButton2, lastButton2);
  currentButton3 = debounce(pinButton3, lastButton3);
  currentButton4 = debounce(pinButton4, lastButton4);

  if (currentButton1 == HIGH && lastButton1 == LOW) {
    sendButtonPress("4019"); // 버튼 1 눌림
    lastButton1 = currentButton1;
  }
  if (currentButton2 == HIGH && lastButton2 == LOW) {
    sendButtonPress("4029"); // 버튼 2 눌림
    lastButton2 = currentButton2;
  }
  if (currentButton3 == HIGH && lastButton3 == LOW) {
    sendButtonPress("4039"); // 버튼 3 눌림
    lastButton3 = currentButton3;
  }
  if (currentButton4 == HIGH && lastButton4 == LOW) {
    sendButtonPress("4049"); // 버튼 4 눌림
    lastButton4 = currentButton4;
  }
}
