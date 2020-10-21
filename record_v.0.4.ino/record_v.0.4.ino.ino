/*
   v.4ではボタンが押されたら時間を打刻


*/
#include <EEPROM.h>

unsigned long tm;
int a = 0;
int b = 0;
const int DIN_PIN = 5;

void setup() {
  pinMode(13, OUTPUT);
  pinMode( DIN_PIN, INPUT_PULLUP );
  Serial.begin(9600);
  int i[10];
  int a = 0;
}

void loop() {
  int i[10];
  int value;
  int b[10];
  int wait = 0;
  int set_time;

  value = digitalRead( DIN_PIN );

  //Serial.println("start");
  if (value == 0 && a == 0) {
    tm = millis() / 100;
    i[a] = tm;
    b[a] = tm;
    //Serial.println(i[a]);
    a = a + 1;
    delay( 300 );
  }

  if (value == 0 && a < 10) {
    tm = millis() / 100;
    i[a] = tm;
    b[a] = i[a] - i[a - 1];
    EEPROM.write (a, b[a]); //EEPROM記録
    Serial.println(i[a] - i[a - 1]); //b[a]でもOK
    a = a + 1;
    delay( 300 );
  }

  if (value == 0 && a == 10) {
    tm = millis() / 100;
    i[a] = tm;
    b[a] = i[a] - i[a - 1];
    Serial.println(i[a] - i[a - 1]);
    Serial.println("finish! Mode_Change");
    delay(2500);

    //配列の真ん中の安定して取得できている値の間隔を取得する

    for (a = 3; a <= 9 ; a++) {
      Serial.print("EEPROM_Data=");
      Serial.println(EEPROM[a]);
      delay(250);
    }

    Serial.println("Check TEST mode");
    while (1) {
      for (a = 3; a <= 8 ; a++) {
        digitalWrite(12, HIGH);
        delay(100);
        digitalWrite(12, LOW);
        delay(EEPROM[a] * 100 - 100);
      }
      //delay(650);  //ここはwait用の時間を算出して割当がよい。一旦は650msで設定
    }
  }

  if (  (millis() / 1000) > 30) {
    Serial.println("Auto Puls-Mode begin");
    for (a = 3; a <= 9 ; a++) {
      Serial.println(EEPROM[a]);
      delay(250);
    }

    while (1) {
      for (a = 3; a <= 8 ; a++) {
        digitalWrite(12, HIGH);
        delay(100);
        digitalWrite(12, LOW);
        delay(EEPROM[a] * 100 - 100);
      }
      //delay(650);  //ここはwait用の時間を算出して割当がよい。一旦は650msで設定
    }
  }
}
