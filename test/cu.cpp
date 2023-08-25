#include<iostream>
#include<math.h>
#include<list>
enum Direcao{
    Norte,Leste,Sul,Oeste
};

int ManhattamDistance(int y1,int x1,int y2,int x2){
    return abs(x1-x2)+abs(y1-y2);
}

static int arrayPosicoesCima []={11,12,13,14,15,16,17,21,22,23,24,25,26,27};
static int arrayPosicoesBaixo[]={51,52,53,54,55,56,57,61,62,63,64,65,66,67,71,72,73,74,75,76,77};
static int arrayLados []={31,34,37,41,44,47};
void corrigirDirecao(int * direction){
    static int flag = 1;
    if(*direction>=Oeste){
        *direction = Norte;
    }
    else{
        *direction=*direction+1;
    }
    std::cout<<"Girei "<<flag<<std::endl;
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
            closest[0]=*coordinatesPtr;//y
            closest[1]=*(coordinatesPtr+1);//X
        }
        coordinatesPtr++;
        coordinatesPtr++;
        tam--;
    }
    return closest;
    
}

Direcao direction(char eixo,int inicial, int final){
       
        if(eixo =='y'){
            if(final<=inicial){
            return  Norte;
            }
            return  Sul;
        }
        if(final>inicial){
            return  Leste;
        }
        //estou na direita e ele na esquerda 
        return  Oeste;          
        
}
bool atravessei(){
    return true;
}
void moveTo(int * xInicial,int *yInicial,int *menorYmenorX,int *direcaoAtual){
    
    //if ele não precisa atravessar:
    Direcao direcaoDestino= direction('y',*yInicial,*menorYmenorX);
        while(*direcaoAtual !=direcaoDestino){
            //giro os motores
            //e depois atualizo a direção
            corrigirDirecao(direcaoAtual);
        }
    
    if(*yInicial<*menorYmenorX){
        
        while(*yInicial<*menorYmenorX){
            if(atravessei()){
                std::cout<<"Andei pra baixo"<<std::endl;
                *yInicial =*yInicial+1;
                
            }
        }
    }
    else if(*yInicial>*menorYmenorX){
        while(*yInicial>*menorYmenorX){
            if(atravessei()){
                *yInicial=*yInicial-1;
                std::cout<<"Andei Pra Cima"<<std::endl;
            }
        }
    }
    
    direcaoDestino= direction('x',*xInicial,*(menorYmenorX+1));
        while(*direcaoAtual !=direcaoDestino){
            //giro os motores
            //e depois atualizo a direção
            corrigirDirecao(direcaoAtual);
        }
    if(*xInicial<*(menorYmenorX+1)){
        while(*xInicial<*(menorYmenorX+1)){
            if(atravessei()){
                *xInicial=*xInicial+1;
                std::cout<<"Andei pra direita"<<std::endl;
                
            }
        }
    }
    else if(*xInicial>*(menorYmenorX+1)){
        while(*xInicial>*(menorYmenorX+1)){
            if(atravessei()){
                *xInicial=*xInicial-1;
                std::cout<<"Andei pra esquerda"<<std::endl;
                
            }
        }
    }
    
}
/*
void corrigirDirecao(int * direction,MotorDC motorEsquerdo,MotorDc motorDireito){
    
    if(*direction>=Oeste){
        *direction = Norte;
    }
    else{
        *direction=*direction+1;
    }
    girar(Esquerda,motorEsquerda,motorDireito,160);
}

*/


/*

void moveTo(int xInicial,int yInicial,int x2,int y2, Direcao direcao, Infra1 infrEsq, Infra2 infraDir){
    //Direcao direction = direcaoDestino(xInicial,yInicial, x2, y2);
    //if ele não precisa atravessar:
    
}
*/

void maquinaDeEstados(int* y,int* x,int direcaoAtual){
        
        int * menorYMenorX =  shortestArea(*y,*x);
        *menorYMenorX=5;
        *(menorYMenorX+1)=7;   
        
    moveTo(x,y,menorYMenorX,&direcaoAtual);
    
        
    
}
int main(){
    int y =6;
    int x =1;
    Direcao direc = Sul;
    maquinaDeEstados(&y,&x,direc);
    
    return 0;
}
