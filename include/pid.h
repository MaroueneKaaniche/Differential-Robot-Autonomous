#ifndef PID_H
#define PID_H

extern float right_erreur = 0;
extern float left_erreur = 0;
extern float i_right_erreur = 0;
extern float i_left_erreur = 0;

extern float orientation = 0;
extern float i_orientation = 0;
extern float orientation_erreur = 0;
extern float i_orientation_erreur = 0;
extern float Theta_correction = 0;
extern float position_erreur = 0;

extern float kp = 0.3;
extern float kp_dour = 12;
extern float ki = 0;
extern float kTheta = 8;
extern float k_position = 1.5;

extern int sens = 1;

float erreur(float PWM, float min, float max);

#endif