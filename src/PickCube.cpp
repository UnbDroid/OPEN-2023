#include<PickCube.h>

int pick_cube_from_right( MotorDC * leftMotor, MotorDC * rightMotor, LightSensor * light_LateralRight, LightSensor * rightIR, Ultrassonic * ultrassonicSensor, Claw * RobotClaw){
    int count, max_distance_right, right_distance, right_floor;
    float frontal_distance;
    max_distance_right = 0;

    // delay(3000);
    // leftMotor->moveForward(75);
    // rightMotor->moveForward(55);
    // delay(800);
    // stop(leftMotor,rightMotor);
    delay(2000);
    rotates(LEFT, leftMotor,rightMotor);
    delay(2000);


    for (count = 0; count < 30; count++){
        max_distance_right += light_LateralRight->read();
    }
    max_distance_right /= 30;

    do{
        right_distance = light_LateralRight->read();
        right_floor = rightIR->read();
        // if (right_floor < 100){
        //     rightMotor->moveForward(45);
        // }
        // else if (right_floor < 800){
        //     rightMotor->moveForward(42 + (int)(right_floor/35));
        // }
        // else{
        //     rightMotor->moveForward(65);
        // }
        rightMotor->moveForward(55);
        leftMotor->moveForward(75);
    }
    while(right_distance >= max_distance_right - 20);

    stop(leftMotor,rightMotor);
    delay(2000);
    leftMotor->moveForward(85);
    rightMotor->moveForward(75);
    delay(500);
    stop(leftMotor,rightMotor);
    delay(2000);
    rotates(RIGHT, leftMotor,rightMotor);
    delay(2000);
    do{
        // frontal_distance = ultrassonicSensor->distance_cm();
        frontal_distance = 5;
        leftMotor->moveForward(75);
        rightMotor->moveForward(55);}
    while (frontal_distance > 10);
    delay(700);
    stop(leftMotor,rightMotor);
    delay(3000);
    RobotClaw->close_claw_with_cube();
    delay(2000);

    return 0;

}


int pick_cube_from_left (MotorDC * leftMotor, MotorDC * rightMotor, LightSensor * light_LateralLeft){
    int count, max_distance_left, left_distance;
    max_distance_left = 0;
    for (count = 0; count < 30; count++){
        max_distance_left += light_LateralLeft->read();
    }
    max_distance_left /= 30;

    do{
        left_distance = light_LateralLeft->read();
        leftMotor->moveForward(75);
        rightMotor->moveForward(55);
    }
    while(left_distance >= max_distance_left - 30);

    stop(leftMotor,rightMotor);
    delay(2000);
    leftMotor->moveForward(95);
    rightMotor->moveForward(65);
    delay(500);
    stop(leftMotor,rightMotor);
    delay(2000);
    rotates(LEFT, leftMotor,rightMotor);
    delay(2000);
    leftMotor->moveForward(75);
    rightMotor->moveForward(55);
    delay(2000);

    return 0;
    
}