#ifndef AUCTUATORS_CONTROL_H
#define AUCTUATORS_CONTROL_H

#include <Arduino.h>

extern Servo gliss;
extern Servo beb;

extern Servo catchR;
extern Servo catchL;
extern int stripLedPin1 = 52;
extern int stripLedPin2 = 53;
extern int motorGliss1 = 7;
extern int motorGliss2 = 6;

extern int finCourseUp = 48;
extern int finCourseDown = 46;
extern int finCourseG = 9;
extern int finCourseD = 8;

extern int pompe1 = 33;
extern int pompe2 = 35;

extern int glissServoPin = 10;
extern int bebServoPin = 11;

extern TimerOne timer;

// decleration of the functions used to manipulate actuators

void stripOFF();
void stripON();
void glissUp(int vitesse);

void glissDown(int vitesse);
void CatchDown();
void OneCatchDown();
void CatchUp();
void glissSequence();


#endif