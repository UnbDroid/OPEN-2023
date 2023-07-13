#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include<Arduino.h>
class LightSensor{
    public:
    float read();
    LightSensor(int pinoA0);
    private:
    int pinoA0;
};

#endif