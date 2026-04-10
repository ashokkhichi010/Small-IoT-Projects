#define TRIG D5
#define ECHO D6
#define BUZZER D7

long duration;
float distance;

void setup() {

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  distance = duration * 0.034 / 2;

  Serial.println(distance);

  if(distance > 100) {
    digitalWrite(BUZZER, LOW);
  }

  else if(distance > 50) {
    beep(800);
  }

  else if(distance > 20) {
    beep(300);
  }

  else {
    digitalWrite(BUZZER, HIGH);
  }

}

void beep(int delayTime) {
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(delayTime);
}