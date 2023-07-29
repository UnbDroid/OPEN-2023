#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include<Arduino.h>

class LightSensor{
    public:
    float read();
    LightSensor(int pinoA0);
    void setLastestChange(char value);
    char getLastestChange();
    void setCrossed(bool value);
    bool getCrossed();
    char getCurrentColor();
    void setCurrentColor(char color);
    int mediaPonderada=150;
    private:
    char currentColor;
    int changesCounter=0;
    char lastestChange;
    int pinoA0;
    bool crossed;
};

#endif