void ps4_setup() 
{
 
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 USB Library Started"));
}

void xbox_setup()
{
  #if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
}


//motor setup.......
void motorSetup()
{
  pinMode(fra, OUTPUT);
  pinMode(frd, OUTPUT);
  pinMode(lta, OUTPUT);
  pinMode(ltd, OUTPUT);
  pinMode(rta, OUTPUT);
  pinMode(rtd, OUTPUT);  
}

// imu setup function
void imusetup() 
{
  Serial1.begin(57600);
  Serial1.write("#o0");

  for(int i=0;i<20;i++)//stabilization of imu values
  {
  ref_yaw=getImuValue();
  first_ref_yaw=ref_yaw;
  Serial.println(ref_yaw);
  } 
}


