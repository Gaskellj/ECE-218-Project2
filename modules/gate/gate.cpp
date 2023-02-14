#include "mbed.h"
#include "arm_book_lib.h"

#include "servo.h"
#include "gate.h"
#include "matrix_keypad.h"



DigitalOut testLED(LED2);

void gateInit()
{servoInit();
testLED=OFF;

}

void gateCycle(bool code)
{
  
  if (code) {
    gateRaise();
    testLED = ON;
    delay(10000);
    gateLower();
    testLED = OFF;
    delay(5000);
    }
}
