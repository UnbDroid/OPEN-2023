#include"LightSensor.h"

#define ALPHA 0.5



LightSensor::LightSensor(int pinoA0){
    pinMode(pinoA0, INPUT);
    this->pinoA0=pinoA0;
    this->setLastestChange('b');
    this->setCrossed(false);
    this->changesCounter=0;
};

float LightSensor::read(){
    float read =analogRead(this->pinoA0);
    this->mediaPonderada = (float)this->mediaPonderada *ALPHA +(1 -ALPHA)*read;
    char color = read>=200?'b':'w';
    this->setCurrentColor(color);
    if(this->mediaPonderada>=200 or (this->mediaPonderada<=40 and this->mediaPonderada>=24)){
        if(this->changesCounter<2){
            if(this->currentColor!=this->getLastestChange()){
                this->changesCounter++;
                this->setLastestChange(this->currentColor);   
            }
            setCrossed(false);
        }
        else{
            this->changesCounter=1;
            setCrossed(true);
            setLastestChange(this->currentColor);
        }
    }
    return mediaPonderada;   
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