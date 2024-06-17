// LED 코드 - 슬레이브
// 길안내 - UART로 통신 / ‘8버튼으로 호수 선택 시 길안내 led 발광, UART 통신

#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
int c;
const int red_1 = 4;
const int green_1 = 5;
const int red_2 = 6;
const int green_2 = 7;
const int red_3 = 8;
const int green_3 = 9;
const int red_4 = 10;
const int green_4 = 11;
const int red_5 = 12;
const int green_5 = 13;
const int red_6 = A0;
const int green_6 = A1;

void setup() {
  // put your setup code here, to run once:

  pinMode(red_1, OUTPUT);
  pinMode(green_1, OUTPUT);
  pinMode(red_2, OUTPUT);
  pinMode(green_2, OUTPUT);
  pinMode(red_3, OUTPUT);
  pinMode(green_3, OUTPUT);
  pinMode(red_4, OUTPUT);
  pinMode(green_4, OUTPUT);
  pinMode(red_5, OUTPUT);
  pinMode(green_5, OUTPUT);
  pinMode(red_6, OUTPUT);
  pinMode(green_6, OUTPUT);

  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(mySerial.available()) {
    c = mySerial.read();
    if(c == 1) {
      digitalWrite(red_5, HIGH);
      delay(8000);
      digitalWrite(red_5, LOW);
      digitalWrite(red_1, HIGH);
      delay(3000);
      digitalWrite(red_1, LOW);
    }
    if(c == 2) {
      digitalWrite(red_4, HIGH);
      delay(5000);
      digitalWrite(red_4, LOW);
    }
    if(c == 3) {
      digitalWrite(red_5, HIGH);
      delay(8000);
      digitalWrite(red_5, LOW);
      digitalWrite(red_3, HIGH);
      delay(3000);
      digitalWrite(red_3, LOW);
    }
    if(c == 4) {
      digitalWrite(red_2, HIGH);
      delay(7000);
      digitalWrite(red_2, LOW);
    }
    Serial.println(c);
  }
  
}
