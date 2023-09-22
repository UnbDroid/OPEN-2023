#include <StepMotor.h>
#include <Arduino.h>
#include <Wire.h>


StepMotor::StepMotor(int pin_dir, int pin_pul){

    this->pin_dir = pin_dir;
    this->pin_pul = pin_pul;   

    pinMode(this->pin_dir, OUTPUT);
    pinMode(this->pin_pul, OUTPUT);
}

int StepMotor::run_motor(int direction, int position, int velocity, int time_delay){  // Direction == 0 -> Clockwise, else: Counterclockwise
    
    int delay_per_pulse = time_delay/velocity;

    if (direction){
        digitalWrite(this->pin_dir, LOW); 
    }
    else{
        digitalWrite(this->pin_dir, HIGH);
    }

    for (int i = 0; i < position; i++){
        // Serial.println(i);
        digitalWrite(this->pin_pul, HIGH);
        delay(delay_per_pulse);
        digitalWrite(this->pin_pul, LOW);
        delay(delay_per_pulse);}

    return 0;
}


