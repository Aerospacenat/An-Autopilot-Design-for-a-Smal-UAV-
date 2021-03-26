void LiDARinit(){
   // Step 2: Initialize the data rate for the SoftwareSerial port
  Serial3.begin(TFMINI_BAUDRATE);

  // Step 3: Initialize the TF Mini sensor
  tfmini.begin(&Serial3); 
}
void LiDAR(){
  dist = tfmini.getDistance();
  strength = tfmini.getRecentSignalStrength();

  // Display the measurement
   

  // Wait some short time before taking the next measurement
  if (dist > 400){
    dist = 400;
  }
  else if (dist < 400){
    LidarOB = true;
  }
  delay(10); 
}
