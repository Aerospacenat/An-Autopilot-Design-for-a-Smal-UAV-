void pico() {
  if (Serial2.available() > 0) {
    data = Serial2.readStringUntil('\n');
    /* Serial.print("You sent me: ");
      Serial.println(data);
      Serial1.print("You sent me: ");
      Serial1.println(data);
    */
    Serial.println(data); Serial1.println(data);
    if ( data == "D20") {
      Serial1.println("TakeOff Height Reached");
      TOHeightR = true;
      LDGNDR = false;
    }
    Serial.println(data); Serial1.println(data);
    if ( data == "D12") {
      Serial1.println("Landed on Ground");
      LDGNDR = true;
      TOHeightR = false;
    }
    if ( data == "LO") {
      Serial1.println("Object to the left");
      Left = true;
    }
    if ( data == "RO") {
      Serial1.println("Object to the right");
      Right = true;
    }
    if ( data == "BO") {
      Serial1.println("Object to the back");
      Behind = true;
    }
    lastData = data;
  }
  //yield();
}
