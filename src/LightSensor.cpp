#include"LightSensor.h"

LightSensor::LightSensor(int pinoA0){
    pinMode(pinoA0, INPUT);
    this->pinoA0=pinoA0;
    this->lastRead = getLastestChanges();
};

float LightSensor::read(){
    float read =analogRead(this->pinoA0);
    if(*this->lastRead){
        if(read>500& *this->lastRead!='B'){
            lastRead++;
            *lastRead = 'B';
    }
    else if(read<200& *this->lastRead!='W'){
        lastRead++;
        *lastRead = 'W';
    }
    }
    else{
    this->lastRead--;
    char lastInArray = *this->lastRead;
    char aa[3]{'A','A','A'};
    setLastestChanges(aa);
    this->lastRead = getLastestChanges();
    *this->lastRead=lastInArray;
    this->lastRead++;
    }
    return read;
};
bool LightSensor::acrossed(){
    char * lastestChanges = getLastestChanges();
    return true;
}
char * LightSensor::getLastestChanges(){
    return this->lastestChanges;
}
void LightSensor::setLastestChanges(char array[3]){
    for(int i=0;i<3;i++){
        this->lastestChanges[i]=array[i];
    }
}
