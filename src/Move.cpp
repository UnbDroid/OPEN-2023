#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Pins.h>
int count =0;
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
    int a;
}
void rotates180(RotateDirections rotateDirection, int velocity ,MotorDC * motorLeft, MotorDC * motorRight){
    int a;
}
void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLef, MotorDC * motorRight, int velocity){
    int a;
}
void moveForSquare(int quantityToMove, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    while(count<quantityToMove){
        lightSensorLeft->read();
        lightSensorRight->read();
        movePID(FORWARD, 255 ,leftMotor, rightMotor);
        if(lightSensorRight->getCrossed()){
            count++;
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