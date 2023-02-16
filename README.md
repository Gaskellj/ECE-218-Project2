# ECE-218-Project2

## Outline

Our project adds new functionality to the existing smart-home system by adding a gate that can be opened by the user. The code is initialised at '1100' for ease of testing. The user may use the attached keypad to deactivate the code - the instruction to do this is displayed on the LCD screen.
The user can use the serical monitor in the same way as before with two additional features changeGateCode and showGateCode that can be activated by pressing '5' and '6' respeciverly on the serial monitor.

## Conditions

#### Correct Code

If the user gets the code correct the servo will open the gate and the number of incorrect attempts is reset.

#### Incorrect Code

If the user gets the code incorrect the servo gate will not open and an error message will display on screen for two seconds alongside the number of remaining attempts. The user must wait for the error messege to disappear and will be reinstructed to enter a code.

#### Incorrect Code Three Times

If the user gets the code wrong three times in a row they are locked out of the system and must press reset in order to gain access to the gate functionality again - a message is displayed on the LCD to explain this.

#### User presses 5 on serial monitor

ChangeGateCode is activated. The user must input a 4 digit code to the serial monitor. The code is hidden using * and when the code is completed it is set to the defined value.

#### User presses 6 on serial monitor

ShowGateCode is activated. This outputs the current gate code to screen in the format "Current Gate Code = ".

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
|Change Code|No|Yes|

