#include "pid.h"

float erreur(float PWM, float min, float max)
{
    if (PWM < min)
    {
        PWM = min;
    }
    else if (PWM > max)
    {
        PWM = max;
    }
    return PWM;
}


