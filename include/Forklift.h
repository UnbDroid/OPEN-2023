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
        void initial_lift();

    /*
        float positions_per_cm = 200;
        float distance0_1 = 3; // Distance from step 0 (floor) to 1 
        float distance1_2 = 11.5;
        float distance2_3 = 11.5;
        float distance1_0 = 3;
        float distance2_1 = 11.5;
        float distance3_2 = 11.5;
    */

    private:
        float positions_per_cm = 200;
        float distance0_1 = 2.5; // Distance from step 0 (floor) to 1 
        float distance1_2 = 11;
        float distance2_3 = 11;
        float distance1_0 = 2.5;
        float distance2_1 = 11;
        float distance3_2 = 11;
};

#endif
