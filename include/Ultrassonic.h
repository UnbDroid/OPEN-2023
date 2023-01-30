
#ifndef ULTRASSONIC_H
#define ULTRASSONIC_H

    class Ultrassonic{
        public:
            Ultrassonic(int echoPin, int trigPin);

            float distance_meters();
            float distance_cm();
            void send_pulse();

        private:
            float distance;
            float time;
            int echoPin;
            int trigPin;   
    };




#endif