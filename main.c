/*
 * File:   main.c
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "p24FJ64GA002.h"
#include "shared.h"
#include "switch.h"
#include "statefunctions.h"
#include "initObjectSensor.h"
#include "ADC.h"



_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

int main(int argc, char** argv) {

    while(1)
    {
        switch(currentState)
        {
            case initState: init_State();
                break;
            case forwardState: forward_State();
                break;
            case idleState: idle_State();
                break;
            case turnAroundState: turnAround_State();
                break;
            case sensorStopState: sensorStop_State();
                break;
        }
    }
    return (EXIT_SUCCESS);
}

/************************************************************************/

// Controls whether robot is in active or idle mode.
void _ISR _CNInterrupt()
{

    while(SW1 == PRESSED){}
    if(SW1 == RELEASED && currentState != idleState)
    {
        currentState = idleState;
    }
    else if(SW1 == RELEASED && currentState == idleState)
    {
        currentState = forwardState;
        LED_R5 = LED_ON;
    }
    IFS1bits.CNIF = 0;
}

/************************************************************************/
// Tells the robot how long it has been sitting in front of an obstacle, if the
// time is greater than a predefined amount, the robot go to the turnAroundState.
void _ISR _T3Interrupt(void)
{
    turnCount++;
    IFS0bits.T3IF = 0;

    if(turnCount >= DODGE_OBSTACLE)
    {
        currentState = turnAroundState;
        T3CONbits.TON = 0;
    }
}

/************************************************************************/

