#include<Solution.h>
#include<Move.h>
#include<Rasp.h>
#include<PickCube.h>
#include <Bumper.h>

static int state=0;
char typeOfBlock=2;
int smallPosition=0;
int closestBlock[2];
int indexShelf;
int squareBlocks [][2]={ {22,0},{23,0},      {25,0},{26,0},
                        {52,0},{53,0},      {55,1},{56,1}
    };
                                    //  g7 0 ,d4 3,a1 6   h8 1,e5 4 ,b2 7  i9 3 ,f6 6 ,c3 8
static int deliveryLocations[][2][2]={  {{11,1},{15,1}},{{12,1},{16,1}},{{13,1},{17,1}},
                                        {{11,1},{15,1}},{{12,1},{16,1}},{{13,1},{17,1}},
                                        {{11,1},{15,1}},{{12,1},{16,1}},{{13,1},{17,1}},

                                    //    Verde 9            Azul 10           Amarelo 11       Vermelho 12
                                    {{61,1},{67,1}},    {{62,1},{66,1}},    {{63,1},{65,1}},    {{64,1},{64,1}}
                            };
//rgby -wxyz 
int * deliveryPlace(int y,int x,char blockType){
    int lowest =90;    
    int *coordinatesPtr;
    switch (blockType)
    {
    case 'g':
        indexShelf=0;
        break;
    case '7': 
        indexShelf=0;
        break;   
    case '1':
        indexShelf=6;
        break;
    case 'a':
        indexShelf=6;
        break;
    case '2':
        indexShelf=7;
        break;
    case 'b':
        indexShelf=7;
        break;
    case '3':
        indexShelf=9;
        break;
    case '4':
        indexShelf=3;
        break;
    case 'd':
        indexShelf=3;
        break;
    case '5':
        indexShelf=4;
        break;
    case 'e':
        indexShelf=4;
        break;
    case '6':
        indexShelf=6;
        break;
    case 'f':
        indexShelf=6;
        break;
    case '8':
        indexShelf=1;
        break;
    case 'h':
        indexShelf=1;
        break;
    case '9':
        indexShelf=2;
        break;
    case 'i':
        indexShelf=2;
        break;    
    case 'w':
        //red
        indexShelf=12;
        break;   
    case 'x':
        //green
        indexShelf=9;
        break;
    case 'y':
        //blue
        indexShelf=10;
        break;
    case 'z':
        //yellow
        indexShelf=11;
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

void stateMachine(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,Claw*robotClaw, Forklift * forkLift, Ultrassonic * lateralUltrassonic,Ultrassonic*frontalUltrassonic){
    int destination[2];
    int *best = bestBlock(*y,*x);
    forkLift->forklift_up_steps(0,1);
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
            
            correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);
            int numberOfBlocks=2;
            //aqui entra a função da camera que retorna a quantidade de blocos
            /*
                int numberOfBlocks = 2
                squareBlocks[smallPosition][1]=numberOfBlocks;     
            */
            squareBlocks[smallPosition][1]=(squareBlocks[smallPosition][1])-1;
            delay(3000);
            

            if(numberOfBlocks>0){
                state=1;
            }
            else{
                state=0;
            }
        }
        if(state==1){
            
            pick_cube_from_right(leftMotor,rightMotor,lateralUltrassonic,lightSensorRight,frontalUltrassonic,robotClaw,forkLift);
            //typeOfBlock= return_type_of_cube();
            typeOfBlock='d';
            int forkDestiny=1;
            if(typeOfBlock=='g'||typeOfBlock=='7'||typeOfBlock=='h'||typeOfBlock=='8'||typeOfBlock=='i'||typeOfBlock=='9'){
                forkLift->forklift_up_steps(0,3);
                forkDestiny=3;
            }
            else if(typeOfBlock=='d'||typeOfBlock=='4'||typeOfBlock=='e'||typeOfBlock=='5'||typeOfBlock=='f'||typeOfBlock=='6'){
                forkLift->forklift_up_steps(0,2);
                forkDestiny=2;
            }
            int* ptrDelivery = deliveryPlace(*y,*x,typeOfBlock);
            destination[0]=*(ptrDelivery);
            destination[1]=*(ptrDelivery+1);
            if(destination[0]==1){
                destination[0]=2;
                moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
                SOL::Direcao destinationDirection=SOL::Norte;
                resetEncoders(leftMotor,rightMotor);
                
            while(rightMotor->getEncoder()<=450||leftMotor->getEncoder()<=450){
                leftMotor->moveBackward(100);
                rightMotor->moveBackward(80);
            }    
            stop(leftMotor,rightMotor);
            resetEncoders(leftMotor,rightMotor);
            delay(500);
            correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);
            resetEncoders(leftMotor,rightMotor);
            while(rightMotor->getEncoder()<=500||leftMotor->getEncoder()<=500){
                leftMotor->moveBackward(100);
                rightMotor->moveBackward(80);
            }    
            stop(leftMotor,rightMotor);
            resetEncoders(leftMotor,rightMotor);
            while(!(lightSensorLeft->read()>=150 && lightSensorRight->read()>=150)){
                Serial.println(lightSensorLeft->read());
                leftMotor->moveForward(100);
                rightMotor->moveForward(80);
            }
            stop(leftMotor,rightMotor);
            delay(500);
            resetEncoders(leftMotor,rightMotor);
            while(leftMotor->getEncoder()<1313&&rightMotor->getEncoder()<1283){
                    leftMotor->moveForward(100);
                    rightMotor->moveForward(80);
            }
            stop(leftMotor,rightMotor);
            robotClaw->open_claw_with_cube();
            delay(500);
            resetEncoders(leftMotor,rightMotor);
            while(leftMotor->getEncoder()<1313&&rightMotor->getEncoder()<1283){
                    leftMotor->moveBackward(100);
                    rightMotor->moveBackward(80);
            }
            stop(leftMotor,rightMotor);
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
                correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);
                while(lightSensorLeft->read()<=60 ||lightSensorRight->read()<=60){
                    leftMotor->moveForward(100);
                    rightMotor->moveForward(80);
                }
                stop(leftMotor,rightMotor);
                delay(500);
                robotClaw->open_claw_with_cube();
            }
        
        if(forkDestiny!=1){
            forkLift->forklift_up_steps(forkDestiny,1);
        }
        best = bestBlock(*y,*x);
        state=0;
        typeOfBlock++;
        }
    }
    Serial.println("nao existe mais blocos para serem pegos");
    stop(leftMotor,rightMotor);
}
    

