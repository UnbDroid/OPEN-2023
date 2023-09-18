#include<Arduino.h>
#include<Wire.h>
#include <Bumper.h>

Bumper :: Bumper(int pinBumper){
    
    this->pinBumper = pinBumper;
    pinMode(pinBumper, INPUT_PULLUP);
}

bool Bumper::checkBumper(){
    bool value = digitalRead(pinBumper);
    return value;
}