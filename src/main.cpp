#include<Arduino.h>
#include<Wire.h>
#include <MotorDC.h>
#include <Ultrassonic.h>

#define IN1 22
#define IN2 23
#define IN3 24
#define IN4 25

#define PwM_left 3
#define PwM_right 2

#define echoPin 50
#define trigPin 51

float velocidade = 255;
float distance;

Ultrassonic ultrassound(echoPin,trigPin);

// MotorDC leftMotor(IN1,IN2,PwM_left);
// MotorDC rightMotor(IN3,IN4,PwM_right);

void setup(){
    Serial.begin(9600);

}
void loop(){

    distance = ultrassound.distance_meters();

    Serial.println("a distance que o pulso volta é que ta lendo em metros é:");
    Serial.println(distance);

    delay(100);

    // rightMotor.andar_para_frente(&velocidade);
    // leftMotor.andar_para_frente(&velocidade);

}
        