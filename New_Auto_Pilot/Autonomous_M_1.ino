void  autonomousMode_1() {
  currentMillis = millis(); // variable being set to time
  unsigned long Minute = currentMillis / 60000; // converts the time to a minute
  Serial.println(Minute); // print minute
  Serial1.println(Minute);
  //PODA();
  //Serial.println(previousCase);
  previousCase = switchCase; // set this variable to the last switch case number

  if (Minute == 0) { // take off
    switchCase = 1;
  }
  if(Minute == 2){ // hover
    switchCase = 8;
  }
  if (Minute == 2) { // right
    switchCase = 2;
  }
  if (Minute == 3) { // left
    switchCase = 3;
  }
  if (Minute == 4) { //backward
    switchCase = 4;
  }
  if (Minute == 5) { // forward
    switchCase = 5;
  }
  if (Minute == 6) { //land
    switchCase = 6;
  }
  if (Minute > 7) { //land
    if (DistDown <= 12) { //motor stop
      switchCase = 7;
    }
  }
  switch (previousCase) { // switch cases

    case 1:
      Serial.println("Take OFF");
      Serial1.println("Take OFF");
      x_setpoint = 0;
      y_setpoint = 0;
      //Ultra_TO();
      hover();
      break;
    case 2:
      Serial.println("right");
      Serial1.println("right");
      Bright = true;
      movement();
      break;
    case 3:
      Serial.println("left");
      Serial1.println("left");
      Bright = false;
      Bleft = true;
      movement();
      break;
    case 4:
      Serial.println("backward");
      Serial1.println("backward");
      Bleft = false;
      Bbackward = true;
      movement();
      break;
    case 5:
      Serial.println("forward");
      Serial1.println("forward");
      Bbackward = false;
      Bforward = true;
      movement();
      break;
    case 6:
      Serial.println("Land");
      Serial1.println("Land");
      Bforward = false;
      land();
      break;
    case 7:
      Serial.println("Landed");
      Serial1.println("Landed");
      motors_stop();
      break;
    case 8:
      Serial.println("hover");
      Serial1.println("hover");
      x_setpoint = 0;
      y_setpoint = 0;
      hover();
      break;

  }
  Serial.println(switchCase);
  if (throttle >=1600){
    throttle = 1600;
  }
}
