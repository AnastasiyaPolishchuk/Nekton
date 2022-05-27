// lib includes
#include <Arduino.h>

#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050.h"

// user difines

// user varinbles
int motSpeedS[5];
int motSpeed1 = 0;
int motSpeed2 = 0;
int motSpeed3 = 0;
int motSpeed4 = 0;
int motSpeed5 = 0;


int adr = 0;
int arg[5] = {0, 0, 0, 0, 0};

bool enbl_stab = 0;
uint8_t rgbLaneState = 0; // 0 - off, 1 - do, 2 - error
int sideAct = 0;

int angle[2] = {0, 0};
int depth = 0;
int temper = 0;

// user includes
#include "senor.h"
#include "strings.h"
#include "motors.h"
#include "protocol.h"


void setup()
{
 

  // usb setup
  Serial.begin(9600);
    pinMode(13, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    analogWrite(3, 100);
    delay(1000);
  // servo/mot setup
  // pin setup
    pinMode(LED_PIN, OUTPUT);

    // servo setup
    mot1.attach(MOT_PIN1);
    mot2.attach(MOT_PIN2);
    mot3.attach(MOT_PIN3);
    mot4.attach(MOT_PIN4);
    mot5.attach(MOT_PIN5);
    // need to put setup to controllers bldc
    Serial.println("start");
    mot1.writeMicroseconds(2300);
    mot2.writeMicroseconds(2300);
    mot3.writeMicroseconds(2300);
    mot4.writeMicroseconds(2300);
    mot5.writeMicroseconds(2300);
    delay(2000);
    Serial.write("mid");
    mot1.writeMicroseconds(1470);
    mot2.writeMicroseconds(1470);
    mot3.writeMicroseconds(1470);
    mot4.writeMicroseconds(1470);
    mot5.writeMicroseconds(1470);
    delay(2000);
    Serial.println("end");
    delay(100);
      int val = analogRead(0);
    val = map(analogRead(0), 0, 1023, 800, 2300);
//    if(val > 1470 && val < 1530)
//    {
      val = 1500;
//    }
    mot1.writeMicroseconds(val);
    mot2.writeMicroseconds(val);
    mot3.writeMicroseconds(val);
    mot4.writeMicroseconds(val);
    mot5.writeMicroseconds(val);
    Serial.println(val);
    delay(4000);
}

void loop()
{
adr = 0;
    if (Serial.available())
    {


      char data[30] = ""; // here is string from pi
      adr = Serial.readBytesUntil(';', data, 30);
      data[adr] = 0;
      Serial.flush();

      char param[3] = "";
      getPar(data, param, 1); // first parameter: xx, from 10 to 99 (1-9 can cause bugs)
      adr = atoi(param);      // get adr from pi

      switch (adr) // decode data from pi
      {
      case (LED_ADR):           // use to set led power
        getPar(data, param, 2); // get parameter
        arg[0] = atoi(param);
        Serial.println(arg[0]);
        digitalWrite(13, arg[0]);
        break;

      case (MOT_ADR):
        for (int i = 0; i < 5; i++)
        {
          getPar(data, param, i + 2);
          motSpeedS[i] = atoi(param);

          //Serial.println(motSpeedS[i]);
        }
       mot1.writeMicroseconds(1500+motspeed[0]);
       mot2.writeMicroseconds(1500+motspeed[1]);
       mot3.writeMicroseconds(1500+motspeed[2]);
       mot4.writeMicroseconds(1500+motspeed[3]);
       mot5.writeMicroseconds(1500+motspeed[4]);
        
        break;

      case (STABLE_ADR):
        getPar(data, param, 2);
        enbl_stab = atoi(param);
        break;

      case (RGB_ADR):
        getPar(data, param, 2);
        rgbLaneState = atoi(param);
        break;

      case (SIDE_ACT_ADR):
        getPar(data, param, 2);
        sideAct = atoi(param);
        if (sideAct > 0)
        {
          switch (sideAct)
          {
          case (1):
            break;
          case (2):
            break;
          case (3):
            break;
          }
        sideAct = 0;
       }
        break;

      case (SEND_ANGLE1):
        getPar(data, param, 2);
        Serial.println(angle[0]);
        break;

      case (SEND_ANGLE2):
        getPar(data, param, 2);
        Serial.println(angle[1]);
        break;

      case (SEND_DEPTH):
        getPar(data, param, 2);
        Serial.println(depth);
        break;

      case (SEND_TEMPER):
        getPar(data, param, 2);
        Serial.println(temper);
        break;
      }

    }
    delay(10);
}




        
    
    

    // do side actions
    /*if (sideAct > 0)
    {
      switch (sideAct)
      {
      case (1):
        break;
      case (2):
        break;
      case (3):
        break;
      }
      sideAct = 0;
    }*/
