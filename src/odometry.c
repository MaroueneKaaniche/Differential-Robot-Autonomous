#include "odometry.h"

float ticks2Distance(long int ticks, float radius, float resolution, int precision)
{
    return ticks * 2 * PI * radius / (resolution * precision);
}

float rad2Deg(float rad)
{
    return rad * 180 / PI;
}

void doEncodeA0()
{
    if (digitalRead(right_pinA) != digitalRead(right_pinB))
    {
        right_ticks++;
    }
    else
    {
        right_ticks--;
    }
}
void doEncodeB0()
{
    if (digitalRead(right_pinA) == digitalRead(right_pinB))
    {
        right_ticks++;
    }
    else
    {
        right_ticks--;
    }
}
void doEncodeA1()
{
    if (digitalRead(left_pinA) != digitalRead(left_pinB))
    {
        left_ticks++;
    }
    else
    {
        left_ticks--;
    }
}
void doEncodeB1()
{
    if (digitalRead(left_pinA) == digitalRead(left_pinB))
    {
        left_ticks++;
    }
    else
    {
        left_ticks--;
    }
}

void updatePosition()
{

    previous_right_ticks = current_right_ticks;
    previous_left_ticks = current_left_ticks;
    current_right_ticks = right_ticks;
    current_left_ticks = left_ticks;

    d_right_ticks = current_right_ticks - previous_right_ticks;
    d_left_ticks = current_left_ticks - previous_left_ticks;

    dR = ticks2Distance(d_right_ticks, radius_r, resoultion, precision);
    dL = ticks2Distance(d_left_ticks, radius_l, resoultion, precision);

    dR_total += dR;
    dR_speed += dR;
    dL_total += dL;
    dL_speed += dL;

    dC = (dR + dL) / 2;
    dC_total += dC;

    dTheta = (dR - dL) / entreAxe;

    dL_speed += dTheta;
    orientation_rad += dTheta;

    while (orientation_rad > PI)
    {
        orientation_rad -= 2 * PI;
    }

    while (orientation_rad < -PI)
    {
        orientation_rad += 2 * PI;
    }

    orientation_deg = rad2Deg(orientation_rad);

    dX = dC * cos(orientation_rad);
    dY = dC * sin(orientation_rad);

    X += dX;
    Y += dY;
    // Serial.println(dC_total);
}

void updateSpeed()
{

    right_encoder_speed = dR_speed * 1000 / (T * 5);
    dR_speed = 0;

    left_encoder_speed = dL_speed * 1000 / (T * 5);
    dL_speed = 0;

    theta_encoder_speed = dTheta_speed * 1000 / (T * 5);
    dTheta_speed = 0;
}

void callback()
{
    t++;
    updatePosition();

    if (t % T == 0)
    {
        updateSpeed();
    }
}