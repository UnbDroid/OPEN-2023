#include<Sol.h>
static int correctedYFlag = 0;
static int correctedXFlag = 0;
static int blocosSemCubos[]={55,56,53};


int ManhattamDistance(int y1,int x1,int y2,int x2){
    return abs(x1-x2)+abs(y1-y2);
}
int a(int a[][2]){
    return 0;
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
    int tam = 8;
    if(cross){
        coordinatesPtr = *crossBlocks;
        tam=6;
    }
    else{
        Serial.println("eu entrei aqui cara");
        coordinatesPtr = *areasBlocks;
        tam=8;
    }
    
    static int closest[2];
    while(tam){
        int distance = ManhattamDistance(y,x,*coordinatesPtr,*(coordinatesPtr+1));
        if(distance<lowest){
            lowest = distance; 
            
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

    
    int yDestino =*destinationYX;
    int xDestino = *(destinationYX+1);
    int arrayPosicaoAtual[]={yDestino,xDestino};
    if(*currentX!=xDestino || *currentY !=yDestino){
        while(*currentX!=xDestino || *currentY !=yDestino){
            if((*currentY >=5 && yDestino>=5)  || (*currentY <=2  && xDestino<=2)){
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


static int posicaoComCubos[]={
22,23,25,26,31,34,37,41,44,47,52,53,55,56
};
bool temCubo(){
    return true;
}    

void  maquinaDeEstados(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    static int state=0;
    delay(2000);
    while (true)
    {
        if(state==0){
        delay(1000);
        Serial.print("ATUAL ");
        Serial.print(*y);
        Serial.print(" ");
        Serial.println(*x);
        Serial.print("bloco mais próximo ");
        int * destinationYX =  shortestArea(0,*y,*x);

        
        Serial.print(*destinationYX);
        Serial.print(" ");  
        Serial.println(*(destinationYX+1));
        moveTo(x,y,destinationYX,currentDirection,lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
        if(!temCubo){

        }

    }
    else{
        stop(leftMotor,rightMotor);
    }
    }
    
    
    
    
}