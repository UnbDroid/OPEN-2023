#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H
    class StepMotor{
        public:
            StepMotor(int pin_dir, int pin_pul);
            int run_motor(int direction = 0, int position = 100, int velocity = 400, int time_delay = 500);


        private:
            int pin_dir;
            int pin_pul;
            
    };

#endif