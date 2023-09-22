
#include <Arduino.h>
#include <Wire.h>
#include <Claw.h>


Claw::Claw(int pin_dir, int pin_pul) : StepMotor(pin_dir, pin_pul){
}

void Claw::open_claw_distance_cm(float distance, int velocity){
    int position = (int)(distance * this->positions_per_cm);
    this->run_motor(0, position);
}

void Claw::close_claw_distance_cm(float distance, int velocity){
    int position = (int)(distance * this->positions_per_cm);
    this->run_motor(1, position);
}

void Claw::open_claw_with_cube(int velocity){
    this->open_claw_distance_cm(this->distance_open_cube);
}

void Claw::open_claw_entirely(int velocity){
    this->open_claw_distance_cm(this->distance_open_entirely);
}

void Claw::close_claw_with_cube(int velocity){
    this->close_claw_distance_cm(this->distance_close_cube);
}

void Claw::close_claw_entirely(int velocity){
    this->close_claw_distance_cm(this->distance_close_entirely);
}
