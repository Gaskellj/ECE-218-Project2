# ECE-218-Project2

## Outline

Our project adds new functionality to the existing smart-home system by adding a gate that can be opened by the user. The code is initialised at '1100' for ease of testing. The user may use the attached keypad to deactivate the code - the instruction to do thisis displayed on the LCD screen.

## Conditions

### Correct Code

If the user gets the code correct the servo will open the gate and the number of incorrect attempts is reset.

### Incorrect Code

If the user gets the code incorrect the servo gate will not open and an error message will display on screen for two seconds alongside the number of remaining attempts. The user must wait for the error messege to disappear and will be reinstructed to enter a code.

### Incorrect Code Three Times

If the user gets the code wrong three times in a row they are locked out of the system and must press reset in order to gain access to the gate functionality again - a message is displayed on the LCD to explain this

## Functionality

|Function|Required?|Implemented?|
|--------|---------|------------|
|Gate Passcode|Yes|Yes|
|Gate Open 90 Degrees|Yes|Yes|
|Gate Delay|Yes|Yes|
|Accepts new entries|Yes|Yes|
|LCD User Instructions|Yes|Yes|
|LCD Show Passcode|Yes|Yes|
|Incorrect Passcode Display|Yes|Yes|
|Three Attempts|Yes|Yes|
|System Lockout|Yes|Yes|
|System Reset|Yes|Yes|
|View Code|Yes|Yes|
|Change Cose|No|Yes|

