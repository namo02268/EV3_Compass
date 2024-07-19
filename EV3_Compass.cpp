#include "EV3_Compass.h"
#include <Arduino.h>
#include <Wire.h>

CompassSensor::CompassSensor(int addr) : address(addr)
{
  Wire.begin();
}

int CompassSensor::getAngle()
{
  // コンパスとの通信開始
  Wire.beginTransmission(address);
  Wire.write(0x44);
  Wire.endTransmission();
  delay(10);

  // 2バイト分のデータを読み込む
  Wire.requestFrom(address, 2); // 2バイトを要求

  if (Wire.available() < 2)
  {
    return -1; // データが不足している場合のエラーハンドリング
  }

  uint8_t lowByte = Wire.read();
  uint8_t highByte = Wire.read();

  int angle = (highByte << 8) | lowByte; // 2バイトをint型に結合

  return angle;
}

bool CompassSensor::calibrate()
{
  // キャリブレーションモードに変更
  Wire.beginTransmission(address);
  Wire.write(0x41); // Mode control register
  Wire.write(0x43); // Calibration mode
  Wire.endTransmission();

  // キャリブレーションモードに入るのを待つ
  Serial.begin(9600);
  Serial.println("キャリブレーションを開始します");
  delay(100);

  // キャリブレーションの実行（ここでは仮定的に10000ms待つ）
  Serial.println("10秒間かけてコンパスを1~2周まわしてください");
  delay(10000);

  // 測定モードに戻す
  Wire.beginTransmission(address);
  Wire.write(0x41); // Mode control register
  Wire.write(0x00); // Measurement mode
  Wire.endTransmission();
  delay(100);

  // キャリブレーションが成功したかどうかを確認
  Wire.requestFrom(address, 1);
  if (Wire.available())
  {
    uint8_t status = Wire.read();
    if (status == 0)
    {
      Serial.println("キャリブレーションに成功しました");
      return true; // キャリブレーション成功
    }
    else if (status == 2)
    {
      Serial.println("キャリブレーションに失敗しました");
      return false; // キャリブレーション失敗
    }
  }
  Serial.end();

  return false;
}
