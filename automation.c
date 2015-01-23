#pragma config(Hubs,  S4, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S3,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          irArm,         tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          clawSide,      tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          clawFrontLeft, tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     rightWheel,    tmotorTetrix, openLoop, driveRight, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     leftWheel,     tmotorTetrix, openLoop, driveLeft, encoder)
#pragma config(Motor,  mtr_S4_C2_1,     pulley1,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_2,     pulley2,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_1,     collector1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_2,     collector2,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_6,    Center,               tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
*		Author:		Markus Feng & Alex Guo
*			Team:		DA Roboticss
*	 Project:		Cascade Effect 2014
*	 Program:		Robot Controllers
*/

#include "hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

const int minSpeed = 5;
const int maxSpeed = 100;

const int wheelDist = 32.5;

const int irRegion = 5;

const float wheelCircum = 31.415926;

#include "JoystickDriver.c"


float absSqrt(float input){
	if(input < 0){
		return -sqrt(-input);
	}
	else{
		return sqrt(input);
	}
}

/*
* 0: false
* 1: true
* -1: error
*/
int irFound(int value){
	int _dirAC = HTIRS2readACDir(HTIRS2);
	if (_dirAC <= 0){
		return -1;
	}
	if(_dirAC == value){
		return 1;
	}
	else{
		return 0;
	}
}

bool travelDistance(int leftSpeed, int rightSpeed, float distance, int mode, bool trueValue){
	nMotorEncoder[leftWheel] = 0;
	nMotorEncoder[rightWheel] = 0;

	motor[leftWheel] = -leftSpeed;
	motor[rightWheel] = rightSpeed;

	//nMotorEncoderTarget[leftWheel] = -distance*1120/wheelCircum;
	//nMotorEncoderTarget[rightWheel] = distance*1120/wheelCircum;

	//motor[leftWheel] = 0;
	//motor[rightWheel] = 0;

	//while(nMotorRunState[leftWheel] != runStateIdle && nMotorRunState[rightWheel] != runStateIdle){
	//float constant = 1.16;
	float constant = 1.10;
	if(!trueValue){
		constant = 1120/wheelCircum;
	}
	if(distance >= 0){
		while((mode != 2 || irFound(irRegion) != 1) && -1*nMotorEncoder[leftWheel] < distance*constant
			&& nMotorEncoder[rightWheel] < distance*constant){
			nxtDisplayTextLine(0, "%d", motor[leftWheel]);
			nxtDisplayTextLine(1, "%d", motor[rightWheel]);
			nxtDisplayTextLine(2, "%d", nMotorEncoder[leftWheel]);
			nxtDisplayTextLine(3, "%d", nMotorEncoder[rightWheel]);
			nxtDisplayTextLine(2, "%d", distance*constant);
		}
	}
	else{
		while((mode != 2 || irFound(irRegion) != 1) && nMotorEncoder[leftWheel]  < -1*distance*constant
			&& -1*nMotorEncoder[rightWheel] < -1*distance*constant){
			nxtDisplayTextLine(0, "%d", motor[leftWheel]);
			nxtDisplayTextLine(1, "%d", motor[rightWheel]);
			nxtDisplayTextLine(2, "%d", nMotorEncoder[leftWheel]);
			nxtDisplayTextLine(3, "%d", nMotorEncoder[rightWheel]);
			nxtDisplayTextLine(4, "%d", distance*constant);
		}
	}
	return irFound(irRegion) == 1;
}

void turn(float degrees, int speed, bool direction){
	//true = left, false = right
	float dist = 3.14*2*4550*degrees/1413;

	if(direction){
		travelDistance(0, speed*2, dist, false, true);
		}else{
		travelDistance(speed*2, 0, dist, false, true);
	}
}

void raise(int ms, bool up){
	if(up){
		servo[Center] = 125;
		wait1Msec(500);
		motor[pulley1] = maxSpeed;
		motor[pulley2] = -maxSpeed;
	}
	else{
		servo[Center] = 125;
		motor[pulley1] = -maxSpeed;
		motor[pulley2] = maxSpeed;
	}
	wait1Msec(ms);
	motor[pulley1] = 0;
	motor[pulley2] = 0;
	if(!up){
		servo[Center] = 70;
	}
}


