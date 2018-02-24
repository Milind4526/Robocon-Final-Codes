
//imu read function

float getImuValue()
{
  float my_value = 0;
  int i = 0;

  for (int j = 0; j < 40; j++)
  {
    buff[j] = 0;
  }

  //token request
  Serial1.write("#f");
  delay(35);   //waiting for arbitrary time of around 90ms after which imu sends data packet

  int f = 1; //flag variable

  while (1)
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      buff[i++] = c;
      f = 0;
    }

    if (f == 0)
    {
      break;
    }
  }
  String str = buff;
  yaw_string = str.substring(5, str.indexOf(",")); //breaking the sting yaw
  pitch_string = str.substring(str.indexOf(",") + 1, str.lastIndexOf(","));
  roll_string = str.substring(str.lastIndexOf(",") + 1);

  float yaw =::atof(yaw_string.c_str()); //change into char array then into float
  float pitch =::atof(pitch_string.c_str());
  float roll =::atof(roll_string.c_str());

  //Serial.println();

  //Serial.print("pitch : ");
  //Serial.println(pitch);
  //Serial.print("roll : ");
  //Serial.println(roll);


  if (yaw == 0 && abs(lastYaw - yaw) >= 10)
  {
    yaw = lastYaw;
  }
  lastYaw = yaw;
  if (yaw >= -180 and yaw < 0) {
    my_value = angle[int(Map(yaw, -180, 0 , 180, 360))];
  }
  else my_value = angle[int(yaw)];
  Serial.print("my_value ");
  Serial.println(my_value);
  return my_value;
}


float Map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
