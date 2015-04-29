#include "ADC.h"
#include "motors.h"
#include "timers.h"
#include "math.h"
#include "shared.h"
#include "p24FJ64GA002.h"
#include <stdio.h>
#include <stdlib.h>

// Defines for converting.
#define ON 1
#define OFF 0
#define convert(x)  (x/1023.0)*5.0
#define distanceReading(x) (27.86)*(pow(x,-1.15))
#define threshold_distance 20

/*
 * File:   ADC.c
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */


/******************************************************************************/

// Initializes the ADC to read an analog voltage from the potentiometer
void initADC()
{
    AD1PCFGbits.PCFG0 = 0; // PIN2 ON PIC
    AD1PCFGbits.PCFG1 = 0; // PIN3 ON PIC
    AD1PCFGbits.PCFG2 = 0; // PIN4 ON PIC
    AD1PCFGbits.PCFG2 = 0; // PIN5 ON PIC

    TRISAbits.TRISA0 = 1;  // PIN2 ON PIC
    TRISBbits.TRISB14 = 1; // PIN3 ON PIC
    TRISBbits.TRISB2 = 1;  // PIN4 ON PIC
    TRISBbits.TRISB3 = 1;  // PIN5 ON PIC

    AD1CSSLbits.CSSL0 = 1; // PIN2 ON PIC
    AD1CSSLbits.CSSL1 = 1; // PIN3 ON PIC
    AD1CSSLbits.CSSL2 = 1; // PIN4 ON PIC
    AD1CSSLbits.CSSL3 = 1; // PIN5 ON PIC

    AD1CON1bits.FORM = 0;       // Output formatted as an integer
    AD1CON1bits.SSRC = 0b0111;  // Auto internal clock usage
    AD1CON1bits.ASAM = 0;       // Auto start sampling

    AD1CON2bits.VCFG = 0;       // Uses system voltage for reference voltages
    AD1CON2bits.CSCNA = 1;      // Uses CH0SA bits as MUXA input, inputs only work on MUXA
    AD1CON2bits.SMPI = 0b1111;  // Interrupt at 16th sample convert sequence
    AD1CON2bits.ALTS = 0;       // Always uses MUXA input multiplexor settings

    AD1CON3bits.ADRC = 0;       // Uses system clock for conversions
    AD1CON3bits.SAMC = 1;       // 1 = use TAD
    AD1CON3bits.ADCS = 10;      // Clock period select bits = 10 so *FCY
    AD1CHS = 0;                 // Connect pin as positive input: AN0
    AD1CON1bits.ADON = 1;       // Turn on A/D

    IFS0bits.AD1IF = 0;         //Put the flag down
}

/******************************************************************************/

// Takes value from the ADC buffer and returns that value
void getSensorVoltage()
{
    int i = 0;

    // These will hold the voltage reading from each of the buffers in the PIC
    float rSensor[5];
    float mSensor[5];
    float lSensor[5];
    float oSensor[5];

    IFS0bits.AD1IF = 0;         // Puts A/D flag down
    AD1CON1bits.ASAM = ON;      // Starts Auto Sampling
    while (!IFS0bits.AD1IF){};  // Waits for sampling to finish
    AD1CON1bits.ASAM = OFF;     // Stops sampling


    // Converts the Voltage Value from a Binary number to Decimal
    rSensor[0] = convert(ADC1BUF0);
    rSensor[1] = convert(ADC1BUF4);
    rSensor[2] = convert(ADC1BUF8);
    rSensor[3] = convert(ADC1BUFC);
    rSensor[4] = 0;
    
    mSensor[0] = convert(ADC1BUF1);
    mSensor[1] = convert(ADC1BUF5);
    mSensor[2] = convert(ADC1BUF9);
    mSensor[3] = convert(ADC1BUFD);
    mSensor[4] = 0;

    lSensor[0] = convert(ADC1BUF2);
    lSensor[1] = convert(ADC1BUF6);
    lSensor[2] = convert(ADC1BUFA);
    lSensor[3] = convert(ADC1BUFE);
    lSensor[4] = 0;

    oSensor[0] = (convert(ADC1BUF3));
    oSensor[1] = (convert(ADC1BUF7));
    oSensor[2] = (convert(ADC1BUFB));
    oSensor[3] = (convert(ADC1BUFF));
    oSensor[4] = 0;

    // Sums the read Values
    for(i = 0; i <4; i++)
    {
        rSensor[4] = (rSensor[i] + rSensor[4]);
        lSensor[4] = (lSensor[i] + lSensor[4]);
        mSensor[4] = (mSensor[i] + mSensor[4]);
        oSensor[4] = (oSensor[i] + oSensor[4]);
    }

    // Averages this sum for higher accuracy readings
    rSensor[4] = (rSensor[4])/4;
    lSensor[4] = (lSensor[4])/4;
    mSensor[4] = (mSensor[4])/4;
    oSensor[4] = (oSensor[4])/4;

    // Determines the position of each IR Sensor
    if(rSensor[4] <= 3.5)   {   sensors.right_pin4 = ON_BLACK;    }
    else                    {   sensors.right_pin4 = OFF_BLACK;   }

    if(lSensor[4] <= 2.0)   {   sensors.left_pin5 = ON_BLACK;     }
    else                    {   sensors.left_pin5 = OFF_BLACK;    }

    if(mSensor[4] <= 2.0)   {   sensors.middle_pin6 = ON_BLACK;   }
    else                    {   sensors.middle_pin6 = OFF_BLACK;  }

    // Shifts the of the current state of the IR Circuit
    sensors.state = shift(sensors.right_pin4,sensors.middle_pin6,sensors.left_pin5);

    // Determines if the Robot is facing an object
    if(distanceReading(oSensor[4]) <= threshold_distance)
    {
        currentState = sensorStopState;
        T3CONbits.TON = 1;
    }
    else
    {
        currentState = forwardState;
        T3CONbits.TON = 0;
        turnCount = 0;
    }

   
    
}

/******************************************************************************/




