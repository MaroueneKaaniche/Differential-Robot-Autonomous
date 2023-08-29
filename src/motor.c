#include "motor.h"

void iniiit()
{
    dR_total = 0;
    dL_total = 0;
    dC_total = 0;
    i_right_erreur = 0;
    i_left_erreur = 0;
    right_erreur = 0;
    left_erreur = 0;
    position_erreur = 0;
    orientation_erreur = 0;
}

void run()
{

    if (PWM_R > 0)
    {
        // PWM_R=erreur(PWM_R,PWM_MIN,PWM_MAX);
        analogWrite(right_motorF, PWM_R);
        analogWrite(right_motorB, 0);
    }
    else
    {
        // PWM_R=erreur(PWM_R,PWM_MIN,PWM_MAX);
        analogWrite(right_motorF, 0);
        analogWrite(right_motorB, -PWM_R);
    }
    if (PWM_L > 0)
    {
        // PWM_L=erreur(PWM_L,PWM_MIN,PWM_MAX);

        analogWrite(left_motorF, PWM_L);
        analogWrite(left_motorB, 0);
    }
    else
    {
        // PWM_L=erreur(PWM_L,-PWM_MAX,-PWM_MIN);

        analogWrite(left_motorF, 0);
        analogWrite(left_motorB, -PWM_L);
    }
}
void STOP()
{
    analogWrite(right_motorF, 0);
    analogWrite(right_motorB, 0);
    analogWrite(left_motorF, 0);
    analogWrite(left_motorB, 0);
}

float acceleration(float speed, float distance, float accel, float decel)
{
    float current_speed;

    if (abs(dC_total) < accel)
    {
        current_speed = (speed / (accel)) * abs(dC_total);
    }
    else if (distance - abs(dC_total) < decel)
    {
        current_speed = (speed / -decel) * abs(dC_total) + speed - ((distance - decel) * (speed / -decel));
    }
    else
    {
        current_speed = speed;
    }
    return current_speed;
}

float acceleration_turn(float speed, float distance, float accel, float decel)
{
    float current_speed;

    if ((dR_total - dL_total) < accel)
    {
        current_speed = (speed / (accel)) * (dR_total - dL_total);
    }
    else if (distance - (dR_total - dL_total) < decel)
    {
        current_speed = (speed / -decel) * (dR_total - dL_total) + speed - ((distance - decel) * (speed / -decel));
    }
    else
    {
        current_speed = speed;
    }

    // current_speed = erreur(current_speed, PWM_MIN, speed);
    return current_speed;
}

void turn(float angle, float speed)
{
    iniiit();

    float distance = angle * PI * entreAxe / 180;

    float accel = 0.25 * distance;
    float decel = 0.5 * distance;

    while (abs((abs(dL_total - dR_total) - abs(distance))) > 0.5)
    {
        TurnTimerOn();
        if (((dR_total - dL_total) - distance) < 0)
            sens = 1;
        else
            sens = -1;
        /*Serial.print(distance);
Serial.print("   ");
        Serial.print(sens);
Serial.print("   ");*/
        float current_speed = sens * acceleration_turn(speed, abs(distance), abs(accel), abs(decel));

        // right pid
        right_erreur = current_speed - right_encoder_speed;
        i_right_erreur += right_erreur;
        PWM_R = kp_dour * right_erreur + ki * i_right_erreur;

        //  PWM_R=erreur(PWM_R,PWM_MIN,PWM_MAX);

        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }

        /*Serial.print(PWM_R);
        Serial.print("     ");*/
        // left pid
        left_erreur = -current_speed - left_encoder_speed;
        i_left_erreur += left_erreur;
        PWM_L = kp_dour * left_erreur + ki * i_left_erreur;
        // PWM_L=erreur(PWM_L,-PWM_MAX,-PWM_MIN);
        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        else
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        // Serial.println(PWM_L);
        // position pid
        position_erreur = k_position * (dR_total + dL_total);
        // Theta_correction=kTheta*orientation_erreur;

        PWM_R += position_erreur;
        PWM_L -= position_erreur;

        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        else
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }

        run();
    }
    STOP();
    delay(500);
}