int greenEdge(MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * lightSensorLeft, LightSensor * lightSensorRight){
    int white = 100;
    int coord = 0;
    Serial.println("checando em qual verde to");
    
    // int leftValue = lightSensorLeft->read();
    // int rightValue = lightSensorRight->read();
    stop(leftMotor,rightMotor);
    delay(500);
    rotates(RIGHT,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    resetEncoders(leftMotor,rightMotor);
    // while (leftMotor->getEncoder() < 1000 && rightMotor->getEncoder() < 1000)
    // {
    //     leftMotor->moveForward(100);
    //     rightMotor->moveForward(80);
    // }
    move_cm(10,FORWARD,leftMotor,rightMotor);
    
    stop(leftMotor,rightMotor);
    delay(500);

    int leftValue = lightSensorLeft->read();
    int rightValue = lightSensorRight->read();
    
    if ( rightValue > white){
        coord = 7;        
    } else {
        coord = 1;
    }

    Serial.print("estou na ponta 6.");
    Serial.println(coord);
    return coord;
    
    
}

bool checksBumper(Bumper * bumper){
    int bumperValue = 0;
    bool seesBumper = false;

    for (int i = 0; i < 100; i++)
    {
        bumperValue = bumperValue+ bumper->checkBumper();    
    }
    Serial.print("validei bumper e li: ");
    Serial.println(bumperValue);
    if(bumperValue >= 90){
        seesBumper = true;
    }

    return seesBumper;  
}

bool checksUltrassonic (Ultrassonic * frontalUltrassonic, Ultrassonic * lateralUltrassonic, MotorDC * leftMotor, MotorDC * rightMotor){
    bool seesSomething = false;
    float closeToUltra = 20;
    // resetEncoders(leftMotor,rightMotor);
    // while(leftMotor->getEncoder()<400 && rightMotor->getEncoder()<400){
    //     leftMotor->moveBackward(80);
    //     rightMotor->moveBackward(60);
    // }
    stop(leftMotor,rightMotor);
    delay(500);
    move_cm(5,BACKWARD,leftMotor,rightMotor);

    stop(leftMotor,rightMotor);
    delay(500);
    rotates(LEFT,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    int readingUltraLateral = lateralUltrassonic->distance_cm();
    int readingUltraFrontal = frontalUltrassonic->distance_cm();

    Serial.print("as leituras  dos ultra frontal/lateral: ");
    Serial.print(readingUltraFrontal);
    Serial.print(" ");
    Serial.println(readingUltraLateral);

    if (readingUltraLateral <= closeToUltra || readingUltraFrontal <= closeToUltra){
        seesSomething = true;
    }

    stop(leftMotor,rightMotor);
    delay(500);
    rotates(RIGHT,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    move_cm(5,FORWARD,leftMotor,rightMotor);


    stop(leftMotor,rightMotor);
    delay(500);
    Serial.println("checagem com o ultrassom");
    Serial.print("checando ultra lateral, li: ");
    Serial.print(readingUltraLateral);
    Serial.println(" checando ultra frontal, li: ");
    Serial.print(readingUltraFrontal);
    Serial.print(" depois eu li: ");
    Serial.println(seesSomething);

    return seesSomething;
}

