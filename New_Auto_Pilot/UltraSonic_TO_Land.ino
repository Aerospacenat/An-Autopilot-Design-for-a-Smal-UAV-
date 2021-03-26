void Ultra_TO() {
  Serial.println("TO Time");
  pico();
  excel();
  pico();
  if (TOHeightR == false) {
    //Serial.println("Take Off");
    //Serial1.println("Take Off");
    throttle = throttle + 2;
    TO();
  }
  if (TOHeightR == true) {
    //Serial.println("Hover");
    //Serial1.println("Hover");
    throttle = throttle;
    TO();
    //ultra_hover();
  }
  if (throttle >=1600){
    throttle = 1600;
  }
  delay(100);
}
