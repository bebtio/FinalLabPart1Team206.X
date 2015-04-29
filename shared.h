/*
 * File:   shared.h
 * Author: albertoheras
 *
 * Created on April 13, 2015, 1:36 PM
 */

#ifndef SHARED_H
#define	SHARED_H

/******************************************************************************/
// Defines for switch
#define SW1 PORTBbits.RB5
#define PRESSED 0
#define RELEASED 1

/******************************************************************************/
// Defines for line following functionality
#define R_ID 1
#define L_ID 2
#define M_ID 3
#define shift(L,M,R) ((((0 | L) << 1) | M) << 1) | R

// The possible states of the IR Sensors
#define Right_ON  0b0100
#define Left_ON  0b0001
#define Middle_ON  0b0010
#define Left_Middle_ON 0b0011
#define Right_Middle_ON 0b0110
#define Middle_ON 0b0010
#define ALL_ON 0b0111
#define ALL_OFF 0b0000
#define Right_Left_ON 0b0101

#define ON_BLACK 1
#define OFF_BLACK 0
#define LED_ON 0
#define LED_OFF 1

#define LED_R5 LATBbits.LATB15
#define OBJECT_SENSOR TRISBbits.TRISB14

// Time Setting for dodging obstacles
#define DODGE_OBSTACLE 8

/******************************************************************************/
// For the group of IR receivers

typedef struct LMRreceiver
{
    int left_pin5;
    int middle_pin6;
    int right_pin4;

    int state;

}Sensors;

/******************************************************************************/
// State variables for line following

typedef enum
{
    initState,
    idleState,
    forwardState,
    turnAroundState,
    sensorStopState

} stateType;

/******************************************************************************/

// Global Variables
extern volatile stateType currentState;
extern volatile int lastState;
extern volatile int searchDirection;
extern volatile unsigned int turnCount;
extern volatile Sensors sensors;
extern volatile int SensorCondition;

/******************************************************************************/

#endif	/* SHARED_H */

