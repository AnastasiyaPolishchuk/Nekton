#include <Arduino.h>
#include "senor.h"
#include <GyverBME280.h>
#include <MPU6050.h>
GyverBME280 bme;
MPU6050 mpu;
// user defines in .h file

// funct
void initSensors()
{
   if (!bme.begin(0x76)) Serial.println("Error!"); // init bmp280 ofr pressure and temperature

    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


}
float getTemper() // in c
{
  float temp = bme.readTemperature();
  return temp;
}
float getPress() // in pa
{
  float temp = bme.readPressure();
  return temp;
}

int getData(int ardess)
{
  switch (ardess)
  {
  case (001):
    return analogRead(A0);
    break;
   case (002):
    return analogRead(A0);
    break;
   case (003):
    return analogRead(A0);
    break;
  
  default:
  return 0;
    break;
  }

}
int watClear()
{
  int lit = analogRead(LIT_SEN_PIN);
  analogWrite(3, 100);
  lit = map(lit, 0, 1023, 0, 255);
  analogWrite(3, 100);
  return lit;
}
