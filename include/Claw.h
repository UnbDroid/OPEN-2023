#ifndef __CLAW_H
#define __CLAW_H

#include "StepMotor.h"

class Claw: public StepMotor{
    public:
        Claw(int pin_dir, int pin_pul);
        void open_claw_distance_cm(float distance, int velocity = 400);
        void close_claw_distance_cm(float distance, int velocity = 400);
        void open_claw_with_cube(int velocity = 400);
        void close_claw_with_cube(int velocity = 400);
        void open_claw_entirely(int velocity = 400);
        void close_claw_entirely(int velocity = 400);

    
    private:
        float positions_per_cm = 104;
        float distance_close_cube = 9;
        float distance_open_cube = 9;
        float distance_open_entirely= 14;
        float distance_close_entirely= 14;


};

#endif
