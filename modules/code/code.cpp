//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "code.h"

#include "user_interface.h"
#include "pc_serial_com.h"
#include "date_and_time.h"
#include "temperature_sensor.h"
#include "gas_sensor.h"
#include "matrix_keypad.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

extern char codeSequenceFromUserInterface[CODE_NUMBER_OF_KEYS];
extern char codeSequenceFromPcSerialCom[CODE_NUMBER_OF_KEYS];

//=====[Declaration and initialization of private global variables]============

static int numberOfIncorrectAlarmCodes = 0;
static int numberOfIncorrectGateCodes = 0;
static char alarmCodeSequence[CODE_NUMBER_OF_KEYS] = { '1', '8', '0', '5' };
static char gateCodeSequence[CODE_NUMBER_OF_KEYS] = {'1', '1', '0', '0'};

//=====[Declarations (prototypes) of private functions]========================

static bool codeMatch( char* codeToCompare, int type );
static void alarmCodeDeactivate();

//=====[Implementations of public functions]===================================

void codeWrite( char* newCodeSequence, int type )
{
    int i;
    if (type == 1){
        for (i = 0; i < CODE_NUMBER_OF_KEYS; i++) {
            alarmCodeSequence[i] = newCodeSequence[i];
        }
    } else {
        for (i = 0; i < CODE_NUMBER_OF_KEYS; i++) {
            gateCodeSequence[i] = newCodeSequence[i];
        }
    }
}

//int type refers to 1: Alarm or 2: Gate
bool codeMatchFrom( codeOrigin_t codeOrigin, int type )
{
    bool codeIsCorrect = false;
    switch (codeOrigin) {
        case CODE_KEYPAD:
            if( userInterfaceCodeCompleteRead() ) {
                codeIsCorrect = codeMatch(codeSequenceFromUserInterface, type);
                userInterfaceCodeCompleteWrite(false);
                if ( codeIsCorrect ) {
                    numberOfIncorrectGateCodes = 0;
                    correctCodeDisplayUpdate();
                } else {
                    numberOfIncorrectGateCodes++;
                    if (numberOfIncorrectGateCodes > 2){
                        systemIncorrectGateCodeStateWrite(ON);
                    }
                    incorrectCodeDisplayUpdate(3-numberOfIncorrectGateCodes);
                }
            }


        break;
        case CODE_PC_SERIAL:
            if( pcSerialComCodeCompleteRead() ) {
                codeIsCorrect = codeMatch(codeSequenceFromPcSerialCom, type);
                pcSerialComCodeCompleteWrite(false);
                if ( codeIsCorrect ) {
                    alarmCodeDeactivate();
                    pcSerialComStringWrite( "\r\nThe code is correct\r\n\r\n" );
                } else {
                    incorrectCodeStateWrite(ON);
                    numberOfIncorrectAlarmCodes++;
                    pcSerialComStringWrite( "\r\nThe code is incorrect\r\n\r\n" );
                }
            }

        break;
        default:
        break;
    }

    if ( numberOfIncorrectAlarmCodes >= 5 ) {
        systemBlockedStateWrite(ON);
    }

    return codeIsCorrect;
}

char* getGateCode()
{
    return gateCodeSequence;
}

//=====[Implementations of private functions]==================================

static bool codeMatch( char* codeToCompare, int type )
{
    bool isEqual = true;
    int i;
    if (type == 1){
        for (i = 0; i < CODE_NUMBER_OF_KEYS; i++) {
            if ( alarmCodeSequence[i] != codeToCompare[i] ) {
                isEqual =  false;
            }
        }
    } else {
        for (i = 0; i < CODE_NUMBER_OF_KEYS; i++) {
            if ( gateCodeSequence[i] != codeToCompare[i] ) {
                isEqual = false;
            }
        }
    }
    return isEqual;
}

static void alarmCodeDeactivate()
{
    systemBlockedStateWrite(OFF);
    incorrectCodeStateWrite(OFF);
    numberOfIncorrectAlarmCodes = 0;
}