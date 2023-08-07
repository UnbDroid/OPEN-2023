#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Pins.h>
int count =0;
void move(MOVE::Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor * lightSensorLeft,LightSensor* lightSensorRight){
    switch (direction)
    {
    case MOVE::FORWARD:
        
        motorLeft->moveForward(velocity);
        motorRight->moveForward(velocity);    
        break;
    case MOVE::BACKWARD:
        motorLeft->moveBackward(velocity);
        motorRight->moveBackward(velocity);
        break;    
    default:
        break;
    }
}

void initialPosition(MPU9250 * mpu){
    int a;
}
void rotates90(MOVE::RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight){
    int a;
}
void rotates180(MOVE::RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight){
    int a;
}
void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight, int velocity){
    int a;
}
void moveForSquare(int quantityToMove, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    quantityToMove++;
    while(count<quantityToMove){
      lightSensorLeft->read();
      lightSensorRight->read();
      movePID(MOVE::FORWARD, 255 ,leftMotor, rightMotor);
        if(lightSensorRight->getCrossed()){
            count++;
            lightSensorLeft->setCrossed(false);
            lightSensorRight->setCrossed(false);
        }
    }
}


// void moveForwardPid(MotorDC* motorLeft, MotorDC* motorRight, int velocity){
//     int posEncoderLeft = motorLeft->getEncoder();
//     int posEncoderRight = motorRight->getEncoder();

//     int erro = posEncoderLeft - posEncoderRight;
//     int incremento = erro*KP;
//     int parameterVelocityLeft = velocity - incremento;
//     int parameterVelocityRight = velocity + incremento;

//     motorLeft->moveFoward(parameterVelocityLeft);
//     motorLeft->moveFoward(parameterVelocityRight);
// }


void movePID(MOVE::Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight){
    int posEncoderLeft = motorLeft->getEncoder();
    int posEncoderRight = motorRight->getEncoder();

    int erro = posEncoderLeft - posEncoderRight;
    int incremento = erro*KP;
    int parameterVelocityLeft = velocity - incremento;
    int parameterVelocityRight = velocity + incremento;


    switch (direction)
    {
    case MOVE::FORWARD:
        
        motorLeft->moveForward(parameterVelocityLeft);
        motorRight->moveForward(parameterVelocityRight);    
        break;

    case MOVE::BACKWARD:
        motorLeft->moveBackward(parameterVelocityLeft);
        motorRight->moveBackward(parameterVelocityRight);
        break;    

    default:
        break;
    }
}
void move2(int quantityToMove,LightSensor * lightSensorLeft, LightSensor *lightSensorRight){
    quantityToMove++;
    while(count<quantityToMove){
        analogWrite(A12,0);
        analogWrite(A11, 255);
        analogWrite(A9, 255);
        analogWrite(A10, 0);
      
      lightSensorLeft->read();
      lightSensorRight->read();
        if(lightSensorRight->getCrossed()){
            Serial.println("atravessei");
            count++;
            lightSensorLeft->setCrossed(false);
            lightSensorRight->setCrossed(false);
        }
    }
    analogWrite(A12,0);
    analogWrite(A11, 0);
    analogWrite(A9, 0);
    analogWrite(A10, 0);
}