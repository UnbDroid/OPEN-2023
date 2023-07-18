#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include<Arduino.h>

class LightSensor{
    public:
    float read();
    char * lastRead;
    LightSensor(int pinoA0);
    bool acrossed();
    char lastestChanges[3]={'A','A','A'};
    void setLastestChanges(char latestRead[3]);
    char * getLastestChanges();
    private:
    int pinoA0;
};

#endif