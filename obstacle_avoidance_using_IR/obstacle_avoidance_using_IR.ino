// -------- IR PINS --------
#define IR_LEFT  6
#define IR_RIGHT 7

// -------- MOTOR PINS --------
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENA 9
#define ENB 10

// -------- STATES --------
enum State { MOVE, STOP, REVERSE, TURN };
State currentState = MOVE;

// -------- SPEED --------
int currentSpeed = 0;
int targetSpeed = 0;
const int MAX_SPEED = 180;

// -------- TIMING --------
unsigned long lastSpeedUpdate = 0;
unsigned long stateStartTime = 0;

// -------- TURN --------
int turnDirection = 0; // 1 = left, 2 = right

// -------- SETUP --------
void setup() {
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
}

// -------- MOTOR CONTROL --------
void setMotor(int left, int right, bool forward = true) {

  left = constrain(left, 0, 255);
  right = constrain(right, 0, 255);

  analogWrite(ENA, left);
  analogWrite(ENB, right);

  if (forward) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

void stopMotor() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// -------- SMOOTH SPEED --------
void updateSpeed() {
  if (millis() - lastSpeedUpdate > 20) {
    lastSpeedUpdate = millis();

    if (currentSpeed < targetSpeed) currentSpeed += 2;
    else if (currentSpeed > targetSpeed) currentSpeed -= 10;
  }
}

// -------- READ IR --------
void readIR(bool &leftObs, bool &rightObs) {
  leftObs  = (digitalRead(IR_LEFT)  == LOW);
  rightObs = (digitalRead(IR_RIGHT) == LOW);
}

// -------- LOOP --------
void loop() {

  bool leftObs, rightObs;
  readIR(leftObs, rightObs);

  Serial.print("L:");
  Serial.print(leftObs);
  Serial.print(" R:");
  Serial.print(rightObs);
  Serial.print(" State:");
  Serial.println(currentState);

  switch (currentState) {

    // -------- NORMAL MOVE --------
    case MOVE:

      if (!leftObs && !rightObs) {
        targetSpeed = MAX_SPEED;
        updateSpeed();
        setMotor(currentSpeed, currentSpeed, true);
      }

      else {
        targetSpeed = 0;
        currentState = STOP;
        stateStartTime = millis();
      }

      break;

    // -------- STOP --------
    case STOP:

      updateSpeed();
      setMotor(currentSpeed, currentSpeed);

      if (currentSpeed == 0) {
        currentState = REVERSE;
        stateStartTime = millis();
      }

      break;

    // -------- REVERSE --------
    case REVERSE:

      setMotor(200, 200, false); // backward

      if (millis() - stateStartTime > 800) {
        
        // decide direction
        if (leftObs && !rightObs) turnDirection = 2; // go right
        else if (!leftObs && rightObs) turnDirection = 1; // go left
        else turnDirection = 2; // default right

        currentState = TURN;
        stateStartTime = millis();
      }

      break;

    // -------- TURN --------
    case TURN:

      if (turnDirection == 1) {
        // LEFT TURN
        setMotor(80, 160, true);
      } else {
        // RIGHT TURN
        setMotor(160, 80, true);
      }

      if (millis() - stateStartTime > 500) {
        currentState = MOVE;
      }

      break;
  }
}