#include "initObjectSensor.h"
#include "p24FJ64GA002.h"

#define ADC_SETTING AD1PCFGbits.PCFG1 = 0;  AD1CSSLbits.CSSL1 = 1
#define TRIS_OBJECT_SENSOR TRISAbits.TRISA1
void initObjectSensor()
{
    ADC_SETTING;
    TRIS_OBJECT_SENSOR = 1;

}
