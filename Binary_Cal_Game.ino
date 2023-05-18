#include <Arduino.h>
#include <stdlib.h>

const int LED_PINS[] = { 9, 10, 11, 12, 13 };  // Pins for LED digits
const int OPERATOR_PLUS_PIN = 2;               // Pin for operator +
const int OPERATOR_MINUS_PIN = 3;              // Pin for operator -
const int ENTER_PIN = 8;                       // Pin for enter button

// Define pin numbers for operand buttons
const int OPERAND1_PIN = 4;
const int OPERAND2_PIN = 5;
const int OPERAND3_PIN = 6;
const int OPERAND4_PIN = 7;

int level = 1;               // Current game level
int goalResult = 0;          // Goal binary result
int operand1 = 0;            // First operand
int operand2 = 0;            // Second operand
char currentOperator = '+';  // Current operator

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(OPERATOR_PLUS_PIN, INPUT_PULLUP);
  pinMode(OPERATOR_MINUS_PIN, INPUT_PULLUP);
  pinMode(ENTER_PIN, INPUT_PULLUP);

  pinMode(OPERAND1_PIN, INPUT_PULLUP);
  pinMode(OPERAND2_PIN, INPUT_PULLUP);
  pinMode(OPERAND3_PIN, INPUT_PULLUP);
  pinMode(OPERAND4_PIN, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(ENTER_PIN)){
    displayAlternatingLED();
  }
  playGame();
}

void displayAlternatingLED() {
  for(int i = 0; i <= 100; i++) {
    if(digitalRead(ENTER_PIN)){
      turnOffLED();
      return;
    }
    if (i % 2) {
      displayBinary(21);
    } else {
      displayBinary(10);
    }
    delay(500);    
  }
}

void turnOffLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}

void playGame() {
  generateGoalResult();
  delay(5000);
  turnOffLED();
  operand1 = getOperand();
  currentOperator = getOperator();
  operand2 = getOperand();

  int playerResult;
  if (currentOperator == '+') {
    playerResult = operand1 + operand2;
  } else {
    playerResult = operand1 - operand2;
  }

  if (playerResult == goalResult) {
    displaySuccess();
    level++;
    if (level == 8) {
      displayWinning();
      level = 1;
    }
  } else {
    displayFail();
    level = 1;
  }

  delay(2000);
}

void generateGoalResult() {
  int ub = 32; //upperbound
  int lb = 0; //increase depending on levels (max = 16)
  //randomize number between 0&31
  goalResult = (rand() % (ub - lb + 1)) + lb;
  displayBinary(goalResult);
}

int getOperand() {
  int operand = 0;
  operand |= digitalRead(OPERAND1_PIN) << 3;
  operand |= digitalRead(OPERAND2_PIN) << 2;
  operand |= digitalRead(OPERAND3_PIN) << 1;
  operand |= digitalRead(OPERAND4_PIN);
  return operand;
}

char getOperator() {
  while (digitalRead(OPERATOR_PLUS_PIN) == HIGH && digitalRead(OPERATOR_MINUS_PIN) == HIGH) {
    // Wait for operator button press
  }
  if (digitalRead(OPERATOR_PLUS_PIN) == LOW) {
    return '+';
  } else {
    return '-';
  }
}

void displayBinary(int number) {
  for (int i = 4; i >= 0; i--) {
    digitalWrite(LED_PINS[i], (number >> (4 - i)) & 1);
  }
}

void displaySuccess() {
  turnOffLED();
  for (int i = 0; i < 5; i++) {
    // bitSet(LED[i], i);
    if (i >= 1) {
      digitalWrite(LED_PINS[i - 1], LOW);
    }
    digitalWrite(LED_PINS[i], HIGH);
    delay(500);
  }
}

void displayFail() {
  while (digitalRead(8)) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
    delay(500);
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_PINS[i], LOW);
    }
    delay(500);
  }
}

void displayWinning() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PINS[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  delay(1000);
}
