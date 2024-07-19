#ifndef EV3_COMPASS_H
#define EV3_COMPASS_H

class CompassSensor
{
public:
  // コンストラクタ  アドレスはたぶん0x01 0x21もある？
  CompassSensor(int addr = 0x01);
  // デストラクタ
  ~CompassSensor() = default;

  // 角度を取得する関数
  int getAngle();

  bool calibrate();

private:
  // コンパスのI2Cアドレス
  int address;
};

#endif // EV3_COMPASS_H
