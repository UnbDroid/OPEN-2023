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
    movePID_cm(10,FORWARD,0.3,leftMotor,rightMotor);
    
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
    movePID_cm(5,BACKWARD,0.3,leftMotor,rightMotor);

    stop(leftMotor,rightMotor);
    delay(500);
    rotates(LEFT,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    // for (int i = 1; i < 20; i++) { //faz uma média das leituras do ultrassom
    //     readingUltraLateral =  readingUltraLateral + lateralUltrassonic->distance_cm();
    //     readingUltraFrontal = readingUltraFrontal + frontalUltrassonic->distance_cm();
    //     }
    // readingUltraLateral = readingUltraLateral/20;
    // readingUltraFrontal = readingUltraFrontal/20;
    
    int readingUltraLateral = lateralUltrassonic->distance_cm();
    int readingUltraFrontal = frontalUltrassonic->distance_cm();

    Serial.print("as leituras  dos ultra frontal/lateral: ");
    Serial.print(readingUltraFrontal);
    Serial.print(" ");
    Serial.println(readingUltraLateral);

    if (readingUltraLateral < closeToUltra || readingUltraFrontal < closeToUltra){
        seesSomething = true;
    }

    stop(leftMotor,rightMotor);
    delay(500);
    rotates(RIGHT,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    movePID_cm(5,FORWARD,0.3,leftMotor,rightMotor);
    // resetEncoders(leftMotor,rightMotor);
    // while(leftMotor->getEncoder()<200 && rightMotor->getEncoder()<200){
    //     leftMotor->moveForward(80);
    //     rightMotor->moveForward(60);
    // }

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

void beginning(LightSensor * lightSensorLeft, LightSensor * lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * frontalUltrassonic, Ultrassonic * lateralUltrassonic, ColorSensor * colorSensor, Bumper * bumper){
    //objetos = prateleira(1), cores(2), cubo(3), borda(4).

    Serial.println("to no começo");
    float closeToUltra = 18;
    bool mustTurn = false;
    bool edge = false;
    int lastSeen = 0;
    bool shelve = false;
    int position[2] = {0,0}; //y,x, respectivamente
    setPreviusTime(micros());

    while(!edge || !lastSeen){ 
        // float readingColor = colorSensor->identify_color();
        float readingFrontalUltra = 0;
        // Serial.print("tempo atual: ");
        // Serial.print(micros());
        for (int i = 0; i < 2; i++) { //faz uma média das leituras do ultrassom
            readingFrontalUltra =  readingFrontalUltra + frontalUltrassonic->distance_cm();
            // Serial.print("soma leitura ultra: ");
            // Serial.println(readingFrontalUltra);
            movePID(FORWARD,0.5,leftMotor,rightMotor); 
            }

        // Serial.println("fim iteração ultrassom");
        readingFrontalUltra = readingFrontalUltra/2;
        // Serial.print(" vs tempo final: ");
        // Serial.println(micros());

        if (false){//bumper->checkBumper()){
            stop(leftMotor,rightMotor);
            // delay(2000);
            resetEncoders(leftMotor,rightMotor);
            // Serial.println("vou p tras pq borda");
            while (leftMotor->getEncoder()<600 && rightMotor->getEncoder() < 600){
                leftMotor->moveBackward(80);
                rightMotor->moveBackward(60);
            }
            stop(leftMotor,rightMotor);
            delay(500);
            

            //testa a cor do sensor de cor
            // Serial.println("bumper sentiu algo, parei");
            shelve = checksUltrassonic(frontalUltrassonic, lateralUltrassonic,leftMotor,rightMotor);

            if (edge){
                // Serial.println("vejo borda e ja vi borda");
                if(shelve){
                    // Serial.println("estou na quina 1.7, pois vi borda/borda/prateleira");
                    position[0] = 1;
                    position[1] = 7;
                    break;

                } else {
                    position[0] = 6;
                    position[1] = greenEdge(leftMotor,rightMotor,lightSensorLeft,lightSensorRight);
                    //ou está em 6.7 ou em 6.1
                    break;
                }

            } else{
                edge = true;

                if (shelve){
                    // Serial.println("estou na quina 1.7, pois vi prateleira/borda");
                    position[0] = 1;
                    position[1] = 7;
                    break;

                } else {
                    edge = true;
                    mustTurn = true;
                }
            }
        
        } else if (readingFrontalUltra<closeToUltra && readingFrontalUltra > 0){ //viu objeto
            Serial.print("distancia: ");
            Serial.print(" ");
            Serial.println(readingFrontalUltra);

            shelve = checksUltrassonic(frontalUltrassonic,lateralUltrassonic,leftMotor,rightMotor);

            if (shelve){ 
                if(edge){
                    // Serial.println("estou na quina 1.1");
                    position[0] = 1;
                    position[1] = 1;
                    
                } else{
                    lastSeen = 1;
                    mustTurn = true;
                }
            } else { //cubo
                mustTurn = true;
            }      
        } 
        
        if (mustTurn){

            stop(leftMotor,rightMotor);
            delay(500);
            resetEncoders(leftMotor,rightMotor);
            // Serial.println("vou p tras pq preciso girar");

            movePID_cm(3,BACKWARD,0.30,leftMotor,rightMotor);
            // while(leftMotor->getEncoder()< 200 and rightMotor->getEncoder() < 200){
                // movePID(BACKWARD,40,leftMotor,rightMotor);
                // leftMotor->moveBackward(70);
                // rightMotor->moveBackward(55);
                // Serial.println("indo pra trass");
            // } 
            
            stop(leftMotor,rightMotor);
            delay(500);
            rotates(RIGHT,leftMotor, rightMotor);
            stop(leftMotor,rightMotor);
            delay(500);
            // Serial.println("quero alinhar");

            while(lightSensorLeft->read()<150 && lightSensorRight->read()<150){
                // leftMotor->moveForward(75);
                // rightMotor->moveForward(55);
                movePID(FORWARD,0.25,leftMotor,rightMotor);

                // Serial.print("alinha e le: Esq/Dir ");
                Serial.print(lightSensorLeft->read());
                Serial.print(" ");
                Serial.println(lightSensorRight->read());

            } 
            stop(leftMotor,rightMotor);
            delay(1000);
            align(lightSensorLeft,lightSensorRight,leftMotor,rightMotor,55);
            // Serial.println("terminei de alinhar");

            resetEncoders(leftMotor,rightMotor);
            mustTurn = false;

        } else {
            // resetEncoders(leftMotor,rightMotor);
            movePID(FORWARD,0.5,leftMotor,rightMotor);
            // leftMotor->moveForward(80);
            // rightMotor->moveForward(60);

        }
    }
    
    stop(leftMotor,rightMotor);
    // Serial.print(lastSeen);
    // Serial.print(" ");
    // Serial.println(edge);

}
