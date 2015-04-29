#include "statefunctions.h"
#include "shared.h"
#include "ADC.h"
#include "PWM.h"
#include "motors.h"
#include "p24FJ64GA002.h"
#include "switch.h"
#include "timers.h"

// Functions that will be called by the  switch statement in the main function
// Perfoms the states functions.

/******************************************************************************/
// Initializes all modules and initial settings for robot operation.

void init_State()
{
    initADC();
    initPWM();
    initSW1();
    initTimer3();

    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    LED_R5 = LED_OFF;
    OBJECT_SENSOR = LED_OFF;
    sensors.left_pin5 = 0;
    sensors.right_pin4 = 0;
    sensors.middle_pin6 = 0;
    sensors.state = 0;
    turnCount = 0;

    currentState = idleState;
}

/******************************************************************************/
// Performs forward State Operations

void forward_State()
{
    getSensorVoltage();
    OBJECT_SENSOR = LED_OFF;

    // If the current state is different from the previous, give the robot time to stop
    // as to not overshoot its current position on the tape.
    if(lastState!=sensors.state)
    {
        STOP();
        delayMs(50);
        lastState = sensors.state;
    }

    // Depending on the current state, the robot will perform based on these if
    // statements.
    if(sensors.state == ALL_OFF)
    {
        if(searchDirection == Left_ON)      {   turnLeft180();     }
        else if(searchDirection == Right_ON){   turnRight180();    }
        else                                {   moveBackward();    }
    }
    else if(sensors.state == Left_ON)
    {
        moveForward();
        searchDirection = 0b0001;
    }
    else if(sensors.state == Right_ON)
    { 
        moveForward();
        searchDirection = 0b0100;
    }
    else
    {
        moveForward();
    }
    
    
}

/******************************************************************************/
// Sits and waits for SW1 to be pressed in order to go to the forward State.

void idle_State()
{
    OBJECT_SENSOR = LED_OFF;
    LED_R5 = LED_OFF;
    STOP();
}

/******************************************************************************/
// This is a consequence of the robot sensing an object in front of it and it
// remaining immobile for a preset amount of time.

void turnAround_State()
{
    turnCount = 0;
    sensors.state = ALL_OFF;

    if(searchDirection == Left_ON)      {   turnLeft180();     }
    else if(searchDirection == Right_ON){   turnRight180();    }

    delayMs(300);
    
    while(sensors.state == ALL_OFF)
    {
        getSensorVoltage();
    }
    STOP();
    currentState = forwardState;
}

/******************************************************************************/
// This state occurs when the robot senses an object, freezes and waits for
// motion to occur or for the timer to exceed its preset limit, in which case
// it will turn around.

void sensorStop_State()
{
     STOP();
     getSensorVoltage();
     OBJECT_SENSOR = LED_ON;
}

/******************************************************************************/