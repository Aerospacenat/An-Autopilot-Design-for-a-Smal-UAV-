void hover() {
  //IMURead();
  Serial.println("Hover Mode");
  stabilize();
  level();
  if (check_throttle == false) {
    throttle_check();
  }
  speed_motors();
  motors();
  delay(10);
  if (PID_Activated = 1) {
    motors();
    delay(10);
  }
  PID_Activated = 0;
  min_max();
  excel();
  delay(10);
}
void level() {

  if (TOHeightR == false) {
    throttle = throttle + 1;
    TO();
  }
  if (TOHeightR == true) {
    throttle = throttle;
  }
}
