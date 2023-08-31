#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Pins.h>
#include<Sol.h>

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
void correctingDirection(int * direction, MotorDC * leftMotor,MotorDC* rightMotor){
    // leftMotor->moveForward(60);
    // rightMotor->moveForward(40);
    static int flag = 1;
    if(*direction>=SOL::Oeste){
        rotates(RIGHT,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        *direction = SOL::Norte;
    }
    else{
        rotates(RIGHT,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        *direction=*direction+1;
    }
    Serial.print("Girei ");
    Serial.println(flag);
    flag++;
    return ;
}

void rotates(RotateDirections rotateDirection,MotorDC * motorLeft, MotorDC * motorRight){
    int velocity = 130;
    
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);

    // int encoderLeftValue = abs(motorLeft->getEncoder());
    // int encoderRightValue = abs(motorRight->getEncoder());

    switch(rotateDirection)
    {
    case LEFT:
        motorLeft->moveBackward(velocity);
        motorRight->moveForward(velocity);
        while (abs(motorLeft->getEncoder()) < 910 && abs(motorRight->getEncoder()) < 910){
            motorLeft->moveBackward(velocity);
            motorRight->moveForward(velocity);
        }
        motorLeft->stop();
        motorRight->stop();
        break;

    case RIGHT:
        motorLeft->moveForward(velocity);
        motorRight->moveBackward(velocity);

        while (abs(motorLeft->getEncoder()) < 900 && abs(motorRight->getEncoder()) < 900){
            motorLeft->moveForward(velocity);
            motorRight->moveBackward(velocity);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break; 

    case AROUND:
        motorLeft->moveForward(velocity);
        motorRight->moveBackward(velocity);

        while (abs(motorLeft->getEncoder()) < 1900 && abs(motorRight->getEncoder()) < 1900){
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

void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLeft, MotorDC * motorRight, int velocity){
    int leftWhite = 150;
    int rightWhite = 200;

    if (lightSensorLeft->read()>leftWhite || lightSensorRight->read()>rightWhite){
        Serial.println("estou me alinhando");
        stop(motorLeft,motorRight);
        delay(5000);
        // movePID(BACKWARD,30,)
        
        if (lightSensorLeft->read()<leftWhite) //vê branco
        {
            Serial.println("esquerdo ve branco");
            while (lightSensorLeft->read()<leftWhite){ // ve branco
                motorLeft->moveForward(velocity+10);
                if(lightSensorRight->read()<rightWhite){
                    while (lightSensorRight->read()<rightWhite)
                    {
                        motorRight->moveBackward(velocity);
                    }    
                }
            }
        }
        else if (lightSensorRight->read() < rightWhite) //ve branco
        {
            Serial.println("direito ve branco");
            while (lightSensorRight->read()<rightWhite) {// ve branco
                motorRight->moveForward(velocity);
                if(lightSensorLeft->read()<leftWhite){
                    while (lightSensorLeft->read()<leftWhite)
                    {
                        motorLeft->moveBackward(velocity+10);
                    }    
                }    
            }
        }  
    stop(motorLeft, motorRight);
    delay(500);
    }
}


void moveForSquare(int quantityToMove, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    quantityToMove++;
    int count =0;
    if(count<quantityToMove){
        while(count<quantityToMove){
        leftMotor->moveForward(60);
        rightMotor->moveForward(40);
        lightSensorLeft->read();
        lightSensorRight->read();
            if(lightSensorRight->getCrossed()){
                Serial.println("atravesseiiii");
                count++;
                lightSensorLeft->setCrossed(false);
                lightSensorRight->setCrossed(false);
        }
        }
    }
    return ;
}



void movePID(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight){
    int posEncoderLeft = motorLeft->getEncoder();
    int posEncoderRight = motorRight->getEncoder();

    int erro = posEncoderRight - posEncoderLeft;
    int incremento = erro*KP;
    int parameterVelocityLeft = velocity + incremento;
    int parameterVelocityRight = velocity - incremento;


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
    return ;
}

void resetEncoders(MotorDC* motorLeft, MotorDC* motorRight){
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);

}