void moveParallel(float distance, float speed)
{
    iniiit();
    float accel = 0.25 * distance;
    float decel = 0.5 * distance;

    glissUp(255);
    int debut = millis();
    while (abs(dC_total - distance) > 5)
    {

        if (millis() - debut > 4000)
        {
            glissUp(0);
        }
        TurnTimerOn();
        if ((dC_total - distance) < 0)
            sens = 1;
        else
            sens = -1;
       // Serial.print(sens);
       // Serial.print("      ");

        float current_speed = sens * acceleration(speed, abs(distance), abs(accel), abs(decel));
        // right pid
        right_erreur = current_speed - right_encoder_speed;
        i_right_erreur = right_erreur;
        PWM_R = kp * right_erreur + ki * i_right_erreur;
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }
        // left pid
        left_erreur = current_speed - left_encoder_speed;
        i_left_erreur += left_erreur;
        PWM_L = kp * left_erreur + ki * i_left_erreur;

        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        // Serial.print(PWM_R);
        // Serial.print("      ");
        // Serial.print(dC_total);
        // Serial.print("      ");
        // Serial.print(current_speed);
        // Serial.println("      ");
        /*Serial.print(right_erreur);
        Serial.print("    ");
        Serial.print(current_speed);
        Serial.print("   ");
        Serial.println(PWM_R);*/

        // orientation pid
        orientation_erreur = dR_total - dL_total;
        Theta_correction = kTheta * orientation_erreur;

        PWM_R -= Theta_correction;
        PWM_L += Theta_correction;
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }
        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        run();
    }
    STOP();

    while (millis() - debut < 4000)
    {
    }
    glissUp(0);

    //Serial.print(dC_total);
}

void move(float distance, float speed)
{
    iniiit();
    float accel = 0.25 * distance;
    float decel = 0.5 * distance;

    while (abs(dC_total - distance) > 5)
    {
        TurnTimerOn();
        if ((dC_total - distance) < 0)
            sens = 1;
        else
            sens = -1;
       // Serial.print(sens);
      //  Serial.print("      ");

        float current_speed = sens * acceleration(speed, abs(distance), abs(accel), abs(decel));
        // right pid
        right_erreur = current_speed - right_encoder_speed;
        i_right_erreur = right_erreur;
        PWM_R = kp * right_erreur + ki * i_right_erreur;
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }
        // left pid
        left_erreur = current_speed - left_encoder_speed;
        i_left_erreur += left_erreur;
        PWM_L = kp * left_erreur + ki * i_left_erreur;

        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        // Serial.print(PWM_R);
        // Serial.print("      ");
        // Serial.print(dC_total);
        // Serial.print("      ");
        // Serial.print(current_speed);
        // Serial.println("      ");
        /*Serial.print(right_erreur);
        Serial.print("    ");
        Serial.print(current_speed);
        Serial.print("   ");
        Serial.println(PWM_R);*/

        // orientation pid
        orientation_erreur = dR_total - dL_total;
        Theta_correction = kTheta * orientation_erreur;

        PWM_R -= Theta_correction;
        PWM_L += Theta_correction;
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }
        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        run();
    }
    STOP();
   // Serial.print(dC_total);
}

