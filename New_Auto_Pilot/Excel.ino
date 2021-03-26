void excel() { //prints to serial which can then be exported to excel to graph the data
  Serial.print((gyroX));
  Serial.print(",");
  Serial.print((gyroY));
  Serial.print(",");
  Serial.print((gyroZ));
  Serial.print(",");
  Serial.print(speed1);
  Serial.print(",");
  Serial.print(speed2);
  Serial.print(",");
  Serial.print(speed3);
  Serial.print(",");
  Serial.print(speed4);
  Serial.print(",");
  Serial.print(x_output);
  Serial.print(",");
  Serial.print(y_output);
  Serial.print(",");
  Serial.print(z_output);
  Serial.print(",");
  Serial.print(throttle);
  Serial.print(",");
  Serial.println(dist);

  Serial1.print((gyroX));
  Serial1.print(",");
  Serial1.print((gyroY));
  Serial1.print(",");
  Serial1.print((gyroZ));
  Serial1.print(",");
  Serial1.print(x_output);
  Serial1.print(",");
  Serial1.print(y_output);
  Serial1.print(",");
  Serial1.println(z_output);
  

}
