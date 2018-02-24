// pid variables for yaw control

float pid_valW;//TOTAL pid_val=kp*error+ki*integral+kd*prop
float errorW, last_errorW, propW, integralW, derW;
float limitW = 10;

// pid calculation function
float pidW()//function to calculate pid values
{
  // pid variables
  float kp = 24; // CONSTANT KP//oscillations
  float ki = 0.1;//.0031; // CONSTANT KI//smoothness
  float kd = 4;//.0123; // CONSTANT KD//jerks
  float yaw_val = getImuValue();

  Serial.println("///////////////////////////////////////");
  Serial.print("ref yaw  "); Serial.println(ref_yaw);
  Serial.print("yaw_val  "); Serial.println(yaw_val);
  Serial.println("///////////////////////////////////////");

//  if (abs(errorW) > 300) {
//    if (yflag == 1) {
//      errorW = 20;
//    }
//    else if (yflag == 1) {
//      errorW = -20;
//    }
//  }
//
//  else errorW = int((ref_yaw - yaw_val)); //change in data type

errorW = int((ref_yaw - yaw_val));
if (errorW>330){
  errorW=errorW-360;
}
else if (errorW<-330){
  errorW=360+errorW;
}

  Serial.print("errow");
  Serial.println(errorW);
  Serial.print("imu");
  Serial.println(yaw_val);
  propW = errorW;
  integralW = integralW + errorW;//sum of errors
  integralW = integralW > limitW ? limitW : integralW;//limiting of error stops overshooting
  integralW = (integralW < -limitW && integralW < 0) ? -limitW : integralW;
  derW = errorW - last_errorW; //rate of error
  last_errorW = errorW;
  pid_valW = kp * propW + ki * integralW + kd * derW;
  pid_valW = (pid_valW >= 240) ? 240 : pid_valW;
  pid_valW = (pid_valW <= -240) ? -240 : pid_valW;
  return (pid_valW);
}


void displayPidWValues()
{
  Serial.print("ref   W  :"); Serial.print(ref_yaw);
  Serial.print("errorW  :"); Serial.print(errorW);
  Serial.print("last_errorW  :"); Serial.print(last_errorW);
  Serial.print("proportionalW  :"); Serial.print(propW);
  Serial.print("integralW  :"); Serial.print(integralW);
  Serial.print("derivativeW  :"); Serial.print(derW);
  Serial.print("pid_valW  "); Serial.println(pid_valW);
}
