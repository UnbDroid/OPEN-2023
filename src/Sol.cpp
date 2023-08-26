#include<Sol.h>

int ManhattamDistance(int y1,int x1,int y2,int x2){
    return abs(x1-x2)+abs(y1-y2);
}
bool atravessei(){
    return true;
}
int * shortestArea(int y,int x){
    int lowest =90;
    int areasBlocks[8][2]={ {2,2},{2,3},     {2,5},{2,6},


                            {5,2},{5,3},     {5,5},{5,6}
    };
    
    int *coordinatesPtr;
    coordinatesPtr = *areasBlocks;
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


SOL::Direcao direction(char eixo,int inicial, int final){
       
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

void corrigirDirecao2(int * direction, MotorDC * leftMotor,MotorDC* rightMotor){
    leftMotor->moveForward(60);
    rightMotor->moveForward(40);
    static int flag = 1;
    if(*direction>=SOL::Oeste){
        rotates90(RIGHT,50,leftMotor,rightMotor);
        //stop(leftMotor,rightMotor);
        *direction = SOL::Norte;
    }
    else{
        rotates90(RIGHT,50,leftMotor,rightMotor);
        //stop(leftMotor,rightMotor);
        *direction=*direction+1;
    }
    Serial.print("Girei ");
    Serial.println(flag);
    flag++;
}

void corrigirDirecao(int * direction, MotorDC * leftMotor,MotorDC* rightMotor){
    // leftMotor->moveForward(60);
    // rightMotor->moveForward(40);
    static int flag = 1;
    if(*direction>=SOL::Oeste){
        rotates90(RIGHT,80,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        *direction = SOL::Norte;
    }
    else{
        rotates90(RIGHT,80,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        *direction=*direction+1;
    }
    Serial.print("Girei ");
    Serial.println(flag);
    flag++;
}
    
void moveTo(int * xAtual,int *yAtual,int *menorYmenorX,int *direcaoAtual, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    int dist = abs(*yAtual-*menorYmenorX);
    //if ele não precisa atravessar:
    static int  flagCorrigiuY = 0;
    static int flagCorrigiuX = 0;
    SOL::Direcao direcaoDestino= direction('y',*yAtual,*menorYmenorX);
    int a = direcaoDestino;
    while(!flagCorrigiuY &&*yAtual!=*menorYmenorX ){
        while(*direcaoAtual!=a){
            corrigirDirecao(direcaoAtual,leftMotor,rightMotor);
        }
        stop(leftMotor,rightMotor);    
        if(*yAtual<*menorYmenorX){
            while(*yAtual<*menorYmenorX){
                moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
                *yAtual = *yAtual+1;
            }
            moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
        }
        else if(*yAtual>*menorYmenorX){
            while(*yAtual>*menorYmenorX){
                moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
                *yAtual = *yAtual-1;
            }
            moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
        }
        flagCorrigiuY=1;
        break;
    }
    
    while(!flagCorrigiuX != *xAtual<*(menorYmenorX+1)){
        direcaoDestino= direction('x',*xAtual,*(menorYmenorX+1));
        while(*direcaoAtual !=direcaoDestino){
            corrigirDirecao(direcaoAtual,leftMotor,rightMotor);
        }
        stop(leftMotor,rightMotor);
        if(*xAtual<*(menorYmenorX+1)){
            while(*xAtual<*(menorYmenorX+1)){
                moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
                *xAtual = *xAtual+1;
            }
            moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
        }
        else if(*xAtual>*(menorYmenorX+1)){
            while(*xAtual>*(menorYmenorX+1)){
                moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
                *xAtual = *xAtual-1;
            }
            moveForSquare(0, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
            stop(leftMotor,rightMotor);
        }
        stop(leftMotor,rightMotor);
        flagCorrigiuX=1;
        break;
    }
    
}

void maquinaDeEstados(int* y,int* x,int *direcaoAtual,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
        
    int * menorYMenorX =  shortestArea(*y,*x);
    *menorYMenorX=6;
    *(menorYMenorX+1)=5;   
        
    moveTo(x,y,menorYMenorX,direcaoAtual,lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
    
}