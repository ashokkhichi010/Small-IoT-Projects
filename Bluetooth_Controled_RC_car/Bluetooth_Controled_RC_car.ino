#include <SoftwareSerial.h>

// -------- BLUETOOTH --------
SoftwareSerial BT(2, 3); // RX, TX

char command;

// -------- MOTOR PINS --------
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENA 9
#define ENB 10

int speedVal = 180;

// -------- SETUP --------
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  BT.begin(9600);
  Serial.begin(9600);
}

// -------- MOTOR FUNCTIONS --------
void forward() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
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

// -------- DIAGONAL --------
void forwardLeft() {
  analogWrite(ENA, speedVal / 2);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void forwardRight() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal / 2);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backwardLeft() {
  analogWrite(ENA, speedVal / 2);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backwardRight() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal / 2);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// -------- LOOP --------
void loop() {

  if (BT.available()) {
    command = BT.read();
    Serial.println(command);

    switch (command) {

      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stopCar(); break;

      case 'G': forwardLeft(); break;
      case 'I': forwardRight(); break;
      case 'H': backwardLeft(); break;
      case 'J': backwardRight(); break;
    }
  }
}