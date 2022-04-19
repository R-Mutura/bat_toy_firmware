
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
//#include <Wire.h>

Adafruit_MPU6050 mpu;

 struct mpuData{
    float accel_x;
    float accel_y;
    float accel_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;

    float mputemp;
    
  };

void mpu6050_init()
{
      
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      yield();
    }
  }
  Serial.println("MPU6050 Found!");

  //initializing accelerometer 
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  //initialize gyroscope
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  //initializing filter parameters
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  
}
struct mpuData getMpuData()
{     
  //initialize storage variables
      struct mpuData mpu6050_data;
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

 //read accelerometer data
   mpu6050_data.accel_x = a.acceleration.x;
   mpu6050_data.accel_y = a.acceleration.y;   
   mpu6050_data.accel_z = a.acceleration.z;
 //read gyro data
    mpu6050_data.gyro_x = g.gyro.x;
    mpu6050_data.gyro_y = g.gyro.y;
    mpu6050_data.gyro_z = g.gyro.z;
//read temperature
    mpu6050_data.mputemp=temp.temperature;

    
  return mpu6050_data;
} 

//function to get the angle from the mpu data
