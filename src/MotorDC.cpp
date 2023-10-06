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

MotorDC::MotorDC(int pinoLpwm, int pinoRpwm, int pinoEN, int pinEncA, int pinEncB){
    this->pinoLpwm = pinoLpwm;
    this->pinoRpwm = pinoRpwm;
    this->pinoEN = pinoEN;
    // this-> pinEncA = pinEncA; // não sei se devia add isso
    // this-> pinEncB = pinEncB; // não sei se devia add isso
    
    pinMode(this->pinoLpwm, OUTPUT);
    pinMode(this->pinoRpwm, OUTPUT);
    pinMode(this->pinoEN, OUTPUT);
    pinMode(this->pinEncA, INPUT);
    pinMode(this->pinEncB, INPUT);
}
void MotorDC::moveForward(int velocidade){
    digitalWrite(this->pinoLpwm, HIGH);
    digitalWrite(this->pinoRpwm, LOW);
    analogWrite(this->pinoEN, velocidade);
}

void MotorDC::stop(){
    digitalWrite(this->pinoRpwm, HIGH);
    digitalWrite(this->pinoLpwm, HIGH);
    digitalWrite(this->pinoEN,HIGH);
}

void MotorDC::stopLow(){
    digitalWrite(this->pinoRpwm, LOW);
    digitalWrite(this->pinoLpwm, LOW);
    digitalWrite(this->pinoEN,LOW);
}

void MotorDC::moveBackward(int velocidade){
    digitalWrite(this->pinoLpwm, LOW);
    digitalWrite(this->pinoRpwm, HIGH);
    analogWrite(this->pinoEN, velocidade);
}


void MotorDC::readEncoder(){
  posEncoder++;
}

unsigned int MotorDC::getEncoder(){
    return posEncoder;
}

int MotorDC::setEncoder(int value){
    posEncoder = value;
}
