#include <Servo.h>

#define TRIG 9
#define ECHO 10

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

#define ENA 11
#define ENB 12

Servo scanServo;

long duration;
float distance;

// Speed control
int currentSpeed = 0;
int targetSpeed = 0;

// Turning control
int leftSpeed = 0;
int rightSpeed = 0;

// Timing
unsigned long lastUpdate = 0;

// Servo scan state
int scanState = 0;
unsigned long scanTimer = 0;
int leftDist = 0, rightDist = 0;

// Const vars
int BREAK_DIST = 150;
int STOP_DIST = 20;
int HIGHEST_SPEED = 200;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  scanServo.attach(6);

  Serial.begin(9600);
}

// -------- Distance --------
float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);
  return duration * 0.034 / 2;
}

// -------- Motor Control --------
void setMotor(int left, int right) {  
  analogWrite(ENA, left);
  analogWrite(ENB, right);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// -------- Smooth Speed --------
void updateSpeed() {
  if (millis() - lastUpdate > 20) {
    lastUpdate = millis();

    if (targetSpeed == 0) currentSpeed = 0;
    else if (currentSpeed < targetSpeed) currentSpeed += 1;
    else if (currentSpeed > targetSpeed) currentSpeed -= 1;
  }
}

// -------- Servo Scan (Non-blocking) --------
bool scanEnvironment(int &direction) {    
  Serial.print("- scanState ");
  Serial.print(scanState);
  Serial.print("- ");

  if (scanState == 0) {
    scanServo.write(150);
    scanTimer = millis();
    scanState = 1;
  }

  else if (scanState == 1 && millis() - scanTimer > 300) {
    leftDist = getDistance();    
    scanServo.write(30);
    scanTimer = millis();
    scanState = 2;
  }

  else if (scanState == 2 && millis() - scanTimer > 300) {
    rightDist = getDistance();    
    scanServo.write(90);
    scanState = 3;
  }

  else if (scanState == 3) {
    direction = (leftDist > rightDist) ? 1 : 2;
    Serial.print("- direction ");
    Serial.print(direction);
    scanState = 0;
    return true;
  }

  return false;
}

// -------- Loop --------
void loop() {

  distance = getDistance();
  // -------- Speed Logic --------
  if (distance <= STOP_DIST) {
    targetSpeed = 0;
  } else if (distance < BREAK_DIST) {
    targetSpeed = map(distance, STOP_DIST, BREAK_DIST, 0, currentSpeed);
  } else {
    targetSpeed = HIGHEST_SPEED;
    scanServo.write(0);
    scanState = 0;
  }
  updateSpeed();
  // smooth straight movement
  setMotor(currentSpeed, currentSpeed); 
  
  Serial.print("distance ");
  Serial.print(distance);
  Serial.print(" currentSpeed ");
  Serial.print(currentSpeed);

  // -------- Movement --------
  if (distance < BREAK_DIST) {
    int dir;    
    if (scanEnvironment(dir)) {

      if (dir == 1) {
        // smooth left turn (differential)        
        Serial.print(" -- left turn -- ");
        setMotor(80, 180);
      }
      else {
        // smooth right turn    
        Serial.print(" -- right turn -- ");
        setMotor(180, 80);
      }
    }
  }  

  Serial.println();
}




/*
 - output: 

distance 262.29 currentSpeed 23
distance 260.95 currentSpeed 24
distance 260.73 currentSpeed 25
distance 131.46 currentSpeed 24- scanState 0- 
distance 89.69 currentSpeed 23- scanState 1- 
distance 94.89 currentSpeed 22- scanState 1- 
distance 95.12 currentSpeed 21- scanState 1- 
distance 78.63 currentSpeed 20- scanState 1- 
distance 80.34 currentSpeed 19- scanState 1- 
distance 80.12 currentSpeed 18- scanState 1- 
distance 90.15 currentSpeed 17- scanState 1- 
distance 90.42 currentSpeed 16- scanState 2- 
distance 102.15 currentSpeed 15- scanState 2- 
distance 96.83 currentSpeed 14- scanState 2- 
distance 100.20 currentSpeed 13- scanState 2- 
distance 98.67 currentSpeed 12- scanState 2- 
distance 112.91 currentSpeed 11- scanState 2- 
distance 113.27 currentSpeed 10- scanState 2- 
distance 114.75 currentSpeed 9- scanState 3- - direction 2 -- right turn -- 
distance 135.46 currentSpeed 8- scanState 0- 
distance 144.96 currentSpeed 7- scanState 1- 
*/