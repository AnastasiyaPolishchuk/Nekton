#ifndef MOTORS_H
#define MOTORS_H
//defines
#define MOT_PIN1 3
#define MOT_PIN2 4
#define MOT_PIN3 5
#define MOT_PIN4 6
#define MOT_PIN5 7

#define L_MOT1 1
#define L_MOT2 1 
#define L_MOT3 2 

#define MAX_SPEED 100
#define MIN_SPEED -100

#define LED_PIN 3

//funct
void motInit();
void motGetSpeed(int *src);
void stability(bool enbl); 
void motSetSpeed();
void setLedPower(int power);

#endif
