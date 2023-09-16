#include<Arduino.h>
#include<Wire.h>
#include <Bumper.h>

Bumper :: Bumper(int pinBumper){
    
    this->pinBumper = pinBumper;
    pinMode(pinBumper, INPUT_PULLUP);
}

bool Bumper::checkBumper(){
    bool value = digitalRead(pinBumper);
    
    Serial.print("entrei aqui ");
    Serial.println(value);

    return value;
}