#include "mbed.h"
#include "arm_book_lib.h"
#include "servo.h"

#define DUTY_MIN 0.020
#define DUTY_MAX 0.895
#define PERIOD 0.02

PwmOut servo(PF_9);

void servoInit()
{
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
}

void gateRaise()
{
    int dest = DUTY_MAX/2
    servo.write(dest);
}

void gateLower()
{
    servo.write(DUTY_MIN);
}