int irRead(){
	return HTIRS2readACDir(HTIRS2);
}



task main() {
	//raise(4400, true);
	//wait1Msec(1000);
	//raise(2640, false);
	//wait1Msec(1000);
	//turn(45, 40, false);
//}

//void run(){
	/*int acx = 0;
	int ac1, ac2, ac3, ac4, ac5 = 0;
	while(true){
	HTIRS2readAllACStrength(HTIRS2, ac1, ac2, ac3, ac4, ac5);
	nxtDisplayTextLine(0, "%d", ac1);
	nxtDisplayTextLine(1, "%d", ac2);
	nxtDisplayTextLine(2, "%d", ac3);
	nxtDisplayTextLine(3, "%d", ac4);
	nxtDisplayTextLine(4, "%d", ac5);
	acx = HTIRS2readACDir(HTIRS2);
	nxtDisplayTextLine(5, "%d", acx);
	wait1Msec(1000);
	}
	}*/
	servo[servo2] = 180;
	servo[Center] = 70;

	wait1Msec(1000);
	nMotorEncoder[irArm] = 0;
	motor[irArm] = 40;
	while(nMotorEncoder[irArm] < 140){
		nxtDisplayTextLine(0, "%d", nMotorEncoder[irArm]);
	}
	motor[irArm] = 0;
	//motor[irArm] = 10;
	wait1Msec(795);
	motor[irArm] = 0;

	/*
	while(true){
	nxtDisplayTextLine(0, "%d", nMotorEncoder[irArm]);
	nxtDisplayTextLine(1, "%d", motor[irArm]);
	}
	wait1Msec(2000);
	}
	void run(){
	*/



	/*while(true){
	int j = irRead();
	//writeDebugStreamLine("Int i is		: %d", j);
	nxtDisplayTextLine(0, "%d", j);
	}
	*/
	short basej1_y2 = joystick.joy1_y2;
	short basej1_y1 = joystick.joy1_y1;

	/*
	* 0: not turning / arc
	* 1: turning
	* 2: until infrared
	* 3: distance sensor
	* 4: dump ball
	*/
	//int encoder = 0;
	int initSpeed = 40;
	//double arc = 0.6623;

	int data0len = 12;
	int data0[] = {80       ,        -90,        40,        40,        -45,        45,        30,        45,        30,        90,       100,       100}; //distance/values of until
	int data1[] = {initSpeed, -initSpeed, initSpeed, initSpeed,  0        , initSpeed, initSpeed, initSpeed, initSpeed, initSpeed, initSpeed, initSpeed}; // left speed
	int data2[] = {initSpeed,  0        , initSpeed, initSpeed, -initSpeed, initSpeed, initSpeed, 0        , initSpeed, 0        , initSpeed, initSpeed}; // right speed
	int data3[] = {0        ,1          ,2         ,0         ,1          ,2         ,0         ,1         , 2        ,1         ,0         ,0         }; // mode, see thing on top

	int data4len = 3;
	int data4[] = {2, 5, 8}; //sub-instruction groups (correspond to break of infrared)
	int data5[] = {6, 6, 6}; // length of sub-instruction group

	int data0x[] = {-16       ,90        , -0       , 4400, 180      , 100        , -20       , 90       , -5       , 4400, 180      , 100        , -12       , 90       , -40       , 4400, 180      , 100};         //sub-instruction data0
	int data1x[] = {-initSpeed, 0        , -initSpeed, 2640, 0        , initSpeed*2, -initSpeed, 0        , -initSpeed, 2640, 0        , initSpeed*2, -initSpeed, 0        , -initSpeed, 2640, 0        , initSpeed*2}; //sub-instruction data1
	int data2x[] = {-initSpeed, initSpeed, -initSpeed, 0   , initSpeed, initSpeed*2, -initSpeed, initSpeed, -initSpeed, 0   , initSpeed, initSpeed*2, -initSpeed, initSpeed, -initSpeed, 0   , initSpeed, initSpeed*2}; //sub-instruction data2
	int data3x[] = {0         ,1         , 0          ,4   , 1        , 0          , 0         , 1        , 0         , 4   , 1        , 0          , 0         , 1        , 0         , 4   , 1        , 0};           //sub-instruction data3

	/*int leftSpeed
	motor[leftWheel] = -leftSpeed;
	motor[rightWheel] = rightSpeed;
	wait1Msec(1000);
	*/

	int i = 0;

	for(; i < data0len; i++){

		/*
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;

		//Start Debug
		bool go = true;
		int n = 0;
		while(n == 0){
		getJoystickSettings(joystick);
		n = joy1Btn(Btn2);
		nxtDisplayTextLine(0, "%d", n);
		if(joy1Btn(1) == 1){
		go = false;
		break;
		}
		}
		if(!go){
		break;
		}
		*/
		//End Debug

		if(data3[i] == 0){
			travelDistance(data1[i], data2[i], data0[i], 0, false);
		}
		else if(data3[i] == 1){
			if(data1[i] == 0 && data2[i] != 0){
				turn(data0[i], data2[i], true);
			}
			else if(data1[i] !=0 && data2[i] == 0){
				turn(data0[i], data1[i], false);
			}
			else{
				//print("Error in data[][]...");
			}
		}
		else if(data3[i] == 2){
			if(travelDistance(data1[i], data2[i], data0[i], 2, false)){
				motor[leftWheel] = 0;
				motor[rightWheel] = 0;
				wait1Msec(1000);
				break;
			}
		}
		else if(data3[i] == 3){
			travelDistance(data1[i], data2[i], data0[i], 3, false);
		}
		else if(data3[i] == 4){
			wait1Msec(1000);
		}
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		wait1Msec(1000);
	}

	int totalLen = 0;
	int insLen = 0;
	for(int j = 0; j < data4len; j++){
		if(data4[j] == i){
				insLen = data5[j];
				break;
		}
		else{
			totalLen += data5[j];
		}
	}



	for(int k = totalLen; k < totalLen + insLen; k++){
		nxtDisplayTextLine(5, "%d", k);
		if(data3x[k] == 0){
			travelDistance(data1x[k], data2x[k], data0x[k], 0, false);
		}
		else if(data3x[k] == 1){
			if(data1x[k] == 0 && data2x[k] != 0){
				turn(data0x[k], data2x[k], true);
			}
			else if(data1x[k] !=0 && data2x[k] == 0){
				turn(data0x[k], data1x[k], false);
			}
			else{
				//print("Error in data[][]...");
			}
		}
		else if(data3x[k] == 2){
			if(travelDistance(data1x[k], data2x[k], data0x[k], 2, false)){
				break;
			}
		}
		else if(data3x[k] == 3){
			travelDistance(data1x[k], data2x[k], data0x[k], 3, false);
		}
		else if(data3x[k] == 4){
			raise(data0x[k], true);
			travelDistance(-initSpeed/2, -initSpeed/2, -12, 0, false);
			motor[leftWheel] = 0;
			motor[rightWheel] = 0;
			wait1Msec(500);
			servo[servo2] = 0;
			wait1Msec(2500);
			//servo[servo2] = 180;
			//wait1Msec(500);
			travelDistance(initSpeed/2, initSpeed/2, 12, 0, false);
			motor[leftWheel] = 0;
			motor[rightWheel] = 0;
			wait1Msec(500);
			raise(data1x[k], false);
			//wait1Msec(1000);
		}
		motor[leftWheel] = 0;
		motor[rightWheel] = 0;
		wait1Msec(1000);
	}
	nxtDisplayTextLine(0, "%d", 1);
	nxtDisplayTextLine(1, "%d", nMotorEncoder[leftWheel]);
	nxtDisplayTextLine(2, "%d", nMotorEncoder[rightWheel]);
	motor[leftWheel] = 0;
	motor[rightWheel] = 0;
	wait1Msec(10000);
	//1848
}
