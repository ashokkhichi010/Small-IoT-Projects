#include <Wire.h>

// MPU6050 registers
const int MPU_addr = 0x68;

int16_t AcX, AcY, AcZ;

void setup() {
  Serial.begin(115200);

  Wire.begin(D2, D1);  // SDA, SCL

  // Wake up MPU6050
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  // Wire.requestFrom(0x68, 6, true);
  Wire.requestFrom((uint8_t)0x68, (size_t)6, true);

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();

  Serial.print("X: ");
  Serial.print(AcX);
  Serial.print(" Y: ");
  Serial.print(AcY);
  Serial.print(" Z: ");
  Serial.println(AcZ);

  delay(500);
}
