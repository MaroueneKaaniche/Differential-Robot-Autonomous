#include <Arduino.h>
#include <TimerOne.h>
#include <Servo.h>
#include "auctuators_control.h"
#include "odometry.h"
#include "motor.h"
#include "pid.h"



void TurnTimerOn()
{
    if (millis() > 90000)
    {
        stripON();
    }
}

int tirette = 23;
int couleur = 11;


void Blue()
{
    MoveAndStop(1200, 500);

    glissSequence();

    moveParallel(-550, 500);

    gliss.attach(glissServoPin);
    gliss.write(180);
    delay(4000);

    gliss.write(120);
    delay(300);
    gliss.write(180);
    delay(300);
    gliss.write(120);

    gliss.detach();
    // beb.detach();

    TurnTimerOn();

    glissDown(255);
    delay(100);
    glissDown(0);

    orienter(-90, 300);

    PWM_L = -85;
    PWM_R = -85;
    run();
    delay(2000);
    STOP();

    beb.attach(bebServoPin);
    beb.write(0);
    delay(1500);

    PWM_L = 85;
    PWM_R = 85;
    run();
    delay(100);
    STOP();

    PWM_L = -85;
    PWM_R = -85;
    run();
    delay(1000);
    STOP();



    beb.detach();

    move(200, 500);
    orienter(0, 200);
    MoveAndStop(500, 500);
}

void Green()
{
    MoveAndStop(1000, 500);
    orientation_deg = 0;
    orientation_rad = 0;
    glissSequence();
    move(-100, 300);
    orienter(90, 250);
    move(80, 300);
    orienter(0, 300);

    beb.detach();

    moveParallel(-550, 500);

    gliss.attach(glissServoPin);
    gliss.write(180);
    delay(4000);

    gliss.write(120);
    delay(300);
    gliss.write(180);
    delay(300);
    gliss.write(120);

    gliss.detach();

    TurnTimerOn();

    glissDown(255);
    delay(100);
    glissDown(0);

    orienter(90, 300);

    PWM_L = -85;
    PWM_R = -85;
    run();
    delay(2000);
    STOP();

    beb.attach(bebServoPin);
    beb.write(0);
    delay(1500);

    PWM_L = 85;
    PWM_R = 85;
    run();
    delay(100);
    STOP();

    PWM_L = -85;
    PWM_R = -.85;
    run();
    delay(1000);
    STOP();

    // orientation_deg=-90;
    // orientation_rad=-PI/2;

    beb.detach();

    move(-200, 500);
    orienter(90, 200);
    MoveAndStop(-500, 500);
}

void setup()

{

    timer.initialize(5000);
    timer.attachInterrupt(callback);
    // put your setup code here, to run once:
    pinMode(tirette, INPUT);
    pinMode(couleur, INPUT_PULLUP);
    pinMode(right_motorF, OUTPUT);
    pinMode(left_motorF, OUTPUT);
    pinMode(right_motorB, OUTPUT);
    pinMode(left_motorB, OUTPUT);
    pinMode(motorGliss1, OUTPUT);
    pinMode(motorGliss2, OUTPUT);
    pinMode(finCourseD, INPUT_PULLUP);
    pinMode(finCourseG, INPUT_PULLUP);
    pinMode(finCourseUp, INPUT_PULLUP);
    pinMode(finCourseDown, INPUT_PULLUP);
    pinMode(stripLedPin1, OUTPUT);
    pinMode(stripLedPin2, OUTPUT);
    pinMode(tirette, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(right_pinA), doEncodeA0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(right_pinB), doEncodeB0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(left_pinA), doEncodeA1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(left_pinB), doEncodeB1, CHANGE);

     move(900,450);






    Serial.begin(9600);
    beb.attach(bebServoPin);
    beb.write(74);
    delay(1000);
    beb.detach();

    if (digitalRead(finCourseD))
    {
        stripON();
        delay(200);
        stripOFF();
        while (digitalRead(tirette) == 0)
        {
            Serial.println(digitalRead(tirette));
        }
        Blue();
    }
    else
    {
        stripON();
        delay(200);
        stripOFF();
        delay(200);
        stripON();
        delay(200);
        stripOFF();
        delay(200);
        stripON();
        delay(200);
        stripOFF();
        while (digitalRead(tirette) == 0)
        {
            Serial.println(digitalRead(tirette));
        }
       

        gliss.attach(glissServoPin);

        gliss.write(40);
        delay(3000);
        gliss.detach();

        glissDown(255);
        delay(3000);
        glissUp(255);
        delay(800);
        glissDown(0);

        Green();
    }

}