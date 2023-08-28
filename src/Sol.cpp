#include<Sol.h>
static int correctedYFlag = 0;
static int correctedXFlag = 0;


int ManhattamDistance(int y1,int x1,int y2,int x2){
    return abs(x1-x2)+abs(y1-y2);
}
int * shortestArea(int notCross,int y,int x){
    int lowest =90;
    int areasBlocks[8][2]={ {2,2},{2,3},     {2,5},{2,6},


                            {5,2},{5,3},     {5,5},{5,6}
    };
    int crossBlocks[][2]={{2,1},    {2,4},  {2,7},
    
    
                           {5,1},   {5,4},  {5,7} 
    };
    int *coordinatesPtr;
    if(notCross){
        coordinatesPtr = *areasBlocks;
    }
    else{
        coordinatesPtr = *crossBlocks;
    }
    int tam = 8;
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
}
void moveYandMoveX(int *currentX,int *currentY,int *destinationYX, int * currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    SOL::Direcao destinationDirection= futureDirection('y',*currentY,*destinationYX);
        while(!correctedYFlag &&*currentY!=*destinationYX ){
            while(*currentDirection!=destinationDirection){
                correctingDirection(currentDirection,leftMotor,rightMotor);
            }
            stop(leftMotor,rightMotor);    
            changingAndCountingPosition(currentY,destinationYX,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            correctedYFlag=1;
            break;
        }
        while(!correctedXFlag && *currentX<*(destinationYX+1)){
            destinationDirection= futureDirection('x',*currentX,*(destinationYX+1));
            while(*currentDirection !=destinationDirection){
                correctingDirection(currentDirection,leftMotor,rightMotor);
            }
            stop(leftMotor,rightMotor);
            changingAndCountingPosition(currentX,destinationYX+1,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            break;
        }
}

void moveTo(int * currentX,int *currentY,int *destinationYX,int *currentDirection, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    //if ele não precisa atravessar:
    if((*currentY && *destinationYX) >=5 || (*currentY && *destinationYX)<=2){
        moveYandMoveX(currentX,currentY,destinationYX,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
    }
    
        // int * lowestCrossBlock = shortestArea(0,*currentX,*currentY);
        // SOL::Direcao destinationDirection= futureDirection('y',*currentY,*lowestCrossBlock);
        // while(!correctedYFlag &&*currentY!=*lowestCrossBlock ){
        //     while(*currentDirection!=destinationDirection){
        //         correctingDirection(currentDirection,leftMotor,rightMotor);
        //     }
        //     stop(leftMotor,rightMotor);    
        //     changingAndCountingPosition(currentY,lowestCrossBlock,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        //     correctedYFlag=1;
        //     break;
        // }
        // while(!correctedXFlag && *currentX<*(lowestCrossBlock+1)){
        //     destinationDirection= futureDirection('x',*currentX,*(lowestCrossBlock+1));
        //     while(*currentDirection !=destinationDirection){
        //         correctingDirection(currentDirection,leftMotor,rightMotor);
        //     }
        //     stop(leftMotor,rightMotor);
        //     changingAndCountingPosition(currentX,lowestCrossBlock+1,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        //     break;
        
        
    }
    
    

void maquinaDeEstados(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
       
    int * destinationYX =  shortestArea(1,*y,*x);
    *destinationYX=4;
    *(destinationYX+1)=4;   
        
    moveTo(x,y,destinationYX,currentDirection,lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
    
}