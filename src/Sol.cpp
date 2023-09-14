#include<Sol.h>

int blocosSemCubos[]={55,56,53};

int smallPosition=0;
int closestBlock[2];
int squareBlocks [][2]={ {22,1},{23,1},      {25,0},{26,1},
                                {52,2},{53,0},      {55,1},{56,1}
    };

int manhattamDistance(int y1,int x1,int y2,int x2){
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
    int tam = 8;
    if(cross){
        coordinatesPtr = *crossBlocks;
        tam=6;
    }
    else{
        coordinatesPtr = *areasBlocks;
        tam=8;
    }
    
    static int closest[2];
    while(tam){
        int distance = manhattamDistance(y,x,*coordinatesPtr,*(coordinatesPtr+1));
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


SOL::Direcao futureDirection(char axis,int start, int final){
       
        if(axis =='y'){
            if(final<=start){
            return  SOL::Norte;
            }
            return  SOL::Sul;
        }
        if(final>start){
            return  SOL::Leste;
        }
        //estou na direita e ele na esquerda 
        return  SOL::Oeste;              
}

int* bestBlock(int currentY,int currentX){
    int lowest =90;
    int indice=0;
    smallPosition=0;
    *closestBlock=0;
    *(closestBlock+1)=0;
    for(int *block:squareBlocks){
        int yBlock = (int)(*block/10);
        int xBlock = (int)(*(block)%10);
        int distance = manhattamDistance(currentY,currentX,yBlock,xBlock);  
        //aqui entra a função da camera e retorna a quantidade de blocos
        /*
            int quantBlocos = 
        */
        if(distance<lowest && *(block+1)>=1){
            lowest=distance;
            closestBlock[0]=yBlock;
            closestBlock[1]=xBlock;
            smallPosition=indice;
        }
        indice++;
    }
    
    squareBlocks[smallPosition][1]=(squareBlocks[smallPosition][1])-1;
    return closestBlock;
}

void stateMachine(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
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

    }
    else{
        stop(leftMotor,rightMotor);
    }
    }
    
    
    
    
}