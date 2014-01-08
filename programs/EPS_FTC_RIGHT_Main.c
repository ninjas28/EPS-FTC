#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//
// Eastside Preparatory FTC Robot 1 main robot control code
//

#include "EPS_JoystickDriver.c"
#include "hitechnic-irseeker-v2.h"
#define button1   0x01
#define button2   0x02
#define button3   0x04
#define button4   0x08
#define button5   0x10
#define button6   0x20
#define button7   0x40
#define button8   0x80
#define button9  0x100
#define button10 0x200
#define SCOOP_UP 128
#define SCOOP_DOWN 0
#define CHECK_FOR_STOP() {getJoystickSettings(joystick); if (joystick.StopPgm) return;}

void PlayNote (int index, float beats, float pause)
{
	PlayImmediateTone (((float)200*(pow(1.08333333,index))), (beats - pause)*25);
	writeDebugStreamLine ("Freq: %f", ((float)300*(pow(1.08333333,index))));
	if (pause > 0)
	{
		wait10Msec ((beats - pause) * 25);
		ClearSounds();
		wait10Msec (pause * 25);
	}
	else
	{
		wait10Msec (beats * 25);
	}

}

void EPS_WeAreTheChampions (void)
{
	ClearSounds();
	PlayNote (10, 4, 0.3);
	PlayNote (9, 1, 0);
	PlayNote (10, 1, 0);
	PlayNote (9, 3, 0.3);
	PlayNote (6, 3, 0);
}

void EPS_Housework (void)
{
	ClearSounds();

	PlayNote (10, 0.5, 0.2);
	PlayNote (10, 0.5, 0.2);
	PlayNote (10, 0.5, 0.2);
	PlayNote (10, 1, 0.2);
	PlayNote (10, 0.5, 0.2);
	PlayNote (8,1, 0.2);
	PlayNote (11, 1, 0.2);
}

void MoveClaw (int amount)
{
	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorB] = 0;
	nMotorEncoderTarget[motorA]= abs(amount);
	nMotorEncoderTarget[motorB]= abs(amount);

motor[motorA] = (amount >0 ? 20:-20);
motor[motorB] = (amount >0 ? 20:-20);
	int i = 5000;
	while (nMotorRunState[motorA] != runStateIdle && nMotorRunState[motorB] != runStateIdle && i > 0) {
		i-= 1;
	}

	motor[motorA] = 0;
	motor[motorB] = 0;

}


void EPS_initialize ()
{
	// initialization after power up and before autonomus period
	// we may put servos into a certain position etc. here
	// if we do antyhing here, don't for get to put the "robot moves during init" label on the robot!!!

	EPS_WeAreTheChampions ();
	//	nSyncedMotors = synchAB;
	//	nSyncedTurnRatio = -100;

	//MoveClaw(-20);o
	//wait10Msec (100);
	//MoveClaw(20);



}

int ret = 1;
void EPS_autonomous_work ()
{
	if(ret == 1)
	{
		EPS_Housework();
		motor[motorD] = 0;
		motor[motorE] = 0;
		//forward
		servoChangeRate[servo1] = 1;
		motor[motorD] = -100;
		motor[motorE] = 100;
		wait10Msec(90);
		CHECK_FOR_STOP();
		//stop
		servo[servo1] = SCOOP_DOWN;
		wait10Msec(20);
		motor[motorD] = 0;
		motor[motorE] = 0;
		wait10Msec(60);
		CHECK_FOR_STOP();
		//move back
		motor[motorD] = 100;
		motor[motorE] = -100;
		wait10Msec(50);
		CHECK_FOR_STOP();
		//stop and close claw
		motor[motorD] = 0;
		motor[motorE] = 0;
		wait10Msec(100);
		servo[servo1] = SCOOP_UP;
		CHECK_FOR_STOP();
		//turn
		motor[motorD] = -50;
		motor[motorE] = -100;
		wait10Msec(100);
		servo[servo1] = SCOOP_UP;
		CHECK_FOR_STOP();
		//forward
		motor[motorD] = -100;
		motor[motorE] = 100;
		wait10Msec(150);
		CHECK_FOR_STOP();
		//turn
		motor[motorD] = 100;
		motor[motorE] = 100;
		wait10Msec(100);
		servo[servo1] = SCOOP_UP;
		CHECK_FOR_STOP();
		//forward
		motor[motorD] = -100;
		motor[motorE] = 100;
		wait10Msec(240);
		CHECK_FOR_STOP();
		////turn
		//////motor[motorD] = -40;
		//////motor[motorE] = 0;
		//////wait10Msec(80);
		//CHECK_FOR_STOP();
		//////forward
		//////motor[motorD] = -50;
		//////motor[motorE] = 50;
		//////wait10Msec(200);
		//CHECK_FOR_STOP();
		//stop
		motor[motorD] = 0;
		motor[motorE] = 0;
		wait10Msec(5000);
		PlayNote(200,3,0);
		servo[servo1] = SCOOP_UP;
		wait10Msec(300);
		servo[servo1] = SCOOP_DOWN;
	}
}


