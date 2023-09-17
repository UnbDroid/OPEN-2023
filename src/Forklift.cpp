#include <Arduino.h>
#include <Wire.h>
#include <Forklift.h>


Forklift::Forklift(int pin_dir, int pin_pul) : StepMotor(pin_dir, pin_pul){
}

void Forklift::forklift_up_distance_cm(float distance, int velocity){
    int position = (int)(distance * this->positions_per_cm);
    this->run_motor(1, position);
}

void Forklift::forklift_down_distance_cm(float distance, int velocity){
    int position = (int)(distance * this->positions_per_cm);
    this->run_motor(0, position);
}

void Forklift::forklift_up_steps(int initial_step, int final_step, int velocity){
    float distance = 0;

    if (initial_step == 0){
        distance += this->distance0_1;
        initial_step ++;
    }

    if (initial_step == 1 && final_step > 1){
        distance += this->distance1_2;
        initial_step ++;
    }

    if (initial_step == 2 && final_step == 3){
        distance += this->distance2_3;
    }

    this->forklift_up_distance_cm(distance);
}

void Forklift::forklift_down_steps(int initial_step, int final_step, int velocity){
    float distance = 0;

    if (initial_step == 3){
        distance += this->distance3_2;
        initial_step --;
    }

    if (initial_step == 2 && final_step < 2){
        distance += this->distance2_1;
        initial_step --;
    }

    if (initial_step == 1 && final_step == 0){
        distance += this->distance1_0;
    }

    this->forklift_down_distance_cm(distance);
}
