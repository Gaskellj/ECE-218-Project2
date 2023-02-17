#include "mbed.h"
#include "arm_book_lib.h"

#include "servo_gate.h"
#include "matrix_keypad.h"

#define DUTY_MIN 0.025
#define DUTY_MAX 0.07
#define PERIOD 0.02

PwmOut servo(PF_9);


DigitalOut testLED(LED2);

static void lowerGate();

//Initialises the servo
//Puts the servo into its closed position
void servo_gateInit()
{
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
}

//Puts the servo into its open position
//Delays for 4 seconds until the sequence of the program will re-initialise the servo
void raiseGate()
{
    servo.write(DUTY_MAX);
    delay(4000);
}