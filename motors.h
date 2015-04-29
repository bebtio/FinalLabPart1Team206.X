/*
 * File:   motors.h
 * Author: albertoheras
 *
 * Created on April 13, 2015, 1:36 PM
 */

#ifndef MOTORS_H
#define	MOTORS_H

void moveForward();
void moveBackward();
void RWStop();
void LWStop();
void turnLeft();
void turnRight();

void turnRight180();
void turnLeft180();

void steerRight(float steerControl);
void steerLeft(float steerControl);
void STOP();
void RWForward(float DC);
void LWForward(float DC);
void RWBackward(float DC);
void LWBackward(float DC);

#endif	/* MOTORS_H */

