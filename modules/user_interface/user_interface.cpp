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
static bool systemIncorrectGateCodeState = OFF;

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

bool systemIncorrectGateCodeStateRead()
{
    return systemIncorrectGateCodeState;
}


void systemIncorrectGateCodeStateWrite( bool state)
{
    systemIncorrectGateCodeState = state;
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

//Informs the user the code they entered is correct
//Raises the gate
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

//Informs the user the code they entered is incorrect
//Takes parameter attempts to display the number of attempts remaining to the user
//Delays for 2 seconds so the user can see the message, the user cannot enter a character in this time
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

//Writes the entered code portion to the display
void displayEnteredCode(char enteredCode [])
{
    displayCharPositionWrite ( 12,1 );

    displayStringWrite(enteredCode);
}

//=====[Implementations of private functions]==================================

//Now handles the code inputted by the matrix keypad in relation to the gate code
//Checks if the entered code is equal after four character are entered
//Displays locked out screen if the systemIncorrectGateCodeState is ON
//Uses initCode() to clear the chaaracter array after each code entry to allow a new entry
static void userInterfaceMatrixKeypadUpdate()
{
    static int numberOfHashKeyReleased = 0;
    char keyReleased = matrixKeypadUpdate();
    if( keyReleased != '\0' ) {
        if( !systemIncorrectGateCodeStateRead()) {
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

//Display if a user can't input a new code
static void userInterfaceDisplayLockedOut()
{
    systemIncorrectGateCodeState = (ON);

    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Locked Out" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Press Reset " );
}

//Display if a user can input a new code
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

//Emptys the array that contains the current entered code
static void initCode(){
    memset(codeSequenceFromUserInterface, 0, sizeof(codeSequenceFromUserInterface));
}