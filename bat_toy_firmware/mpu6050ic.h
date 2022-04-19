#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

struct mpuAngle{
    float angle_x;
    float angle_y;
    float angle_z;
  };
  
void mpu_init(){
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  }

 struct mpuAngle getangles(){
  struct mpuAngle angle;
  angle.angle_x = mpu6050.getAngleX();
  angle.angle_y = mpu6050.getAngleY();
  angle.angle_z = mpu6050.getAngleZ();

  return angle;
  }
