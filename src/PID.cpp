#include<PID.h>
#include<Arduino.h>
#include<Wire.h>

extern int NMOTORS;
extern long prevT;
extern volatile int posi[];
extern float target_f[];
extern long target[];

// função que seta os parâmetros:
void SimplePID::setParameters(float kpIn, float kdIn, float kiIn, float umaxIn){
    kp = kpIn; 
    kd = kdIn; 
    ki = kiIn; 
    umax = umaxIn;
}

//função para computar o controle em si:
void SimplePID::evalu(int value, int target, float deltaT, int &pwr, int &dir){
  //ATÉ A LINHA 27, ESSES SÃO OS CÁLCULOS DOS VALORES DE PID, ou seja    
  //erro no valor do encoder 
  int e = target - value; //a posição que ele assume - a posição que eu quero que ele assuma

  //derivative: calcula a o quão rápido o erro está mudando
  float dedt = (e-eprev)/(deltaT); 

  //integral: acumula o erro ao longo do tempo
  eintegral = eintegral + e*deltaT;

  //o valor PID que vai ser mandado de fato
  float u = kp*e + kd*dedt + ki*eintegral;

  //intensidade do motor
  pwr = (int)fabs(u);
  if (pwr > umax){  
  pwr = umax;
  }

  //sentido do motor que queremos mandar. Usamos isso na chamada da própria função
  dir = 1; 
  if(u<0){
  dir = -1;
}
  //armazena o erro anterior:
  eprev = e;
}


void setTarget(float t, float deltat){ // em que "t" é o momento no tempo atual
  float positionChange[] = {0.2,0.2};
  for (int k = 0; k<2; k++){
      target_f[k] = target_f[k]+ positionChange[k]; // 
  }
  target[0] = (long) target_f[0];
  target[1] = (long) -target_f[1];
}

//instanciando a classe
SimplePID pid[NMOTORS];
// SimplePID pidA;

// função coriga pra qualquer motor. 
//Toda vez que o sensor B do encoder é gatilhado, a gente soma nessa função
template <int j>
void readEncoder(){
  int b = digitalRead(encb[j]);
  if (b>0){
    posi[j]++;
  } else{
    posi[j]--;
  }
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }
}