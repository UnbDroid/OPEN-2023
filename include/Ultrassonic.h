
#ifndef ULTRASSONIC_H
#define ULTRASSONIC_H

    class Ultrassonic{
        public:
            Ultrassonic(int echoPin, int trigPin);

            float distance_meters();
            float distance_cm();
            void send_pulse();
            float last_ten_values();

        private:
            float distance;
            float time;
            int echoPin;
            int trigPin;   
            float list[10] = {100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0};

    };




#endif