#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Ultrassonic.h>
#include <Pins.h>
#include<Sol.h>
// #define deltaT 500

int previousError = 0;
unsigned long previousTime = 0;
int integralError = 0; 
float constMotors[2] = {0,0};

double motorLeftTurns = 0;
double motorRightTurns = 0;

double sumRPSLeft = 0;
double sumRPSRight = 0;

//PID separado motores
double previousMotorLeftTurns = 0;
double previousMotorRightTurns = 0;
// int leftIntegralError = 0;
// int rightIntegralError = 0;

double leftIntegralErrorSum = 0;
double rigthIntegralErrorSum = 0;

double leftIntegralError[5] = {0,0,0,0,0};
double rightIntegralError[5] = {0,0,0,0,0};

double add(double * ptr, double valor){
    double sum = 0;
    int tam = 4;

    while(tam){
        *(ptr+tam) = *(ptr+(tam-1));
        sum = sum + *(ptr+tam);
        tam --;
   }

   *ptr = valor;
   sum = sum + *ptr;

   return sum;
}

void calibrateMotorsCT(MotorDC * leftMotor, MotorDC * rightMotor){
    resetEncoders(leftMotor,rightMotor);
    leftMotor->moveForward(255);
    rightMotor->moveForward(255);
    delay(1000);
    stop(leftMotor,rightMotor);

    constMotors[0] = leftMotor->getEncoder();
    constMotors[1] = rightMotor->getEncoder();

    constMotors[0] = constMotors[0]/2048;
    constMotors[1] = constMotors[1] /2000;

    constMotors[0] = 255/constMotors[0];
    constMotors[1] = 255/constMotors[1];

    Serial.print("constantes das rodas Esq/Dir: ");
    Serial.print(constMotors[0]);
    Serial.print(" ");
    Serial.println(constMotors[1]);
}

void setPreviusTime(double value){
    previousTime = value;    
}

double getPreviusTime(){
    return previousTime;
}

void move(Directions direction, int PWM ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor * lightSensorLeft,LightSensor* lightSensorRight){
    switch (direction)
    {
    case FORWARD:
        motorLeft->moveForward(PWM);
        motorRight->moveForward(PWM);    
        break;
    case BACKWARD:
        motorLeft->moveBackward(PWM);
        motorRight->moveBackward(PWM);
        break;    
    default:
        break;
    }
}

