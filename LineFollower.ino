// Motor driver pins
#define ENA 33 // Enable pin for left motor (PWM)
#define IN1 32 // Left motor IN1
#define IN2 25 // Left motor IN2
#define ENB 26 // Enable pin for right motor (PWM)
#define IN3 14 // Right motor IN3
#define IN4 27 // Right motor IN4

// IR sensor pins
#define LEFT_IR 13 // Left IR sensor (GPIO 13)
#define RIGHT_IR 35 // Right IR sensor (GPIO 35)

// Define speed factors for each motor
float leftMotorSpeed = 0.65/1.55; // Speed factor for the left motor
float rightMotorSpeed = 1/1.55; // Speed factor for the right motor
float turnSpeed = 2; // Speed factor during turns (for sharper turns)

// Enum to represent the last action taken by the robot
// This is crucial for handling acute angles where both sensors detect black
enum LastAction {
  FORWARD,
  LEFT_TURN,
  RIGHT_TURN
};

LastAction lastAction = FORWARD; // Initialize with FORWARD as the default action

void setup() {
  // Set motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set IR sensor pins as inputs
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  Serial.begin(115200); // Initialize serial communication for debugging
}

void loop() {
  // Read IR sensor values
  // 0 indicates no black line detected, 1 indicates black line detected
  int leftIRValue = digitalRead(LEFT_IR);
  int rightIRValue = digitalRead(RIGHT_IR);

  // Case 1: Move forward if neither sensor detects black
  if (leftIRValue == 0 && rightIRValue == 0) {
    moveForward();
    lastAction = FORWARD;
  }
  // Case 2: Turn right if only the left sensor detects black
  else if (leftIRValue == 0 && rightIRValue == 1) {
    turnRight();
    lastAction = RIGHT_TURN;
  }
  // Case 3: Turn left if only the right sensor detects black
  else if (rightIRValue == 0 && leftIRValue == 1) {
    turnLeft();
    lastAction = LEFT_TURN;
  }
  // Case 4: Both sensors detect black (potential acute angle)
  // Continue the last action to navigate through the acute angle
  else if (leftIRValue == 1 && rightIRValue == 1) {
    continueLastAction();
  }
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(IN1, HIGH); // Left motor forward
  digitalWrite(IN2, LOW);
  analogWrite(ENA, (int)(leftMotorSpeed * 255)); // Set left motor speed

  digitalWrite(IN3, HIGH); // Right motor forward
  digitalWrite(IN4, LOW);
  analogWrite(ENB, (int)(rightMotorSpeed * 255)); // Set right motor speed
}

// Function to turn the robot left
void turnLeft() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, (int)(turnSpeed * leftMotorSpeed * 255)); // Adjust speed for left turn
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, (int)(turnSpeed * 1 * 255)); // Adjust speed for right turn
}

// Function to continue the last action
// This is crucial for navigating acute angles
void continueLastAction() {
  switch (lastAction) {
    case FORWARD:
      moveForward();
      break;
    case LEFT_TURN:
      turnLeft();
      break;
    case RIGHT_TURN:
      turnRight();
      break;
  }
}
