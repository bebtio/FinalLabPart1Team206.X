#include "switch.h"
#include "p24FJ64GA002.h"

// Switch for changing from the idleState to the forwardState.
void initSW1()
{
    // Initialize the pin connected to the switch as an input.
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    CNEN2bits.CN27IE = 1;
}


