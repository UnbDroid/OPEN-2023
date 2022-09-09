#include<Sol.h>

int ManhattamDistance(int y1,int x1,int y2,int x2){
    return abs(x1-x2)+abs(y1-y2);
}
bool atravessei(){
    return true;
}
void corrigirDirecao(int * direction){
    static int flag = 1;
    if(*direction>=SOL::Oeste){
        *direction = SOL::Norte;
    }
    else{
        *direction=*direction+1;
    }
    Serial.print("Girei ");
    Serial.println(flag);
    flag++;
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

void moveTo(int * xAtual,int *yAtual,int *menorYmenorX,int *direcaoAtual, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    
    //if ele não precisa atravessar:
    SOL::Direcao direcaoDestino= direction('y',*yAtual,*menorYmenorX);
        while(*direcaoAtual !=direcaoDestino){
            //giro os motores
            //e depois atualizo a direção
            corrigirDirecao(direcaoAtual);
        }
    
    if(*yAtual<*menorYmenorX){
        while(*yAtual<*(menorYmenorX)){
            moveForSquare(1, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
            *yAtual = *yAtual+1;
        }
    }
    
    direcaoDestino= direction('x',*xAtual,*(menorYmenorX+1));
        while(*direcaoAtual !=direcaoDestino){
            //giro os motores
            //e depois atualizo a direção
            corrigirDirecao(direcaoAtual);
        }
    if(*xAtual<*(menorYmenorX+1)){
        while(*xAtual<*(menorYmenorX+1)){
            moveForSquare(1, lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
            *xAtual = *xAtual+1;
        }
    }
    
}
void maquinaDeEstados(int* y,int* x,int direcaoAtual,LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
        
        int * menorYMenorX =  shortestArea(*y,*x);
        *menorYMenorX=3;
        *(menorYMenorX+1)=6;   
        
    moveTo(x,y,menorYMenorX,&direcaoAtual,lightSensorLeft, lightSensorRight, leftMotor,rightMotor);
       
    
}