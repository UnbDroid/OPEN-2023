#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Pins.h>

void move(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor * lightSensorLeft,LightSensor* lightSensorRight){
    switch (direction)
    {
    case FORWARD:
        
        motorLeft->moveForward(velocity);
        motorRight->moveForward(velocity);    
        break;
    case BACKWARD:
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

void rotates90(RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight){
    
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);

    // int encoderLeftValue = abs(motorLeft->getEncoder());
    // int encoderRightValue = abs(motorRight->getEncoder());

    switch(rotateDirection)
    {
    case LEFT:
        motorLeft->moveBackward(velocity);
        motorRight->moveForward(velocity);
        while (abs(motorLeft->getEncoder()) < 1000 && abs(motorRight->getEncoder()) < 1000){
            motorLeft->moveBackward(velocity);
            motorRight->moveForward(velocity);
        }
        motorLeft->stop();
        motorRight->stop();
        break;

    case RIGHT:
        motorLeft->moveForward(velocity);
        motorRight->moveBackward(velocity);

        while (abs(motorLeft->getEncoder()) < 1000 && abs(motorRight->getEncoder()) < 1000){
            motorLeft->moveForward(velocity);
            motorRight->moveBackward(velocity);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break;  

    default:
        break;
    }
}

void rotates180(RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight){
    int a;
}
void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight, int velocity){
    int a;
}


void movePID(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight){
    int posEncoderLeft = motorLeft->getEncoder();
    int posEncoderRight = motorRight->getEncoder();

    int erro = posEncoderLeft - posEncoderRight;
    int incremento = erro*KP;
    int parameterVelocityLeft = velocity - incremento;
    int parameterVelocityRight = velocity + incremento;


    switch (direction)
    {
    case FORWARD:
        
        motorLeft->moveForward(parameterVelocityLeft);
        motorRight->moveForward(parameterVelocityRight);    
        break;

    case BACKWARD:
        motorLeft->moveBackward(parameterVelocityLeft);
        motorRight->moveBackward(parameterVelocityRight);
        break;    

    default:
        break;
    }
}

void stop(MotorDC* motorLeft, MotorDC* motorRight){
    motorLeft->stop();
    motorRight->stop();
}

void resetEncoders(MotorDC* motorLeft, MotorDC* motorRight){
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);

}