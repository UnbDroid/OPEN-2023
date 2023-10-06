#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Ultrassonic.h>
#include <Pins.h>
#include <Solution.h>
#include <Bumper.h>
#include <LDR.h>

static int correctedYFlag = 0;
static int correctedXFlag = 0;

int previousError = 0;
unsigned long previousTime = 0;
int integralError = 0; 
float constMotors[2] = {0,0};

double motorLeftTurns = 0;
double motorRightTurns = 0;

double sumRPSLeft = 0;
double sumRPSRight = 0;

//PID separado motores
double previousMotorLeftTurns = 0;
double previousMotorRightTurns = 0;
// int leftIntegralError = 0;
// int rightIntegralError = 0;

double leftIntegralErrorSum = 0;
double rigthIntegralErrorSum = 0;

double leftIntegralError[5] = {0,0,0,0,0};
double rightIntegralError[5] = {0,0,0,0,0};

double add(double * ptr, double valor){
    double sum = 0;
    int tam = 4;

    while(tam){
        *(ptr+tam) = *(ptr+(tam-1));
        sum = sum + *(ptr+tam);
        tam --;
   }

   *ptr = valor;
   sum = sum + *ptr;

   return sum;
}

void move(Directions direction, int PWM ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor * lightSensorLeft,LightSensor* lightSensorRight){
    switch (direction)
    {
    case FORWARD:
        motorLeft->moveForward(PWM);
        motorRight->moveForward(PWM);    
        break;
    case BACKWARD:
        motorLeft->moveBackward(PWM);
        motorRight->moveBackward(PWM);
        break;    
    default:
        break;
    }
}

