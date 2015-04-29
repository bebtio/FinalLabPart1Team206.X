/*
 * File:   PWM.h
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */

#ifndef PWM_H
#define	PWM_H

void initPWM();
void initModule1();
void initModule2();
void setDutyCycleOCM1(float dutyCycle);
void setDutyCycleOCM2(float dutyCycle);
void setDutyCycleOCM3(float dutyCycle);
void setDutyCycleOCM4(float dutyCycle);

#endif	/* PWM_H */

