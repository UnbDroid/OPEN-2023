#include<iostream>

int smallPosition=0;
int closestBlock[2];
int verde [][2]={{61,1},{67,1}};
int azul [][2]={{62,1},{66,1}};
int amarelo [][2]={{63,1},{65,1}};
int vermelho [][2]={{64,1},{64,1}};

int g7 [][2]={{1,1},{1,5}};
int d4 [][2]={{1,1},{1,5}};
int a1 [][2]={{1,1},{1,5}};

int h8 [][2]={{1,2},{1,6}};
int e5 [][2]={{1,2},{1,6}};
int b2 [][2]={{1,2},{1,6}};

int i9 [][2]={{1,3},{1,7}};
int f6 [][2]={{1,3},{1,7}};
int c3 [][2]={{1,3},{1,7}};

int teste [2][2];
int manhattamDistance(int y1,int x1,int y2,int x2){
    return abs(x1-x2)+abs(y1-y2);
}
int verde61,verde67,azul62,azul66,azul63,azul65,vermelho64=1;
int * shortestArea(int y,int x,int bloco){
    int lowest =90;
    
    int *coordinatesPtr;

    switch (bloco)
    {
    case 1:
        teste[0][0] = 61;
        teste[0][1]=1;
        teste[1][0]=67;
        teste[1][1]=1;
        break;
    
    case 2:
        teste[0][0] = 62;
        teste[0][1]=1;
        teste[1][0]=66;
        teste[1][1]=1;
        break;
    case 3:
        teste[0][0] = 63;
        teste[0][1]=1;
        teste[1][0]=65;
        teste[1][1]=1;
        break;  
    case 4:
        teste[0][0] = 64;
        teste[0][1]=1;
        teste[1][0]=64;
        teste[1][1]=1;
        break;
    default:
        break;
    }
    
    
   int lowest =90;
    int indice=0;
    smallPosition=0;
    *closestBlock=0;
    *(closestBlock+1)=0;
    for(int *block:teste){
        int yBlock = (int)(*block/10);
        int xBlock = (int)(*(block)%10);
        int distance = manhattamDistance(y,x,yBlock,xBlock);  
        
        if(distance<lowest && *(block+1)>=1){
            lowest=distance;
            closestBlock[0]=yBlock;
            closestBlock[1]=xBlock;
            smallPosition=indice;
        }
        indice++;
    }
    std::cout<<(*closestBlock)<<" "<<*(closestBlock+1)<<std::endl;
    
    teste[smallPosition][1]=(teste[smallPosition][1])-1;
    return closestBlock;
}
int * ptr;
int * entregarBloco(){
    return ptr;
}