void rotates(RotateDirections rotateDirection,MotorDC * motorLeft, MotorDC * motorRight){
    int PWM = 130;
    
    resetEncoders(motorLeft,motorRight);

    switch(rotateDirection)
    {
    case LEFT:

        motorLeft->moveBackward(PWM);
        motorRight->moveForward(PWM);
        while (abs(motorLeft->getEncoder()) < 1100 && abs(motorRight->getEncoder()) < 1100){
            motorLeft->moveBackward(PWM);
            motorRight->moveForward(PWM);
        }
        stop(motorLeft,motorRight);
        break;

    case RIGHT:
        motorLeft->moveForward(PWM);
        motorRight->moveBackward(PWM);

        while (abs(motorLeft->getEncoder()) < 1050 && abs(motorRight->getEncoder()) < 1050){
            motorLeft->moveForward(PWM);
            motorRight->moveBackward(PWM);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break; 

    case AROUND:
        motorLeft->moveForward(PWM);
        motorRight->moveBackward(PWM);

        while (abs(motorLeft->getEncoder()) < 2010 && abs(motorRight->getEncoder()) < 2010){
            motorLeft->moveForward(PWM);
            motorRight->moveBackward(PWM);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break; 
     

    default:
        break;
    }
}

void align(LightSensor * leftIR, LightSensor *rightIR, MotorDC * motorLeft, MotorDC * motorRight, int PWM, LightSensor * backIR){
    int leftWhite = 110; //200
    int rightWhite = 110;

    int leftReading = leftIR->read();
    int rightReading = rightIR->read();
    Serial.print("sensores IR: ");
    Serial.print(leftReading);
    Serial.print(" ");
    bool alinhou=false;
    Serial.println(rightReading);
    Serial.println("estou me alinhando");

    if ((leftReading>leftWhite || rightReading>rightWhite)&&!alinhou && !(leftIR->read()>leftWhite && rightIR->read()>rightWhite)){
        
        stop(motorLeft,motorRight);
        delay(500);
        if (leftReading<rightReading) //vê branco
        {   
            Serial.print("esquerdo ve branco ");
            motorLeft->setEncoder(0);
            motorRight->stop();
            while (leftReading < rightReading&&motorLeft->getEncoder()<300) { // && rightIR->read()>rightWhite){ // ve branco
                
                motorLeft->moveForward(PWM+20);              
                leftReading = leftIR->read();
                rightReading = rightIR->read();
                
                Serial.print("leitura IR ao alinhar: ");            
                Serial.print(leftReading);
                Serial.print(" ");
                Serial.println(rightReading);
            }

            leftReading = leftIR->read();
            rightReading = rightIR->read();

            if(leftReading >=leftWhite){
                stop(motorLeft,motorRight);
                resetEncoders(motorLeft,motorRight);
                while(motorRight->getEncoder() < 80){
                    motorRight->moveBackward(PWM);
                }
                motorRight->stop();
                alinhou=true;
                
                return;
            }
            else{
                resetEncoders(motorLeft,motorRight);
                motorRight->stop();
                while(leftReading<=leftWhite&&motorLeft->getEncoder()<300){
                    motorLeft->moveBackward(PWM+20);  
                    leftReading = leftIR->read();               
                }
                motorLeft->stop();
                if(leftReading>=leftWhite){
                    alinhou=true;
                    return;
                }
                else{
                    resetEncoders(motorLeft,motorRight);
                    while(leftIR->read()<=leftWhite&&motorLeft->getEncoder()<300){   
                        motorLeft->moveBackward(PWM+20);                 
                    }
                    motorLeft->stop();
                    while(motorRight->getEncoder()<50){
                        motorRight->moveBackward(PWM);                 
                    }
                    motorRight->stop();
                    if(leftReading>=leftWhite){
                        alinhou=true;
                        stop(motorLeft,motorRight);
                        return;
                    }
                    
                    // if(!alinhou){
                    //     resetEncoders(motorLeft,motorRight);
                    //     while(motorLeft->getEncoder()<300){
                    //         Serial.println("entrei aq");
                    //         motorLeft->moveForward(PWM+20);                
                    //     }
                    // } 
                      
                    
                    // motorRight->stop();
                    
                }

            }
            stop(motorLeft,motorRight);
            delay(300);
            return;
        } else if (rightReading < leftReading) //ve branco
            Serial.print("direito ve branco");
            motorRight->setEncoder(0);
            motorLeft->stop();
            while (rightReading < leftReading&&motorRight->getEncoder()<300) { // && rightIR->read()>rightWhite){ // ve branco
                
                motorRight->moveForward(PWM);              
                leftReading = leftIR->read();
                rightReading = rightIR->read();
                
                Serial.print("leitura IR ao alinhar: ");            
                Serial.print(leftReading);
                Serial.print(" ");
                Serial.println(rightReading);
            }

            leftReading = leftIR->read();
            rightReading = rightIR->read();

            if(rightReading >=rightWhite){
                stop(motorLeft,motorRight);
                resetEncoders(motorLeft,motorRight);
                while(motorLeft->getEncoder() < 80){
                    motorLeft->moveBackward(PWM);
                }
                motorLeft->stop();
                alinhou=true;
                
                return;
            }
            else{
                resetEncoders(motorLeft,motorRight);
                motorLeft->stop();
                while(rightReading<=rightWhite&&motorRight->getEncoder()<300){
                    motorRight->moveBackward(PWM+20);  
                    rightReading = leftIR->read();               
                }
                motorRight->stop();
                if(rightReading>=rightWhite){
                    alinhou=true;
                    return;
                }
                else{
                    resetEncoders(motorLeft,motorRight);
                    while(rightIR->read()<=rightWhite&&motorRight->getEncoder()<300){   
                        motorRight->moveBackward(PWM+20);                 
                    }
                    motorRight->stop();
                    while(motorLeft->getEncoder()<50){
                        motorLeft->moveBackward(PWM+20);                 
                    }
                    motorLeft->stop();
                    if(rightReading>=rightWhite){
                        alinhou=true;
                        stop(motorLeft,motorRight);
                        return;
                    }
                    
                    // if(!alinhou){
                    //     resetEncoders(motorLeft,motorRight);
                    //     while(motorRight->getEncoder()<300){
                    //         Serial.println("entrei aq");
                    //         motorRight->moveForward(PWM);                
                    //     }
                    // } 
                      
                    
                    // motorRight->stop();
                    
                }

            }
            stop(motorLeft,motorRight);
            delay(300);
            return;
        }
}


void align(LightSensor * leftIR, LightSensor *rightIR, MotorDC * motorLeft, MotorDC * motorRight, int PWM){
    int leftWhite = 200;
    int rightWhite = 110;

    
    int leftReading = leftIR->read();
    int rightReading = rightIR->read();
    Serial.print("sensores IR: ");
    Serial.print(leftReading);
    Serial.print(" ");
    Serial.println(rightReading);
    
    if ((leftReading>leftWhite || rightReading>rightWhite)){
        Serial.println("estou me alinhando");
        stop(motorLeft,motorRight);
        delay(500);
        leftReading = leftIR->read();
        rightReading = rightIR->read();
        
        if (leftReading<rightReading) //vê branco
        {
            Serial.print("esquerdo ve branco ");
            while (leftReading < rightReading) { // && rightIR->read()>rightWhite){ // ve branco
                motorLeft->moveForward(PWM+20);              
                leftReading = leftIR->read();
                rightReading = rightIR->read();
        
                Serial.print("leitura IR ao alinhar: ");            
                Serial.print(leftReading);
                Serial.print(" ");
                Serial.println(rightReading);
            }
            stop(motorLeft,motorRight);
            delay(300);
            return;
        }
        else if (rightReading < leftReading) //ve branco
        {
            Serial.println("direito ve branco");
            while (rightIR->read()<rightWhite) {// ve branco
                motorRight->moveForward(PWM);
                leftReading = leftIR->read();
                rightReading = rightIR->read();
        
                Serial.print("leitura IR ao alinhar: ");            
                Serial.print(leftReading);
                Serial.print(" ");
                Serial.println(rightReading);
                
                } 
            stop(motorLeft,motorRight);
            delay(300);
            return;
        }

    // return aligned;
    // Serial.println("parei no align");
    // stop(motorLeft, motorRight);
    // delay(500);
    
    } else {
        return;
    }
}





void moveForSquare(int quantityToMove, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    quantityToMove++;
    int count =0;
    if(count<quantityToMove){
        while(count<quantityToMove){
            boucing(leftMotor,rightMotor,lightSensorLeft,lightSensorRight);
        // leftMotor->moveForward(100);
        // rightMotor->moveForward(80);
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

void boucing(MotorDC* leftMotor, MotorDC* rightMotor, LightSensor * leftIR, LightSensor * rightIR){
    int leftBlack = 100;
    int rightBlack = 100;

    if((leftIR->read()>leftBlack && leftIR->read()>rightBlack)){
        leftMotor->moveForward(100);
        rightMotor->moveForward(80);
        
    } else if (leftIR->read()<leftBlack && rightIR->read()<rightBlack){
        leftMotor->moveForward(100);
        rightMotor->moveForward(80);
    }
    
    if (leftIR->read() > leftBlack) {
        while(leftIR->read() > leftBlack){
            leftMotor->moveForward(130);
            // rightMotor->moveForward(50);
        }
    }    

    else if (rightIR->read() > rightBlack) {
        while(rightIR->read() > rightBlack){
            rightMotor->moveForward(100);
            // leftMotor->moveForward(60);
        }
    }
}

void boucing(MotorDC* leftMotor, MotorDC* rightMotor, LightSensor * leftIR, LightSensor * rightIR, Bumper * bumper){
    int leftBlack = 100;
    int rightBlack = 100;

    if((leftIR->read()>leftBlack && rightIR->read()>rightBlack)){
        Serial.println("vi bumper com boucing");
        if(bumper->checkBumper()){
            stop(leftMotor,rightMotor);
            return;
        } else {
        leftMotor->moveForward(100);
        rightMotor->moveForward(80);
        }
    } else if (leftIR->read()<leftBlack && rightIR->read()<rightBlack){

        leftMotor->moveForward(100);
        rightMotor->moveForward(80);
    }
    
    resetEncoders(leftMotor,rightMotor);
    if (leftIR->read() > leftBlack) {

        Serial.print("esquerdo preto ");
        Serial.println(leftIR->read());

        resetEncoders(leftMotor,rightMotor);
        while(leftIR->read() > leftBlack && leftMotor->getEncoder() < 300){
            if(bumper->checkBumper()){
                stop(leftMotor,rightMotor);
                return;
            } else {
                leftMotor->moveForward(130);
                rightMotor->moveForward(80);
            }
            
        }
    }   else if (rightIR->read() > rightBlack) {
        // stop(leftMotor,rightMotor);
        // delay(200);

        Serial.print("direito preto R");
        Serial.println(rightIR->read());

        resetEncoders(leftMotor,rightMotor);
        while(rightIR->read() > rightBlack  && rightMotor->getEncoder()<300){
            if(bumper->checkBumper()){
                Serial.println("vi bumper com boucing");
                stop(leftMotor,rightMotor);
                return;
            } else {
                rightMotor->moveForward(100);
                leftMotor->moveForward(100);
            }
        }
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
    Serial.println(*current);
    return ;
}


void move_cm(int distance_cm, Directions direction ,MotorDC* motorLeft, MotorDC* motorRight){
    float circunference = 37.7;
    int leftEncoderValue = (2048/circunference)*distance_cm;
    int rightEncoderValue = (2000/circunference)*distance_cm;

    resetEncoders(motorLeft,motorRight);
    switch (direction)
    {
    case FORWARD:
        while(motorLeft->getEncoder() < leftEncoderValue && motorRight->getEncoder() < rightEncoderValue){
            motorLeft->moveForward(90);
            motorRight->moveForward(70);
            }
        // stop(motorLeft,motorRight);
        // if(motorLeft->getEncoder() < leftEncoderValue){
        //     while(motorLeft->getEncoder() < leftEncoderValue){
        //         motorRight->stop();
        //         motorLeft->moveForward(90);
        //     }
        // } else if (motorRight->getEncoder()<rightEncoderValue){
        //     while(motorRight->getEncoder()<rightEncoderValue){
        //         motorLeft->stop();
        //         motorRight->moveForward(70);
        //     }
        // }
        break;
    
    case BACKWARD:
        while(motorLeft->getEncoder() < leftEncoderValue && motorRight->getEncoder() < rightEncoderValue){
            motorLeft->moveBackward(90);
            motorRight->moveBackward(70);
            }
        stop(motorLeft,motorRight);
        // if(motorLeft->getEncoder() < leftEncoderValue){
        //     while (motorLeft->getEncoder() < leftEncoderValue)
        //     {
        //         motorRight->stop();
        //         motorLeft->moveBackward(70);
        //     }
        // stop(motorLeft,motorRight);
        // } else if (motorRight->getEncoder()<rightEncoderValue){
        //     while(motorRight->getEncoder()<rightEncoderValue){
        //         motorLeft->stop();
        //         motorRight->moveBackward(60);
        //     }
        //     stop(motorLeft,motorRight);
        // }
        break;
    
    default:
        break;
    }

    delay(500);
}

void movePID(Directions direction, float goalRPS ,MotorDC* motorLeft, MotorDC* motorRight){
    // KD tem que compensar rapido o suficiente pro KI não ficar muito tempo errado
    // Se ele tiver oscilando demais, tira primeiro o KD e depois o KI
    unsigned long currentTime = micros();
    double deltaT = (currentTime-previousTime);
    deltaT = deltaT/(double)1000000;
    previousTime = currentTime;
    // double deltaT = 0.57;
    // double start_time = micros();

    previousMotorLeftTurns = motorLeftTurns;
    previousMotorRightTurns = motorRightTurns;

     //descobrindo o número de rotações
    motorLeftTurns = motorLeft->getEncoder()/(double)2048;
    motorRightTurns = motorRight->getEncoder()/(double)2000; 

    // descobrindo o RPS de cada roda
    double rpsLeft = (motorLeftTurns - previousMotorLeftTurns)/(deltaT);
    double rpsRight = (motorRightTurns - previousMotorRightTurns)/(deltaT);

    sumRPSLeft = sumRPSLeft + rpsLeft;
    sumRPSRight = sumRPSRight + rpsRight;

    double leftError = goalRPS - rpsLeft;
    double rightError = goalRPS - rpsRight;

    leftIntegralErrorSum = add(&leftIntegralError[0],leftError*deltaT);
    rigthIntegralErrorSum = add(&rightIntegralError[0],leftError*deltaT);

    
    double PWMLeft = rpsLeft + leftError*KP_LEFT + leftIntegralErrorSum*KI_LEFT;
    double PWMRight = rpsRight + rightError*KP_RIGHT + rigthIntegralErrorSum*KI_RIGHT;

    if (PWMLeft < 0 || PWMLeft > 1.2)
    {
        PWMLeft = goalRPS;
    } 

    if (PWMRight < 0 || PWMRight > 1.2)
    {
        PWMRight = goalRPS;
    }

    double parameterPWMLeft = PWMLeft*(double)200;//198 ou 210
    double parameterPWMRight = PWMRight*(double)154; //157 ou 156 ou 140

    // double delay_time = deltaT - (micros() - start_time);
    // if (delay_time > 0){
    //     delayMicroseconds(delay_time);
    // }

    // Serial.print("DeltaT: ");
    // Serial.print(deltaT);
    // // Serial.print(" integral:");
    // // Serial.print(leftIntegralErrorSum);
    // // Serial.print(" ");
    // // Serial.print(rigthIntegralErrorSum);
    // // Serial.print("soma RPS ");
    // // Serial.print(sumRPSLeft);
    // // Serial.print(" ");
    // // Serial.print(sumRPSRight);
    // Serial.print(" RPS: ");
    // Serial.print(rpsLeft);
    // Serial.print(" ");
    // Serial.print(rpsRight);
    // Serial.print(" > ");
    // Serial.print("ERRO ");
    // Serial.print(leftError);
    // Serial.print(" ");
    // Serial.print(rightError);
    // Serial.print(" > ");
    // Serial.print("RPS enviado ");
    // Serial.print(PWMLeft);
    // Serial.print(" ");
    // Serial.print(PWMRight);
    // Serial.print(" > ");
    // Serial.print("no motor ");
    // Serial.print(parameterPWMLeft);
    // Serial.print(" ");
    // Serial.println(parameterPWMRight);
 
    

    switch (direction)
    {
    case FORWARD:
        
        motorLeft->moveForward(parameterPWMLeft);
        motorRight->moveForward(parameterPWMRight);    
        break;

    case BACKWARD:
        motorLeft->moveBackward(parameterPWMLeft);
        motorRight->moveBackward(parameterPWMRight);
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
    correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);
    return ;
}
void correctDirection(int* currentDirection,int destinationDirection,MotorDC * leftMotor, MotorDC * rightMotor){
    if(*currentDirection!=destinationDirection){
      if(!(*currentDirection==0&&destinationDirection==3)){
      if((*currentDirection+1==destinationDirection)||(*currentDirection==3&& destinationDirection==0)){
        rotates(RIGHT,leftMotor,rightMotor);
        *currentDirection=destinationDirection;
      }
      else if(*currentDirection-1 == destinationDirection){
        rotates(LEFT,leftMotor,rightMotor);
        *currentDirection= destinationDirection;
      }
      else{
        rotates(RIGHT,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        delay(500);
        rotates(RIGHT,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        delay(500);
        *currentDirection=destinationDirection;
      }
      }
      else{
          rotates(LEFT,leftMotor,rightMotor);
          stop(leftMotor,rightMotor);
          *currentDirection= destinationDirection;
      }
      delay(500);
    }
}
void moveYandMoveX(int *currentX,int *currentY,int *destinationYX, int * currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    SOL::Direcao destinationDirection= futureDirection('y',*currentY,*destinationYX);
        resetEncoders(leftMotor,rightMotor);  
        while(!correctedYFlag &&(*currentY!=*destinationYX)){

            while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
                leftMotor->moveBackward(120);
                rightMotor->moveBackward(100);
            }    
            stop(leftMotor,rightMotor);
            delay(1000);
            resetEncoders(leftMotor,rightMotor);
            correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);
            changingAndCountingPosition(currentY,destinationYX,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            correctedYFlag=1;
            break;
        }
        resetEncoders(leftMotor,rightMotor);
        while(!correctedXFlag && (*currentX!=*(destinationYX+1))){
            while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
                leftMotor->moveBackward(120);
                rightMotor->moveBackward(100);
            }    
            stop(leftMotor,rightMotor);
            delay(1000);
            resetEncoders(leftMotor,rightMotor);
            destinationDirection= futureDirection('x',*currentX,*(destinationYX+1));
            correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);
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

void beginning(LightSensor * lightSensorLeft, LightSensor * lightSensorRight, LightSensor * middleLeftIR,LightSensor * middleRightIR ,LightSensor * backIR, MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * frontalUltrassonic, Ultrassonic * lateralUltrassonic,Bumper * bumper, LDR * ldr){
    Serial.println("to no comeco");
    float closeToUltra = 13;
    bool mustTurn = false;
    bool edge = false;
    int lastSeen = 0;
    bool shelve = false;
    int position[3] = {0,0,0}; //y,x, orientacao respectivamente. Sendo: 0 Norte, 1 Sul, 2 Leste, 3 Oeste


    while(!edge || !lastSeen){ 
        float readingFrontalUltra = frontalUltrassonic->distance_cm();
        int readingBumper = 0;

        while((readingFrontalUltra > closeToUltra && readingFrontalUltra > 0) && !readingBumper){ 
            boucing(leftMotor,rightMotor,lightSensorLeft,lightSensorRight, bumper);
            readingBumper = bumper->checkBumper();
            delay(100);
            readingBumper = bumper->checkBumper();
            readingFrontalUltra = frontalUltrassonic->distance_cm();
    
        }
        
        Serial.println("vi algo!");
        Serial.print("bumper: ");
        Serial.print(readingBumper);
        Serial.print(". Ultra: ");
        Serial.println(readingFrontalUltra);
        
        stop(leftMotor,rightMotor);
        delay(500);
        if (readingBumper){
            Serial.println("vou validar bumper");
            bool seesBumper = checksBumper(bumper,leftMotor,rightMotor);
            if(seesBumper){
                // Serial.print("senti bumper ");
                // Serial.println(readingBumper);
                stop(leftMotor,rightMotor);
                delay(500);
                align(middleLeftIR,middleRightIR,leftMotor,rightMotor,80);
                move_cm(5,BACKWARD,leftMotor,rightMotor); 
                stop(leftMotor,rightMotor);
                delay(500);
            
                shelve = checksUltrassonic(frontalUltrassonic, lateralUltrassonic,leftMotor,rightMotor);
                Serial.println("to aq apos shelve");

                if (edge){
                    if(shelve){
                        // Serial.println("estou na quina 1.7, pois vi borda/borda/prateleira");
                        position[0] = 1;
                        position[1] = 7;
                        position[3] = 2;
                        break;

                    } else {
                        position[0] = 6;
                        position[1] = greenEdge(leftMotor,rightMotor,lightSensorLeft,lightSensorRight,middleLeftIR,middleRightIR,ldr);
                        //ou está em 6.7 ou em 6.1
                        break;
                    }

                } else{
                    edge = true;

                    if (shelve){
                        // Serial.println("estou na quina 1.7, pois vi prateleira/borda");
                        position[0] = 1;
                        position[1] = 7;
                        position[2] = 2;
                        break;

                    } else {
                        // edge = true;
                        mustTurn = true;
                    }
                }
            }
        } else if (readingFrontalUltra<=closeToUltra && readingFrontalUltra > 0){ //viu objeto
            readingFrontalUltra = frontalUltrassonic->distance_cm();
            Serial.print(" li com o ultrassom no elseIf ");
            Serial.println(readingFrontalUltra);


            if(readingFrontalUltra<=closeToUltra){ 
                shelve = checksUltrassonic(frontalUltrassonic,lateralUltrassonic,leftMotor,rightMotor);
                Serial.print("na validacao da praleira, li ");
                Serial.println(shelve);

                if (shelve){ 
                    if(edge){
                        // Serial.println("estou na quina 1.1");
                        position[0] = 1;
                        position[1] = 1;
                        break;
                        
                    } else{
                        lastSeen = 1;
                        mustTurn = true;
                    }
                } else { //cubo
                    mustTurn = true;
                }      
            }
        }
        if (mustTurn){

            stop(leftMotor,rightMotor);
            delay(500);
            resetEncoders(leftMotor,rightMotor);

            move_cm(5,BACKWARD,leftMotor,rightMotor);
  
            stop(leftMotor,rightMotor);
            delay(500);
            rotates(RIGHT,leftMotor, rightMotor);
            stop(leftMotor,rightMotor);
            delay(800);

            leftMotor->moveForward(80);
            rightMotor->moveForward(60);       
            Serial.print("Esq DIr");
            Serial.print(middleLeftIR->read());
            Serial.print(" ");
            Serial.println(middleRightIR->read());

            while(middleRightIR->read() < 300 || middleRightIR->read() < 300){//middleIR->read()
                leftMotor->moveForward(80);
                rightMotor->moveForward(60);       
                Serial.print("Esq DIr");
                Serial.print(middleLeftIR->read());
                Serial.print(" ");
                Serial.println(middleRightIR->read());
            } 
            Serial.println("sai do while");

            stop(leftMotor,rightMotor);
            delay(500);
            align(middleLeftIR,middleRightIR,leftMotor,rightMotor,70,backIR);
            Serial.println("terminei de alinhar");

            resetEncoders(leftMotor,rightMotor);
            mustTurn = false;
        }
    //     } else {
    //         boucing(leftMotor,rightMotor,lightSensorLeft,lightSensorRight);
    //     }
    // }
    
    // stop(leftMotor,rightMotor);
    // Serial.print(lastSeen);
    // Serial.print(" ");
    // Serial.println(edge);

    }
    Serial.print("estou na: ");
    Serial.print(position[0]);
    Serial.print(".");
    Serial.print(position[1]);
    

    repositionBeginning(position[0],position[1],position[2],leftMotor,rightMotor,middleLeftIR,middleRightIR, backIR);

    

}
    

    
    
    
