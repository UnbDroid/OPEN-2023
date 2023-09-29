
#ifndef BUMPER_H
#define BUMPER_H
    class Bumper{
        public: 
            Bumper(int pinBumper);

            bool checkBumper();
            

        private:
            int pinBumper;
    };
#endif