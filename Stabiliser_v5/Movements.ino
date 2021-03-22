void movement() {
  PODA();
  if (throttleCheck = false) {
    throttle_check();
  }
  if (Bright = true) {
    right();
  }
  if (Bleft = true) {
    left();
  }
  if (Bbackward = true) {
    backward();
  }
  if (Bforward = true) {
    forward();
  }
  level();
  stabilize();
  speed_motors();
  min_max_Hover();
  motors();
  excel();
  delay(100);
  if (PID_Activated = 1) {
    min_max_Hover();
    motors();
    delay(100);
  }
  PID_Activated = 0;
  //serial_motors();

  delay(50);
  Left = false;
  Right = false;
  Behind = false;
}

void right() {
  y_setpoint = 0;  // Y axis
  x_setpoint = -10; // X axis
}
void left() {
  y_setpoint = 0;  // Y axis
  x_setpoint = +10; // X axis
}

void forward() {
  y_setpoint = +10;  // Y axis
  x_setpoint = 0; // X axis
}

void backward() {
  y_setpoint = -10;  // Y axis
  x_setpoint = 0; // X axis
}
