// lib
#include <Servo.h>
#include <string.h>
#include <Arduino.h>

// user includes
#include "motors.h"

// user defines in .h file

// vertical mot 1-3
Servo mot1; // left
Servo mot2; // right
Servo mot3; // back
// horisontal mot 4-5
Servo mot4; // left
Servo mot5; // right

// variabels
int motSpeedL[5] = {0, 0, 0, 0, 0};

float angleX = 0;
float angleY = 0;

// funct
void motInit()
{
    // pin setup
    pinMode(LED_PIN, OUTPUT);


    // servo setup
    mot1.attach(MOT_PIN1);
    mot2.attach(MOT_PIN2);
    mot3.attach(MOT_PIN3);
    mot4.attach(MOT_PIN4);
    mot5.attach(MOT_PIN5);
    // need to put setup to controllers bldc
}

bool normalWorkingState()
{
    // error handler
    // if speed is out of range
    for (int i; i < 5; i++)
    {
        if (motSpeedL[i] > MAX_SPEED)
        {
            motSpeedL[i] = MAX_SPEED;
        }
        else
        {
            if (motSpeedL[i] < MIN_SPEED)
            {
                motSpeedL[i] = MIN_SPEED;
            }
        }
    }
    return true;
}

void motGetSpeed(int *src)
{
    memcpy(motSpeedL, src, 5);
}

void motSetSpeed()
{
    if (normalWorkingState())
    {
        mot1.write(motSpeedL[0]);
        mot2.write(motSpeedL[1]);
        mot3.write(motSpeedL[2]);
        mot4.write(motSpeedL[3]);
        mot5.write(motSpeedL[4]);
    }
}

void stability(bool enbl)
{
    if (enbl == 0)
    {
        return;
    }
    else
    {
        if (abs(angleX) >= 30) // ignore angle X (up/down)
        {
            if (angleX >= 30) // if front down
            {
                angleX = 30;
                motSpeedL[0] += angleX * L_MOT1;
                motSpeedL[1] += angleX * L_MOT2;
                motSpeedL[2] -= angleX * L_MOT3;
            }
            else // if front up
            {
                angleX = -30;
                motSpeedL[0] += angleX * L_MOT1;
                motSpeedL[1] += angleX * L_MOT2;
                motSpeedL[2] -= angleX * L_MOT3;
            }
        }
        else
        {
            if (angleX >= 30) // if front down
            {
                motSpeedL[0] += angleX * L_MOT1;
                motSpeedL[1] += angleX * L_MOT2;
                motSpeedL[2] -= angleX * L_MOT3;
            }
            else // if front up
            {
                motSpeedL[0] += angleX * L_MOT1;
                motSpeedL[1] += angleX * L_MOT2;
                motSpeedL[2] -= angleX * L_MOT3;
            }
        }

        if (abs(angleY) >= 30) // ignore angle Y (right/left) (pos/neg)
        {
            if (angleY >= 30) // if right is up
            {
                angleY = 30;
                motSpeedL[0] += angleY * L_MOT1;
                motSpeedL[1] -= angleY * L_MOT2;
            }
            else // if left is up
            {
                angleY = -30;
                motSpeedL[0] += angleY * L_MOT1;
                motSpeedL[1] -= angleY * L_MOT2;
            }
        }
        else
        {
            if (angleY >= 30)
            {
                motSpeedL[0] += angleY * L_MOT1;
                motSpeedL[1] -= angleY * L_MOT2;
            }
            else
            {
                motSpeedL[0] += angleY * L_MOT1;
                motSpeedL[1] -= angleY * L_MOT2;
            }
        }
    }
}
void setLedPower(int power)
{
    if (power > 255)
    {
        analogWrite(LED_PIN, power);
        return;
    }
    if (power < 0)
    {
        analogWrite(LED_PIN, 0);
        return;
    }
    analogWrite(LED_PIN, power);
}
