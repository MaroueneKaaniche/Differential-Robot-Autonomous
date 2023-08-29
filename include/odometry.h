#ifndef ODOMETRY_H
#define ODOMETRY_H

#include <Arduino.h>

extern long int current_right_ticks = 0;
extern volatile long int current_left_ticks = 0;
extern volatile long int previous_right_ticks = 0;
extern volatile long int previous_left_ticks = 0;
extern volatile long int d_right_ticks = 0;
extern volatile long int d_left_ticks = 0;

extern volatile long int right_ticks = 0;
extern volatile long int left_ticks = 0;

extern volatile float orientation_rad = 0;
extern volatile float orientation_deg = 0;

extern volatile float dR = 0;
extern volatile float dL = 0;
extern volatile float dC = 0;
extern volatile float dTheta = 0;

extern volatile float dR_total = 0;
extern volatile float dL_total = 0;
extern volatile float dC_total = 0;

extern volatile float dR_speed = 0;
extern volatile float dL_speed = 0;
extern volatile float dTheta_speed = 0;

extern volatile float dX = 0;
extern volatile float dY = 0;

extern volatile float X = 0;
extern volatile float Y = 0;

extern volatile float right_encoder_speed = 0;
extern volatile float left_encoder_speed = 0;
extern volatile float theta_encoder_speed = 0;

extern int precision = 4;
extern float resoultion = 700;

extern float radius_r = 36.47;
extern float radius_l = 36.15;

extern float entreAxe = 272;

extern float rotation = 0;

extern int right_pinA = 19;
extern int right_pinB = 18;

extern int left_pinA = 21;
extern int left_pinB = 20;

extern volatile long int t = 0;
extern int T = 10;

float ticks2Distance(long int ticks, float radius, float resolution, int precision);
float rad2Deg(float rad);
void doEncodeA1();
void doEncodeB1();
void doEncodeB0();
void doEncodeA0();
void updatePosition();
void updateSpeed();
void callback();
#endif