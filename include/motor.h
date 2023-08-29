#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "odometry.h"
#include "pid.h"
#include "auctuators_control.h"

float PWM_R = 0;
float PWM_L = 0;
float PWM_MIN = 35;
float PWM_MAX = 180;

int right_motorF = 3;
int right_motorB = 2;

int left_motorF = 5;
int left_motorB = 4;

void run();
void STOP();
float acceleration(float speed, float distance, float accel, float decel);
float acceleration_turn(float speed, float distance, float accel, float decel);
void turn(float angle, float speed);
void iniiit();
void moveParallel(float distance, float speed);
void move(float distance, float speed);
void MoveAndStop(float distance, float speed);
void MoveAndStopOneTime(float distance, float speed);
void orienter(float orientation, float speed);
void go(float x, float y, float speedf, float speedr);
#endif