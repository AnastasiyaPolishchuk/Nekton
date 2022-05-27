#ifndef SENSOR_H
#define SENSOR_H

//user defines
#define LIT_SEN_PIN A7


void initSensors();
float getTemper();
float getPress();

int getData(int ardess);
int watClear();

#endif
