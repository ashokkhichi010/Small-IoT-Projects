#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

#define ENA 9
#define ENB 10

#define IR_LEFT A0
#define IR_RIGHT A1

void setupMotors() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void moveForward(int speedVal) {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward(int speedVal) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft(int speedVal) {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight(int speedVal) {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void lineFollower() {
  int left = digitalRead(IR_LEFT);
  int right = digitalRead(IR_RIGHT);

  if (left == 0 && right == 0) {
    moveForward(150);
  } else if (left == 1 && right == 0) {
    turnLeft(150);
  } else if (left == 0 && right == 1) {
    turnRight(150);
  } else {
    stopCar();
  }
}

void setup() {
  Serial.begin(9600);
  setupMotors();

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
}

void loop() {
  lineFollower();
}
