#include <EV3_Compass.h>

CompassSensor compass;
// CompassSensor compass(0x21); 読み込めない場合はI2Cアドレスが違う可能性もあります。こちらも試してみてください。

void setup() {
  Serial.begin(9600);
}

void loop() {
  // コンパスの値を読み込んで変数に代入
  int angle = compass.getAngle();

  // シリアルに出力
  Serial.print("方角: ");
  Serial.println(angle);
}