#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Ultrassonic.h>>
#include <Pins.h>
#include<Sol.h>
// #define deltaT 500

int previousError = 0;
long previousTime = 0;
int integralError = 0; 
double deltaT = 0.01248;//0.023;

double motorLeftTurns = 0;
double motorRightTurns = 0;

//PID separado motores
double previousMotorLeftTurns = 0;
double previousMotorRightTurns = 0;
int leftIntegralError = 0;
int rightIntegralError = 0;


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
    int leftWhite = 140;
    int rightWhite = 140;
    
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
                Serial.println(lightSensorLeft->read());
                motorLeft->moveForward(PWM+10);
                if(lightSensorRight->read()<rightWhite){
                    motorRight->readEncoder();
                    while (motorRight->getEncoder() < 1024){
                    motorRight->moveBackward(PWM);
                  }
                  Serial.println("sai 1");
                }
            }

        }
        else if (lightSensorRight->read() < rightWhite) //ve branco
        {
            Serial.println("direito ve branco");
            while (lightSensorRight->read()<rightWhite) {// ve branco
                motorRight->moveForward(PWM);
                if(lightSensorLeft->read()<leftWhite){
                motorLeft->readEncoder();
                while (motorLeft->getEncoder() < 1024){
                    motorLeft->moveBackward(PWM);
                  }
                Serial.println("sai");
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



void movePID(Directions direction, int goalPWM ,MotorDC* motorLeft, MotorDC* motorRight){
    // KD tem que compensar rapido o suficiente pro KI não ficar muito tempo errado
    // Se ele tiver oscilando demais, tira primeiro o KD e depois o KI

    double currentTime = micros();
    double deltaT = ((currentTime-previousTime));
    deltaT = deltaT/(double)1000000;
    previousTime = currentTime;
    
    previousMotorLeftTurns = motorLeftTurns;
    previousMotorRightTurns = motorRightTurns;

    motorLeftTurns = motorLeft->getEncoder()/(double)2048;
    motorRightTurns = motorRight->getEncoder()/(double)2048; // sendo o valor uma constante do sistema!! 2^12 na thamires

    // descobrindo o RPM e o PWM atual do robô

    double leftPWM = (motorLeftTurns - previousMotorLeftTurns)/(deltaT);
    double rightPWM = (motorRightTurns - previousMotorRightTurns)/(deltaT);
    //constante do sistema direito 1.8388671875
    //constante do sistema esquerdo 1.77099609375

    rightPWM = rightPWM*158.28; // conversão de rps pra pwm
    leftPWM = leftPWM*148.19;
    

    double leftError = goalPWM - leftPWM;
    double rightError = goalPWM - rightPWM;

    leftIntegralError = leftIntegralError + leftError*deltaT;
    rightIntegralError = rightIntegralError + rightError*deltaT;

    double parameterPWMLeft = leftPWM + leftError*KP_LEFT + leftIntegralError*KI_LEFT;
    double parameterPWMRight = rightPWM + rightError*KP_RIGHT + rightIntegralError*KI_RIGHT;
    
    // // Serial.print(" ");
    // Serial.print(leftPWM);
    // Serial.print(" ");
    Serial.print(leftPWM);
    Serial.print(" ");
    Serial.println(leftError);

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