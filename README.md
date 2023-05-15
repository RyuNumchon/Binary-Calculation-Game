#Binary Calculation Game

A single player Binary Calculation game: Arduino project

Required components:
a) 1 Arduino Board
b) 6 switches
c) 4 LEDs
d) 10 330-Ohm resisotrs
e) wires

Explanation:
This project is a Binary Number Calculation game, which is designed to be played using an
Arduino board, a breadboard, 5 LEDs, and 7 switches. The goal of the game is for the player
to correctly calculate the result of a binary calculation by inputting two operands and an
operator. The game has 15 levels, and the difficulty increases with each level.
The game starts with the LEDs lighting up alternately indicating the start of the level. Once
the user presses the enter switch, the board generates a goal 5-digit binary result that the
player has to achieve. After 5 seconds, all the LEDs are turned off indicating that the player
has to enter the first operand. The player then does so by toggling the corresponding switch,
followed by the operator (either addition or subtraction), and then the second operand. Once
the player has entered all the required values, they press the enter switch again to submit
their answer.

If the player's calculation is correct, the LEDs light up consecutively, until the player press
enter to go to the next level. If the player's calculation is incorrect, the LEDs all turn on and
off alternatively, until the player restart the game. The game repeats until the player reaches
the 15th level.

For example,
1) The generated goal result: 11100
2) The player inputs the 1st operand: 1111
3) The player inputs operator: +
4) The player inputs the 2nd operand: 1101
5) The player presses enter switch
6) Here the answer is correct, so the player goes to the next level.
