#include <stdlib.h>
#include <PinChangeInterrupt.h>

//All swithes in this code are pull-up switches (default = 1)
int LED[] = { 9, 10, 11, 12, 13 };  //LED for binary number (MSB = 9)
int N_LED = 5;                      //5-bit binary number
int SW[] = { 4, 5, 6, 7, 8 };       //4 switches for each input bit, and 1 switch for '='
int OP[] = { 2, 3 };                //2 switches for operators: pin2 for '+' and pin3 for '-'
int H_DELAY = 500;                  //0.5 second time delay
int F_DELAY = 5000;                 //1 second time delay
int OF = HIGH;                      //On/off value of the first LED in christmas light
int LEVEL = 1;                      //Current game LEVEL
int MAX_LEVEL = 5;                  //Maximum game Level
int GoalResult = 0;                 //Goal binary result
int operand1 = 0;                   //First operand
int operand2 = 0;                   //Second operand
char currentOperator = '+';         //Current operator
bool token = false;                 //player's turn
bool enter = true;                  //player can press enter or not
int operand = 0;

void setup() {
  Serial.begin(9600);

  Serial.println("Welcome to Binary Calculation Game!");

  for (int i = 0; i < N_LED; i++) {
    //Set all LED pins to be output mode and set the initial values to be LOW
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], LOW);
    //Set 5 switch pins to be input mode
    pinMode(SW[i], INPUT_PULLUP);
    if (i != 4) {
      attachPCINT(digitalPinToPCINT(SW[i]), getOperand, FALLING);
    }
  }

  //Set 2 operator-switch pins to be input mode
  pinMode(OP[0], INPUT);
  pinMode(OP[1], INPUT);

  delay(H_DELAY);

  Serial.println("Please press enter switch to start.");
}

void loop() {
  //Display Christmas Light until user press enter
  if(LEVEL == 1){
    int seed = 0;
    while (pressEnter()) {
      seed++;
      waitForStart();
      
      delay(H_DELAY);
    
    }
    srand(seed);  //randomize seed setup
  }

  playGame();
}

bool pressEnter() {
  if (enter) {
    return digitalRead(SW[4]);
  }
  return false;
}

void waitForStart() {
  for (int i = 0; i < N_LED; i++) {
    if (i % 2 == 0) {
      digitalWrite(LED[i], OF);
    } else {
      digitalWrite(LED[i], !OF);
    }
  }
  OF = !OF;
}

void playGame() {
  Serial.println("\nLEVEL: " + String(LEVEL));
  int playerResult;

  enter = false;

  clearLED();
  
  delay(1500);

  generateGoalResult();
  
  delay(F_DELAY);
  
  clearLED();

  operand = 0;
  enter = true;   
  token = true;

  while (pressEnter());
  Serial.println("Enter 1st operand: ");
  operand1 = operand;

  enter = false;
  token = false;

  Serial.print("\noperand1 = " + String(operand1) + "\nEnter Operator: ");
  currentOperator = getOperator();

  Serial.print(String(currentOperator) + "\nEnter 2nd operand:\n");
  clearLED();

  operand = 0;
  enter = true;
  token = true;

  while (pressEnter());
  Serial.println("Test for OG operand = " + String(operand));
  operand2 = operand;
  Serial.println("operand2 = " + String(operand2));

  enter = false;
  token = false;

  if (currentOperator == '+') {
    playerResult = operand1 + operand2;
  } else {
    playerResult = operand1 - operand2;
  }

  Serial.println("playerResult = " + String(playerResult));
  Serial.println("GoalResult = " + String(GoalResult));
  delay(H_DELAY);

  enter = true;

  if (playerResult == GoalResult) {
    Serial.println("Correct");
    displaySuccess();
    LEVEL++;
    if (LEVEL > MAX_LEVEL) {
      Serial.println("Won");
      displayWinning();
      LEVEL = 1;
    }
  } else {
    Serial.println("BooHoo");
    displayFail();
    LEVEL = 1;
  }

  delay(2000);  //2*F_DELAY
}

void clearLED() {
  for (int i = 0; i < N_LED; i++) {
    digitalWrite(LED[i], LOW);
  }
}

void generateGoalResult() {
  //upperbound (Maximum of binary with 5 digits = 30)
  int ub = 31;
  //Lowerbound - affects game difficulty
  int lb = myCeil((30 - 1) / MAX_LEVEL) * LEVEL ;
  //randomize number between lb & ub
  GoalResult = (rand() % (ub - lb + 1)) + lb;
  Serial.println("Randomized Result = " + String(GoalResult));
  displayBinary(GoalResult);
}

int myCeil(float f) {
  int n = int(f);
  if (f > n) {
    return n+1;
  }
  else {
    return n;
  }
}

void getOperand() {
  if (token) {
    int sw = input();
    int led = digitalRead(LED[sw-3]);

    if (led) {
      operand &= ~(1 << (3 - (sw-4)));
    } else {
      operand |= 1 << (3 - (sw-4));
    }

    Serial.println("Current operand: " + String(operand));
    digitalWrite(LED[sw-3], !led);
  }
}

int input() {
  for (int i = 0; i < 4; i++) {
    if (!digitalRead(SW[i])) {
      return SW[i];
    }
  }
}

char getOperator() {
  while (digitalRead(OP[0]) && digitalRead(OP[1])); // Wait for operator button press
  
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
    if (i >= 1) {
      digitalWrite(LED[i - 1], LOW);
    }
    digitalWrite(LED[i], HIGH);
    
    delay(H_DELAY);
  }
}

void displayFail() {
  while (pressEnter()) {      
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED[i], OF);
    }
    
    delay(H_DELAY);
    
    OF = !OF;
  }
}

void displayWinning() {
  int win[] = {4,14,31,0,31,14,4,0};
  int i = 0;
  while (pressEnter()) {
    if (i > 7) {
      i = 0;
    }
    displayBinary(win[i]);
    i++;
    
    delay(H_DELAY);
  
  }
}
