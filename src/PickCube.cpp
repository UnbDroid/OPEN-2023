#include<PickCube.h>

char pick_cube_from_right( MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * lateralUltrassonicSensor, LightSensor * rightIR, Ultrassonic * frontalUltrassonicSensor, Claw * RobotClaw, Forklift * Fork){

    float frontal_distance, right_distance;
    unsigned long loopDuration = 2000;
    unsigned long startTime;
    char c = '0';

    delay(500);
    rotates(LEFT, leftMotor,rightMotor);
    delay(500);

    startTime = millis();
    loopDuration = 1800;
    while (millis() - startTime < loopDuration) {
        leftMotor->moveBackward(80);
        rightMotor->moveBackward(60);
    }

    do{
        right_distance = lateralUltrassonicSensor->distance_cm();
        //movePID(FORWARD, 60, leftMotor, rightMotor);
        leftMotor->moveForward(80);
        rightMotor->moveForward(60);
    }
    while(right_distance >= 20);

    stop(leftMotor,rightMotor);
    delay(2000);

    startTime = millis();
    loopDuration = 1350;
    while (millis() - startTime < loopDuration) {
        leftMotor->moveForward(80);
        rightMotor->moveForward(60);
    }

    stop(leftMotor,rightMotor);
    delay(500);
    rotates(RIGHT, leftMotor,rightMotor);
    delay(500);
    do{
        frontal_distance = frontalUltrassonicSensor->distance_cm();
        leftMotor->moveForward(80);
        rightMotor->moveForward(60);}
    while (frontal_distance > 17);
    stop(leftMotor,rightMotor);
    delay(500);

    Fork->forklift_down_steps(1,0);  // Não apagar essas 4 linhas pq é a integração da visão e a empilhadeira precisa estar abaixada
    delay(200);
    // c = return_type_of_cube();
    Fork->forklift_up_distance_cm(4.5);
    
    startTime = millis();
    loopDuration = 1100;
     do{
        leftMotor->moveForward(80);
        rightMotor->moveForward(60);}
    while (millis() - startTime < loopDuration);
    stop(leftMotor,rightMotor);
    delay(1000);
    startTime = millis();
    loopDuration = 500;
     do{
        leftMotor->moveBackward(80);
        rightMotor->moveBackward(60);}
    while (millis() - startTime < loopDuration);
    stop(leftMotor,rightMotor);
    delay(1000);
    Fork->forklift_down_distance_cm(2.5);
    delay(500);
    RobotClaw->close_claw_with_cube();
    // Fork->forklift_down_distance_cm(2); // Como ele subiu 4,5 cm antes, agora ele desceu 2.5cm, pegou o cubo, depois desceu mais 2 cm
    
    delay(500);

    return c;

}