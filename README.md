## README: Arduino KK2 Interface

The Arduino KK2 Interface is a simple but effective serial driven connection between your computer, arduino and KK2 board.

### Installation

..* Just upload the sketch as you would normally with any .ino from the Arduino IDE
..* Open the serial monitor

### How it works & Useage

Your KK2 board receives PWM input from the Arduino Controller in microseconds and outputs them to the ESC's.
5 PWM pins on the Arduino are required to run this program.

Keep in mind the;
..* Ailerion Max value is 1900 and Min value is 1100
..* Elevator Max value is 1900 and Min value is 1100
..* Throttle Max value is 2400 and Min value is 1100
..* Rudder Max value is 1900 and Min value is 1100

To send a command use this format : e.g. TH_1850
..* for Aileron AI
..* for Elevator EL
..* for Throttle TH
..* for Throttle RD
..* for Auxiliary use AUX_ON or AUX_OFF

### Support

The following dev boards are supported:
..* Arduino UNO
..* Arduino Leonardo 
..* Arudino Mega 2560 & ADK

### Dev -

Mike Armstrong 2014
