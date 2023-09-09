#include<Sol.h>
static int correctedYFlag = 0;
static int correctedXFlag = 0;


int ManhattamDistance(int y1,int x1,int y2,int x2){
    return abs(x1-x2)+abs(y1-y2);
}
int * shortestArea(bool cross,int y,int x){
    int lowest =90;
    int areasBlocks[8][2]={ {2,2},{2,3},     {2,5},{2,6},


                            {5,2},{5,3},     {5,5},{5,6}
    };
    int crossBlocks[6][2]={{2,1},    {2,4},  {2,7},
    
    
                           {5,1},   {5,4},  {5,7} 
    };
    int *coordinatesPtr;
    if(cross){
        coordinatesPtr = *crossBlocks;
    }
    else{
        coordinatesPtr = *areasBlocks;
    }
    int tam = 8;
    static int closest[2];
    while(tam-2){
        int distance = ManhattamDistance(y,x,*coordinatesPtr,*(coordinatesPtr+1));
        if(distance<lowest){
            lowest = distance; 
            // Serial.print(*coordinatesPtr);
            // Serial.print(" ");
            // Serial.println(*(coordinatesPtr+1));
            closest[0]=*coordinatesPtr;
            closest[1]=*(coordinatesPtr+1);
        }
        coordinatesPtr++;
        coordinatesPtr++;
        tam--;
    }
    return closest;
}


SOL::Direcao futureDirection(char eixo,int inicial, int final){
       
        if(eixo =='y'){
            if(final<=inicial){
            return  SOL::Norte;
            }
            return  SOL::Sul;
        }
        if(final>inicial){
            return  SOL::Leste;
        }
        //estou na direita e ele na esquerda 
        return  SOL::Oeste;          
        
}
void changingAndCountingPosition(int * current ,int *destination,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    if(*current<*destination){
        while(*current<*destination){
            Serial.print(" Valor Aí :");
            Serial.println(*current);
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
void moveYandMoveX(int *currentX,int *currentY,int *destinationYX, int * currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    SOL::Direcao destinationDirection= futureDirection('y',*currentY,*destinationYX);
        leftMotor->setEncoder(0);
        rightMotor->setEncoder(0);
        while(!correctedYFlag &&(*currentY!=*destinationYX)){
            while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
                leftMotor->moveBackward(100);
                rightMotor->moveBackward(80);
                Serial.println(leftMotor->getEncoder());
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
                leftMotor->moveBackward(100);
                rightMotor->moveBackward(80);
                Serial.println(leftMotor->getEncoder());
            }    
            stop(leftMotor,rightMotor);
            delay(1000);
            leftMotor->setEncoder(0);
            rightMotor->setEncoder(0);
            destinationDirection= futureDirection('x',*currentX,*(destinationYX+1));
            while(*currentDirection !=destinationDirection){
                Serial.print(" x: ");
                Serial.println(*currentX);
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
    //if ele não precisa atravessar:
    while(*currentX!=*(destinationYX+1) && *currentY !=*destinationYX){
        if((*currentY >=5 && *destinationYX>=5)  || (*currentY <=2  && *destinationYX<=2)){
        moveYandMoveX(currentX,currentY,destinationYX,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        }
        else{
            Serial.println("to aqui");
            int * lowestCrossBlock = shortestArea(true,*currentY,*currentX);
            Serial.print(*lowestCrossBlock);
            Serial.print(*(lowestCrossBlock+1));
            moveYandMoveX(currentX,currentY,lowestCrossBlock,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            // rightMotor->moveBackward(100);
            // leftMotor->moveBackward(80);
            // delay(500);
            // stop(leftMotor,rightMotor);
            // delay(1000);
            if(*lowestCrossBlock==5){
                *lowestCrossBlock =2;
                moveYandMoveX(currentX,currentY,lowestCrossBlock,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);    
            }
            else{
                *lowestCrossBlock =5;
                moveYandMoveX(currentX,currentY,lowestCrossBlock,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            }
            // stop(leftMotor,rightMotor);
            // rightMotor->moveBackward(100);
            // leftMotor->moveBackward(80);
            // delay(500);
            // stop(leftMotor,rightMotor);
        }
    }
         
}


    
    

void maquinaDeEstados(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
       
    int * destinationYX =  shortestArea(1,*y,*x);
    *destinationYX=1;
    *(destinationYX+1)=6;  
    moveTo(x,y,destinationYX,currentDirection,lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
    
    Serial.println("terminei");
    *destinationYX=6;
    *(destinationYX+1)=7;
    moveTo(x,y,destinationYX,currentDirection,lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    
}