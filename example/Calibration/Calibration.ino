#include <EV3_Compass.h>

// コンパス
EV3_Compass compass;

void setup() {
  // コンパスのキャリブレーション
  compass.calibrate();
}

void loop() {
}
