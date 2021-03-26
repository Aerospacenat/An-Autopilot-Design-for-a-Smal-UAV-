
void PODA() {
  PODA_check();
  //////////forward///////////////////////////
  if (LidarOB == true) {
    ///hover();
    Bright = true;
    Bleft = false;
    movement();
  }

  /////////right//////////////////////////////

  else if (Right == true) {
    hover();
    Bright = false;
    Bleft = true;
    movement();
  }



  ///////////left/////////////////////////////

  else if (Left == true) {
    hover();
    Bright = true;
    Bleft = false;
    movement();
  }

  /////////////behind//////////////////////////

  else if (Behind == true) {
    Bright = true;
    Bleft = false;
    movement();
    hover();
  }
}

void PODA_check(){
  LiDAR();
  pico();
}
