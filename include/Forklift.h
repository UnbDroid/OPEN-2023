#ifndef __FORKLIFT_H
#define __FORKLIFT_H

#include "StepMotor.h"

class Forklift: public StepMotor{
    public:
        Forklift(int pin_dir, int pin_pul);
        void forklift_up_distance_cm(float distance, int velocity = 400);
        void forklift_down_distance_cm(float distance, int velocity = 400);
        void forklift_up_steps(int initial_step, int final_step, int velocity = 400);
        void forklift_down_steps(int initial_step, int final_step, int velocity = 400);



    private:
        int positions_per_cm = 30;
        float distance0_1; // DIstance from step 0 (floor) to 1 
        float distance1_2;
        float distance2_3;
        float distance1_0;
        float distance2_1;
        float distance3_2;
};

#endif
