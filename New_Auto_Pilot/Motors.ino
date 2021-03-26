void motors() {
  m1.writeMicroseconds(speed1);
  m2.writeMicroseconds(speed2);
  m3.writeMicroseconds(speed3);
  m4.writeMicroseconds(speed4);
  delay(10);
}

void motors_stop() {
  m1.writeMicroseconds(1000); // send "stop" signal to ESC. was 1000
  m2.writeMicroseconds(1000); // send "stop" signal to ESC.
  m3.writeMicroseconds(1000); // send "stop" signal to ESC.
  m4.writeMicroseconds(1000); // send "stop" signal to ESC.
  delay(10);
}

void throttle_check() { // This is to throttle down the motors if throttle is over 1500
  if (throttle >= 1500) {
    check_throttle = false;
    //for (throttle; throttle <= 1500; throttle--) {
      throttle = throttle - 1;
      stabilize();
      speed_motors();
      min_max_Hover();
      motors();
      delay(100);
    }
    check_throttle = true;
  }


void motors_comm(){ // common motor functions
speed_motors();
  min_max();
  motors();
  delay(100);
  if (PID_Activated = 1) {
    min_max();
    motors();
    delay(100);
  }
  PID_Activated = 0;
  delay(50);
}
