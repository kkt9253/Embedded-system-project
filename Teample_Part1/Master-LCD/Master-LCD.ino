// LCD 코드 - 마스터
// 길안내 - UART로 통신 / ‘8버튼으로 호수 선택 시 길안내 led 발광, UART 통신

#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
LiquidCrystal lcd(6, 7, A3, A2, A1, A0);
const int k1 = 8;
const int k2 = 9;
const int k3 = 10;
const int k5 = 11;
const int k6 = 12;
const int k7 = 13;
byte room = 0; //401은 1 402는 2 403은 3 404는 4
byte state = 0;

void setup() {
  pinMode(k1, INPUT);
  pinMode(k2, INPUT);
  pinMode(k3, INPUT);
  pinMode(k5, INPUT);
  pinMode(k6, INPUT);
  pinMode(k7, INPUT);
  
  lcd.begin(16, 2);
  lcd.print("Hello, IoT");
  lcd.setCursor(0, 1);
  lcd.print("May I help you?");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.print("Choose the room");
  
  Serial.begin(9600);
  mySerial.begin(9600);
}


void loop() {
  switch (state) { //버튼 코드
    case 0: {
      if (digitalRead(k2) == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Are you sure");
        lcd.setCursor(0, 1);
        lcd.print("401?");
        state++;
        delay(1000);
        room = 1;
      }
      else if(digitalRead(k6) == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Are you sure");
        lcd.setCursor(0, 1);
        lcd.print("402?");
        state++;
        delay(1000);
        room = 2;
      }
      else if(digitalRead(k1) == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Are you sure");
        lcd.setCursor(0, 1);
        lcd.print("403?");
        state++;
        delay(1000);
        room = 3;
      }
      else if(digitalRead(k5) == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Are you sure");
        lcd.setCursor(0, 1);
        lcd.print("404?");
        state++;
        delay(1000);
        room = 4;
      }
      break;
    }

    case 1: {
      if (digitalRead(k3) == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Follow the RED");
        state++;
        mySerial.println(room);
        room = 0;
        delay(1000);
      }
      break;
    }

    case 2: {
      delay(1000);
      state = 0;
      lcd.clear();
      lcd.print("choose the room");
      delay(500);
      break;
    }
  }
}
