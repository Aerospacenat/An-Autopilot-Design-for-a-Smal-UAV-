void loop1() {

  
  // what if we multiply everything by 10 to then get it into degrees?
  //int previousX = gyroX;
  //int previousY = gyroY;
  //int previousZ = gyroZ;
  mpu.update();
  delay(10);
  /*gyroX_raw = mpu.getGyroX();
  gyroY_raw = mpu.getGyroY();
  gyroZ_raw = mpu.getGyroZ();*/
  gyroX_raw = mpu.getAngleX();
  gyroY_raw = mpu.getAngleY();
  gyroZ_raw = mpu.getAngleZ();
  delay(10);
  //double ang_x_raw = mpu.getAccX();
  //double ang_y_raw = mpu.getAccY();
  //double ang_z_raw = mpu.getAccZ();

  //accelX = ang_x_raw - Acc_angle_error_x;
  //accelY = ang_y_raw - Acc_angle_error_y;
  //accelZ = ang_z_raw - Acc_angle_error_z;
  gyroX = gyroX_raw - Gyro_raw_error_x;
  gyroY = gyroY_raw - Gyro_raw_error_y;
  gyroZ = gyroZ_raw - Gyro_raw_error_z;

  //meanGX = (gyroX + previousX) /2;
  //meanGY = (gyroY + previousY) /2;
  //meanGZ = (gyroZ + previousZ) /2;
  /*
  if (gyroX >= 5) {
    xpos = true;
  }
  if (gyroX <= -5) {
    xneg = true;
  }
  if (gyroY >= 5) {
    ypos = true;
  }
  if (gyroY <= -5) {
    yneg = true;
  }
  if (gyroZ >= 5) {
    zpos = true;
  }
  if (gyroZ <= -5) {
    zneg = true;
  }
  */

  if (gyroX >= 15) { // imu limits
    gyroX = 15;
  }
  else if (gyroX <= -15) {
    gyroX = -15;
  }
  else if (gyroY >= 15) {
    gyroY = 15;
  }
  else if (gyroY <= -15) {
    gyroY = -15;
  }

  delay(10);
  //pico();
  yield(); // pass control on to another loop
}
