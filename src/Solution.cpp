#include<Solution.h>
#include<Move.h>

int blocosSemCubos[]={55,56,53};

int smallPosition=0;
int closestBlock[2];
int squareBlocks [][2]={ {22,1},{23,1},      {25,0},{26,0},
                        {52,0},{53,0},      {55,0},{56,0}
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
    Serial.print(*closestBlock);
    Serial.print(" ");
    Serial.println(*(closestBlock+1));
    squareBlocks[smallPosition][1]=(squareBlocks[smallPosition][1])-1;
    return closestBlock;
}
static int state=0;
void stateMachine(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    int destination[2];
    delay(3000);
    int *best = bestBlock(*y,*x);
    while(*best!=0){
        if(state==0){
        destination[0]=*best;
        destination[1]=*(best+1);

        moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            *y= *best;
            *x = *(best+1);
            state=1;
        }
        if(state==1){
            //vou deixar pra ele entregar em um lugar só por enquanto
            //mas a ideia é ter uma função que identifica o bloco e manda o lugar
            destination[0]=1;
            destination[1]=2;
            *y =1;
            *x=2;
            
            moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
        }
        best = bestBlock(*y,*x);
        state=0;
        
    }
    Serial.println("nao existe mais blocos para serem pegos");
    stop(leftMotor,rightMotor);
    
}
    
    
    
    
