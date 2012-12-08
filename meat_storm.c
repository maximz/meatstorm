#pragma config(Sensor, dgtl1,  rightTowerEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rwheelEncoder,  sensorRotation)
#pragma config(Sensor, dgtl4,  lwheelEncoder,  sensorRotation)
#pragma config(Sensor, dgtl6,  rightBackBumper,        sensorTouch)
#pragma config(Sensor, dgtl7,  leftBackBumper,        sensorTouch)
#pragma config(Motor,  port2,           rightTower,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           leftTower,     tmotorVex393, openLoop)
#pragma config(Motor,  port6,           intake,        tmotorNormal, openLoop)
#pragma config(Motor,  port8,           leftWheel,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           rightWheel,    tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

 // Low-level movement methods for autonomous
#include "autonomous.c"

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
	while(true)
	{
			if(SensorValue[leftBackBumper] == 1)
			{
					currentX = 12;
					currentY= 18;
					goTo(24,48);
					pickup();
					goTo(12, 18);
					break;
			}
			else if (SensorValue[rightBackBumper] == 1)
			{
					currentX = 36;
					currentY= 18;
					goTo(24,48);
					pickup();
					goTo(36, 18);
					break;
			}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop
	float threshold = 12.7;
	bool isIntakeOn = false;
	bool wasChangingIntake = false;

	while (true)
	{
		// base wheels: joystick movement
	  if (abs(vexRT[Ch3]) > threshold)
	  {
	  	motor[leftWheel] = vexRT[Ch3];
		}
		else
		{
				motor[leftWheel] = 0;
		}
		if (abs(vexRT[Ch2]) > threshold)
		{
			motor[rightWheel] = vexRT[Ch2];
		}
		else
		{
			motor[rightWheel] = 0;
		}

		// tower motors: press and hold to activate
		if (vexRT[Btn6U] == 1)
		{
			motor[rightTower] = 90;
			motor[leftTower] = 90;
		}
		else if (vexRT[Btn6D] == 1)
		{
			motor[rightTower] = -90;
			motor[leftTower] = -90;
		}
		else
		{
			motor[rightTower] = 0;
			motor[leftTower] = 0;
		}
		/*
		if(vexRT[Btn5U] == 1)
			{
				motor[intake] = 90;
			}
		else if(vexRT[Btn5D] == 1)
			{
			motor[intake] = -90;
		}
		else
			{
			motor[intake] = 0;
		}
		*/

		/*
		* Note for implementing toggle controls:
		*
		* The robot runs through the entire while loop faster than you can press and release the button.
		* That means that a condition like if (vexRT[Btn5U] == 1) will be true multiple times.
		* Thus, you cannot just look for when that button is pressed and then toggle whether the motors are enabled.
		*
		* You have to make sure there is a time in between button presses where the button is not pressed,
		* meaning the button-is-pressed situations are not from a single press.
		*
		* See below for a good way to implement toggling buttons.
		*/

		// intake motors: toggle controls. 5U toggles on+in vs. off; 5D toggles on+out vs. off; either button can turn off any motor activity.
		if (vexRT[Btn5U] == 1) // up button pressed, toggle on+in vs off.
		{
			if(!wasChangingIntake) // only respond if it's a new signal; we turn off wasChangingIntake as soon as we get a time where neither button is pressed
			{
				if(!isIntakeOn) // intake is currently off, so let's turn it on
				{
						motor[intake] = 90;
				}
				else
				{
						motor[intake] = 0;
				}
				wasChangingIntake = true; // ensure that we do not respond again to this button press; the next repsonse to this button will only happen after we set wasChangingIntake to false when neither button is pressed
			}
		}
		else if (vexRT[Btn5D] == 1) // down button pressed, toggle on+out vs off.
		{
			if(!wasChangingIntake) // only respond if it's a new signal; we turn off wasChangingIntake as soon as we get a time where neither button is pressed
			{
				if(!isIntakeOn) // intake is currently off, so let's turn it on
				{
						motor[intake] = -90;
				}
				else
				{
						motor[intake] = 0;
				}
				wasChangingIntake = true; // ensure that we do not respond again to this button press; the next repsonse to this button will only happen after we set wasChangingIntake to false when neither button is pressed
			}
		}
		else // neither button is pressed, so we might be anticipating a toggle button press to turn the motors off.
		{
				if(wasChangingIntake) // if we had just been changing the intake motor and then let go
				{
						isIntakeOn = !isIntakeOn; // toggle isIntakeOn to update to new state
						wasChangingIntake = false; // reset so that we can respond to the next button press
				}
		}


	} // end while loop

} // end usercontrol task
