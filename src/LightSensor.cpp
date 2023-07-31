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
    char color = mediaPonderada>=200?'b':'w';
    this->setCurrentColor(color);
    if(this->mediaPonderada>=200 or (this->mediaPonderada<=40 and this->mediaPonderada>=24)){
        if(this->changesCounter<2){
            /* 
               Talvez o problema é que ele está contabilizando errado que atravessou, pois ele não está contando o
               preto do quadrado dele, só o próximo, o que é um problema. 
            */
            if(this->currentColor!=this->getLastestChange()){
                this->changesCounter++;
                this->setLastestChange(this->currentColor);
                setCrossed(false);   
                /*
                    Alterei para ele colocar como falso apenas quando ele achar dnv o branco, pois assim talvez 
                    na lógica eu consigo contabilizar que ele atravessou apenas quando os dois
                    estiverem como true
                */
            }
        }
        else{
            this->changesCounter=0;
            setCrossed(true);
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