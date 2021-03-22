void TO() { // take off
  // change the speed1 for next time through the loop:
  stabilize();
  motors_comm();
  TOHeightR = false;
  delay(100);
}

void land() {
  currentMillis = 0;
  pico();
  if (LDGNDR == false) {
    Serial.println("Landing");
    Serial1.println("Landing");
    if ( speed1 < 1600) {
      stabilize();
      throttle = throttle - 8 ;
      motors_comm();
    }
  }
  
  else if (LDGNDR == true) {
    Serial.println("Landed");
    Serial1.println("Landed");
    speed1 = 1100;
    speed2 = 1100;
    speed3 = 1100;
    speed4 = 1100;
  }
}
