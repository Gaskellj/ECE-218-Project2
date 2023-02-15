//=====[Libraries]=============================================================

#include <cstring>
#include <iostream>

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "code.h"
#include "siren.h"
#include "smart_home_system.h"
#include "fire_alarm.h"
#include "date_and_time.h"
#include "temperature_sensor.h"
#include "gas_sensor.h"
#include "matrix_keypad.h"
#include "display.h"
#include "servo_gate.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut incorrectCodeLed(LED3);
DigitalOut systemBlockedLed(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

char codeSequenceFromUserInterface[CODE_NUMBER_OF_KEYS];

//=====[Declaration and initialization of private global variables]============

static bool incorrectCodeState = OFF;
static bool systemBlockedState = OFF;

static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();
static void incorrectCodeIndicatorUpdate();
static void systemBlockedIndicatorUpdate();

static void userInterfaceDisplayInit();

static void initCode();

static void userInterfaceDisplayLockedOut();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    incorrectCodeLed = OFF;
    systemBlockedLed = OFF;
    matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    userInterfaceMatrixKeypadUpdate();
    incorrectCodeIndicatorUpdate();
    systemBlockedIndicatorUpdate();
}

bool incorrectCodeStateRead()
{
    return incorrectCodeState;
}

void incorrectCodeStateWrite( bool state )
{
    incorrectCodeState = state;
}

bool systemBlockedStateRead()
{
    return systemBlockedState;
}

void systemBlockedStateWrite( bool state )
{
    systemBlockedState = state;
}

bool userInterfaceCodeCompleteRead()
{
    return codeComplete;
}

void userInterfaceCodeCompleteWrite( bool state )
{
    codeComplete = state;
}

void resetDisplay()
{
    userInterfaceDisplayInit();
}

void correctCodeDisplayUpdate()
{
    displayInit();

    displayCharPositionWrite ( 0,0 );
    displayStringWrite("Congratulations ");

    displayCharPositionWrite ( 0,1 );
    displayStringWrite("Gate Is Open");

    raiseGate();

    userInterfaceDisplayInit();
}

void incorrectCodeDisplayUpdate(int attempts)
{
    displayInit();

    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Incorrect Code" );

    displayCharPositionWrite ( 0,1 );
    char message[10];
    if (attempts ==1){
        sprintf(message, "%i More Try",  attempts );
    } else {
        sprintf(message, "%i More Tries",  attempts );
    }
    displayStringWrite(message);

    delay(2000);

    userInterfaceDisplayInit();
}

void displayEnteredCode(char enteredCode [])
{
    displayCharPositionWrite ( 12,1 );

    displayStringWrite(enteredCode);
}

//=====[Implementations of private functions]==================================

static void userInterfaceMatrixKeypadUpdate()
{
    static int numberOfHashKeyReleased = 0;
    char keyReleased = matrixKeypadUpdate();
    if( keyReleased != '\0' ) {
        if( !incorrectCodeStateRead() ) {
                codeSequenceFromUserInterface[numberOfCodeChars] = keyReleased;
                displayEnteredCode(codeSequenceFromUserInterface);
                numberOfCodeChars++;
                if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS ) {
                    codeComplete = true;
                    numberOfCodeChars = 0;
                    bool correctCode = codeMatchFrom(CODE_KEYPAD,2);
                    initCode();
                }
            } else {
                userInterfaceDisplayLockedOut();
            }
        } else {
            
        }
}

static void userInterfaceDisplayLockedOut()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Locked Out" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Press Reset " );
}

static void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Gate Is Closed" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Enter Code:" );

}


static void incorrectCodeIndicatorUpdate()
{
    incorrectCodeLed = incorrectCodeStateRead();
}

static void systemBlockedIndicatorUpdate()
{
    systemBlockedLed = systemBlockedState;
}

static void initCode(){
    memset(codeSequenceFromUserInterface, 0, sizeof(codeSequenceFromUserInterface));
}