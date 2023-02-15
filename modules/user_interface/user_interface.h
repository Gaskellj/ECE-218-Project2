//=====[#include guards - begin]===============================================

#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void userInterfaceInit();
void userInterfaceUpdate();
bool userInterfaceCodeCompleteRead();
void userInterfaceCodeCompleteWrite( bool state );

bool incorrectCodeStateRead();
void incorrectCodeStateWrite( bool state );

bool systemBlockedStateRead();
void systemBlockedStateWrite( bool state );

void userInterfaceDisplayUpdate(char enteredCode [], int startingCodeIndex);
void userInterfaceCorrectOrIncorrect(bool codeCorrect);

void correctCodeDisplayUpdate();

void incorrectCodeDisplayUpdate(int attempts);

void resetDisplay();

//=====[#include guards - end]=================================================

#endif // _USER_INTERFACE_H_