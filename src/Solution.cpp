#include<Solution.h>
#include<Move.h>
#include<Rasp.h>
#include<PickCube.h>
#include <Bumper.h>
#include <LDR.h>

static int state=0;
char typeOfBlock=2;
int smallPosition=0;
int closestBlock[2];
int indexShelf;
int squareBlocks [][2]={ {22,1},{23,1},      {25,1},{26,1},
                        {52,1},{53,1},      {55,1},{56,1}
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
            if(final<start){
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

void stateMachine(int* y,int* x,int *currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor,Claw*robotClaw, Forklift * forkLift, Ultrassonic * lateralUltrassonic,Ultrassonic*frontalUltrassonic,LightSensor * middleSensor,LightSensor*backIr,LightSensor* middleSensorLeft, Bumper * bumper){
    int destination[2];
    int *best = bestBlock(*y,*x);
    
    robotClaw->open_claw_entirely();
    while(*best!=0){
        if(state==0){
            destination[0]=*best;
            destination[1]=*(best+1);
            SOL::Direcao destinationDirection;
            moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor,middleSensor,backIr,middleSensorLeft);
            resetEncoders(leftMotor,rightMotor);

            while(backIr->read()<250){
                leftMotor->moveBackward(80);
                rightMotor->moveBackward(60);
            }
            stop(leftMotor,rightMotor);
            delay(500);

        
            if(*y==5){
                destinationDirection=SOL::Norte;
            }
            else if(*y==2){
                destinationDirection=SOL::Sul;
            }
            
            correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);

            
            //aqui entra a função da camera que retorna a quantidade de blocos
            /*
                int numberOfBlocks = 2
                squareBlocks[smallPosition][1]=numberOfBlocks;     
            */
            move_cm(3,BACKWARD,leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
            delay(500);
            // int numberOfBlocks = return_count_of_cubes();
            int numberOfBlocks = 2;
            squareBlocks[smallPosition][1]=(squareBlocks[smallPosition][1])-1;

            //move_cm(3,FORWARD,leftMotor,rightMotor);
            //stop(leftMotor,rightMotor);
            //delay(500);


            if(numberOfBlocks>0){
                state=1;
            }
            else{
                state=0;
            }
        }
        if(state==1){
            

            typeOfBlock= pick_cube_from_right(leftMotor,rightMotor,lateralUltrassonic,frontalUltrassonic,robotClaw,forkLift, middleSensor, middleSensorLeft, lightSensorRight, lightSensorLeft);
            
            while(middleSensor->read()<100){
                leftMotor->moveBackward(80);
                rightMotor->moveBackward(60);
            }
            stop(leftMotor,rightMotor);
            delay(500);

            move_cm(2,BACKWARD,leftMotor,rightMotor);
            while(backIr->read()<200){
                leftMotor->moveBackward(90);
                rightMotor->moveBackward(70);
            }
            stop(leftMotor,rightMotor);
            delay(500);
            resetEncoders(leftMotor,rightMotor);
            if((*y==2&&*x==5)||(*y==2&&*x==6)||(*y==5&&*x==2)||(*y==5&&*x==3)){
                int direcaoDestino;
                if(*y==5){
                    *currentDirection=SOL::Oeste;
                    //direcaoDestino=SOL::Oeste;
                    //correctDirection(currentDirection,*destination,leftMotor,rightMotor);
                    rotates(LEFT,leftMotor,rightMotor);
                    *x= 1; 
                }
                else{
                    *currentDirection=SOL::Leste;
                    //direcaoDestino=SOL::Leste;
                    Serial.println("estou aqui");
                    rotates(LEFT,leftMotor,rightMotor);
                    //correctDirection(currentDirection,*destination,leftMotor,rightMotor);
                    *x=7;
                }
            }

            else{
                int direcaoDestino;
                if(*y==5){
                    *currentDirection=SOL::Leste;
                    rotates(RIGHT,leftMotor,rightMotor);
                    //correctDirection(currentDirection,*destination,leftMotor,rightMotor);
                    *x= 7; 
                }
                else{
                    *currentDirection=SOL::Oeste;
                    //direcaoDestino=SOL::Oeste;
                    //correctDirection(currentDirection,*destination,leftMotor,rightMotor);
                    rotates(RIGHT,leftMotor,rightMotor);
                    *x=1;
                }
            }
            stop(leftMotor,rightMotor);
            delay(500);
            while(!bumper->checkBumper()){
                boucing(leftMotor,rightMotor,lightSensorLeft,lightSensorRight,middleSensorLeft,middleSensor,bumper);
            }
            stop(leftMotor,rightMotor);
            delay(500);
            
            int forkDestiny=1;
            if(typeOfBlock=='0'){
                typeOfBlock='g';
            }
            if(typeOfBlock=='g'||typeOfBlock=='7'||typeOfBlock=='h'||typeOfBlock=='8'||typeOfBlock=='i'||typeOfBlock=='9'){
                forkLift->forklift_up_steps(2,3);
                forkDestiny=3;
            }
            else if(typeOfBlock=='d'||typeOfBlock=='4'||typeOfBlock=='e'||typeOfBlock=='5'||typeOfBlock=='f'||typeOfBlock=='6'){
                forkDestiny=2;
            }
            else{
                forkDestiny=1;
            }
            int* ptrDelivery = deliveryPlace(*y,*x,typeOfBlock);
            destination[0]=*(ptrDelivery);
            destination[1]=*(ptrDelivery+1);
            if(destination[0]==1){
                destination[0]=2;
                moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor,middleSensor,backIr,middleSensorLeft);
                SOL::Direcao destinationDirection=SOL::Norte;
                resetEncoders(leftMotor,rightMotor);

                while(backIr->read()<80){
                    leftMotor->moveBackward(80);
                    rightMotor->moveBackward(60);
                }    
                stop(leftMotor,rightMotor);
                delay(500);
                resetEncoders(leftMotor,rightMotor);
                
                correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);
                resetEncoders(leftMotor,rightMotor);
                    
                stop(leftMotor,rightMotor);
                delay(500);
                resetEncoders(leftMotor,rightMotor);
                //move_cm(2,BACKWARD,leftMotor,rightMotor);
                //stop(leftMotor,rightMotor);
                //delay(500);
                while(backIr->read() < 200){
                    //Serial.println(lightSensorLeft->read());
                    //leftMotor->moveForward(100);
                    //rightMotor->moveForward(80);
                    boucing(leftMotor,rightMotor,lightSensorLeft,lightSensorRight,middleSensorLeft,middleSensor);
                }
                stop(leftMotor,rightMotor);
                delay(500);
                resetEncoders(leftMotor,rightMotor);
                long startTime = millis();
                long loopDuration = 2000;

                while(millis() - startTime < loopDuration){
                    boucing(leftMotor,rightMotor,lightSensorLeft,lightSensorRight,middleSensorLeft,middleSensor);
                }
                stop(leftMotor,rightMotor);
                delay(300);
                robotClaw->open_claw_with_cube();
                //indo agr voltar para pegar outro bloco
                while(middleSensor->read()<100){
                    leftMotor->moveBackward(80);
                    rightMotor->moveBackward(60);
                }
                stop(leftMotor,rightMotor);
                delay(500);
            }
            else if (destination[0]==6){
                moveTo(x,y,destination,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor,middleSensor,backIr,middleSensorLeft);
                stop(leftMotor,rightMotor);
                delay(500);
                while(backIr->read()<200){
                    leftMotor->moveBackward(80);
                    rightMotor->moveBackward(60);
                }
                stop(leftMotor,rightMotor);
                resetEncoders(leftMotor,rightMotor);
                delay(500);
                SOL::Direcao destinationDirection=SOL::Sul;
                correctDirection(currentDirection,destinationDirection,leftMotor,rightMotor);
                while(middleSensor->read()<80){
                    boucing(leftMotor,rightMotor,lightSensorLeft,lightSensorRight,middleSensorLeft,middleSensor);
                }
                stop(leftMotor,rightMotor);
                delay(500);
                forkLift->forklift_down_steps(2,0);
                forkDestiny=0;
                robotClaw->open_claw_with_cube();
                *y=6;
            }
        
        if(forkDestiny>2){
            forkLift->forklift_down_steps(forkDestiny,2);
        }
        else{
            forkLift->forklift_up_steps(forkDestiny,2);
        }
        best = bestBlock(*y,*x);
        state=0;
        typeOfBlock++;
        }
    }
    //Serial.println("nao existe mais blocos para serem pegos");
    stop(leftMotor,rightMotor);
}
    

