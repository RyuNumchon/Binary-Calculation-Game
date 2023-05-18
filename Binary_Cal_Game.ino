#include <stdlib.h>

//All swithes in this code are pull-up switches (default = 1)
int LED[] = {9, 10, 11, 12, 13};  //LED for binary number
int N_LED = 5;                    //5-bit binary number
int SW[] = {4, 5, 6, 7, 8};       //4 switches for each input bit & 1 switch for =
int OP[] = {2, 3};                //2 switches for operators + and -
int C_Delay = 500;                //Time delay for Christmas lighting
int L_Delay = 5000;               //Time delay for 5-bit binary
int OF = HIGH;                    //On/off value of the first LED in christmas light
int LEVEL = 1;                    //Current game LEVEL
int GoalResult = 0;               //Goal binary result
int operand1 = 0;                 //First operand
int operand2 = 0;                 //Second operand
char currentOperator = '+';       //Current operator

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to Binary Calculation Game!");
  for (int i = 0; i < N_LED; i++) {
    //Set all LED pins to be output mode and set the initial values to be LOW
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
    //Set 5 switch pins to be input mode
    pinMode(SW[i], INPUT);
  }
  //Set 2 operator-switch pins to be input mode
  pinMode(OP[0], INPUT);
  pinMode(OP[1], INPUT);
  delay(C_Delay);
  Serial.println("Please press enter switch to start.");
}

void loop() {  
  //Display Christmas Light until user press enter
  while (digitalRead(SW[4])) {
    waitForStart();
    delay(C_Delay);
  }
  playGame();
}

void waitForStart() {
  for (int i = 0; i < N_LED; i++) {
    if (i%2 == 0) {
      digitalWrite(LED[i],OF);
    }
    else {
      digitalWrite(LED[i],!OF);
    }
  }
  OF = !OF;
}

void playGame() {
  clearLED();
  delay(1500);
  generateGoalResult();
  delay(L_Delay);
  clearLED();
  operand1 = getOperand();
  currentOperator = getOperator();
  operand2 = getOperand();

  int playerResult;
  if (currentOperator == '+') {
    playerResult = operand1 + operand2;
  } else {
    playerResult = operand1 - operand2;
  }

  if (playerResult == GoalResult) {
    displaySuccess();
    LEVEL++;
    if (LEVEL == 8) {
      displayWinning();
      LEVEL = 1;
    }
  } else {
    displayFail();
    LEVEL = 1;
  }

  delay(2000);
}

void clearLED() {
  for (int i = 0; i < N_LED; i++) {
    digitalWrite(LED[i],LOW);
  }
}

void generateGoalResult() {
  int ub = 32; //upperbound
  int lb = 0; //increase depending on LEVELs (max = 16)
  //randomize number between 0&31
  GoalResult = (rand() % (ub - lb + 1)) + lb;
  displayBinary(GoalResult);
}

int getOperand() {
  int operand = 0;
  for (int i = 0; i < 4; i++) {
    operand |= digitalRead(SW[i]) << (3-i);
  }
  return operand;
}

char getOperator() {
  // Wait for operator button press
  while (digitalRead(OP[0]) == HIGH && digitalRead(OP[1]) == HIGH)
  if (digitalRead(OP[0]) == LOW) {
    return '+';
  } else {
    return '-';
  }
}

void displayBinary(int number) {
  for (int i = 4; i >= 0; i--) {
    digitalWrite(LED[i], (number >> (4 - i)) & 1);
  }
}

void displaySuccess() {
  clearLED();
  for (int i = 0; i < 5; i++) {
    // bitSet(LED[i], i);
    if (i >= 1) {
      digitalWrite(LED[i - 1], LOW);
    }
    digitalWrite(LED[i], HIGH);
    delay(C_Delay);
  }
}

void displayFail() {
  while (digitalRead(SW[4])) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED[i], OF);
    }
    delay(C_Delay);
    OF = !OF;
  }
}

void displayWinning() {
  int j = 0;
  int step = 1;
  while (j <= 3) {
    for (int i = 0; i <= N_LED; i++) {
      if (j == -1 || j == 3) {
        digitalWrite(LED[i],LOW);
        step *= -1;
      }
      else if ((i >= 2-j) && (i <= 2+j)) {
        digitalWrite(LED[i],HIGH);
      }
    }
    j += step;
  }
}
