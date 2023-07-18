#include"LightSensor.h"

LightSensor::LightSensor(int pinoA0){
    pinMode(pinoA0, OUTPUT);
    this->pinoA0=pinoA0;
};

float LightSensor::read(){
    return analogRead(this->pinoA0);
};