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
double previousTime = 0;
int integralError = 0; 
double deltaT = 0.01248;//0.023;

double motorLeftTurns = 0;
double motorRightTurns = 0;

//PID separado motores
double previousMotorLeftTurns = 0;
double previousMotorRightTurns = 0;
int leftIntegralError = 0;
int rightIntegralError = 0;

void setPreviusTime(int value){
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
    
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);

    // int encoderLeftValue = abs(motorLeft->getEncoder());
    // int encoderRightValue = abs(motorRight->getEncoder());

    switch(rotateDirection)
    {
    case LEFT:
        motorLeft->moveBackward(PWM);
        motorRight->moveForward(PWM);
        while (abs(motorLeft->getEncoder()) < 910 && abs(motorRight->getEncoder()) < 910){
            motorLeft->moveBackward(PWM);
            motorRight->moveForward(PWM);
        }
        motorLeft->stop();
        motorRight->stop();
        break;

    case RIGHT:
        motorLeft->moveForward(PWM);
        motorRight->moveBackward(PWM);

        while (abs(motorLeft->getEncoder()) < 900 && abs(motorRight->getEncoder()) < 900){
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
    int leftWhite = 500;
    int rightWhite = 500;

    Serial.print("sensores IR: ");
    Serial.print(lightSensorLeft->read());
    Serial.print(" ");
    Serial.println(lightSensorRight->read());
    
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);
    
    if (lightSensorLeft->read()>leftWhite || lightSensorRight->read()>rightWhite){
        Serial.println("estou me alinhando");
        stop(motorLeft,motorRight);
        delay(5000);
        
        if (lightSensorLeft->read()<leftWhite) //vê branco
        {
            Serial.print("esquerdo ve branco ");
            while (lightSensorLeft->read()<leftWhite) { // && lightSensorRight->read()>rightWhite){ // ve branco
               
                Serial.print(lightSensorLeft->read());
                Serial.print(" ");
                Serial.println(lightSensorRight->read());

                motorLeft->moveForward(PWM+10);
                
                motorRight->setEncoder(0);
                while(motorRight->getEncoder() < 10){
                    motorRight->moveBackward(40);
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
                    motorLeft->moveBackward(50);
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



void movePID(Directions direction, float goalRPS ,MotorDC* motorLeft, MotorDC* motorRight){
    // KD tem que compensar rapido o suficiente pro KI não ficar muito tempo errado
    // Se ele tiver oscilando demais, tira primeiro o KD e depois o KI

    double currentTime = micros();
    double deltaT = (currentTime-previousTime);
    deltaT = deltaT/(double)1000000;
    previousTime = currentTime;
    
    previousMotorLeftTurns = motorLeftTurns;
    previousMotorRightTurns = motorRightTurns;

     //descobrindo o número de rotações
    motorLeftTurns = motorLeft->getEncoder()/(double)2048;
    motorRightTurns = motorRight->getEncoder()/(double)2048; 

    // descobrindo o RPS de cada roda


    double rpsLeft = (motorLeftTurns - previousMotorLeftTurns)/(deltaT);
    double rpsRight = (motorRightTurns - previousMotorRightTurns)/(deltaT);

    // conversão de rps pra pwm
    // double leftPWM = rpsLeft*199.25; //o número que multiplica é uma ct do motor. Sendo 255/RPS_Máximo
    // double rightPWM = rpsRight*185.98; 

    double leftError = goalRPS - rpsLeft;
    double rightError = goalRPS - rpsRight;

    leftIntegralError = leftIntegralError + leftError*deltaT;
    rightIntegralError = rightIntegralError + rightError*deltaT;

    
    double PWMLeft = rpsLeft + leftError*KP_LEFT + leftIntegralError*KI_LEFT;
    double PWMRight = rpsRight + rightError*KP_RIGHT + rightIntegralError*KI_RIGHT;

    double parameterPWMLeft = PWMLeft*199.25;
    double parameterPWMRight = PWMRight*170.25;

    
    Serial.print("RPS: ");
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