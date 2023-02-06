#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>

void move_foward(MotorDC* motor1, MotorDC* motor2, int * velocity){
    motor1->andar_para_frente(velocity);
    motor2->andar_para_frente(velocity);
}
void move_backward(MotorDC* motor1, MotorDC* motor2, int * velocity){
    motor1->andar_para_tras(velocity);
    motor2->andar_para_tras(velocity);
}


int main(){
    return 0;
}