int greenEdge(MotorDC * leftMotor, MotorDC * rightMotor,LightSensor * lightSensorLeft, LightSensor * lightSensorRight,LightSensor * middleLeftIR, LightSensor * middleRightIR, LightSensor * backIR, LDR * Ldr){
    int blue = 28;
    int coord = 0;
    //Serial.println("checando em qual verde to");
    
    // int leftValue = lightSensorLeft->read();
    // int rightValue = lightSensorRight->read();
    stop(leftMotor,rightMotor);
    delay(500);
    //move_cm(7,BACKWARD,leftMotor,rightMotor);
    while(backIR->read() < 350){
        leftMotor->moveBackward(90);
        rightMotor->moveBackward(70);
    }
    //Serial.println("fui p tras");
    stop(leftMotor,rightMotor);
    delay(500);
    rotates(RIGHT,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    while(middleLeftIR->read() < 300){
        leftMotor->moveForward(80);
        rightMotor->moveForward(60);
        //Serial.println(middleLeftIR->read() );
    } 

    stop(leftMotor,rightMotor);
    delay(500);
    align(middleLeftIR,middleRightIR,leftMotor,rightMotor,70,lightSensorLeft,lightSensorRight);
    stop(leftMotor,rightMotor);
    delay(500);

    
    move_cm(10,FORWARD,leftMotor,rightMotor);
    //Serial.println("acabei de ir pra frente");
    
    stop(leftMotor,rightMotor);
    delay(500);

    int LDRread = Ldr->read();
    
    if ( LDRread > blue){
        coord = 7;        
        // move_cm(12,BACKWARD,leftMotor,rightMotor);
    } else {
        coord = 1;
    }

    //Serial.print("estou na ponta 6.");
    //Serial.println(coord);
    return coord;
    
    
}

bool checksBumper(Bumper * bumper, MotorDC * leftMotor, MotorDC * rightMotor){
    int bumperValue = 0;
    bool seesBumper = false;
    stop(leftMotor,rightMotor);
    
    for (int i = 0; i < 3; i++)
    {
        bumperValue = bumperValue+ bumper->checkBumper();    
        delay(150);
    }
   // Serial.print("validei bumper e li: ");
   // Serial.println(bumperValue);
    if(bumperValue >= 2){
        seesBumper = true;
    }

    return seesBumper;  
}

bool checksUltrassonic (Ultrassonic * frontalUltrassonic, Ultrassonic * lateralUltrassonic, MotorDC * leftMotor, MotorDC * rightMotor){
    bool seesSomething = false;
    float closeToUltra = 30;
    // resetEncoders(leftMotor,rightMotor);
    // while(leftMotor->getEncoder()<400 && rightMotor->getEncoder()<400){
    //     leftMotor->moveBackward(80);
    //     rightMotor->moveBackward(60);
    // }
    stopLow(leftMotor,rightMotor);
    delay(500);
    move_cm(11,BACKWARD,leftMotor,rightMotor);

    stop(leftMotor,rightMotor);
    delay(500);
    rotates(LEFT,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    int readingUltraLateral = lateralUltrassonic->distance_cm();
    int readingUltraFrontal = frontalUltrassonic->distance_cm();

    //Serial.print("as leituras  dos ultra frontal/lateral: ");
    //Serial.print(readingUltraFrontal);
    //Serial.print(" ");
    //Serial.println(readingUltraLateral);

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
    /*
    Serial.println("checagem com o ultrassom");
    Serial.print("checando ultra lateral, li: ");
    Serial.print(readingUltraLateral);
    Serial.println(" checando ultra frontal, li: ");
    Serial.print(readingUltraFrontal);
    Serial.print(" depois eu li: ");
    Serial.println(seesSomething);
    */
    return seesSomething;
}

void repositionBeginning(int y, int x, int orientacao, MotorDC * leftMotor, MotorDC * rightMotor, LightSensor * leftIR, LightSensor * rightIR, LightSensor * middleLeftIR,LightSensor * middleRightIR, LightSensor * backIR){
    move_cm(1,BACKWARD,leftMotor,rightMotor);

    if (y == 1){
        if(x== 1){
            //pos 1.1
            rotates(AROUND,leftMotor,rightMotor);
            
        } else {
            //pos 1.7
                rotates(RIGHT,leftMotor,rightMotor);
                stop(leftMotor,rightMotor);
                delay(500);
        }
        //Serial.println("vou p tras");
        move_cm(10,BACKWARD,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        delay(500);
        
        stop(leftMotor,rightMotor);
        delay(500);
        
    } else {
        if(x == 1){
            //pos 6.1
            move_cm(3,leftMotor,rightMotor,leftIR,rightIR,middleRightIR);
        } else {
            //pos 6.7
            move_cm(16.5,BACKWARD,leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
            delay(500);
            //Serial.println("entrei aqui");
            stop(leftMotor,rightMotor);
            delay(500);
            rotates(RIGHT,leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
            delay(500);
            move_cm(15,FORWARD,leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
            delay(500);

        }
    }
    // Serial.print("leituras: ");
    // Serial.print(leftIR->read());
    // Serial.print(" ");
    // Serial.println(rightIR->read());
    while(middleLeftIR->read()<=100 || middleRightIR->read()<=100){ //anda reto ate ver preto com o sensor IR e se alinha
        // Serial.print(leftIR->read());
        // Serial.print(" ");
        // Serial.println(rightIR->read());
        //leftMotor->moveForward(80);
        //rightMotor->moveForward(60);
        boucing(leftMotor,rightMotor,leftIR,rightIR,middleLeftIR,middleRightIR);
    } 

    move_cm(1.5,FORWARD,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);
    align(middleLeftIR,middleRightIR,leftMotor,rightMotor,80);
    stop(leftMotor,rightMotor);
    delay(500);
    
    return;
}

float median(int x, int y, int z){
    float values[3] = {0,0,0};
    if ((x>=y) && (y>=z)) {
        values[0] = z;
        values[1] = y;
        values[2] = x;
    } else if ((x>=y) && (y<=z )&&(z>=x)){
        values[0] = y;
        values[1] = x;
        values[2] = z;
    } else if ((x>=y) && (y<=z )&&(z<=x)){
        values[0] = y;
        values[1] = z;
        values[2] = x;
    } else if ((x<=y) && (y>=z) && (z >= x)){
        values[0] = x;
        values[1] = z;
        values[2] = y;
    } else if ((x<=y) && (y>=z) && (z <= x)){
        values[0] = z;
        values[1] = x;
        values[2] = y;
    } else if((x<=y) && (y<=z)){
        values[0] = x;
        values[1] = y;
        values[2] = z;
    }
    
    return values[1];
}

float readingUltrasonic(Ultrassonic * ultrassonic){
    float firstList[3] = {0,0,0};
    float secondList[3] = {0,0,0};
    float valuesToCalculate[2] = {0,0};
    float meanReading = 0;

    for (int i = 0; i < 3; i++)
    {
        firstList[i] = ultrassonic->distance_cm();      
    }
    for (int i = 0; i < 3; i++)
    {
        secondList[i] = ultrassonic->distance_cm();      
    }
    valuesToCalculate[0] = median(firstList[0],firstList[1],firstList[2]);
    valuesToCalculate[1] = median(secondList[0],secondList[1],secondList[2]);

    meanReading = (valuesToCalculate[0] + valuesToCalculate[1])/2;
    
return meanReading;
}