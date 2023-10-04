#include<Ultrassonic.h>
#include<Arduino.h>
#include<Wire.h>

Ultrassonic::Ultrassonic(int echoPin, int trigPin){
    this->echoPin = echoPin;
    this->trigPin = trigPin;

    pinMode(echoPin, INPUT); 
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
}

void Ultrassonic::send_pulse(){
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
}

float Ultrassonic::distance_meters(){
    send_pulse();
    time = pulseIn(echoPin,HIGH);
    distance = (time*0.000340)/2;

    return distance;
}

float Ultrassonic::distance_cm(){
    send_pulse();
    time = pulseIn(echoPin,HIGH);
    distance = ((time*0.000340)/2)*100;

    return distance;
}

float Ultrassonic::last_ten_values(){
    float media = 0;
    for (int i = 9; i > 0; i--) {
            this->list[i] = this->list[i - 1];
            media += this->list[i];
        }

        
        this->list[0] = this->distance_cm();
        media += this->list[0];
        return media / 10.0;
}

// float Ultrassonic::mediumValueUltrassonic(){
//     float values[3] = {0,0,0};
//     float values[3] = {0,0,0};

//     for (int i = 0; i < 3; i++)
//     {
//         values[i] = this->distance_cm();
//     }   
// }
