#ifndef MOTORDC_H
#define MOTORDC_H
    class MotorDC{
        public: 
            MotorDC(int pinoLpwm, int pinoRpwm, int pinoEN, int pinEncA, int pinEncB);
            // MotorDC(int pinoA, int pinoB, int pinoPwm);
            // ~MotorDC();
            void moveForward(int velocity);
            void moveBackward(int velocity);
            void readEncoder();
            void stop();
            void stopLow();
            unsigned int getEncoder();
            int setEncoder(int value);

        private:
            int velocity;
            int pinoRpwm;
            int pinoLpwm;
            int pinoEN;
            unsigned int posEncoder = 0; 
            int pinEncA;
            int pinEncB;
            int value;
    };
#endif