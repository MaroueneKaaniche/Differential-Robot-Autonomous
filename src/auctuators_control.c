#include "auctuators_control.h"

void stripOFF()
{
    digitalWrite(stripLedPin1, LOW);
    digitalWrite(stripLedPin2, LOW);
}
void stripON()
{
    digitalWrite(stripLedPin1, HIGH);
    digitalWrite(stripLedPin2, LOW);
}

void glissUp(int vitesse)
{
    analogWrite(motorGliss1, 0);
    analogWrite(motorGliss2, vitesse);
}

void glissDown(int vitesse)
{
    analogWrite(motorGliss1, vitesse);
    analogWrite(motorGliss2, 0);
}

void CatchDown()
{
    timer.stop();
    catchR.attach(A6);
    catchL.attach(A7);
    catchR.write(50);
    catchL.write(120);

    delay(1200);
    catchL.detach();
    catchR.detach();
    timer.start();
}
void OneCatchDown()
{
    timer.stop();

    catchL.attach(A7);
    catchL.write(120);

    delay(1200);
    catchL.detach();
    timer.start();
}
void CatchUp()
{
    timer.stop();
    catchR.attach(A6);
    catchL.attach(A7);
    catchR.write(145);
    catchL.write(40);

    delay(1200);
    catchL.detach();
    catchR.detach();
    timer.start();
}

void glissSequence()
{
    TurnTimerOn();

    beb.attach(bebServoPin);
    timer.stop();
    beb.write(74);

    gliss.attach(glissServoPin);

    gliss.write(35);
    delay(300);
    gliss.detach();

    TurnTimerOn();

    glissDown(255);
    delay(1000);
    glissUp(255);
    delay(200);
    glissDown(255);
    delay(1000);

    TurnTimerOn();
    timer.start();
}