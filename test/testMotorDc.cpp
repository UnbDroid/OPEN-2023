#include<Arduino.h>
#include<Wire.h>

#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25
#define PwM_left 3
#define PwM_right 2
void setup(){
   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);

}
void loop(){
    for ( int i=0;i<250;i++){
        digitalWrite(IN1, HIGH);
        digitalWrite(IN1, LOW);
        analogWrite(PwM_left, i);
        delay(2000);
    }
    for ( int i=0;i<250;i++){
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(PwM_right, i);
        delay(2000);
    }
   
}
