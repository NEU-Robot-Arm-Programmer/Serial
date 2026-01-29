#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

constexpr int SDA1_PIN = 26;
constexpr int SCL1_PIN = 27;
constexpr int SDA0_PIN = 20;  
constexpr int SCL0_PIN = 21; 

constexpr uint8_t BNO_ADDR = 0x28;

Adafruit_BNO055 bno_1 = Adafruit_BNO055(55, BNO_ADDR, &Wire1);
Adafruit_BNO055 bno_2 = Adafruit_BNO055(55, BNO_ADDR, &Wire);

double radTodeg = 57.295779513;
int calib[6];
int button;

// Store QUATERNIONS for calibration, not Euler angles!
imu::Quaternion q1_neutral;
imu::Quaternion q2_neutral;
bool is_calibrated = false;

void setup(void) 
{
  Serial.begin(115200);
  
  Wire1.setSDA(SDA1_PIN);
  Wire1.setSCL(SCL1_PIN);
  Wire1.begin();  

  Wire.setSDA(SDA0_PIN);
  Wire.setSCL(SCL0_PIN);
  Wire.begin();
  
  if(!bno_1.begin(OPERATION_MODE_NDOF))
  {
    Serial.print("Ooops no BNO055 #1 detected ... Check your wiring or I2C ADDR!");
  }
  if(!bno_2.begin(OPERATION_MODE_NDOF))
  {
    Serial.print("Ooops no BNO055 #2 detected ... Check your wiring or I2C ADDR!");
  }
  
  pinMode(17, INPUT_PULLUP);
  
  delay(1000);
    
  bno_1.setExtCrystalUse(true);
  bno_2.setExtCrystalUse(true);
  
  // Initialize neutral quaternions to identity
  q1_neutral = imu::Quaternion(1, 0, 0, 0);
  q2_neutral = imu::Quaternion(1, 0, 0, 0);
}

void setCalStatus(void)
{
  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  bno_1.getCalibration(&sys, &gyro, &accel, &mag);

  calib[0] = (int)gyro;
  calib[1] = (int)accel;
  calib[2] = (int)mag;

  sys = gyro = accel = mag = 0;
  bno_2.getCalibration(&sys, &gyro, &accel, &mag);

  calib[3] = (int)gyro;
  calib[4] = (int)accel;
  calib[5] = (int)mag;
}

// Quaternion conjugate (inverse for unit quaternions)
imu::Quaternion quatConjugate(const imu::Quaternion& q) {
  return imu::Quaternion(q.w(), -q.x(), -q.y(), -q.z());
}

void loop(void) 
{
  setCalStatus();
  button = digitalRead(17);
  
  // Get quaternions directly (no Euler conversion needed!)
  imu::Quaternion q1 = bno_1.getQuat();  // Thumb
  imu::Quaternion q2 = bno_2.getQuat();  // Hand
  
  // Send quaternions: w,x,y,z for each IMU
  Serial.print(q1.w(), 6); Serial.print(",");
  Serial.print(q1.x(), 6); Serial.print(",");
  Serial.print(q1.y(), 6); Serial.print(",");
  Serial.print(q1.z(), 6); Serial.print(",");
  Serial.print(q2.w(), 6); Serial.print(",");
  Serial.print(q2.x(), 6); Serial.print(",");
  Serial.print(q2.y(), 6); Serial.print(",");
  Serial.print(q2.z(), 6); Serial.print(",");
  Serial.print(calib[0]); Serial.print(",");
  Serial.print(calib[1]); Serial.print(",");
  Serial.print(calib[2]); Serial.print(",");
  Serial.print(button);
  Serial.println("");
  
  delay(10);
}