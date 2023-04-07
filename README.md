# Simon_Say_Game
A Simon Say Game: Arduino project.

Required components:
a) 1 Arduino Board
b) 5 switches
c) 5 LEDs
d) 10 220-Ohm resisotrs
e) wires

Explaination: 
The Simon Says game project involves building an electronic game using an Arduino board, switches, LEDs, a 7-segment display, resistors, and wires. The game involves the generation of a random sequence of LED flashes, which the player must then repeat by pressing the corresponding buttons in the correct order. The game has now been enhanced to include an additional LED that indicates whether the player needs to perform the action or skip the turn, and a switch that allows the player to skip their turn. The game has also been expanded to include 10 levels of increasing difficulty, with each level having a longer and faster sequence. When the player reaches level 10, all LEDs light up to indicate the winning state

How to Connect:
1) Connect the breadboard to the Arduino board's 5V and GND pins.
2) Connect four switches to the breadboard.
3) Connect four 220-ohm resistors to the breadboard.
4) Connect one LED to each of the four resistors.
5) Connect the common anode of a 7-segment display to the breadboard.
6) Connect the cathodes of the 7-segment display to four 220-ohm resistors.
7) Connect the four resistors to four different digital pins of the Arduino board. Make sure to note down which pin is connected to which segment of the display.
8) Connect the switches to four different digital pins of the Arduino board.
9) Connect three LEDs to three different digital pins of the Arduino board. The first LED will be used to indicate the current button press, the second LED will be used to indicate a correct button press, and the third LED will be used to indicate the end of the game.
10) Connect a 10k-ohm LDR to the breadboard.
11) Connect a DC motor to the breadboard.
12) Connect a transistor to the breadboard.
13) Connect the base of the transistor to a digital pin of the Arduino board.
14) Connect the emitter of the transistor to GND.
15) Connect the collector of the transistor to the DC motor.
16) Connect the LDR to an analog pin of the Arduino board.
17) Connect a 10k-ohm resistor to the LDR and connect the other end of the resistor to 5V.
18) Connect the 7-segment display's common anode to 5V.
19) Connect the Arduino board to your computer using a USB cable.

Once you have all the components connected, you can upload the Simon Says game code to the Arduino board and start playing!