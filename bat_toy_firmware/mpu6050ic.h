#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

struct mpuAngle{
    float angle_x;
    float angle_y;
    float angle_z;
  }angle;
  
void mpu_init(){
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  }

 void getangles(){
  
  struct mpuAngle angle;

  mpu6050.update();
  
  angle.angle_x = mpu6050.getAngleX();
  angle.angle_y = mpu6050.getAngleY();
  angle.angle_z = mpu6050.getAngleZ();

  
  }
  
 void resetangle(int x)
 {
  if(x==1)  angle.angle_x = 0;
  else if(x==2)  angle.angle_y = 0;
  else if(x==3)  angle.angle_z = 0;
  else {return;}
 }

 float getaccelz(){
   return mpu6050.getAccZ();
  }

 
