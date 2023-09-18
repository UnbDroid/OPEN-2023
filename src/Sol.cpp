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
    return ;
}
void moveYandMoveX(int *currentX,int *currentY,int *destinationYX, int * currentDirection,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    SOL::Direcao destinationDirection= futureDirection('y',*currentY,*destinationYX);
        if(!correctedYFlag){
            
        }
        while(!correctedYFlag &&(*currentY!=*destinationYX)){
            while(*currentDirection!=destinationDirection){
                correctingDirection(currentDirection,leftMotor,rightMotor);
            }
            stop(leftMotor,rightMotor);

            changingAndCountingPosition(currentY,destinationYX,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            correctedYFlag=1;
            break;
        }
        while(!correctedXFlag && (*currentX!=*(destinationYX+1))){
            destinationDirection= futureDirection('x',*currentX,*(destinationYX+1));
            while(*currentDirection !=destinationDirection){
                Serial.println(*currentX);
                correctingDirection(currentDirection,leftMotor,rightMotor);
            }
            stop(leftMotor,rightMotor);
            changingAndCountingPosition(currentX,destinationYX+1,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
            break;
        }
        return ;
}

void moveTo(int * currentX,int *currentY,int *destinationYX,int *currentDirection, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    //if ele não precisa atravessar:

    if((*currentY >=5 && *destinationYX>=5)  || (*currentY <=2 && *destinationYX<=2)){
        moveYandMoveX(currentX,currentY,destinationYX,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);
    }
    else{
        
        int * lowestCrossBlock = shortestArea(true,*currentY,*currentX);
        ;
        // Serial.print(*lowestCrossBlock);
        // Serial.print(" ");
        // Serial.println(*(lowestCrossBlock+1));
        moveYandMoveX(currentX,currentY,lowestCrossBlock,currentDirection,lightSensorLeft,lightSensorRight,leftMotor,rightMotor);

    }
        
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
    *destinationYX=2;
    *(destinationYX+1)=4;  
    moveTo(x,y,destinationYX,currentDirection,lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
    
}


void beginning(LightSensor * lightSensorLeft, LightSensor * lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * ultrassonic, ColorSensor * colorSensor, Bumper * bumper){
    Serial.println("to no começo");
    float closeToUltra = 10;
    //objetos = prateleira(1), cubo(2), cores(3), borda(4).
    // bool objectsItSees[2] = {false,};
    // int memory = 0;
    int lastSeen[2] = {0,0}; // bool pra borda e qualquer outra coisa, nessa ordem
    bool mustTurn = false;


    while(lastSeen[0]==0 || lastSeen[1]==0){ 
        float readingUltra = 0;
        for (int i = 0; i < 20; i++) { //faz uma média das leituras do ultrassom
            readingUltra =  readingUltra + ultrassonic->distance_cm(); }
        readingUltra = readingUltra/20;
        // float readingColor = colorSensor->identify_color();
    

        if (!bumper->checkBumper()){
            stop(leftMotor,rightMotor);
            lastSeen[0] = 4;
            mustTurn = true;
            Serial.println("bumper acionou");

        } else if(readingUltra<closeToUltra && readingUltra>0){
            Serial.print("distancia: ");
            Serial.print(" ");
            Serial.println(readingUltra);

            lastSeen[1] = 2;
            mustTurn = true;
        }

        /*
        if(readingColor<=3){
            Serial.print("cor: ");
            Serial.print(" ");
            Serial.println(readingColor);
            mustTurn = true;
            stop(leftMotor,rightMotor);
            
             while(leftMotor->getEncoder()< 512 and rightMotor->getEncoder() < 512){
                movePID(BACKWARD,80,leftMotor,rightMotor);
            }
            stop(leftMotor, rightMotor);

            lastSeen[1]=3;
        }
        */
        
        if (mustTurn){

            stop(leftMotor,rightMotor);
            resetEncoders(leftMotor,rightMotor);
            while(leftMotor->getEncoder()< 300 and rightMotor->getEncoder() < 300){
                // movePID(BACKWARD,40,leftMotor,rightMotor);
                leftMotor->moveBackward(70);
                rightMotor->moveBackward(55);
                // Serial.println("indo pra trass");
            } 
            stop(leftMotor,rightMotor);
            delay(500);
            rotates(RIGHT,leftMotor, rightMotor);
            stop(leftMotor,rightMotor);
            delay(1000);
            
            while(lightSensorLeft->read()<500 && lightSensorRight->read()<500){
                leftMotor->moveForward(50);
                rightMotor->moveForward(40);

                Serial.print(lightSensorLeft->read());
                Serial.print(" ");
                Serial.println(lightSensorRight->read());

            } 
            stop(leftMotor,rightMotor);
            delay(1000);
            align(lightSensorLeft,lightSensorRight,leftMotor,rightMotor,50);

            // resetEncoders(leftMotor,rightMotor);
            mustTurn = false;

        } else {
            // resetEncoders(leftMotor,rightMotor);
            // movePID(FORWARD,60,leftMotor,rightMotor);
            leftMotor->moveForward(70);
            rightMotor->moveForward(55);
            // Serial.println("eu to indo reto");

        }
    }
    
    if (lastSeen[1] == 2){
        stop(leftMotor,rightMotor);
        Serial.print(lastSeen[0]);
        Serial.print(" ");
        Serial.println(lastSeen[1]);
        Serial.print("vi algo e borda");
    }


    
}

/*
Coisas que ele pode ver em frente:
    borda da arena - bumper
    objeto frontal (prateleira ou cubos) - ultrassom
    área das cores - sensor de cor
    



*/