#include<Arduino.h>
#include<Wire.h>
#include <LDR.h>


LDR::LDR(int pinLDR){
    
    this->pinLDR = pinLDR;
    pinMode(pinLDR, INPUT);
}

int LDR::read(){
    int value = analogRead(pinLDR);
    return value;

}