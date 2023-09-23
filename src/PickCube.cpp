#include<PickCube.h>


char pick_cube_from_right( MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * lateralUltrassonicSensor, LightSensor * rightIR, Ultrassonic * frontalUltrassonicSensor, Claw * RobotClaw, Forklift * Fork){

    float frontal_distance, right_distance;
    unsigned long loopDuration = 2000;
    unsigned long startTime;
    char c = '0';

    delay(500);
    rotates(LEFT, leftMotor,rightMotor);
    delay(500);

    do{
        right_distance = lateralUltrassonicSensor->distance_cm();
        movePID(FORWARD, 90, leftMotor, rightMotor);
    }
    while(right_distance >= 20);

    stop(leftMotor,rightMotor);
    delay(2000);

    startTime = millis();
    loopDuration = 500;
    while (millis() - startTime < loopDuration) {
        movePID(FORWARD, 90, leftMotor, rightMotor);
    }

    stop(leftMotor,rightMotor);
    delay(500);
    rotates(RIGHT, leftMotor,rightMotor);
    delay(500);
    do{
        frontal_distance = frontalUltrassonicSensor->distance_cm();
        movePID(FORWARD, 90, leftMotor, rightMotor);}
    while (frontal_distance > 17);
    stop(leftMotor,rightMotor);
    delay(1000);
    Fork->forklift_down_steps(3,0);
    delay(2000);
    c = return_type_of_cube();
    
    Fork->forklift_up_distance_cm(5);
    startTime = millis();
    loopDuration = 500;
     do{
        frontal_distance = frontalUltrassonicSensor->distance_cm();
        movePID(FORWARD, 90, leftMotor, rightMotor);}
    while (frontal_distance > 4);
    delay(200);
    stop(leftMotor,rightMotor);
    delay(500);
    Fork->forklift_down_distance_cm(4.5);
    delay(1000);
    RobotClaw->close_claw_with_cube();
    delay(5000);
    Fork->forklift_up_steps(0,3);
    delay(500);

    return c;

}
