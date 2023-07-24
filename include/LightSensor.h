#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include<Arduino.h>

class LightSensor{
    public:
    float read();
    char * lastRead;
    LightSensor(int pinoA0);
    
    void setLastestChanges(char value);
    char getLastestChanges();
    void setAcrossed(bool value);
    bool getAcrossed();
    private:
    char lastestChange;
    int pinoA0;
    bool acrossed;
};

#endif