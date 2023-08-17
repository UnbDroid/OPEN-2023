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


MotorDC::MotorDC(int pinoLpwm, int pinoRpwm, int pinEncA, int pinEncB){
    this->pinoLpwm = pinoLpwm;
    this->pinoRpwm = pinoRpwm;
    
    pinMode(this->pinoLpwm, OUTPUT);
    pinMode(this->pinoRpwm, OUTPUT);
    pinMode(this->pinEncA, INPUT);
    pinMode(this->pinEncB, INPUT);

    /*
    AQUI É O CONSTRUTOR DA NOSSA CLASSE, JA ESTAMOS SETANDO O MODO DOS PINOS BEM AQUI.
    */
}

void MotorDC::moveForward(int velocidade){
    analogWrite(this->pinoLpwm, velocidade);
    analogWrite(this->pinoRpwm, 0);
}

void MotorDC::stop(){
    digitalWrite(this->pinoRpwm, 0);
    digitalWrite(this->pinoLpwm, 0);
}

void MotorDC::moveBackward(int velocidade){
    analogWrite(this->pinoLpwm, 0);
    analogWrite(this->pinoRpwm, velocidade);
}


void MotorDC::readEncoder(){
  int b = digitalRead(pinEncA);
  // Serial.println(b);

  if (b>0){
    posEncoder++;
  } else{
    posEncoder--;
  }
}

int MotorDC::getEncoder(){
    return posEncoder;
}

int MotorDC::setEncoder(int value){
    posEncoder = value;
}

// int MotorDC::getEncoderRight(){
//     return pos_encoder_left;
// }