#include<PickCube.h>

char pick_cube_from_right( MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * lateralUltrassonicSensor, Ultrassonic * frontalUltrassonicSensor, Claw * RobotClaw, Forklift * Fork, LightSensor * rightMiddleIR,LightSensor * leftMiddleIR,LightSensor * rightIR,LightSensor * leftIR, Bumper * bumper){

    float frontal_distance, right_distance;
    unsigned long loopDuration = 2000;
    unsigned long startTime;
    char c = '0';

    //move_cm(1.2,BACKWARD,leftMotor,rightMotor);
    //stop(leftMotor,rightMotor);
    //delay(500);
    //rotates(LEFT, leftMotor,rightMotor);
    //stop(leftMotor,rightMotor);
    //delay(500);
    //resetEncoders(leftMotor,rightMotor);
    /*
    while(rightMiddleIR->read()<100&&leftMiddleIR->read()<100){
        boucing(leftMotor,rightMotor,leftIR,rightIR,leftMiddleIR,rightMiddleIR);

    }
    stop(leftMotor,rightMotor);
    delay(500);
    //move_cm(30,BACKWARD,leftMotor,rightMotor);

    startTime = millis();
    loopDuration = 1800;
    
    
    stop(leftMotor,rightMotor);
    delay(500);
    */

    do{
        right_distance = lateralUltrassonicSensor->distance_cm();
        //movePID(FORWARD, 60, leftMotor, rightMotor);
        //leftMotor->moveBackward(90);
        //rightMotor->moveBackward(70);
        boucing(leftMotor,rightMotor,leftIR,rightIR,leftMiddleIR,rightMiddleIR,bumper);
    }
    while((right_distance >= 20 || right_distance < 1)&&!bumper->checkBumper());

    stop(leftMotor,rightMotor);
    delay(500);

    // startTime = millis();
    // loopDuration = 1350;
    /*
    while (millis() - startTime < loopDuration) {
        leftMotor->moveForward(80);
        rightMotor->moveForward(60);
    }
    */
    //AJUSTAR VALOR 
    // Serial.println("indo p frente");
    move_cm(3,FORWARD,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    rotates(RIGHT, leftMotor,rightMotor);
    delay(500);

    frontal_distance = frontalUltrassonicSensor->distance_cm();  
    if (frontal_distance >= 15)
        frontal_distance =15;
    
    stop(leftMotor,rightMotor);
    delay(500);

    move_cm(4,BACKWARD,leftMotor,rightMotor);
    Fork->forklift_down_steps(2,0);  // Não apagar essas 4 linhas pq é a integração da visão e a empilhadeira precisa estar abaixada
    delay(500);
    c = return_type_of_cube();
    //c='8';
    Fork->forklift_up_distance_cm(4.5);
    //checar essa distancia
    move_cm((int)(frontal_distance+9),FORWARD,leftMotor,rightMotor);



    stop(leftMotor,rightMotor);
    delay(500);
    
    move_cm(3,BACKWARD,leftMotor,rightMotor);

    stop(leftMotor,rightMotor);
    delay(500);
    Fork->forklift_down_distance_cm(4.5);
    //Fork->forklift_down_distance_cm(2.5);
    delay(500);
    RobotClaw->close_claw_with_cube();
    Fork->forklift_up_steps(0,2);
    //Fork->forklift_down_distance_cm(2); // Como ele subiu 4,5 cm antes, agora ele desceu 2.5cm, pegou o cubo, depois desceu mais 2 cm

    return c;

}


char pick_cube_from_left( MotorDC * leftMotor, MotorDC * rightMotor, Ultrassonic * lateralUltrassonicSensor, Ultrassonic * frontalUltrassonicSensor, Claw * RobotClaw, Forklift * Fork, LightSensor * rightMiddleIR,LightSensor * leftMiddleIR,LightSensor * rightIR,LightSensor * leftIR, Bumper * bumper){

    float frontal_distance, left_distance;
    unsigned long loopDuration = 2000;
    unsigned long startTime;
    char c = '0';

    //move_cm(1.2,BACKWARD,leftMotor,rightMotor);
    //stop(leftMotor,rightMotor);
    //delay(500);
    //rotates(LEFT, leftMotor,rightMotor);
    //stop(leftMotor,rightMotor);
    //delay(500);
    //resetEncoders(leftMotor,rightMotor);
    /*
    while(rightMiddleIR->read()<100&&leftMiddleIR->read()<100){
        boucing(leftMotor,rightMotor,leftIR,rightIR,leftMiddleIR,rightMiddleIR);

    }
    stop(leftMotor,rightMotor);
    delay(500);
    //move_cm(30,BACKWARD,leftMotor,rightMotor);

    startTime = millis();
    loopDuration = 1800;
    
    
    stop(leftMotor,rightMotor);
    delay(500);
    */

    do{
        left_distance = lateralUltrassonicSensor->distance_cm();
        //movePID(FORWARD, 60, leftMotor, rightMotor);
        //leftMotor->moveBackward(90);
        //rightMotor->moveBackward(70);
        boucing(leftMotor,rightMotor,leftIR,rightIR,leftMiddleIR,rightMiddleIR,bumper);
    }
    while((left_distance >= 20 || left_distance < 1)&&!bumper->checkBumper());

    stop(leftMotor,rightMotor);
    delay(500);

    // startTime = millis();
    // loopDuration = 1350;
    /*
    while (millis() - startTime < loopDuration) {
        leftMotor->moveForward(80);
        rightMotor->moveForward(60);
    }
    */
    //AJUSTAR VALOR 
    // Serial.println("indo p frente");
    move_cm(2,FORWARD,leftMotor,rightMotor);
    stop(leftMotor,rightMotor);
    delay(500);

    rotates(LEFT, leftMotor,rightMotor);
    delay(500);

    frontal_distance = frontalUltrassonicSensor->distance_cm();  
    if (frontal_distance >= 15){
        frontal_distance =15;}
    
    stop(leftMotor,rightMotor);
    delay(500);

    move_cm(4,BACKWARD,leftMotor,rightMotor);
    Fork->forklift_down_steps(2,0);  // Não apagar essas 4 linhas pq é a integração da visão e a empilhadeira precisa estar abaixada
    delay(500);
    c = return_type_of_cube();
    //c='8';
    Fork->forklift_up_distance_cm(4.5);
    //checar essa distancia
    move_cm((int)(frontal_distance+9),FORWARD,leftMotor,rightMotor);



    stop(leftMotor,rightMotor);
    delay(500);
    
    move_cm(3,BACKWARD,leftMotor,rightMotor);

    stop(leftMotor,rightMotor);
    delay(500);
    Fork->forklift_down_distance_cm(4.5);
    //Fork->forklift_down_distance_cm(2.5);
    delay(500);
    RobotClaw->close_claw_with_cube();
    Fork->forklift_up_steps(0,2);
    //Fork->forklift_down_distance_cm(2); // Como ele subiu 4,5 cm antes, agora ele desceu 2.5cm, pegou o cubo, depois desceu mais 2 cm

    return c;

}