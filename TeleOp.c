#pragma config(Hubs,  S4, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     irSensor,       sensorAnalog)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S4_C1_1,     rightWheel,    tmotorTetrix, openLoop, driveRight)
#pragma config(Motor,  mtr_S4_C1_2,     leftWheel,     tmotorTetrix, openLoop, driveLeft)
#pragma config(Motor,  mtr_S4_C2_1,     pulley1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     pulley2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_1,     collector1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_2,     collector2,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_6,    servo6,               tServoNone)

#include "JoystickDriver.c"

/*
 * Author:  Markus Feng, Alex Guo, William Ughetta
 * Team:    DA Roboticss
 * Project: Cascade Effect 2014
 * Program: Robot Controller
 * Date:    2015
 */

const int minSpeed = 5;
const int maxSpeed = 100;

float absSqrt(float input);
short getWheelSpeed(int controllerSpeed);
void pollControllerJoystick(short base1, short base2);
void pollControllerButtons();

task main() {
	//waitForStart(); //Enable for competition

	short basej1_y1 = joystick.joy1_y1;	//base is subtracted from reading to remove error
	short basej1_y2 = joystick.joy1_y2;

	while(true) {
		pollControllerJoystick(basej1_y1, basej1_y2);
		pollControllerButtons();
	}
}


float absSqrt(float input){
	if(input < 0){
		return -sqrt(-input);
	}
	else{
		return sqrt(input);
	}
}

short getWheelSpeed(int controllerSpeed) {
	if(controllerSpeed > maxSpeed) {
		return maxSpeed;
	}
	else if(controllerSpeed < -maxSpeed) {
		return -maxSpeed;
	}
	else if(controllerSpeed > minSpeed) {
		return controllerSpeed / 4; //slower
	}
	else if(controllerSpeed < -minSpeed) {
		return controllerSpeed / 6; //even slower going backwards
	}
	else {
		return 0;
	}
}

void pollControllerJoystick(short base1, short base2) {
	getJoystickSettings(joystick); //poll for joystick activity

	int leftSpeed = absSqrt(getWheelSpeed(joystick.joy1_y1 - base1))*10;	//read joy1, translate for motors, & apply transformation
	int rightSpeed = absSqrt(getWheelSpeed(joystick.joy1_y2 - base2))*10;

	/* if(joy1Btn(8) == 1){
		rightSpeed = rightSpeed / 2;
		leftSpeed = leftSpeed / 2;
	} */
	motor[rightWheel] = rightSpeed;
	motor[leftWheel]  = -leftSpeed;
	
}

void pollControllerButtons() {
	if(joy1Btn(5) == 1){
		motor[pulley1] = maxSpeed;
		motor[pulley2] = -maxSpeed;
	}
	else if(joy1Btn(7) == 1){
		motor[pulley1] = -maxSpeed;
		motor[pulley2] = maxSpeed;
	}
	else{
		motor[pulley1] = 0;
		motor[pulley2] = 0;
	}
	/*
		if(joy1Btn(8) == 1){
		motor[pulley2] = maxSpeed;
	}
	else if(joy1Btn(6) == 1){
		motor[pulley2] = -maxSpeed;
	}
	else{
		motor[pulley2] = 0;
	}
	*/
}