void initialPosition(MPU9250 * mpu){
    int a;
}
void correctingDirection(int * direction, MotorDC * leftMotor,MotorDC* rightMotor){
    // leftMotor->moveForward(60);
    // rightMotor->moveForward(40);
    static int flag = 1;
    if(*direction>=SOL::Oeste){
        rotates(RIGHT,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        *direction = SOL::Norte;
    }
    else{
        rotates(RIGHT,leftMotor,rightMotor);
        stop(leftMotor,rightMotor);
        *direction=*direction+1;
    }
    Serial.print("Girei ");
    Serial.println(flag);
    flag++;
    return ;
}

void rotates(RotateDirections rotateDirection,MotorDC * motorLeft, MotorDC * motorRight){
    int PWM = 130;
    
    resetEncoders(motorLeft,motorRight);

    // int encoderLeftValue = abs(motorLeft->getEncoder());
    // int encoderRightValue = abs(motorRight->getEncoder());

    switch(rotateDirection)
    {
    case LEFT:
        motorLeft->moveBackward(PWM);
        motorRight->moveForward(PWM);
        while (abs(motorLeft->getEncoder()) < 1100 && abs(motorRight->getEncoder()) < 1100){
            motorLeft->moveBackward(PWM);
            motorRight->moveForward(PWM);
        }
        motorLeft->stop();
        motorRight->stop();
        break;

    case RIGHT:
        motorLeft->moveForward(PWM);
        motorRight->moveBackward(PWM);

        while (abs(motorLeft->getEncoder()) < 1095 && abs(motorRight->getEncoder()) < 1095){
            motorLeft->moveForward(PWM);
            motorRight->moveBackward(PWM);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break; 

    case AROUND:
        motorLeft->moveForward(PWM);
        motorRight->moveBackward(PWM);

        while (abs(motorLeft->getEncoder()) < 2010 && abs(motorRight->getEncoder()) < 2010){
            motorLeft->moveForward(PWM);
            motorRight->moveBackward(PWM);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break; 
     

    default:
        break;
    }


}

void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLeft, MotorDC * motorRight, int PWM){
    int leftWhite = 150;
    int rightWhite = 300;

    Serial.print("sensores IR: ");
    Serial.print(lightSensorLeft->read());
    Serial.print(" ");
    Serial.println(lightSensorRight->read());
    
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);
    
    if (lightSensorLeft->read()>leftWhite || lightSensorRight->read()>rightWhite){
        Serial.println("estou me alinhando");
        stop(motorLeft,motorRight);
        delay(500);
        
        if (lightSensorLeft->read()<leftWhite) //vê branco
        {
            Serial.print("esquerdo ve branco ");
            while (lightSensorLeft->read()<leftWhite) { // && lightSensorRight->read()>rightWhite){ // ve branco
               
                Serial.print("leitura IR ao alinhar: ");            
                Serial.print(lightSensorLeft->read());
                Serial.print(" ");
                Serial.println(lightSensorRight->read());

                motorLeft->moveForward(PWM+10);
                
                motorRight->setEncoder(0);
                while(motorRight->getEncoder() < 10){
                    motorRight->moveBackward(50);
                }
                

            }

        }
        else if (lightSensorRight->read() < rightWhite) //ve branco
        {
            Serial.println("direito ve branco");
            while (lightSensorRight->read()<rightWhite) {// ve branco
                motorRight->moveForward(PWM);

                Serial.print(lightSensorLeft->read());
                Serial.print(" ");
                Serial.println(lightSensorRight->read());

                motorLeft->setEncoder(0);
                while (motorLeft->getEncoder() < 15){
                    motorLeft->moveBackward(70);
                }    
            }
        }  
    stop(motorLeft, motorRight);
    delay(500);
    
    } else{
        return ;
    }
}



void moveForSquare(int quantityToMove, LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * leftMotor, MotorDC * rightMotor){
    quantityToMove++;
    int count =0;
    if(count<quantityToMove){
        while(count<quantityToMove){
        leftMotor->moveForward(60);
        rightMotor->moveForward(40);
        lightSensorLeft->read();
        lightSensorRight->read();
            if(lightSensorRight->getCrossed()){
                Serial.println("atravesseiiii");
                count++;
                lightSensorLeft->setCrossed(false);
                lightSensorRight->setCrossed(false);
        }
        }
    }
    return ;
}

void movePID_cm(int distance_cm, Directions direction, float goalRPS ,MotorDC* motorLeft, MotorDC* motorRight){
    float circunference = 37.7;
    int leftEncoderValue = (2048/circunference)*distance_cm;
    int rightEncoderValue = (2000/circunference)*distance_cm;

    setPreviusTime(0);
    resetEncoders(motorLeft,motorRight);
    while(motorLeft->getEncoder() < leftEncoderValue && motorRight->getEncoder() < rightEncoderValue){
        movePID(direction, 0.5, motorLeft, motorRight);
    }
    stop(motorLeft,motorRight);

}

void movePID(Directions direction, float goalRPS ,MotorDC* motorLeft, MotorDC* motorRight){
    // KD tem que compensar rapido o suficiente pro KI não ficar muito tempo errado
    // Se ele tiver oscilando demais, tira primeiro o KD e depois o KI
    unsigned long currentTime = micros();
    double deltaT = (currentTime-previousTime);
    deltaT = deltaT/(double)1000000;
    previousTime = currentTime;
    // double deltaT = 0.57;
    // double start_time = micros();

    previousMotorLeftTurns = motorLeftTurns;
    previousMotorRightTurns = motorRightTurns;

     //descobrindo o número de rotações
    motorLeftTurns = motorLeft->getEncoder()/(double)2048;
    motorRightTurns = motorRight->getEncoder()/(double)2000; 

    // descobrindo o RPS de cada roda

    
    double rpsLeft = (motorLeftTurns - previousMotorLeftTurns)/(deltaT);
    double rpsRight = (motorRightTurns - previousMotorRightTurns)/(deltaT);

    sumRPSLeft = sumRPSLeft + rpsLeft;
    sumRPSRight = sumRPSRight + rpsRight;

    double leftError = goalRPS - rpsLeft;
    double rightError = goalRPS - rpsRight;

    leftIntegralErrorSum = add(&leftIntegralError[0],leftError*deltaT);
    rigthIntegralErrorSum = add(&rightIntegralError[0],leftError*deltaT);

    
    double PWMLeft = rpsLeft + leftError*KP_LEFT + leftIntegralErrorSum*KI_LEFT;
    double PWMRight = rpsRight + rightError*KP_RIGHT + rigthIntegralErrorSum*KI_RIGHT;

    if (PWMLeft < 0 || PWMLeft > 1.2)
    {
        PWMLeft = goalRPS;
    } 

    if (PWMRight < 0 || PWMRight > 1.2)
    {
        PWMRight = goalRPS;
    }

    double parameterPWMLeft = PWMLeft*(double)200;//198 ou 210
    double parameterPWMRight = PWMRight*(double)154; //157 ou 156 ou 140

    // double delay_time = deltaT - (micros() - start_time);
    // if (delay_time > 0){
    //     delayMicroseconds(delay_time);
    // }

    Serial.print("DeltaT: ");
    Serial.print(deltaT);
    Serial.print(" integral:");
    Serial.print(leftIntegralErrorSum);
    Serial.print(" ");
    Serial.print(rigthIntegralErrorSum);
    // Serial.print("soma RPS ");
    // Serial.print(sumRPSLeft);
    // Serial.print(" ");
    // Serial.print(sumRPSRight);
    Serial.print(" RPS: ");
    Serial.print(rpsLeft);
    Serial.print(" ");
    Serial.print(rpsRight);
    Serial.print(" > ");
    Serial.print("ERRO ");
    Serial.print(leftError);
    Serial.print(" ");
    Serial.print(rightError);
    Serial.print(" > ");
    Serial.print("RPS enviado ");
    Serial.print(PWMLeft);
    Serial.print(" ");
    Serial.print(PWMRight);
    Serial.print(" > ");
    Serial.print("no motor ");
    Serial.print(parameterPWMLeft);
    Serial.print(" ");
    Serial.println(parameterPWMRight);
 
    

    switch (direction)
    {
    case FORWARD:
        
        motorLeft->moveForward(parameterPWMLeft);
        motorRight->moveForward(parameterPWMRight);    
        break;

    case BACKWARD:
        motorLeft->moveBackward(parameterPWMLeft);
        motorRight->moveBackward(parameterPWMRight);
        break;    

    default:
        break;
    }

    // currentTime = micros() - currentTime;
    // Serial.print("tempo de execução do movePID: ");
    // Serial.println(currentTime);
}



void stop(MotorDC* motorLeft, MotorDC* motorRight){
    motorLeft->stop();
    motorRight->stop();
    return ;
}

void resetEncoders(MotorDC* motorLeft, MotorDC* motorRight){
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);

}
