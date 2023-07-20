#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include<Arduino.h>

class LightSensor{
    public:
    float read();
    char * lastRead;
    LightSensor(int pinoA0);
    bool acrossed();
    void setLastestChanges(char latestRead[3]);
    char * getLastestChanges();
    private:
    char lastestChanges[3]={'A','A','A'};
    int pinoA0;
};

#endif