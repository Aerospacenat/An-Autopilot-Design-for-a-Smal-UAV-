void Emergency_land() {
  speed1 = speed1 - 5;
  speed2 = speed2 - 5;
  speed3 = speed3 - 5;
  speed4 = speed4 - 5;

  min_max();
  // wait for 300 milliseconds to see the dimming effect
  delay(100);
  currentMillis = 0;
}

//void PID_check(){
//  current_x_adder
// current_y_adder
//current_z_adder
//}

void off(){
  speed1 = speed1 - 5;
  speed2 = speed2 - 5;
  speed3 = speed3 - 5;
  speed4 = speed4 - 5;

  // wait for 300 milliseconds to see the dimming effect
  delay(100);
  currentMillis = 0;
}
