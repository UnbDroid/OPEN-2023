#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Pins.h>

static int correctedYFlag = 0;
static int correctedXFlag = 0;

int previouError = 0;
int previousTime = 0;
int integralError = 0;

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

void correctingDirection(int * direction, MotorDC * leftMotor,MotorDC* rightMotor){
    // leftMotor->moveForward(60);
    // rightMotor->moveForward(40);
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

        while (abs(motorLeft->getEncoder()) < 1100 && abs(motorRight->getEncoder()) < 1100){
            motorLeft->moveForward(velocity);
            motorRight->moveBackward(velocity);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break; 

    case AROUND:
        motorLeft->moveForward(velocity);
        motorRight->moveBackward(velocity);

        while (abs(motorLeft->getEncoder()) < 2010 && abs(motorRight->getEncoder()) < 2010){
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
    int rightWhite = 150;
    //dica do caio, ao inves de ser o while dentro de while, o motor que tiver no branco pode chegar pra tras algumas rotações do encoder.
    // pra que não fique preso.

    // if (type == 6){
    //     if (lightSensorLeft->read()<leftWhite){
    //         Serial.println("tras 6");
    //         while(lightSensorLeft->read()<leftWhite){
    //             motorLeft->moveBackward(velocity+10);
                
    //         }        
    //     }
    //     stop(motorLeft,motorRight);
    //     delay(1000);
    //     type = 1;
    // } else if (type == 7){
    //     if (lightSensorRight->read()<rightWhite){
    //         while(lightSensorRight->read()<rightWhite){
    //             motorRight->moveBackward(velocity);
    //             // Serial.println("tras 7");
    //         }
    //     stop(motorLeft,motorRight);
    //     delay(1000);
    //     type = 2;
    // }

    // if(type == 1){
    //     while(lightSensorRight->read()<rightWhite){
    //         motorRight->moveForward(velocity);
    //     }
    // } else if (type == 2){
    //     while(lightSensorLeft->read()<leftWhite){
    //         motorLeft->moveForward(velocity+10);
    //     }
    // } else if(type == 3){
    //     return ;
    // } else if (type == 4){
    //     while(lightSensorLeft->read()<leftWhite){
    //         motorLeft->moveBackward(velocity+10);
    //     }
    // } else if(type == 5){
    //     while(lightSensorRight->read()<rightWhite){
    //         motorRight->moveBackward(velocity);
    //     }

    if (lightSensorLeft->read()>leftWhite || lightSensorRight->read()>rightWhite){
        Serial.println("estou me alinhando");
        stop(motorLeft,motorRight);
        delay(5000);
        // movePID(BACKWARD,30,)
        
        if (lightSensorLeft->read()<leftWhite) //vê branco
        {
            Serial.print("esquerdo ve branco ");
            while (lightSensorLeft->read()<leftWhite) { // && lightSensorRight->read()>rightWhite){ // ve branco
                Serial.println(lightSensorLeft->read());
                motorLeft->moveForward(velocity+10);
                // motorRight->moveBackward(velocity-5);
                if(lightSensorRight->read()<rightWhite){
                    while (lightSensorRight->read()<rightWhite)
                    {
                        motorRight->moveBackward(velocity);
                    }    
                }
            }
            // while(!(lightSensorLeft->read()<leftWhite && lightSensorRight->read()>rightWhite)){
            //     movePID(FORWARD,45,motorLeft,motorRight);
            // }
            
        }
        else if (lightSensorRight->read() < rightWhite) //ve branco
        {
            Serial.println("direito ve branco");
            while (lightSensorRight->read()<rightWhite) {// ve branco
                motorRight->moveForward(velocity);
                // motorLeft->moveBackward(velocity-20);
                // if(lightSensorLeft->read()<leftWhite){
                //     while (lightSensorLeft->read()<leftWhite)
                //     {
                //         motorLeft->moveBackward(velocity+10);
                //     }    
                // }    
            }
        }  
    stop(motorLeft, motorRight);
    delay(500);
    } else{
        return ;
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
                count++;
                lightSensorLeft->setCrossed(false);
                lightSensorRight->setCrossed(false);
        }
        }
    }
    return ;
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
    Serial.println(*current);
    return ;
}


void movePID(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight){

    // KD tem que compensar rapido o suficiente pro KI não ficar muito tempo errado
    // Se ele tiver oscilando demais, tira primeiro o KD e depois o KI

    long currentTime = micros();
    float deltaT = ((float)(currentTime-previousTime))/10e6;
    previousTime = currentTime;

    int posEncoderLeft = motorLeft->getEncoder();
    int posEncoderRight = motorRight->getEncoder();
    int erro = posEncoderRight - posEncoderLeft;

    float derivativeErro = (erro - previouError)/deltaT;
    integralError = integralError + erro*deltaT;

    int incremento = erro*KP + derivativeErro*KD + integralError*KI;
    
    int parameterVelocityLeft = velocity + incremento;
    int parameterVelocityRight = velocity;


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
        leftMotor->setEncoder(0);
        rightMotor->setEncoder(0);  
        while(!correctedYFlag &&(*currentY!=*destinationYX)){

            while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
                leftMotor->moveBackward(120);
                rightMotor->moveBackward(100);
            }    
            stop(leftMotor,rightMotor);
            delay(1000);
            leftMotor->setEncoder(0);
            rightMotor->setEncoder(0);
            while(*currentDirection!=destinationDirection){
                correctingDirection(currentDirection,leftMotor,rightMotor);
                delay(1000);
            }
            stop(leftMotor,rightMotor);
            changingAndCountingPosition(currentY,destinationYX,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            correctedYFlag=1;
            break;
        }
        leftMotor->setEncoder(0);
        rightMotor->setEncoder(0);
        while(!correctedXFlag && (*currentX!=*(destinationYX+1))){
            while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
                leftMotor->moveBackward(120);
                rightMotor->moveBackward(100);
            }    
            stop(leftMotor,rightMotor);
            delay(1000);
            leftMotor->setEncoder(0);
            rightMotor->setEncoder(0);
            destinationDirection= futureDirection('x',*currentX,*(destinationYX+1));
            while(*currentDirection !=destinationDirection){
                correctingDirection(currentDirection,leftMotor,rightMotor);
                delay(1000);
            }
            stop(leftMotor,rightMotor);
            changingAndCountingPosition(currentX,destinationYX+1,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            break;
        }
        correctedXFlag=0;
        correctedYFlag=0;
        return ;
}




void moveTo(int * currentX,int *currentY,int *destinationYX,int *currentDirection, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){

    
    int yDestino =*destinationYX;
    int xDestino = *(destinationYX+1);
    int arrayPosicaoAtual[]={yDestino,xDestino};
    if(*currentX!=xDestino || *currentY !=yDestino){
        while(*currentX!=xDestino || *currentY !=yDestino){
            if((*currentY >=5 && yDestino>=5)  || (*currentY <=2  && yDestino<=2)){
            moveYandMoveX(currentX,currentY,destinationYX,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            }
            else if(yDestino==3||yDestino==4){
                int * lowestCrossBlock;
                lowestCrossBlock = shortestArea(true,*currentY,*currentX);
                delay(2000);
                moveYandMoveX(currentX,currentY,lowestCrossBlock,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
                stop(leftMotor,rightMotor);
                moveYandMoveX(currentX,currentY,arrayPosicaoAtual,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
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
                stop(leftMotor,rightMotor);
                moveYandMoveX(currentX,currentY,arrayPosicaoAtual,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
                
            }
        }
    }
         
}