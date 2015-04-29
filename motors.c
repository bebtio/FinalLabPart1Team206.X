/*
 * File:   motors.c
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */
#include "motors.h"
#include "PWM.h"
#include "p24FJ64GA002.h"


// Defines for motor function setting editing.
#define MAX_SPEED 1.0
#define LOW -1
#define ON 0
#define OFF 1
#define OUTPUT 0
#define R_moveForward   MAX_SPEED*0.92
#define L_moveForward   MAX_SPEED*1.0
#define _turnLeft       MAX_SPEED*0.55
#define _turnRight      MAX_SPEED*0.55
#define _turnRight180   MAX_SPEED*.70
#define _turnLeft180    MAX_SPEED*.70
#define _steering       MAX_SPEED*.65

/**************************************************************************************/

// This moves the robot forward by calling the functions that move each
// wheel forward independently
void moveForward()
{
    LWForward(L_moveForward);
    RWForward(R_moveForward);
}

/**************************************************************************************/

// This moves the robot backward by calling the functions that move each
// wheel backward independently
void moveBackward()
{
    LWBackward(L_moveForward);
    RWBackward(R_moveForward);

}

/**************************************************************************************/

// Stops the robots motions by setting all Duty cylces equal to eachother
void STOP()
{
    RWStop();
    LWStop();
}

/**************************************************************************************/
// Stops the right wheel.
void RWStop()
{
    setDutyCycleOCM3(LOW);
    setDutyCycleOCM1(LOW);
}

/**************************************************************************************/
// Stops the left wheel.
void LWStop()
{
    setDutyCycleOCM4(LOW);
    setDutyCycleOCM2(LOW);
}

/**************************************************************************************/
// Pivots the robot on the left wheel.
void turnLeft()
{
    LWStop();
    RWForward(_turnLeft);
}

/**************************************************************************************/
// Pivots the robot on the right wheel.
void turnRight()
{
    RWStop();
    LWForward(_turnRight);
}

/**************************************************************************************/
// Rotates the robot clockwise.
void turnRight180()
{
    LWForward(_turnRight180);
    RWBackward(_turnRight180);
}

/**************************************************************************************/
// Rotates the robot counter clockwise
void turnLeft180()
{
    LWBackward(_turnLeft180);
    RWForward(_turnLeft180);
}

/**************************************************************************************/
// Steers the robot right by setting the RW duty cycle slower than the left's.
void steerRight(float steerControl)
{
    RWForward(steerControl);
    LWForward(MAX_SPEED);
}

/**************************************************************************************/
// Steers the robot to the right by setting the LW duty cycle slower than the right's.
void steerLeft(float steerControl)
{
    RWForward(MAX_SPEED);
    LWForward(steerControl);
}

/**************************************************************************************/
// Moves the Left wheel forward.
void LWForward(float DC)
{
    setDutyCycleOCM3(DC);
    setDutyCycleOCM4(LOW);
}

/**************************************************************************************/

// Moves the Right wheel forward.
void RWForward(float DC)
{
    setDutyCycleOCM1(DC);
    setDutyCycleOCM2(LOW);
}

/**************************************************************************************/

// Moves the Right wheel backward.
void RWBackward(float DC)
{
    setDutyCycleOCM1(LOW);
    setDutyCycleOCM2(DC);
}

/**************************************************************************************/

// Moves the Left wheel bacwkard.
void LWBackward(float DC)
{
    setDutyCycleOCM3(LOW);
    setDutyCycleOCM4(DC);
}

/**************************************************************************************/



