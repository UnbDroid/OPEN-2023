#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>

void move(Directions direction, int *velocity ,MotorDC* motorLeft, MotorDC* motorRight){
    switch (direction)
    {
    case FOWARD:
        motorLeft->moveFoward(velocity);
        motorRight->moveFoward(velocity);    
        break;
    case BACKWARD:
        motorLeft->moveBackward(velocity);
        motorRight->moveBackward(velocity);
        break;    
    default:
        break;
    }
}
void movePid(Directions direction, int velocity ,MotorDC * motorLeft, MotorDC * motorRight){
    int a;
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
