Motor Control Driver with Direction and Timing Control
This Arduino-based motor control driver enables timed forward and reverse motor movement, triggered by a button. The driver uses PWM signals to control two motors' speed and direction and is ideal for applications where motors need to alternate directions with specified delays.

Features
Button-Activated Control: Initiate motor movement with a single button press.
Timed Forward and Reverse Motion: Runs motors forward for 15 seconds, stops for 4 seconds, and then reverses for another 15 seconds before stopping.
PWM Speed Control: Adjustable motor speed via PWM for smooth starting and stopping.
Wiring
Connect motors to PWM pins (M1_R, M1_L, M2_R, M2_L).
Button input connects to the specified Push_Enable pin.
Set appropriate enable and direction pins for motor control.
Usage
Install: Load the code onto your Arduino.
Press Button: To start, press the button. Motors will move forward for 15 seconds, stop for 4 seconds, and then reverse for 15 seconds.
Cycle Control: The state machine manages each cycle and stops after one full sequence.
This code is a template and can be modified for different timings or control schemes as needed.
