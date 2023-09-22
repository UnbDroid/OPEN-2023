#include<Solution.h>
#include<Move.h>


static int state=0;
int typeOfBlock=2;
int smallPosition=0;
int closestBlock[2];
int indexShelf;
int squareBlocks [][2]={ {22,1},{23,1},      {25,0},{26,0},
                        {52,0},{53,0},      {55,1},{56,0}
    };
                                    //  g7 0 ,d4 3,a1 6   h8 2,e5 4 ,b2 7  i9 3 ,f6 6 ,c3 8
static int deliveryLocations[][2][2]={  {{11,1},{15,1}},{{12,1},{16,1}},{{13,1},{17,1}},
                                        {{11,1},{15,1}},{{12,1},{16,1}},{{13,1},{17,1}},
                                        {{11,1},{15,1}},{{12,1},{16,1}},{{13,1},{17,1}},

                                    //    Verde 9            Azul 10           Amarelo 11       Vermelho 12
                                    {{61,1},{67,1}},    {{62,1},{66,1}},    {{63,1},{65,1}},    {{64,2}}
                            };

int * deliveryPlace(int y,int x,int blockType){
    int lowest =90;    
    int *coordinatesPtr;
    switch (blockType)
    {
    case 3:
        indexShelf=11;
        break;
    case 2:
        indexShelf=9;
        break;
    case 5:
        indexShelf=0;
        break;
    default:
        break;
    }
    
    int index=0;
    smallPosition=0;
    *closestBlock=0;
    *(closestBlock+1)=0;
    int * block = *deliveryLocations[indexShelf];
    int size = 2;
    while(size){
        int yBlock = (int)(*block/10);
        int xBlock = (int)(*(block)%10);
        int distance = manhattamDistance(y,x,yBlock,xBlock); 
        if(distance<lowest && ((deliveryLocations[indexShelf][index][1])==1)){
            lowest=distance;
            closestBlock[0]=yBlock;
            closestBlock[1]=xBlock;
            smallPosition=index;
        }
        block++;
        block++;
        index++;
        size--;
    }
    deliveryLocations[indexShelf][smallPosition][1]=(deliveryLocations[indexShelf][smallPosition][1])-1;  
    return closestBlock;
}

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

int*  bestBlock(int currentY,int currentX){
    int lowest =90;
    int indice=0;
    smallPosition=0;
    *closestBlock=0;
    *(closestBlock+1)=0;
    for(int *block:squareBlocks){
        int yBlock = (int)(*block/10);
        int xBlock = (int)(*(block)%10);
        int distance = manhattamDistance(currentY,currentX,yBlock,xBlock);  
        if(distance<lowest && *(block+1)>=1){
            lowest=distance;
            closestBlock[0]=yBlock;
            closestBlock[1]=xBlock;
            smallPosition=indice;
        }
        indice++;
    }
    //Serial.print(*closestBlock);
    //Serial.print(" ");
    //Serial.println(*(closestBlock+1));
    return closestBlock;
}

void stateMachine(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,Claw*robotClaw, Forklift * forkLift){
    int destination[2];
    delay(3000);
    int *best = bestBlock(*y,*x);
    //Serial.print("to no inicio ");
    while(*best!=0){
        if(state==0){
            destination[0]=*best;
            destination[1]=*(best+1);
            SOL::Direcao destinationDirection;
            moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            resetEncoders(leftMotor,rightMotor);
            while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
                leftMotor->moveBackward(100);
                rightMotor->moveBackward(80);
            }    
            stop(leftMotor,rightMotor);
            resetEncoders(leftMotor,rightMotor);
            delay(1000);
            
            
            if(*y==5){
                destinationDirection=SOL::Norte;
            }
            else if(*y==2){
                destinationDirection=SOL::Sul;
            }
            
            while(*currentDirection!=destinationDirection){       
                    correctingDirection(currentDirection,leftMotor,rightMotor);
                    delay(1000);
            }
            int numberOfBlocks=2;
            //aqui entra a função da camera que retorna a quantidade de blocos
            /*
                int numberOfBlocks = 2
                squareBlocks[smallPosition][1]=numberOfBlocks;     
            */
            squareBlocks[smallPosition][1]=(squareBlocks[smallPosition][1])-1;
            delay(3000);
            robotClaw->close_claw_with_cube();

            if(numberOfBlocks>0){
                state=1;
            }
            else{
                state=0;
            }
        }
        if(state==1){
            Serial.println("eu entrei aqui");
            /*
            a ideia é a camera colocar o valor nessa variável typeOfBlock    
            */
            
            int* ptrDelivery = deliveryPlace(*y,*x,typeOfBlock);
            destination[0]=*(ptrDelivery);
            destination[1]=*(ptrDelivery+1);
            Serial.print("Local de Entrega: ");
            Serial.print(*destination);
            Serial.println(*(destination+1));
            if(destination[0]==1){
                destination[0]=2;
                //ja levantar a garra aqui a depender do tipo de bloco
                moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            }
            else if (destination[0]==6){
                moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
                resetEncoders(leftMotor,rightMotor);
                while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
                    leftMotor->moveBackward(100);
                    rightMotor->moveBackward(80);
                }    
                stop(leftMotor,rightMotor);
                resetEncoders(leftMotor,rightMotor);
                delay(1000);
                SOL::Direcao destinationDirection=SOL::Sul;
                while(*currentDirection!=destinationDirection){       
                    correctingDirection(currentDirection,leftMotor,rightMotor);
                    delay(1000);
                }
            }
            robotClaw->open_claw_with_cube();
        best = bestBlock(*y,*x);
        state=0;
        typeOfBlock++;
        }
    }
    Serial.println("nao existe mais blocos para serem pegos");
    stop(leftMotor,rightMotor);
}
    
    
    
    
