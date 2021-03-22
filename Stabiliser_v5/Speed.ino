void speed_motors(){ //To add the PID to the throttle for
  speed1 = (int)(throttle + (y_output ) + (x_output) );
  speed2 = (int)(throttle - (y_output ) + (x_output) );
  speed3 = (int)(throttle - (y_output ) - (x_output) );
  speed4 = (int)(throttle + (y_output ) - (x_output) );
  
  /*speed1 += x_output / 2;
  //speed1 += z_output;
  speed4 -= x_output / 2;
 // speed4 += z_output;

  speed2 -= y_output / 2;
  //speed2 -= z_output;
  speed3 += y_output / 2;
  //speed3 -= z_output;
  */
  
}

/*
  speed1 = (int)(throttle + current_y_adder + current_x_adder - current_z_adder);
  speed2 = (int)(throttle - current_y_adder + current_x_adder + current_z_adder);
  speed3 = (int)(throttle - current_y_adder - current_x_adder - current_z_adder);
  speed4 = (int)(throttle + current_y_adder - current_x_adder + current_z_adder);
 */


/*
  speed1 = (int)(main_power + current_y_adder + current_x_adder - current_z_adder );//-  (-P_z - I_z - D_z-)
  speed2 = (int)(main_power - current_y_adder + current_x_adder + current_z_adder);//-
  speed3 = (int)(main_power - current_y_adder - current_x_adder - current_z_adder);
  speed4 = (int)(main_power + current_y_adder - current_x_adder + current_z_adder);
 */
