#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//
// Eastside Preparatory FTC Robot 1 main robot control code
//

#include "EPS_JoystickDriver.c"

void EPS_initialize ()
{
	// initialization after power up and before autonomus period
	// we may put servos into a certain position etc. here
  // if we do antyhing here, don't for get to put the "robot moves during init" label on the robot!!!
}


void EPS_autonomous ()
{
	while (true)
  {
    // Get fresh raw joystick values for left stick

    getJoystickSettings(joystick);
    if (joystick.StopPgm || joystick.UserMode)
    {
    	motor[motorD] = 0;
    	motor[motorE] = 0;
    	return;
    }

 		// Move circle left, then circle right THIS IS EXAMPLE CODE ONLY

  	motor[motorD] = 20;
  	motor[motorE] = 20;

  	wait10Msec(100);

  	motor[motorD] = -20;
  	motor[motorE] = -20;

  	wait10Msec(100);

  	//
  	// Leave this in here: yield to other tasks
  	//

  	wait1Msec (4);
  }
}

void EPS_driver_control ()
	{
	float joy1x1;
	float joy1y1;
	float turn_slow_factor = 2;
	float straight_slow_factor = 2;

  motor[motorD] = 0;
  motor[motorE] = 0;

  while (true)
  {
    // Get fresh raw joystick values for left stick

    getJoystickSettings(joystick);

    joy1x1 = joystick.joy1_x1;
    joy1y1 = joystick.joy1_y1;

    // if movement smaller than calibration value (10), set to zero to switch off motors

    if (abs(joy1x1) < 10) joy1x1 = 0;
    if (abs(joy1y1) < 10) joy1y1 = 0;

    if (joy1x1 < 0)
    {
    	// moving left;
     	motor[motorD] = (int) (0);
  		motor[motorE] = (int) (joy1y1 / turn_slow_factor);
 		}
 		else if (joy1x1 > 0)
 		{
 			// moving right
  		motor[motorD] = (int) ((-1) * joy1y1 / turn_slow_factor);
     	motor[motorE] = (int) ((-1) * (0));
 		}
 		else
 		{
 			// straight forward or back
  		motor[motorD] = (int) ((-1) * (joy1y1) / straight_slow_factor);
  		motor[motorE] = (int) (joy1y1 / straight_slow_factor);
 		}


/*
    motor[motorD] = (int) ((-joy1x1-joy1y1)/2);
    motor[motorE] = (int) ((-joy1x1+joy1y1)/2);
*/

  	//
  	// yield to other tasks
  	//

  	wait1Msec (4);
  }
}


task main()
{
	while (true)
	{
		EPS_initialize ();

		waitForStart ();
		getJoystickSettings(joystick);
  	if (joystick.UserMode)
  	{
  		EPS_driver_control();
  	}
  	else
  	{
  		EPS_autonomous ();
  	}
  }
}
