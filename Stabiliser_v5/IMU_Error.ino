void IMU_init(){
  //IMU Initialation
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) { } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true, true); // gyro and accelero
  Serial.println("Done!\n");

  Serial1.print(F("MPU6050 status: "));
  Serial1.println(status);
  Serial1.println("Done!\n");
}

void gyro_error_check() {
  
  for (int i = 0; i < 200; i++)
  {
    mpu.update();
    Gyr_rawX = mpu.getGyroX();
    Gyr_rawY = mpu.getGyroY();
    Gyr_rawZ = mpu.getGyroZ();
    /*---X---*/
    Gyro_raw_error_x = Gyro_raw_error_x + (Gyr_rawX / 32.8);
    /*---Y---*/
    Gyro_raw_error_y = Gyro_raw_error_y + (Gyr_rawY / 32.8);
    Gyro_raw_error_z = Gyro_raw_error_z + (Gyr_rawZ / 32.8);
    if (i == 199)
    {
      Gyro_raw_error_x = Gyro_raw_error_x / 200;
      Gyro_raw_error_y = Gyro_raw_error_y / 200;
      Gyro_raw_error_z = Gyro_raw_error_z / 200;
      gyro_error = 1;
    }
  }
}

  void acc_error_check() {
    
    for (int a = 0; a < 200; a++)
    {
      mpu.update();
      Acc_rawX = mpu.getAccX(); //each value needs two registres
      Acc_rawY = mpu.getAccY();
      Acc_rawZ = mpu.getAccZ();
      /*---X---*/
      Acc_angle_error_x = Acc_angle_error_x + ((atan((Acc_rawY) / sqrt(pow((Acc_rawX), 2) + pow((Acc_rawZ), 2))) * rad_to_deg));
      /*---Y---*/
      Acc_angle_error_y = Acc_angle_error_y + ((atan(-1 * (Acc_rawX) / sqrt(pow((Acc_rawY), 2) + pow((Acc_rawZ), 2))) * rad_to_deg));

      if (a == 199)
      {
        Acc_angle_error_x = Acc_angle_error_x / 200;
        Acc_angle_error_y = Acc_angle_error_y / 200;
        Acc_angle_error_z = Acc_rawZ / 200;
        acc_error = 1;
      }
    }
  }
