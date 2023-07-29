#include"LightSensor.h"

int changesCounter=0;
LightSensor::LightSensor(int pinoA0){
    pinMode(pinoA0, INPUT);
    this->pinoA0=pinoA0;
    
};

float LightSensor::read(){
    float read =analogRead(this->pinoA0);
    char color = read>250?'b':'w';
    this->setCurrentColor(color);
    if(this->changesCounter<3){
        if(this->currentColor!=this->getLastestChange()){
        this->changesCounter++;
        this->setLastestChange(this->currentColor);
        }
        setCrossed(false);
    }
    else{
        this->changesCounter=1;
        if(this->currentColor!=this->getLastestChange()){
            setLastestChange(this->currentColor);
        }
        setCrossed(true);
    }
    return read;   
};

char  LightSensor::getLastestChange(){
    return this->lastestChange;
};
void LightSensor::setCrossed(bool value){
    this->crossed=value;
};
bool LightSensor::getCrossed(){
    return this->crossed;
}
void LightSensor::setLastestChange(char value){
    this->lastestChange=value;
};

char LightSensor::getCurrentColor(){
    return this->currentColor;
}
void LightSensor::setCurrentColor(char color){
     this->currentColor=color;
}