void MoveAndStop(float distance, float speed)
{
    iniiit();
    float accel = 0.25 * distance;
    float decel = 0.5 * distance;

    while (abs(dC_total - distance) > 5 && !(digitalRead(finCourseD) == 1 && digitalRead(finCourseG) == 0))
    {
        TurnTimerOn();
        if ((dC_total - distance) < 0)
            sens = 1;
        else
            sens = -1;
    //    Serial.print(sens);
      //  Serial.print("      ");

        float current_speed = sens * acceleration(speed, abs(distance), abs(accel), abs(decel));
        // right pid
        right_erreur = current_speed - right_encoder_speed;
        i_right_erreur = right_erreur;
        PWM_R = kp * right_erreur + ki * i_right_erreur;
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }
        // left pid
        left_erreur = current_speed - left_encoder_speed;
        i_left_erreur += left_erreur;
        PWM_L = kp * left_erreur + ki * i_left_erreur;

        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        // Serial.print(PWM_R);
        // Serial.print("      ");
        // Serial.print(dC_total);
        // Serial.print("      ");
        // Serial.print(current_speed);
        // Serial.println("      ");
        /*Serial.print(right_erreur);
        Serial.print("    ");
        Serial.print(current_speed);
        Serial.print("   ");
        Serial.println(PWM_R);*/

        // orientation pid
        orientation_erreur = dR_total - dL_total;
        Theta_correction = kTheta * orientation_erreur;

        PWM_R -= Theta_correction;
        PWM_L += Theta_correction;
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }
        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        run();
    }
    STOP();
   // Serial.print(dC_total);
}

void MoveAndStopOneTime(float distance, float speed)
{
    iniiit();
    float accel = 0.25 * distance;
    float decel = 0.5 * distance;

    while (abs(dC_total - distance) > 1 && !(digitalRead(finCourseD) == 0 || digitalRead(finCourseG) == 0))
    {
        if ((dC_total - distance) < 0)
            sens = 1;
        else
            sens = -1;
      //  Serial.print(sens);
      //  Serial.print("      ");

        float current_speed = sens * acceleration(speed, abs(distance), abs(accel), abs(decel));
        // right pid
        right_erreur = current_speed - right_encoder_speed;
        i_right_erreur += right_erreur;
        PWM_R = kp * right_erreur + ki * i_right_erreur;
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }
        // left pid
        left_erreur = current_speed - left_encoder_speed;
        i_left_erreur += left_erreur;
        PWM_L = kp * left_erreur + ki * i_left_erreur;

        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
/*         Serial.print(PWM_R);
        Serial.print("      ");
        Serial.print(dC_total);
        Serial.print("      ");
        Serial.print(current_speed);
        Serial.println("      "); */
        /*Serial.print(right_erreur);
        Serial.print("    ");
        Serial.print(current_speed);
        Serial.print("   ");
        Serial.println(PWM_R);*/

        // orientation pid
        orientation_erreur = dR_total - dL_total;
        Theta_correction = kTheta * orientation_erreur;

        PWM_R -= Theta_correction;
        PWM_L += Theta_correction;
        if (sens == 1)
        {
            PWM_R = erreur(PWM_R, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_R = erreur(PWM_R, -PWM_MAX, -PWM_MIN);
        }
        if (sens == 1)
        {
            PWM_L = erreur(PWM_L, PWM_MIN, PWM_MAX);
        }
        else
        {
            PWM_L = erreur(PWM_L, -PWM_MAX, -PWM_MIN);
        }
        run();
    }
    STOP();
  //  Serial.print(dC_total);
}

void orienter(float orientation, float speed)
{
    float target_angle = orientation - orientation_deg;
    if (target_angle > 180)
        target_angle -= 360;
    if (target_angle < -180)
        target_angle += 360;
    turn(target_angle, speed);
}


void go(float x, float y, float speedf, float speedr)
{
    int sens = (asinf((y - Y) / sqrtf((X - x) * (X - x) + (Y - y) * (Y - y))) > 0) ? 1 : -1;
    float target_angle = sens * rad2Deg(acosf((x - X) / sqrtf((X - x) * (X - x) + (Y - y) * (Y - y))));
    orienter(target_angle, speedr);
    float goal_distance = sqrtf((X - x) * (X - x) + (Y - y) * (Y - y));
    move(goal_distance, speedf);
    // Serial.print(target_angle);
    // Serial.println("   ");
}
