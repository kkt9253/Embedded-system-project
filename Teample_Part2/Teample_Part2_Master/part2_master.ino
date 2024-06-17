// 화재 - (마스터) SPI로 통신 / 불꽃감지센서와 가스감지 센서가 감지하면 'A' 를 SPI 통신을 통해 슬레이브에게 전송

#include <SPI.h>

const int ssPin = 10;                // 슬레이브 선택 핀
const int flameSensorPins[4] = {A0, A1, A2, A3}; // 불꽃 감지 센서 핀 배열
const int gasSensorPins[4] = {4, 5, 6, 7};    // 가스 감지 센서 핀 배열

const int flameThreshold = 1050;    // 수정된 불꽃 감지 센서 임계값
const int gasThreshold = 1000;      // 수정된 가스 감지 센서 임계값

void setup() {
  Serial.begin(9600);
  SPI.begin();
}

void loop() {
  char sensorSignal = 'N'; // 초기 값으로 정상 상태 설정
    
  for (int i = 0; i < 4; i++) {
    // 가스 센서 값 안정화를 위한 추가 코드
    int gasValueStabilized = 0;
    for (int j = 0; j < 5; j++) {
      gasValueStabilized += analogRead(gasSensorPins[i]);
      delay(50);  // 50ms 대기
    }
    int gasValue = gasValueStabilized / 5;

    Serial.print("Flame Sensor ");
    Serial.print(i + 1);
    Serial.print(" Value: ");
    Serial.println(analogRead(flameSensorPins[i]));

    Serial.print("Gas Sensor ");
    Serial.print(i + 1);
    Serial.print(" Value: ");
    Serial.println(gasValue);

    if (analogRead(flameSensorPins[i]) > flameThreshold || gasValue > gasThreshold) {
      sensorSignal = 'A';  // 가스 또는 불꽃 감지 센서 감지 시
      break;  // 한 번이라도 감지되면 나머지 센서는 확인하지 않음
    }


    if (analogRead(flameSensorPins[i]) < 500) {
      sensorSignal = 'A';  // 불꽃이 700 미만 또는 가스가 600 미만일 때도 감지로 처리
      break;
    }

    
  }

  Serial.print("Sending Signal: ");
  Serial.println(sensorSignal);

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(ssPin, LOW);
  SPI.transfer(sensorSignal);
  digitalWrite(ssPin, HIGH);
  SPI.endTransaction();

  delay(500);  // 딜레이를 추가하여 감지 간격을 조절할 수 있습니다.
}  
