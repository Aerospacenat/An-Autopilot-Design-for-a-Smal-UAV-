void stabilize() {
  PIDv2();
}
 void PID_reset(){
  x_output = 0;
  y_output = 0;
  z_output = 0;
 }
void PIDv2() {

  //x_rotation = gyroX * 180 / M_PI - x_level_error;
  x_rotation = gyroX ;
  //x_rotation = float(x_rotation);
  //y_rotation = gyroY * 180 / M_PI - y_level_error;
  y_rotation = gyroY ;
  //y_rotation = float(y_rotation);
  //z_rotation = gyroZ * 180 / M_PI;
  z_rotation = gyroZ ;
  //z_rotation = float(z_rotation);
  Serial1.println(x_rotation);
  Serial1.println(y_rotation);
  Serial1.println(z_rotation);
  x_output = calculatePID(0, x_rotation);
  y_output = calculatePID(1, y_rotation);
  z_output = calculatePID(2, z_rotation);

  /*if ( xpos == true || xneg == true) {
    x_output = calculatePID(0, x_rotation);
    }
    else if ( xpos == false || xneg == false) {
    x_output = 0;
    }
    if ( ypos == true || yneg == true) {
    y_output = calculatePID(1, y_rotation);
    }
    else if ( ypos == false || yneg == false) {
    y_output = 0;
    }
    if ( zpos == true || zneg == true) {
    z_output = calculatePID(2, z_rotation);
    }
    else if ( zpos == false || zneg == false) {
    z_output = 0;
    }
  */
}

int calculatePID(int _axis, int _angel) {
  
  //int x_kp = 1, x_ki = 1, x_kd = 2; //values for PID X axis
  //int y_kp = 1, y_ki = 1, y_kd = 2; //values for PID Y axis
  //int z_kp = 1, z_ki = 0, z_kd = 0; //values for PID Z axis
  float x_kp = 1.3, x_ki = 0.04, x_kd = 18.0; //values for PID X axis
  float y_kp = 1.3, y_ki = 0.04, y_kd = 18.0; //values for PID Y axis
  float z_kp = 4.0, z_ki = 0.02, z_kd = 0.0; //values for PID Z axis
  float  notZ_out, notY_out, notX_out;

  // X AXIS
  if (_axis == 0) {
    x_now = millis();
    x_timechange = x_now - x_lasttime;
    x_error = x_setpoint - _angel;
    x_p_out = (x_kp * x_error);

    x_errorsum = (x_errorsum + x_error);
    if (x_errorsum > 1023) {
      x_errorsum = 1023;
    }
    if (x_errorsum < -1023) {
      x_errorsum = -1023;
    }
    x_i_out = (x_ki * x_errorsum)/2;
    x_d_error = (x_error - x_lasterror) / x_timechange;
    x_d_out = x_kd * x_d_error;
    x_lasterror = x_error;
    notX_out = (x_p_out + x_i_out + x_d_out);
    if (notX_out > max_pid) {
      notX_out = max_pid;
    } else if (notX_out < -(max_pid)) {
      notX_out = -(max_pid);
    }
    
    x_lasttime = millis();
    x_output = notX_out;
    /*if (isnan(x_output)){
      x_output = 0;
    }*/
    return x_output;
  }

  // Y AXIS
  else if (_axis == 1) {
    y_now = millis();
    y_timechange = y_now - y_lasttime;
    y_error = y_setpoint - _angel;
    y_p_out = (y_kp * y_error);

    y_errorsum = (y_errorsum + y_error) * y_timechange;
    if (y_errorsum > 1023) {
      y_errorsum = 1023;
    }
    if (y_errorsum < -1023) {
      y_errorsum = -1023;
    }
    y_i_out = (y_ki * y_errorsum)/2;
    y_d_error = (y_error - y_lasterror) / y_timechange;
    y_d_out = y_kd * y_d_error;
    y_lasterror = y_error;
    notY_out = (y_p_out + y_i_out + y_d_out);
    if (notY_out > max_pid) {
      notY_out = max_pid;
    } else if (notY_out < -(max_pid)) {
      notY_out = -(max_pid);
    }
    y_output = notY_out;
    y_lasttime = millis();
    /*if (isnan(y_output)){
      y_output = 0;
    }*/
    return y_output;

    // ALTITUDE
    // } else if(_axis == 2){
    //           return (set_altitude - current_altitude) * 20;
  } else if (_axis == 2) {
    z_now = millis();
    z_timechange = z_now - z_lasttime;
    z_error = z_setpoint - _angel;
    z_p_out = (z_kp * z_error);

    z_errorsum = (z_errorsum + z_error) * z_timechange;
    if (z_errorsum > 1023) {
      z_errorsum = 1023;
    }
    if (z_errorsum < -1023) {
      z_errorsum = -1023;
    }
    z_i_out = (z_ki * z_errorsum)/2;
    z_d_error = (z_error - z_lasterror) / z_timechange;
    z_d_out = z_kd * y_d_error;
    z_lasterror = y_error;
    notZ_out = (z_p_out + z_i_out + z_d_out);
    if (notZ_out > max_pid) {
      notZ_out = max_pid;
    } else if (notZ_out < -(max_pid)) {
      notZ_out = -(max_pid);
    }
    z_output = notZ_out;
    z_lasttime = millis();
    /*if (isnan(z_output)){
      z_output = 0;
    }*/
    return z_output;

    // ALTITUDE
    // } else if(_axis == 2){
    //           return (set_altitude - current_altitude) * 20;
  } else {
    return 0;
  }


  
  delay(200);
  PID_Activated = 1;
  /*
  xpos = false;
  xneg = false;
  ypos = false;
  yneg = false;
  zpos = false;
  zneg = false;
*/
}
