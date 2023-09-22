#ifndef __PINS_H
#define __PINS_H

//motoresDC

// #define M_LEFT_IN1 25 //26
// #define M_LEFT_IN2 23 //28
// #define PWM_LEFT 5
// #define ENC_A_LEFT 18
// #define ENC_B_LEFT 19

// #define M_RIGHT_IN3 24
// #define M_RIGHT_IN4 22
// #define M_PWM_RIGHT 4
// #define ENC_A_RIGHT 3
// #define ENC_B_RIGHT 2

#define M_LEFT_RPWM A8 //ANTIGO IN1
#define M_LEFT_LPWM A7

#define ENC_A_LEFT 20
#define ENC_B_LEFT 19
#define EN_LEFT_MOTOR 13

#define M_RIGHT_RPWM A6//ANTIGO IN3
#define M_RIGHT_LPWM A5//ANTIGO IN4

#define ENC_A_RIGHT 21
#define ENC_B_RIGHT 18
#define EN_RIGHT_MOTOR 11

#define BUMPER_PIN 37

//

/* Infravermelhos
pbrav
*/
#define A0_DIREITA_FRENTE   A12
#define A0_ESQUERDA_FRENTE  A11
#define A0_ESQUERDA_MEIO 9
#define A0_DIREITA_MEIO 10
#define A0_LATERAL_LEFT A9
#define A0_LATERAL_RIGHT A10
/*  Sensores de Cor*/
#define S0_COLORSENSOR 33
#define S1_COLORSENSOR 31 
#define S2_COLORSENSOR 41
#define S3_COLORSENSOR 39
#define OUT_COLORSENSOR 35
/**/



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



#endif
