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

int velocidade = 255;
float distance;

// Ultrassonic ultrassound(echoPin,trigPin);

MotorDC leftMotor(IN1,IN2,PwM_left);
MotorDC rightMotor(IN3,IN4,PwM_right);

void setup(){
    // Serial.begin(9600);
    // pinMode(IN1, OUTPUT);
    // pinMode(IN2, OUTPUT);
    rightMotor.andar_para_frente(&velocidade);
    leftMotor.andar_para_tras(&velocidade);
    delay(3000)

}
void loop(){
    // digitalWrite(IN1, HIGH);
    // digitalWrite(IN2, LOW);

    // distance = ultrassound.distance_meters();

    // Serial.println("a distance que o pulso volta e que ta lendo em metros é:");
    // Serial.println(distance);

    // delay(100);

    rightMotor.andar_para_frente(&velocidade);
    leftMotor.andar_para_frente(&velocidade);

}
        