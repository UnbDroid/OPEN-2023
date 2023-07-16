#include<MotorDC.h>
#include<Arduino.h>
#include<Wire.h>
/*
AQUI O QUE QUE ACONTECE? BOM BASICAMENTE SE LEMBRAM QUANDO A GENTE PEGA UMA STRING POR EXEMPLO
E FAZIA STRING.LENGTH, ETC? ESSE '.' SÃO MÉTODOS E QUE A GENTE IMPLEMENTA DESSE JEITO
COLOCANDO A CLASSE::( MÉTODO OU ATRIBUTO)
ESTOU PASSANDO UM PONTEIRO PARA A FUNÇÃO DE ANDAR PORQUE PRECISAREMOS PASSAR UM PONTEIRO 
PARA FAZER O CONTROLE, CASO NÃO SAIBAM O QUE É, POSSO TENTAR EXPLICAR COMO FUNCIONA

*/


MotorDC::MotorDC(int pinoA, int pinoB, int pinoPwm){
    this->pinoA = pinoA;
    this->pinoB = pinoB;
    this->pinoPwm = pinoPwm;
    pinMode(this->pinoA, OUTPUT);
    pinMode(this->pinoB, OUTPUT);
    pinMode(this->pinoPwm, OUTPUT);
    pinMode(this->pinEnc, INPUT);

    /*
    AQUI É O CONSTRUTOR DA NOSSA CLASSE, JA ESTAMOS SETANDO O MODO DOS PINOS BEM AQUI.
    */
}

MotorDC::MotorDC(int pinoA, int pinoB, int pinoPwm, int pinEnc){
    this->pinoA = pinoA;
    this->pinoB = pinoB;
    this->pinoPwm = pinoPwm;
    this->pinEnc=pinEnc;
    pinMode(this->pinoA, OUTPUT);
    pinMode(this->pinoB, OUTPUT);
    pinMode(this->pinoPwm, OUTPUT);
    

    /*
    AQUI É O CONSTRUTOR DA NOSSA CLASSE, JA ESTAMOS SETANDO O MODO DOS PINOS BEM AQUI.
    */
}

void MotorDC::moveFoward(int *velocidade){
    digitalWrite(this->pinoA, HIGH);
    digitalWrite(this->pinoB, LOW);
    analogWrite(this->pinoPwm, *velocidade);
}

void MotorDC::stop(){
    digitalWrite(this->pinoA, LOW);
    digitalWrite(this->pinoB, LOW);
}

void MotorDC::moveBackward(int *velocidade){
    digitalWrite(this->pinoA, LOW);
    digitalWrite(this->pinoB, HIGH);
    analogWrite(this->pinoPwm, *velocidade);
}
