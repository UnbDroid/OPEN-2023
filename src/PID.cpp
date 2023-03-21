#include<PID.h>
#include<Arduino.h>
#include<Wire.h>
#include<MotorDC.h>

SimplePID::SimplePID(int kp, int kd, int ki, int umax, int eprevious, int eintegral, int ENCA, int ENCB){
  this-> kp = kp; 
  this-> kd = kd;
  this-> ki = ki;
  this-> umax = umax;
  this-> umin = umin;
  this-> eintegral = eintegral;
  this-> erroPrevious = erroPrevious;

  this-> ENCA = ENCA;
  this-> ENCB = ENCB;

  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);

} 

//função para computar o controle em si, retorna o sinal "u_PID" que será usado para enviar pros motores:
int SimplePID::controlValue(int positionRight, int positionLeft, int target, float deltaT, int &pwr, int KP, int KD, int KI){

  int erro = positionLeft - positionRight; // meu objetivo é que  a diferença de ambos seja nula, ou seja, que o erro seja 0

  //derivative: calcula a o quão rápido o erro está mudando
  float dedt = (erro-erroPrevious)/(deltaT); 

  //integral: acumula o erro ao longo do tempo
  eintegral = eintegral + erro*deltaT;

  //o valor PID que vai ser mandado de fato
  float sumPID = KP*erro + KD*dedt + KI*eintegral;
  
  //armazena o erro anterior:
  erroPrevious = erro;
  return sumPID;

}

// Calcula a potencia que será enviada para os motores, bem como a direção com que girarão
void SimplePID::setMotorsPID(int sumPID, int umax, int umin){
  //intensidade que será enviada pro motor
  int pwr = (int) sumPID;
  if (fabs(pwr) > umax){  
  pwr = umax;
  } else if (fabs(pwr) < umin){
  pwr = 150; // valor experimental que se refere ao mínimo de potencia a ser enviado pros motores de forma a ainda fazer o robô andar. NÂO É ESSE VALOR PRO PELAS
  }

  if (sumPID > 0){
    // frente
  } else{
    //tras
  }
  
// Não terminei essa função pois só consegui pensar nela depois da ajuda da thamires e do Luan ao refatorar o código kk. Mas a ideia é retornar uma lista
// com, tanto a potência do motor quanto a direção que deve girar (se usamos motor.andar_pra_frente ou motor.andar_pra_tras)
}

//Toda vez que o sensor B do encoder é gatilhado, a gente soma/subtrai 1 nessa função, usada no attachInterrupt()
void SimplePID::readEncoder(int ENCB, int posicao){
  int b = digitalRead(ENCB);
  if (b>0){
    posicao++;
  } else{
    posicao--;

  }
}
