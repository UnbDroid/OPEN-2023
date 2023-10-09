#ifndef __PINS_H
#define __PINS_H

//motoresDC

#define M_LEFT_RPWM A8 //ANTIGO IN1
#define M_LEFT_LPWM A7
#define EN_LEFT_MOTOR 13

#define ENC_A_LEFT 20
#define ENC_B_LEFT 19

#define M_RIGHT_RPWM A6//ANTIGO IN3
#define M_RIGHT_LPWM A5//ANTIGO IN4
#define EN_RIGHT_MOTOR 11

#define ENC_A_RIGHT 21
#define ENC_B_RIGHT 18

//bumper
#define BUMPER_PIN 37

//Ultrassom
#define TRIG_UlLTRASSONIC_FRONTAL 45
#define ECHO_UlLTRASSONIC_FRONTAL 43
#define TRIG_UlLTRASSONIC_LATERAL 14
#define ECHO_UlLTRASSONIC_LATERAL 15

/* Infravermelhos
*/

#define A0_DIREITA   A12
#define A0_ESQUERDA  A11
#define A0_TRAS A10
#define A0_MEIO_ESQUERDA  A13
#define A0_MEIO_DIREITA A14 
#define D0_DIGITAL 21

//LDR
#define pinLDR A13

/*  Sensores de Cor*/
#define S0_COLORSENSOR 33
#define S1_COLORSENSOR 31 
#define S2_COLORSENSOR 41
#define S3_COLORSENSOR 39
#define OUT_COLORSENSOR 35




/* Motores de Passo

Empilhadeira*/

#define DIR_EMPILHADEIRA 51
#define PUL_EMPILHADEIRA 53

/*Garra*/

#define DIR_GARRA 50
#define PUL_GARRA 52




/*Ultrassom frontal*/
#define echo_ultrassom_frontal 45
#define trig_ultrassom_frontal 43

#define echo_ultrassom_lateral 14
#define trig_ultrassom_lateral 15


/*-----------------*/

#define KP 10
#define KI 1
#define KD 1

// extern int leftWhite = 100;
// extern int rightWhite = 200;




#define KP 1.5//0.09999 // 0.6
#define KI 0 //0.0001 //1
#define KD 0 // 0.5


#define KP_LEFT 1//1
#define KP_RIGHT 1 //0.85//1.4 //gigante, tentou compensar pra esquerda
#define KI_LEFT 1//0.9 ou 0.5
#define KI_RIGHT 1//0.7

//quando oscila demais (KI), pode aumentar kp

#endif
