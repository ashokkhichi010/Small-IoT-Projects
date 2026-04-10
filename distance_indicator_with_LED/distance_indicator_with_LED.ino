#define TRIG 9
#define ECHO 10

#define GREEN 2
#define YELLOW 3
#define RED 4

unsigned long duration;
float distance;

// timing control (non-blocking blink)
unsigned long previousMillis = 0;
bool ledState = false;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);

  Serial.begin(9600);
}

// -------- Distance Measurement --------
float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000); // timeout for stability

  float dist = duration * 0.034 / 2;

  // filter invalid readings
  if (dist == 0 || dist > 400) return -1;

  return dist;
}

// -------- LED Control --------
void setLEDs(bool g, bool y, bool r) {
  digitalWrite(GREEN, g);
  digitalWrite(YELLOW, y);
  digitalWrite(RED, r);
}

// -------- Loop --------
void loop() {

  distance = getDistance();

  if (distance == -1) {
    Serial.println("Out of range");
    return;
  }

  Serial.print("Distance: ");
  Serial.println(distance);

  unsigned long currentMillis = millis();

  // FAR → Green
  if (distance > 70) {
    setLEDs(HIGH, LOW, LOW);
  }

  // MEDIUM → Yellow blinking
  else if (distance > 30) {

    if (currentMillis - previousMillis >= 300) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(YELLOW, ledState);
    }

    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
  }

  // NEAR → Red fast blinking
  else {

    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(RED, ledState);
    }

    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
  }
}