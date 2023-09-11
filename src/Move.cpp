#include<Wire.h>
#include<Arduino.h>
#include<MotorDC.h>
#include<Move.h>
#include<LightSensor.h>
#include <Pins.h>
#include<Sol.h>
// #define deltaT 500

int previousError = 0;
long previousTime = 0;
int integralError = 0; 
int deltaT = 0.023;

int motorLeftTurns = 0;
int motorRightTurns = 0;

//PID separado motores
int previousMotorLeftTurns = 0;
int previousMotorRightTurns = 0;
int leftIntegralError = 0;
int rightIntegralError = 0;


void move(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight, LightSensor * lightSensorLeft,LightSensor* lightSensorRight){
    switch (direction)
    {
    case FORWARD:
        motorLeft->moveForward(velocity);
        motorRight->moveForward(velocity);    
        break;
    case BACKWARD:
        motorLeft->moveBackward(velocity);
        motorRight->moveBackward(velocity);
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
    int velocity = 130;
    
    motorLeft->setEncoder(0);
    motorRight->setEncoder(0);

    // int encoderLeftValue = abs(motorLeft->getEncoder());
    // int encoderRightValue = abs(motorRight->getEncoder());

    switch(rotateDirection)
    {
    case LEFT:
        motorLeft->moveBackward(velocity);
        motorRight->moveForward(velocity);
        while (abs(motorLeft->getEncoder()) < 910 && abs(motorRight->getEncoder()) < 910){
            motorLeft->moveBackward(velocity);
            motorRight->moveForward(velocity);
        }
        motorLeft->stop();
        motorRight->stop();
        break;

    case RIGHT:
        motorLeft->moveForward(velocity);
        motorRight->moveBackward(velocity);

        while (abs(motorLeft->getEncoder()) < 900 && abs(motorRight->getEncoder()) < 900){
            motorLeft->moveForward(velocity);
            motorRight->moveBackward(velocity);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break; 

    case AROUND:
        motorLeft->moveForward(velocity);
        motorRight->moveBackward(velocity);

        while (abs(motorLeft->getEncoder()) < 2010 && abs(motorRight->getEncoder()) < 2010){
            motorLeft->moveForward(velocity);
            motorRight->moveBackward(velocity);
            
        }
        motorLeft->stop();
        motorRight->stop();
        break; 
     

    default:
        break;
    }


}

void align(LightSensor * lightSensorLeft, LightSensor *lightSensorRight, MotorDC * motorLeft, MotorDC * motorRight, int velocity){
    int leftWhite = 200;
    int rightWhite = 200;
    
    motorLeft->readEncoder();
    motorRight->readEncoder();
    
    if (lightSensorLeft->read()>leftWhite || lightSensorRight->read()>rightWhite){
        Serial.println("estou me alinhando");
        stop(motorLeft,motorRight);
        delay(5000);
        
        if (lightSensorLeft->read()<leftWhite) //vê branco
        {
            Serial.print("esquerdo ve branco ");
            while (lightSensorLeft->read()<leftWhite) { // && lightSensorRight->read()>rightWhite){ // ve branco
                Serial.println(lightSensorLeft->read());
                motorLeft->moveForward(velocity+10);

                if(lightSensorRight->read()<rightWhite){
                  while (motorRight->getEncoder() < 512){
                    motorRight->moveBackward(velocity);
                  }
                }
            }

        }
        else if (lightSensorRight->read() < rightWhite) //ve branco
        {
            Serial.println("direito ve branco");
            while (lightSensorRight->read()<rightWhite) {// ve branco
                motorRight->moveForward(velocity);
                // motorLeft->moveBackward(velocity-20);
                // if(lightSensorLeft->read()<leftWhite){
                //     while (lightSensorLeft->read()<leftWhite)
                //     {
                //         motorLeft->moveBackward(velocity+10);
                //     }    
                // }    
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


void movePID(Directions direction, int velocity ,MotorDC* motorLeft, MotorDC* motorRight){
    // KD tem que compensar rapido o suficiente pro KI não ficar muito tempo errado
    // Se ele tiver oscilando demais, tira primeiro o KD e depois o KI

    
    //Controle utilizado ate então:
    long currentTime = micros();
    float deltaT = (currentTime-previousTime);
    deltaT = deltaT/1000000;
    previousTime = currentTime;

    int posEncoderLeft = motorLeft->getEncoder();
    int posEncoderRight = motorRight->getEncoder();
    int erro = posEncoderRight - posEncoderLeft;

    int derivativeErro = (erro - previousError)/deltaT;
    integralError = integralError + erro*deltaT;

    int incremento = erro*KP + derivativeErro*KD + integralError*KI;
    
    int parameterVelocityLeft = velocity + incremento;
    int parameterVelocityRight = velocity;

    previousError = erro;

    // Serial.print(erro);
    // Serial.print(" ");
    // Serial.print(integralError);
    // Serial.print(" ");
    Serial.print(parameterVelocityLeft);
    Serial.print(" ");
    Serial.println(parameterVelocityRight);
    

    


   //ideia thamires:
    // long currentTime = micros();
    // long deltaT = ((currentTime-previousTime));
    // Serial.print(currentTime);
    // Serial.print(" ");
    // Serial.print(previousTime);
    // Serial.print(" ");
    // Serial.println(deltaT);
    // previousTime = currentTime;
    
    // previousMotorLeftTurns = motorLeftTurns;
    // previousMotorRightTurns = motorRightTurns;

    // motorLeftTurns = motorLeft->getEncoder()/2048;
    // motorRightTurns = motorRight->getEncoder()/2048; // sendo o valor uma constante do sistema!! 2^12 na thamires

    //descobrindo a valocidade


    // int leftVelocity = (motorLeftTurns - previousMotorLeftTurns)/(deltaT);
    // int rightVelocity = (motorRightTurns - previousMotorRightTurns)/(deltaT);

    // int leftError = velocity - leftVelocity;
    // int rightError = velocity - rightVelocity;

    // leftIntegralError = leftIntegralError + leftError*deltaT;
    // rightIntegralError = rightIntegralError + rightError*deltaT;

    // int parameterVelocityLeft = leftError*KP_LEFT; //+ leftIntegralError*KI_LEFT;
    // int parameterVelocityRight = rightError*KP_RIGHT; // + rightIntegralError*KI_RIGHT;

    // Serial.print(motorLeftTurns);
    // Serial.print(" ");
    // Serial.print(previousMotorLeftTurns);
    // Serial.print(" ");
    // Serial.print(leftVelocity);
    // Serial.print(" ");
    // // Serial.print(" ");
    // Serial.print(parameterVelocityLeft);
    // Serial.print(" ");
    // Serial.println(parameterVelocityRight);

    // if (parameterVelocityLeft > 255){
    //     parameterVelocityLeft = 255;
    // } else if (parameterVelocityRight > 255) { 
    //     parameterVelocityRight = 255;
    // }

    // if (parameterVelocityLeft < 40){
    //     parameterVelocityLeft = 40;
    // } else if (parameterVelocityRight < 40) { 
    //     parameterVelocityRight = 40;
    // }


    switch (direction)
    {
    case FORWARD:
        
        motorLeft->moveForward(parameterVelocityLeft);
        motorRight->moveForward(parameterVelocityRight);    
        break;

    case BACKWARD:
        motorLeft->moveBackward(parameterVelocityLeft);
        motorRight->moveBackward(parameterVelocityRight);
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