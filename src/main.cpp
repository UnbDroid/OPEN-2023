#include<Arduino.h>
#include<Wire.h>

#define eca 2

#define ecb 3


void meudeus(){

    Serial.println("a");
    
}
void setup(){
    Serial.begin(9600);
    pinMode(7, INPUT);
    pinMode(6, INPUT);
    delay(100);
    attachInterrupt(digitalPinToInterrupt(ecb), meudeus, RISING);

}
void loop(){
}
