#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Pins.h>
#include<Sol.h>
static int correctedYFlag = 0;
static int correctedXFlag = 0;
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
        rotates90(RIGHT,80,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        *direction = SOL::Norte;
    }
    else{
        rotates90(RIGHT,80,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        *direction=*direction+1;
    }
    return ;
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

        while (abs(motorLeft->getEncoder()) < 1100 && abs(motorRight->getEncoder()) < 1100){
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

void moveForSquare(int quantityToMove, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    quantityToMove++;
    int count =0;
    if(count<quantityToMove){
        while(count<quantityToMove){
        leftMotor->moveForward(100);
        rightMotor->moveForward(80);
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

void moveBackAndCorrectDirection(SOL::Direcao destinationDirection,int*currentDirection,MotorDC *leftMotor,MotorDC *rightMotor){
    while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
        leftMotor->moveBackward(100);
        rightMotor->moveBackward(80);
    }    
    stop(leftMotor,rightMotor);
    delay(1000);
    resetEncoders(leftMotor,rightMotor);
    while(*currentDirection!=destinationDirection){
        correctingDirection(currentDirection,leftMotor,rightMotor);
        delay(1000);
    }
    return ;
}
void moveYandMoveX(int *currentX,int *currentY,int *destinationYX, int * currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    SOL::Direcao destinationDirection= futureDirection('y',*currentY,*destinationYX);
    resetEncoders(leftMotor,rightMotor);
    while(!correctedYFlag &&(*currentY!=*destinationYX)){
        moveBackAndCorrectDirection(destinationDirection,currentDirection,leftMotor,rightMotor);
        changingAndCountingPosition(currentY,destinationYX,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        correctedYFlag=1;
        break;
    }
    resetEncoders(leftMotor,rightMotor);
    while(!correctedXFlag && (*currentX!=*(destinationYX+1))){
        moveBackAndCorrectDirection(destinationDirection,currentDirection,leftMotor,rightMotor);
        changingAndCountingPosition(currentX,destinationYX+1,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        break;
    }
    correctedXFlag=0;
    correctedYFlag=0;
    return ;
}
void navegateInRegion(int * currentY,int * currentX,int yDestino, int xDestino,int *destinationYX, int* currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor , int *arrayPosicaoAtual){
    if((*currentY >=5 && yDestino>=5)  || (*currentY <=2  && xDestino<=2)){
            moveYandMoveX(currentX,currentY,destinationYX,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
    }
    else{
        int * lowestCrossBlock;
        lowestCrossBlock = shortestArea(true,*currentY,*currentX);
        delay(2000);
        moveYandMoveX(currentX,currentY,lowestCrossBlock,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        if(*lowestCrossBlock==5){
            *lowestCrossBlock =2;
            moveYandMoveX(currentX,currentY,lowestCrossBlock,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);       
        }
        else{
            *lowestCrossBlock =5;         
            moveYandMoveX(currentX,currentY,lowestCrossBlock,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        }
        moveYandMoveX(currentX,currentY,arrayPosicaoAtual,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        
    }
}
void changingAndCountingPosition(int * current ,int *destination,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    if(*current<*destination){
        while(*current<*destination){
                moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
                *current = *current+1;
        }
            moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
        }
    else if(*current>*destination){
        while(*current>*destination){
                moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
                *current = *current-1;
        }
            moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
        }
    return ;
}
void moveTo(int * currentX,int *currentY,int *destinationYX,int *currentDirection, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    
    int yDestino =*destinationYX;
    int xDestino = *(destinationYX+1);
    int arrayPosicaoAtual[]={yDestino,xDestino};

    if(*currentX!=xDestino || *currentY !=yDestino){
        while(*currentX!=xDestino || *currentY !=yDestino){
            navegateInRegion(currentY,currentX,yDestino,xDestino,destinationYX,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor,arrayPosicaoAtual);
        }
    }
         
}