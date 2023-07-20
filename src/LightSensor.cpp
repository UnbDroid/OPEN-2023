#include"LightSensor.h"

int changesCounter=0;
LightSensor::LightSensor(int pinoA0){
    pinMode(pinoA0, INPUT);
    this->pinoA0=pinoA0;
    
};

float LightSensor::read(){
    float read =analogRead(this->pinoA0);
    char currentCharColor;
    currentCharColor = read>250?'b':'w';
    if(changesCounter<3){
        if(currentCharColor!=this->getLastestChanges()){
        changesCounter++;
        this->setLastestChanges(currentCharColor);
        }
        setAcrossed(false);
    }
    else{
        changesCounter=1;
        if(currentCharColor!=this->getLastestChanges()){
            setLastestChanges(currentCharColor);
        }
        setAcrossed(true);
    }
    return changesCounter;   
};

char  LightSensor::getLastestChanges(){
    return this->lastestChange;
};
void LightSensor::setAcrossed(bool value){
    this->acrossed=value;
};
bool LightSensor::getAcrossed(){
    return this->acrossed;
}
void LightSensor::setLastestChanges(char value){
    this->lastestChange=value;
};