void EPS_autonomous ()
{
	EPS_autonomous_work();
	motor[motorD] = 0;
	motor[motorE] = 0;
	return;
}

void EPS_driver_control ()
{
	int joyvalueX[] = {-75,-40,40,75};
	int joyvalueY[] = {-75,-40,40,75};

	int leftMotorMatrix[5][5] = {{-100,-50,100,0,0},
	  											  	 {-30,20,50,0,0},
	  												   {50,0,0,0,-50},
	  											  	 {-30,0,-50,0,0},
	  											 	   {0,0,-100,0,0}};
	int rightMotorMatrix[5][5] = {{0,0,-100,50,100},
	  											  	  {0,0,-50,25,30},
	  											  	  {50,0,0,0,-50},
	  											  	  {0,0,50,0,30},
	  											  		{0,0,100,0,-50}};
	//EPS_Housework();
  while (true)
  {
		int ix, iy, joy1x1, joy1y1, joy2y2;
		getJoystickSettings(joystick);
		joy2y2 = joystick.joy1_y2;
    joy1x1 = joystick.joy1_x1;
		joy1y1 = joystick.joy1_y1;
		short btn1 = joy1Btn(1);
		short btn3 = joy1Btn(3);
		short btn6 = joy1Btn(6);
		short btn7 = joy1Btn(7);
		short btn2 = joy1Btn(2);

		if (joystick.StopPgm) {
      break;
  	}
		for(iy=0;iy<4;iy++) {
			if(joy1y1 < joyvalueY[iy]) {
				break;
			}
		}
		for(ix=0;ix<4;ix++) {
			if(joy1x1 < joyvalueX[ix]) {
				break;
			}
		}
		motor[motorD] = leftMotorMatrix[iy][ix];
		motor[motorE] = rightMotorMatrix[iy][ix];

		// servo control
		//

		//int buttons = joystick.joy1_Buttons;

		if(joy2y2 > 3)
		{
			servo[servo1] = SCOOP_DOWN;

		}
		if(joy2y2 < -3)
		{
			servo[servo1] = SCOOP_UP;
		}

		if(btn1 > 0) {
			servoChangeRate[servo1] = servoChangeRate[servo1] + 1;
		}

		if(btn3 > 0) {
			servoChangeRate[servo1] = servoChangeRate[servo1] - 1;
		}
		if(btn6 != 0) {
			motor[motorA] = 100;
		}
		else if (btn7 != 0) {
			motor[motorA] = -100;
		}
		else {
			motor[motorA] = 0;
		}
		if(btn2 > 0) {
			motor[motorA] = 0;
			motor[motorD] = 0;
			motor[motorE] = 0;
		}

		wait1Msec (4);
	}
	motor[motorA] = 0;
	motor[motorD] = 0;
	motor[motorE] = 0;
}



task main()
{
	bool bAutoDone = false;
	EPS_initialize ();
	//EPS_autonomous_work();
	while (true)
	{
		waitForStart ();

		getJoystickSettings(joystick);
		if (joystick.UserMode || bAutoDone)
		{
			EPS_driver_control();
		}
		else
		{
			EPS_autonomous ();
			bAutoDone = true;
		}
	}
}
